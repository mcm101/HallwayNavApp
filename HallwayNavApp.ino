const int debug  = 0;
float forward;//, previous_forward;
float right;//, previous_right;
float backward;//, previous_backward;
float left;//, previous_left;
float ir_dif_error;
int sonar;//, previous_sonar;
int heading;//, previous_heading;
float height;//height of user
boolean obstacle_avoidance_left = false;//try and go left around object
boolean obstacle_avoidance_right = false;//try and go right around object
boolean roam;
const float error = .05;//5% error checking 
const int ir_max = 60;//max ir value filtering?
const int average = 5;//number of values to average
byte previous_intersection[2];//[0] most recent, [1] before that
float two_feet = 24;
byte intersection_compare;
boolean repeat;

enum state{
  ROAM,
  HALLWAY,
  INTERSECTION,
  GOAL,
}mode;


void setup()
{
  float temp1;
  float temp2;
  float temp3;
  
  compass_setup();
  sonar_setup();
  map_init();
  accel_init();
  height = sonar_read();//calibrate height, average a few values
  
  // get_sensor_data(); //for initial localize
  //localize();
  
  previous_intersection[0] = B1111;
  previous_intersection[1] = B1111;
  repeat = true;
  mode = ROAM;
  ir_dif_error = error * ir_max;

  Serial.begin(9600);


  get_ir_average();
  temp1 =  max(right, left);
  temp2 = max(forward, backward);
//  temp3 = max(temp1, temp2);
  if(forward == max(temp1, temp2))
  {
    direct(0);
  }
  else if(left == max(temp1, temp2))
  {
    direct(2700);
  }
  else if(right == max(temp1, temp2))
  {
    direct(900);
  }
  else //if(backward == max(temp1, temp2))
  {
    direct(1800);
  }
  delay(500);
  
  direct(-1); //turn the headband off
  delay(2000);
}

void loop()
{
  int new_heading;
  float difference;
  int degree;
  
  if(mode == ROAM)
  {
    Serial.println("ROAM");
    
    get_ir_average();
    difference = right - left;
    
    //both hallways present, try and center
    degree = map(abs(difference), 0, 60, 0, 450);
    if(forward < 24)  //if true -> wall in front
    {
      direct(-1);  //stop
      if(abs(difference) < ir_dif_error)  //dead end, thus intersection
      {
        direct(1800);        
        delay(500);
        direct(-1);
        mode = INTERSECTION;
      }
      else if(difference > 0)  //difference > ir_dif_error)  //right>left, go right
      {
           direct(450);
           delay(500);
           direct(-1);
      }
      else if(difference > 0)  //difference > ir_dif_error)  //right>left, go right
      {
           direct(3150);
           delay(200);
           direct(-1);
      }
      else  //default turn around....
      {
        direct(1800);
        delay(200);
        direct(-1);
      }
    }
    else  //no wall in front
    {
      if(abs(difference) < ir_dif_error  && (right < ir_max || left < ir_max))
      {
        direct(-1);
        mode = HALLWAY;
       
      }
      else if(difference > 0) //right>left, closer to left
      {
        direct(degree);
        Serial.print("difference>0 : ");
        Serial.println(degree);
      }
      else if(difference < 0) //closer to right
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
  }
  else if(mode == HALLWAY)
  {
    Serial.println("HALLWAY");
    //direct(-1);
    
    get_ir_average();
    difference = right - left;
    
    //both hallways present, try and center
    degree = map(abs(difference), 0, 60, 0, 300);
    
    if(right == ir_max && left > two_feet)// no wall on right
    {
      direct(-1);
      mode = INTERSECTION;
    }
    else if(left == ir_max && right > two_feet) //no wall on left
    {
      direct(-1);
      mode = INTERSECTION; 
    }
    else // not at intersection
    {
      if(difference > 0) //right>left, closer to left
      {
        direct(degree);
        Serial.print("difference>0 : ");
        Serial.println(degree);
      }
      else if(difference < 0) //closer to right
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
  }  
  else if(mode == INTERSECTION)
  {
    Serial.println("INTERSECTION");
    direct(-1);
    delay(150);
    direct(900);
    delay(150);
    direct(2700);
    delay(150);
    
    intersection_compare = B0000;
    heading = compass();
    //iterate through the map orientations
    for(int i = 0; i < 19; i++)
    {
       
    }
    get_ir_average():
    if(front == ir_max)
    {
      
    }
    
    
    
  }
  else if(mode == GOAL) //GOAL!!!!!
  {
      Serial.println("GOAL!");
  }
}
    
void get_sensor_data()
{
  //read into a struct?
  //average all values by reading in multiple times?
  forward = ir_read('F');
  right = ir_read('R');
  backward = ir_read('B');
  left = ir_read('L');
  sonar = sonar_read();
  heading = compass();
  //accel?  //part of take a step function instead?
}

void get_ir_average()  //average 100 ir readings
{   
  left = 0;
  right = 0;
  forward = 0;
  backward = 0;
  for(int i = 0; i < 100; i++)
  {  
    left += ir_read('L');
    right += ir_read('R');
    forward += ir_read('F');
    backward += ir_read('B');
  }
  left = left/100;
  right = right/100;
  forward = forward/100;
  backward = backward/100;
} 
 
 
  

void localize()
{
  //use sensor data and previous intersections to guess location
  //scan through list
   
  
}

boolean take_a_step(int angle)
{
  //return true if step taken
  //return false if not
  //get accel data
  //reisue command for some number of times to get user to progress
  //delap between each loop
  return true;

}
boolean following_path()
{
  //if not following path
  //put in wander mode
  return false; 
}

boolean obstacle()
{
  //check to see if there is an obstacle ahead
  if(sonar < height*(1-error))  //error needs to be smaller to detect small obstacles?
  {
    //obstacle!
    //set obstacle avoidance flag left 
    //or obstacle avoidance flag right 
    return true;
  }
  return false;
}

boolean at_intersection()  //note: deadend also considered intersection
{
  //both at least one sensor must read > max distance
  //compare byte value of intersection to the map
  //NESW  relative to the map
  //N = north, E = east, etc.
  //set previous intersections
  //previous_intersection[1] = previous_intersection[0];
  //previous_intersection[0] = this intersection
  
  get_ir_average();
  
  return false;
}

boolean at_goal()
{
  //requirements to be at goal:
  //at a hallway B1010 for open door
  //at a intersection B1110 for closed door
  //previous intersection was B0001
  //intersection before that was either B0000 or B0100
  //compass facing east(relative to map)
  //distance traveled from last intersection is about 288
  return false; 
}
