#ifndef __SUBCOMPONENTS_HH__
#define __SUBCOMPONENTS_HH__

#include <iostream>

#include "../include/Bitmap.hh"
#include "../include/skeletonisation.hh"
#include "../include/setup.hh"
#include "../include/viewer.hh"
#include "../Segmentation/segmentation.hh"

/* Functions are pretty explanatory */
/* Remember to call setup_matrix() from include/setup.cc first! */
int countVerticalLines( cBitmap * bitmap );
int countHorizontalLines( cBitmap * bitmap );

#endif
