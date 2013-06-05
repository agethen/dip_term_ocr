#ifndef __ORIENTATION_HH__
#define __ORIENTATION_HH__
#include <cmath> 
#include <cstdio>
#include "skeletonisation.hh"
using namespace std;
struct lamda
{
	double l_max;
	double l_min;
	double theta;
};
class Moment
{
	private:
		double **M_u;
		double **M;

		double **U;
		double **U_u;
		double **inertia;
		lamda Lamda;
	public:
		Moment(unsigned char *buf, int width, int height);
		~Moment();
		void eigenvalue();
		void print_eigenvalue();
};
#endif