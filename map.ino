#include "map.h"

// creates an array of intersections and hallways
// that will encode our physical map in order to 
// determine our location and guide the user to 
// the destination;
void map_init()
{  
  intersects[0].walls = B1010;
  intersects[0].halls[2].length = -1;  //goal!
  intersects[0].halls[2].orientation = 326;
  intersects[0].halls[0].length = 288;
  intersects[0].halls[0].orientation = 145;
  intersects[0].halls[1].orientation = -1;
  intersects[0].halls[3].orientation = -1;
  intersects[0].number_of_hallways = 2;
  intersects[0].preferred_hall = 2;
  
  intersects[1].walls = B0001;
  intersects[1].halls[2].length = 288;
  intersects[1].halls[2].orientation = 260;
  intersects[1].halls[1].length = 305;
  intersects[1].halls[1].orientation = 356;
  intersects[1].halls[3].length = 480;
  intersects[1].halls[3].orientation = 184;
  intersects[1].halls[0].orientation = -1;
  intersects[1].number_of_hallways = 3;
  intersects[1].preferred_hall = 2;
  
  intersects[2].walls = B0100;
  intersects[2].halls[3].length = 305;
  intersects[2].halls[3].orientation = 146;
  intersects[2].halls[0].length = 754;
  intersects[2].halls[0].orientation = 48;
  intersects[2].halls[1].length = 577;
  intersects[2].halls[1].orientation = 320;
  intersects[2].halls[2].orientation = -1;
  intersects[2].number_of_hallways = 3;
  intersects[2].preferred_hall = 3;
  
  intersects[3].walls = B0111;
  intersects[3].halls[3].length = 577;
  intersects[3].halls[3].orientation = 225;
  intersects[3].halls[2].orientation = -1;
  intersects[3].halls[1].orientation = -1;
  intersects[3].halls[0].orientation = -1;
  intersects[3].number_of_hallways = 1;
  intersects[3].preferred_hall = 3;
  
  intersects[4].walls = B0001;
  intersects[4].halls[2].length = 754;
  intersects[4].halls[2].orientation = 43;
  intersects[4].halls[3].length = 420;
  intersects[4].halls[3].orientation = 317;
  intersects[4].halls[1].length = 456;
  intersects[4].halls[1].orientation = 134;
  intersects[4].halls[0].orientation = -1;
  intersects[4].number_of_hallways = 3;
  intersects[4].preferred_hall = 2;
  
  intersects[5].walls = B0111;
  intersects[5].halls[3].length = 456;
  intersects[5].halls[3].orientation = 238;
  intersects[5].halls[2].orientation = -1;
  intersects[5].halls[1].orientation = -1;
  intersects[5].halls[0].orientation = -1;
  intersects[5].number_of_hallways = 1;
  intersects[5].preferred_hall = 3;
  
  intersects[6].walls = B1100;
  intersects[6].halls[1].length = 420;
  intersects[6].halls[1].orientation = 54;
  intersects[6].halls[0].length = 166;
  intersects[6].halls[0].orientation = 155;
  intersects[6].halls[2].orientation = -1;
  intersects[6].halls[3].orientation = -1;
  intersects[6].number_of_hallways = 2;
  intersects[6].preferred_hall = 1;
  
  intersects[7].walls = B0011;
  intersects[7].halls[2].length = 166;
  intersects[7].halls[2].orientation = 310;
  intersects[7].halls[3].length = 363;
  intersects[7].halls[3].orientation = 232;
  intersects[7].halls[1].orientation = -1;
  intersects[7].halls[0].orientation = -1;
  intersects[7].number_of_hallways = 2;
  intersects[7].preferred_hall = 2;
  
  intersects[8].walls = B1000;
  intersects[8].halls[2].length = 466;
  intersects[8].halls[2].orientation = 288;
  intersects[8].halls[1].length = 363;
  intersects[8].halls[1].orientation = 12;
  intersects[8].halls[0].length = 188;
  intersects[8].halls[0].orientation = 93;
  intersects[8].halls[3].orientation = -1;
  intersects[8].number_of_hallways = 3;
  intersects[8].preferred_hall = 2;
  
  intersects[9].walls = B1011;
  intersects[9].halls[2].length = 188;
  intersects[9].halls[2].orientation = 10;
  intersects[9].halls[3].orientation = -1;
  intersects[9].halls[1].orientation = -1;
  intersects[9].halls[0].orientation = -1;
  intersects[9].number_of_hallways = 1;
  intersects[9].preferred_hall = 2;
  
  intersects[10].walls = B1000;
  intersects[10].halls[2].length = 543;
  intersects[10].halls[2].orientation = 284;
  intersects[10].halls[0].length = 466;
  intersects[10].halls[0].orientation = 87;
  intersects[10].halls[1].length = 234;
  intersects[10].halls[1].orientation = 10;
  intersects[10].halls[3].orientation = -1;
  intersects[10].number_of_hallways = 3;
  intersects[10].preferred_hall = 2;
  
  intersects[11].walls = B0111;
  intersects[11].halls[3].length = 234;
  intersects[11].halls[3].orientation = 150;
  intersects[11].halls[2].orientation = -1;
  intersects[11].halls[1].orientation = -1;
  intersects[11].halls[0].orientation = -1;
  intersects[11].number_of_hallways = 1;
  intersects[11].preferred_hall = 3;
  
  intersects[12].walls = B0000;
  intersects[12].halls[1].length = 480;
  intersects[12].halls[1].orientation = 110;
  intersects[12].halls[3].length = 100;
  intersects[12].halls[3].orientation = 290;
  intersects[12].halls[0].length = 543;
  intersects[12].halls[0].orientation = 210;
  intersects[12].halls[2].length = 898;
  intersects[12].halls[2].orientation = 21;
  intersects[12].number_of_hallways = 4;
  intersects[12].preferred_hall = 1;
  
  intersects[13].walls = B1101;
  intersects[13].halls[1].length = 100;
  intersects[13].halls[1].orientation = 40;
  intersects[13].halls[3].orientation = -1;
  intersects[13].halls[2].orientation = -1;
  intersects[13].halls[0].orientation = -1;
  intersects[13].number_of_hallways = 1;
  intersects[13].preferred_hall = 1;
  
  intersects[14].walls = B1100;
  intersects[14].halls[0].length = 898;
  intersects[14].halls[0].orientation = 180;
  intersects[14].halls[1].length = 1120;
  intersects[14].halls[1].orientation = 65;
  intersects[14].halls[3].orientation = -1;
  intersects[14].halls[2].orientation = -1;
  intersects[14].number_of_hallways = 2;
  intersects[14].preferred_hall = 0;
  
  intersects[15].walls = B0110;
  intersects[15].halls[3].length = 1120;
  intersects[15].halls[3].orientation = 244;
  intersects[15].halls[0].length = 100;
  intersects[15].halls[0].orientation = 157;
  intersects[15].halls[2].orientation = -1;
  intersects[15].halls[1].orientation = -1;
  intersects[15].number_of_hallways = 2;
  intersects[15].preferred_hall = 3;
  
  intersects[16].walls = B1000;
  intersects[16].halls[2].length = 232;
  intersects[16].halls[2].orientation = 330;
  intersects[16].halls[1].length = 126;
  intersects[16].halls[1].orientation = 54;
  intersects[16].halls[0].length = 198;
  intersects[16].halls[0].orientation = 160;
  intersects[16].halls[3].orientation = -1;
  intersects[16].number_of_hallways = 3;
  intersects[16].preferred_hall = 2;
  
  intersects[17].walls = B0111;
  intersects[17].halls[3].length = 126;
  intersects[17].halls[3].orientation = 240;
  intersects[17].halls[2].orientation = -1;
  intersects[17].halls[1].orientation = -1;
  intersects[17].halls[0].orientation = -1;
  intersects[17].number_of_hallways = 1;
  intersects[17].preferred_hall = 3;
  
  intersects[18].walls = B1011;
  intersects[18].halls[2].length = 198;
  intersects[18].halls[2].orientation = 355;
  intersects[18].halls[3].orientation = -1;
  intersects[18].halls[1].orientation = -1;
  intersects[18].halls[0].orientation = -1;
  intersects[18].number_of_hallways = 1;
  intersects[18].preferred_hall = 2;
}


