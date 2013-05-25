#include "Split.hh"

using namespace std;

int main( int argc, char ** argv ){
 /* Define two files to test the splitting */
 char inputfile[32];
 char outputfile[32];

 strcpy( inputfile, "a.bmp" );
 strcpy( outputfile, "b.bmp" );

 /* Create objects */
 cSplit * split = new cSplit();
 cBitmap * bitmap = new cBitmap( inputfile );

 vector<FontBoundary> t;

 split->findSentenceBoundary( bitmap );

 t = split->sentences;

 /* This is important! Always add one to each dimension, as getRangeOfBitmap loads all pixels including the maximum */
 int size = (t[0].right-t[0].left+1)*( t[0].bottom - t[0].top+1 )*sizeof( Pixel );

 /* Allocate some memory to get copy the bitmap */
 unsigned char * test = (unsigned char *) malloc( size );
 if( test == NULL ){ fprintf( stderr, "Could not allocate memory!\n" ); exit(1); }

 /* Copy a range from the bitmap. NOTE: This command copies all pixels __including__ minimum and maximum, e.g., left <= i <= right, top <= j <= bottom */
 /* (That is why if you do not allocate enough memory above, you may run into problems */
 bitmap->getRangeOfBitmap( test, size, t[0].left, t[0].right, t[0].top, t[0].bottom );

 /* Create a bitmap from buffer "test". Remember here, too, that minimum and maximum are included, so width and height should be (maximum-minimum+1) */
 bitmap->setBitmap( test, t[0].right-t[0].left+1, t[0].bottom-t[0].top+1, 3 );

 /* Save bitmap to file outputfile */
 bitmap->saveBitmap( outputfile );

 return 0;
}
