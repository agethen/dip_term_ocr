#ifndef __EULER_HH__
#define __EULER_HH__

#include <cmath>
#include <vector>
#include "../include/Bitmap.hh"


struct CharacterComponent{
 unsigned short id;
 unsigned char color;
 bool connectsBorder;
 int pos[2];
};


/* Find the Euler number for this bitmap */
/* Bitmap is assumed to be black/white */
int getEulerNumber( cBitmap * bitmap );

/* Helper functions. You should probably call getEulerNumber() instead */
int getNumberOfConnectedComponents( vector<CharacterComponent> & data );
int getNumberOfLakes( vector<CharacterComponent> & data );
#endif
