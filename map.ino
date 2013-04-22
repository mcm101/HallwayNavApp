
typedef struct
{
  int length; // in inches
  int orientation[2]; // first is closest angle from north
                      // second is first + 180 degress
} hallway;

typedef struct
{
  byte walls; // encoded in the first 4 bits
              // corresponding to direction
              // bit 0 - front
              // bit 1 - right
              // bit 2 - left
              // bit 3 - rear
  hallway halls[4]; // in order of desired path.
  int number_of_hallways;
  
} intersection;

static intersection intersects[19];
const int max_hallways = 4;  //possible hallways off of an inersection

// creates an array of intersections and hallways
// that will encode our physical map in order to 
// determine our location and guide the user to 
// the destination;
void map_init()
{  
  intersects[0].walls = B1010;  //goal! 
  intersects[0].halls[0].length = -1;  //goal!
  intersects[0].halls[1].length = 288;
  intersects[0].number_of_hallways = 2;
  
  intersects[1].walls = B0001;
  intersects[1].halls[0].length = 288;
  intersects[1].halls[1].length = 305;
  intersects[1].halls[2].length = 480;
  intersects[1].number_of_hallways = 3;
  
  intersects[2].walls = B0100;
  intersects[2].halls[0].length = 305;
  intersects[2].halls[1].length = 630;
  intersects[2].halls[2].length = 577;
  intersects[2].number_of_hallways = 3;
  
  intersects[3].walls = B0111;
  intersects[3].halls[0].length = 577;
  intersects[3].number_of_hallways = 1;
  
  intersects[4].walls = B0001;
  intersects[4].halls[0].length = 630;
  intersects[4].halls[1].length = 269;
  intersects[4].halls[2].length = 511;
  intersects[4].number_of_hallways = 3;
  
  intersects[5].walls = B0111;
  intersects[5].halls[0].length = 511;
  intersects[5].number_of_hallways = 1;
  
  intersects[6].walls = B1100;
  intersects[6].halls[0].length = 269;
  intersects[6].halls[1].length = 166;
  intersects[6].number_of_hallways = 2;
  
  intersects[7].walls = B0011;
  intersects[7].halls[0].length = 166;
  intersects[7].halls[1].length = 363;
  intersects[7].number_of_hallways = 2;
  
  intersects[8].walls = B1000;
  intersects[8].halls[0].length = 466;
  intersects[8].halls[1].length = 363;
  intersects[8].halls[2].length = 188;
  intersects[8].number_of_hallways = 3;
  
  intersects[9].walls = B1011;
  intersects[9].halls[0].length = 188;
  intersects[9].number_of_hallways = 1;
  
  intersects[10].walls = B1000;
  intersects[10].halls[0].length = 543;
  intersects[10].halls[1].length = 466;
  intersects[10].halls[2].length = 234;
  intersects[10].number_of_hallways = 3;
  
  intersects[11].walls = B0111;
  intersects[11].halls[0].length = 234;
  intersects[11].number_of_hallways = 1;
  
  intersects[12].walls = B0000;
  intersects[12].halls[0].length = 480;
  intersects[12].halls[1].length = 100;
  intersects[12].halls[2].length = 543;
  intersects[12].halls[3].length = 898;
  intersects[12].number_of_hallways = 3;
  
  intersects[13].walls = B1101;
  intersects[13].halls[0].length = 100;
  intersects[13].number_of_hallways = 1;
  
  intersects[14].walls = B1100;
  intersects[14].halls[0].length = 898;
  intersects[14].halls[1].length = 1120;
  intersects[14].number_of_hallways = 2;
  
  intersects[15].walls = B0110;
  intersects[15].halls[0].length = 1120;
  intersects[15].halls[1].length = 100;
  intersects[15].number_of_hallways = 2;
  
  intersects[16].walls = B1000;
  intersects[16].halls[0].length = 232;
  intersects[16].halls[1].length = 162;
  intersects[16].halls[2].length = 198;
  intersects[16].number_of_hallways = 3;
  
  intersects[17].walls = B0111;
  intersects[17].halls[0].length = 162;
  intersects[17].number_of_hallways = 1;
  
  intersects[18].walls = B1011;
  intersects[18].halls[0].length = 198;
  intersects[18].number_of_hallways = 1;
}


