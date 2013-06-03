#include "euler.hh"

void parseComponent( cBitmap & bitmap, int x, int y, CharacterComponent & c ){
 Pixel p;

 if( x < 0 || y < 0 ){
  c.connectsBorder = true;
  return;
 }

 if( x >= bitmap.getWidth() || y >= bitmap.getHeight() ){
  c.connectsBorder = true;
  return;
 }

 bitmap.getPixel( x, y, p );

 if( p.r != 0 && p.r != 255 ) return;		//This pixel already belongs to a component (different color)

 p.r = abs( (int)p.r-(10*c.id) );
 bitmap.setPixel( x, y, p );			//Color pixel as visited

 /* Recursion on 4-neighborhood */
 parseComponent( bitmap, x-1, y, c );
 parseComponent( bitmap, x+1, y, c );
 parseComponent( bitmap, x, y-1, c );
 parseComponent( bitmap, x, y+1, c );
}

void restoreImage( cBitmap & bitmap ){
 Pixel p;
 for( int i = 0; i < bitmap.getHeight(); i++ ){
  for( int j = 0; j < bitmap.getWidth(); j++ ){
   bitmap.getPixel( j, i, p );
   p.r = p.g;
   bitmap.setPixel( j, i, p );
  }
 }
}

void findComponents( cBitmap & bitmap, vector<CharacterComponent> & data ){
 Pixel p;

 CharacterComponent c;
 c.id = 0;

 for( int i = 0; i < bitmap.getHeight(); i++ ){
  for( int j = 0; j < bitmap.getWidth(); j++ ){
   bitmap.getPixel( j, i, p );

   if( p.r + p.g + p.b == 0 ){ 			//Black pixel
    c.id++; c.connectsBorder = false;		//Initialize Component
    c.color = 0; c.pos[0] = j; c.pos[1] = i;
    parseComponent( bitmap, j, i, c );		//Read region
    data.push_back( c );			//Save data
   }else{
    if( ((p.r & p.g) & p.b) == 255 ){ 		//White pixel
     c.id++; c.connectsBorder = false;		//Initialize Component
     c.color = 255; c.pos[0] = j; c.pos[1] = i;
     parseComponent( bitmap, j, i, c );		//Read region
     data.push_back( c );			//Save data
    }
   }
  }
 }

 restoreImage( bitmap );
}

int getNumberOfLakes( vector<CharacterComponent> & data ){
 int numLakes = 0;
 for( vector<CharacterComponent>::iterator it = data.begin(); it != data.end(); ++it ){
  if( it->color == 0 ) continue;		//Black pixels do not belong to a lake

  if( it->connectsBorder ) continue;	//A lake does not connect to the border

  numLakes++;
 }
}

int getNumberOfConnectedComponents( vector<CharacterComponent> & data ){
 int numComponents = 0;

 for( vector<CharacterComponent>::iterator it = data.begin(); it != data.end(); ++it ){
  if( it->color == 255 ) continue; //White pixels do not belong to a component

  numComponents++;  
 }

 return numComponents;
}

int getNumberOfHoles( vector<CharacterComponent> & data ){
 return getNumberOfLakes( data );
}

int getEulerNumber( cBitmap & bitmap ){
 int euler = 0;
 vector<CharacterComponent> data;

 findComponents( bitmap, data );

 euler = getNumberOfConnectedComponents( data ) - getNumberOfHoles( data ); 

 return euler;
}
