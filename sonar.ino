const int SONAR_AN_PIN = 0;
const int SONAR_RX_PIN = 10;
void sonar_setup()
{
  delay(250);
  digitalWrite(SONAR_RX_PIN, HIGH);
}
int sonar_read()
{
  digitalWrite(SONAR_RX_PIN, HIGH);
  
  //delayMicroseconds(20);
 // digitalWrite(SONAR_RX_PIN, LOW);
  delay(50);
  int inches = analogRead(SONAR_AN_PIN)/2;
  
  if (debug)
  {
    Serial.print("analog Sonar Inches: ");
    Serial.println(inches);
  }
  
  return inches;
}



