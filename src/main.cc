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

vector< vector<double*> > hist_database;


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
  vector<double *> hist;
  choosePointsUniform( character, 50, hist );
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

  /* Straight lines */
  feature = countVerticalLines( character );
  f.push_back( feature );

  feature = countHorizontalLines( character );
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

  /* Compute Bays and Lakes */
  //commented for now cause i dont want to screw your code up :D
  //vector<double> results = findBaysLakes(character);
  //f.push_back(results.at(0));
  //f.push_back(results.at(1));
  
  centroids.push_back( make_pair( f, (unsigned char) trainingset_files[i][pos] ) );
 }

}


int main( int argc, char ** argv ){
 if( argc != 2 && argc != 4 ) exit(1);
 unsigned int out_max_i = 0;
 unsigned int dis_i = 0;

 if( argc == 4 ){
  if( strcmp( argv[2], "features" ) == 0 )
   sscanf( argv[3], "%d", &out_max_i );
  if( strcmp( argv[2], "show" ) == 0 )
   sscanf( argv[3], "%d", &dis_i );

 }

 vector<Segment> segments;
 vector< pair<vector<double>,int> > datapoints;
 vector< vector<double*> > shapes;
 vector< pair<vector<double>,unsigned char> > centroids;
 vector<double> weights;

 const double shape_weight = 75;

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
  vector<double *> hist;
  choosePointsUniform( segments[i].bmap, 50, hist );
  shapes.push_back( hist );

  /* Order ABSOLUTELY needs to be the same as in training (Can we maybe write a common function for this?) */
  feature = computeFeatureDummy( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 1.0 );

  feature = getEulerNumber( segments[i].bmap );		//Euler feature. Relative stable -> High weight
  f.push_back( feature );
  weights.push_back( 50.0 );
  if( i < out_max_i )
   cout << "E: " << feature;

  /* Circles */

  feature = countCircles( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 10.0 );
  if( i < out_max_i )
   cout << "\tC: " << feature;

  /* Straight lines */
  feature = countVerticalLines( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 30.0 );
  if( i < out_max_i )
   cout << "\tL (V): " << feature;

  feature = countHorizontalLines( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 30.0 );
  if( i < out_max_i )
   cout << "\tL (H): " << feature;

  /* Compute Geometry */

  computeGeometry( segments[i].bmap );

  feature = getAverageDistance();
  f.push_back( feature );
  weights.push_back( 5 );

  feature = getMaximumDistance();
  f.push_back( feature );
  weights.push_back( 5 );

  feature = getArea();
  f.push_back( feature );
  weights.push_back( 1 );

  pair<int,int> f_coord = make_pair( 0,0 );
  getWeightCenter( f_coord );

  f.push_back( f_coord.first );
  weights.push_back( 15 );

  f.push_back( f_coord.second );
  weights.push_back( 15 );

  if( i < out_max_i )
   cout << "\tCenter: (" << f_coord.first << "," << f_coord.second << ")";

  if( i < out_max_i )
   cout << endl;

  /* Compute Bays and Lakes */
  //commented for now cause i dont want to screw your code up :D
  //vector<double> results = findBaysLakes(segments[i].bmap);
  //f.push_back(results.at(0));
  //f.push_back(results.at(1));


  //Save datapoint
  datapoints.push_back( make_pair( f, 0 ) ); //Second value is not important atm.
 }


 if( dis_i > 0 ){
  /* Just for testing */
  int indexno = dis_i - 1;
  sscanf( argv[2], "%d", &indexno );
  cBitmap * testme = segments[indexno].bmap;
  unsigned char * t = (unsigned char*) malloc( testme->getWidth()*testme->getHeight()*sizeof( struct Pixel ) );
  testme->getBitmap( t, testme->getWidth()*testme->getHeight()*sizeof( struct Pixel ) );
  glutViewer( t, testme->getWidth(), testme->getHeight(), argc, argv, 400, 400 );
  free( t );
 }
 //Do clustering
 simpleRecognizeCharacter( datapoints, centroids, weights, hist_database, shapes, shape_weight );

 //Print result ;)
 //For demo purposes, actual string here:
 //char actual[256] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

 //printClusteringResult( datapoints, centroids, actual );
 printClusteringResult( datapoints, centroids );
 return 0;
}
