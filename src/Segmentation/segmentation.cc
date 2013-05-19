#include "../include/Bitmap.hh"
#include "../include/viewer.hh"

#include <iostream>
#include <vector>

using namespace std;

struct Segment{
 cBitmap * bmap;
 int min_x;	//Minimum value of x (i.e., the position)
 int min_y;
 int max_x;	//Maximum value of x (together w position: width)
 int max_y;
};

cBitmap * bitmap;

void quantizeBW( cBitmap * b );
void findSegments( cBitmap * b, vector<Segment> & results );

int main( int argc, char ** argv ){
 vector<Segment> results;

 bitmap = new cBitmap( argv[1] );
 
 quantizeBW( bitmap );

 findSegments( bitmap, results );

 if( !results.empty() )
  bitmap = results[0].bmap;	//Just as an example, switch the viewer to the first recognized character here. (Viewer always displays pointer bitmap)


 cout << results.size() << " Characters segmented" << endl;

 /* OpenGL Viewer Related */
 int size = (bitmap->getWidth())*(bitmap->getHeight())*sizeof(struct Pixel);

 unsigned char * buffer = (unsigned char *) malloc( size );
 if( buffer == NULL ){ fprintf( stderr, "Could not allocate memory\n" ); return 1; }
 
 bitmap->getBitmap( buffer, size );

 glutViewer( buffer, bitmap->getWidth(), bitmap->getHeight(), argc, argv, 800, 800 );

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


void parseSegment( cBitmap * b, Segment & s, int x, int y ){
 struct Pixel p;
 struct Pixel marked;
 marked.r = 1;
 marked.g = 1;
 marked.b = 1;

 if( x < 0 || x > b->getWidth() || y < 0 || y > b->getHeight() ) //Out of image bounds
  return;

 b->getPixel( x, y, p );
 
 if( p.r + p.g + p.b > 0 )	//Not a black pixel -> End of object
  return;

 if( x < s.min_x )
  s.min_x = x;
 if( x > s.max_x )
  s.max_x = x;
 if( y < s.min_y )
  s.min_y = y;
 if( y > s.max_y )
  s.max_y = y; 

 b->setPixel( x, y, marked );

 /* Recurse all 8 neighbors */
 parseSegment( b, s, x-1, y-1 );
 parseSegment( b, s, x, y-1 );
 parseSegment( b, s, x+1, y-1 );
 parseSegment( b, s, x-1, y );
 parseSegment( b, s, x+1, y );
 parseSegment( b, s, x-1, y+1 );
 parseSegment( b, s, x, y+1 );
 parseSegment( b, s, x+1, y+1 );
 
}

void initSegment( Segment & s ){
 s.bmap = NULL;
 s.min_x = 99999;
 s.max_x = -1;
 s.min_y = 99999;
 s.max_y = -1;
}

void padSegment( Segment & s, int w, int h ){
#define PADDING 1
s.min_x -= PADDING; if( s.min_x < 0 ) s.min_x = 0;
s.max_x += PADDING; if( s.min_x >= w ) s.min_x = w;
s.min_y -= PADDING; if( s.min_y < 0 ) s.min_y = 0;
s.max_y += PADDING; if( s.max_y >= h ) s.max_y = h;
}

void findSegments( cBitmap * b, vector<Segment> & results ){
 struct Pixel p;

 /* Walk row-first */
 for( int j = 0; j < b->getHeight(); j++ ){
  for( int i = 0; i < b->getWidth(); i++ ){
   b->getPixel( i, j, p );
   if( p.r + p.g + p.b == 0 ){	//A black pixel
    struct Segment s;
    initSegment( s );

    parseSegment( b, s, i, j );

    padSegment( s, b->getWidth(), b->getHeight() );

    /* Compute Extend */
    int dx = s.max_x - s.min_x + 1;
    int dy = s.max_y - s.min_y + 1;

    /* Copy this area into a new bitmap */
    unsigned char * buffer = (unsigned char * ) malloc( dx*dy*sizeof( struct Pixel ) );
    b->getRangeOfBitmap( buffer, dx*dy*sizeof( struct Pixel ), s.min_x, s.max_x, s.min_y, s.max_y );
    s.bmap = new cBitmap();
    s.bmap->setBitmap( buffer, dx, dy, 3 );
    free( buffer );

    /* Save result */
    results.push_back( s );
   }
  }
 }
}
