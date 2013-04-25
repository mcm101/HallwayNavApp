#include "fir.h"
#include "map.h"

const int debug  = 0;

float forward, right, backward, left;
float ir_dif_error;
int sonar;
int heading;

const int ir_max = 60;//max ir value filtering?
const float two_feet = 24;
const int nav_fov = 450;
const float compass_error = 0.10;
const float ir_error = 0.05;

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

  ir_dif_error = ir_error * ir_max;

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
    int open_hallway_count = 0;
    boolean open_hallway[4];
    int hallway_encode = 0; 
    int index; 

    Serial.println("INTERSECTION");

    int num_hallways = 0;
    get_ir_data();
    if(backward == ir_max)
    {
      open_hallway_count++;
      degree = 1800; 
    }
    if(left == ir_max)
    {  
      open_hallway_count++;
      degree = 2700; 
    }
    if(right == ir_max)
    {
      open_hallway_count++;
      degree = 900; 
    }
    if(forward == ir_max)
    {
      open_hallway_count++;
      degree = 0; 
    }
    direct(degree);
    accel_wait_step();
    get_ir_data();

    if(left == ir_max)
    {
      open_hallway[3] = true;
    }
    if(backward == ir_max)
    {
      open_hallway[2] = true;
    }
    if(right == ir_max)
    {
      open_hallway[1] = true;
    }
    if(forward == ir_max)
    {
      open_hallway[0] = true;
    }

    for(int i = 0; i < NUM_INTERSECTS; i++)
    {
      if(open_hallway_count == intersects[i].number_of_hallways)
      {
        for(int j = 0; j < 4; j++)
        {
          if((abs(heading - intersects[i].halls[j].orientation) / 90) < compass_error )
          {
            hallway_encode = (1 << j);  //front!
  
            index = (index - 1) < 0 ? 3 : index - 1;
            hallway_encode |= open_hallway[1] ? (1 << index) : 0;
            index = (index - 1) < 0 ? 3 : index - 1;
            hallway_encode |= open_hallway[2] ? (1 << index) : 0;
            index = (index - 1) < 0 ? 3 : index - 1;
            hallway_encode |= open_hallway[3] ? (1 << index) : 0;
  
  
  
            if(~intersects[i].walls & (1 << j) == (1 << j))
            {
  
            }     
          }
        }
      }
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


