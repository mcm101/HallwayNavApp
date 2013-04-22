const int debug  = 1;

void setup()
{
  Serial.begin(9600);
  //compassSetup();
}

void loop()
{
  /*
  float distance;
  float angle;
  int sonar;
  distance = sharpIR('F');
  delay(500);
  distance = sharpIR('R');
  delay(500);
  distance = sharpIR('B');
  delay(500);
  distance = sharpIR('L');
  delay(500);
  angle = compass();
  delay(500);
  */
  dac_write(0, 255);
  delay(2000);
  dac_write(0, 0);
  dac_write(1, 255);
  delay(2000);
  dac_write(1, 0);
  dac_write(2, 255);
  delay(2000);
  dac_write(2, 0);
  dac_write(3, 255);
  delay(2000);
  dac_write(3, 0);
  dac_write(4, 255);
  delay(2000);
  dac_write(4, 0);
  dac_write(5, 255);
  delay(2000);
  dac_write(5, 0);
  dac_write(6, 255);
  delay(2000);
  dac_write(6, 0);
  dac_write(7, 255);
  delay(2000);
  dac_write(7, 0);
  
  //sonar = LVMaxSonarEZ4();
}

