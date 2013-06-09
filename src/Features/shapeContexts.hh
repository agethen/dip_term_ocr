#ifndef __SHAPECONTEXTS_HH__
#define __SHAPECONTEXTS_HH__

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <utility>

#include "../include/header.hh"

using namespace std;

void chooseAllPoints( cBitmap * bitmap, double * norm_hist );
void chooseSamplePoints( cBitmap * bitmap, int num_points, double * norm_hist );
void choosePointsUniform( cBitmap * bitmap, int num_points, double * norm_hist );
double chiSquare( double * hist_a, double * hist_b, int size );

#endif
