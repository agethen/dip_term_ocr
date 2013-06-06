#include "resize.hh"

void resizeImage( cBitmap * bitmap, int target_w, int target_h ){
 Pixel p;

 unsigned char * newImage = (unsigned char * ) malloc( target_w * target_h * sizeof( struct Pixel ) );
 memset( newImage, 0, target_w*target_h*sizeof( struct Pixel ) );

 double ratio_x = target_w/(double)bitmap->getWidth();
 double ratio_y = target_h/(double)bitmap->getHeight();

 for( int i = 0; i < target_h; i++ ){
  for( int j = 0; j < target_w; j++ ){
   int old_x = j/ratio_x;
   int old_y = i/ratio_y;

   bitmap->getPixel( old_x, old_y, p );
   memcpy( newImage + (i*target_w + j)*sizeof(Pixel), &p, sizeof(Pixel ) );
  }
 }

 bitmap->setBitmap( newImage, target_w, target_h, 3 );
 free( newImage );
}
