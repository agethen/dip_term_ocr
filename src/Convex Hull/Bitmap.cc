#include "Bitmap.hh"
#include <iostream>

cBitmap::cBitmap(){}

cBitmap::cBitmap( char * filename ){
 loadBitmap( filename );
}

cBitmap::~cBitmap(){}

int cBitmap::loadBitmap( char * filename ){

 fstream file;
 char buffer[128];

 int cBitmapoffset = 0;
 int dibsize = 0;

 file.open( filename, fstream::in|fstream::binary|fstream::ate );

 if( file == NULL ){
  fprintf( stderr, "Could not open file %s\n", filename );
  return -1;
 }
 
 file.seekg( 0, file.beg );

 file.read( buffer, 14 ); //Read cBitmap header
 memcpy( &cBitmapoffset, buffer+10, 4 );
 file.read( buffer, 4 );
 memcpy( &dibsize, buffer, 4 );
 assert( dibsize == 40 );
 file.read( buffer, dibsize-4 );
 memcpy( &width, buffer, 4 );
 memcpy( &height, buffer+4, 4 );
 memcpy( &bpp, buffer+10, 2 );
 assert( bpp == 24 || bpp == 32 );

 bpp /= 8;
 
 file.seekg( cBitmapoffset, file.beg );

 bmap = (Pixel *) malloc( width*height*bpp );

 if( !bmap ){ fprintf( stderr, "Could not allocate memory\n" ); return -1; }

 int xpos = 0;
 int ypos = height-1;

 while( !file.eof() ){
  file.read( buffer, bpp );


  if( !file && !file.eof() ){ fprintf( stderr, "An error occured when reading from file\n" ); return -1; }

  memcpy( &(bmap[ypos*width+xpos]), buffer, 3 ); 	//We read bpp bytes, but only use the first 3 bytes (->in case of 32 bit skip alpha value)

  char t = bmap[ypos*width+xpos].r;			//Format in bitmap is BGRA, we need RGB though
  bmap[ypos*width+xpos].r = bmap[ypos*width+xpos].b;
  bmap[ypos*width+xpos].b = t;

  xpos = (xpos+1)%width;

  if( xpos == 0 )
   ypos--;
 }

 file.close();
 return 0;
}

int cBitmap::saveBitmap( char * filename ){ 

 char header[14];
 header[0] = 'B';
 header[1] = 'M';

 int filesize = width*height*3;
 memcpy( header+2, &filesize, sizeof( int ) );

 header[6] = 0;
 header[7] = 0;
 header[8] = 0;
 header[9] = 0;

 int start = 54;
 memcpy( header+10, &start, sizeof( int ) );

 char dibheader[40];
 int dibsize = 40;
 memcpy( dibheader, &dibsize, sizeof( int ) );
 memcpy( dibheader+sizeof(int), &width, sizeof(int) );
 memcpy( dibheader+2*sizeof(int), &height, sizeof(int) );
 short planes = 1;
 memcpy( dibheader+3*sizeof(int), &planes, sizeof(short) );
 short bbp = 3*8; //Store in 24bbp format, even though 8 bit only supported
 memcpy( dibheader+3*sizeof(int)+sizeof(short), &bbp, sizeof(short) );
 int compression = 0;
 memcpy( dibheader+3*sizeof(int)+2*sizeof(short), &compression, sizeof(int) );
 int rawsize = width*height*3;
 memcpy( dibheader+4*sizeof(int)+2*sizeof(short), &rawsize, sizeof(int) );
 int resolution = 2835; // lol
 memcpy( dibheader+5*sizeof(int)+2*sizeof(short), &resolution, sizeof(int) );
 memcpy( dibheader+6*sizeof(int)+2*sizeof(short), &resolution, sizeof(int) );
 int palette = 0;
 memcpy( dibheader+7*sizeof(int)+2*sizeof(short), &palette, sizeof(int) );
 int important = 0;
 memcpy( dibheader+8*sizeof(int)+2*sizeof(short), &important, sizeof(int) );

 fstream output;
 output.open( filename, fstream::out|fstream::binary );

 if( output == NULL ){
   fprintf( stderr, "Could not open file (writeToFile)!\n" );
   exit(1);
 }

 //Write headers
 output.write( header, 14 );
 output.write( dibheader, 40 );

 for( int i = height-1; i >= 0; i-- ){
  for( int j = 0; j < width; j++ ){
   char buffer[3];
   memcpy( buffer, &(bmap[i*width+j]), 3 );

   output.write( buffer, 3 );
  }
 }
 output.close();

return 0; 
}
 
 
int cBitmap::getPixel( int x, int y, Pixel & p ){
 if( x < 0 || x >= width || y < 0 || y >= height ) return -1; 
 p.r = (bmap[y*width+x]).r;
 p.g = (bmap[y*width+x]).g;
 p.b = (bmap[y*width+x]).b;
 return 0;
}

int cBitmap::setPixel( int x, int y, Pixel p ){
 if( x < 0 || x >= width || y < 0 || y >= height ) return -1;
 bmap[y*width+x] = p;
 return 0;
}

void cBitmap::getBitmap( unsigned char * buffer, int max ){

 int size = width*height*sizeof(struct Pixel);

 if( size > max )
  return;
 else 
  memcpy( buffer, bmap, size );
}

void cBitmap::setBitmap( unsigned char * bmp, int w, int h, int b ){
 width = w;
 height = h;
 bpp = b;

 bmap = (Pixel *) realloc( bmap, width*height*bpp );
 memcpy( bmap, bmp, width*height*bpp );
}


int cBitmap::getWidth(){ return width; }
int cBitmap::getHeight(){ return height; }
int cBitmap::getBPP(){ return bpp; }
