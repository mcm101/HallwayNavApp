
  //All this does is read the heading from HMC6352 and spit it out via serial

#include <Wire.h>

const int HMC6352SlaveAddress = 0x42 >> 1; // only 7 bits
const int HMC6352ReadAddress = 0x41; // internal address of the data

void compass_init()
{
  // "The Wire library uses 7 bit addresses throughout. 
  //If you have a datasheet or sample code that uses 8 bit address, 
  //you'll want to drop the low bit (i.e. shift the value one bit to the right), 
  //yielding an address between 0 and 127."
  byte outputModeCommand[] = {0x47, 0x4e, 0x00};
  byte opModeCommand[] = {0x47, 0x74, 0x62};
  
  //setup compass module
  Wire.begin();
  Wire.beginTransmission(HMC6352SlaveAddress);
  Wire.write(outputModeCommand, 3);
  Wire.write(opModeCommand, 3);
  Wire.endTransmission();
}

float compass_read()
{
  float reading = 0;
 
  for(int i = 0; i < 20; i++)
  {
    reading += compass_request();
    delay(50);
  }
  
  return reading / 20;
}

float compass_request()
{
  // Get Data
  Wire.requestFrom(HMC6352SlaveAddress, 2, true);

  // Wait for the bytes to arrive
  while (Wire.available() != 2);
  
  // The heading output data will be the value in tenths of degrees
  // from zero to 3599 and provided in binary format over the two bytes.
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  
  float headingSum = (MSB << 8) + LSB; //(MSB / LSB sum)
  float headingInt = headingSum / 10.0;
  
  if (debug)
  {
    Serial.print("Heading Degrees: ");
    Serial.println(headingInt);
  }
  
  return headingInt;
}


