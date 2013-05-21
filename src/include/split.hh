#include "Bitmap.cc"
#include "viewer.cc"
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
struct font_boundary
{
  //The boundary of each character
	int top;
	int bottom;
	int left;
	int right;
};
class split
{
	private:
		vector<font_boundary> sentences;
		vector< vector<font_boundary> > characters;
		int diff;
	public:
		split();
		//Find boundary of the sentence. Call at the frist time along with no arguments constructor
		void find_sentence_boundary(cBitmap &);
		//Extract a character from a sentence
		void extract(cBitmap &);
		//Get sentences range
		void get_sentences();
		//Get characters range
		void get_characters();
		//Write the characters out
		void IO(unsigned char* &, int, int);
};
