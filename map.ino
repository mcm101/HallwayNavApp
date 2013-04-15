
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
  hallway halls[4]; // in order of orientation from north.
} intersection;

static intersection intersects[10];

// creates an array of intersections and hallways
// that will encode our physical map in order to 
// determine our location and guide the user to 
// the destination;
void map_init()
{
  
  
}


