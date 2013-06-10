#include "boundary.hh"
#include "viewer.hh"
void erodeImage( cBitmap * image, cBitmap * result, int masksize ){

 Pixel p;

 if( masksize%2 == 0 ){
  fprintf( stderr, "Error: ExtractBoundary: masksize is not odd!\n" );
  return;
 }

 for( int i = 0; i < image->getWidth(); i++ ){
  for( int j = 0; j < image->getHeight(); j++ ){
   int pixel = 0;
   for( int dx = i-(masksize/2); dx <= i+(masksize/2); dx++ ){
    for( int dy = j-(masksize/2); dy <= j+(masksize/2); dy++ ){
     if( dx >= 0 && dx < image->getWidth() && dy >= 0 && dy < image->getHeight() )
     image->getPixel( dx, dy, p );

     if( p.r == 255 )
      pixel = 255;

    }
   }

   p.r = pixel;
   p.g = pixel;
   p.b = pixel;

   result->setPixel( i, j, p );
  }
 }
}

void extractBoundary( cBitmap * image, cBitmap * result ){
 cBitmap * tmp = new cBitmap( );
 tmp->setWidth( image->getWidth() );
 tmp->setHeight( image->getHeight() );
 tmp->setBPP( image->getBPP() );
 tmp->allocateMemory();

 Pixel p1, p2;

 //Step one: Erode
 erodeImage( image, tmp, 3 );
 
 //Step two: Substract (Effectively an XOR here) 
 for( int i = 0; i < image->getWidth(); i++ ){
  for( int j = 0; j < image->getHeight(); j++ ){
   image->getPixel( i, j, p1 );
   tmp->getPixel( i, j, p2 );

   if( p1.r == p2.r ){
    p1.r = 255;
    p1.g = 255;
    p1.b = 255;
   }else{
    p1.r = 0;
    p1.g = 0;
    p1.b = 0;
   }

   result->setPixel( i, j, p1 );
  }
 }
}
#ifdef TSET
int main( int argc, char ** argv){
 cBitmap * b = new cBitmap("../../Letters/A.bmp");
 extractBoundary( b, b );

 	//Just for testing
cBitmap * character = b;
	unsigned char * t = (unsigned char*) malloc( character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	character->getBitmap( t, character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	glutViewer( t, character->getWidth(), character->getHeight(), argc, argv, 400, 400 );
	free( t );


 return 0;
}
#endif
