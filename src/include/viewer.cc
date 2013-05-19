#include "viewer.hh"
#include <GL/glut.h>

unsigned char * buffer;
int width;
int height;

void glutViewer( unsigned char * b, int w, int h, int argc, char ** argv, int windowsize_x, int windowsize_y ){
 buffer = b;
 width = w;
 height = h;


 /* Viewer */
 glutInit( &argc, argv );
 glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
 glutInitWindowSize( windowsize_x,windowsize_y );
 glutInitWindowPosition( 400, 400 );
 glutCreateWindow("Raw Image Display");
 glutDisplayFunc(draw);
 glutKeyboardFunc(myKeyboard);
 glutMainLoop();

 
}



/* Viewer Related Stuff */
void myKeyboard(unsigned char key, int x, int y){
 switch(key){
   case 27:
    exit(0);
 };
}

void draw( ){

 
  glClear(GL_COLOR_BUFFER_BIT);
 
  glEnable( GL_TEXTURE_RECTANGLE_ARB );

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);

  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, width, height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
 
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER,	//Use GL_NEAREST here to avoid interpolation (instead of GL_LINEAR)
                  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST);
 
  glBegin(GL_QUADS);
  glTexCoord2i(0, height);
  glVertex2f(-1, -1);
  glTexCoord2i(width, height);
  glVertex2f(1, -1);
  glTexCoord2i(width, 0);
  glVertex2f(1, 1);
  glTexCoord2i(0, 0);
  glVertex2f(-1, 1);
  glEnd();
 
  glDeleteTextures(1, &texture);
 
  glFlush();
  glutSwapBuffers();
}

