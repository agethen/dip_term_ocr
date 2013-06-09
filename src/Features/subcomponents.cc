#include "subcomponents.hh"

#define CUTOFF 12

/* Very simple functions, might need some revamping */
int parseVertical( cBitmap * b, int x, int y ){
 int ly = 0;
 Pixel p;
 b->getPixel( x, y, p );

 while( true ){
  if( y+ly >= b->getHeight() ) break;

  b->getPixel( x, y+ly, p );

  if( p.r != 0 ){
   break;
  }else{   
   p.r = 1;
   b->setPixel( x, y+ly, p );
   ly++;
  }
 }
 return ly;
}

int parseHorizontal( cBitmap * b, int x, int y ){
 int lx = 0;
 Pixel p;
 b->getPixel( x, y, p );

 while( true ){
  if( x+lx >= b->getWidth() ) break;

  b->getPixel( x+lx, y, p );

  if( p.r != 0 ){
   break;
  }else{   
   p.r = 1;
   b->setPixel( x+lx, y, p );
   lx++;
  }
 }
 return lx;
}





int countVerticalLines( cBitmap * bitmap ){
 int size = bitmap->getWidth()*bitmap->getHeight()*sizeof( Pixel );
 int numberOfLines = 0;

 /* Create a copy */
 cBitmap * copy = new cBitmap();

 unsigned char * t = (unsigned char*)malloc( size );
 bitmap->getBitmap( t, size );
 copy->setBitmap( t, bitmap->getWidth(), bitmap->getHeight(), bitmap->getBPP() );
 free( t );
 
 extractBoundary( bitmap, copy );

 /* Parse Lines */
 Pixel p;
 int length = 0;
 for( int i = 0; i < copy->getHeight(); i++ ){
  for( int j = 0; j < copy->getWidth(); j++ ){
   copy->getPixel( j, i, p );
   if( p.r != 0 ) continue;

   length = parseVertical( copy, j, i );
   if( length >= CUTOFF ){
    numberOfLines++;
   }
  }
 }
 delete copy;

 return numberOfLines;
}

int countHorizontalLines( cBitmap * bitmap ){
 int size = bitmap->getWidth()*bitmap->getHeight()*sizeof( Pixel );
 int numberOfLines = 0;

 /* Create a copy */
 cBitmap * copy = new cBitmap();

 unsigned char * t = (unsigned char*)malloc( size );
 bitmap->getBitmap( t, size );
 copy->setBitmap( t, bitmap->getWidth(), bitmap->getHeight(), bitmap->getBPP() );
 free( t );
 
 extractBoundary( bitmap, copy );

 /* Parse Lines */
 Pixel p;
 int length = 0;
 for( int i = 0; i < copy->getWidth(); i++ ){
  for( int j = 0; j < copy->getHeight(); j++ ){
   copy->getPixel( i, j, p );
   if( p.r != 0 ) continue;

   length = parseHorizontal( copy, i, j );

   if( length >= CUTOFF ){
    numberOfLines++;
   }
  }
 }

 delete copy;

 return numberOfLines;
}
