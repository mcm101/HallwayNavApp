#ifndef MAP_H
#define MAP_H

#define MAX_HALLS 4  //possible hallways off of an inersection

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
  hallway halls[4]; // mapped by bits above.
  int preferred_hall;
  int number_of_hallways;
  
} intersection;

static intersection intersects[19];

#endif /* MAP_H */
