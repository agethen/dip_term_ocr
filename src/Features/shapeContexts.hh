#ifndef __SHAPECONTEXTS_HH__
#define __SHAPECONTEXTS_HH__

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <utility>

#include "../include/header.hh"
#include "../Preprocessing/resize.hh"
using namespace std;

void chooseAllPoints( cBitmap * bitmap, vector<double *> & norm_hist );
void chooseSamplePoints( cBitmap * bitmap, int num_points, vector<double *> & norm_hist );
void choosePointsUniform( cBitmap * bitmap, int num_points, vector<double *> & norm_hist );
double chiSquare( double * hist_a, double * hist_b, int size );
double hungarian( double ** original, double ** assignment, int size );
double bipartiteMatching( vector<double *> & a, vector<double *> & b );
#endif
