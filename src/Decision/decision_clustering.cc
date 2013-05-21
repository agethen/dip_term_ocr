#include "decision_clustering.hh"

using namespace std;

void printClusteringResult( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids ){
 cout << "Recognized characters: " << endl;

 for( unsigned int i = 0; i < datapoints.size(); i++ ){
  cout << centroids[datapoints[i].second].second << " ";
if( i%25 == 24 )
 cout << endl;
 }
cout << endl;
}

//Compute distance between to vectors of same dimensionality
double compute_distance( vector<double> & a, vector<double> & b ){
 assert( a.size() == b.size() );
 double tmp = 0;
 for( unsigned int i = 0; i < a.size(); i++ )
  tmp += (a[i]-b[i])*(a[i]-b[i]);

 return sqrt( tmp );
}


//Let's start with a simple method: We generate Features for all known characters (see folder Letters).
//Use these letters as cluster centroids. We then compute the distance of each recognized object to each centroids, and thereby assign a cluster
//(Basically, this is kmeans but with only one iteration)
//
//Parameters:
//datapoints: a vector of pairs. Each pair contains the actual datapoint vector and the assigned cluster (to be determined)
//centroids: a vector of pairs. Each pair contains the actual centroids vector and unsigned char representing the original character
void simpleRecognizeCharacter( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids ){
 if( datapoints.empty() || centroids.empty() )
  return;

 //int dimensionality = centroids[0].first.size();	//The (expected) dimensionality of the datapoints and centroids

 for( unsigned int i = 0; i < datapoints.size(); i++ ){
  double distance = HUGE_VAL;				//Start with distance infinity (i.e., a very high value)
  int c = -1;
  
  for( unsigned int j = 0; j < centroids.size(); j++ ){
   double d = compute_distance( datapoints[i].first, centroids[j].first );

   if( d < distance ){
    distance = d;
    c = j;
   } 
  }

  datapoints[i].second = c;
 }
}


