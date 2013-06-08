#include "features.hh"

vector<double> computeFeatures( cBitmap * b ){
 vector<double> feats;
 vector<vector<int>> bw = quantize2DArray(b);
  // cBitmap* cv = b; // need deep-copy method
 myTempConvexHull(b);
 vector<vector<int>> convex = quantize2DArray(b);

 // Feature 1: # (black/colored) pixels
 double count = countPixels(&bw);
 feats.push_back(count);

 // Feature 2: width/height ratio
 feats.push_back(whRatio(&bw));

 // Feature 3: (adapted) circularity
 feats.push_back(circularity(&bw,&convex));
 return feats;
}

vector<vector<int>> quantize2DArray( cBitmap * b){
	 int threshold = 224; //out of 255
	 struct Pixel p;
	 vector<vector<int>> storage;
	 storage.resize(b->getWidth());

	 for( int i = 0; i < b->getWidth(); i++ ){
		storage[i].resize(b->getHeight());
		for( int j = 0; j < b->getHeight(); j++ ){
		   b->getPixel( i, j, p );
		   if(p.a == 1) storage[i][j] = 128; //convex hull!
		   else if( p.r +  p.g +  p.b > 3*threshold ) storage[i][j] = 255; else storage[i][j] = 0;
		}
	 }
	 return storage;
}

double countPixels(vector<vector<int>>* bitmap){

	 double count = 0;
	 for( int i = 0; i < bitmap->size(); i++ ){
		 for( int j = 0; j < bitmap->at(i).size(); j++ ){
			if( bitmap->at(i)[j] < 255) // non-white pixel (so convex hull also included!)
			count++;
		}
	}
	return count;
}

double whRatio(vector<vector<int>>* bitmap) {
	double maxW =0, maxH=0, start;
	for( int i = 0; i < bitmap->size(); i++ ){
		 start = -1;
		 for( int j = 0; j < bitmap->at(i).size(); j++ ){
			 if(bitmap->at(i)[j] == 0){
				 if(start == -1) start = j;
				 else maxH = max(maxH,j-start);
			 }
		}
	}
	for( int i = 0; i < bitmap->at(0).size(); i++ ){
		 start = -1;
		 for( int j = 0; j < bitmap->size(); j++ ){
			 if(bitmap->at(j)[i] == 0){
				 if(start == -1) start = j;
				 else maxW = max(maxW,j-start);
			 }
		}
	}
	return maxW/maxH;
}

double circularity(vector<vector<int>>* bitmap,vector<vector<int>>* convexHull){
	double cntBM = countPixels(bitmap);
	double cntCV = countPixels(convexHull);
	return (4*PI*cntCV)/(cntBM*cntBM);
}

void myTempConvexHull(cBitmap* bm){
	// I changed the mark value for a to have +1, so this easily find the pixels marked as convex hull
 int min[2] = {99999,99999};
 int max[2] = {-1,-1};

 int flag = 1;
 
 int detect = 0;

 struct Pixel p,mark;
 mark.r = 128;
 mark.g = 128;
 mark.b = 128;
 mark.a = 1;

 double count2 = 0;
 //Get min-max dimensions first

 for( int i = 0; i < bm->getWidth(); i++ ){
  for( int j = 0; j < bm->getHeight(); j++ ){
   count2++;
   bm->getPixel( i, j, p );
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
count2++;
      bm->getPixel( i, j+z, p );
      if( p.r < 255 )
       detect++;
     }

     if( detect == 3 ){
      bm->getPixel( i-1,j, p );
      if( p.r == 255 ){
       bm->setPixel( i-1,j,mark );
       flag++;
      }

      bm->getPixel( i+1,j, p );
      if( p.r == 255 ){
       bm->setPixel( i+1,j,mark );
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
count2++;
      bm->getPixel( j+z, i, p );
      if( p.r < 255 )
       detect++;
     }

     if( detect == 3 ){
      bm->getPixel( j, i-1, p );
      if( p.r == 255 )
       bm->setPixel( j, i-1, mark );

      bm->getPixel( j, i+1, p );
      if( p.r == 255 )
       bm->setPixel( j,i+1, mark );
     }
   }
  }
 }
}
