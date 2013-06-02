#ifndef __SPLIT_HH__
#define __SPLIT_HH__

#include "Bitmap.hh"

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
struct FontBoundary
{
  //The boundary of each character
	int top;
	int bottom;
	int left;
	int right;
};
class cSplit
{
	public:

		vector<FontBoundary> sentences;
		vector< vector<FontBoundary> > characters;
		int diff;

		cSplit();

		//Find boundary of the sentence. Call at the frist time along with no arguments constructor
		void findSentenceBoundary(cBitmap * );

		//Extract a character from a sentence
		void extract(cBitmap * );

		//Copy sentence i into parameter s
		void getSentences( FontBoundary & s, unsigned int i );

		//Print all sentences
		void printSentences();

		//Get characters range
		void printCharacters();

		//Write the characters out
		void IO(unsigned char *, int, int);
};
#endif
