#include "setup.hh"

using namespace std;

unsigned char ***hit_matrices;
vector<int> num;
unsigned char ***M_pattern;
vector<int> M_num;
int *x_map = new int[9];
int *hash_lut_hit = new int[512];
int *hash_lut_M = new int[512];
int *hash_lut_bridge = new int[512];

bool isInitialized = false;

void setup_matrix()
{
  if( isInitialized ) return;	//There seems to be some problem (Segmentation fault) calling this method twice. For now, protection against repeated calling.
  isInitialized = true;

	x_map[0] = 1;	x_map[1] = 2;	x_map[2] = 4;
	x_map[3] = 8;	x_map[4] = 16;	x_map[5] = 32;
	x_map[6] = 64;	x_map[7] = 128;	x_map[8] = 256;
	num.push_back(4);	num.push_back(4);	num.push_back(8);	num.push_back(8);
	num.push_back(8);	num.push_back(10);	num.push_back(4);	num.push_back(4);
	num.push_back(8);	num.push_back(4);	num.push_back(4);	
	hit_matrices = new unsigned char **[11];
	//num should have 11 elements; the 12th was a result of misunderstanding the LUT.
	for(int i = 0; i < num.size(); i++) 
	{
		hit_matrices[i] = new unsigned char *[num[i]];
		for(int j = 0; j < num[i]; j++)
		{
			hit_matrices[i][j] = new unsigned char[9];
			memset(hit_matrices[i][j], 0, 9 * sizeof(unsigned char));
		}
	}


	/*hit_matrices[0][0][0] = 0;	hit_matrices[0][0][1] = 0;	hit_matrices[0][0][2] = 1;
	hit_matrices[0][0][3] = 0;	hit_matrices[0][0][4] = 1;	hit_matrices[0][0][5] = 0;
	hit_matrices[0][0][6] = 0;	hit_matrices[0][0][7] = 0;	hit_matrices[0][0][8] = 0;

	hit_matrices[0][1][0] = 1;	hit_matrices[0][1][1] = 0;	hit_matrices[0][1][2] = 0;
	hit_matrices[0][1][3] = 0;	hit_matrices[0][1][4] = 1;	hit_matrices[0][1][5] = 0;
	hit_matrices[0][1][6] = 0;	hit_matrices[0][1][7] = 0;	hit_matrices[0][1][8] = 0;

	hit_matrices[0][2][0] = 0;	hit_matrices[0][2][1] = 0;	hit_matrices[0][2][2] = 0;
	hit_matrices[0][2][3] = 0;	hit_matrices[0][2][4] = 1;	hit_matrices[0][2][5] = 0;
	hit_matrices[0][2][6] = 1;	hit_matrices[0][2][7] = 0;	hit_matrices[0][2][8] = 0;

	hit_matrices[0][3][0] = 0;	hit_matrices[0][3][1] = 0;	hit_matrices[0][3][2] = 0;
	hit_matrices[0][3][3] = 0;	hit_matrices[0][3][4] = 1;	hit_matrices[0][3][5] = 0;
	hit_matrices[0][3][6] = 0;	hit_matrices[0][3][7] = 0;	hit_matrices[0][3][8] = 1;*/




	/*hit_matrices[1][0][0] = 0;	hit_matrices[1][0][1] = 0;	hit_matrices[1][0][2] = 0;
	hit_matrices[1][0][3] = 0;	hit_matrices[1][0][4] = 1;	hit_matrices[1][0][5] = 1;
	hit_matrices[1][0][6] = 0;	hit_matrices[1][0][7] = 0;	hit_matrices[1][0][8] = 0;

	hit_matrices[1][1][0] = 0;	hit_matrices[1][1][1] = 1;	hit_matrices[1][1][2] = 0;
	hit_matrices[1][1][3] = 0;	hit_matrices[1][1][4] = 1;	hit_matrices[1][1][5] = 0;
	hit_matrices[1][1][6] = 0;	hit_matrices[1][1][7] = 0;	hit_matrices[1][1][8] = 0;

	hit_matrices[1][2][0] = 0;	hit_matrices[1][2][1] = 0;	hit_matrices[1][2][2] = 0;
	hit_matrices[1][2][3] = 1;	hit_matrices[1][2][4] = 1;	hit_matrices[1][2][5] = 0;
	hit_matrices[1][2][6] = 0;	hit_matrices[1][2][7] = 0;	hit_matrices[1][2][8] = 0;

	hit_matrices[1][3][0] = 0;	hit_matrices[1][3][1] = 0;	hit_matrices[1][3][2] = 0;
	hit_matrices[1][3][3] = 0;	hit_matrices[1][3][4] = 1;	hit_matrices[1][3][5] = 0;
	hit_matrices[1][3][6] = 0;	hit_matrices[1][3][7] = 1;	hit_matrices[1][3][8] = 0;*/




	/*hit_matrices[2][0][0] = 0;	hit_matrices[2][0][1] = 0;	hit_matrices[2][0][2] = 1;
	hit_matrices[2][0][3] = 0;	hit_matrices[2][0][4] = 1;	hit_matrices[2][0][5] = 1;
	hit_matrices[2][0][6] = 0;	hit_matrices[2][0][7] = 0;	hit_matrices[2][0][8] = 0;

	hit_matrices[2][1][0] = 0;	hit_matrices[2][1][1] = 1;	hit_matrices[2][1][2] = 1;
	hit_matrices[2][1][3] = 0;	hit_matrices[2][1][4] = 1;	hit_matrices[2][1][5] = 0;
	hit_matrices[2][1][6] = 0;	hit_matrices[2][1][7] = 0;	hit_matrices[2][1][8] = 0;

	hit_matrices[2][2][0] = 1;	hit_matrices[2][2][1] = 1;	hit_matrices[2][2][2] = 0;
	hit_matrices[2][2][3] = 0;	hit_matrices[2][2][4] = 1;	hit_matrices[2][2][5] = 0;
	hit_matrices[2][2][6] = 0;	hit_matrices[2][2][7] = 0;	hit_matrices[2][2][8] = 0;

	hit_matrices[2][3][0] = 1;	hit_matrices[2][3][1] = 0;	hit_matrices[2][3][2] = 0;
	hit_matrices[2][3][3] = 1;	hit_matrices[2][3][4] = 1;	hit_matrices[2][3][5] = 0;
	hit_matrices[2][3][6] = 0;	hit_matrices[2][3][7] = 0;	hit_matrices[2][3][8] = 0;

	hit_matrices[2][4][0] = 0;	hit_matrices[2][4][1] = 0;	hit_matrices[2][4][2] = 0;
	hit_matrices[2][4][3] = 1;	hit_matrices[2][4][4] = 1;	hit_matrices[2][4][5] = 0;
	hit_matrices[2][4][6] = 1;	hit_matrices[2][4][7] = 0;	hit_matrices[2][4][8] = 0;

	hit_matrices[2][5][0] = 0;	hit_matrices[2][5][1] = 0;	hit_matrices[2][5][2] = 0;
	hit_matrices[2][5][3] = 0;	hit_matrices[2][5][4] = 1;	hit_matrices[2][5][5] = 0;
	hit_matrices[2][5][6] = 1;	hit_matrices[2][5][7] = 1;	hit_matrices[2][5][8] = 0;

	hit_matrices[2][6][0] = 0;	hit_matrices[2][6][1] = 0;	hit_matrices[2][6][2] = 0;
	hit_matrices[2][6][3] = 0;	hit_matrices[2][6][4] = 1;	hit_matrices[2][6][5] = 0;
	hit_matrices[2][6][6] = 0;	hit_matrices[2][6][7] = 1;	hit_matrices[2][6][8] = 1;

	hit_matrices[2][7][0] = 0;	hit_matrices[2][7][1] = 0;	hit_matrices[2][7][2] = 0;
	hit_matrices[2][7][3] = 0;	hit_matrices[2][7][4] = 1;	hit_matrices[2][7][5] = 1;
	hit_matrices[2][7][6] = 0;	hit_matrices[2][7][7] = 0;	hit_matrices[2][7][8] = 1;*/




	hit_matrices[3][0][0] = 0;	hit_matrices[3][0][1] = 1;	hit_matrices[3][0][2] = 0;
	hit_matrices[3][0][3] = 0;	hit_matrices[3][0][4] = 1;	hit_matrices[3][0][5] = 1;
	hit_matrices[3][0][6] = 0;	hit_matrices[3][0][7] = 0;	hit_matrices[3][0][8] = 0;

	hit_matrices[3][1][0] = 0;	hit_matrices[3][1][1] = 1;	hit_matrices[3][1][2] = 0;
	hit_matrices[3][1][3] = 1;	hit_matrices[3][1][4] = 1;	hit_matrices[3][1][5] = 0;
	hit_matrices[3][1][6] = 0;	hit_matrices[3][1][7] = 0;	hit_matrices[3][1][8] = 0;

	hit_matrices[3][2][0] = 0;	hit_matrices[3][2][1] = 0;	hit_matrices[3][2][2] = 0;
	hit_matrices[3][2][3] = 1;	hit_matrices[3][2][4] = 1;	hit_matrices[3][2][5] = 0;
	hit_matrices[3][2][6] = 0;	hit_matrices[3][2][7] = 1;	hit_matrices[3][2][8] = 0;

	hit_matrices[3][3][0] = 0;	hit_matrices[3][3][1] = 0;	hit_matrices[3][3][2] = 0;
	hit_matrices[3][3][3] = 0;	hit_matrices[3][3][4] = 1;	hit_matrices[3][3][5] = 1;
	hit_matrices[3][3][6] = 0;	hit_matrices[3][3][7] = 1;	hit_matrices[3][3][8] = 0;

	hit_matrices[3][4][0] = 0;	hit_matrices[3][4][1] = 0;	hit_matrices[3][4][2] = 1;
	hit_matrices[3][4][3] = 0;	hit_matrices[3][4][4] = 1;	hit_matrices[3][4][5] = 1;
	hit_matrices[3][4][6] = 0;	hit_matrices[3][4][7] = 0;	hit_matrices[3][4][8] = 1;

	hit_matrices[3][5][0] = 1;	hit_matrices[3][5][1] = 1;	hit_matrices[3][5][2] = 1;
	hit_matrices[3][5][3] = 0;	hit_matrices[3][5][4] = 1;	hit_matrices[3][5][5] = 0;
	hit_matrices[3][5][6] = 0;	hit_matrices[3][5][7] = 0;	hit_matrices[3][5][8] = 0;

	hit_matrices[3][6][0] = 1;	hit_matrices[3][6][1] = 0;	hit_matrices[3][6][2] = 0;
	hit_matrices[3][6][3] = 1;	hit_matrices[3][6][4] = 1;	hit_matrices[3][6][5] = 0;
	hit_matrices[3][6][6] = 1;	hit_matrices[3][6][7] = 0;	hit_matrices[3][6][8] = 0;

	hit_matrices[3][7][0] = 0;	hit_matrices[3][7][1] = 0;	hit_matrices[3][7][2] = 0;
	hit_matrices[3][7][3] = 0;	hit_matrices[3][7][4] = 1;	hit_matrices[3][7][5] = 0;
	hit_matrices[3][7][6] = 1;	hit_matrices[3][7][7] = 1;	hit_matrices[3][7][8] = 1;




	/*hit_matrices[4][0][0] = 1;	hit_matrices[4][0][1] = 1;	hit_matrices[4][0][2] = 0;
	hit_matrices[4][0][3] = 0;	hit_matrices[4][0][4] = 1;	hit_matrices[4][0][5] = 1;
	hit_matrices[4][0][6] = 0;	hit_matrices[4][0][7] = 0;	hit_matrices[4][0][8] = 0;

	hit_matrices[4][1][0] = 0;	hit_matrices[4][1][1] = 1;	hit_matrices[4][1][2] = 0;
	hit_matrices[4][1][3] = 0;	hit_matrices[4][1][4] = 1;	hit_matrices[4][1][5] = 1;
	hit_matrices[4][1][6] = 0;	hit_matrices[4][1][7] = 0;	hit_matrices[4][1][8] = 1;

	hit_matrices[4][2][0] = 0;	hit_matrices[4][2][1] = 1;	hit_matrices[4][2][2] = 1;
	hit_matrices[4][2][3] = 1;	hit_matrices[4][2][4] = 1;	hit_matrices[4][2][5] = 0;
	hit_matrices[4][2][6] = 0;	hit_matrices[4][2][7] = 0;	hit_matrices[4][2][8] = 0;

	hit_matrices[4][3][0] = 0;	hit_matrices[4][3][1] = 0;	hit_matrices[4][3][2] = 1;
	hit_matrices[4][3][3] = 0;	hit_matrices[4][3][4] = 1;	hit_matrices[4][3][5] = 1;
	hit_matrices[4][3][6] = 0;	hit_matrices[4][3][7] = 1;	hit_matrices[4][3][8] = 0;

	hit_matrices[4][4][0] = 0;	hit_matrices[4][4][1] = 1;	hit_matrices[4][4][2] = 1;
	hit_matrices[4][4][3] = 0;	hit_matrices[4][4][4] = 1;	hit_matrices[4][4][5] = 1;
	hit_matrices[4][4][6] = 0;	hit_matrices[4][4][7] = 0;	hit_matrices[4][4][8] = 0;

	hit_matrices[4][5][0] = 1;	hit_matrices[4][5][1] = 1;	hit_matrices[4][5][2] = 0;
	hit_matrices[4][5][3] = 1;	hit_matrices[4][5][4] = 1;	hit_matrices[4][5][5] = 0;
	hit_matrices[4][5][6] = 0;	hit_matrices[4][5][7] = 0;	hit_matrices[4][5][8] = 0;

	hit_matrices[4][6][0] = 0;	hit_matrices[4][6][1] = 0;	hit_matrices[4][6][2] = 0;
	hit_matrices[4][6][3] = 1;	hit_matrices[4][6][4] = 1;	hit_matrices[4][6][5] = 0;
	hit_matrices[4][6][6] = 1;	hit_matrices[4][6][7] = 1;	hit_matrices[4][6][8] = 0;


	hit_matrices[4][7][0] = 0;	hit_matrices[4][7][1] = 0;	hit_matrices[4][7][2] = 0;
	hit_matrices[4][7][3] = 0;	hit_matrices[4][7][4] = 1;	hit_matrices[4][7][5] = 1;
	hit_matrices[4][7][6] = 0;	hit_matrices[4][7][7] = 1;	hit_matrices[4][7][8] = 1;*/




	/*hit_matrices[5][0][0] = 1;	hit_matrices[5][0][1] = 1;	hit_matrices[5][0][2] = 0;
	hit_matrices[5][0][3] = 0;	hit_matrices[5][0][4] = 1;	hit_matrices[5][0][5] = 1;
	hit_matrices[5][0][6] = 0;	hit_matrices[5][0][7] = 0;	hit_matrices[5][0][8] = 1;

	hit_matrices[5][1][0] = 0;	hit_matrices[5][1][1] = 1;	hit_matrices[5][1][2] = 1;
	hit_matrices[5][1][3] = 1;	hit_matrices[5][1][4] = 1;	hit_matrices[5][1][5] = 0;
	hit_matrices[5][1][6] = 1;	hit_matrices[5][1][7] = 0;	hit_matrices[5][1][8] = 0;*/

	hit_matrices[5][2][0] = 1;	hit_matrices[5][2][1] = 1;	hit_matrices[5][2][2] = 1;
	hit_matrices[5][2][3] = 0;	hit_matrices[5][2][4] = 1;	hit_matrices[5][2][5] = 1;
	hit_matrices[5][2][6] = 0;	hit_matrices[5][2][7] = 0;	hit_matrices[5][2][8] = 0;

	hit_matrices[5][3][0] = 0;	hit_matrices[5][3][1] = 1;	hit_matrices[5][3][2] = 1;
	hit_matrices[5][3][3] = 0;	hit_matrices[5][3][4] = 1;	hit_matrices[5][3][5] = 1;
	hit_matrices[5][3][6] = 0;	hit_matrices[5][3][7] = 0;	hit_matrices[5][3][8] = 1;

	hit_matrices[5][4][0] = 1;	hit_matrices[5][4][1] = 1;	hit_matrices[5][4][2] = 1;
	hit_matrices[5][4][3] = 1;	hit_matrices[5][4][4] = 1;	hit_matrices[5][4][5] = 0;
	hit_matrices[5][4][6] = 0;	hit_matrices[5][4][7] = 0;	hit_matrices[5][4][8] = 0;

	hit_matrices[5][5][0] = 1;	hit_matrices[5][5][1] = 1;	hit_matrices[5][5][2] = 0;
	hit_matrices[5][5][3] = 1;	hit_matrices[5][5][4] = 1;	hit_matrices[5][5][5] = 0;
	hit_matrices[5][5][6] = 1;	hit_matrices[5][5][7] = 0;	hit_matrices[5][5][8] = 0;

	hit_matrices[5][6][0] = 1;	hit_matrices[5][6][1] = 0;	hit_matrices[5][6][2] = 0;
	hit_matrices[5][6][3] = 1;	hit_matrices[5][6][4] = 1;	hit_matrices[5][6][5] = 0;
	hit_matrices[5][6][6] = 1;	hit_matrices[5][6][7] = 1;	hit_matrices[5][6][8] = 0;

	hit_matrices[5][7][0] = 0;	hit_matrices[5][7][1] = 0;	hit_matrices[5][7][2] = 0;
	hit_matrices[5][7][3] = 1;	hit_matrices[5][7][4] = 1;	hit_matrices[5][7][5] = 0;
	hit_matrices[5][7][6] = 1;	hit_matrices[5][7][7] = 1;	hit_matrices[5][7][8] = 1;

	hit_matrices[5][8][0] = 0;	hit_matrices[5][8][1] = 0;	hit_matrices[5][8][2] = 0;
	hit_matrices[5][8][3] = 0;	hit_matrices[5][8][4] = 1;	hit_matrices[5][8][5] = 1;
	hit_matrices[5][8][6] = 1;	hit_matrices[5][8][7] = 1;	hit_matrices[5][8][8] = 1;


	hit_matrices[5][9][0] = 0;	hit_matrices[5][9][1] = 0;	hit_matrices[5][9][2] = 1;
	hit_matrices[5][9][3] = 0;	hit_matrices[5][9][4] = 1;	hit_matrices[5][9][5] = 1;
	hit_matrices[5][9][6] = 0;	hit_matrices[5][9][7] = 1;	hit_matrices[5][9][8] = 1;




	hit_matrices[6][0][0] = 1;	hit_matrices[6][0][1] = 1;	hit_matrices[6][0][2] = 1;
	hit_matrices[6][0][3] = 0;	hit_matrices[6][0][4] = 1;	hit_matrices[6][0][5] = 1;
	hit_matrices[6][0][6] = 0;	hit_matrices[6][0][7] = 0;	hit_matrices[6][0][8] = 1;

	hit_matrices[6][1][0] = 1;	hit_matrices[6][1][1] = 1;	hit_matrices[6][1][2] = 1;
	hit_matrices[6][1][3] = 1;	hit_matrices[6][1][4] = 1;	hit_matrices[6][1][5] = 0;
	hit_matrices[6][1][6] = 1;	hit_matrices[6][1][7] = 0;	hit_matrices[6][1][8] = 0;

	hit_matrices[6][2][0] = 1;	hit_matrices[6][2][1] = 0;	hit_matrices[6][2][2] = 0;
	hit_matrices[6][2][3] = 1;	hit_matrices[6][2][4] = 1;	hit_matrices[6][2][5] = 0;
	hit_matrices[6][2][6] = 1;	hit_matrices[6][2][7] = 1;	hit_matrices[6][2][8] = 1;

	hit_matrices[6][3][0] = 0;	hit_matrices[6][3][1] = 0;	hit_matrices[6][3][2] = 1;
	hit_matrices[6][3][3] = 0;	hit_matrices[6][3][4] = 1;	hit_matrices[6][3][5] = 1;
	hit_matrices[6][3][6] = 1;	hit_matrices[6][3][7] = 1;	hit_matrices[6][3][8] = 1;




	hit_matrices[7][0][0] = 0;	hit_matrices[7][0][1] = 1;	hit_matrices[7][0][2] = 1;
	hit_matrices[7][0][3] = 0;	hit_matrices[7][0][4] = 1;	hit_matrices[7][0][5] = 1;
	hit_matrices[7][0][6] = 0;	hit_matrices[7][0][7] = 1;	hit_matrices[7][0][8] = 1;

	hit_matrices[7][1][0] = 1;	hit_matrices[7][1][1] = 1;	hit_matrices[7][1][2] = 1;
	hit_matrices[7][1][3] = 1;	hit_matrices[7][1][4] = 1;	hit_matrices[7][1][5] = 1;
	hit_matrices[7][1][6] = 0;	hit_matrices[7][1][7] = 0;	hit_matrices[7][1][8] = 0;

	hit_matrices[7][2][0] = 1;	hit_matrices[7][2][1] = 1;	hit_matrices[7][2][2] = 0;
	hit_matrices[7][2][3] = 1;	hit_matrices[7][2][4] = 1;	hit_matrices[7][2][5] = 0;
	hit_matrices[7][2][6] = 1;	hit_matrices[7][2][7] = 1;	hit_matrices[7][2][8] = 0;

	hit_matrices[7][3][0] = 0;	hit_matrices[7][3][1] = 0;	hit_matrices[7][3][2] = 0;
	hit_matrices[7][3][3] = 1;	hit_matrices[7][3][4] = 1;	hit_matrices[7][3][5] = 1;
	hit_matrices[7][3][6] = 1;	hit_matrices[7][3][7] = 1;	hit_matrices[7][3][8] = 1;




	hit_matrices[8][0][0] = 1;	hit_matrices[8][0][1] = 1;	hit_matrices[8][0][2] = 1;
	hit_matrices[8][0][3] = 0;	hit_matrices[8][0][4] = 1;	hit_matrices[8][0][5] = 1;
	hit_matrices[8][0][6] = 0;	hit_matrices[8][0][7] = 1;	hit_matrices[8][0][8] = 1;

	hit_matrices[8][1][0] = 0;	hit_matrices[8][1][1] = 1;	hit_matrices[8][1][2] = 1;
	hit_matrices[8][1][3] = 0;	hit_matrices[8][1][4] = 1;	hit_matrices[8][1][5] = 1;
	hit_matrices[8][1][6] = 1;	hit_matrices[8][1][7] = 1;	hit_matrices[8][1][8] = 1;

	hit_matrices[8][2][0] = 1;	hit_matrices[8][2][1] = 1;	hit_matrices[8][2][2] = 1;
	hit_matrices[8][2][3] = 1;	hit_matrices[8][2][4] = 1;	hit_matrices[8][2][5] = 1;
	hit_matrices[8][2][6] = 1;	hit_matrices[8][2][7] = 0;	hit_matrices[8][2][8] = 0;

	hit_matrices[8][3][0] = 1;	hit_matrices[8][3][1] = 1;	hit_matrices[8][3][2] = 1;
	hit_matrices[8][3][3] = 1;	hit_matrices[8][3][4] = 1;	hit_matrices[8][3][5] = 1;
	hit_matrices[8][3][6] = 0;	hit_matrices[8][3][7] = 0;	hit_matrices[8][3][8] = 1;

	hit_matrices[8][4][0] = 1;	hit_matrices[8][4][1] = 1;	hit_matrices[8][4][2] = 1;
	hit_matrices[8][4][3] = 1;	hit_matrices[8][4][4] = 1;	hit_matrices[8][4][5] = 0;
	hit_matrices[8][4][6] = 1;	hit_matrices[8][4][7] = 1;	hit_matrices[8][4][8] = 0;

	hit_matrices[8][5][0] = 1;	hit_matrices[8][5][1] = 1;	hit_matrices[8][5][2] = 0;
	hit_matrices[8][5][3] = 1;	hit_matrices[8][5][4] = 1;	hit_matrices[8][5][5] = 0;
	hit_matrices[8][5][6] = 1;	hit_matrices[8][5][7] = 1;	hit_matrices[8][5][8] = 1;

	hit_matrices[8][6][0] = 1;	hit_matrices[8][6][1] = 0;	hit_matrices[8][6][2] = 0;
	hit_matrices[8][6][3] = 1;	hit_matrices[8][6][4] = 1;	hit_matrices[8][6][5] = 1;
	hit_matrices[8][6][6] = 1;	hit_matrices[8][6][7] = 1;	hit_matrices[8][6][8] = 1;

	hit_matrices[8][7][0] = 0;	hit_matrices[8][7][1] = 0;	hit_matrices[8][7][2] = 1;
	hit_matrices[8][7][3] = 1;	hit_matrices[8][7][4] = 1;	hit_matrices[8][7][5] = 1;
	hit_matrices[8][7][6] = 1;	hit_matrices[8][7][7] = 1;	hit_matrices[8][7][8] = 1;




	hit_matrices[9][0][0] = 1;	hit_matrices[9][0][1] = 1;	hit_matrices[9][0][2] = 1;
	hit_matrices[9][0][3] = 0;	hit_matrices[9][0][4] = 1;	hit_matrices[9][0][5] = 1;
	hit_matrices[9][0][6] = 1;	hit_matrices[9][0][7] = 1;	hit_matrices[9][0][8] = 1;

	hit_matrices[9][1][0] = 1;	hit_matrices[9][1][1] = 1;	hit_matrices[9][1][2] = 1;
	hit_matrices[9][1][3] = 1;	hit_matrices[9][1][4] = 1;	hit_matrices[9][1][5] = 1;
	hit_matrices[9][1][6] = 1;	hit_matrices[9][1][7] = 0;	hit_matrices[9][1][8] = 1;

	hit_matrices[9][2][0] = 1;	hit_matrices[9][2][1] = 1;	hit_matrices[9][2][2] = 1;
	hit_matrices[9][2][3] = 1;	hit_matrices[9][2][4] = 1;	hit_matrices[9][2][5] = 0;
	hit_matrices[9][2][6] = 1;	hit_matrices[9][2][7] = 1;	hit_matrices[9][2][8] = 1;

	hit_matrices[9][3][0] = 1;	hit_matrices[9][3][1] = 0;	hit_matrices[9][3][2] = 1;
	hit_matrices[9][3][3] = 1;	hit_matrices[9][3][4] = 1;	hit_matrices[9][3][5] = 1;
	hit_matrices[9][3][6] = 1;	hit_matrices[9][3][7] = 1;	hit_matrices[9][3][8] = 1;




	hit_matrices[10][0][0] = 1;	hit_matrices[10][0][1] = 1;	hit_matrices[10][0][2] = 1;
	hit_matrices[10][0][3] = 1;	hit_matrices[10][0][4] = 1;	hit_matrices[10][0][5] = 1;
	hit_matrices[10][0][6] = 0;	hit_matrices[10][0][7] = 1;	hit_matrices[10][0][8] = 1;

	hit_matrices[10][1][0] = 1;	hit_matrices[10][1][1] = 1;	hit_matrices[10][1][2] = 1;
	hit_matrices[10][1][3] = 1;	hit_matrices[10][1][4] = 1;	hit_matrices[10][1][5] = 1;
	hit_matrices[10][1][6] = 1;	hit_matrices[10][1][7] = 1;	hit_matrices[10][1][8] = 0;

	hit_matrices[10][2][0] = 1;	hit_matrices[10][2][1] = 1;	hit_matrices[10][2][2] = 0;
	hit_matrices[10][2][3] = 1;	hit_matrices[10][2][4] = 1;	hit_matrices[10][2][5] = 1;
	hit_matrices[10][2][6] = 1;	hit_matrices[10][2][7] = 1;	hit_matrices[10][2][8] = 1;

	hit_matrices[10][3][0] = 0;	hit_matrices[10][3][1] = 1;	hit_matrices[10][3][2] = 1;
	hit_matrices[10][3][3] = 1;	hit_matrices[10][3][4] = 1;	hit_matrices[10][3][5] = 1;
	hit_matrices[10][3][6] = 1;	hit_matrices[10][3][7] = 1;	hit_matrices[10][3][8] = 1;




	

	M_num.push_back(4);		M_num.push_back(4);		M_num.push_back(4);		M_num.push_back(64);
	M_num.push_back(128);	M_num.push_back(224);	M_num.push_back(16);	
	M_pattern = new unsigned char **[7];
	for(int i = 0; i < M_num.size(); i++)
	{
		M_pattern[i] = new unsigned char *[M_num[i]];
		for(int j = 0; j < M_num[i]; j++)
		{
			M_pattern[i][j] = new unsigned char[9];
		}
	}
	M_pattern[0][0][0] = 0;	M_pattern[0][0][1] = 0;	M_pattern[0][0][2] = 0;
	M_pattern[0][0][3] = 0;	M_pattern[0][0][4] = 1;	M_pattern[0][0][5] = 0;
	M_pattern[0][0][6] = 0;	M_pattern[0][0][7] = 0;	M_pattern[0][0][8] = 1;


	M_pattern[0][1][0] = 0;	M_pattern[0][1][1] = 0;	M_pattern[0][1][2] = 0;
	M_pattern[0][1][3] = 0;	M_pattern[0][1][4] = 1;	M_pattern[0][1][5] = 0;
	M_pattern[0][1][6] = 1;	M_pattern[0][1][7] = 0;	M_pattern[0][1][8] = 0;


	M_pattern[0][2][0] = 0;	M_pattern[0][2][1] = 0;	M_pattern[0][2][2] = 1;
	M_pattern[0][2][3] = 0;	M_pattern[0][2][4] = 1;	M_pattern[0][2][5] = 0;
	M_pattern[0][2][6] = 0;	M_pattern[0][2][7] = 0;	M_pattern[0][2][8] = 0;


	M_pattern[0][3][0] = 1;	M_pattern[0][3][1] = 0;	M_pattern[0][3][2] = 0;
	M_pattern[0][3][3] = 0;	M_pattern[0][3][4] = 1;	M_pattern[0][3][5] = 0;
	M_pattern[0][3][6] = 0;	M_pattern[0][3][7] = 0;	M_pattern[0][3][8] = 0;





	M_pattern[1][0][0] = 0;	M_pattern[1][0][1] = 0;	M_pattern[1][0][2] = 0;
	M_pattern[1][0][3] = 0;	M_pattern[1][0][4] = 1;	M_pattern[1][0][5] = 0;
	M_pattern[1][0][6] = 0;	M_pattern[1][0][7] = 1;	M_pattern[1][0][8] = 0;


	M_pattern[1][1][0] = 0;	M_pattern[1][1][1] = 0;	M_pattern[1][1][2] = 0;
	M_pattern[1][1][3] = 0;	M_pattern[1][1][4] = 1;	M_pattern[1][1][5] = 1;
	M_pattern[1][1][6] = 0;	M_pattern[1][1][7] = 0;	M_pattern[1][1][8] = 0;


	M_pattern[1][2][0] = 0;	M_pattern[1][2][1] = 0;	M_pattern[1][2][2] = 0;
	M_pattern[1][2][3] = 1;	M_pattern[1][2][4] = 1;	M_pattern[1][2][5] = 0;
	M_pattern[1][2][6] = 0;	M_pattern[1][2][7] = 0;	M_pattern[1][2][8] = 0;


	M_pattern[1][3][0] = 0;	M_pattern[1][3][1] = 1;	M_pattern[1][3][2] = 0;
	M_pattern[1][3][3] = 0;	M_pattern[1][3][4] = 1;	M_pattern[1][3][5] = 0;
	M_pattern[1][3][6] = 0;	M_pattern[1][3][7] = 0;	M_pattern[1][3][8] = 0;





	M_pattern[2][0][0] = 0;	M_pattern[2][0][1] = 1;	M_pattern[2][0][2] = 0;
	M_pattern[2][0][3] = 0;	M_pattern[2][0][4] = 1;	M_pattern[2][0][5] = 1;
	M_pattern[2][0][6] = 0;	M_pattern[2][0][7] = 0;	M_pattern[2][0][8] = 0;


	M_pattern[2][1][0] = 0;	M_pattern[2][1][1] = 1;	M_pattern[2][1][2] = 0;
	M_pattern[2][1][3] = 1;	M_pattern[2][1][4] = 1;	M_pattern[2][1][5] = 0;
	M_pattern[2][1][6] = 0;	M_pattern[2][1][7] = 0;	M_pattern[2][1][8] = 0;


	M_pattern[2][2][0] = 0;	M_pattern[2][2][1] = 0;	M_pattern[2][2][2] = 0;
	M_pattern[2][2][3] = 0;	M_pattern[2][2][4] = 1;	M_pattern[2][2][5] = 1;
	M_pattern[2][2][6] = 0;	M_pattern[2][2][7] = 1;	M_pattern[2][2][8] = 0;


	M_pattern[2][3][0] = 0;	M_pattern[2][3][1] = 0;	M_pattern[2][3][2] = 0;
	M_pattern[2][3][3] = 1;	M_pattern[2][3][4] = 1;	M_pattern[2][3][5] = 0;
	M_pattern[2][3][6] = 0;	M_pattern[2][3][7] = 1;	M_pattern[2][3][8] = 0;





	M_pattern[3][0][0] = 1;	M_pattern[3][0][1] = 1;	M_pattern[3][0][2] = 0;
	M_pattern[3][0][3] = 1;	M_pattern[3][0][4] = 1;	M_pattern[3][0][5] = 0;
	M_pattern[3][0][6] = 0;	M_pattern[3][0][7] = 0;	M_pattern[3][0][8] = 0;


	M_pattern[3][1][0] = 1;	M_pattern[3][1][1] = 1;	M_pattern[3][1][2] = 0;
	M_pattern[3][1][3] = 1;	M_pattern[3][1][4] = 1;	M_pattern[3][1][5] = 0;
	M_pattern[3][1][6] = 0;	M_pattern[3][1][7] = 0;	M_pattern[3][1][8] = 1;


	M_pattern[3][2][0] = 1;	M_pattern[3][2][1] = 1;	M_pattern[3][2][2] = 0;
	M_pattern[3][2][3] = 1;	M_pattern[3][2][4] = 1;	M_pattern[3][2][5] = 0;
	M_pattern[3][2][6] = 0;	M_pattern[3][2][7] = 1;	M_pattern[3][2][8] = 0;


	M_pattern[3][3][0] = 1;	M_pattern[3][3][1] = 1;	M_pattern[3][3][2] = 0;
	M_pattern[3][3][3] = 1;	M_pattern[3][3][4] = 1;	M_pattern[3][3][5] = 0;
	M_pattern[3][3][6] = 0;	M_pattern[3][3][7] = 1;	M_pattern[3][3][8] = 1;


	M_pattern[3][4][0] = 1;	M_pattern[3][4][1] = 1;	M_pattern[3][4][2] = 0;
	M_pattern[3][4][3] = 1;	M_pattern[3][4][4] = 1;	M_pattern[3][4][5] = 0;
	M_pattern[3][4][6] = 1;	M_pattern[3][4][7] = 0;	M_pattern[3][4][8] = 0;


	M_pattern[3][5][0] = 1;	M_pattern[3][5][1] = 1;	M_pattern[3][5][2] = 0;
	M_pattern[3][5][3] = 1;	M_pattern[3][5][4] = 1;	M_pattern[3][5][5] = 0;
	M_pattern[3][5][6] = 1;	M_pattern[3][5][7] = 0;	M_pattern[3][5][8] = 1;


	M_pattern[3][6][0] = 1;	M_pattern[3][6][1] = 1;	M_pattern[3][6][2] = 0;
	M_pattern[3][6][3] = 1;	M_pattern[3][6][4] = 1;	M_pattern[3][6][5] = 0;
	M_pattern[3][6][6] = 1;	M_pattern[3][6][7] = 1;	M_pattern[3][6][8] = 0;


	M_pattern[3][7][0] = 1;	M_pattern[3][7][1] = 1;	M_pattern[3][7][2] = 0;
	M_pattern[3][7][3] = 1;	M_pattern[3][7][4] = 1;	M_pattern[3][7][5] = 0;
	M_pattern[3][7][6] = 1;	M_pattern[3][7][7] = 1;	M_pattern[3][7][8] = 1;


	M_pattern[3][8][0] = 1;	M_pattern[3][8][1] = 1;	M_pattern[3][8][2] = 0;
	M_pattern[3][8][3] = 1;	M_pattern[3][8][4] = 1;	M_pattern[3][8][5] = 1;
	M_pattern[3][8][6] = 0;	M_pattern[3][8][7] = 0;	M_pattern[3][8][8] = 0;


	M_pattern[3][9][0] = 1;	M_pattern[3][9][1] = 1;	M_pattern[3][9][2] = 0;
	M_pattern[3][9][3] = 1;	M_pattern[3][9][4] = 1;	M_pattern[3][9][5] = 1;
	M_pattern[3][9][6] = 0;	M_pattern[3][9][7] = 0;	M_pattern[3][9][8] = 1;


	M_pattern[3][10][0] = 1;	M_pattern[3][10][1] = 1;	M_pattern[3][10][2] = 0;
	M_pattern[3][10][3] = 1;	M_pattern[3][10][4] = 1;	M_pattern[3][10][5] = 1;
	M_pattern[3][10][6] = 0;	M_pattern[3][10][7] = 1;	M_pattern[3][10][8] = 0;


	M_pattern[3][11][0] = 1;	M_pattern[3][11][1] = 1;	M_pattern[3][11][2] = 0;
	M_pattern[3][11][3] = 1;	M_pattern[3][11][4] = 1;	M_pattern[3][11][5] = 1;
	M_pattern[3][11][6] = 0;	M_pattern[3][11][7] = 1;	M_pattern[3][11][8] = 1;


	M_pattern[3][12][0] = 1;	M_pattern[3][12][1] = 1;	M_pattern[3][12][2] = 0;
	M_pattern[3][12][3] = 1;	M_pattern[3][12][4] = 1;	M_pattern[3][12][5] = 1;
	M_pattern[3][12][6] = 1;	M_pattern[3][12][7] = 0;	M_pattern[3][12][8] = 0;


	M_pattern[3][13][0] = 1;	M_pattern[3][13][1] = 1;	M_pattern[3][13][2] = 0;
	M_pattern[3][13][3] = 1;	M_pattern[3][13][4] = 1;	M_pattern[3][13][5] = 1;
	M_pattern[3][13][6] = 1;	M_pattern[3][13][7] = 0;	M_pattern[3][13][8] = 1;


	M_pattern[3][14][0] = 1;	M_pattern[3][14][1] = 1;	M_pattern[3][14][2] = 0;
	M_pattern[3][14][3] = 1;	M_pattern[3][14][4] = 1;	M_pattern[3][14][5] = 1;
	M_pattern[3][14][6] = 1;	M_pattern[3][14][7] = 1;	M_pattern[3][14][8] = 0;


	M_pattern[3][15][0] = 1;	M_pattern[3][15][1] = 1;	M_pattern[3][15][2] = 0;
	M_pattern[3][15][3] = 1;	M_pattern[3][15][4] = 1;	M_pattern[3][15][5] = 1;
	M_pattern[3][15][6] = 1;	M_pattern[3][15][7] = 1;	M_pattern[3][15][8] = 1;


	M_pattern[3][16][0] = 1;	M_pattern[3][16][1] = 1;	M_pattern[3][16][2] = 1;
	M_pattern[3][16][3] = 1;	M_pattern[3][16][4] = 1;	M_pattern[3][16][5] = 0;
	M_pattern[3][16][6] = 0;	M_pattern[3][16][7] = 0;	M_pattern[3][16][8] = 0;


	M_pattern[3][17][0] = 1;	M_pattern[3][17][1] = 1;	M_pattern[3][17][2] = 1;
	M_pattern[3][17][3] = 1;	M_pattern[3][17][4] = 1;	M_pattern[3][17][5] = 0;
	M_pattern[3][17][6] = 0;	M_pattern[3][17][7] = 0;	M_pattern[3][17][8] = 1;


	M_pattern[3][18][0] = 1;	M_pattern[3][18][1] = 1;	M_pattern[3][18][2] = 1;
	M_pattern[3][18][3] = 1;	M_pattern[3][18][4] = 1;	M_pattern[3][18][5] = 0;
	M_pattern[3][18][6] = 0;	M_pattern[3][18][7] = 1;	M_pattern[3][18][8] = 0;


	M_pattern[3][19][0] = 1;	M_pattern[3][19][1] = 1;	M_pattern[3][19][2] = 1;
	M_pattern[3][19][3] = 1;	M_pattern[3][19][4] = 1;	M_pattern[3][19][5] = 0;
	M_pattern[3][19][6] = 0;	M_pattern[3][19][7] = 1;	M_pattern[3][19][8] = 1;


	M_pattern[3][20][0] = 1;	M_pattern[3][20][1] = 1;	M_pattern[3][20][2] = 1;
	M_pattern[3][20][3] = 1;	M_pattern[3][20][4] = 1;	M_pattern[3][20][5] = 0;
	M_pattern[3][20][6] = 1;	M_pattern[3][20][7] = 0;	M_pattern[3][20][8] = 0;


	M_pattern[3][21][0] = 1;	M_pattern[3][21][1] = 1;	M_pattern[3][21][2] = 1;
	M_pattern[3][21][3] = 1;	M_pattern[3][21][4] = 1;	M_pattern[3][21][5] = 0;
	M_pattern[3][21][6] = 1;	M_pattern[3][21][7] = 0;	M_pattern[3][21][8] = 1;


	M_pattern[3][22][0] = 1;	M_pattern[3][22][1] = 1;	M_pattern[3][22][2] = 1;
	M_pattern[3][22][3] = 1;	M_pattern[3][22][4] = 1;	M_pattern[3][22][5] = 0;
	M_pattern[3][22][6] = 1;	M_pattern[3][22][7] = 1;	M_pattern[3][22][8] = 0;


	M_pattern[3][23][0] = 1;	M_pattern[3][23][1] = 1;	M_pattern[3][23][2] = 1;
	M_pattern[3][23][3] = 1;	M_pattern[3][23][4] = 1;	M_pattern[3][23][5] = 0;
	M_pattern[3][23][6] = 1;	M_pattern[3][23][7] = 1;	M_pattern[3][23][8] = 1;


	M_pattern[3][24][0] = 1;	M_pattern[3][24][1] = 1;	M_pattern[3][24][2] = 1;
	M_pattern[3][24][3] = 1;	M_pattern[3][24][4] = 1;	M_pattern[3][24][5] = 1;
	M_pattern[3][24][6] = 0;	M_pattern[3][24][7] = 0;	M_pattern[3][24][8] = 0;


	M_pattern[3][25][0] = 1;	M_pattern[3][25][1] = 1;	M_pattern[3][25][2] = 1;
	M_pattern[3][25][3] = 1;	M_pattern[3][25][4] = 1;	M_pattern[3][25][5] = 1;
	M_pattern[3][25][6] = 0;	M_pattern[3][25][7] = 0;	M_pattern[3][25][8] = 1;


	M_pattern[3][26][0] = 1;	M_pattern[3][26][1] = 1;	M_pattern[3][26][2] = 1;
	M_pattern[3][26][3] = 1;	M_pattern[3][26][4] = 1;	M_pattern[3][26][5] = 1;
	M_pattern[3][26][6] = 0;	M_pattern[3][26][7] = 1;	M_pattern[3][26][8] = 0;


	M_pattern[3][27][0] = 1;	M_pattern[3][27][1] = 1;	M_pattern[3][27][2] = 1;
	M_pattern[3][27][3] = 1;	M_pattern[3][27][4] = 1;	M_pattern[3][27][5] = 1;
	M_pattern[3][27][6] = 0;	M_pattern[3][27][7] = 1;	M_pattern[3][27][8] = 1;


	M_pattern[3][28][0] = 1;	M_pattern[3][28][1] = 1;	M_pattern[3][28][2] = 1;
	M_pattern[3][28][3] = 1;	M_pattern[3][28][4] = 1;	M_pattern[3][28][5] = 1;
	M_pattern[3][28][6] = 1;	M_pattern[3][28][7] = 0;	M_pattern[3][28][8] = 0;


	M_pattern[3][29][0] = 1;	M_pattern[3][29][1] = 1;	M_pattern[3][29][2] = 1;
	M_pattern[3][29][3] = 1;	M_pattern[3][29][4] = 1;	M_pattern[3][29][5] = 1;
	M_pattern[3][29][6] = 1;	M_pattern[3][29][7] = 0;	M_pattern[3][29][8] = 1;


	M_pattern[3][30][0] = 1;	M_pattern[3][30][1] = 1;	M_pattern[3][30][2] = 1;
	M_pattern[3][30][3] = 1;	M_pattern[3][30][4] = 1;	M_pattern[3][30][5] = 1;
	M_pattern[3][30][6] = 1;	M_pattern[3][30][7] = 1;	M_pattern[3][30][8] = 0;


	M_pattern[3][31][0] = 1;	M_pattern[3][31][1] = 1;	M_pattern[3][31][2] = 1;
	M_pattern[3][31][3] = 1;	M_pattern[3][31][4] = 1;	M_pattern[3][31][5] = 1;
	M_pattern[3][31][6] = 1;	M_pattern[3][31][7] = 1;	M_pattern[3][31][8] = 1;


	M_pattern[3][32][0] = 0;	M_pattern[3][32][1] = 0;	M_pattern[3][32][2] = 0;
	M_pattern[3][32][3] = 0;	M_pattern[3][32][4] = 1;	M_pattern[3][32][5] = 1;
	M_pattern[3][32][6] = 0;	M_pattern[3][32][7] = 1;	M_pattern[3][32][8] = 1;


	M_pattern[3][33][0] = 0;	M_pattern[3][33][1] = 0;	M_pattern[3][33][2] = 0;
	M_pattern[3][33][3] = 0;	M_pattern[3][33][4] = 1;	M_pattern[3][33][5] = 1;
	M_pattern[3][33][6] = 1;	M_pattern[3][33][7] = 1;	M_pattern[3][33][8] = 1;


	M_pattern[3][34][0] = 0;	M_pattern[3][34][1] = 0;	M_pattern[3][34][2] = 0;
	M_pattern[3][34][3] = 1;	M_pattern[3][34][4] = 1;	M_pattern[3][34][5] = 1;
	M_pattern[3][34][6] = 0;	M_pattern[3][34][7] = 1;	M_pattern[3][34][8] = 1;


	M_pattern[3][35][0] = 0;	M_pattern[3][35][1] = 0;	M_pattern[3][35][2] = 0;
	M_pattern[3][35][3] = 1;	M_pattern[3][35][4] = 1;	M_pattern[3][35][5] = 1;
	M_pattern[3][35][6] = 1;	M_pattern[3][35][7] = 1;	M_pattern[3][35][8] = 1;


	M_pattern[3][36][0] = 0;	M_pattern[3][36][1] = 0;	M_pattern[3][36][2] = 1;
	M_pattern[3][36][3] = 0;	M_pattern[3][36][4] = 1;	M_pattern[3][36][5] = 1;
	M_pattern[3][36][6] = 0;	M_pattern[3][36][7] = 1;	M_pattern[3][36][8] = 1;


	M_pattern[3][37][0] = 0;	M_pattern[3][37][1] = 0;	M_pattern[3][37][2] = 1;
	M_pattern[3][37][3] = 0;	M_pattern[3][37][4] = 1;	M_pattern[3][37][5] = 1;
	M_pattern[3][37][6] = 1;	M_pattern[3][37][7] = 1;	M_pattern[3][37][8] = 1;


	M_pattern[3][38][0] = 0;	M_pattern[3][38][1] = 0;	M_pattern[3][38][2] = 1;
	M_pattern[3][38][3] = 1;	M_pattern[3][38][4] = 1;	M_pattern[3][38][5] = 1;
	M_pattern[3][38][6] = 0;	M_pattern[3][38][7] = 1;	M_pattern[3][38][8] = 1;


	M_pattern[3][39][0] = 0;	M_pattern[3][39][1] = 0;	M_pattern[3][39][2] = 1;
	M_pattern[3][39][3] = 1;	M_pattern[3][39][4] = 1;	M_pattern[3][39][5] = 1;
	M_pattern[3][39][6] = 1;	M_pattern[3][39][7] = 1;	M_pattern[3][39][8] = 1;


	M_pattern[3][40][0] = 0;	M_pattern[3][40][1] = 1;	M_pattern[3][40][2] = 0;
	M_pattern[3][40][3] = 0;	M_pattern[3][40][4] = 1;	M_pattern[3][40][5] = 1;
	M_pattern[3][40][6] = 0;	M_pattern[3][40][7] = 1;	M_pattern[3][40][8] = 1;


	M_pattern[3][41][0] = 0;	M_pattern[3][41][1] = 1;	M_pattern[3][41][2] = 0;
	M_pattern[3][41][3] = 0;	M_pattern[3][41][4] = 1;	M_pattern[3][41][5] = 1;
	M_pattern[3][41][6] = 1;	M_pattern[3][41][7] = 1;	M_pattern[3][41][8] = 1;


	M_pattern[3][42][0] = 0;	M_pattern[3][42][1] = 1;	M_pattern[3][42][2] = 0;
	M_pattern[3][42][3] = 1;	M_pattern[3][42][4] = 1;	M_pattern[3][42][5] = 1;
	M_pattern[3][42][6] = 0;	M_pattern[3][42][7] = 1;	M_pattern[3][42][8] = 1;


	M_pattern[3][43][0] = 0;	M_pattern[3][43][1] = 1;	M_pattern[3][43][2] = 0;
	M_pattern[3][43][3] = 1;	M_pattern[3][43][4] = 1;	M_pattern[3][43][5] = 1;
	M_pattern[3][43][6] = 1;	M_pattern[3][43][7] = 1;	M_pattern[3][43][8] = 1;


	M_pattern[3][44][0] = 0;	M_pattern[3][44][1] = 1;	M_pattern[3][44][2] = 1;
	M_pattern[3][44][3] = 0;	M_pattern[3][44][4] = 1;	M_pattern[3][44][5] = 1;
	M_pattern[3][44][6] = 0;	M_pattern[3][44][7] = 1;	M_pattern[3][44][8] = 1;


	M_pattern[3][45][0] = 0;	M_pattern[3][45][1] = 1;	M_pattern[3][45][2] = 1;
	M_pattern[3][45][3] = 0;	M_pattern[3][45][4] = 1;	M_pattern[3][45][5] = 1;
	M_pattern[3][45][6] = 1;	M_pattern[3][45][7] = 1;	M_pattern[3][45][8] = 1;


	M_pattern[3][46][0] = 0;	M_pattern[3][46][1] = 1;	M_pattern[3][46][2] = 1;
	M_pattern[3][46][3] = 1;	M_pattern[3][46][4] = 1;	M_pattern[3][46][5] = 1;
	M_pattern[3][46][6] = 0;	M_pattern[3][46][7] = 1;	M_pattern[3][46][8] = 1;


	M_pattern[3][47][0] = 0;	M_pattern[3][47][1] = 1;	M_pattern[3][47][2] = 1;
	M_pattern[3][47][3] = 1;	M_pattern[3][47][4] = 1;	M_pattern[3][47][5] = 1;
	M_pattern[3][47][6] = 1;	M_pattern[3][47][7] = 1;	M_pattern[3][47][8] = 1;


	M_pattern[3][48][0] = 1;	M_pattern[3][48][1] = 0;	M_pattern[3][48][2] = 0;
	M_pattern[3][48][3] = 0;	M_pattern[3][48][4] = 1;	M_pattern[3][48][5] = 1;
	M_pattern[3][48][6] = 0;	M_pattern[3][48][7] = 1;	M_pattern[3][48][8] = 1;


	M_pattern[3][49][0] = 1;	M_pattern[3][49][1] = 0;	M_pattern[3][49][2] = 0;
	M_pattern[3][49][3] = 0;	M_pattern[3][49][4] = 1;	M_pattern[3][49][5] = 1;
	M_pattern[3][49][6] = 1;	M_pattern[3][49][7] = 1;	M_pattern[3][49][8] = 1;


	M_pattern[3][50][0] = 1;	M_pattern[3][50][1] = 0;	M_pattern[3][50][2] = 0;
	M_pattern[3][50][3] = 1;	M_pattern[3][50][4] = 1;	M_pattern[3][50][5] = 1;
	M_pattern[3][50][6] = 0;	M_pattern[3][50][7] = 1;	M_pattern[3][50][8] = 1;


	M_pattern[3][51][0] = 1;	M_pattern[3][51][1] = 0;	M_pattern[3][51][2] = 0;
	M_pattern[3][51][3] = 1;	M_pattern[3][51][4] = 1;	M_pattern[3][51][5] = 1;
	M_pattern[3][51][6] = 1;	M_pattern[3][51][7] = 1;	M_pattern[3][51][8] = 1;


	M_pattern[3][52][0] = 1;	M_pattern[3][52][1] = 0;	M_pattern[3][52][2] = 1;
	M_pattern[3][52][3] = 0;	M_pattern[3][52][4] = 1;	M_pattern[3][52][5] = 1;
	M_pattern[3][52][6] = 0;	M_pattern[3][52][7] = 1;	M_pattern[3][52][8] = 1;


	M_pattern[3][53][0] = 1;	M_pattern[3][53][1] = 0;	M_pattern[3][53][2] = 1;
	M_pattern[3][53][3] = 0;	M_pattern[3][53][4] = 1;	M_pattern[3][53][5] = 1;
	M_pattern[3][53][6] = 1;	M_pattern[3][53][7] = 1;	M_pattern[3][53][8] = 1;


	M_pattern[3][54][0] = 1;	M_pattern[3][54][1] = 0;	M_pattern[3][54][2] = 1;
	M_pattern[3][54][3] = 1;	M_pattern[3][54][4] = 1;	M_pattern[3][54][5] = 1;
	M_pattern[3][54][6] = 0;	M_pattern[3][54][7] = 1;	M_pattern[3][54][8] = 1;


	M_pattern[3][55][0] = 1;	M_pattern[3][55][1] = 0;	M_pattern[3][55][2] = 1;
	M_pattern[3][55][3] = 1;	M_pattern[3][55][4] = 1;	M_pattern[3][55][5] = 1;
	M_pattern[3][55][6] = 1;	M_pattern[3][55][7] = 1;	M_pattern[3][55][8] = 1;


	M_pattern[3][56][0] = 1;	M_pattern[3][56][1] = 1;	M_pattern[3][56][2] = 0;
	M_pattern[3][56][3] = 0;	M_pattern[3][56][4] = 1;	M_pattern[3][56][5] = 1;
	M_pattern[3][56][6] = 0;	M_pattern[3][56][7] = 1;	M_pattern[3][56][8] = 1;


	M_pattern[3][57][0] = 1;	M_pattern[3][57][1] = 1;	M_pattern[3][57][2] = 0;
	M_pattern[3][57][3] = 0;	M_pattern[3][57][4] = 1;	M_pattern[3][57][5] = 1;
	M_pattern[3][57][6] = 1;	M_pattern[3][57][7] = 1;	M_pattern[3][57][8] = 1;


	M_pattern[3][58][0] = 1;	M_pattern[3][58][1] = 1;	M_pattern[3][58][2] = 0;
	M_pattern[3][58][3] = 1;	M_pattern[3][58][4] = 1;	M_pattern[3][58][5] = 1;
	M_pattern[3][58][6] = 0;	M_pattern[3][58][7] = 1;	M_pattern[3][58][8] = 1;


	M_pattern[3][59][0] = 1;	M_pattern[3][59][1] = 1;	M_pattern[3][59][2] = 0;
	M_pattern[3][59][3] = 1;	M_pattern[3][59][4] = 1;	M_pattern[3][59][5] = 1;
	M_pattern[3][59][6] = 1;	M_pattern[3][59][7] = 1;	M_pattern[3][59][8] = 1;


	M_pattern[3][60][0] = 1;	M_pattern[3][60][1] = 1;	M_pattern[3][60][2] = 1;
	M_pattern[3][60][3] = 0;	M_pattern[3][60][4] = 1;	M_pattern[3][60][5] = 1;
	M_pattern[3][60][6] = 0;	M_pattern[3][60][7] = 1;	M_pattern[3][60][8] = 1;


	M_pattern[3][61][0] = 1;	M_pattern[3][61][1] = 1;	M_pattern[3][61][2] = 1;
	M_pattern[3][61][3] = 0;	M_pattern[3][61][4] = 1;	M_pattern[3][61][5] = 1;
	M_pattern[3][61][6] = 1;	M_pattern[3][61][7] = 1;	M_pattern[3][61][8] = 1;


	M_pattern[3][62][0] = 1;	M_pattern[3][62][1] = 1;	M_pattern[3][62][2] = 1;
	M_pattern[3][62][3] = 1;	M_pattern[3][62][4] = 1;	M_pattern[3][62][5] = 1;
	M_pattern[3][62][6] = 0;	M_pattern[3][62][7] = 1;	M_pattern[3][62][8] = 1;


	M_pattern[3][63][0] = 1;	M_pattern[3][63][1] = 1;	M_pattern[3][63][2] = 1;
	M_pattern[3][63][3] = 1;	M_pattern[3][63][4] = 1;	M_pattern[3][63][5] = 1;
	M_pattern[3][63][6] = 1;	M_pattern[3][63][7] = 1;	M_pattern[3][63][8] = 1;





	M_pattern[4][0][0] = 0;	M_pattern[4][0][1] = 1;	M_pattern[4][0][2] = 0;
	M_pattern[4][0][3] = 1;	M_pattern[4][0][4] = 1;	M_pattern[4][0][5] = 1;
	M_pattern[4][0][6] = 0;	M_pattern[4][0][7] = 0;	M_pattern[4][0][8] = 0;


	M_pattern[4][1][0] = 0;	M_pattern[4][1][1] = 1;	M_pattern[4][1][2] = 0;
	M_pattern[4][1][3] = 1;	M_pattern[4][1][4] = 1;	M_pattern[4][1][5] = 1;
	M_pattern[4][1][6] = 0;	M_pattern[4][1][7] = 0;	M_pattern[4][1][8] = 1;


	M_pattern[4][2][0] = 0;	M_pattern[4][2][1] = 1;	M_pattern[4][2][2] = 0;
	M_pattern[4][2][3] = 1;	M_pattern[4][2][4] = 1;	M_pattern[4][2][5] = 1;
	M_pattern[4][2][6] = 0;	M_pattern[4][2][7] = 1;	M_pattern[4][2][8] = 0;


	M_pattern[4][3][0] = 0;	M_pattern[4][3][1] = 1;	M_pattern[4][3][2] = 0;
	M_pattern[4][3][3] = 1;	M_pattern[4][3][4] = 1;	M_pattern[4][3][5] = 1;
	M_pattern[4][3][6] = 0;	M_pattern[4][3][7] = 1;	M_pattern[4][3][8] = 1;


	M_pattern[4][4][0] = 0;	M_pattern[4][4][1] = 1;	M_pattern[4][4][2] = 0;
	M_pattern[4][4][3] = 1;	M_pattern[4][4][4] = 1;	M_pattern[4][4][5] = 1;
	M_pattern[4][4][6] = 1;	M_pattern[4][4][7] = 0;	M_pattern[4][4][8] = 0;


	M_pattern[4][5][0] = 0;	M_pattern[4][5][1] = 1;	M_pattern[4][5][2] = 0;
	M_pattern[4][5][3] = 1;	M_pattern[4][5][4] = 1;	M_pattern[4][5][5] = 1;
	M_pattern[4][5][6] = 1;	M_pattern[4][5][7] = 0;	M_pattern[4][5][8] = 1;


	M_pattern[4][6][0] = 0;	M_pattern[4][6][1] = 1;	M_pattern[4][6][2] = 0;
	M_pattern[4][6][3] = 1;	M_pattern[4][6][4] = 1;	M_pattern[4][6][5] = 1;
	M_pattern[4][6][6] = 1;	M_pattern[4][6][7] = 1;	M_pattern[4][6][8] = 0;


	M_pattern[4][7][0] = 0;	M_pattern[4][7][1] = 1;	M_pattern[4][7][2] = 0;
	M_pattern[4][7][3] = 1;	M_pattern[4][7][4] = 1;	M_pattern[4][7][5] = 1;
	M_pattern[4][7][6] = 1;	M_pattern[4][7][7] = 1;	M_pattern[4][7][8] = 1;


	M_pattern[4][8][0] = 0;	M_pattern[4][8][1] = 1;	M_pattern[4][8][2] = 1;
	M_pattern[4][8][3] = 1;	M_pattern[4][8][4] = 1;	M_pattern[4][8][5] = 1;
	M_pattern[4][8][6] = 0;	M_pattern[4][8][7] = 0;	M_pattern[4][8][8] = 0;


	M_pattern[4][9][0] = 0;	M_pattern[4][9][1] = 1;	M_pattern[4][9][2] = 1;
	M_pattern[4][9][3] = 1;	M_pattern[4][9][4] = 1;	M_pattern[4][9][5] = 1;
	M_pattern[4][9][6] = 0;	M_pattern[4][9][7] = 0;	M_pattern[4][9][8] = 1;


	M_pattern[4][10][0] = 0;	M_pattern[4][10][1] = 1;	M_pattern[4][10][2] = 1;
	M_pattern[4][10][3] = 1;	M_pattern[4][10][4] = 1;	M_pattern[4][10][5] = 1;
	M_pattern[4][10][6] = 0;	M_pattern[4][10][7] = 1;	M_pattern[4][10][8] = 0;


	M_pattern[4][11][0] = 0;	M_pattern[4][11][1] = 1;	M_pattern[4][11][2] = 1;
	M_pattern[4][11][3] = 1;	M_pattern[4][11][4] = 1;	M_pattern[4][11][5] = 1;
	M_pattern[4][11][6] = 0;	M_pattern[4][11][7] = 1;	M_pattern[4][11][8] = 1;


	M_pattern[4][12][0] = 0;	M_pattern[4][12][1] = 1;	M_pattern[4][12][2] = 1;
	M_pattern[4][12][3] = 1;	M_pattern[4][12][4] = 1;	M_pattern[4][12][5] = 1;
	M_pattern[4][12][6] = 1;	M_pattern[4][12][7] = 0;	M_pattern[4][12][8] = 0;


	M_pattern[4][13][0] = 0;	M_pattern[4][13][1] = 1;	M_pattern[4][13][2] = 1;
	M_pattern[4][13][3] = 1;	M_pattern[4][13][4] = 1;	M_pattern[4][13][5] = 1;
	M_pattern[4][13][6] = 1;	M_pattern[4][13][7] = 0;	M_pattern[4][13][8] = 1;


	M_pattern[4][14][0] = 0;	M_pattern[4][14][1] = 1;	M_pattern[4][14][2] = 1;
	M_pattern[4][14][3] = 1;	M_pattern[4][14][4] = 1;	M_pattern[4][14][5] = 1;
	M_pattern[4][14][6] = 1;	M_pattern[4][14][7] = 1;	M_pattern[4][14][8] = 0;


	M_pattern[4][15][0] = 0;	M_pattern[4][15][1] = 1;	M_pattern[4][15][2] = 1;
	M_pattern[4][15][3] = 1;	M_pattern[4][15][4] = 1;	M_pattern[4][15][5] = 1;
	M_pattern[4][15][6] = 1;	M_pattern[4][15][7] = 1;	M_pattern[4][15][8] = 1;


	M_pattern[4][16][0] = 1;	M_pattern[4][16][1] = 1;	M_pattern[4][16][2] = 0;
	M_pattern[4][16][3] = 1;	M_pattern[4][16][4] = 1;	M_pattern[4][16][5] = 1;
	M_pattern[4][16][6] = 0;	M_pattern[4][16][7] = 0;	M_pattern[4][16][8] = 0;


	M_pattern[4][17][0] = 1;	M_pattern[4][17][1] = 1;	M_pattern[4][17][2] = 0;
	M_pattern[4][17][3] = 1;	M_pattern[4][17][4] = 1;	M_pattern[4][17][5] = 1;
	M_pattern[4][17][6] = 0;	M_pattern[4][17][7] = 0;	M_pattern[4][17][8] = 1;


	M_pattern[4][18][0] = 1;	M_pattern[4][18][1] = 1;	M_pattern[4][18][2] = 0;
	M_pattern[4][18][3] = 1;	M_pattern[4][18][4] = 1;	M_pattern[4][18][5] = 1;
	M_pattern[4][18][6] = 0;	M_pattern[4][18][7] = 1;	M_pattern[4][18][8] = 0;


	M_pattern[4][19][0] = 1;	M_pattern[4][19][1] = 1;	M_pattern[4][19][2] = 0;
	M_pattern[4][19][3] = 1;	M_pattern[4][19][4] = 1;	M_pattern[4][19][5] = 1;
	M_pattern[4][19][6] = 0;	M_pattern[4][19][7] = 1;	M_pattern[4][19][8] = 1;


	M_pattern[4][20][0] = 1;	M_pattern[4][20][1] = 1;	M_pattern[4][20][2] = 0;
	M_pattern[4][20][3] = 1;	M_pattern[4][20][4] = 1;	M_pattern[4][20][5] = 1;
	M_pattern[4][20][6] = 1;	M_pattern[4][20][7] = 0;	M_pattern[4][20][8] = 0;


	M_pattern[4][21][0] = 1;	M_pattern[4][21][1] = 1;	M_pattern[4][21][2] = 0;
	M_pattern[4][21][3] = 1;	M_pattern[4][21][4] = 1;	M_pattern[4][21][5] = 1;
	M_pattern[4][21][6] = 1;	M_pattern[4][21][7] = 0;	M_pattern[4][21][8] = 1;


	M_pattern[4][22][0] = 1;	M_pattern[4][22][1] = 1;	M_pattern[4][22][2] = 0;
	M_pattern[4][22][3] = 1;	M_pattern[4][22][4] = 1;	M_pattern[4][22][5] = 1;
	M_pattern[4][22][6] = 1;	M_pattern[4][22][7] = 1;	M_pattern[4][22][8] = 0;


	M_pattern[4][23][0] = 1;	M_pattern[4][23][1] = 1;	M_pattern[4][23][2] = 0;
	M_pattern[4][23][3] = 1;	M_pattern[4][23][4] = 1;	M_pattern[4][23][5] = 1;
	M_pattern[4][23][6] = 1;	M_pattern[4][23][7] = 1;	M_pattern[4][23][8] = 1;


	M_pattern[4][24][0] = 1;	M_pattern[4][24][1] = 1;	M_pattern[4][24][2] = 1;
	M_pattern[4][24][3] = 1;	M_pattern[4][24][4] = 1;	M_pattern[4][24][5] = 1;
	M_pattern[4][24][6] = 0;	M_pattern[4][24][7] = 0;	M_pattern[4][24][8] = 0;


	M_pattern[4][25][0] = 1;	M_pattern[4][25][1] = 1;	M_pattern[4][25][2] = 1;
	M_pattern[4][25][3] = 1;	M_pattern[4][25][4] = 1;	M_pattern[4][25][5] = 1;
	M_pattern[4][25][6] = 0;	M_pattern[4][25][7] = 0;	M_pattern[4][25][8] = 1;


	M_pattern[4][26][0] = 1;	M_pattern[4][26][1] = 1;	M_pattern[4][26][2] = 1;
	M_pattern[4][26][3] = 1;	M_pattern[4][26][4] = 1;	M_pattern[4][26][5] = 1;
	M_pattern[4][26][6] = 0;	M_pattern[4][26][7] = 1;	M_pattern[4][26][8] = 0;


	M_pattern[4][27][0] = 1;	M_pattern[4][27][1] = 1;	M_pattern[4][27][2] = 1;
	M_pattern[4][27][3] = 1;	M_pattern[4][27][4] = 1;	M_pattern[4][27][5] = 1;
	M_pattern[4][27][6] = 0;	M_pattern[4][27][7] = 1;	M_pattern[4][27][8] = 1;


	M_pattern[4][28][0] = 1;	M_pattern[4][28][1] = 1;	M_pattern[4][28][2] = 1;
	M_pattern[4][28][3] = 1;	M_pattern[4][28][4] = 1;	M_pattern[4][28][5] = 1;
	M_pattern[4][28][6] = 1;	M_pattern[4][28][7] = 0;	M_pattern[4][28][8] = 0;


	M_pattern[4][29][0] = 1;	M_pattern[4][29][1] = 1;	M_pattern[4][29][2] = 1;
	M_pattern[4][29][3] = 1;	M_pattern[4][29][4] = 1;	M_pattern[4][29][5] = 1;
	M_pattern[4][29][6] = 1;	M_pattern[4][29][7] = 0;	M_pattern[4][29][8] = 1;


	M_pattern[4][30][0] = 1;	M_pattern[4][30][1] = 1;	M_pattern[4][30][2] = 1;
	M_pattern[4][30][3] = 1;	M_pattern[4][30][4] = 1;	M_pattern[4][30][5] = 1;
	M_pattern[4][30][6] = 1;	M_pattern[4][30][7] = 1;	M_pattern[4][30][8] = 0;


	M_pattern[4][31][0] = 1;	M_pattern[4][31][1] = 1;	M_pattern[4][31][2] = 1;
	M_pattern[4][31][3] = 1;	M_pattern[4][31][4] = 1;	M_pattern[4][31][5] = 1;
	M_pattern[4][31][6] = 1;	M_pattern[4][31][7] = 1;	M_pattern[4][31][8] = 1;


	M_pattern[4][32][0] = 0;	M_pattern[4][32][1] = 1;	M_pattern[4][32][2] = 0;
	M_pattern[4][32][3] = 1;	M_pattern[4][32][4] = 1;	M_pattern[4][32][5] = 0;
	M_pattern[4][32][6] = 0;	M_pattern[4][32][7] = 1;	M_pattern[4][32][8] = 0;


	M_pattern[4][33][0] = 0;	M_pattern[4][33][1] = 1;	M_pattern[4][33][2] = 0;
	M_pattern[4][33][3] = 1;	M_pattern[4][33][4] = 1;	M_pattern[4][33][5] = 0;
	M_pattern[4][33][6] = 0;	M_pattern[4][33][7] = 1;	M_pattern[4][33][8] = 1;


	M_pattern[4][34][0] = 0;	M_pattern[4][34][1] = 1;	M_pattern[4][34][2] = 0;
	M_pattern[4][34][3] = 1;	M_pattern[4][34][4] = 1;	M_pattern[4][34][5] = 1;
	M_pattern[4][34][6] = 0;	M_pattern[4][34][7] = 1;	M_pattern[4][34][8] = 0;


	M_pattern[4][35][0] = 0;	M_pattern[4][35][1] = 1;	M_pattern[4][35][2] = 0;
	M_pattern[4][35][3] = 1;	M_pattern[4][35][4] = 1;	M_pattern[4][35][5] = 1;
	M_pattern[4][35][6] = 0;	M_pattern[4][35][7] = 1;	M_pattern[4][35][8] = 1;


	M_pattern[4][36][0] = 0;	M_pattern[4][36][1] = 1;	M_pattern[4][36][2] = 0;
	M_pattern[4][36][3] = 1;	M_pattern[4][36][4] = 1;	M_pattern[4][36][5] = 0;
	M_pattern[4][36][6] = 1;	M_pattern[4][36][7] = 1;	M_pattern[4][36][8] = 0;


	M_pattern[4][37][0] = 0;	M_pattern[4][37][1] = 1;	M_pattern[4][37][2] = 0;
	M_pattern[4][37][3] = 1;	M_pattern[4][37][4] = 1;	M_pattern[4][37][5] = 0;
	M_pattern[4][37][6] = 1;	M_pattern[4][37][7] = 1;	M_pattern[4][37][8] = 1;


	M_pattern[4][38][0] = 0;	M_pattern[4][38][1] = 1;	M_pattern[4][38][2] = 0;
	M_pattern[4][38][3] = 1;	M_pattern[4][38][4] = 1;	M_pattern[4][38][5] = 1;
	M_pattern[4][38][6] = 1;	M_pattern[4][38][7] = 1;	M_pattern[4][38][8] = 0;


	M_pattern[4][39][0] = 0;	M_pattern[4][39][1] = 1;	M_pattern[4][39][2] = 0;
	M_pattern[4][39][3] = 1;	M_pattern[4][39][4] = 1;	M_pattern[4][39][5] = 1;
	M_pattern[4][39][6] = 1;	M_pattern[4][39][7] = 1;	M_pattern[4][39][8] = 1;


	M_pattern[4][40][0] = 0;	M_pattern[4][40][1] = 1;	M_pattern[4][40][2] = 1;
	M_pattern[4][40][3] = 1;	M_pattern[4][40][4] = 1;	M_pattern[4][40][5] = 0;
	M_pattern[4][40][6] = 0;	M_pattern[4][40][7] = 1;	M_pattern[4][40][8] = 0;


	M_pattern[4][41][0] = 0;	M_pattern[4][41][1] = 1;	M_pattern[4][41][2] = 1;
	M_pattern[4][41][3] = 1;	M_pattern[4][41][4] = 1;	M_pattern[4][41][5] = 0;
	M_pattern[4][41][6] = 0;	M_pattern[4][41][7] = 1;	M_pattern[4][41][8] = 1;


	M_pattern[4][42][0] = 0;	M_pattern[4][42][1] = 1;	M_pattern[4][42][2] = 1;
	M_pattern[4][42][3] = 1;	M_pattern[4][42][4] = 1;	M_pattern[4][42][5] = 1;
	M_pattern[4][42][6] = 0;	M_pattern[4][42][7] = 1;	M_pattern[4][42][8] = 0;


	M_pattern[4][43][0] = 0;	M_pattern[4][43][1] = 1;	M_pattern[4][43][2] = 1;
	M_pattern[4][43][3] = 1;	M_pattern[4][43][4] = 1;	M_pattern[4][43][5] = 1;
	M_pattern[4][43][6] = 0;	M_pattern[4][43][7] = 1;	M_pattern[4][43][8] = 1;


	M_pattern[4][44][0] = 0;	M_pattern[4][44][1] = 1;	M_pattern[4][44][2] = 1;
	M_pattern[4][44][3] = 1;	M_pattern[4][44][4] = 1;	M_pattern[4][44][5] = 0;
	M_pattern[4][44][6] = 1;	M_pattern[4][44][7] = 1;	M_pattern[4][44][8] = 0;


	M_pattern[4][45][0] = 0;	M_pattern[4][45][1] = 1;	M_pattern[4][45][2] = 1;
	M_pattern[4][45][3] = 1;	M_pattern[4][45][4] = 1;	M_pattern[4][45][5] = 0;
	M_pattern[4][45][6] = 1;	M_pattern[4][45][7] = 1;	M_pattern[4][45][8] = 1;


	M_pattern[4][46][0] = 0;	M_pattern[4][46][1] = 1;	M_pattern[4][46][2] = 1;
	M_pattern[4][46][3] = 1;	M_pattern[4][46][4] = 1;	M_pattern[4][46][5] = 1;
	M_pattern[4][46][6] = 1;	M_pattern[4][46][7] = 1;	M_pattern[4][46][8] = 0;


	M_pattern[4][47][0] = 0;	M_pattern[4][47][1] = 1;	M_pattern[4][47][2] = 1;
	M_pattern[4][47][3] = 1;	M_pattern[4][47][4] = 1;	M_pattern[4][47][5] = 1;
	M_pattern[4][47][6] = 1;	M_pattern[4][47][7] = 1;	M_pattern[4][47][8] = 1;


	M_pattern[4][48][0] = 1;	M_pattern[4][48][1] = 1;	M_pattern[4][48][2] = 0;
	M_pattern[4][48][3] = 1;	M_pattern[4][48][4] = 1;	M_pattern[4][48][5] = 0;
	M_pattern[4][48][6] = 0;	M_pattern[4][48][7] = 1;	M_pattern[4][48][8] = 0;


	M_pattern[4][49][0] = 1;	M_pattern[4][49][1] = 1;	M_pattern[4][49][2] = 0;
	M_pattern[4][49][3] = 1;	M_pattern[4][49][4] = 1;	M_pattern[4][49][5] = 0;
	M_pattern[4][49][6] = 0;	M_pattern[4][49][7] = 1;	M_pattern[4][49][8] = 1;


	M_pattern[4][50][0] = 1;	M_pattern[4][50][1] = 1;	M_pattern[4][50][2] = 0;
	M_pattern[4][50][3] = 1;	M_pattern[4][50][4] = 1;	M_pattern[4][50][5] = 1;
	M_pattern[4][50][6] = 0;	M_pattern[4][50][7] = 1;	M_pattern[4][50][8] = 0;


	M_pattern[4][51][0] = 1;	M_pattern[4][51][1] = 1;	M_pattern[4][51][2] = 0;
	M_pattern[4][51][3] = 1;	M_pattern[4][51][4] = 1;	M_pattern[4][51][5] = 1;
	M_pattern[4][51][6] = 0;	M_pattern[4][51][7] = 1;	M_pattern[4][51][8] = 1;


	M_pattern[4][52][0] = 1;	M_pattern[4][52][1] = 1;	M_pattern[4][52][2] = 0;
	M_pattern[4][52][3] = 1;	M_pattern[4][52][4] = 1;	M_pattern[4][52][5] = 0;
	M_pattern[4][52][6] = 1;	M_pattern[4][52][7] = 1;	M_pattern[4][52][8] = 0;


	M_pattern[4][53][0] = 1;	M_pattern[4][53][1] = 1;	M_pattern[4][53][2] = 0;
	M_pattern[4][53][3] = 1;	M_pattern[4][53][4] = 1;	M_pattern[4][53][5] = 0;
	M_pattern[4][53][6] = 1;	M_pattern[4][53][7] = 1;	M_pattern[4][53][8] = 1;


	M_pattern[4][54][0] = 1;	M_pattern[4][54][1] = 1;	M_pattern[4][54][2] = 0;
	M_pattern[4][54][3] = 1;	M_pattern[4][54][4] = 1;	M_pattern[4][54][5] = 1;
	M_pattern[4][54][6] = 1;	M_pattern[4][54][7] = 1;	M_pattern[4][54][8] = 0;


	M_pattern[4][55][0] = 1;	M_pattern[4][55][1] = 1;	M_pattern[4][55][2] = 0;
	M_pattern[4][55][3] = 1;	M_pattern[4][55][4] = 1;	M_pattern[4][55][5] = 1;
	M_pattern[4][55][6] = 1;	M_pattern[4][55][7] = 1;	M_pattern[4][55][8] = 1;


	M_pattern[4][56][0] = 1;	M_pattern[4][56][1] = 1;	M_pattern[4][56][2] = 1;
	M_pattern[4][56][3] = 1;	M_pattern[4][56][4] = 1;	M_pattern[4][56][5] = 0;
	M_pattern[4][56][6] = 0;	M_pattern[4][56][7] = 1;	M_pattern[4][56][8] = 0;


	M_pattern[4][57][0] = 1;	M_pattern[4][57][1] = 1;	M_pattern[4][57][2] = 1;
	M_pattern[4][57][3] = 1;	M_pattern[4][57][4] = 1;	M_pattern[4][57][5] = 0;
	M_pattern[4][57][6] = 0;	M_pattern[4][57][7] = 1;	M_pattern[4][57][8] = 1;


	M_pattern[4][58][0] = 1;	M_pattern[4][58][1] = 1;	M_pattern[4][58][2] = 1;
	M_pattern[4][58][3] = 1;	M_pattern[4][58][4] = 1;	M_pattern[4][58][5] = 1;
	M_pattern[4][58][6] = 0;	M_pattern[4][58][7] = 1;	M_pattern[4][58][8] = 0;


	M_pattern[4][59][0] = 1;	M_pattern[4][59][1] = 1;	M_pattern[4][59][2] = 1;
	M_pattern[4][59][3] = 1;	M_pattern[4][59][4] = 1;	M_pattern[4][59][5] = 1;
	M_pattern[4][59][6] = 0;	M_pattern[4][59][7] = 1;	M_pattern[4][59][8] = 1;


	M_pattern[4][60][0] = 1;	M_pattern[4][60][1] = 1;	M_pattern[4][60][2] = 1;
	M_pattern[4][60][3] = 1;	M_pattern[4][60][4] = 1;	M_pattern[4][60][5] = 0;
	M_pattern[4][60][6] = 1;	M_pattern[4][60][7] = 1;	M_pattern[4][60][8] = 0;


	M_pattern[4][61][0] = 1;	M_pattern[4][61][1] = 1;	M_pattern[4][61][2] = 1;
	M_pattern[4][61][3] = 1;	M_pattern[4][61][4] = 1;	M_pattern[4][61][5] = 0;
	M_pattern[4][61][6] = 1;	M_pattern[4][61][7] = 1;	M_pattern[4][61][8] = 1;


	M_pattern[4][62][0] = 1;	M_pattern[4][62][1] = 1;	M_pattern[4][62][2] = 1;
	M_pattern[4][62][3] = 1;	M_pattern[4][62][4] = 1;	M_pattern[4][62][5] = 1;
	M_pattern[4][62][6] = 1;	M_pattern[4][62][7] = 1;	M_pattern[4][62][8] = 0;


	M_pattern[4][63][0] = 1;	M_pattern[4][63][1] = 1;	M_pattern[4][63][2] = 1;
	M_pattern[4][63][3] = 1;	M_pattern[4][63][4] = 1;	M_pattern[4][63][5] = 1;
	M_pattern[4][63][6] = 1;	M_pattern[4][63][7] = 1;	M_pattern[4][63][8] = 1;


	M_pattern[4][64][0] = 0;	M_pattern[4][64][1] = 0;	M_pattern[4][64][2] = 0;
	M_pattern[4][64][3] = 1;	M_pattern[4][64][4] = 1;	M_pattern[4][64][5] = 1;
	M_pattern[4][64][6] = 0;	M_pattern[4][64][7] = 1;	M_pattern[4][64][8] = 0;


	M_pattern[4][65][0] = 0;	M_pattern[4][65][1] = 0;	M_pattern[4][65][2] = 0;
	M_pattern[4][65][3] = 1;	M_pattern[4][65][4] = 1;	M_pattern[4][65][5] = 1;
	M_pattern[4][65][6] = 0;	M_pattern[4][65][7] = 1;	M_pattern[4][65][8] = 1;


	M_pattern[4][66][0] = 0;	M_pattern[4][66][1] = 0;	M_pattern[4][66][2] = 0;
	M_pattern[4][66][3] = 1;	M_pattern[4][66][4] = 1;	M_pattern[4][66][5] = 1;
	M_pattern[4][66][6] = 1;	M_pattern[4][66][7] = 1;	M_pattern[4][66][8] = 0;


	M_pattern[4][67][0] = 0;	M_pattern[4][67][1] = 0;	M_pattern[4][67][2] = 0;
	M_pattern[4][67][3] = 1;	M_pattern[4][67][4] = 1;	M_pattern[4][67][5] = 1;
	M_pattern[4][67][6] = 1;	M_pattern[4][67][7] = 1;	M_pattern[4][67][8] = 1;


	M_pattern[4][68][0] = 0;	M_pattern[4][68][1] = 0;	M_pattern[4][68][2] = 1;
	M_pattern[4][68][3] = 1;	M_pattern[4][68][4] = 1;	M_pattern[4][68][5] = 1;
	M_pattern[4][68][6] = 0;	M_pattern[4][68][7] = 1;	M_pattern[4][68][8] = 0;


	M_pattern[4][69][0] = 0;	M_pattern[4][69][1] = 0;	M_pattern[4][69][2] = 1;
	M_pattern[4][69][3] = 1;	M_pattern[4][69][4] = 1;	M_pattern[4][69][5] = 1;
	M_pattern[4][69][6] = 0;	M_pattern[4][69][7] = 1;	M_pattern[4][69][8] = 1;


	M_pattern[4][70][0] = 0;	M_pattern[4][70][1] = 0;	M_pattern[4][70][2] = 1;
	M_pattern[4][70][3] = 1;	M_pattern[4][70][4] = 1;	M_pattern[4][70][5] = 1;
	M_pattern[4][70][6] = 1;	M_pattern[4][70][7] = 1;	M_pattern[4][70][8] = 0;


	M_pattern[4][71][0] = 0;	M_pattern[4][71][1] = 0;	M_pattern[4][71][2] = 1;
	M_pattern[4][71][3] = 1;	M_pattern[4][71][4] = 1;	M_pattern[4][71][5] = 1;
	M_pattern[4][71][6] = 1;	M_pattern[4][71][7] = 1;	M_pattern[4][71][8] = 1;


	M_pattern[4][72][0] = 0;	M_pattern[4][72][1] = 1;	M_pattern[4][72][2] = 0;
	M_pattern[4][72][3] = 1;	M_pattern[4][72][4] = 1;	M_pattern[4][72][5] = 1;
	M_pattern[4][72][6] = 0;	M_pattern[4][72][7] = 1;	M_pattern[4][72][8] = 0;


	M_pattern[4][73][0] = 0;	M_pattern[4][73][1] = 1;	M_pattern[4][73][2] = 0;
	M_pattern[4][73][3] = 1;	M_pattern[4][73][4] = 1;	M_pattern[4][73][5] = 1;
	M_pattern[4][73][6] = 0;	M_pattern[4][73][7] = 1;	M_pattern[4][73][8] = 1;


	M_pattern[4][74][0] = 0;	M_pattern[4][74][1] = 1;	M_pattern[4][74][2] = 0;
	M_pattern[4][74][3] = 1;	M_pattern[4][74][4] = 1;	M_pattern[4][74][5] = 1;
	M_pattern[4][74][6] = 1;	M_pattern[4][74][7] = 1;	M_pattern[4][74][8] = 0;


	M_pattern[4][75][0] = 0;	M_pattern[4][75][1] = 1;	M_pattern[4][75][2] = 0;
	M_pattern[4][75][3] = 1;	M_pattern[4][75][4] = 1;	M_pattern[4][75][5] = 1;
	M_pattern[4][75][6] = 1;	M_pattern[4][75][7] = 1;	M_pattern[4][75][8] = 1;


	M_pattern[4][76][0] = 0;	M_pattern[4][76][1] = 1;	M_pattern[4][76][2] = 1;
	M_pattern[4][76][3] = 1;	M_pattern[4][76][4] = 1;	M_pattern[4][76][5] = 1;
	M_pattern[4][76][6] = 0;	M_pattern[4][76][7] = 1;	M_pattern[4][76][8] = 0;


	M_pattern[4][77][0] = 0;	M_pattern[4][77][1] = 1;	M_pattern[4][77][2] = 1;
	M_pattern[4][77][3] = 1;	M_pattern[4][77][4] = 1;	M_pattern[4][77][5] = 1;
	M_pattern[4][77][6] = 0;	M_pattern[4][77][7] = 1;	M_pattern[4][77][8] = 1;


	M_pattern[4][78][0] = 0;	M_pattern[4][78][1] = 1;	M_pattern[4][78][2] = 1;
	M_pattern[4][78][3] = 1;	M_pattern[4][78][4] = 1;	M_pattern[4][78][5] = 1;
	M_pattern[4][78][6] = 1;	M_pattern[4][78][7] = 1;	M_pattern[4][78][8] = 0;


	M_pattern[4][79][0] = 0;	M_pattern[4][79][1] = 1;	M_pattern[4][79][2] = 1;
	M_pattern[4][79][3] = 1;	M_pattern[4][79][4] = 1;	M_pattern[4][79][5] = 1;
	M_pattern[4][79][6] = 1;	M_pattern[4][79][7] = 1;	M_pattern[4][79][8] = 1;


	M_pattern[4][80][0] = 1;	M_pattern[4][80][1] = 0;	M_pattern[4][80][2] = 0;
	M_pattern[4][80][3] = 1;	M_pattern[4][80][4] = 1;	M_pattern[4][80][5] = 1;
	M_pattern[4][80][6] = 0;	M_pattern[4][80][7] = 1;	M_pattern[4][80][8] = 0;


	M_pattern[4][81][0] = 1;	M_pattern[4][81][1] = 0;	M_pattern[4][81][2] = 0;
	M_pattern[4][81][3] = 1;	M_pattern[4][81][4] = 1;	M_pattern[4][81][5] = 1;
	M_pattern[4][81][6] = 0;	M_pattern[4][81][7] = 1;	M_pattern[4][81][8] = 1;


	M_pattern[4][82][0] = 1;	M_pattern[4][82][1] = 0;	M_pattern[4][82][2] = 0;
	M_pattern[4][82][3] = 1;	M_pattern[4][82][4] = 1;	M_pattern[4][82][5] = 1;
	M_pattern[4][82][6] = 1;	M_pattern[4][82][7] = 1;	M_pattern[4][82][8] = 0;


	M_pattern[4][83][0] = 1;	M_pattern[4][83][1] = 0;	M_pattern[4][83][2] = 0;
	M_pattern[4][83][3] = 1;	M_pattern[4][83][4] = 1;	M_pattern[4][83][5] = 1;
	M_pattern[4][83][6] = 1;	M_pattern[4][83][7] = 1;	M_pattern[4][83][8] = 1;


	M_pattern[4][84][0] = 1;	M_pattern[4][84][1] = 0;	M_pattern[4][84][2] = 1;
	M_pattern[4][84][3] = 1;	M_pattern[4][84][4] = 1;	M_pattern[4][84][5] = 1;
	M_pattern[4][84][6] = 0;	M_pattern[4][84][7] = 1;	M_pattern[4][84][8] = 0;


	M_pattern[4][85][0] = 1;	M_pattern[4][85][1] = 0;	M_pattern[4][85][2] = 1;
	M_pattern[4][85][3] = 1;	M_pattern[4][85][4] = 1;	M_pattern[4][85][5] = 1;
	M_pattern[4][85][6] = 0;	M_pattern[4][85][7] = 1;	M_pattern[4][85][8] = 1;


	M_pattern[4][86][0] = 1;	M_pattern[4][86][1] = 0;	M_pattern[4][86][2] = 1;
	M_pattern[4][86][3] = 1;	M_pattern[4][86][4] = 1;	M_pattern[4][86][5] = 1;
	M_pattern[4][86][6] = 1;	M_pattern[4][86][7] = 1;	M_pattern[4][86][8] = 0;


	M_pattern[4][87][0] = 1;	M_pattern[4][87][1] = 0;	M_pattern[4][87][2] = 1;
	M_pattern[4][87][3] = 1;	M_pattern[4][87][4] = 1;	M_pattern[4][87][5] = 1;
	M_pattern[4][87][6] = 1;	M_pattern[4][87][7] = 1;	M_pattern[4][87][8] = 1;


	M_pattern[4][88][0] = 1;	M_pattern[4][88][1] = 1;	M_pattern[4][88][2] = 0;
	M_pattern[4][88][3] = 1;	M_pattern[4][88][4] = 1;	M_pattern[4][88][5] = 1;
	M_pattern[4][88][6] = 0;	M_pattern[4][88][7] = 1;	M_pattern[4][88][8] = 0;


	M_pattern[4][89][0] = 1;	M_pattern[4][89][1] = 1;	M_pattern[4][89][2] = 0;
	M_pattern[4][89][3] = 1;	M_pattern[4][89][4] = 1;	M_pattern[4][89][5] = 1;
	M_pattern[4][89][6] = 0;	M_pattern[4][89][7] = 1;	M_pattern[4][89][8] = 1;


	M_pattern[4][90][0] = 1;	M_pattern[4][90][1] = 1;	M_pattern[4][90][2] = 0;
	M_pattern[4][90][3] = 1;	M_pattern[4][90][4] = 1;	M_pattern[4][90][5] = 1;
	M_pattern[4][90][6] = 1;	M_pattern[4][90][7] = 1;	M_pattern[4][90][8] = 0;


	M_pattern[4][91][0] = 1;	M_pattern[4][91][1] = 1;	M_pattern[4][91][2] = 0;
	M_pattern[4][91][3] = 1;	M_pattern[4][91][4] = 1;	M_pattern[4][91][5] = 1;
	M_pattern[4][91][6] = 1;	M_pattern[4][91][7] = 1;	M_pattern[4][91][8] = 1;


	M_pattern[4][92][0] = 1;	M_pattern[4][92][1] = 1;	M_pattern[4][92][2] = 1;
	M_pattern[4][92][3] = 1;	M_pattern[4][92][4] = 1;	M_pattern[4][92][5] = 1;
	M_pattern[4][92][6] = 0;	M_pattern[4][92][7] = 1;	M_pattern[4][92][8] = 0;


	M_pattern[4][93][0] = 1;	M_pattern[4][93][1] = 1;	M_pattern[4][93][2] = 1;
	M_pattern[4][93][3] = 1;	M_pattern[4][93][4] = 1;	M_pattern[4][93][5] = 1;
	M_pattern[4][93][6] = 0;	M_pattern[4][93][7] = 1;	M_pattern[4][93][8] = 1;


	M_pattern[4][94][0] = 1;	M_pattern[4][94][1] = 1;	M_pattern[4][94][2] = 1;
	M_pattern[4][94][3] = 1;	M_pattern[4][94][4] = 1;	M_pattern[4][94][5] = 1;
	M_pattern[4][94][6] = 1;	M_pattern[4][94][7] = 1;	M_pattern[4][94][8] = 0;


	M_pattern[4][95][0] = 1;	M_pattern[4][95][1] = 1;	M_pattern[4][95][2] = 1;
	M_pattern[4][95][3] = 1;	M_pattern[4][95][4] = 1;	M_pattern[4][95][5] = 1;
	M_pattern[4][95][6] = 1;	M_pattern[4][95][7] = 1;	M_pattern[4][95][8] = 1;


	M_pattern[4][96][0] = 0;	M_pattern[4][96][1] = 1;	M_pattern[4][96][2] = 0;
	M_pattern[4][96][3] = 0;	M_pattern[4][96][4] = 1;	M_pattern[4][96][5] = 1;
	M_pattern[4][96][6] = 0;	M_pattern[4][96][7] = 1;	M_pattern[4][96][8] = 0;


	M_pattern[4][97][0] = 0;	M_pattern[4][97][1] = 1;	M_pattern[4][97][2] = 0;
	M_pattern[4][97][3] = 0;	M_pattern[4][97][4] = 1;	M_pattern[4][97][5] = 1;
	M_pattern[4][97][6] = 0;	M_pattern[4][97][7] = 1;	M_pattern[4][97][8] = 1;


	M_pattern[4][98][0] = 0;	M_pattern[4][98][1] = 1;	M_pattern[4][98][2] = 0;
	M_pattern[4][98][3] = 1;	M_pattern[4][98][4] = 1;	M_pattern[4][98][5] = 1;
	M_pattern[4][98][6] = 0;	M_pattern[4][98][7] = 1;	M_pattern[4][98][8] = 0;


	M_pattern[4][99][0] = 0;	M_pattern[4][99][1] = 1;	M_pattern[4][99][2] = 0;
	M_pattern[4][99][3] = 1;	M_pattern[4][99][4] = 1;	M_pattern[4][99][5] = 1;
	M_pattern[4][99][6] = 0;	M_pattern[4][99][7] = 1;	M_pattern[4][99][8] = 1;


	M_pattern[4][100][0] = 0;	M_pattern[4][100][1] = 1;	M_pattern[4][100][2] = 0;
	M_pattern[4][100][3] = 0;	M_pattern[4][100][4] = 1;	M_pattern[4][100][5] = 1;
	M_pattern[4][100][6] = 1;	M_pattern[4][100][7] = 1;	M_pattern[4][100][8] = 0;


	M_pattern[4][101][0] = 0;	M_pattern[4][101][1] = 1;	M_pattern[4][101][2] = 0;
	M_pattern[4][101][3] = 0;	M_pattern[4][101][4] = 1;	M_pattern[4][101][5] = 1;
	M_pattern[4][101][6] = 1;	M_pattern[4][101][7] = 1;	M_pattern[4][101][8] = 1;


	M_pattern[4][102][0] = 0;	M_pattern[4][102][1] = 1;	M_pattern[4][102][2] = 0;
	M_pattern[4][102][3] = 1;	M_pattern[4][102][4] = 1;	M_pattern[4][102][5] = 1;
	M_pattern[4][102][6] = 1;	M_pattern[4][102][7] = 1;	M_pattern[4][102][8] = 0;


	M_pattern[4][103][0] = 0;	M_pattern[4][103][1] = 1;	M_pattern[4][103][2] = 0;
	M_pattern[4][103][3] = 1;	M_pattern[4][103][4] = 1;	M_pattern[4][103][5] = 1;
	M_pattern[4][103][6] = 1;	M_pattern[4][103][7] = 1;	M_pattern[4][103][8] = 1;


	M_pattern[4][104][0] = 0;	M_pattern[4][104][1] = 1;	M_pattern[4][104][2] = 1;
	M_pattern[4][104][3] = 0;	M_pattern[4][104][4] = 1;	M_pattern[4][104][5] = 1;
	M_pattern[4][104][6] = 0;	M_pattern[4][104][7] = 1;	M_pattern[4][104][8] = 0;


	M_pattern[4][105][0] = 0;	M_pattern[4][105][1] = 1;	M_pattern[4][105][2] = 1;
	M_pattern[4][105][3] = 0;	M_pattern[4][105][4] = 1;	M_pattern[4][105][5] = 1;
	M_pattern[4][105][6] = 0;	M_pattern[4][105][7] = 1;	M_pattern[4][105][8] = 1;


	M_pattern[4][106][0] = 0;	M_pattern[4][106][1] = 1;	M_pattern[4][106][2] = 1;
	M_pattern[4][106][3] = 1;	M_pattern[4][106][4] = 1;	M_pattern[4][106][5] = 1;
	M_pattern[4][106][6] = 0;	M_pattern[4][106][7] = 1;	M_pattern[4][106][8] = 0;


	M_pattern[4][107][0] = 0;	M_pattern[4][107][1] = 1;	M_pattern[4][107][2] = 1;
	M_pattern[4][107][3] = 1;	M_pattern[4][107][4] = 1;	M_pattern[4][107][5] = 1;
	M_pattern[4][107][6] = 0;	M_pattern[4][107][7] = 1;	M_pattern[4][107][8] = 1;


	M_pattern[4][108][0] = 0;	M_pattern[4][108][1] = 1;	M_pattern[4][108][2] = 1;
	M_pattern[4][108][3] = 0;	M_pattern[4][108][4] = 1;	M_pattern[4][108][5] = 1;
	M_pattern[4][108][6] = 1;	M_pattern[4][108][7] = 1;	M_pattern[4][108][8] = 0;


	M_pattern[4][109][0] = 0;	M_pattern[4][109][1] = 1;	M_pattern[4][109][2] = 1;
	M_pattern[4][109][3] = 0;	M_pattern[4][109][4] = 1;	M_pattern[4][109][5] = 1;
	M_pattern[4][109][6] = 1;	M_pattern[4][109][7] = 1;	M_pattern[4][109][8] = 1;


	M_pattern[4][110][0] = 0;	M_pattern[4][110][1] = 1;	M_pattern[4][110][2] = 1;
	M_pattern[4][110][3] = 1;	M_pattern[4][110][4] = 1;	M_pattern[4][110][5] = 1;
	M_pattern[4][110][6] = 1;	M_pattern[4][110][7] = 1;	M_pattern[4][110][8] = 0;


	M_pattern[4][111][0] = 0;	M_pattern[4][111][1] = 1;	M_pattern[4][111][2] = 1;
	M_pattern[4][111][3] = 1;	M_pattern[4][111][4] = 1;	M_pattern[4][111][5] = 1;
	M_pattern[4][111][6] = 1;	M_pattern[4][111][7] = 1;	M_pattern[4][111][8] = 1;


	M_pattern[4][112][0] = 1;	M_pattern[4][112][1] = 1;	M_pattern[4][112][2] = 0;
	M_pattern[4][112][3] = 0;	M_pattern[4][112][4] = 1;	M_pattern[4][112][5] = 1;
	M_pattern[4][112][6] = 0;	M_pattern[4][112][7] = 1;	M_pattern[4][112][8] = 0;


	M_pattern[4][113][0] = 1;	M_pattern[4][113][1] = 1;	M_pattern[4][113][2] = 0;
	M_pattern[4][113][3] = 0;	M_pattern[4][113][4] = 1;	M_pattern[4][113][5] = 1;
	M_pattern[4][113][6] = 0;	M_pattern[4][113][7] = 1;	M_pattern[4][113][8] = 1;


	M_pattern[4][114][0] = 1;	M_pattern[4][114][1] = 1;	M_pattern[4][114][2] = 0;
	M_pattern[4][114][3] = 1;	M_pattern[4][114][4] = 1;	M_pattern[4][114][5] = 1;
	M_pattern[4][114][6] = 0;	M_pattern[4][114][7] = 1;	M_pattern[4][114][8] = 0;


	M_pattern[4][115][0] = 1;	M_pattern[4][115][1] = 1;	M_pattern[4][115][2] = 0;
	M_pattern[4][115][3] = 1;	M_pattern[4][115][4] = 1;	M_pattern[4][115][5] = 1;
	M_pattern[4][115][6] = 0;	M_pattern[4][115][7] = 1;	M_pattern[4][115][8] = 1;


	M_pattern[4][116][0] = 1;	M_pattern[4][116][1] = 1;	M_pattern[4][116][2] = 0;
	M_pattern[4][116][3] = 0;	M_pattern[4][116][4] = 1;	M_pattern[4][116][5] = 1;
	M_pattern[4][116][6] = 1;	M_pattern[4][116][7] = 1;	M_pattern[4][116][8] = 0;


	M_pattern[4][117][0] = 1;	M_pattern[4][117][1] = 1;	M_pattern[4][117][2] = 0;
	M_pattern[4][117][3] = 0;	M_pattern[4][117][4] = 1;	M_pattern[4][117][5] = 1;
	M_pattern[4][117][6] = 1;	M_pattern[4][117][7] = 1;	M_pattern[4][117][8] = 1;


	M_pattern[4][118][0] = 1;	M_pattern[4][118][1] = 1;	M_pattern[4][118][2] = 0;
	M_pattern[4][118][3] = 1;	M_pattern[4][118][4] = 1;	M_pattern[4][118][5] = 1;
	M_pattern[4][118][6] = 1;	M_pattern[4][118][7] = 1;	M_pattern[4][118][8] = 0;


	M_pattern[4][119][0] = 1;	M_pattern[4][119][1] = 1;	M_pattern[4][119][2] = 0;
	M_pattern[4][119][3] = 1;	M_pattern[4][119][4] = 1;	M_pattern[4][119][5] = 1;
	M_pattern[4][119][6] = 1;	M_pattern[4][119][7] = 1;	M_pattern[4][119][8] = 1;


	M_pattern[4][120][0] = 1;	M_pattern[4][120][1] = 1;	M_pattern[4][120][2] = 1;
	M_pattern[4][120][3] = 0;	M_pattern[4][120][4] = 1;	M_pattern[4][120][5] = 1;
	M_pattern[4][120][6] = 0;	M_pattern[4][120][7] = 1;	M_pattern[4][120][8] = 0;


	M_pattern[4][121][0] = 1;	M_pattern[4][121][1] = 1;	M_pattern[4][121][2] = 1;
	M_pattern[4][121][3] = 0;	M_pattern[4][121][4] = 1;	M_pattern[4][121][5] = 1;
	M_pattern[4][121][6] = 0;	M_pattern[4][121][7] = 1;	M_pattern[4][121][8] = 1;


	M_pattern[4][122][0] = 1;	M_pattern[4][122][1] = 1;	M_pattern[4][122][2] = 1;
	M_pattern[4][122][3] = 1;	M_pattern[4][122][4] = 1;	M_pattern[4][122][5] = 1;
	M_pattern[4][122][6] = 0;	M_pattern[4][122][7] = 1;	M_pattern[4][122][8] = 0;


	M_pattern[4][123][0] = 1;	M_pattern[4][123][1] = 1;	M_pattern[4][123][2] = 1;
	M_pattern[4][123][3] = 1;	M_pattern[4][123][4] = 1;	M_pattern[4][123][5] = 1;
	M_pattern[4][123][6] = 0;	M_pattern[4][123][7] = 1;	M_pattern[4][123][8] = 1;


	M_pattern[4][124][0] = 1;	M_pattern[4][124][1] = 1;	M_pattern[4][124][2] = 1;
	M_pattern[4][124][3] = 0;	M_pattern[4][124][4] = 1;	M_pattern[4][124][5] = 1;
	M_pattern[4][124][6] = 1;	M_pattern[4][124][7] = 1;	M_pattern[4][124][8] = 0;


	M_pattern[4][125][0] = 1;	M_pattern[4][125][1] = 1;	M_pattern[4][125][2] = 1;
	M_pattern[4][125][3] = 0;	M_pattern[4][125][4] = 1;	M_pattern[4][125][5] = 1;
	M_pattern[4][125][6] = 1;	M_pattern[4][125][7] = 1;	M_pattern[4][125][8] = 1;


	M_pattern[4][126][0] = 1;	M_pattern[4][126][1] = 1;	M_pattern[4][126][2] = 1;
	M_pattern[4][126][3] = 1;	M_pattern[4][126][4] = 1;	M_pattern[4][126][5] = 1;
	M_pattern[4][126][6] = 1;	M_pattern[4][126][7] = 1;	M_pattern[4][126][8] = 0;


	M_pattern[4][127][0] = 1;	M_pattern[4][127][1] = 1;	M_pattern[4][127][2] = 1;
	M_pattern[4][127][3] = 1;	M_pattern[4][127][4] = 1;	M_pattern[4][127][5] = 1;
	M_pattern[4][127][6] = 1;	M_pattern[4][127][7] = 1;	M_pattern[4][127][8] = 1;





	M_pattern[5][0][0] = 1;	M_pattern[5][0][1] = 0;	M_pattern[5][0][2] = 1;
	M_pattern[5][0][3] = 0;	M_pattern[5][0][4] = 1;	M_pattern[5][0][5] = 0;
	M_pattern[5][0][6] = 0;	M_pattern[5][0][7] = 0;	M_pattern[5][0][8] = 1;


	M_pattern[5][1][0] = 1;	M_pattern[5][1][1] = 0;	M_pattern[5][1][2] = 1;
	M_pattern[5][1][3] = 0;	M_pattern[5][1][4] = 1;	M_pattern[5][1][5] = 0;
	M_pattern[5][1][6] = 0;	M_pattern[5][1][7] = 1;	M_pattern[5][1][8] = 0;


	M_pattern[5][2][0] = 1;	M_pattern[5][2][1] = 0;	M_pattern[5][2][2] = 1;
	M_pattern[5][2][3] = 0;	M_pattern[5][2][4] = 1;	M_pattern[5][2][5] = 0;
	M_pattern[5][2][6] = 0;	M_pattern[5][2][7] = 1;	M_pattern[5][2][8] = 1;


	M_pattern[5][3][0] = 1;	M_pattern[5][3][1] = 0;	M_pattern[5][3][2] = 1;
	M_pattern[5][3][3] = 0;	M_pattern[5][3][4] = 1;	M_pattern[5][3][5] = 0;
	M_pattern[5][3][6] = 1;	M_pattern[5][3][7] = 0;	M_pattern[5][3][8] = 0;


	M_pattern[5][4][0] = 1;	M_pattern[5][4][1] = 0;	M_pattern[5][4][2] = 1;
	M_pattern[5][4][3] = 0;	M_pattern[5][4][4] = 1;	M_pattern[5][4][5] = 0;
	M_pattern[5][4][6] = 1;	M_pattern[5][4][7] = 0;	M_pattern[5][4][8] = 1;


	M_pattern[5][5][0] = 1;	M_pattern[5][5][1] = 0;	M_pattern[5][5][2] = 1;
	M_pattern[5][5][3] = 0;	M_pattern[5][5][4] = 1;	M_pattern[5][5][5] = 0;
	M_pattern[5][5][6] = 1;	M_pattern[5][5][7] = 1;	M_pattern[5][5][8] = 0;


	M_pattern[5][6][0] = 1;	M_pattern[5][6][1] = 0;	M_pattern[5][6][2] = 1;
	M_pattern[5][6][3] = 0;	M_pattern[5][6][4] = 1;	M_pattern[5][6][5] = 0;
	M_pattern[5][6][6] = 1;	M_pattern[5][6][7] = 1;	M_pattern[5][6][8] = 1;


	M_pattern[5][7][0] = 1;	M_pattern[5][7][1] = 0;	M_pattern[5][7][2] = 1;
	M_pattern[5][7][3] = 0;	M_pattern[5][7][4] = 1;	M_pattern[5][7][5] = 1;
	M_pattern[5][7][6] = 0;	M_pattern[5][7][7] = 0;	M_pattern[5][7][8] = 1;


	M_pattern[5][8][0] = 1;	M_pattern[5][8][1] = 0;	M_pattern[5][8][2] = 1;
	M_pattern[5][8][3] = 0;	M_pattern[5][8][4] = 1;	M_pattern[5][8][5] = 1;
	M_pattern[5][8][6] = 0;	M_pattern[5][8][7] = 1;	M_pattern[5][8][8] = 0;


	M_pattern[5][9][0] = 1;	M_pattern[5][9][1] = 0;	M_pattern[5][9][2] = 1;
	M_pattern[5][9][3] = 0;	M_pattern[5][9][4] = 1;	M_pattern[5][9][5] = 1;
	M_pattern[5][9][6] = 0;	M_pattern[5][9][7] = 1;	M_pattern[5][9][8] = 1;


	M_pattern[5][10][0] = 1;	M_pattern[5][10][1] = 0;	M_pattern[5][10][2] = 1;
	M_pattern[5][10][3] = 0;	M_pattern[5][10][4] = 1;	M_pattern[5][10][5] = 1;
	M_pattern[5][10][6] = 1;	M_pattern[5][10][7] = 0;	M_pattern[5][10][8] = 0;


	M_pattern[5][11][0] = 1;	M_pattern[5][11][1] = 0;	M_pattern[5][11][2] = 1;
	M_pattern[5][11][3] = 0;	M_pattern[5][11][4] = 1;	M_pattern[5][11][5] = 1;
	M_pattern[5][11][6] = 1;	M_pattern[5][11][7] = 0;	M_pattern[5][11][8] = 1;


	M_pattern[5][12][0] = 1;	M_pattern[5][12][1] = 0;	M_pattern[5][12][2] = 1;
	M_pattern[5][12][3] = 0;	M_pattern[5][12][4] = 1;	M_pattern[5][12][5] = 1;
	M_pattern[5][12][6] = 1;	M_pattern[5][12][7] = 1;	M_pattern[5][12][8] = 0;


	M_pattern[5][13][0] = 1;	M_pattern[5][13][1] = 0;	M_pattern[5][13][2] = 1;
	M_pattern[5][13][3] = 0;	M_pattern[5][13][4] = 1;	M_pattern[5][13][5] = 1;
	M_pattern[5][13][6] = 1;	M_pattern[5][13][7] = 1;	M_pattern[5][13][8] = 1;


	M_pattern[5][14][0] = 1;	M_pattern[5][14][1] = 0;	M_pattern[5][14][2] = 1;
	M_pattern[5][14][3] = 1;	M_pattern[5][14][4] = 1;	M_pattern[5][14][5] = 0;
	M_pattern[5][14][6] = 0;	M_pattern[5][14][7] = 0;	M_pattern[5][14][8] = 1;


	M_pattern[5][15][0] = 1;	M_pattern[5][15][1] = 0;	M_pattern[5][15][2] = 1;
	M_pattern[5][15][3] = 1;	M_pattern[5][15][4] = 1;	M_pattern[5][15][5] = 0;
	M_pattern[5][15][6] = 0;	M_pattern[5][15][7] = 1;	M_pattern[5][15][8] = 0;


	M_pattern[5][16][0] = 1;	M_pattern[5][16][1] = 0;	M_pattern[5][16][2] = 1;
	M_pattern[5][16][3] = 1;	M_pattern[5][16][4] = 1;	M_pattern[5][16][5] = 0;
	M_pattern[5][16][6] = 0;	M_pattern[5][16][7] = 1;	M_pattern[5][16][8] = 1;


	M_pattern[5][17][0] = 1;	M_pattern[5][17][1] = 0;	M_pattern[5][17][2] = 1;
	M_pattern[5][17][3] = 1;	M_pattern[5][17][4] = 1;	M_pattern[5][17][5] = 0;
	M_pattern[5][17][6] = 1;	M_pattern[5][17][7] = 0;	M_pattern[5][17][8] = 0;


	M_pattern[5][18][0] = 1;	M_pattern[5][18][1] = 0;	M_pattern[5][18][2] = 1;
	M_pattern[5][18][3] = 1;	M_pattern[5][18][4] = 1;	M_pattern[5][18][5] = 0;
	M_pattern[5][18][6] = 1;	M_pattern[5][18][7] = 0;	M_pattern[5][18][8] = 1;


	M_pattern[5][19][0] = 1;	M_pattern[5][19][1] = 0;	M_pattern[5][19][2] = 1;
	M_pattern[5][19][3] = 1;	M_pattern[5][19][4] = 1;	M_pattern[5][19][5] = 0;
	M_pattern[5][19][6] = 1;	M_pattern[5][19][7] = 1;	M_pattern[5][19][8] = 0;


	M_pattern[5][20][0] = 1;	M_pattern[5][20][1] = 0;	M_pattern[5][20][2] = 1;
	M_pattern[5][20][3] = 1;	M_pattern[5][20][4] = 1;	M_pattern[5][20][5] = 0;
	M_pattern[5][20][6] = 1;	M_pattern[5][20][7] = 1;	M_pattern[5][20][8] = 1;


	M_pattern[5][21][0] = 1;	M_pattern[5][21][1] = 0;	M_pattern[5][21][2] = 1;
	M_pattern[5][21][3] = 1;	M_pattern[5][21][4] = 1;	M_pattern[5][21][5] = 1;
	M_pattern[5][21][6] = 0;	M_pattern[5][21][7] = 0;	M_pattern[5][21][8] = 1;


	M_pattern[5][22][0] = 1;	M_pattern[5][22][1] = 0;	M_pattern[5][22][2] = 1;
	M_pattern[5][22][3] = 1;	M_pattern[5][22][4] = 1;	M_pattern[5][22][5] = 1;
	M_pattern[5][22][6] = 0;	M_pattern[5][22][7] = 1;	M_pattern[5][22][8] = 0;


	M_pattern[5][23][0] = 1;	M_pattern[5][23][1] = 0;	M_pattern[5][23][2] = 1;
	M_pattern[5][23][3] = 1;	M_pattern[5][23][4] = 1;	M_pattern[5][23][5] = 1;
	M_pattern[5][23][6] = 0;	M_pattern[5][23][7] = 1;	M_pattern[5][23][8] = 1;


	M_pattern[5][24][0] = 1;	M_pattern[5][24][1] = 0;	M_pattern[5][24][2] = 1;
	M_pattern[5][24][3] = 1;	M_pattern[5][24][4] = 1;	M_pattern[5][24][5] = 1;
	M_pattern[5][24][6] = 1;	M_pattern[5][24][7] = 0;	M_pattern[5][24][8] = 0;


	M_pattern[5][25][0] = 1;	M_pattern[5][25][1] = 0;	M_pattern[5][25][2] = 1;
	M_pattern[5][25][3] = 1;	M_pattern[5][25][4] = 1;	M_pattern[5][25][5] = 1;
	M_pattern[5][25][6] = 1;	M_pattern[5][25][7] = 0;	M_pattern[5][25][8] = 1;


	M_pattern[5][26][0] = 1;	M_pattern[5][26][1] = 0;	M_pattern[5][26][2] = 1;
	M_pattern[5][26][3] = 1;	M_pattern[5][26][4] = 1;	M_pattern[5][26][5] = 1;
	M_pattern[5][26][6] = 1;	M_pattern[5][26][7] = 1;	M_pattern[5][26][8] = 0;


	M_pattern[5][27][0] = 1;	M_pattern[5][27][1] = 0;	M_pattern[5][27][2] = 1;
	M_pattern[5][27][3] = 1;	M_pattern[5][27][4] = 1;	M_pattern[5][27][5] = 1;
	M_pattern[5][27][6] = 1;	M_pattern[5][27][7] = 1;	M_pattern[5][27][8] = 1;


	M_pattern[5][28][0] = 1;	M_pattern[5][28][1] = 1;	M_pattern[5][28][2] = 1;
	M_pattern[5][28][3] = 0;	M_pattern[5][28][4] = 1;	M_pattern[5][28][5] = 0;
	M_pattern[5][28][6] = 0;	M_pattern[5][28][7] = 0;	M_pattern[5][28][8] = 1;


	M_pattern[5][29][0] = 1;	M_pattern[5][29][1] = 1;	M_pattern[5][29][2] = 1;
	M_pattern[5][29][3] = 0;	M_pattern[5][29][4] = 1;	M_pattern[5][29][5] = 0;
	M_pattern[5][29][6] = 0;	M_pattern[5][29][7] = 1;	M_pattern[5][29][8] = 0;


	M_pattern[5][30][0] = 1;	M_pattern[5][30][1] = 1;	M_pattern[5][30][2] = 1;
	M_pattern[5][30][3] = 0;	M_pattern[5][30][4] = 1;	M_pattern[5][30][5] = 0;
	M_pattern[5][30][6] = 0;	M_pattern[5][30][7] = 1;	M_pattern[5][30][8] = 1;


	M_pattern[5][31][0] = 1;	M_pattern[5][31][1] = 1;	M_pattern[5][31][2] = 1;
	M_pattern[5][31][3] = 0;	M_pattern[5][31][4] = 1;	M_pattern[5][31][5] = 0;
	M_pattern[5][31][6] = 1;	M_pattern[5][31][7] = 0;	M_pattern[5][31][8] = 0;


	M_pattern[5][32][0] = 1;	M_pattern[5][32][1] = 1;	M_pattern[5][32][2] = 1;
	M_pattern[5][32][3] = 0;	M_pattern[5][32][4] = 1;	M_pattern[5][32][5] = 0;
	M_pattern[5][32][6] = 1;	M_pattern[5][32][7] = 0;	M_pattern[5][32][8] = 1;


	M_pattern[5][33][0] = 1;	M_pattern[5][33][1] = 1;	M_pattern[5][33][2] = 1;
	M_pattern[5][33][3] = 0;	M_pattern[5][33][4] = 1;	M_pattern[5][33][5] = 0;
	M_pattern[5][33][6] = 1;	M_pattern[5][33][7] = 1;	M_pattern[5][33][8] = 0;


	M_pattern[5][34][0] = 1;	M_pattern[5][34][1] = 1;	M_pattern[5][34][2] = 1;
	M_pattern[5][34][3] = 0;	M_pattern[5][34][4] = 1;	M_pattern[5][34][5] = 0;
	M_pattern[5][34][6] = 1;	M_pattern[5][34][7] = 1;	M_pattern[5][34][8] = 1;


	M_pattern[5][35][0] = 1;	M_pattern[5][35][1] = 1;	M_pattern[5][35][2] = 1;
	M_pattern[5][35][3] = 0;	M_pattern[5][35][4] = 1;	M_pattern[5][35][5] = 1;
	M_pattern[5][35][6] = 0;	M_pattern[5][35][7] = 0;	M_pattern[5][35][8] = 1;


	M_pattern[5][36][0] = 1;	M_pattern[5][36][1] = 1;	M_pattern[5][36][2] = 1;
	M_pattern[5][36][3] = 0;	M_pattern[5][36][4] = 1;	M_pattern[5][36][5] = 1;
	M_pattern[5][36][6] = 0;	M_pattern[5][36][7] = 1;	M_pattern[5][36][8] = 0;


	M_pattern[5][37][0] = 1;	M_pattern[5][37][1] = 1;	M_pattern[5][37][2] = 1;
	M_pattern[5][37][3] = 0;	M_pattern[5][37][4] = 1;	M_pattern[5][37][5] = 1;
	M_pattern[5][37][6] = 0;	M_pattern[5][37][7] = 1;	M_pattern[5][37][8] = 1;


	M_pattern[5][38][0] = 1;	M_pattern[5][38][1] = 1;	M_pattern[5][38][2] = 1;
	M_pattern[5][38][3] = 0;	M_pattern[5][38][4] = 1;	M_pattern[5][38][5] = 1;
	M_pattern[5][38][6] = 1;	M_pattern[5][38][7] = 0;	M_pattern[5][38][8] = 0;


	M_pattern[5][39][0] = 1;	M_pattern[5][39][1] = 1;	M_pattern[5][39][2] = 1;
	M_pattern[5][39][3] = 0;	M_pattern[5][39][4] = 1;	M_pattern[5][39][5] = 1;
	M_pattern[5][39][6] = 1;	M_pattern[5][39][7] = 0;	M_pattern[5][39][8] = 1;


	M_pattern[5][40][0] = 1;	M_pattern[5][40][1] = 1;	M_pattern[5][40][2] = 1;
	M_pattern[5][40][3] = 0;	M_pattern[5][40][4] = 1;	M_pattern[5][40][5] = 1;
	M_pattern[5][40][6] = 1;	M_pattern[5][40][7] = 1;	M_pattern[5][40][8] = 0;


	M_pattern[5][41][0] = 1;	M_pattern[5][41][1] = 1;	M_pattern[5][41][2] = 1;
	M_pattern[5][41][3] = 0;	M_pattern[5][41][4] = 1;	M_pattern[5][41][5] = 1;
	M_pattern[5][41][6] = 1;	M_pattern[5][41][7] = 1;	M_pattern[5][41][8] = 1;


	M_pattern[5][42][0] = 1;	M_pattern[5][42][1] = 1;	M_pattern[5][42][2] = 1;
	M_pattern[5][42][3] = 1;	M_pattern[5][42][4] = 1;	M_pattern[5][42][5] = 0;
	M_pattern[5][42][6] = 0;	M_pattern[5][42][7] = 0;	M_pattern[5][42][8] = 1;


	M_pattern[5][43][0] = 1;	M_pattern[5][43][1] = 1;	M_pattern[5][43][2] = 1;
	M_pattern[5][43][3] = 1;	M_pattern[5][43][4] = 1;	M_pattern[5][43][5] = 0;
	M_pattern[5][43][6] = 0;	M_pattern[5][43][7] = 1;	M_pattern[5][43][8] = 0;


	M_pattern[5][44][0] = 1;	M_pattern[5][44][1] = 1;	M_pattern[5][44][2] = 1;
	M_pattern[5][44][3] = 1;	M_pattern[5][44][4] = 1;	M_pattern[5][44][5] = 0;
	M_pattern[5][44][6] = 0;	M_pattern[5][44][7] = 1;	M_pattern[5][44][8] = 1;


	M_pattern[5][45][0] = 1;	M_pattern[5][45][1] = 1;	M_pattern[5][45][2] = 1;
	M_pattern[5][45][3] = 1;	M_pattern[5][45][4] = 1;	M_pattern[5][45][5] = 0;
	M_pattern[5][45][6] = 1;	M_pattern[5][45][7] = 0;	M_pattern[5][45][8] = 0;


	M_pattern[5][46][0] = 1;	M_pattern[5][46][1] = 1;	M_pattern[5][46][2] = 1;
	M_pattern[5][46][3] = 1;	M_pattern[5][46][4] = 1;	M_pattern[5][46][5] = 0;
	M_pattern[5][46][6] = 1;	M_pattern[5][46][7] = 0;	M_pattern[5][46][8] = 1;


	M_pattern[5][47][0] = 1;	M_pattern[5][47][1] = 1;	M_pattern[5][47][2] = 1;
	M_pattern[5][47][3] = 1;	M_pattern[5][47][4] = 1;	M_pattern[5][47][5] = 0;
	M_pattern[5][47][6] = 1;	M_pattern[5][47][7] = 1;	M_pattern[5][47][8] = 0;


	M_pattern[5][48][0] = 1;	M_pattern[5][48][1] = 1;	M_pattern[5][48][2] = 1;
	M_pattern[5][48][3] = 1;	M_pattern[5][48][4] = 1;	M_pattern[5][48][5] = 0;
	M_pattern[5][48][6] = 1;	M_pattern[5][48][7] = 1;	M_pattern[5][48][8] = 1;


	M_pattern[5][49][0] = 1;	M_pattern[5][49][1] = 1;	M_pattern[5][49][2] = 1;
	M_pattern[5][49][3] = 1;	M_pattern[5][49][4] = 1;	M_pattern[5][49][5] = 1;
	M_pattern[5][49][6] = 0;	M_pattern[5][49][7] = 0;	M_pattern[5][49][8] = 1;


	M_pattern[5][50][0] = 1;	M_pattern[5][50][1] = 1;	M_pattern[5][50][2] = 1;
	M_pattern[5][50][3] = 1;	M_pattern[5][50][4] = 1;	M_pattern[5][50][5] = 1;
	M_pattern[5][50][6] = 0;	M_pattern[5][50][7] = 1;	M_pattern[5][50][8] = 0;


	M_pattern[5][51][0] = 1;	M_pattern[5][51][1] = 1;	M_pattern[5][51][2] = 1;
	M_pattern[5][51][3] = 1;	M_pattern[5][51][4] = 1;	M_pattern[5][51][5] = 1;
	M_pattern[5][51][6] = 0;	M_pattern[5][51][7] = 1;	M_pattern[5][51][8] = 1;


	M_pattern[5][52][0] = 1;	M_pattern[5][52][1] = 1;	M_pattern[5][52][2] = 1;
	M_pattern[5][52][3] = 1;	M_pattern[5][52][4] = 1;	M_pattern[5][52][5] = 1;
	M_pattern[5][52][6] = 1;	M_pattern[5][52][7] = 0;	M_pattern[5][52][8] = 0;


	M_pattern[5][53][0] = 1;	M_pattern[5][53][1] = 1;	M_pattern[5][53][2] = 1;
	M_pattern[5][53][3] = 1;	M_pattern[5][53][4] = 1;	M_pattern[5][53][5] = 1;
	M_pattern[5][53][6] = 1;	M_pattern[5][53][7] = 0;	M_pattern[5][53][8] = 1;


	M_pattern[5][54][0] = 1;	M_pattern[5][54][1] = 1;	M_pattern[5][54][2] = 1;
	M_pattern[5][54][3] = 1;	M_pattern[5][54][4] = 1;	M_pattern[5][54][5] = 1;
	M_pattern[5][54][6] = 1;	M_pattern[5][54][7] = 1;	M_pattern[5][54][8] = 0;


	M_pattern[5][55][0] = 1;	M_pattern[5][55][1] = 1;	M_pattern[5][55][2] = 1;
	M_pattern[5][55][3] = 1;	M_pattern[5][55][4] = 1;	M_pattern[5][55][5] = 1;
	M_pattern[5][55][6] = 1;	M_pattern[5][55][7] = 1;	M_pattern[5][55][8] = 1;


	M_pattern[5][56][0] = 1;	M_pattern[5][56][1] = 0;	M_pattern[5][56][2] = 0;
	M_pattern[5][56][3] = 0;	M_pattern[5][56][4] = 1;	M_pattern[5][56][5] = 0;
	M_pattern[5][56][6] = 1;	M_pattern[5][56][7] = 0;	M_pattern[5][56][8] = 1;


	M_pattern[5][57][0] = 1;	M_pattern[5][57][1] = 0;	M_pattern[5][57][2] = 0;
	M_pattern[5][57][3] = 0;	M_pattern[5][57][4] = 1;	M_pattern[5][57][5] = 1;
	M_pattern[5][57][6] = 1;	M_pattern[5][57][7] = 0;	M_pattern[5][57][8] = 0;


	M_pattern[5][58][0] = 1;	M_pattern[5][58][1] = 0;	M_pattern[5][58][2] = 0;
	M_pattern[5][58][3] = 0;	M_pattern[5][58][4] = 1;	M_pattern[5][58][5] = 1;
	M_pattern[5][58][6] = 1;	M_pattern[5][58][7] = 0;	M_pattern[5][58][8] = 1;


	M_pattern[5][59][0] = 1;	M_pattern[5][59][1] = 0;	M_pattern[5][59][2] = 1;
	M_pattern[5][59][3] = 0;	M_pattern[5][59][4] = 1;	M_pattern[5][59][5] = 0;
	M_pattern[5][59][6] = 1;	M_pattern[5][59][7] = 0;	M_pattern[5][59][8] = 0;


	M_pattern[5][60][0] = 1;	M_pattern[5][60][1] = 0;	M_pattern[5][60][2] = 1;
	M_pattern[5][60][3] = 0;	M_pattern[5][60][4] = 1;	M_pattern[5][60][5] = 0;
	M_pattern[5][60][6] = 1;	M_pattern[5][60][7] = 0;	M_pattern[5][60][8] = 1;


	M_pattern[5][61][0] = 1;	M_pattern[5][61][1] = 0;	M_pattern[5][61][2] = 1;
	M_pattern[5][61][3] = 0;	M_pattern[5][61][4] = 1;	M_pattern[5][61][5] = 1;
	M_pattern[5][61][6] = 1;	M_pattern[5][61][7] = 0;	M_pattern[5][61][8] = 0;


	M_pattern[5][62][0] = 1;	M_pattern[5][62][1] = 0;	M_pattern[5][62][2] = 1;
	M_pattern[5][62][3] = 0;	M_pattern[5][62][4] = 1;	M_pattern[5][62][5] = 1;
	M_pattern[5][62][6] = 1;	M_pattern[5][62][7] = 0;	M_pattern[5][62][8] = 1;


	M_pattern[5][63][0] = 1;	M_pattern[5][63][1] = 0;	M_pattern[5][63][2] = 0;
	M_pattern[5][63][3] = 0;	M_pattern[5][63][4] = 1;	M_pattern[5][63][5] = 0;
	M_pattern[5][63][6] = 1;	M_pattern[5][63][7] = 1;	M_pattern[5][63][8] = 1;


	M_pattern[5][64][0] = 1;	M_pattern[5][64][1] = 0;	M_pattern[5][64][2] = 0;
	M_pattern[5][64][3] = 0;	M_pattern[5][64][4] = 1;	M_pattern[5][64][5] = 1;
	M_pattern[5][64][6] = 1;	M_pattern[5][64][7] = 1;	M_pattern[5][64][8] = 0;


	M_pattern[5][65][0] = 1;	M_pattern[5][65][1] = 0;	M_pattern[5][65][2] = 0;
	M_pattern[5][65][3] = 0;	M_pattern[5][65][4] = 1;	M_pattern[5][65][5] = 1;
	M_pattern[5][65][6] = 1;	M_pattern[5][65][7] = 1;	M_pattern[5][65][8] = 1;


	M_pattern[5][66][0] = 1;	M_pattern[5][66][1] = 0;	M_pattern[5][66][2] = 1;
	M_pattern[5][66][3] = 0;	M_pattern[5][66][4] = 1;	M_pattern[5][66][5] = 0;
	M_pattern[5][66][6] = 1;	M_pattern[5][66][7] = 1;	M_pattern[5][66][8] = 0;


	M_pattern[5][67][0] = 1;	M_pattern[5][67][1] = 0;	M_pattern[5][67][2] = 1;
	M_pattern[5][67][3] = 0;	M_pattern[5][67][4] = 1;	M_pattern[5][67][5] = 0;
	M_pattern[5][67][6] = 1;	M_pattern[5][67][7] = 1;	M_pattern[5][67][8] = 1;


	M_pattern[5][68][0] = 1;	M_pattern[5][68][1] = 0;	M_pattern[5][68][2] = 1;
	M_pattern[5][68][3] = 0;	M_pattern[5][68][4] = 1;	M_pattern[5][68][5] = 1;
	M_pattern[5][68][6] = 1;	M_pattern[5][68][7] = 1;	M_pattern[5][68][8] = 0;


	M_pattern[5][69][0] = 1;	M_pattern[5][69][1] = 0;	M_pattern[5][69][2] = 1;
	M_pattern[5][69][3] = 0;	M_pattern[5][69][4] = 1;	M_pattern[5][69][5] = 1;
	M_pattern[5][69][6] = 1;	M_pattern[5][69][7] = 1;	M_pattern[5][69][8] = 1;


	M_pattern[5][70][0] = 1;	M_pattern[5][70][1] = 0;	M_pattern[5][70][2] = 0;
	M_pattern[5][70][3] = 1;	M_pattern[5][70][4] = 1;	M_pattern[5][70][5] = 0;
	M_pattern[5][70][6] = 1;	M_pattern[5][70][7] = 0;	M_pattern[5][70][8] = 1;


	M_pattern[5][71][0] = 1;	M_pattern[5][71][1] = 0;	M_pattern[5][71][2] = 0;
	M_pattern[5][71][3] = 1;	M_pattern[5][71][4] = 1;	M_pattern[5][71][5] = 1;
	M_pattern[5][71][6] = 1;	M_pattern[5][71][7] = 0;	M_pattern[5][71][8] = 0;


	M_pattern[5][72][0] = 1;	M_pattern[5][72][1] = 0;	M_pattern[5][72][2] = 0;
	M_pattern[5][72][3] = 1;	M_pattern[5][72][4] = 1;	M_pattern[5][72][5] = 1;
	M_pattern[5][72][6] = 1;	M_pattern[5][72][7] = 0;	M_pattern[5][72][8] = 1;


	M_pattern[5][73][0] = 1;	M_pattern[5][73][1] = 0;	M_pattern[5][73][2] = 1;
	M_pattern[5][73][3] = 1;	M_pattern[5][73][4] = 1;	M_pattern[5][73][5] = 0;
	M_pattern[5][73][6] = 1;	M_pattern[5][73][7] = 0;	M_pattern[5][73][8] = 0;


	M_pattern[5][74][0] = 1;	M_pattern[5][74][1] = 0;	M_pattern[5][74][2] = 1;
	M_pattern[5][74][3] = 1;	M_pattern[5][74][4] = 1;	M_pattern[5][74][5] = 0;
	M_pattern[5][74][6] = 1;	M_pattern[5][74][7] = 0;	M_pattern[5][74][8] = 1;


	M_pattern[5][75][0] = 1;	M_pattern[5][75][1] = 0;	M_pattern[5][75][2] = 1;
	M_pattern[5][75][3] = 1;	M_pattern[5][75][4] = 1;	M_pattern[5][75][5] = 1;
	M_pattern[5][75][6] = 1;	M_pattern[5][75][7] = 0;	M_pattern[5][75][8] = 0;


	M_pattern[5][76][0] = 1;	M_pattern[5][76][1] = 0;	M_pattern[5][76][2] = 1;
	M_pattern[5][76][3] = 1;	M_pattern[5][76][4] = 1;	M_pattern[5][76][5] = 1;
	M_pattern[5][76][6] = 1;	M_pattern[5][76][7] = 0;	M_pattern[5][76][8] = 1;


	M_pattern[5][77][0] = 1;	M_pattern[5][77][1] = 0;	M_pattern[5][77][2] = 0;
	M_pattern[5][77][3] = 1;	M_pattern[5][77][4] = 1;	M_pattern[5][77][5] = 0;
	M_pattern[5][77][6] = 1;	M_pattern[5][77][7] = 1;	M_pattern[5][77][8] = 1;


	M_pattern[5][78][0] = 1;	M_pattern[5][78][1] = 0;	M_pattern[5][78][2] = 0;
	M_pattern[5][78][3] = 1;	M_pattern[5][78][4] = 1;	M_pattern[5][78][5] = 1;
	M_pattern[5][78][6] = 1;	M_pattern[5][78][7] = 1;	M_pattern[5][78][8] = 0;


	M_pattern[5][79][0] = 1;	M_pattern[5][79][1] = 0;	M_pattern[5][79][2] = 0;
	M_pattern[5][79][3] = 1;	M_pattern[5][79][4] = 1;	M_pattern[5][79][5] = 1;
	M_pattern[5][79][6] = 1;	M_pattern[5][79][7] = 1;	M_pattern[5][79][8] = 1;


	M_pattern[5][80][0] = 1;	M_pattern[5][80][1] = 0;	M_pattern[5][80][2] = 1;
	M_pattern[5][80][3] = 1;	M_pattern[5][80][4] = 1;	M_pattern[5][80][5] = 0;
	M_pattern[5][80][6] = 1;	M_pattern[5][80][7] = 1;	M_pattern[5][80][8] = 0;


	M_pattern[5][81][0] = 1;	M_pattern[5][81][1] = 0;	M_pattern[5][81][2] = 1;
	M_pattern[5][81][3] = 1;	M_pattern[5][81][4] = 1;	M_pattern[5][81][5] = 0;
	M_pattern[5][81][6] = 1;	M_pattern[5][81][7] = 1;	M_pattern[5][81][8] = 1;


	M_pattern[5][82][0] = 1;	M_pattern[5][82][1] = 0;	M_pattern[5][82][2] = 1;
	M_pattern[5][82][3] = 1;	M_pattern[5][82][4] = 1;	M_pattern[5][82][5] = 1;
	M_pattern[5][82][6] = 1;	M_pattern[5][82][7] = 1;	M_pattern[5][82][8] = 0;


	M_pattern[5][83][0] = 1;	M_pattern[5][83][1] = 0;	M_pattern[5][83][2] = 1;
	M_pattern[5][83][3] = 1;	M_pattern[5][83][4] = 1;	M_pattern[5][83][5] = 1;
	M_pattern[5][83][6] = 1;	M_pattern[5][83][7] = 1;	M_pattern[5][83][8] = 1;


	M_pattern[5][84][0] = 1;	M_pattern[5][84][1] = 1;	M_pattern[5][84][2] = 0;
	M_pattern[5][84][3] = 0;	M_pattern[5][84][4] = 1;	M_pattern[5][84][5] = 0;
	M_pattern[5][84][6] = 1;	M_pattern[5][84][7] = 0;	M_pattern[5][84][8] = 1;


	M_pattern[5][85][0] = 1;	M_pattern[5][85][1] = 1;	M_pattern[5][85][2] = 0;
	M_pattern[5][85][3] = 0;	M_pattern[5][85][4] = 1;	M_pattern[5][85][5] = 1;
	M_pattern[5][85][6] = 1;	M_pattern[5][85][7] = 0;	M_pattern[5][85][8] = 0;


	M_pattern[5][86][0] = 1;	M_pattern[5][86][1] = 1;	M_pattern[5][86][2] = 0;
	M_pattern[5][86][3] = 0;	M_pattern[5][86][4] = 1;	M_pattern[5][86][5] = 1;
	M_pattern[5][86][6] = 1;	M_pattern[5][86][7] = 0;	M_pattern[5][86][8] = 1;


	M_pattern[5][87][0] = 1;	M_pattern[5][87][1] = 1;	M_pattern[5][87][2] = 1;
	M_pattern[5][87][3] = 0;	M_pattern[5][87][4] = 1;	M_pattern[5][87][5] = 0;
	M_pattern[5][87][6] = 1;	M_pattern[5][87][7] = 0;	M_pattern[5][87][8] = 0;


	M_pattern[5][88][0] = 1;	M_pattern[5][88][1] = 1;	M_pattern[5][88][2] = 1;
	M_pattern[5][88][3] = 0;	M_pattern[5][88][4] = 1;	M_pattern[5][88][5] = 0;
	M_pattern[5][88][6] = 1;	M_pattern[5][88][7] = 0;	M_pattern[5][88][8] = 1;


	M_pattern[5][89][0] = 1;	M_pattern[5][89][1] = 1;	M_pattern[5][89][2] = 1;
	M_pattern[5][89][3] = 0;	M_pattern[5][89][4] = 1;	M_pattern[5][89][5] = 1;
	M_pattern[5][89][6] = 1;	M_pattern[5][89][7] = 0;	M_pattern[5][89][8] = 0;


	M_pattern[5][90][0] = 1;	M_pattern[5][90][1] = 1;	M_pattern[5][90][2] = 1;
	M_pattern[5][90][3] = 0;	M_pattern[5][90][4] = 1;	M_pattern[5][90][5] = 1;
	M_pattern[5][90][6] = 1;	M_pattern[5][90][7] = 0;	M_pattern[5][90][8] = 1;


	M_pattern[5][91][0] = 1;	M_pattern[5][91][1] = 1;	M_pattern[5][91][2] = 0;
	M_pattern[5][91][3] = 0;	M_pattern[5][91][4] = 1;	M_pattern[5][91][5] = 0;
	M_pattern[5][91][6] = 1;	M_pattern[5][91][7] = 1;	M_pattern[5][91][8] = 1;


	M_pattern[5][92][0] = 1;	M_pattern[5][92][1] = 1;	M_pattern[5][92][2] = 0;
	M_pattern[5][92][3] = 0;	M_pattern[5][92][4] = 1;	M_pattern[5][92][5] = 1;
	M_pattern[5][92][6] = 1;	M_pattern[5][92][7] = 1;	M_pattern[5][92][8] = 0;


	M_pattern[5][93][0] = 1;	M_pattern[5][93][1] = 1;	M_pattern[5][93][2] = 0;
	M_pattern[5][93][3] = 0;	M_pattern[5][93][4] = 1;	M_pattern[5][93][5] = 1;
	M_pattern[5][93][6] = 1;	M_pattern[5][93][7] = 1;	M_pattern[5][93][8] = 1;


	M_pattern[5][94][0] = 1;	M_pattern[5][94][1] = 1;	M_pattern[5][94][2] = 1;
	M_pattern[5][94][3] = 0;	M_pattern[5][94][4] = 1;	M_pattern[5][94][5] = 0;
	M_pattern[5][94][6] = 1;	M_pattern[5][94][7] = 1;	M_pattern[5][94][8] = 0;


	M_pattern[5][95][0] = 1;	M_pattern[5][95][1] = 1;	M_pattern[5][95][2] = 1;
	M_pattern[5][95][3] = 0;	M_pattern[5][95][4] = 1;	M_pattern[5][95][5] = 0;
	M_pattern[5][95][6] = 1;	M_pattern[5][95][7] = 1;	M_pattern[5][95][8] = 1;


	M_pattern[5][96][0] = 1;	M_pattern[5][96][1] = 1;	M_pattern[5][96][2] = 1;
	M_pattern[5][96][3] = 0;	M_pattern[5][96][4] = 1;	M_pattern[5][96][5] = 1;
	M_pattern[5][96][6] = 1;	M_pattern[5][96][7] = 1;	M_pattern[5][96][8] = 0;


	M_pattern[5][97][0] = 1;	M_pattern[5][97][1] = 1;	M_pattern[5][97][2] = 1;
	M_pattern[5][97][3] = 0;	M_pattern[5][97][4] = 1;	M_pattern[5][97][5] = 1;
	M_pattern[5][97][6] = 1;	M_pattern[5][97][7] = 1;	M_pattern[5][97][8] = 1;


	M_pattern[5][98][0] = 1;	M_pattern[5][98][1] = 1;	M_pattern[5][98][2] = 0;
	M_pattern[5][98][3] = 1;	M_pattern[5][98][4] = 1;	M_pattern[5][98][5] = 0;
	M_pattern[5][98][6] = 1;	M_pattern[5][98][7] = 0;	M_pattern[5][98][8] = 1;


	M_pattern[5][99][0] = 1;	M_pattern[5][99][1] = 1;	M_pattern[5][99][2] = 0;
	M_pattern[5][99][3] = 1;	M_pattern[5][99][4] = 1;	M_pattern[5][99][5] = 1;
	M_pattern[5][99][6] = 1;	M_pattern[5][99][7] = 0;	M_pattern[5][99][8] = 0;


	M_pattern[5][100][0] = 1;	M_pattern[5][100][1] = 1;	M_pattern[5][100][2] = 0;
	M_pattern[5][100][3] = 1;	M_pattern[5][100][4] = 1;	M_pattern[5][100][5] = 1;
	M_pattern[5][100][6] = 1;	M_pattern[5][100][7] = 0;	M_pattern[5][100][8] = 1;


	M_pattern[5][101][0] = 1;	M_pattern[5][101][1] = 1;	M_pattern[5][101][2] = 1;
	M_pattern[5][101][3] = 1;	M_pattern[5][101][4] = 1;	M_pattern[5][101][5] = 0;
	M_pattern[5][101][6] = 1;	M_pattern[5][101][7] = 0;	M_pattern[5][101][8] = 0;


	M_pattern[5][102][0] = 1;	M_pattern[5][102][1] = 1;	M_pattern[5][102][2] = 1;
	M_pattern[5][102][3] = 1;	M_pattern[5][102][4] = 1;	M_pattern[5][102][5] = 0;
	M_pattern[5][102][6] = 1;	M_pattern[5][102][7] = 0;	M_pattern[5][102][8] = 1;


	M_pattern[5][103][0] = 1;	M_pattern[5][103][1] = 1;	M_pattern[5][103][2] = 1;
	M_pattern[5][103][3] = 1;	M_pattern[5][103][4] = 1;	M_pattern[5][103][5] = 1;
	M_pattern[5][103][6] = 1;	M_pattern[5][103][7] = 0;	M_pattern[5][103][8] = 0;


	M_pattern[5][104][0] = 1;	M_pattern[5][104][1] = 1;	M_pattern[5][104][2] = 1;
	M_pattern[5][104][3] = 1;	M_pattern[5][104][4] = 1;	M_pattern[5][104][5] = 1;
	M_pattern[5][104][6] = 1;	M_pattern[5][104][7] = 0;	M_pattern[5][104][8] = 1;


	M_pattern[5][105][0] = 1;	M_pattern[5][105][1] = 1;	M_pattern[5][105][2] = 0;
	M_pattern[5][105][3] = 1;	M_pattern[5][105][4] = 1;	M_pattern[5][105][5] = 0;
	M_pattern[5][105][6] = 1;	M_pattern[5][105][7] = 1;	M_pattern[5][105][8] = 1;


	M_pattern[5][106][0] = 1;	M_pattern[5][106][1] = 1;	M_pattern[5][106][2] = 0;
	M_pattern[5][106][3] = 1;	M_pattern[5][106][4] = 1;	M_pattern[5][106][5] = 1;
	M_pattern[5][106][6] = 1;	M_pattern[5][106][7] = 1;	M_pattern[5][106][8] = 0;


	M_pattern[5][107][0] = 1;	M_pattern[5][107][1] = 1;	M_pattern[5][107][2] = 0;
	M_pattern[5][107][3] = 1;	M_pattern[5][107][4] = 1;	M_pattern[5][107][5] = 1;
	M_pattern[5][107][6] = 1;	M_pattern[5][107][7] = 1;	M_pattern[5][107][8] = 1;


	M_pattern[5][108][0] = 1;	M_pattern[5][108][1] = 1;	M_pattern[5][108][2] = 1;
	M_pattern[5][108][3] = 1;	M_pattern[5][108][4] = 1;	M_pattern[5][108][5] = 0;
	M_pattern[5][108][6] = 1;	M_pattern[5][108][7] = 1;	M_pattern[5][108][8] = 0;


	M_pattern[5][109][0] = 1;	M_pattern[5][109][1] = 1;	M_pattern[5][109][2] = 1;
	M_pattern[5][109][3] = 1;	M_pattern[5][109][4] = 1;	M_pattern[5][109][5] = 0;
	M_pattern[5][109][6] = 1;	M_pattern[5][109][7] = 1;	M_pattern[5][109][8] = 1;


	M_pattern[5][110][0] = 1;	M_pattern[5][110][1] = 1;	M_pattern[5][110][2] = 1;
	M_pattern[5][110][3] = 1;	M_pattern[5][110][4] = 1;	M_pattern[5][110][5] = 1;
	M_pattern[5][110][6] = 1;	M_pattern[5][110][7] = 1;	M_pattern[5][110][8] = 0;


	M_pattern[5][111][0] = 1;	M_pattern[5][111][1] = 1;	M_pattern[5][111][2] = 1;
	M_pattern[5][111][3] = 1;	M_pattern[5][111][4] = 1;	M_pattern[5][111][5] = 1;
	M_pattern[5][111][6] = 1;	M_pattern[5][111][7] = 1;	M_pattern[5][111][8] = 1;


	M_pattern[5][112][0] = 0;	M_pattern[5][112][1] = 0;	M_pattern[5][112][2] = 1;
	M_pattern[5][112][3] = 0;	M_pattern[5][112][4] = 1;	M_pattern[5][112][5] = 0;
	M_pattern[5][112][6] = 1;	M_pattern[5][112][7] = 0;	M_pattern[5][112][8] = 1;


	M_pattern[5][113][0] = 0;	M_pattern[5][113][1] = 1;	M_pattern[5][113][2] = 0;
	M_pattern[5][113][3] = 0;	M_pattern[5][113][4] = 1;	M_pattern[5][113][5] = 0;
	M_pattern[5][113][6] = 1;	M_pattern[5][113][7] = 0;	M_pattern[5][113][8] = 1;


	M_pattern[5][114][0] = 0;	M_pattern[5][114][1] = 1;	M_pattern[5][114][2] = 1;
	M_pattern[5][114][3] = 0;	M_pattern[5][114][4] = 1;	M_pattern[5][114][5] = 0;
	M_pattern[5][114][6] = 1;	M_pattern[5][114][7] = 0;	M_pattern[5][114][8] = 1;


	M_pattern[5][115][0] = 1;	M_pattern[5][115][1] = 0;	M_pattern[5][115][2] = 0;
	M_pattern[5][115][3] = 0;	M_pattern[5][115][4] = 1;	M_pattern[5][115][5] = 0;
	M_pattern[5][115][6] = 1;	M_pattern[5][115][7] = 0;	M_pattern[5][115][8] = 1;


	M_pattern[5][116][0] = 1;	M_pattern[5][116][1] = 0;	M_pattern[5][116][2] = 1;
	M_pattern[5][116][3] = 0;	M_pattern[5][116][4] = 1;	M_pattern[5][116][5] = 0;
	M_pattern[5][116][6] = 1;	M_pattern[5][116][7] = 0;	M_pattern[5][116][8] = 1;


	M_pattern[5][117][0] = 1;	M_pattern[5][117][1] = 1;	M_pattern[5][117][2] = 0;
	M_pattern[5][117][3] = 0;	M_pattern[5][117][4] = 1;	M_pattern[5][117][5] = 0;
	M_pattern[5][117][6] = 1;	M_pattern[5][117][7] = 0;	M_pattern[5][117][8] = 1;


	M_pattern[5][118][0] = 1;	M_pattern[5][118][1] = 1;	M_pattern[5][118][2] = 1;
	M_pattern[5][118][3] = 0;	M_pattern[5][118][4] = 1;	M_pattern[5][118][5] = 0;
	M_pattern[5][118][6] = 1;	M_pattern[5][118][7] = 0;	M_pattern[5][118][8] = 1;


	M_pattern[5][119][0] = 0;	M_pattern[5][119][1] = 0;	M_pattern[5][119][2] = 1;
	M_pattern[5][119][3] = 0;	M_pattern[5][119][4] = 1;	M_pattern[5][119][5] = 0;
	M_pattern[5][119][6] = 1;	M_pattern[5][119][7] = 1;	M_pattern[5][119][8] = 1;


	M_pattern[5][120][0] = 0;	M_pattern[5][120][1] = 1;	M_pattern[5][120][2] = 0;
	M_pattern[5][120][3] = 0;	M_pattern[5][120][4] = 1;	M_pattern[5][120][5] = 0;
	M_pattern[5][120][6] = 1;	M_pattern[5][120][7] = 1;	M_pattern[5][120][8] = 1;


	M_pattern[5][121][0] = 0;	M_pattern[5][121][1] = 1;	M_pattern[5][121][2] = 1;
	M_pattern[5][121][3] = 0;	M_pattern[5][121][4] = 1;	M_pattern[5][121][5] = 0;
	M_pattern[5][121][6] = 1;	M_pattern[5][121][7] = 1;	M_pattern[5][121][8] = 1;


	M_pattern[5][122][0] = 1;	M_pattern[5][122][1] = 0;	M_pattern[5][122][2] = 0;
	M_pattern[5][122][3] = 0;	M_pattern[5][122][4] = 1;	M_pattern[5][122][5] = 0;
	M_pattern[5][122][6] = 1;	M_pattern[5][122][7] = 1;	M_pattern[5][122][8] = 1;


	M_pattern[5][123][0] = 1;	M_pattern[5][123][1] = 0;	M_pattern[5][123][2] = 1;
	M_pattern[5][123][3] = 0;	M_pattern[5][123][4] = 1;	M_pattern[5][123][5] = 0;
	M_pattern[5][123][6] = 1;	M_pattern[5][123][7] = 1;	M_pattern[5][123][8] = 1;


	M_pattern[5][124][0] = 1;	M_pattern[5][124][1] = 1;	M_pattern[5][124][2] = 0;
	M_pattern[5][124][3] = 0;	M_pattern[5][124][4] = 1;	M_pattern[5][124][5] = 0;
	M_pattern[5][124][6] = 1;	M_pattern[5][124][7] = 1;	M_pattern[5][124][8] = 1;


	M_pattern[5][125][0] = 1;	M_pattern[5][125][1] = 1;	M_pattern[5][125][2] = 1;
	M_pattern[5][125][3] = 0;	M_pattern[5][125][4] = 1;	M_pattern[5][125][5] = 0;
	M_pattern[5][125][6] = 1;	M_pattern[5][125][7] = 1;	M_pattern[5][125][8] = 1;


	M_pattern[5][126][0] = 0;	M_pattern[5][126][1] = 0;	M_pattern[5][126][2] = 1;
	M_pattern[5][126][3] = 0;	M_pattern[5][126][4] = 1;	M_pattern[5][126][5] = 1;
	M_pattern[5][126][6] = 1;	M_pattern[5][126][7] = 0;	M_pattern[5][126][8] = 1;


	M_pattern[5][127][0] = 0;	M_pattern[5][127][1] = 1;	M_pattern[5][127][2] = 0;
	M_pattern[5][127][3] = 0;	M_pattern[5][127][4] = 1;	M_pattern[5][127][5] = 1;
	M_pattern[5][127][6] = 1;	M_pattern[5][127][7] = 0;	M_pattern[5][127][8] = 1;


	M_pattern[5][128][0] = 0;	M_pattern[5][128][1] = 1;	M_pattern[5][128][2] = 1;
	M_pattern[5][128][3] = 0;	M_pattern[5][128][4] = 1;	M_pattern[5][128][5] = 1;
	M_pattern[5][128][6] = 1;	M_pattern[5][128][7] = 0;	M_pattern[5][128][8] = 1;


	M_pattern[5][129][0] = 1;	M_pattern[5][129][1] = 0;	M_pattern[5][129][2] = 0;
	M_pattern[5][129][3] = 0;	M_pattern[5][129][4] = 1;	M_pattern[5][129][5] = 1;
	M_pattern[5][129][6] = 1;	M_pattern[5][129][7] = 0;	M_pattern[5][129][8] = 1;


	M_pattern[5][130][0] = 1;	M_pattern[5][130][1] = 0;	M_pattern[5][130][2] = 1;
	M_pattern[5][130][3] = 0;	M_pattern[5][130][4] = 1;	M_pattern[5][130][5] = 1;
	M_pattern[5][130][6] = 1;	M_pattern[5][130][7] = 0;	M_pattern[5][130][8] = 1;


	M_pattern[5][131][0] = 1;	M_pattern[5][131][1] = 1;	M_pattern[5][131][2] = 0;
	M_pattern[5][131][3] = 0;	M_pattern[5][131][4] = 1;	M_pattern[5][131][5] = 1;
	M_pattern[5][131][6] = 1;	M_pattern[5][131][7] = 0;	M_pattern[5][131][8] = 1;


	M_pattern[5][132][0] = 1;	M_pattern[5][132][1] = 1;	M_pattern[5][132][2] = 1;
	M_pattern[5][132][3] = 0;	M_pattern[5][132][4] = 1;	M_pattern[5][132][5] = 1;
	M_pattern[5][132][6] = 1;	M_pattern[5][132][7] = 0;	M_pattern[5][132][8] = 1;


	M_pattern[5][133][0] = 0;	M_pattern[5][133][1] = 0;	M_pattern[5][133][2] = 1;
	M_pattern[5][133][3] = 0;	M_pattern[5][133][4] = 1;	M_pattern[5][133][5] = 1;
	M_pattern[5][133][6] = 1;	M_pattern[5][133][7] = 1;	M_pattern[5][133][8] = 1;


	M_pattern[5][134][0] = 0;	M_pattern[5][134][1] = 1;	M_pattern[5][134][2] = 0;
	M_pattern[5][134][3] = 0;	M_pattern[5][134][4] = 1;	M_pattern[5][134][5] = 1;
	M_pattern[5][134][6] = 1;	M_pattern[5][134][7] = 1;	M_pattern[5][134][8] = 1;


	M_pattern[5][135][0] = 0;	M_pattern[5][135][1] = 1;	M_pattern[5][135][2] = 1;
	M_pattern[5][135][3] = 0;	M_pattern[5][135][4] = 1;	M_pattern[5][135][5] = 1;
	M_pattern[5][135][6] = 1;	M_pattern[5][135][7] = 1;	M_pattern[5][135][8] = 1;


	M_pattern[5][136][0] = 1;	M_pattern[5][136][1] = 0;	M_pattern[5][136][2] = 0;
	M_pattern[5][136][3] = 0;	M_pattern[5][136][4] = 1;	M_pattern[5][136][5] = 1;
	M_pattern[5][136][6] = 1;	M_pattern[5][136][7] = 1;	M_pattern[5][136][8] = 1;


	M_pattern[5][137][0] = 1;	M_pattern[5][137][1] = 0;	M_pattern[5][137][2] = 1;
	M_pattern[5][137][3] = 0;	M_pattern[5][137][4] = 1;	M_pattern[5][137][5] = 1;
	M_pattern[5][137][6] = 1;	M_pattern[5][137][7] = 1;	M_pattern[5][137][8] = 1;


	M_pattern[5][138][0] = 1;	M_pattern[5][138][1] = 1;	M_pattern[5][138][2] = 0;
	M_pattern[5][138][3] = 0;	M_pattern[5][138][4] = 1;	M_pattern[5][138][5] = 1;
	M_pattern[5][138][6] = 1;	M_pattern[5][138][7] = 1;	M_pattern[5][138][8] = 1;


	M_pattern[5][139][0] = 1;	M_pattern[5][139][1] = 1;	M_pattern[5][139][2] = 1;
	M_pattern[5][139][3] = 0;	M_pattern[5][139][4] = 1;	M_pattern[5][139][5] = 1;
	M_pattern[5][139][6] = 1;	M_pattern[5][139][7] = 1;	M_pattern[5][139][8] = 1;


	M_pattern[5][140][0] = 0;	M_pattern[5][140][1] = 0;	M_pattern[5][140][2] = 1;
	M_pattern[5][140][3] = 1;	M_pattern[5][140][4] = 1;	M_pattern[5][140][5] = 0;
	M_pattern[5][140][6] = 1;	M_pattern[5][140][7] = 0;	M_pattern[5][140][8] = 1;


	M_pattern[5][141][0] = 0;	M_pattern[5][141][1] = 1;	M_pattern[5][141][2] = 0;
	M_pattern[5][141][3] = 1;	M_pattern[5][141][4] = 1;	M_pattern[5][141][5] = 0;
	M_pattern[5][141][6] = 1;	M_pattern[5][141][7] = 0;	M_pattern[5][141][8] = 1;


	M_pattern[5][142][0] = 0;	M_pattern[5][142][1] = 1;	M_pattern[5][142][2] = 1;
	M_pattern[5][142][3] = 1;	M_pattern[5][142][4] = 1;	M_pattern[5][142][5] = 0;
	M_pattern[5][142][6] = 1;	M_pattern[5][142][7] = 0;	M_pattern[5][142][8] = 1;


	M_pattern[5][143][0] = 1;	M_pattern[5][143][1] = 0;	M_pattern[5][143][2] = 0;
	M_pattern[5][143][3] = 1;	M_pattern[5][143][4] = 1;	M_pattern[5][143][5] = 0;
	M_pattern[5][143][6] = 1;	M_pattern[5][143][7] = 0;	M_pattern[5][143][8] = 1;


	M_pattern[5][144][0] = 1;	M_pattern[5][144][1] = 0;	M_pattern[5][144][2] = 1;
	M_pattern[5][144][3] = 1;	M_pattern[5][144][4] = 1;	M_pattern[5][144][5] = 0;
	M_pattern[5][144][6] = 1;	M_pattern[5][144][7] = 0;	M_pattern[5][144][8] = 1;


	M_pattern[5][145][0] = 1;	M_pattern[5][145][1] = 1;	M_pattern[5][145][2] = 0;
	M_pattern[5][145][3] = 1;	M_pattern[5][145][4] = 1;	M_pattern[5][145][5] = 0;
	M_pattern[5][145][6] = 1;	M_pattern[5][145][7] = 0;	M_pattern[5][145][8] = 1;


	M_pattern[5][146][0] = 1;	M_pattern[5][146][1] = 1;	M_pattern[5][146][2] = 1;
	M_pattern[5][146][3] = 1;	M_pattern[5][146][4] = 1;	M_pattern[5][146][5] = 0;
	M_pattern[5][146][6] = 1;	M_pattern[5][146][7] = 0;	M_pattern[5][146][8] = 1;


	M_pattern[5][147][0] = 0;	M_pattern[5][147][1] = 0;	M_pattern[5][147][2] = 1;
	M_pattern[5][147][3] = 1;	M_pattern[5][147][4] = 1;	M_pattern[5][147][5] = 0;
	M_pattern[5][147][6] = 1;	M_pattern[5][147][7] = 1;	M_pattern[5][147][8] = 1;


	M_pattern[5][148][0] = 0;	M_pattern[5][148][1] = 1;	M_pattern[5][148][2] = 0;
	M_pattern[5][148][3] = 1;	M_pattern[5][148][4] = 1;	M_pattern[5][148][5] = 0;
	M_pattern[5][148][6] = 1;	M_pattern[5][148][7] = 1;	M_pattern[5][148][8] = 1;


	M_pattern[5][149][0] = 0;	M_pattern[5][149][1] = 1;	M_pattern[5][149][2] = 1;
	M_pattern[5][149][3] = 1;	M_pattern[5][149][4] = 1;	M_pattern[5][149][5] = 0;
	M_pattern[5][149][6] = 1;	M_pattern[5][149][7] = 1;	M_pattern[5][149][8] = 1;


	M_pattern[5][150][0] = 1;	M_pattern[5][150][1] = 0;	M_pattern[5][150][2] = 0;
	M_pattern[5][150][3] = 1;	M_pattern[5][150][4] = 1;	M_pattern[5][150][5] = 0;
	M_pattern[5][150][6] = 1;	M_pattern[5][150][7] = 1;	M_pattern[5][150][8] = 1;


	M_pattern[5][151][0] = 1;	M_pattern[5][151][1] = 0;	M_pattern[5][151][2] = 1;
	M_pattern[5][151][3] = 1;	M_pattern[5][151][4] = 1;	M_pattern[5][151][5] = 0;
	M_pattern[5][151][6] = 1;	M_pattern[5][151][7] = 1;	M_pattern[5][151][8] = 1;


	M_pattern[5][152][0] = 1;	M_pattern[5][152][1] = 1;	M_pattern[5][152][2] = 0;
	M_pattern[5][152][3] = 1;	M_pattern[5][152][4] = 1;	M_pattern[5][152][5] = 0;
	M_pattern[5][152][6] = 1;	M_pattern[5][152][7] = 1;	M_pattern[5][152][8] = 1;


	M_pattern[5][153][0] = 1;	M_pattern[5][153][1] = 1;	M_pattern[5][153][2] = 1;
	M_pattern[5][153][3] = 1;	M_pattern[5][153][4] = 1;	M_pattern[5][153][5] = 0;
	M_pattern[5][153][6] = 1;	M_pattern[5][153][7] = 1;	M_pattern[5][153][8] = 1;


	M_pattern[5][154][0] = 0;	M_pattern[5][154][1] = 0;	M_pattern[5][154][2] = 1;
	M_pattern[5][154][3] = 1;	M_pattern[5][154][4] = 1;	M_pattern[5][154][5] = 1;
	M_pattern[5][154][6] = 1;	M_pattern[5][154][7] = 0;	M_pattern[5][154][8] = 1;


	M_pattern[5][155][0] = 0;	M_pattern[5][155][1] = 1;	M_pattern[5][155][2] = 0;
	M_pattern[5][155][3] = 1;	M_pattern[5][155][4] = 1;	M_pattern[5][155][5] = 1;
	M_pattern[5][155][6] = 1;	M_pattern[5][155][7] = 0;	M_pattern[5][155][8] = 1;


	M_pattern[5][156][0] = 0;	M_pattern[5][156][1] = 1;	M_pattern[5][156][2] = 1;
	M_pattern[5][156][3] = 1;	M_pattern[5][156][4] = 1;	M_pattern[5][156][5] = 1;
	M_pattern[5][156][6] = 1;	M_pattern[5][156][7] = 0;	M_pattern[5][156][8] = 1;


	M_pattern[5][157][0] = 1;	M_pattern[5][157][1] = 0;	M_pattern[5][157][2] = 0;
	M_pattern[5][157][3] = 1;	M_pattern[5][157][4] = 1;	M_pattern[5][157][5] = 1;
	M_pattern[5][157][6] = 1;	M_pattern[5][157][7] = 0;	M_pattern[5][157][8] = 1;


	M_pattern[5][158][0] = 1;	M_pattern[5][158][1] = 0;	M_pattern[5][158][2] = 1;
	M_pattern[5][158][3] = 1;	M_pattern[5][158][4] = 1;	M_pattern[5][158][5] = 1;
	M_pattern[5][158][6] = 1;	M_pattern[5][158][7] = 0;	M_pattern[5][158][8] = 1;


	M_pattern[5][159][0] = 1;	M_pattern[5][159][1] = 1;	M_pattern[5][159][2] = 0;
	M_pattern[5][159][3] = 1;	M_pattern[5][159][4] = 1;	M_pattern[5][159][5] = 1;
	M_pattern[5][159][6] = 1;	M_pattern[5][159][7] = 0;	M_pattern[5][159][8] = 1;


	M_pattern[5][160][0] = 1;	M_pattern[5][160][1] = 1;	M_pattern[5][160][2] = 1;
	M_pattern[5][160][3] = 1;	M_pattern[5][160][4] = 1;	M_pattern[5][160][5] = 1;
	M_pattern[5][160][6] = 1;	M_pattern[5][160][7] = 0;	M_pattern[5][160][8] = 1;


	M_pattern[5][161][0] = 0;	M_pattern[5][161][1] = 0;	M_pattern[5][161][2] = 1;
	M_pattern[5][161][3] = 1;	M_pattern[5][161][4] = 1;	M_pattern[5][161][5] = 1;
	M_pattern[5][161][6] = 1;	M_pattern[5][161][7] = 1;	M_pattern[5][161][8] = 1;


	M_pattern[5][162][0] = 0;	M_pattern[5][162][1] = 1;	M_pattern[5][162][2] = 0;
	M_pattern[5][162][3] = 1;	M_pattern[5][162][4] = 1;	M_pattern[5][162][5] = 1;
	M_pattern[5][162][6] = 1;	M_pattern[5][162][7] = 1;	M_pattern[5][162][8] = 1;


	M_pattern[5][163][0] = 0;	M_pattern[5][163][1] = 1;	M_pattern[5][163][2] = 1;
	M_pattern[5][163][3] = 1;	M_pattern[5][163][4] = 1;	M_pattern[5][163][5] = 1;
	M_pattern[5][163][6] = 1;	M_pattern[5][163][7] = 1;	M_pattern[5][163][8] = 1;


	M_pattern[5][164][0] = 1;	M_pattern[5][164][1] = 0;	M_pattern[5][164][2] = 0;
	M_pattern[5][164][3] = 1;	M_pattern[5][164][4] = 1;	M_pattern[5][164][5] = 1;
	M_pattern[5][164][6] = 1;	M_pattern[5][164][7] = 1;	M_pattern[5][164][8] = 1;


	M_pattern[5][165][0] = 1;	M_pattern[5][165][1] = 0;	M_pattern[5][165][2] = 1;
	M_pattern[5][165][3] = 1;	M_pattern[5][165][4] = 1;	M_pattern[5][165][5] = 1;
	M_pattern[5][165][6] = 1;	M_pattern[5][165][7] = 1;	M_pattern[5][165][8] = 1;


	M_pattern[5][166][0] = 1;	M_pattern[5][166][1] = 1;	M_pattern[5][166][2] = 0;
	M_pattern[5][166][3] = 1;	M_pattern[5][166][4] = 1;	M_pattern[5][166][5] = 1;
	M_pattern[5][166][6] = 1;	M_pattern[5][166][7] = 1;	M_pattern[5][166][8] = 1;


	M_pattern[5][167][0] = 1;	M_pattern[5][167][1] = 1;	M_pattern[5][167][2] = 1;
	M_pattern[5][167][3] = 1;	M_pattern[5][167][4] = 1;	M_pattern[5][167][5] = 1;
	M_pattern[5][167][6] = 1;	M_pattern[5][167][7] = 1;	M_pattern[5][167][8] = 1;


	M_pattern[5][168][0] = 0;	M_pattern[5][168][1] = 0;	M_pattern[5][168][2] = 1;
	M_pattern[5][168][3] = 0;	M_pattern[5][168][4] = 1;	M_pattern[5][168][5] = 0;
	M_pattern[5][168][6] = 1;	M_pattern[5][168][7] = 0;	M_pattern[5][168][8] = 1;


	M_pattern[5][169][0] = 0;	M_pattern[5][169][1] = 0;	M_pattern[5][169][2] = 1;
	M_pattern[5][169][3] = 1;	M_pattern[5][169][4] = 1;	M_pattern[5][169][5] = 0;
	M_pattern[5][169][6] = 0;	M_pattern[5][169][7] = 0;	M_pattern[5][169][8] = 1;


	M_pattern[5][170][0] = 0;	M_pattern[5][170][1] = 0;	M_pattern[5][170][2] = 1;
	M_pattern[5][170][3] = 1;	M_pattern[5][170][4] = 1;	M_pattern[5][170][5] = 0;
	M_pattern[5][170][6] = 1;	M_pattern[5][170][7] = 0;	M_pattern[5][170][8] = 1;


	M_pattern[5][171][0] = 1;	M_pattern[5][171][1] = 0;	M_pattern[5][171][2] = 1;
	M_pattern[5][171][3] = 0;	M_pattern[5][171][4] = 1;	M_pattern[5][171][5] = 0;
	M_pattern[5][171][6] = 0;	M_pattern[5][171][7] = 0;	M_pattern[5][171][8] = 1;


	M_pattern[5][172][0] = 1;	M_pattern[5][172][1] = 0;	M_pattern[5][172][2] = 1;
	M_pattern[5][172][3] = 0;	M_pattern[5][172][4] = 1;	M_pattern[5][172][5] = 0;
	M_pattern[5][172][6] = 1;	M_pattern[5][172][7] = 0;	M_pattern[5][172][8] = 1;


	M_pattern[5][173][0] = 1;	M_pattern[5][173][1] = 0;	M_pattern[5][173][2] = 1;
	M_pattern[5][173][3] = 1;	M_pattern[5][173][4] = 1;	M_pattern[5][173][5] = 0;
	M_pattern[5][173][6] = 0;	M_pattern[5][173][7] = 0;	M_pattern[5][173][8] = 1;


	M_pattern[5][174][0] = 1;	M_pattern[5][174][1] = 0;	M_pattern[5][174][2] = 1;
	M_pattern[5][174][3] = 1;	M_pattern[5][174][4] = 1;	M_pattern[5][174][5] = 0;
	M_pattern[5][174][6] = 1;	M_pattern[5][174][7] = 0;	M_pattern[5][174][8] = 1;


	M_pattern[5][175][0] = 0;	M_pattern[5][175][1] = 0;	M_pattern[5][175][2] = 1;
	M_pattern[5][175][3] = 0;	M_pattern[5][175][4] = 1;	M_pattern[5][175][5] = 0;
	M_pattern[5][175][6] = 1;	M_pattern[5][175][7] = 1;	M_pattern[5][175][8] = 1;


	M_pattern[5][176][0] = 0;	M_pattern[5][176][1] = 0;	M_pattern[5][176][2] = 1;
	M_pattern[5][176][3] = 1;	M_pattern[5][176][4] = 1;	M_pattern[5][176][5] = 0;
	M_pattern[5][176][6] = 0;	M_pattern[5][176][7] = 1;	M_pattern[5][176][8] = 1;


	M_pattern[5][177][0] = 0;	M_pattern[5][177][1] = 0;	M_pattern[5][177][2] = 1;
	M_pattern[5][177][3] = 1;	M_pattern[5][177][4] = 1;	M_pattern[5][177][5] = 0;
	M_pattern[5][177][6] = 1;	M_pattern[5][177][7] = 1;	M_pattern[5][177][8] = 1;


	M_pattern[5][178][0] = 1;	M_pattern[5][178][1] = 0;	M_pattern[5][178][2] = 1;
	M_pattern[5][178][3] = 0;	M_pattern[5][178][4] = 1;	M_pattern[5][178][5] = 0;
	M_pattern[5][178][6] = 0;	M_pattern[5][178][7] = 1;	M_pattern[5][178][8] = 1;


	M_pattern[5][179][0] = 1;	M_pattern[5][179][1] = 0;	M_pattern[5][179][2] = 1;
	M_pattern[5][179][3] = 0;	M_pattern[5][179][4] = 1;	M_pattern[5][179][5] = 0;
	M_pattern[5][179][6] = 1;	M_pattern[5][179][7] = 1;	M_pattern[5][179][8] = 1;


	M_pattern[5][180][0] = 1;	M_pattern[5][180][1] = 0;	M_pattern[5][180][2] = 1;
	M_pattern[5][180][3] = 1;	M_pattern[5][180][4] = 1;	M_pattern[5][180][5] = 0;
	M_pattern[5][180][6] = 0;	M_pattern[5][180][7] = 1;	M_pattern[5][180][8] = 1;


	M_pattern[5][181][0] = 1;	M_pattern[5][181][1] = 0;	M_pattern[5][181][2] = 1;
	M_pattern[5][181][3] = 1;	M_pattern[5][181][4] = 1;	M_pattern[5][181][5] = 0;
	M_pattern[5][181][6] = 1;	M_pattern[5][181][7] = 1;	M_pattern[5][181][8] = 1;


	M_pattern[5][182][0] = 0;	M_pattern[5][182][1] = 0;	M_pattern[5][182][2] = 1;
	M_pattern[5][182][3] = 0;	M_pattern[5][182][4] = 1;	M_pattern[5][182][5] = 1;
	M_pattern[5][182][6] = 1;	M_pattern[5][182][7] = 0;	M_pattern[5][182][8] = 1;


	M_pattern[5][183][0] = 0;	M_pattern[5][183][1] = 0;	M_pattern[5][183][2] = 1;
	M_pattern[5][183][3] = 1;	M_pattern[5][183][4] = 1;	M_pattern[5][183][5] = 1;
	M_pattern[5][183][6] = 0;	M_pattern[5][183][7] = 0;	M_pattern[5][183][8] = 1;


	M_pattern[5][184][0] = 0;	M_pattern[5][184][1] = 0;	M_pattern[5][184][2] = 1;
	M_pattern[5][184][3] = 1;	M_pattern[5][184][4] = 1;	M_pattern[5][184][5] = 1;
	M_pattern[5][184][6] = 1;	M_pattern[5][184][7] = 0;	M_pattern[5][184][8] = 1;


	M_pattern[5][185][0] = 1;	M_pattern[5][185][1] = 0;	M_pattern[5][185][2] = 1;
	M_pattern[5][185][3] = 0;	M_pattern[5][185][4] = 1;	M_pattern[5][185][5] = 1;
	M_pattern[5][185][6] = 0;	M_pattern[5][185][7] = 0;	M_pattern[5][185][8] = 1;


	M_pattern[5][186][0] = 1;	M_pattern[5][186][1] = 0;	M_pattern[5][186][2] = 1;
	M_pattern[5][186][3] = 0;	M_pattern[5][186][4] = 1;	M_pattern[5][186][5] = 1;
	M_pattern[5][186][6] = 1;	M_pattern[5][186][7] = 0;	M_pattern[5][186][8] = 1;


	M_pattern[5][187][0] = 1;	M_pattern[5][187][1] = 0;	M_pattern[5][187][2] = 1;
	M_pattern[5][187][3] = 1;	M_pattern[5][187][4] = 1;	M_pattern[5][187][5] = 1;
	M_pattern[5][187][6] = 0;	M_pattern[5][187][7] = 0;	M_pattern[5][187][8] = 1;


	M_pattern[5][188][0] = 1;	M_pattern[5][188][1] = 0;	M_pattern[5][188][2] = 1;
	M_pattern[5][188][3] = 1;	M_pattern[5][188][4] = 1;	M_pattern[5][188][5] = 1;
	M_pattern[5][188][6] = 1;	M_pattern[5][188][7] = 0;	M_pattern[5][188][8] = 1;


	M_pattern[5][189][0] = 0;	M_pattern[5][189][1] = 0;	M_pattern[5][189][2] = 1;
	M_pattern[5][189][3] = 0;	M_pattern[5][189][4] = 1;	M_pattern[5][189][5] = 1;
	M_pattern[5][189][6] = 1;	M_pattern[5][189][7] = 1;	M_pattern[5][189][8] = 1;


	M_pattern[5][190][0] = 0;	M_pattern[5][190][1] = 0;	M_pattern[5][190][2] = 1;
	M_pattern[5][190][3] = 1;	M_pattern[5][190][4] = 1;	M_pattern[5][190][5] = 1;
	M_pattern[5][190][6] = 0;	M_pattern[5][190][7] = 1;	M_pattern[5][190][8] = 1;


	M_pattern[5][191][0] = 0;	M_pattern[5][191][1] = 0;	M_pattern[5][191][2] = 1;
	M_pattern[5][191][3] = 1;	M_pattern[5][191][4] = 1;	M_pattern[5][191][5] = 1;
	M_pattern[5][191][6] = 1;	M_pattern[5][191][7] = 1;	M_pattern[5][191][8] = 1;


	M_pattern[5][192][0] = 1;	M_pattern[5][192][1] = 0;	M_pattern[5][192][2] = 1;
	M_pattern[5][192][3] = 0;	M_pattern[5][192][4] = 1;	M_pattern[5][192][5] = 1;
	M_pattern[5][192][6] = 0;	M_pattern[5][192][7] = 1;	M_pattern[5][192][8] = 1;


	M_pattern[5][193][0] = 1;	M_pattern[5][193][1] = 0;	M_pattern[5][193][2] = 1;
	M_pattern[5][193][3] = 0;	M_pattern[5][193][4] = 1;	M_pattern[5][193][5] = 1;
	M_pattern[5][193][6] = 1;	M_pattern[5][193][7] = 1;	M_pattern[5][193][8] = 1;


	M_pattern[5][194][0] = 1;	M_pattern[5][194][1] = 0;	M_pattern[5][194][2] = 1;
	M_pattern[5][194][3] = 1;	M_pattern[5][194][4] = 1;	M_pattern[5][194][5] = 1;
	M_pattern[5][194][6] = 0;	M_pattern[5][194][7] = 1;	M_pattern[5][194][8] = 1;


	M_pattern[5][195][0] = 1;	M_pattern[5][195][1] = 0;	M_pattern[5][195][2] = 1;
	M_pattern[5][195][3] = 1;	M_pattern[5][195][4] = 1;	M_pattern[5][195][5] = 1;
	M_pattern[5][195][6] = 1;	M_pattern[5][195][7] = 1;	M_pattern[5][195][8] = 1;


	M_pattern[5][196][0] = 0;	M_pattern[5][196][1] = 1;	M_pattern[5][196][2] = 1;
	M_pattern[5][196][3] = 0;	M_pattern[5][196][4] = 1;	M_pattern[5][196][5] = 0;
	M_pattern[5][196][6] = 1;	M_pattern[5][196][7] = 0;	M_pattern[5][196][8] = 1;


	M_pattern[5][197][0] = 0;	M_pattern[5][197][1] = 1;	M_pattern[5][197][2] = 1;
	M_pattern[5][197][3] = 1;	M_pattern[5][197][4] = 1;	M_pattern[5][197][5] = 0;
	M_pattern[5][197][6] = 0;	M_pattern[5][197][7] = 0;	M_pattern[5][197][8] = 1;


	M_pattern[5][198][0] = 0;	M_pattern[5][198][1] = 1;	M_pattern[5][198][2] = 1;
	M_pattern[5][198][3] = 1;	M_pattern[5][198][4] = 1;	M_pattern[5][198][5] = 0;
	M_pattern[5][198][6] = 1;	M_pattern[5][198][7] = 0;	M_pattern[5][198][8] = 1;


	M_pattern[5][199][0] = 1;	M_pattern[5][199][1] = 1;	M_pattern[5][199][2] = 1;
	M_pattern[5][199][3] = 0;	M_pattern[5][199][4] = 1;	M_pattern[5][199][5] = 0;
	M_pattern[5][199][6] = 0;	M_pattern[5][199][7] = 0;	M_pattern[5][199][8] = 1;


	M_pattern[5][200][0] = 1;	M_pattern[5][200][1] = 1;	M_pattern[5][200][2] = 1;
	M_pattern[5][200][3] = 0;	M_pattern[5][200][4] = 1;	M_pattern[5][200][5] = 0;
	M_pattern[5][200][6] = 1;	M_pattern[5][200][7] = 0;	M_pattern[5][200][8] = 1;


	M_pattern[5][201][0] = 1;	M_pattern[5][201][1] = 1;	M_pattern[5][201][2] = 1;
	M_pattern[5][201][3] = 1;	M_pattern[5][201][4] = 1;	M_pattern[5][201][5] = 0;
	M_pattern[5][201][6] = 0;	M_pattern[5][201][7] = 0;	M_pattern[5][201][8] = 1;


	M_pattern[5][202][0] = 1;	M_pattern[5][202][1] = 1;	M_pattern[5][202][2] = 1;
	M_pattern[5][202][3] = 1;	M_pattern[5][202][4] = 1;	M_pattern[5][202][5] = 0;
	M_pattern[5][202][6] = 1;	M_pattern[5][202][7] = 0;	M_pattern[5][202][8] = 1;


	M_pattern[5][203][0] = 0;	M_pattern[5][203][1] = 1;	M_pattern[5][203][2] = 1;
	M_pattern[5][203][3] = 0;	M_pattern[5][203][4] = 1;	M_pattern[5][203][5] = 0;
	M_pattern[5][203][6] = 1;	M_pattern[5][203][7] = 1;	M_pattern[5][203][8] = 1;


	M_pattern[5][204][0] = 0;	M_pattern[5][204][1] = 1;	M_pattern[5][204][2] = 1;
	M_pattern[5][204][3] = 1;	M_pattern[5][204][4] = 1;	M_pattern[5][204][5] = 0;
	M_pattern[5][204][6] = 0;	M_pattern[5][204][7] = 1;	M_pattern[5][204][8] = 1;


	M_pattern[5][205][0] = 0;	M_pattern[5][205][1] = 1;	M_pattern[5][205][2] = 1;
	M_pattern[5][205][3] = 1;	M_pattern[5][205][4] = 1;	M_pattern[5][205][5] = 0;
	M_pattern[5][205][6] = 1;	M_pattern[5][205][7] = 1;	M_pattern[5][205][8] = 1;


	M_pattern[5][206][0] = 1;	M_pattern[5][206][1] = 1;	M_pattern[5][206][2] = 1;
	M_pattern[5][206][3] = 0;	M_pattern[5][206][4] = 1;	M_pattern[5][206][5] = 0;
	M_pattern[5][206][6] = 0;	M_pattern[5][206][7] = 1;	M_pattern[5][206][8] = 1;


	M_pattern[5][207][0] = 1;	M_pattern[5][207][1] = 1;	M_pattern[5][207][2] = 1;
	M_pattern[5][207][3] = 0;	M_pattern[5][207][4] = 1;	M_pattern[5][207][5] = 0;
	M_pattern[5][207][6] = 1;	M_pattern[5][207][7] = 1;	M_pattern[5][207][8] = 1;


	M_pattern[5][208][0] = 1;	M_pattern[5][208][1] = 1;	M_pattern[5][208][2] = 1;
	M_pattern[5][208][3] = 1;	M_pattern[5][208][4] = 1;	M_pattern[5][208][5] = 0;
	M_pattern[5][208][6] = 0;	M_pattern[5][208][7] = 1;	M_pattern[5][208][8] = 1;


	M_pattern[5][209][0] = 1;	M_pattern[5][209][1] = 1;	M_pattern[5][209][2] = 1;
	M_pattern[5][209][3] = 1;	M_pattern[5][209][4] = 1;	M_pattern[5][209][5] = 0;
	M_pattern[5][209][6] = 1;	M_pattern[5][209][7] = 1;	M_pattern[5][209][8] = 1;


	M_pattern[5][210][0] = 0;	M_pattern[5][210][1] = 1;	M_pattern[5][210][2] = 1;
	M_pattern[5][210][3] = 0;	M_pattern[5][210][4] = 1;	M_pattern[5][210][5] = 1;
	M_pattern[5][210][6] = 1;	M_pattern[5][210][7] = 0;	M_pattern[5][210][8] = 1;


	M_pattern[5][211][0] = 0;	M_pattern[5][211][1] = 1;	M_pattern[5][211][2] = 1;
	M_pattern[5][211][3] = 1;	M_pattern[5][211][4] = 1;	M_pattern[5][211][5] = 1;
	M_pattern[5][211][6] = 0;	M_pattern[5][211][7] = 0;	M_pattern[5][211][8] = 1;


	M_pattern[5][212][0] = 0;	M_pattern[5][212][1] = 1;	M_pattern[5][212][2] = 1;
	M_pattern[5][212][3] = 1;	M_pattern[5][212][4] = 1;	M_pattern[5][212][5] = 1;
	M_pattern[5][212][6] = 1;	M_pattern[5][212][7] = 0;	M_pattern[5][212][8] = 1;


	M_pattern[5][213][0] = 1;	M_pattern[5][213][1] = 1;	M_pattern[5][213][2] = 1;
	M_pattern[5][213][3] = 0;	M_pattern[5][213][4] = 1;	M_pattern[5][213][5] = 1;
	M_pattern[5][213][6] = 0;	M_pattern[5][213][7] = 0;	M_pattern[5][213][8] = 1;


	M_pattern[5][214][0] = 1;	M_pattern[5][214][1] = 1;	M_pattern[5][214][2] = 1;
	M_pattern[5][214][3] = 0;	M_pattern[5][214][4] = 1;	M_pattern[5][214][5] = 1;
	M_pattern[5][214][6] = 1;	M_pattern[5][214][7] = 0;	M_pattern[5][214][8] = 1;


	M_pattern[5][215][0] = 1;	M_pattern[5][215][1] = 1;	M_pattern[5][215][2] = 1;
	M_pattern[5][215][3] = 1;	M_pattern[5][215][4] = 1;	M_pattern[5][215][5] = 1;
	M_pattern[5][215][6] = 0;	M_pattern[5][215][7] = 0;	M_pattern[5][215][8] = 1;


	M_pattern[5][216][0] = 1;	M_pattern[5][216][1] = 1;	M_pattern[5][216][2] = 1;
	M_pattern[5][216][3] = 1;	M_pattern[5][216][4] = 1;	M_pattern[5][216][5] = 1;
	M_pattern[5][216][6] = 1;	M_pattern[5][216][7] = 0;	M_pattern[5][216][8] = 1;


	M_pattern[5][217][0] = 0;	M_pattern[5][217][1] = 1;	M_pattern[5][217][2] = 1;
	M_pattern[5][217][3] = 0;	M_pattern[5][217][4] = 1;	M_pattern[5][217][5] = 1;
	M_pattern[5][217][6] = 1;	M_pattern[5][217][7] = 1;	M_pattern[5][217][8] = 1;


	M_pattern[5][218][0] = 0;	M_pattern[5][218][1] = 1;	M_pattern[5][218][2] = 1;
	M_pattern[5][218][3] = 1;	M_pattern[5][218][4] = 1;	M_pattern[5][218][5] = 1;
	M_pattern[5][218][6] = 0;	M_pattern[5][218][7] = 1;	M_pattern[5][218][8] = 1;


	M_pattern[5][219][0] = 0;	M_pattern[5][219][1] = 1;	M_pattern[5][219][2] = 1;
	M_pattern[5][219][3] = 1;	M_pattern[5][219][4] = 1;	M_pattern[5][219][5] = 1;
	M_pattern[5][219][6] = 1;	M_pattern[5][219][7] = 1;	M_pattern[5][219][8] = 1;


	M_pattern[5][220][0] = 1;	M_pattern[5][220][1] = 1;	M_pattern[5][220][2] = 1;
	M_pattern[5][220][3] = 0;	M_pattern[5][220][4] = 1;	M_pattern[5][220][5] = 1;
	M_pattern[5][220][6] = 0;	M_pattern[5][220][7] = 1;	M_pattern[5][220][8] = 1;


	M_pattern[5][221][0] = 1;	M_pattern[5][221][1] = 1;	M_pattern[5][221][2] = 1;
	M_pattern[5][221][3] = 0;	M_pattern[5][221][4] = 1;	M_pattern[5][221][5] = 1;
	M_pattern[5][221][6] = 1;	M_pattern[5][221][7] = 1;	M_pattern[5][221][8] = 1;


	M_pattern[5][222][0] = 1;	M_pattern[5][222][1] = 1;	M_pattern[5][222][2] = 1;
	M_pattern[5][222][3] = 1;	M_pattern[5][222][4] = 1;	M_pattern[5][222][5] = 1;
	M_pattern[5][222][6] = 0;	M_pattern[5][222][7] = 1;	M_pattern[5][222][8] = 1;


	M_pattern[5][223][0] = 1;	M_pattern[5][223][1] = 1;	M_pattern[5][223][2] = 1;
	M_pattern[5][223][3] = 1;	M_pattern[5][223][4] = 1;	M_pattern[5][223][5] = 1;
	M_pattern[5][223][6] = 1;	M_pattern[5][223][7] = 1;	M_pattern[5][223][8] = 1;





	M_pattern[6][0][0] = 0;	M_pattern[6][0][1] = 1;	M_pattern[6][0][2] = 0;
	M_pattern[6][0][3] = 0;	M_pattern[6][0][4] = 1;	M_pattern[6][0][5] = 1;
	M_pattern[6][0][6] = 1;	M_pattern[6][0][7] = 0;	M_pattern[6][0][8] = 0;


	M_pattern[6][1][0] = 0;	M_pattern[6][1][1] = 1;	M_pattern[6][1][2] = 0;
	M_pattern[6][1][3] = 0;	M_pattern[6][1][4] = 1;	M_pattern[6][1][5] = 1;
	M_pattern[6][1][6] = 1;	M_pattern[6][1][7] = 0;	M_pattern[6][1][8] = 1;


	M_pattern[6][2][0] = 1;	M_pattern[6][2][1] = 1;	M_pattern[6][2][2] = 0;
	M_pattern[6][2][3] = 0;	M_pattern[6][2][4] = 1;	M_pattern[6][2][5] = 1;
	M_pattern[6][2][6] = 1;	M_pattern[6][2][7] = 0;	M_pattern[6][2][8] = 0;


	M_pattern[6][3][0] = 1;	M_pattern[6][3][1] = 1;	M_pattern[6][3][2] = 0;
	M_pattern[6][3][3] = 0;	M_pattern[6][3][4] = 1;	M_pattern[6][3][5] = 1;
	M_pattern[6][3][6] = 1;	M_pattern[6][3][7] = 0;	M_pattern[6][3][8] = 1;


	M_pattern[6][4][0] = 0;	M_pattern[6][4][1] = 1;	M_pattern[6][4][2] = 0;
	M_pattern[6][4][3] = 1;	M_pattern[6][4][4] = 1;	M_pattern[6][4][5] = 0;
	M_pattern[6][4][6] = 0;	M_pattern[6][4][7] = 0;	M_pattern[6][4][8] = 1;


	M_pattern[6][5][0] = 0;	M_pattern[6][5][1] = 1;	M_pattern[6][5][2] = 0;
	M_pattern[6][5][3] = 1;	M_pattern[6][5][4] = 1;	M_pattern[6][5][5] = 0;
	M_pattern[6][5][6] = 1;	M_pattern[6][5][7] = 0;	M_pattern[6][5][8] = 1;


	M_pattern[6][6][0] = 0;	M_pattern[6][6][1] = 1;	M_pattern[6][6][2] = 1;
	M_pattern[6][6][3] = 1;	M_pattern[6][6][4] = 1;	M_pattern[6][6][5] = 0;
	M_pattern[6][6][6] = 0;	M_pattern[6][6][7] = 0;	M_pattern[6][6][8] = 1;


	M_pattern[6][7][0] = 0;	M_pattern[6][7][1] = 1;	M_pattern[6][7][2] = 1;
	M_pattern[6][7][3] = 1;	M_pattern[6][7][4] = 1;	M_pattern[6][7][5] = 0;
	M_pattern[6][7][6] = 1;	M_pattern[6][7][7] = 0;	M_pattern[6][7][8] = 1;


	M_pattern[6][8][0] = 0;	M_pattern[6][8][1] = 0;	M_pattern[6][8][2] = 1;
	M_pattern[6][8][3] = 1;	M_pattern[6][8][4] = 1;	M_pattern[6][8][5] = 0;
	M_pattern[6][8][6] = 0;	M_pattern[6][8][7] = 1;	M_pattern[6][8][8] = 0;


	M_pattern[6][9][0] = 0;	M_pattern[6][9][1] = 0;	M_pattern[6][9][2] = 1;
	M_pattern[6][9][3] = 1;	M_pattern[6][9][4] = 1;	M_pattern[6][9][5] = 0;
	M_pattern[6][9][6] = 0;	M_pattern[6][9][7] = 1;	M_pattern[6][9][8] = 1;


	M_pattern[6][10][0] = 1;	M_pattern[6][10][1] = 0;	M_pattern[6][10][2] = 1;
	M_pattern[6][10][3] = 1;	M_pattern[6][10][4] = 1;	M_pattern[6][10][5] = 0;
	M_pattern[6][10][6] = 0;	M_pattern[6][10][7] = 1;	M_pattern[6][10][8] = 0;


	M_pattern[6][11][0] = 1;	M_pattern[6][11][1] = 0;	M_pattern[6][11][2] = 1;
	M_pattern[6][11][3] = 1;	M_pattern[6][11][4] = 1;	M_pattern[6][11][5] = 0;
	M_pattern[6][11][6] = 0;	M_pattern[6][11][7] = 1;	M_pattern[6][11][8] = 1;


	M_pattern[6][12][0] = 1;	M_pattern[6][12][1] = 0;	M_pattern[6][12][2] = 0;
	M_pattern[6][12][3] = 0;	M_pattern[6][12][4] = 1;	M_pattern[6][12][5] = 1;
	M_pattern[6][12][6] = 0;	M_pattern[6][12][7] = 1;	M_pattern[6][12][8] = 0;


	M_pattern[6][13][0] = 1;	M_pattern[6][13][1] = 0;	M_pattern[6][13][2] = 0;
	M_pattern[6][13][3] = 0;	M_pattern[6][13][4] = 1;	M_pattern[6][13][5] = 1;
	M_pattern[6][13][6] = 1;	M_pattern[6][13][7] = 1;	M_pattern[6][13][8] = 0;


	M_pattern[6][14][0] = 1;	M_pattern[6][14][1] = 0;	M_pattern[6][14][2] = 1;
	M_pattern[6][14][3] = 0;	M_pattern[6][14][4] = 1;	M_pattern[6][14][5] = 1;
	M_pattern[6][14][6] = 0;	M_pattern[6][14][7] = 1;	M_pattern[6][14][8] = 0;


	M_pattern[6][15][0] = 1;	M_pattern[6][15][1] = 0;	M_pattern[6][15][2] = 1;
	M_pattern[6][15][3] = 0;	M_pattern[6][15][4] = 1;	M_pattern[6][15][5] = 1;
	M_pattern[6][15][6] = 1;	M_pattern[6][15][7] = 1;	M_pattern[6][15][8] = 0;








	

	for(int i = 0; i < 512; ++i)
	{
		hash_lut_hit[i] = 0;
	}
	for(int i = 0; i < num.size(); i++)
	{
		for(int j = 0; j < num[i]; j++)
		{
			int counter = 0;
			for(int k = 0; k < 9; k++)
			{
				counter += (int)hit_matrices[i][j][k] * x_map[k];
			}
			hash_lut_hit[counter] = 1;
		}
	}

	for(int i = 0; i < 512; i++)
		hash_lut_M[i] = 0;
	for(int i = 0; i < M_num.size(); i++)
	{
		for(int j = 0; j < M_num[i]; j++)
		{
			int counter = 0;
			for(int k = 0; k < 9; k++)
				counter += (int)M_pattern[i][j][k] * x_map[k];
			hash_lut_M[counter] = 1;
		}
	}
	for(int i = 0; i < 512; i++)
	{
		hash_lut_bridge[i] = 0;
	}
	hash_lut_bridge[12] = 1;	hash_lut_bridge[13] = 1;	hash_lut_bridge[33] = 1;
	hash_lut_bridge[37] = 1;	hash_lut_bridge[40] = 1;	hash_lut_bridge[41] = 1;
	hash_lut_bridge[44] = 1;	hash_lut_bridge[45] = 1;	hash_lut_bridge[66] = 1;
	hash_lut_bridge[67] = 1;	hash_lut_bridge[68] = 1;	hash_lut_bridge[69] = 1;
	hash_lut_bridge[70] = 1;	hash_lut_bridge[71] = 1;	hash_lut_bridge[76] = 1;
	hash_lut_bridge[77] = 1;	hash_lut_bridge[96] = 1;	hash_lut_bridge[97] = 1;
	hash_lut_bridge[98] = 1;	hash_lut_bridge[99] = 1;	hash_lut_bridge[100] = 1;
	hash_lut_bridge[101] = 1;	hash_lut_bridge[102] = 1;	hash_lut_bridge[103] = 1;
	hash_lut_bridge[104] = 1;	hash_lut_bridge[105] = 1;	hash_lut_bridge[108] = 1;
	hash_lut_bridge[109] = 1;	hash_lut_bridge[129] = 1;	hash_lut_bridge[130] = 1;
	hash_lut_bridge[131] = 1;	hash_lut_bridge[132] = 1;	hash_lut_bridge[133] = 1;
	hash_lut_bridge[134] = 1;	hash_lut_bridge[135] = 1;	hash_lut_bridge[140] = 1;
	hash_lut_bridge[141] = 1;	hash_lut_bridge[161] = 1;	hash_lut_bridge[165] = 1;
	hash_lut_bridge[193] = 1;	hash_lut_bridge[194] = 1;	hash_lut_bridge[195] = 1;
	hash_lut_bridge[196] = 1;	hash_lut_bridge[197] = 1;	hash_lut_bridge[198] = 1;
	hash_lut_bridge[199] = 1;	hash_lut_bridge[204] = 1;	hash_lut_bridge[205] = 1;
	hash_lut_bridge[225] = 1;	hash_lut_bridge[229] = 1;	hash_lut_bridge[257] = 1;
	hash_lut_bridge[258] = 1;	hash_lut_bridge[259] = 1;	hash_lut_bridge[261] = 1;
	hash_lut_bridge[262] = 1;	hash_lut_bridge[263] = 1;	hash_lut_bridge[264] = 1;
	hash_lut_bridge[265] = 1;	hash_lut_bridge[266] = 1;	hash_lut_bridge[267] = 1;
	hash_lut_bridge[268] = 1;	hash_lut_bridge[269] = 1;	hash_lut_bridge[270] = 1;
	hash_lut_bridge[271] = 1;	hash_lut_bridge[289] = 1;	hash_lut_bridge[293] = 1;
	hash_lut_bridge[296] = 1;	hash_lut_bridge[297] = 1;	hash_lut_bridge[300] = 1;
	hash_lut_bridge[301] = 1;	hash_lut_bridge[321] = 1;	hash_lut_bridge[322] = 1;
	hash_lut_bridge[323] = 1;	hash_lut_bridge[324] = 1;	hash_lut_bridge[325] = 1;
	hash_lut_bridge[326] = 1;	hash_lut_bridge[327] = 1;	hash_lut_bridge[328] = 1;
	hash_lut_bridge[329] = 1;	hash_lut_bridge[330] = 1;	hash_lut_bridge[331] = 1;
	hash_lut_bridge[332] = 1;	hash_lut_bridge[333] = 1;	hash_lut_bridge[334] = 1;
	hash_lut_bridge[335] = 1;	hash_lut_bridge[352] = 1;	hash_lut_bridge[353] = 1;
	hash_lut_bridge[354] = 1;	hash_lut_bridge[355] = 1;	hash_lut_bridge[356] = 1;
	hash_lut_bridge[357] = 1;	hash_lut_bridge[358] = 1;	hash_lut_bridge[359] = 1;
	hash_lut_bridge[360] = 1;	hash_lut_bridge[361] = 1;	hash_lut_bridge[364] = 1;
	hash_lut_bridge[365] = 1;	hash_lut_bridge[385] = 1;	hash_lut_bridge[386] = 1;
	hash_lut_bridge[387] = 1;	hash_lut_bridge[388] = 1;	hash_lut_bridge[389] = 1;
	hash_lut_bridge[390] = 1;	hash_lut_bridge[391] = 1;	hash_lut_bridge[396] = 1;
	hash_lut_bridge[397] = 1;	hash_lut_bridge[417] = 1;	hash_lut_bridge[421] = 1;
	hash_lut_bridge[449] = 1;	hash_lut_bridge[450] = 1;	hash_lut_bridge[451] = 1;
	hash_lut_bridge[452] = 1;	hash_lut_bridge[453] = 1;	hash_lut_bridge[454] = 1;
	hash_lut_bridge[455] = 1;	hash_lut_bridge[460] = 1;	hash_lut_bridge[461] = 1;
	hash_lut_bridge[481] = 1;	hash_lut_bridge[485] = 1;	

	for(int i = 0; i < num.size(); i++)
	{
		for(int j = 0; j < num[i]; j++)
		{
			delete[] hit_matrices[i][j];
		}
		delete[] hit_matrices[i];
	}
	for(int i = 0; i < M_num.size(); i++)
	{
		for(int j = 0; j < M_num[i]; j++)
		{
			delete[] M_pattern[i][j];
		}
		delete[] M_pattern[i];
	}
	return;
}
void show_matrix()
{
	

	for(int i = 0; i < num.size(); i++)
	{
		fprintf(stderr, "bond: %d\n", i + 1);
		for(int j = 0; j < num[i]; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				fprintf(stderr, "%u %u %u\n", hit_matrices[i][j][3 * k], hit_matrices[i][j][3 * k + 1], hit_matrices[i][j][3 * k + 2]);
			}
			fprintf(stderr, "\n\n\n");
		}
	}
	return;
}
void show_M_matrix()
{
	
	//for(int i = 0; i < M_num.size(); i++)
	int i = 3;
	{
		fprintf(stderr, "bond: %d\n", i + 1);
		for(int j = 0; j < M_num[i]; j++)
		{
			fprintf(stderr, "%dth\n", j);
			for(int k = 0; k < 3; k++)
			{
				fprintf(stderr, "%u %u %u\n", M_pattern[i][j][3 * k], M_pattern[i][j][3 * k + 1], M_pattern[i][j][3 * k + 2]);
			}
			fprintf(stderr, "\n\n\n");
		}
	}
	return;
}
void hash_clear()
{
	delete[] hash_lut_hit;
	delete[] hash_lut_M;
	delete[] hash_lut_bridge;
}
