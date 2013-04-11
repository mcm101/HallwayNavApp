const int debug  = 1;

void setup()
{
  Serial.begin(9600);
  compassSetup();
}

void loop()
{
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
  sonar = LVMaxSonarEZ4();
}

