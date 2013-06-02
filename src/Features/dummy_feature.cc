#include "dummy_feature.hh"

double computeFeatureDummy( cBitmap * b ){
 Pixel p;
 double count = 0;

 for( int i = 0; i < b->getWidth(); i++ ){
  for( int j = 0; j < b->getHeight(); j++ ){
   b->getPixel( i, j, p );
   if( p.r + p.g + p.b < 765 ) // < 255*3
    count++;
  }
 }
 return count;
}
