#ifndef __CIRCULARITY_HH__
#define __CIRCULARITY_HH__

#include <cmath>
#include <vector>
#include "../include/Bitmap.hh"

#define THRESH 0.2	//How much may the radius deviate?

using namespace std;

struct CircleComponent{
 int min_x;
 int min_y;
 int max_x;
 int max_y;
 int center_x;
 int center_y;
};

#endif
