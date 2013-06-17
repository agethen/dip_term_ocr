#ifndef __BAYSLAKES_HH__
#define __BAYSLAKES_HH__

#include <cmath>
#include <vector>
#include "../include/Bitmap.hh"

#define THRESH 0.3	//How much may the radius deviate?

using namespace std;

void mydrawline(cBitmap* bitmap,int i, int j, int x, int y );
void myExhaustiveConvexHull(cBitmap* bitmap );
void convexHull(cBitmap* bitmap );
vector<double> findBaysLakes(cBitmap * bitmap);
void tagBorders(cBitmap* bitmap);
void checkPixel(int x, int y, int z);
vector<struct Pixel> initialiseColors();

#endif
