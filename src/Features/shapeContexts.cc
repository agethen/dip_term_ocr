#include "shapeContexts.hh"

bool chooseRandomPoint( cBitmap * bitmap, pair<int,int> & coord ){
 
 int x = rand()%bitmap->getWidth();
 int y = rand()%bitmap->getHeight();
 
 Pixel p;
 bitmap->getPixel( x, y, p );
 if( p.r == 0 ){ 
  coord.first = x;
  coord.second = y;
  p.r = 1;
  bitmap->setPixel( x, y, p );
  return true;
 }

 //If no hit, check 8-neighbors
 for( int i = -1; i < 2; i++ ){
  for( int j = -1; j < 2; j++ ){
   bitmap->getPixel( x, y, p );
    if( p.r == 0 ){ 
     coord.first = x;
     coord.second = y;
     p.r = 1;
     bitmap->setPixel( x, y, p );
     return true;
    }
  }
 }
 return false;
}

double distance( vector<pair<int,int> > & s, int i, int j ){
 double t =  sqrt( (s[i].first-s[j].first)*(s[i].first-s[j].first) + (s[i].second-s[j].second)*(s[i].second-s[j].second) );
 return log( t );
}

void printHistogram( double * hist, int num ){
 for( int i = 0; i < num; i++ )
  printf( "%d\t", i );
 printf("\n");
 for( int i = 0; i < num; i++ ){
  printf( "%.2f\t", hist[i] );
 }
 printf("\n");
}

void computeDistances( vector<pair<int,int> > & samples, double * norm_hist ){
 /* hist_distances[0]: #samples with distance 0, etc.
    Assuming image size is 32*32, the max distance is 10*log(sqrt(2)*32) = 38 */
 int hist_distances[48];	
 memset( hist_distances, 0, 48*sizeof( int ) );

 for( unsigned int i = 0; i < samples.size(); i++ ){
  for( unsigned int j = 0; j < samples.size(); j++ ){
   if( i == j ) continue;
   int dist = (int)(10*distance( samples, i, j ));

   if( dist < 0 || dist > 47 ) continue;

   hist_distances[dist]++;
  }
 }

 /* Normalize hist_distances */
 int min = 99999;
 int max = -1;
 double count = 0;
 for( int i = 0; i < 48; i++ ){
  if( hist_distances[i] != 0 ){
   count += hist_distances[i];
   if( i < min ) min = i;
   if( i > max ) max = i;
  }
 }

 double span_bin = (max-min)/(double)(NUM_BINS-1);
 memset( norm_hist, 0, NUM_BINS*sizeof( double ) );

 for( int i = min; i <= max; i++ ){
  norm_hist[(int)((i-min)/span_bin)] += hist_distances[i]/count;
 }
}

/* Choose a limited number of sample points */
void chooseSamplePoints( cBitmap * bitmap, int num_points, double * norm_hist){
 vector<pair<int,int> > samples;
 int tries = 50;
 srand(time(NULL));

 for( int i = 0; i < num_points; i++ ){
  pair<int,int> coordinates = make_pair(0,0);
  while( !chooseRandomPoint( bitmap, coordinates ) && tries ){ tries--; }
  if( tries > 0 )
   samples.push_back( coordinates );
 }

 /* Do distance stuff */
 computeDistances( samples, norm_hist );
}

double chiSquare( double * hist_a, double * hist_b, int size ){
 double sum = 0;
 double nom = 0;

 for( int i = 0; i < size; i++ ){
  if( hist_a[i]+hist_b[i] > 0 ){
   nom = (hist_a[i]-hist_b[i])*(hist_a[i]-hist_b[i]);
   sum += nom/(hist_a[i]+hist_b[i]);
  }
 }
 return sum/2.0;
}


/* Choose all black pixels as sample points */
void chooseAllPoints( cBitmap * bitmap, double * norm_hist ){
 vector<pair<int,int> > samples;
 Pixel p;

 for( int i = 0; i < bitmap->getWidth(); i++ ){
  for( int j = 0; j < bitmap->getHeight(); j++ ){
   bitmap->getPixel( i, j, p );
   if( p.r == 0 ) samples.push_back( make_pair( i, j ) );
  }
 }
 /* Do distance stuff */
 computeDistances( samples, norm_hist );
}

/*
int main( int argc, char ** argv ){
 if( argc != 3 ) return 0;
 cBitmap * bitmap = new cBitmap( argv[1] );
 cBitmap * second = new cBitmap( argv[2] );

 double hist_a[NUM_BINS];
 double hist_b[NUM_BINS];

 quantizeBW( bitmap );
 quantizeBW( second );

 chooseSamplePoints( bitmap, 100, hist_a );
 chooseSamplePoints( second, 100, hist_b );

 printHistogram( hist_a, NUM_BINS );
 printHistogram( hist_b, NUM_BINS );

 double result = chiSquare( hist_a, hist_b, NUM_BINS );
 printf( "Result is: %f\n", result );
}
*/
