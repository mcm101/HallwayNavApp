// Note: the distances calculate here are based 
// on 3.3 volts, the numbers will be off if 5v it used.

// the digital pin that the IR sensor is attached to
const int FRONT_PIN = 8;
const int RIGHT_PIN = 9;
const int REAR_PIN = 10;
const int LEFT_PIN = 11;

float ir_read(char sensor)
{
  float voltage;

  if (sensor == 'F')
  {
    if (debug)  Serial.print("Front");
    voltage = analogRead(FRONT_PIN);
  }
  else if (sensor == 'R')
  {
    if (debug)  Serial.print("Right");
    voltage = analogRead(RIGHT_PIN);
    Serial.print(voltage);
    Serial.print(",");
  }
  else if (sensor == 'B')
  {
    if (debug)  Serial.print("Back");
    voltage = analogRead(REAR_PIN);
  }
  else if (sensor == 'L')
  {
    if (debug)  Serial.print("Left");
    voltage = analogRead(LEFT_PIN);
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
  return (6688.7 * pow(y, -1.058)); 
}


