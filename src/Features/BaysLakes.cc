#include "BaysLakes.hh"
//#include "Convex Hull\convex.hh"

#include <iostream>
using namespace std;

int countX;
vector<int> result;	//holds the found bays & lakes: 1st int: 'name' (=color number), 2nd int: 0 = lake, 1=bay
cBitmap* convex;
vector<struct Pixel> colors ;

vector<double> findBaysLakes(cBitmap * bm) {
	vector<double> output;
	colors = initialiseColors();
	countX=0;


	// first copy it!
	unsigned char * buffer = (unsigned char *) malloc( bm->getWidth()*bm->getHeight()*sizeof(Pixel) );
	bm->getBitmap( buffer, bm->getWidth()*bm->getHeight()*sizeof(Pixel));
	convex = new cBitmap();
	convex->setBitmap( buffer, bm->getWidth(), bm->getWidth(), sizeof(Pixel));
	myExhaustiveConvexHull(convex);

	tagBorders(convex);
	for( int i = 0; i < bm->getHeight(); i++ ){
		for( int j = 0; j < bm->getWidth(); j++ ){
			checkPixel(i,j,0);
		}
	} 
	//convex->saveBitmap( "resultBL.bmp" );
	output.push_back(0);
	output.push_back(0);
	for(unsigned int i=0;i<result.size();i++){
		output[result[i]]++;
	}
	return output;
}

void checkPixel(int x, int y,int elementOf){
	Pixel p;

	convex->getPixel( x, y, p );
		// TAGS of p.a: =1: border, =255: already covered
	if(p.r != 128 || p.a != 0) {//not part of hull-original (r=128) or done already (a=255)
		p.a = 255;
		convex->setPixel(x,y,p);
		return; 
	}
	if(elementOf==0){ //new bay/lake found
		countX++;
		//result.resize(countX);

		if(p.b == 64) result.push_back(1); //border! so bay for sure!
		else result.push_back(0);
		p = colors[countX%6];
		p.a=countX; //tag pixel as done
		elementOf = countX;	
		convex->setPixel(x,y,p);
	}
	else { //belongs to previous found lake/bay: check if lake->bay
		if(p.b == 64 && result[elementOf-1] == 0){
			result[elementOf-1] =1; //tag as bay!
		}
		p = colors[countX%6];
		p.a=elementOf;
		convex->setPixel(x,y,p);
	}
	//check neighbours: add them to check list
	for(int i=-1;i<2;i++){
		for( int j=-1;j<2;j++){
			if(i==0 && j==0) continue;
			else{
				if(convex->getPixel( x+i, y+j, p )) continue; //out of bounds!
				if(p.a == 0) { //NOT checked already!
					//if(p.r==128 && p.a!=255){
						checkPixel(x+i,y+j,elementOf);
					//}
				}
			}
		}
	}

}

vector<struct Pixel> initialiseColors(){
	vector<struct Pixel> colors;
	Pixel p1,p2,p3,p4,p5,p6;
	p1.r=255; p1.g=0; p1.b=0;p2.r=0; p2.g=255; p2.b=0;p3.r=0; p3.g=0; p3.b=255;
	p4.r=255; p4.g=255; p4.b=0;p5.r=255; p5.g=0; p5.b=255;p6.r=0; p6.g=255; p6.b=255;
	colors.push_back(p1);colors.push_back(p2);colors.push_back(p3);
	colors.push_back(p4);colors.push_back(p5);colors.push_back(p6);
	return colors;
}

void tagBorders(cBitmap* myBitmap){
	vector<struct Pixel> colors = initialiseColors();
	Pixel p;

	// find border: tag with 'alpha' value = 1
	vector<vector<int> > borderHorz;
	borderHorz.resize(myBitmap->getHeight());
	vector<vector<int> > borderVert;
	borderVert.resize(myBitmap->getWidth());

	for( int i = 0; i < myBitmap->getHeight(); i++ ){
		borderHorz[i].resize(2);
		borderHorz[i][0] =-1; borderHorz[i][1]= -1;
		for( int j = 0; j < myBitmap->getWidth(); j++ ){
			if(i==0){
				borderVert[j].resize(2);
				borderVert[j][0]=-1; borderVert[j][1]=-1;
			}
			myBitmap->getPixel( j, i, p );

			if(p.r == 255) continue; //white pixel
			else {
				if(borderHorz[i][0] == -1) { borderHorz[i][0] = j; } //left border
				borderHorz[i][1] = j;	// right border
			
				if(borderVert[j][0] == -1) { borderVert[j][0] = i; } //upper border
				borderVert[j][1] = i;	// lower border
			}
		}
	}

	for( unsigned int i=0; i <borderHorz.size(); i++){
		if(borderHorz[i][0] == -1) continue;
		myBitmap->getPixel(borderHorz[i][0],i, p);
		p.b = 64; // TAG border
		myBitmap->setPixel(borderHorz[i][0],i, p);
		myBitmap->getPixel(borderHorz[i][1],i, p);
		p.b = 64; // TAG border
		myBitmap->setPixel(borderHorz[i][1],i, p);
	}
	for( unsigned int i=0; i <borderVert.size(); i++){
		if(borderVert[i][0] == -1) continue;
		myBitmap->getPixel(i, borderVert[i][0], p);
		p.b = 64; // TAG border 
		myBitmap->setPixel(i, borderVert[i][0], p);
		myBitmap->getPixel(i, borderVert[i][1], p);
		p.b = 64; // TAG border 
		myBitmap->setPixel(i, borderVert[i][1], p);
	}
}

void myExhaustiveConvexHull(cBitmap* myBitmap ){
struct Pixel p;

for( int i = 0; i < myBitmap->getWidth(); i++ ){
 for( int j = 0; j < myBitmap->getHeight(); j++ ){
  myBitmap->getPixel( i, j, p );
  p.a = 0;
  myBitmap->setPixel( i, j, p );
  if( ((p.r|p.g)|p.b) != 0 )
   continue;

  for( int x = i; x < myBitmap->getWidth(); x++ ){
   for( int y = 0; y < myBitmap->getHeight(); y++ ){
    myBitmap->getPixel( x, y, p );
    if( p.r != 0 || p.g != 0 || p.b != 0 )
     continue;
    mydrawline(myBitmap,i,j, x,y );
   }
  }
  
 }
}
}

void mydrawline(cBitmap* myBitmap,int i, int j, int x, int y ){
 double dx = x-i;
 double dy = y-j;

 struct Pixel p, t;
 p.r = 128;
 p.g = 128;
 p.b = 128;
 //p.a = 1;
 
 double length = sqrt( dx*dx+dy*dy );
 
 double curx = i;
 double cury = j;

 dx = dx/length;
 dy = dy/length;

 for( int z = 0; z < (int) length+1; z++ ){
  //count2++;
  myBitmap->getPixel( (int)curx, (int)cury, t );

  if( t.r+t.g+t.b != 0 )
   myBitmap->setPixel( (int)curx, (int)cury, p );

  curx += dx;
  cury += dy;
 } 
}

