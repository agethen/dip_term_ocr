#include "subcomponents.hh"



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

bool findRoute( cBitmap * b, int ox, int oy, int tx, int ty, int d ){
 Pixel p;
 if( d == 1 && (ox > tx || oy > ty) ) return false;
 if( d == -1 && (ox > tx || oy < ty) ) return false;
 if( ox == tx && oy == ty ) return true;

 b->getPixel( ox, oy, p );
 if( p.r != 0 ) return false;

 
 bool res = findRoute( b, ox+1, oy+d*1, tx, ty, d );
 if( res ){
  p.r = 128;
  b->setPixel( ox, oy, p );
  return true;
 }
 res = findRoute( b, ox+1, oy, tx, ty, d );
 if( res ){   
  p.r = 128;
  b->setPixel( ox, oy, p );
  return true;
 }
 res = findRoute( b, ox, oy+d*1, tx, ty, d );
 if( res ){
  p.r = 128;
  b->setPixel( ox, oy, p );
  return true;
 }
 
 return false;
}

int parseDiagonal( cBitmap * b, int x, int y, int down ){
 Pixel p,p1,p2,p3,p4,p5;
 int lx = 0;
 int ly = 0;

 int tx, ty;

 while( true ){
  b->getPixel( x+lx, y+down*ly, p );

  if( p.r != 0 ) return 0;

 
  if( down == 1 && !(x+lx+5 < b->getWidth() && y+ly+5 < b->getHeight()) ) return lx+ly;
  if( down == -1 && !(x+lx+5 < b->getWidth() && y+down*(ly+5) >= 0) ) return lx+ly;

  b->getPixel( x+lx+5, y+down*(ly+5), p1 );
  b->getPixel( x+lx+5, y+down*(ly+4), p2 );
  b->getPixel( x+lx+4, y+down*(ly+5), p3 );
  b->getPixel( x+lx+3, y+down*(ly+5), p4 );
  b->getPixel( x+lx+5, y+down*(ly+3), p5 );

  bool selected = false;
  if( p1.r == 0 && !selected ){tx = x+lx+5; ty = y+down*(ly+5); selected = true;}
  if( p2.r == 0 && !selected ){tx = x+lx+5; ty = y+down*(ly+4); selected = true;}
  if( p3.r == 0 && !selected ){tx = x+lx+4; ty = y+down*(ly+5); selected = true;}
  if( p4.r == 0 && !selected ){tx = x+lx+3; ty = y+down*(ly+5); selected = true;}
  if( p5.r == 0 && !selected ){tx = x+lx+5; ty = y+down*(ly+3); selected = true;}

  if( !selected ) return lx+ly;

  if( findRoute( b, x+lx, y+down*ly, tx, ty, down ) ){
   lx = tx-x;
   ly = abs(ty-y);

  }else{
   return lx+ly;
  }
 }
 return 0;
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

int countDiagonals( cBitmap * bitmap ){
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

   length = parseDiagonal( copy, j, i, 1 );	//Top-Bottom Lines

   if( length >= CUTOFF_DIA )
    numberOfLines++;

   length = parseDiagonal( copy, j, i, -1 );	//Bottom-Top Lines

   if( length >= CUTOFF_DIA )
    numberOfLines++;

  }
 }

 //Just for testing
 cBitmap * character = copy;
 unsigned char * t1 = (unsigned char*) malloc( character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
 character->getBitmap( t1, character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
 glutViewer( t1, character->getWidth(), character->getHeight(), 0, NULL, 400, 400 );
 free( t1 );


 delete copy;

 return numberOfLines;
}

/*
int main( int argc, char ** argv ){
 cBitmap * a = new cBitmap( argv[1] );

 int result = countDiagonals( a );
 cout << result << " diagonals" << endl;


 return 0;

}
*/
