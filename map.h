#ifndef MAP_H
#define MAP_H

#define MAX_HALLS 4  //possible hallways off of an inersection
#define NUM_INTERSECTS 19

typedef struct
{
  int length; // in inches
  int orientation; // first is closest angle from north
                      // second is first + 180 degress
} hallway;

typedef struct
{
  char walls; // encoded in the first 4 bits
              // corresponding to direction
              // bit 0 - SE
              // bit 1 - NE
              // bit 2 - NW
              // bit 3 - SW
  hallway halls[MAX_HALLS]; // mapped by bits above.
  int preferred_hall;
  int number_of_hallways;
  
} intersection;

static intersection intersects[NUM_INTERSECTS];

#endif /* MAP_H */
