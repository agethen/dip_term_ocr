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
  feature = computeFeatureDummy( character );

  vector<double> f;
  f.push_back( feature );
  centroids.push_back( make_pair( f, (unsigned char) trainingset_files[i][pos] ) );
 }
}


int main( int argc, char ** argv ){
 if( argc != 2 ) exit(1);

 vector<Segment> segments;
 vector< pair<vector<double>,int> > datapoints;
 vector< pair<vector<double>,unsigned char> > centroids;

 bitmap = new cBitmap( argv[1] );
 
 quantizeBW( bitmap );

 findSegments( bitmap, segments );
 
 //Build features for training set
 buildDatabase( centroids );


 //Build features for data
 for( unsigned int i = 0; i < segments.size(); i++ ){
  //Compute a feature
  double feature = computeFeatureDummy( segments[i].bmap );

  //Create the datapoint for this segment (Do this only once!)
  vector<double> f;
  f.push_back( feature );

  //Save datapoint
  datapoints.push_back( make_pair( f, 0 ) ); //Second value is not important atm.
 }

 //Do clustering
 simpleRecognizeCharacter( datapoints, centroids );

 //Print result ;)
 printClusteringResult( datapoints, centroids );
 return 0;
}
