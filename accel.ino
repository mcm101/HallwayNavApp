
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
