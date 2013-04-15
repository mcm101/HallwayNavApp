
  //All this does is read the heading from HMC6352 and spit it out via serial

#include <Wire.h>

const int HMC6352SlaveAddress = 0x42 >> 1; // only 7 bits
const int HMC6352ReadAddress = 0x41; // internal address of the data

int headingValue;

void compassSetup()
{
  // "The Wire library uses 7 bit addresses throughout. 
  //If you have a datasheet or sample code that uses 8 bit address, 
  //you'll want to drop the low bit (i.e. shift the value one bit to the right), 
  //yielding an address between 0 and 127."
  byte outputModeCommand[] = {0x47, 0x4e, 0x00};
  byte opModeCommand[] = {0x47, 0x74, 0x62};
  
  //setup compass module
  Wire.beginTransmission(HMC6352SlaveAddress);
  Wire.write(outputModeCommand, 3);
  Wire.write(opModeCommand, 3);
  Wire.endTransmission();
}

float compass()
{
  //"Get Data. Compensate and Calculate New Heading"\  
  Wire.beginTransmission(HMC6352SlaveAddress);
  Wire.write(HMC6352ReadAddress);              // The "Get Data" command
  Wire.endTransmission();

  //time delays required by HMC6352 upon receipt of the command
  //Get Data. Compensate and Calculate New Heading : 6ms
  delay(6);

  Wire.requestFrom(HMC6352SlaveAddress, 2); //get the two data bytes, MSB and LSB

  //"The heading output data will be the value in tenths of degrees
  //from zero to 3599 and provided in binary format over the two bytes."
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  
  float headingSum = (MSB << 8) + LSB; //(MSB / LSB sum)
  float headingInt = headingSum / 10;
  
  if (debug)
  {
    Serial.print("Heading Degrees: ");
    Serial.println(headingInt);
  }
  
  return headingInt;
}

