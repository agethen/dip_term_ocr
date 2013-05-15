#include "Bitmap.hh"

#include <GL/glut.h>
#include <iostream>
#include <cmath>
cBitmap * bitmap;

void draw();
void myKeyboard( unsigned char, int, int );
void exhaustiveConvexHull();
void convexHull();
int count;

char outputfile[16];

int main( int argc, char ** argv ){

 bitmap = new cBitmap( argv[1] );
 //exhaustiveConvexHull( );
 convexHull();

 strcpy( outputfile, "test.bmp" );

 bitmap->saveBitmap( outputfile );

 /* Viewer */
 glutInit( &argc, argv );
 glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
 glutInitWindowSize( 800,800 );
 glutInitWindowPosition( 400, 400 );
 glutCreateWindow("Raw Image Display");
 glutDisplayFunc(draw);
 glutKeyboardFunc(myKeyboard);
 glutMainLoop();

 return 0;
}



void drawline( int i, int j, int x, int y ){
 double dx = x-i;
 double dy = y-j;


 struct Pixel p, t;
 p.r = 128;
 p.g = 128;
 p.b = 128;
 double length = sqrt( dx*dx+dy*dy );
 
 double curx = i;
 double cury = j;

 dx = dx/length;
 dy = dy/length;

 for( int z = 0; z < (int) length+1; z++ ){
  count++;
  bitmap->getPixel( (int)curx, (int)cury, t );

  if( t.r+t.g+t.b != 0 )
   bitmap->setPixel( (int)curx, (int)cury, p );

  curx += dx;
  cury += dy;

 }
 
}

void exhaustiveConvexHull( ){
struct Pixel p;
count = 0;
for( int i = 0; i < bitmap->getWidth(); i++ ){
 for( int j = 0; j < bitmap->getHeight(); j++ ){
  bitmap->getPixel( i, j, p );
  if( ((p.r|p.g)|p.b) != 0 )
   continue;

  for( int x = i; x < bitmap->getWidth(); x++ ){
   for( int y = 0; y < bitmap->getHeight(); y++ ){
    bitmap->getPixel( x, y, p );
    if( p.r != 0 || p.g != 0 || p.b != 0 )
     continue;
    drawline( i,j, x,y );
   }
  }
  
 }
}
cout << count << endl;
}






void convexHull(){
 int min[2] = {99999,99999};
 int max[2] = {-1,-1};

 int flag = 1;
 
 int detect = 0;

 struct Pixel p,mark;
 mark.r = 128;
 mark.g = 128;
 mark.b = 128;

count = 0;
 //Get min-max dimensions first
 for( int i = 0; i < bitmap->getWidth(); i++ ){
  for( int j = 0; j < bitmap->getHeight(); j++ ){
count++;
   bitmap->getPixel( i, j, p );
   if( p.r < 255 ){
    if( i < min[0] ) min[0] = i;
    if( j < min[1] ) min[1] = j;
    if( i > max[0] ) max[0] = i;
    if( j > max[1] ) max[1] = j;
   }
  }
 }

 while(flag){
  flag = 0;

//Column-wise
  for( int i = min[0]; i <= max[0]; i++ ){   
   for( int j = min[1]; j <= max[1]; j++ ){
     detect = 0;
     for( int z = -1; z <= 1; z++ ){
count++;
      bitmap->getPixel( i, j+z, p );
      if( p.r < 255 )
       detect++;
     }

     if( detect == 3 ){
      bitmap->getPixel( i-1,j, p );
      if( p.r == 255 ){
       bitmap->setPixel( i-1,j,mark );
       flag++;
      }

      bitmap->getPixel( i+1,j, p );
      if( p.r == 255 ){
       bitmap->setPixel( i+1,j,mark );
       flag++;
      }
     }
   }
  }

//Row-wise
  for( int i = min[1]; i <= max[1]; i++ ){   
   for( int j = min[0]; j <= max[0]; j++ ){
     detect = 0;
     for( int z = -1; z <= 1; z++ ){
count++;
      bitmap->getPixel( j+z, i, p );
      if( p.r < 255 )
       detect++;
     }

     if( detect == 3 ){
      bitmap->getPixel( j, i-1, p );
      if( p.r == 255 )
       bitmap->setPixel( j, i-1, mark );

      bitmap->getPixel( j, i+1, p );
      if( p.r == 255 )
       bitmap->setPixel( j,i+1, mark );
     }
   }
  }
 }
}





/* Viewer Related Stuff */
void myKeyboard(unsigned char key, int x, int y){
 switch(key){
   case 27:
    exit(0);
 };
}

void draw( ){
  int size = (bitmap->getWidth())*(bitmap->getHeight())*sizeof(struct Pixel);

  unsigned char * buffer = (unsigned char *) malloc( size );
  if( buffer == NULL ){ fprintf( stderr, "Could not allocate memory\n" ); return; }

  bitmap->getBitmap( buffer, size );

  glClear(GL_COLOR_BUFFER_BIT);
 
  glEnable( GL_TEXTURE_RECTANGLE_ARB );

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);

  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, bitmap->getWidth(), bitmap->getHeight(),
               0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
 
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER,	//Use GL_NEAREST here to avoid interpolation (instead of GL_LINEAR)
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
 
  glBegin(GL_QUADS);
  glTexCoord2i(0, bitmap->getHeight());
  glVertex2f(-1, -1);
  glTexCoord2i(bitmap->getWidth(), bitmap->getHeight());
  glVertex2f(1, -1);
  glTexCoord2i(bitmap->getWidth(), 0);
  glVertex2f(1, 1);
  glTexCoord2i(0, 0);
  glVertex2f(-1, 1);
  glEnd();
 
  glDeleteTextures(1, &texture);
 
  glFlush();
  glutSwapBuffers();

  free(buffer);
}

