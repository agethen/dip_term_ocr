#include "shapeContexts.hh"
#include <iostream>
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

void computeDistances( vector<pair<int,int> > & samples, int origin, double * norm_hist ){
 /* hist_distances[0]: #samples with distance 0, etc.
    Assuming image size is 32*32, the max distance is log(sqrt(2)*32) = 3.8 */
 int hist_distances[40];	
 memset( hist_distances, 0, 40*sizeof( int ) );

 unsigned int i = origin;
 for( unsigned int j = 0; j < samples.size(); j++ ){
  if( i == j ) continue;
  int dist = (int)(distance( samples, i, j ));

  if( dist < 0 || dist > 39 ) continue;

  hist_distances[dist]++;
 }
 
 /* Normalize hist_distances */
 int min = 99999;
 int max = -1;
 double count = 0;
 for( int i = 0; i < 40; i++ ){
  if( hist_distances[i] != 0 ){
   count += hist_distances[i];
   if( i < min ) min = i;
   if( i > max ) max = i;
  }
 }

 assert( count >= NUM_BINS );

 double span_bin = (max-min)/(double)(NUM_BINS-1);
 if( span_bin == 0 ) span_bin = 1;

 memset( norm_hist, 0, NUM_BINS*sizeof( double ) );

 for( int i = min; i <= max; i++ ){
  norm_hist[(int)((i-min)/span_bin)] += hist_distances[i]/count;
 }
}

/* Choose a limited number of sample points */
void chooseSamplePoints( cBitmap * bitmap, int num_points, vector<double *> & norm_hist){
 vector<pair<int,int> > samples;
 srand(time(NULL));

 for( int i = 0; i < num_points; i++ ){
  pair<int,int> coordinates = make_pair(0,0);
  while( !chooseRandomPoint( bitmap, coordinates ) ){}
  samples.push_back( coordinates );
 }

 /* Restore */
 restoreImage( bitmap );

 /* Do distance stuff */
 for( unsigned int i = 0; i < samples.size(); i++ ){
  double * n_hist = (double*) malloc( NUM_BINS*sizeof( double ) );
  computeDistances( samples, i, n_hist );
  norm_hist.push_back( n_hist );
 }
}

