// Note: the distances calculate here are based 
// on 3.3 volts, the numbers will be off if 5v it used.

// the digital pin that the IR sensor is attached to
const int FRONT_PIN = 8;
const int RIGHT_PIN = 9;
const int REAR_PIN = 10;
const int LEFT_PIN = 11;

static filter *front_filt;
static filter *right_filt;
static filter *rear_filt;
static filter *left_filt;

void ir_init()
{
  float ir_coeffs[] = {1};//{-0.039405,0.26463,0.60706,0.26463,-0.039405};
  
  front_filt = fir_create(1, ir_coeffs);
  right_filt = fir_create(1, ir_coeffs);
  rear_filt = fir_create(1, ir_coeffs);
  left_filt = fir_create(1, ir_coeffs);
  
  float f, l, b, r;
  
  // Seed the buffers with some data
  for (int i = 0; i < 17; ++i)
  {
    fir_filter(front_filt, analogRead(FRONT_PIN));
    fir_filter(right_filt, analogRead(RIGHT_PIN));
    fir_filter(rear_filt, analogRead(REAR_PIN));
    fir_filter(left_filt, analogRead(LEFT_PIN));
  }
}

float ir_read(char sensor)
{
  float voltage;

  if (sensor == 'F')
  {
    if (debug)  Serial.print("Front");
    voltage = fir_filter(front_filt, analogRead(FRONT_PIN));
  }
  else if (sensor == 'R')
  {
    if (debug)  Serial.print("Right");
    voltage = fir_filter(right_filt, analogRead(RIGHT_PIN));
  }
  else if (sensor == 'B')
  {
    if (debug)  Serial.print("Back");
    voltage = fir_filter(rear_filt, analogRead(REAR_PIN));
  }
  else if (sensor == 'L')
  {
    if (debug)  Serial.print("Left");
    voltage = fir_filter(left_filt, analogRead(LEFT_PIN));
  }
  else 
  {
    Serial.println("invalid sensor");
    return 0;
  }
  
  if (debug)
  {
    Serial.print(" IR Inches: ");
    Serial.println(voltageToDistance(voltage));
  }
  return (voltageToDistance(voltage));
}

float voltageToDistance(float y) //return distance in inches
{
  //return (4129.936 * pow(y, -0.935) - 3.937); 
  float distance = 6688.7 * pow(y, -1.058);
  if (distance < 7.0)
    distance = 7.0;
  else if (distance > 60.0)
    distance = 60.0;
  return (distance); 
}


