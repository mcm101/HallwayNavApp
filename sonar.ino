const int SONAR_AN_PIN = 0;

int sonar_read()
{
  int inches = map(analogRead(SONAR_AN_PIN), 0, 1023, 0, 254);
  
  if (debug)
  {
    Serial.print("Sonar Inches: ");
    Serial.println(inches);
  }
  
  return inches;
}



