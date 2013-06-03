#ifndef __DECISION_CLUSTERING_HH__
#define __DECISION_CLUSTERING_HH__

#include "../include/header.hh"

/* Perform character recognition */
/* @datapoints: Characters to be classified. Consists of: vector<double>, containing the feature values. int, the centroid index to be determined */
/* @centroids: The characters we can recognize. Consists of: vector<double>, containing the feature values. unsigned char, the character it resembles */
void simpleRecognizeCharacter( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids, vector<double> & weights );

/* Print the result of the recognition */
/* @datapoints: Classified characters */
/* @centroids: Characters we can recognize (= the alphabet) */
void printClusteringResult( vector< pair<vector<double>, int> > & datapoints, vector< pair<vector<double>, unsigned char> > & centroids );
#endif
