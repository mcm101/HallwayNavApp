
const int SPACING = 450;
const int NUM_CHANNELS = 8;
const float DAC_RES = 255.0;
const int DAC_PWM_PINS[NUM_CHANNELS] = {2, 3, 4, 5, 6, 7, 8, 9};

void dac_write(byte channel, byte val)
{
  int scaled = 0;
  if (val > 0)
    scaled = map(val, 0, 255, 128, 153); // map to 2.5 - 3.0 V
  analogWrite(DAC_PWM_PINS[channel], scaled);
}

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
  
  if (deg < 0)
    first_strength = second_strength = 0;
  
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
