#include <SPI.h>

const int LOAD_PIN = 13;

void dac_init()
{
  digitalWrite(LOAD_PIN, 1);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE0);
}

void dac_write(byte channel, byte val)
{
  SPI.begin();
  
  channel <<= 1;
  
  SPI.transfer(channel);
  SPI.transfer(val);
  
  SPI.end();
  
  digitalWrite(LOAD_PIN, 0);
  delayMicroseconds(1);
  digitalWrite(LOAD_PIN, 1);
}

const int SPACING = 450;
const int NUM_CHANNELS = 8;
const float DAC_RES = 255.0;

void direct(int deg)
{
  float temp;
  
  int first_chan = deg / SPACING;
  int second_chan = first_chan + 1;
  
  int first_strength = SPACING - (deg % SPACING);
  temp = DAC_RES / (float)SPACING * (float)first_strength;
  first_strength = round(temp);
  
  int second_strength = deg % SPACING;
  temp = DAC_RES / (float)SPACING * (float)second_strength;
  second_strength = round(temp);
  
  for (int i = 0; i < NUM_CHANNELS; i++)
  {
    if (i == first_chan)
      dac_write(i, first_strength);
    else if (i == second_chan)
      dac_write(i, second_strength);
    else
      dac_write(i, 0);
  }
  
}
