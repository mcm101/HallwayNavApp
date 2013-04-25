const int SONAR_AN_PIN = 15;
const int SONAR_RX_PIN = 10;

void sonar_setup()
{
  delay(250); // power-up
  digitalWrite(SONAR_RX_PIN, HIGH); // calibration
  delayMicroseconds(50);
  digitalWrite(SONAR_RX_PIN, LOW);
  delay(150); // first cycle
}

void sonar_fire(boolean oneShot)
{
  digitalWrite(SONAR_RX_PIN, HIGH); 
  if (oneShot)
  {
    delayMicroseconds(50);
    digitalWrite(SONAR_RX_PIN, LOW);
  }
}

int sonar_read()
{
  delay(50);
  int inches = analogRead(SONAR_AN_PIN);
  
  if (debug)
  {
    Serial.print("Sonar Inches: ");
    Serial.println(inches);
  }
  
  return inches;
}



