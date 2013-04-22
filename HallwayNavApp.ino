const int debug  = 0;
float forward;//, previous_forward;
float right;//, previous_right;
float backward;//, previous_backward;
float left;//, previous_left;
int sonar;//, previous_sonar;
int heading;//, previous_heading;
float height;//height of user
boolean obstacle_avoidance_left = false;//try and go left around object
boolean obstacle_avoidance_right = false;//try and go right around object
const float error = .05;//5% error checking 
const int ir_max = 60;//max ir value filtering?
const int average = 5;//number of values to average
byte previous_intersection[2];//[0] most recent, [1] before that

boolean repeat;

void setup()
{
  
  Serial.begin(9600);
  compass_setup();
  sonar_setup();
  map_init();
  accel_init();
  height = sonar_read();//calibrate height, average a few values
  
 // get_sensor_data(); //for initial localize
  //call take_a_step(direction) to line up with major direction;
  //localize();
  
  previous_intersection[0] = B1111;
  previous_intersection[1] = B1111;
  repeat = true;
}

void loop()
{
  //get_sensor_data();//do this indiviually?
  left = 0;
  right = 0;
  int difference = 0;
  if(!at_goal())
  {
    //main loop!
    
      
    //determine heading
    //make left = right ie. right/left should be 1
    for(int i = 0; i < 100; i++)
    {  
      left += ir_read('L');
      right += ir_read('R');
    }
    left = left/100;
    right = right/100;
    difference = right - left;
    int degree = map(abs(difference), 0, 60, 0, 900);
    if(difference > 0) //closer to left
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
  else
  {
    //at goal, signal done!
    //vibrate motors in a circle to signal done
  }
  //add a delay
 // delay(2000);
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
  //compare byte value of intersection to the map
  //NESW  relative to the map
  //N = north, E = east, etc.
  //set previous intersections
 // previous_intersection[1] = previous_intersection[0];
  //previous_intersection[0] = this intersection
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
