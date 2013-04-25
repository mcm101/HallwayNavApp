#include "fir.h"
#include "map.h"

const int debug  = 0;

float forward, right, backward, left;
float ir_dif_error;
int sonar;
int heading;

const float error = .05;//5% error checking 
const int ir_max = 60;//max ir value filtering?
const float two_feet = 24;
const int nav_fov = 450;

enum state
{
  ROAM,
  HALLWAY,
  INTERSECTION,
  GOAL,
} 
mode;

void setup()
{
  float temp1;
  float temp2;
  float temp3;

  Serial.begin(9600);
  compass_init();
  sonar_init();
  map_init();
  accel_init();
  ir_init();

  mode = ROAM;
  ir_dif_error = error * ir_max;

  get_ir_data();
  temp1 = max(right, left);
  temp2 = max(forward, backward);

  // initial localization, tell user to turn toward the
  // the area with the most space and begin roaming
  if (forward == max(temp1, temp2))
  {
    direct(0);
  }
  else if (left == max(temp1, temp2))
  {
    direct(2700);
  }
  else if (right == max(temp1, temp2))
  {
    direct(900);
  }
  else
  {
    direct(1800);
  }

  accel_wait_step();

  direct(-1); // turn the headband off
}

void loop()
{
  float difference;
  int degree;

  get_ir_data();
  difference = right - left;

  // if hallways present, try and center
  degree = map(abs(difference), 0, ir_max, 0, nav_fov);

  if (mode == ROAM)
  {
    Serial.println("ROAM");

    // both hallways present, try and center
    degree = map(abs(difference), 0, ir_max, 0, nav_fov);
    
    if (forward < two_feet)  // if true -> wall in front
    {
      if (abs(difference) < ir_dif_error)  //dead end, thus intersection
      {
        mode = INTERSECTION;
        return;
      }
      else if (difference > 0) // right > left, go right
      {
        direct(450);
      }
      else if (difference < 0) // left > right, go left
      {
        direct(3150);
      }
      else  // default turn around? shouldn't get here
      {
        direct(1800);
      }
    }
    else  // no wall in front
    {
      if (abs(difference) < ir_dif_error  && (right < ir_max || left < ir_max))
      {
        mode = HALLWAY;
        return;
      }
      else if (difference > 0) // closer to left, bare right
      {
        direct(degree);
        Serial.print("difference>0 : ");
        Serial.println(degree);

      }
      else if (difference < 0) // closer to right, bare left
      {
        direct(3600 - degree);
        Serial.print("difference<0 : ");
        Serial.println(3600 - degree);
      }
      else //middle
      {
        Serial.println("middle");
        direct(0);
      }
    }
    
    accel_wait_step();
    direct(-1);
  }
  else if (mode == HALLWAY)
  {
    Serial.println("HALLWAY");

    if (right == ir_max && left > two_feet) // no wall on right
    {
      mode = INTERSECTION;
      return;
    }
    else if (left == ir_max && right > two_feet) // no wall on left
    {
      mode = INTERSECTION; 
      return;
    }
    else // not at intersection, stay center
    {
      if (difference > 0) // closer to left, bare right
      {
        direct(degree);
        Serial.print("difference>0 : ");
        Serial.println(degree);
      }
      else if (difference < 0) // closer to right, bare left
      {
        direct(3600 - degree);
        Serial.print("difference<0 : ");
        Serial.println(3600 - degree);
      }
      else //middle
      {
        Serial.println("middle");
        direct(0);
      }
    }
    
    accel_wait_step();      
    direct(-1);
  }  
  else if (mode == INTERSECTION)
  {
    Serial.println("INTERSECTION");

    int num_hallways = 0;
    
    if (backward == ir_max)
    {
      num_hallways++;
      degree = 1800;
    }
    if (left == ir_max)
    {
      num_hallways++;
      degree = 2700;
    }
    if (right == ir_max)
    {
      num_hallways++;
      degree = 900;
    }
    if (forward == ir_max)
    {
      num_hallways++;
      degree = 0;
    }

    heading = compass_read();
    //iterate through the map orientations
    for(int i = 0; i < 19; i++)
    {
      //intersects[i];
    }
  }
  else if(mode == GOAL) //GOAL!!!!!
  {
    Serial.println("GOAL!");
  }
}

void get_ir_data()
{
  left = ir_read('L');
  right = ir_read('R');
  forward = ir_read('F');
  backward = ir_read('B');
}

