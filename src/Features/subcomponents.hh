#ifndef __SUBCOMPONENTS_HH__
#define __SUBCOMPONENTS_HH__

#include "../include/header.hh"

#define CUTOFF 12
#define CUTOFF_DIA 12
/* Functions are pretty explanatory */
//Uses boundary instead of skeleton at
int countVerticalLines( cBitmap * bitmap );
int countHorizontalLines( cBitmap * bitmap );

/* Count diagonals. TODO: Not as stable as functions above */
int countDiagonals( cBitmap * bitmap );
#endif
