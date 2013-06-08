#include "include/header.hh"

#define PATH_PREFIX "../Letters"

using namespace std;

cBitmap * bitmap;

char trainingset_files[36][24] =
{
 { PATH_PREFIX"/0.bmp\0" }, { PATH_PREFIX"/1.bmp\0" }, { PATH_PREFIX"/2.bmp\0" }, { PATH_PREFIX"/3.bmp\0" },
 { PATH_PREFIX"/4.bmp\0" }, { PATH_PREFIX"/5.bmp\0" }, { PATH_PREFIX"/6.bmp\0" }, { PATH_PREFIX"/7.bmp\0" },
 { PATH_PREFIX"/8.bmp\0" }, { PATH_PREFIX"/9.bmp\0" }, { PATH_PREFIX"/A.bmp\0" }, { PATH_PREFIX"/B.bmp\0" },
 { PATH_PREFIX"/C.bmp\0" }, { PATH_PREFIX"/D.bmp\0" }, { PATH_PREFIX"/E.bmp\0" }, { PATH_PREFIX"/F.bmp\0" },
 { PATH_PREFIX"/G.bmp\0" }, { PATH_PREFIX"/H.bmp\0" }, { PATH_PREFIX"/I.bmp\0" }, { PATH_PREFIX"/J.bmp\0" },
 { PATH_PREFIX"/K.bmp\0" }, { PATH_PREFIX"/L.bmp\0" }, { PATH_PREFIX"/M.bmp\0" }, { PATH_PREFIX"/N.bmp\0" },
 { PATH_PREFIX"/O.bmp\0" }, { PATH_PREFIX"/P.bmp\0" }, { PATH_PREFIX"/Q.bmp\0" }, { PATH_PREFIX"/R.bmp\0" },
 { PATH_PREFIX"/S.bmp\0" }, { PATH_PREFIX"/T.bmp\0" }, { PATH_PREFIX"/U.bmp\0" }, { PATH_PREFIX"/V.bmp\0" },
 { PATH_PREFIX"/W.bmp\0" }, { PATH_PREFIX"/X.bmp\0" }, { PATH_PREFIX"/Y.bmp\0" }, { PATH_PREFIX"/Z.bmp\0" },
};

vector<double*> hist_database;


void buildDatabase( vector< pair<vector<double>,unsigned char> > & centroids ){
 cBitmap * character;
 double feature;

 for( int i = 0; i < 36; i++ ){
  int pos = strlen( trainingset_files[i] )-1-4; //The position of the character in the filenames

  character = new cBitmap( trainingset_files[i] );
  quantizeBW( character );

  vector<double> f; 
  #ifdef DEBUG
  cout << trainingset_files[i] << endl;
  #endif

  /* Compute all features. Keep the order! */
  /* Shape Contexts */
  double * hist = (double*) malloc( NUM_BINS*sizeof( double ) );
  chooseSamplePoints( character, 100, hist );
  hist_database.push_back( hist );

  /* Counts black pixels */
  feature = computeFeatureDummy( character );
  f.push_back( feature );

  /* Computes Euler number */
  feature = getEulerNumber( character );
  f.push_back( feature );

  /* Compute Number of Circles */
  feature = countCircles( character );
  f.push_back( feature );

  /* Compute Geometry */
  computeGeometry( character );
  f.push_back( getAverageDistance() );
  f.push_back( getMaximumDistance() );
  f.push_back( getArea() );
  pair<int,int> f_coord = make_pair( 0,0 );
  getWeightCenter( f_coord );
  f.push_back( f_coord.first );
  f.push_back( f_coord.second );

  centroids.push_back( make_pair( f, (unsigned char) trainingset_files[i][pos] ) );
 }

}


int main( int argc, char ** argv ){
 if( argc != 2 ) exit(1);

 vector<Segment> segments;
 vector< pair<vector<double>,int> > datapoints;
 vector<double*> shapes;
 vector< pair<vector<double>,unsigned char> > centroids;
 vector<double> weights;

 const double shape_weight = 100;

 bitmap = new cBitmap( argv[1] );
 
 /* Do Preprocessing here */

 quantizeBW( bitmap );			//Convert to Black & White bitmap


 /* Segmentation */
 findSegments( bitmap, segments );	//Extract single characters (as bitmaps) from original image
 

 /* Build features for training set */
 buildDatabase( centroids );

 /* Build features for data */
 for( unsigned int i = 0; i < segments.size(); i++ ){
  double feature;

  //Create the datapoint for this segment (Do this only once!)
  vector<double> f;

  /* Preprocessing */
  resizeImage( segments[i].bmap, 32, 32 );		//Training data is 32x32

  /* Compute features */
  double * hist = (double*) malloc( NUM_BINS*sizeof( double ) );
  chooseSamplePoints( segments[i].bmap, 100, hist );
  shapes.push_back( hist );

  /* Order ABSOLUTELY needs to be the same as in training (Can we maybe write a common function for this?) */
  feature = computeFeatureDummy( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 1.0 );

  feature = getEulerNumber( segments[i].bmap );		//Euler feature. Relative stable -> High weight
  f.push_back( feature );
  weights.push_back( 50.0 );

  feature = countCircles( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 20.0 );

  /* Compute Geometry */
  computeGeometry( segments[i].bmap );

  f.push_back( getAverageDistance() );
  weights.push_back( 5 );

  f.push_back( getMaximumDistance() );
  weights.push_back( 5 );

  f.push_back( getArea() );
  weights.push_back( 1 );

  pair<int,int> f_coord = make_pair( 0,0 );
  getWeightCenter( f_coord );

  f.push_back( f_coord.first );
  weights.push_back( 15 );

  f.push_back( f_coord.second );
  weights.push_back( 15 );


  //Save datapoint
  datapoints.push_back( make_pair( f, 0 ) ); //Second value is not important atm.
 }

#ifdef TESTING
 /* Just for testing */
 cBitmap * testme = segments[0].bmap;
 unsigned char * t = (unsigned char*) malloc( testme->getWidth()*testme->getHeight()*sizeof( struct Pixel ) );
 testme->getBitmap( t, testme->getWidth()*testme->getHeight()*sizeof( struct Pixel ) );
 glutViewer( t, testme->getWidth(), testme->getHeight(), argc, argv, 400, 400 );
 free( t );
#endif

 //Do clustering
 simpleRecognizeCharacter( datapoints, centroids, weights, hist_database, shapes, shape_weight );

 //Print result ;)
 printClusteringResult( datapoints, centroids );
 return 0;
}
