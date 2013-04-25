
const int SLEEP_PIN = 22;
const int GSEL_PIN = 26;
const int ZERO_DETECT_PIN = 23;
const int SELF_TEST_PIN = 27;

const int X_AN_PIN = 2;
const int Y_AN_PIN = 3;
const int Z_AN_PIN = 4;

void accel_init()
{
  digitalWrite(SLEEP_PIN, HIGH);
  digitalWrite(GSEL_PIN, LOW);
  digitalWrite(SELF_TEST_PIN, HIGH);
  delay(50);
  digitalWrite(SELF_TEST_PIN, LOW);
  delay(50);
}

float accel_getX()
{
  return map(analogRead(X_AN_PIN), 0, 1023, -1500, 1500) / 1000.0;
}

float accel_getY()
{
  return map(analogRead(Y_AN_PIN), 0, 1023, -1500, 1500) / 1000.0;
}

float accel_getZ()
{
  return map(analogRead(Z_AN_PIN), 0, 1023, -1500, 1500) / 1000.0;
}
