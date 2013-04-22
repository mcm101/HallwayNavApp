const int SONAR_AN_PIN = 0;

int sonar_read()
{
  int inches = analogRead(SONAR_AN_PIN) / 2;
  
  if (debug)
  {
    Serial.print("Sonar Inches: ");
    Serial.println(inches);
  }
  
  return inches;
}



