#ifndef __SEGMENTATION_HH__
#define __SEGMENTATION_HH__

#include "../include/header.hh"

struct Segment{
 cBitmap * bmap;
 int min_x;	//Minimum value of x (i.e., the position)
 int min_y;
 int max_x;	//Maximum value of x (together w position: width)
 int max_y;
};


void quantizeBW( cBitmap * b );
void findSegments( cBitmap * b, vector<Segment> & results );

#endif
