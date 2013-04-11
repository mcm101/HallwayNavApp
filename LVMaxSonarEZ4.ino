/*

int incomingByte = 0;
char buffer[100];

void setup()
{
  
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  buffer[0] = '1';
  Serial.println("test");
  if(Serial1.available() > 0){
  
      
   Serial1.readBytes(buffer, 1);
  //  incomingByte = Serial1.read();
//  {
    Serial.print(buffer[0]);
    Serial.print("     -     ");
    Serial.println(buffer[0], DEC);
  }
  delay(1000);
}

*/


//analog
const int anPin = 0;
long anVolt;
/*
void setup() {
  Serial.begin(9600);
}*/
//void loop() {
int LVMaxSonarEZ4()
{
  anVolt = analogRead(anPin);
  anVolt = (anVolt * .0049)/.0098;
  if(debug)
  {
    Serial.print("Sonar Inches: ");
    Serial.println(anVolt);
  }
 // delay(500);
  return anVolt;
}



