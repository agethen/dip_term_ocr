#include "subcomponents.hh"

/* Very simple functions, might need some revamping */
int parseHorizontal( cBitmap * b, int x, int y ){
 int ly = 0;
 Pixel p;
 b->getPixel( x, y, p );

 while( true ){
  if( y+ly >= b->getHeight() ) break;

  b->getPixel( x, y+ly, p );

  //After skeletonization, we sometimes have gaps of 1 pixel (see 'E' etc).
  //Allow 1 missing black pixel
  if( p.r != 0 ){
   if( y+ly >= b->getHeight()-1 ) break;
   b->getPixel( x, y+ly+1, p );
   if( p.r != 0 ){ 	//Following pixel is also white -> break
    break;
   }else{		//There is actually a black pixel. Advance by 2.
    b->getPixel( x, y+ly, p );
    p.r = 1;
    b->setPixel( x, y+ly, p );
    b->getPixel( x, y+ly+1, p );
    p.r = 1;
    b->setPixel( x, y+ly+1, p );
    ly += 2;
   }
  }else{   
   p.r = 1;
   b->setPixel( x, y+ly, p );
   ly++;
  }
 }
 return ly;
}

int parseVertical( cBitmap * b, int x, int y ){
 int lx = 0;
 Pixel p;
 b->getPixel( x, y, p );

 while( true ){
  if( x+lx >= b->getWidth() ) break;

  b->getPixel( x+lx, y, p );

  //After skeletonization, we sometimes have gaps of 1 pixel (see 'E' etc).
  //Allow 1 missing black pixel
  if( p.r != 0 ){
   if( x+lx >= b->getWidth()-1 ) break;
   b->getPixel( x+lx+1, y, p );
   if( p.r != 0 ){ 	//Following pixel is also white -> break
    break;
   }else{		//There is actually a black pixel. Advance by 2.
    b->getPixel( x+lx, y, p );
    p.r = 1;
    b->setPixel( x+lx, y, p );
    b->getPixel( x+lx+1, y, p );
    p.r = 1;
    b->setPixel( x+lx+1, y, p );
    lx += 2;
   }
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
 
 /* Do Skeletonization */
 hit_miss Kick( copy );
 int result;
 do{ result = Kick.skeleton(); Kick.shift(); }while( result );
 Kick.Bridge();
 Kick.shift();
 Kick.exportToBitmap( copy );

 /* Parse Lines */
 Pixel p;
 int length = 0;
 for( int i = 0; i < copy->getHeight(); i++ ){
  for( int j = 0; j < copy->getWidth(); j++ ){
   copy->getPixel( j, i, p );
   if( p.r != 0 ) continue;

   length = parseHorizontal( copy, j, i );
   if( length >= 12 ){
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
 
 /* Do Skeletonization */
 hit_miss Kick( copy );

 int result;
 do{ result = Kick.skeleton(); Kick.shift(); }while( result );
 Kick.Bridge();
 Kick.shift();
 Kick.exportToBitmap( copy );

 /* Parse Lines */
 Pixel p;
 int length = 0;
 for( int i = 0; i < copy->getWidth(); i++ ){
  for( int j = 0; j < copy->getHeight(); j++ ){
   copy->getPixel( i, j, p );
   if( p.r != 0 ) continue;

   length = parseVertical( copy, i, j );
   if( length >= 11 ){
    numberOfLines++;
   }
  }
 }
 delete copy;

 return numberOfLines;
}

int main( int argc, char ** argv ){
 if( argc != 2 ) return 0;
 cBitmap * bitmap = new cBitmap( argv[1] );
 quantizeBW( bitmap );
 setup_matrix();
 cout << countVerticalLines( bitmap ) << endl;
 cout << countHorizontalLines( bitmap ) << endl;
}
