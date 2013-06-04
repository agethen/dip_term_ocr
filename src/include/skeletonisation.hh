#ifndef __SKELETONISATION_HH__
#define __SKELETONISATION_HH__

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

#include "Bitmap.hh"

using namespace std;
struct m_window
{
	unsigned char *x;
};
class hit_miss
{
	private:
		/*
			buf: save the original image.
			M: the image after check for hit-or-miss look up table
			G: the output image
			bond: the weight of each bond
			width: the width of the image
			height: the height of the image 
		*/
		unsigned char *buf;
		unsigned char *M;
		unsigned char *G;
		int *bond;
		int width;
		int height;
	public:
		/*
			constructor: put the bitmap image, width, height and bpp; the bitwise of the image
			is stored in buf. 
		*/
		hit_miss(unsigned char *, int, int, int);
		~hit_miss();
		/*
			check_for_hit() is to check if the (row, column) match the lookup table. The result 
			will be stored in the M; called by skeleton().
		*/
		unsigned char check_for_hit(int, int);
		/*
			check_for_M_hit() is to check if the (row, column) match the lookup table. The result 
			will be stored in the M; called by skeleton().
		*/
		unsigned char check_for_M_hit(int, int);
		/*
			show() prints out the original bitwise image.
		*/
		void show();
		/*
			show_M() prints out the M image.
		*/
		void show_M();
		/*
			show_G() prints out the ginal image.
		*/

		void show_G();
		/*
			skeleton() skeletonises the input image.
		*/
		void skeleton();
		/*
			shift() shifts the G to buf; this function is called for another call of skeleton().
		*/
		void shift();
		/*
			getShrunk takes a buffer, width, and height; the buffer needs to be allocated a chunk of 
			memory. width and height is to double check.
		*/
		void getShrunk(unsigned char*, int w, int h);
};
#endif
