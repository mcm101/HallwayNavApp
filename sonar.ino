const int SONAR_AN_PIN = 15;
const int SONAR_RX_PIN = 10;

static filter *sonar_filt;

static float dist_base = 0.0;

const float dist_thresh = 0.2;

void sonar_init()
{
  delay(250); // power-up
  digitalWrite(SONAR_RX_PIN, HIGH); // calibration
  delay(150); // first cycle (calibration)
  
  float sonar_coeffs[] = {0.00018855, -0.006088, -0.022433, -0.039895,
                          -0.031307, 0.030367, 0.14061, 0.25099,
                          0.29763, 0.25099, 0.14061, 0.030367,
                          -0.031307, -0.039895, -0.022433, -0.006088, 0.00018855};
  
  sonar_filt = fir_create(17, sonar_coeffs);
  
  for (int i = 0; i < 16; ++i)
  {
    sonar_read();
    delay(50);
  }
  
  digitalWrite(SONAR_RX_PIN, LOW);
  
  dist_base = sonar_read();
}

void sonar_fire(boolean oneShot)
{
  digitalWrite(SONAR_RX_PIN, HIGH);
  if (oneShot)
  {
    delay(1);
    digitalWrite(SONAR_RX_PIN, LOW);
  }
}

float sonar_read()
{
  float inches = fir_filter(sonar_filt, analogRead(SONAR_AN_PIN)) * 0.7422;
  
  if (debug)
  {
    Serial.print("Sonar Inches: ");
    Serial.println(inches);
  }
  
  return inches;
}

boolean sonar_object()
{
  float dist;
  
  for (int i = 0; i < 16; ++i)
  {
    dist = sonar_read();
    delay(50);
  }
  
  //return dist;
  
  if (abs(dist - dist_base) / dist_base > dist_thresh) return true;
  
  return false;
}



