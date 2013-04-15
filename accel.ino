
const int SLEEP_PIN = 10;
const int GSEL_PIN = 11;
const int ZERO_DETECT_PIN = 12;
const int SELF_TEST_PIN = 13;

const int X_AN_PIN = 8;
const int Y_AN_PIN = 9;
const int Z_AN_PIN = 10;

void accel_init()
{
  digitalWrite(SLEEP_PIN, HIGH);
  digitalWrite(GSEL_PIN, LOW);
  digitalWrite(SELF_TEST_PIN, HIGH);
  delay(5);
  digitalWrite(SELF_TEST_PIN, LOW);
}

int accel_getX()
{
  return analogRead(X_AN_PIN);
}

int accel_getY()
{
  return analogRead(Y_AN_PIN);
}

int accel_getZ()
{
  return analogRead(Z_AN_PIN);
}
