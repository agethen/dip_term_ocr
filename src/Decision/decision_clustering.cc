#include "decision_clustering.hh"

using namespace std;

void printClusteringResult( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids ){

 cout << "Recognized characters: " << endl;
 for( unsigned int i = 0; i < datapoints.size(); i++ ){
  cout << centroids[datapoints[i].second].second << " ";

if( i%30 == 29 )
 cout << endl;
 }
cout << endl;
}

void printClusteringResult( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids, char * actual ){
 int errors = 0;
 cout << "Recognized characters: " << endl;
 for( unsigned int i = 0; i < datapoints.size(); i++ ){
  cout << centroids[datapoints[i].second].second << " ";
  if( centroids[datapoints[i].second].second != actual[i] ) errors++;
if( i%25 == 24 )
 cout << endl;
 }
cout << endl;

cout << "Number of errors: " << errors << " (" << errors/(double)datapoints.size() << "%)" << endl;
}

//Compute distance between to vectors of same dimensionality
double compute_distance( vector<double> & a, vector<double> & b, vector<double> & weights ){
 assert( a.size() == b.size() );

 double tmp = 0;
 for( unsigned int i = 0; i < a.size(); i++ )		//For each feature
  tmp += weights[i]*weights[i]*(a[i]-b[i])*(a[i]-b[i]); //Apply weight to vectors, compute square-dist

 return sqrt( tmp );
}


//Let's start with a simple method: We generate Features for all known characters (see folder Letters).
//Use these letters as cluster centroids. We then compute the distance of each recognized object to each centroids, and thereby assign a cluster
//(Basically, this is kmeans but with only one iteration)
//
//Parameters:
//datapoints: a vector of pairs. Each pair contains the actual datapoint vector and the assigned cluster (to be determined)
//centroids: a vector of pairs. Each pair contains the actual centroids vector and unsigned char representing the original character
//shape_db and shapes are split since they are histograms that cannot be expressed as a single double
void simpleRecognizeCharacter(
				vector< pair<vector<double>, int> > & datapoints, 
				vector< pair<vector<double>, unsigned char> > & centroids, 
				vector<double> & weights,
				vector< vector<double*> > & shape_db, vector< vector<double*> > & shapes, double shape_weight ){
 if( datapoints.empty() || centroids.empty() )
  return;

 assert( datapoints.size() == shapes.size() );
 assert( shape_db.size() == centroids.size() );

 //int dimensionality = centroids[0].first.size();	//The (expected) dimensionality of the datapoints and centroids

 for( unsigned int i = 0; i < datapoints.size(); i++ ){
  double distance = HUGE_VAL;				//Start with distance infinity (i.e., a very high value)
  int c = -1;
  vector<double *> hist_shape = shapes[i];
  
  for( unsigned int j = 0; j < centroids.size(); j++ ){
   double shape_dist = bipartiteMatching( hist_shape, shape_db[j] )*shape_weight;//chiSquare( hist_shape, shape_db[j], NUM_BINS )*shape_weight;
//cout << shape_dist << endl;
   double d = compute_distance( datapoints[i].first, centroids[j].first, weights )+shape_dist;

   if( d < distance ){
    distance = d;
    c = j;
   } 
  }

  datapoints[i].second = c;
 }
}


