#include "circularity.hh"

int parseCircleComponent( cBitmap * bitmap, int x, int y, CircleComponent & c, unsigned char color ){
 Pixel p;

 if( x < 0 ){ c.min_x = 0; return 1; }
 if( y < 0 ){ c.min_y = 0; return 1; }
 if( x >= bitmap->getWidth() ){ c.max_x = bitmap->getWidth()-1; return 1; }
 if( y >= bitmap->getHeight() ){ c.max_y = bitmap->getHeight()-1; return 1; }

 bitmap->getPixel( x, y, p );

 if( p.r != 255 ){ 				//This pixel already belongs to a component (different color)
  if( x < c.min_x ) c.min_x = x;
  if( x > c.max_x ) c.max_x = x;
  if( y < c.min_y ) c.min_y = y;
  if( y > c.max_y ) c.max_y = y;
  return 0;
 }

 Pixel p1,p2,p3,p4;
 bitmap->getPixel( x-1, y, p1 );
 bitmap->getPixel( x+1, y, p2 );
 bitmap->getPixel( x, y-1, p3 );
 bitmap->getPixel( x, y+1, p4 );
 if( p1.r * p2.r * p3.r * p4.r == 0 ){		//At least one black pixel neighbor
  p.r = 100;					//Mark as border pixel
 }else{
  p.r = 200;					//Mark as visited, non-border
 }
 bitmap->setPixel( x, y, p );			//Color pixel as visited

 /* Recursion on 4-neighborhood */
 int result = 0;
 result += parseCircleComponent( bitmap, x-1, y, c, color );
 result += parseCircleComponent( bitmap, x+1, y, c, color );
 result += parseCircleComponent( bitmap, x, y-1, c, color );
 result += parseCircleComponent( bitmap, x, y+1, c, color );

 return result;
}


void restoreImage( cBitmap * bitmap ){
 Pixel p;
 for( int i = 0; i < bitmap->getHeight(); i++ ){
  for( int j = 0; j < bitmap->getWidth(); j++ ){
   bitmap->getPixel( j, i, p );
   p.r = p.g;
   bitmap->setPixel( j, i, p );
  }
 }
}

void findLakes( cBitmap * bitmap, vector<CircleComponent> & lakes ){
 Pixel p; 
 unsigned char color = 00;

 int touchesBorder = 0;
 CircleComponent c;

 for( int i = 0; i < bitmap->getHeight(); i++ ){
  for( int j = 0; j < bitmap->getWidth(); j++ ){
   bitmap->getPixel( j, i, p );
   if( ((p.r & p.g) & p.b) != 255 ) continue;

   color += 10;
   /* Initialize values */
   c.max_x = 0;
   c.min_x = bitmap->getWidth()-1;
   c.max_y = 0;
   c.min_y = bitmap->getHeight()-1;

   touchesBorder = parseCircleComponent( bitmap, j, i, c, color );

   if( !touchesBorder ){
    c.center_x = (c.min_x+c.max_x)/2; 
    c.center_y = (c.min_y+c.max_y)/2;
    lakes.push_back( c );
   }
  }
 }

}

bool testCircularity( cBitmap * bitmap, CircleComponent & circle ){
 Pixel p;
 double distance = 0;
 double sum_dist = 0;
 double num_dist = 0;
 int cx = circle.center_x;
 int cy = circle.center_y;

 //Find all pixels with p.r = 100 (border pixels)
 for( int i = circle.min_y; i < circle.max_y; i++ ){
  for( int j = circle.min_x; j < circle.max_x; j++ ){
   bitmap->getPixel( j, i, p );
   if( p.r != 100 ) continue;

   /* Found a border pixel. Measure distance */
   distance = sqrt( ((j-cx)*(j-cx))+((i-cy)*(i-cy)) );
   sum_dist += distance;
   num_dist++;

   if( distance < (1-THRESH)*(sum_dist/num_dist) || distance > (1+THRESH)*(sum_dist/num_dist) ){
    return false;
   }
  }
 }

 return true;
}

int countCircles( cBitmap * bitmap ){
 vector<CircleComponent> lakes;
 int numCircles = 0;

 findLakes( bitmap, lakes );

 for( unsigned int i = 0; i < lakes.size(); i++ )
  if( testCircularity( bitmap, lakes[i] ) ) numCircles++;
 

 restoreImage( bitmap );
 return numCircles;
}