void choosePointsUniform( cBitmap * bitmap, int num_points, vector<double *> & norm_hist ){
 vector<pair<int,int> > samples;
 int ppc = ceil( num_points/(double)bitmap->getHeight() );	//We want to have ppc pixels per column if possible
 Pixel p;
 srand(time(NULL));

 if( num_points <= 0 ) return;

 while( num_points > 0 ){
  for( int i = 0; i < bitmap->getWidth(); i++ ){
   int numpixel = 0;
   //How many black pixels?
   for( int j = 0; j < bitmap->getHeight(); j++ ){
    bitmap->getPixel( i, j, p );
    if( p.r != 0 ) continue;
    numpixel++;
   }

   //Choose random pixels
   for( int j = 0; j < bitmap->getHeight(); j++ ){
    bitmap->getPixel( i, j, p );
    if( p.r != 0 ) continue;
    double chance = 0;
    if( numpixel > 0 ) chance = ppc/(double) numpixel;
    if( rand()%100 <= chance*100 ){
     samples.push_back( make_pair( i, j ) );
     num_points--;
     p.r = 1;
     bitmap->setPixel( i, j, p );
     if( num_points == 0 ) break;
     j += 5; continue;	//Paper: Have a minimum distance between selected pixels
    }
   }

   if( num_points == 0 ) break;
  }
 }

 /* Restore */
 restoreImage( bitmap );

 /* Do distance stuff */
 for( unsigned int i = 0; i < samples.size(); i++ ){
  double * n_hist = (double*) malloc( NUM_BINS*sizeof( double ) );
  computeDistances( samples, i, n_hist );
  norm_hist.push_back( n_hist );
 }
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
void chooseAllPoints( cBitmap * bitmap, vector<double *> & norm_hist ){
 vector<pair<int,int> > samples;
 Pixel p;

 for( int i = 0; i < bitmap->getWidth(); i++ ){
  for( int j = 0; j < bitmap->getHeight(); j++ ){
   bitmap->getPixel( i, j, p );
   if( p.r == 0 ) samples.push_back( make_pair( i, j ) );
  }
 }

 /* Restore */
 restoreImage( bitmap );

 /* Do distance stuff */
 for( unsigned int i = 0; i < samples.size(); i++ ){
  double * n_hist = (double*) malloc( NUM_BINS*sizeof( double ) );
  computeDistances( samples, i, n_hist );
  norm_hist.push_back( n_hist );
 }
}


double bipartiteMatching( vector<double *> & a, vector<double *> & b ){
 assert( a.size() == b.size() );
 int size = (int) a.size();

 double ** original = new double*[size];
 double ** assignment = new double*[size];
 for( int i = 0; i < size; i++ ){
  assignment[i] = new double[size];
  original[i] = new double[size];
 }

 /* Compute all combinations of shape coefficients */
 for( int i = 0; i < size; i++ ){
  for( int j = i; j < size; j++ ){
   assignment[i][j] = chiSquare( a[i], b[j], NUM_BINS );
   assignment[j][i] = assignment[i][j];
  }  
 }

 for( int i = 0; i < size; i++ )
  memcpy( original[i], assignment[i], size*sizeof(double) ); 

 /* Find matching */
 double result = hungarian( original, assignment, size );

 /* Cleanup */
 for( int i = 0; i < size; i++ ){
  delete[] assignment[i];
 }
 delete[] assignment;
 return result;
}


double hungarian( double ** original, double ** assignment, int size ){
 /* Do bipartite matching (objective: minimum). Hungarian method */
 double * minima = new double[size];
 bool flagRedo;

 double result = 0;

 do{
  /* Find minimum of each column */
  for( int j = 0; j < size; j++ ) minima[j] = assignment[0][j];

  for( int i = 1; i < size; i++ ){
   for( int j = 0; j < size; j++ ){

    if( assignment[i][j] < minima[j] )
     minima[j] = assignment[i][j];
   }
  }

  /* Substract minima from columns */
  for( int i = 0; i < size; i++ ){
   for( int j = 0; j < size; j++ ){
    assignment[i][j] -= minima[j];
   }
  }

  /* Find minimum of each row */
  for( int j = 0; j < size; j++ ) minima[j] = assignment[j][0];
  
  for( int j = 1; j < size; j++ ){
   for( int i = 0; i < size; i++ ){
    if( assignment[i][j] < minima[i] )
     minima[i] = assignment[i][j];
   }
  }

  /* Substract minima from rows */
  for( int j = 0; j < size; j++ ){
   for( int i = 0; i < size; i++ ){
    assignment[i][j] -= minima[i];
   }
  }


  /* Check condition (one marked zero per row/col) */
  bool ** fine = new bool *[size];
  for( int i = 0; i < size; i++ )
   fine[i] = new bool[size];

  for( int i = 0; i < size; i++ )
   for( int j = 0; j < size; j++ )
    if( assignment[i][j] == 0 )
     fine[i][j] = 1;
    else
     fine[i][j] = 0;

  for( int i = 0; i < size; i++ )
   for( int j = 0; j < size; j++ ){
    if( fine[i][j] == 0 ) continue;
    int z = 0;
    bool f = false;

    for( int x = 0; x < size; x++ )
     z += fine[i][x];
    if( z > 1 ) f = true;

    z = 0;
    for( int y = 0; y < size; y++ )
     z += fine[y][j]; 
    if( f && z > 1 ) fine[i][j] = 0;	//If both cols and rows have more than a zero, delete
   }
  
  flagRedo = false;
  for( int i = 0; i < size; i++ ){
   int z = 0;
   for( int j = 0; j < size; j++ )
    z += fine[i][j];
   if( z > 1 ) flagRedo = true;
  }

 if( flagRedo ){
  //cout << "No solution in first iteration" << endl;
  break; //TODO
 }

  for( int i = 0; i < size; i++ )
   delete[] fine[i];

  delete[] fine; 
 }while( flagRedo );

 /* Matching done. Compute result */
 /* We choose a simple sum here. Paper: Any linear mapping */
  for( int i = 0; i < size; i++ ){
   for( int j = 0; j < size; j++ ){
    if( assignment[i][j] == 0 ){ result += original[i][j]; break;}
   }
  }

 delete[] minima;
 return result;
}

/* TODO: If no solution is found after one iteration: Cover all 0's with min. amount of vertical and horizontal lines */
/* Choose a minimum (smallest not covered value) */
/* New matrix: non-covered value: value-min. 1-covered: value. 2-covered: value+min */

int rowPotential( double **, int, int );
int colPotential( double **, int, int );

void markZero( double ** matrix, int size ){
 bool flagNoZero = false;
 int nextIndex = 0;
 bool nextIsRow = false;

 bool * rowMarks = new bool[size];
 bool * colMarks = new bool[size];

 for( int i = 0; i < size; i++ ){
  rowMarks[i] = false;
  colMarks[i] = false;
 }

 while( !flagNoZero ){
  int p =0;
  /* Choose greatest potential, mark */
  /* Don't choose if already marked! */
  //Row potentials
  for( int i = 0; i < size; i++ ){
   if( rowMarks[i] ) continue;
   int t = rowPotential( matrix, i, size );
   if( t > p ){ p = t; nextIndex = i; nextIsRow = true; }
  }
  //Col potentials
  for( int i = 0; i < size; i++ ){
   if( colMarks[i] ) continue;
   int t = colPotential( matrix, i, size );
   if( t > p ){ p = t; nextIndex = i; nextIsRow = false; }
  }

  /* Mark nextIndex (row if nextIsRow == true, col otherwise ) */
  if( nextIsRow )
   rowMarks[nextIndex] = true;
  else
   colMarks[nextIndex] = true;

  /* Check if 0's are left, set flagNoZero accordingly */
 }

 /* Compute minimum */
 int min = 99999;
 for( int i = 0; i < size; i++ ){
  if( rowMarks[i] ) continue;
  for( int j = 0; j < size; j++ ){
   if( colMarks[j] ) continue;
   if( matrix[i][j] < min ) min = matrix[i][j];
  }
 }

 /* Update matrix */
 for( int i = 0; i < size; i++ ){
  for( int j = 0; j < size; j++ ){
   if( rowMarks[i] && colMarks[j] )	//Double marked, add min
    matrix[i][j] += min;
   if( !rowMarks[i] && !colMarks[j] )	//Not marked, substract min
     matrix[i][j] -= min;
					//Leave otherwise
  }
 }
 
 delete[] rowMarks;
 delete[] colMarks;
}

int rowPotential( double ** matrix, int row, int size ){
 int p = 0;
 for( int i = 0; i < size; i++ )
  if( matrix[row][i] == 0 ) p++;
 
 return p;
}

int colPotential( double ** matrix, int col, int size ){
 int p = 0;
 for( int i = 0; i < size; i++ )
  if( matrix[i][col] == 0 ) p++;
 
 return p;
}
/* END TODO */

#ifdef DEBUG_SHAPECONTEXT
int main( int argc, char ** argv ){
 cBitmap * a = new cBitmap( argv[1] );
 cBitmap * b = new cBitmap( argv[2] );
 resizeImage( b, 32, 32 );

 vector<double *> hist_a, hist_b;
 choosePointsUniform( a, 50, hist_a );
 choosePointsUniform( b, 50, hist_b );

 double result = bipartiteMatching( hist_a, hist_b );
 cout << result << endl;
 return 0;
}
#endif
