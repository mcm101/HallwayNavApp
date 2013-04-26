#include "fir.h"

const int SLEEP_PIN = 22;
const int GSEL_PIN = 26;
const int ZERO_DETECT_PIN = 23;
const int SELF_TEST_PIN = 27;

const int X_AN_PIN = 2;
const int Y_AN_PIN = 3;
const int Z_AN_PIN = 4;

static filter *x_filt;
static filter *y_filt;
static filter *z_filt;

const float x_thresh = 0.5;
const float y_thresh = 1.5;
const float z_thresh = 0.5;

static float x_base = 0.0;
static float y_base = 0.0;
static float z_base = 0.0;

void accel_init()
{
  digitalWrite(SLEEP_PIN, HIGH);
  digitalWrite(GSEL_PIN, LOW);
  digitalWrite(SELF_TEST_PIN, HIGH);
  delay(50);
  digitalWrite(SELF_TEST_PIN, LOW);
  delay(50);
  
  float accel_coeffs[] = {1};//{-0.039405,0.26463,0.60706,0.26463,-0.039405};
  
  x_filt = fir_create(1, accel_coeffs);
  y_filt = fir_create(1, accel_coeffs);
  z_filt = fir_create(1, accel_coeffs);
  
  float x, y, z;
  
  for (int i = 0; i < 16; ++i)
  {
    x = accel_getX();
    y = accel_getY();
    z = accel_getZ();
    fir_filter(x_filt, x);
    fir_filter(y_filt, y);
    fir_filter(z_filt, z);
  }
  
  x = accel_getX();
  y = accel_getY();
  z = accel_getZ();
  x_base = fir_filter(x_filt, x);
  y_base = fir_filter(y_filt, y);
  z_base = fir_filter(z_filt, z);
  
  //Serial.println("Cal Done");
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

void accel_wait_step()
{  
  float x, y, z;
  
  Serial.println("Waiting for step");
  
  while (1)
  {
    x = accel_getX();
    y = accel_getY();
    z = accel_getZ();
    x = fir_filter(x_filt, x);
    y = fir_filter(y_filt, y);
    z = fir_filter(z_filt, z);
    //Serial.print(x);
    //Serial.print(",");
    //Serial.print(y);
    //Serial.print(",");
    //Serial.println(z);
    if ((x - x_base) / x_base > x_thresh)
    {
      break;
    }
  }
  
  Serial.println("X passed");
 /*
  while (1)
  {
    //x = accel_getX();
    y = accel_getY();
    z = accel_getZ();
    //x = fir_filter(x_filt, x);
    y = fir_filter(y_filt, y);
    z = fir_filter(z_filt, z);
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
    if ((z - z_base) / z_base > z_thresh)
    {
      break;
    }
  }
  
  Serial.println("Z passed");
  */
  
  while (1)
  {
    //x = accel_getX();
    y = accel_getY();
    //z = accel_getZ();
    //x = fir_filter(x_filt, x);
    y = fir_filter(y_filt, y);
    //z = fir_filter(z_filt, z);
    /*
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);*/
    if ((y - y_base) / y_base > y_thresh)
    {
      break;
    }
  }
  
  Serial.println("Y passed");
  
  delay(400);
}
