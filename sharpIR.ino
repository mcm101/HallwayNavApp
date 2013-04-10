//note: the distances calculate here are based 
//on 3.3 volts, the numbers will be off if 5v it used.

const int frontIR = 8;  // the pin that the IR sensor's data is attached to
const int rightIR = 9;
const int backIR = 10;
const int leftIR = 11;

float sharpIR(char sensor) {
  float voltage;

  if(sensor == 'F')
  {
    if(debug)  Serial.print("Front");
    voltage = analogRead(frontIR);
  }
  else if(sensor == 'R')
  {
    if(debug)  Serial.print("Right");
    voltage = analogRead(rightIR);
  }
  else if(sensor == 'B')
  {
    if(debug)  Serial.print("Back");
    voltage = analogRead(backIR);
  }
  else if(sensor == 'L')
  {
    if(debug)  Serial.print("Left");
    voltage = analogRead(leftIR);
  }
  else 
  {
    Serial.println("invalid sensor");
    return 0;
  }
  if(debug)
  {
    Serial.print(" IR Inches: ");
    Serial.println(voltageToDistance(voltage));
  }
  return (voltageToDistance(voltage));
}

float voltageToDistance(float y) //return distance in inches
{
  return (4129.936 * pow(y, -0.935) - 3.937); 
}


