#ifndef __FEATURES_HH__
#define __FEATURES_HH__

#include "../include/Bitmap.hh"
#include "../include/header.hh"

#define PI 3.14

vector<double> computeFeatures( cBitmap * b );

///<summary>Returns array (vector&lt;vector&lt;int&gt;&gt;) with black (=0) and white (=255) values</summary>
vector<vector<int>> quantize2DArray( cBitmap * b );

///<summary> returns # (black) colored pixels </summary>
double countPixels(vector<vector<int>>* bw);

///<summary> returns the ratio of width vs. height of the bitmap </summary>
double whRatio(vector<vector<int>>* bitmap);

///<summary> returns circularity of character, input: bitmap and convex hull </summary>
///<remarks> Adjusted algorithm that makes an approximation: surface -> weight convex hull, circumference -> weight original bitmap
double circularity(vector<vector<int>>* bitmap,vector<vector<int>>* convexHull);

void myTempConvexHull(cBitmap* bm);

#endif
