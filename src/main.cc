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




void buildDatabase( vector< pair<vector<double>,unsigned char> > & centroids ){
 cBitmap * character;
 double feature;

 for( int i = 0; i < 36; i++ ){
  int pos = strlen( trainingset_files[i] )-1-4; //The position of the character in the filenames

  character = new cBitmap( trainingset_files[i] );
  quantizeBW( character );

  vector<double> f; 

  /* Compute all features. Keep the order! */
  /* Counts black pixels */
  feature = computeFeatureDummy( character );
  f.push_back( feature );

  /* Computes Euler number */
  feature = getEulerNumber( character );
  f.push_back( feature );

  centroids.push_back( make_pair( f, (unsigned char) trainingset_files[i][pos] ) );
 }
}


int main( int argc, char ** argv ){
 if( argc != 2 ) exit(1);

 vector<Segment> segments;
 vector< pair<vector<double>,int> > datapoints;
 vector< pair<vector<double>,unsigned char> > centroids;
 vector<double> weights;


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

  /* Compute features */
  /* Order ABSOLUTELY needs to be the same as in training (Can we maybe write a common function for this?) */
  feature = computeFeatureDummy( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 1.0 );

  feature = getEulerNumber( segments[i].bmap );
  f.push_back( feature );
  weights.push_back( 500.0 );

  //Save datapoint
  datapoints.push_back( make_pair( f, 0 ) ); //Second value is not important atm.
 }

 //Do clustering
 simpleRecognizeCharacter( datapoints, centroids, weights );

 //Print result ;)
 printClusteringResult( datapoints, centroids );
 return 0;
}
