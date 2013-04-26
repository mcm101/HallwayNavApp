#include "fir.h"
#include "map.h"

const int debug  = 0;

float forward, right, backward, left;
float ir_diff_error;
int sonar;
float heading;
boolean from_intersection = false;
int intersect_count;
int length;

const int ir_max = 60;//max ir value filtering?
const float two5_feet = 30;
const float four_feet = 48;
const int nav_fov = 450;
const float compass_error = 0.13;
const float ir_error = 0.10;
const int intersect_thresh = 0;
const int STEP_LENGTH = 25; // inches

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
  map_init();
  accel_init();
  ir_init();

  intersect_count = 0;

  ir_diff_error = ir_error * ir_max;

  get_ir_data();
  //temp1 = max(right, left);
  //temp2 = max(forward, backward);

  // initial localization, tell user to turn toward the
  // the area with the most space and begin roaming
  if (forward > four_feet)
  {
    direct(0);
  }
  else if (left > four_feet)
  {
    direct(2700);
  }
  else if (right > four_feet)
  {
    direct(900);
  }
  else
  {
    direct(1800);
  }

  accel_wait_step();

  direct(-1); // turn the headband off
  
  sonar_init();
}

void loop()
{
  float difference;
  int degree;
  
  /*
  // Object detection
  while (sonar_object())
  {
    delay(3000); // wait to see if the object (person) moves out of the way
    if (sonar_object())
    {
      direct(1800);
      accel_wait_step();
      direct(-1);
      break;
    }
  }
  */

  get_ir_data();
  difference = right - left;

  // if hallways present, try and center
  degree = map(abs(difference), 0, ir_max, 0, nav_fov);

  if (mode == ROAM)
  {
    Serial.println("ROAM");

    // both hallways present, try and center
    degree = map(abs(difference), 0, ir_max, 0, nav_fov);

    if (forward < two5_feet)  // if true -> wall in front
    {
      if (abs(difference) < ir_diff_error)  //dead end, thus intersection
      {
        if (intersect_count++ > intersect_thresh)
        {
          mode = INTERSECTION;
          return;
        }
      }
      else
      {
        intersect_count = 0;        
      }

      if (difference > 0) // right > left, go right
      {
        direct(degree);
      }
      else if (difference < 0) // left > right, go left
      {
        direct(3599-degree);
      }
      else  // default turn around? shouldn't get here
      {
        direct(1800);
      }
    }
    else  // no wall in front
    {
      //intersect_count = 0;
      if (abs(difference) < ir_diff_error  && (right < ir_max || left < ir_max))
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
        direct(3599 - degree);
        Serial.print("difference<0 : ");
        Serial.println(3599 - degree);
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

    if (forward < two5_feet)  // if true -> wall in front
    {
      mode = INTERSECTION;
      return;
    }
    else if (right == ir_max && left > two5_feet && !from_intersection) // no wall on right
    {
      if (intersect_count++ > intersect_thresh)
      {
        mode = INTERSECTION;
        return;
      }
    }
    else if (left == ir_max && right > two5_feet && !from_intersection) // no wall on left
    {
      if (intersect_count++ > intersect_thresh)
      {
        mode = INTERSECTION;
        return;
      }
    }
    else // not at intersection, stay center
    {
      intersect_count = 0;
    }

    if (from_intersection)
    {
      direct(0);
      if (left != ir_max && right != ir_max)
        from_intersection = false;
    }
    else if (difference > 0) // closer to left, bare right
    {
      direct(degree);
      Serial.print("difference>0 : ");
      Serial.println(degree);
    }
    else if (difference < 0) // closer to right, bare left
    {
      direct(3599 - degree);
      Serial.print("difference<0 : ");
      Serial.println(3599 - degree);
    }
    else //middle
    {
      Serial.println("middle");
      direct(0);
    }

    accel_wait_step();      
    direct(-1);
  }  
  else if (mode == INTERSECTION)
  {
    intersect_count = 0;
    int i = 0;
    int front_bit, right_bit, back_bit, left_bit;
    int index;
    boolean skip_step = false;

    while (1)
    {
      int open_hallway_count = 0;
      boolean open_hallway[4] = {
        false, false, false, false            };
      int hallway_encode = 0; 
      int intersect_index = -1, hall_index = -1;

      Serial.println("INTERSECTION");

      int num_hallways = 0;
      get_ir_data();
      if(ir_max - backward < ir_diff_error)
      {
        open_hallway_count++;
        degree = 1800; 
      }
      if(ir_max - left < ir_diff_error)
      {  
        open_hallway_count++;
        degree = 2700; 
      }
      if(ir_max - right < ir_diff_error)
      {
        open_hallway_count++;
        degree = 900; 
      }
      if(ir_max - forward < ir_diff_error)
      {
        open_hallway_count++;
        degree = -1; 
      }

      if (!skip_step)
      {
        direct(degree);
        if (degree > 0)
          accel_wait_step();
        direct(-1);
      }

      get_ir_data();

      if(ir_max - left < ir_diff_error)
      {
        open_hallway[3] = true;
      }
      if(ir_max - backward < ir_diff_error)
      {
        open_hallway[2] = true;
      }
      if(ir_max - right < ir_diff_error)
      {
        open_hallway[1] = true;
      }
      if(ir_max - forward < ir_diff_error)
      {
        open_hallway[0] = true;
      }

      delay(500);
      heading = compass_read();
      Serial.println(heading);

      for (i; i < NUM_INTERSECTS && intersect_index < 0; i++)
      {
        if (open_hallway_count == intersects[i].number_of_hallways)
        {
          Serial.println(open_hallway_count);
          for (int j = 0; j < MAX_HALLS && hall_index < 0; j++)
          {
            if (intersects[i].halls[j].orientation != -1)
            {
              Serial.println(intersects[i].halls[j].orientation);

              float diff = heading - intersects[i].halls[j].orientation;
              if (abs(diff) > 180)
              {
                if (diff > 0)
                  diff = intersects[i].halls[j].orientation - heading;
                diff += 360;
              }

              if ((abs(diff) / 90) < compass_error)
              {
                Serial.println("Passed compass");
                front_bit = index = j;
                hallway_encode = (1 << j);  //front!

                index = (index - 1) < 0 ? 3 : index - 1;
                right_bit = index;
                hallway_encode |= open_hallway[1] ? (1 << index) : 0;
                index = (index - 1) < 0 ? 3 : index - 1;
                back_bit = index;
                hallway_encode |= open_hallway[2] ? (1 << index) : 0;
                index = (index - 1) < 0 ? 3 : index - 1;
                left_bit = index;
                hallway_encode |= open_hallway[3] ? (1 << index) : 0;

                Serial.println(hallway_encode);
                if (((~intersects[i].walls & 0x0F) & hallway_encode) == hallway_encode)
                {
                  intersect_index = i;
                  hall_index = intersects[i].preferred_hall;
                  Serial.print("Intersection: ");
                  Serial.print(i);
                  Serial.print(" Hallway: ");
                  Serial.print(hall_index);
                  Serial.print(" Diff: ");
                  Serial.println((abs(diff)));
                }
              }
            }
          }
        }
      }

      if (hall_index == front_bit)
        degree = 0; 
      else if (hall_index == right_bit)
        degree = 900;
      else if (hall_index == back_bit)
        degree = 1800; 
      else if (hall_index == left_bit)
        degree = 2700;
      else
        degree = 0; // already faced straight and its open

      if (!skip_step)
      {
        direct(degree);
        accel_wait_step();
        direct(-1);
      }

      if (intersect_index >= 0 && hall_index >= 0)
      {
        if (intersect_index == 1 && hall_index == 2)
        {
          mode = GOAL;
          length = intersects[intersect_index].halls[hall_index].length;
          return;
        }
        else
        {
          from_intersection = true;
          mode = HALLWAY;
        }
        break;
      }
      else if (i < NUM_INTERSECTS)
      {
        skip_step = true;
        continue;
      }
      else
      {
        from_intersection = true;
        mode = HALLWAY;
        break;
      }
    }
  }
  else if (mode == GOAL) //GOAL!!!!!
  {
    Serial.println("GOAL!");

    if (difference > 0) // closer to left, bare right
    {
      direct(degree);
      Serial.print("difference>0 : ");
      Serial.println(degree);
    }
    else if (difference < 0) // closer to right, bare left
    {
      direct(3599 - degree);
      Serial.print("difference<0 : ");
      Serial.println(3599 - degree);
    }
    else //middle
    {
      Serial.println("middle");
      direct(0);
    }

    accel_wait_step();
    length -= STEP_LENGTH;
    if (length < 0)
    {
      finished();
      while (1);
    }
  }
}

void get_ir_data()
{
  left = 0;
  right = 0;
  forward = 0;
  backward = 0;

  for (int i = 0; i < 100; i++)
  {
    left += ir_read('L');
    right += ir_read('R');
    forward += ir_read('F');
    backward += ir_read('B');
  }

  left /= 100;
  right /= 100;
  forward /= 100;
  backward /= 100;
}
