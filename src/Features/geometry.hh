#ifndef __GEOMETRY_HH__
#define __GEOMETRY_HH__

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <utility>

#include "../include/header.hh"

using namespace std;
struct Geometry
{
	double avg_dis; // average distance from the centre of mass
	double Max_dis; // maximum distance from the centre of mass
	int area;		// area of the character
	int wc_x;		// weight centre of character in the x direction
	int wc_y;		// weight centre of character in the y direction
};


Geometry geometry( cBitmap * bitmap );
void computeGeometry( cBitmap * bitmap );

double getAverageDistance();
double getMaximumDistance();
double getArea();
void getWeightCenter( pair<int,int> & a );
#endif
