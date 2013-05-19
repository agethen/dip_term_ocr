#include "../include/Bitmap.hh"
#include "../include/viewer.hh"

#include <iostream>
#include <cmath>

cBitmap * bitmap;

void quantizeBW( cBitmap * b );


int main( int argc, char ** argv ){

 bitmap = new cBitmap( argv[1] );
 
 quantizeBW( bitmap );


 /* OpenGL Viewer Related */
 int size = (bitmap->getWidth())*(bitmap->getHeight())*sizeof(struct Pixel);

 unsigned char * buffer = (unsigned char *) malloc( size );
 if( buffer == NULL ){ fprintf( stderr, "Could not allocate memory\n" ); return 1; }
 
 bitmap->getBitmap( buffer, size );

 glutViewer( buffer, bitmap->getWidth(), bitmap->getHeight(), argc, argv );

 free(buffer);

 return 0;
}


void quantizeBW( cBitmap * b ){
 int threshold[3] = { 224, 224, 224 };
 struct Pixel p;

 for( int i = 0; i < b->getWidth(); i++ ){
  for( int j = 0; j < b->getHeight(); j++ ){
   b->getPixel( i, j, p );
   if( p.r > threshold[0] ) p.r = 255; else p.r = 0;
   if( p.g > threshold[1] ) p.g = 255; else p.g = 0;
   if( p.b > threshold[2] ) p.b = 255; else p.b = 0;
   b->setPixel( i, j, p );
  }
 }
}











