#ifndef __VIEWER_HH__
#define __VIEWER_HH__

/* Call this function to display an image */
/* @b: image buffer. Expected size is w*h*4 */
/* @w: Width of image */
/* @h: Height of image */
/* @argc: Pass argc of main( .. ) here. Needed for glut stuff */
/* @argv: Pass argv of main( .. ) here. Needed for glut stuff */
/* Notes: Expected format of buffer is RGBA. */
void glutViewer( unsigned char * b, int w, int h, int argc, char ** argv );

/* Keyboard function. Used by glutViewer(..) */
void myKeyboard(unsigned char key, int x, int y);

/* Draw function. Used by glutViewer(..) */
void draw( );
#endif
