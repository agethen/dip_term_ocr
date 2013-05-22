#include <vector>
using namespace std;
unsigned char ***hit_matrices;
vector<int> num;
unsigned char ***M_pattern;
vector<int> M_num;
void setup_matrix()
{
	num.push_back(4);	num.push_back(4);	num.push_back(8);	num.push_back(8);
	num.push_back(8);	num.push_back(10);	num.push_back(4);	num.push_back(4);
	num.push_back(8);	num.push_back(4);	num.push_back(4);	num.push_back(1);
	hit_matrices = new unsigned char **[12];
	for(int i = 0; i < num.size(); i++)
	{
		hit_matrices[i] = new unsigned char *[num[i]];
		for(int j = 0; j < num[i]; j++)
		{
			hit_matrices[i][j] = new unsigned char[9];
		}
	}


	hit_matrices[0][0][0] = 0;	hit_matrices[0][0][1] = 0;	hit_matrices[0][0][2] = 1;
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
	hit_matrices[0][3][6] = 0;	hit_matrices[0][3][7] = 0;	hit_matrices[0][3][8] = 1;




	hit_matrices[1][0][0] = 0;	hit_matrices[1][0][1] = 0;	hit_matrices[1][0][2] = 0;
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
	hit_matrices[1][3][6] = 0;	hit_matrices[1][3][7] = 1;	hit_matrices[1][3][8] = 0;




	hit_matrices[2][0][0] = 0;	hit_matrices[2][0][1] = 0;	hit_matrices[2][0][2] = 1;
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
	hit_matrices[2][7][6] = 0;	hit_matrices[2][7][7] = 0;	hit_matrices[2][7][8] = 1;




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




	hit_matrices[4][0][0] = 1;	hit_matrices[4][0][1] = 1;	hit_matrices[4][0][2] = 0;
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
	hit_matrices[4][7][6] = 0;	hit_matrices[4][7][7] = 1;	hit_matrices[4][7][8] = 1;




	hit_matrices[5][0][0] = 1;	hit_matrices[5][0][1] = 1;	hit_matrices[5][0][2] = 0;
	hit_matrices[5][0][3] = 0;	hit_matrices[5][0][4] = 1;	hit_matrices[5][0][5] = 1;
	hit_matrices[5][0][6] = 0;	hit_matrices[5][0][7] = 0;	hit_matrices[5][0][8] = 1;

	hit_matrices[5][1][0] = 0;	hit_matrices[5][1][1] = 1;	hit_matrices[5][1][2] = 1;
	hit_matrices[5][1][3] = 1;	hit_matrices[5][1][4] = 1;	hit_matrices[5][1][5] = 0;
	hit_matrices[5][1][6] = 1;	hit_matrices[5][1][7] = 0;	hit_matrices[5][1][8] = 0;

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


	hit_matrices[11][0][0] = 1;	hit_matrices[11][0][1] = 1;	hit_matrices[11][0][2] = 1;
	hit_matrices[11][0][3] = 1;	hit_matrices[11][0][4] = 1;	hit_matrices[11][0][5] = 1;
	hit_matrices[11][0][6] = 1;	hit_matrices[11][0][7] = 1;	hit_matrices[11][0][8] = 1;




	M_num.push_back(4);		M_num.push_back(8);		M_num.push_back(4);		M_num.push_back(12);
	M_num.push_back(32);	M_num.push_back(32);	M_num.push_back(224);	M_num.push_back(16);
	M_pattern = new unsigned char **[8];
	for(int i = 0; i < M_num.size(); i++)
	{
		M_pattern[i] = new unsigned char *[M_num[i]];
		for(int j = 0; j < M_num[i]; j++)
		{
			M_pattern[i][j] = new unsigned char[9];
		}
	}
	M_pattern[0][0][0] = 0;	M_pattern[0][0][1] = 0;	M_pattern[0][0][2] = 1;
	M_pattern[0][0][3] = 0;	M_pattern[0][0][4] = 1;	M_pattern[0][0][5] = 0;
	M_pattern[0][0][6] = 0;	M_pattern[0][0][7] = 0;	M_pattern[0][0][8] = 0;


	M_pattern[0][1][0] = 1;	M_pattern[0][1][1] = 0;	M_pattern[0][1][2] = 0;
	M_pattern[0][1][3] = 0;	M_pattern[0][1][4] = 1;	M_pattern[0][1][5] = 0;
	M_pattern[0][1][6] = 0;	M_pattern[0][1][7] = 0;	M_pattern[0][1][8] = 0;


	M_pattern[0][2][0] = 0;	M_pattern[0][2][1] = 0;	M_pattern[0][2][2] = 0;
	M_pattern[0][2][3] = 0;	M_pattern[0][2][4] = 1;	M_pattern[0][2][5] = 0;
	M_pattern[0][2][6] = 0;	M_pattern[0][2][7] = 1;	M_pattern[0][2][8] = 0;


	M_pattern[0][3][0] = 0;	M_pattern[0][3][1] = 0;	M_pattern[0][3][2] = 0;
	M_pattern[0][3][3] = 0;	M_pattern[0][3][4] = 1;	M_pattern[0][3][5] = 1;
	M_pattern[0][3][6] = 0;	M_pattern[0][3][7] = 0;	M_pattern[0][3][8] = 0;





	M_pattern[1][0][0] = 0;	M_pattern[1][0][1] = 0;	M_pattern[1][0][2] = 1;
	M_pattern[1][0][3] = 0;	M_pattern[1][0][4] = 1;	M_pattern[1][0][5] = 1;
	M_pattern[1][0][6] = 0;	M_pattern[1][0][7] = 0;	M_pattern[1][0][8] = 0;


	M_pattern[1][1][0] = 0;	M_pattern[1][1][1] = 1;	M_pattern[1][1][2] = 1;
	M_pattern[1][1][3] = 0;	M_pattern[1][1][4] = 1;	M_pattern[1][1][5] = 0;
	M_pattern[1][1][6] = 0;	M_pattern[1][1][7] = 0;	M_pattern[1][1][8] = 0;


	M_pattern[1][2][0] = 1;	M_pattern[1][2][1] = 1;	M_pattern[1][2][2] = 0;
	M_pattern[1][2][3] = 0;	M_pattern[1][2][4] = 1;	M_pattern[1][2][5] = 0;
	M_pattern[1][2][6] = 0;	M_pattern[1][2][7] = 0;	M_pattern[1][2][8] = 0;


	M_pattern[1][3][0] = 1;	M_pattern[1][3][1] = 0;	M_pattern[1][3][2] = 0;
	M_pattern[1][3][3] = 1;	M_pattern[1][3][4] = 1;	M_pattern[1][3][5] = 0;
	M_pattern[1][3][6] = 0;	M_pattern[1][3][7] = 0;	M_pattern[1][3][8] = 0;


	M_pattern[1][4][0] = 0;	M_pattern[1][4][1] = 0;	M_pattern[1][4][2] = 0;
	M_pattern[1][4][3] = 1;	M_pattern[1][4][4] = 1;	M_pattern[1][4][5] = 0;
	M_pattern[1][4][6] = 1;	M_pattern[1][4][7] = 0;	M_pattern[1][4][8] = 0;


	M_pattern[1][5][0] = 0;	M_pattern[1][5][1] = 0;	M_pattern[1][5][2] = 0;
	M_pattern[1][5][3] = 0;	M_pattern[1][5][4] = 1;	M_pattern[1][5][5] = 0;
	M_pattern[1][5][6] = 1;	M_pattern[1][5][7] = 1;	M_pattern[1][5][8] = 0;


	M_pattern[1][6][0] = 0;	M_pattern[1][6][1] = 0;	M_pattern[1][6][2] = 0;
	M_pattern[1][6][3] = 0;	M_pattern[1][6][4] = 1;	M_pattern[1][6][5] = 0;
	M_pattern[1][6][6] = 0;	M_pattern[1][6][7] = 1;	M_pattern[1][6][8] = 1;


	M_pattern[1][7][0] = 0;	M_pattern[1][7][1] = 0;	M_pattern[1][7][2] = 0;
	M_pattern[1][7][3] = 0;	M_pattern[1][7][4] = 1;	M_pattern[1][7][5] = 1;
	M_pattern[1][7][6] = 0;	M_pattern[1][7][7] = 0;	M_pattern[1][7][8] = 1;





	M_pattern[2][0][0] = 0;	M_pattern[2][0][1] = 1;	M_pattern[2][0][2] = 1;
	M_pattern[2][0][3] = 1;	M_pattern[2][0][4] = 1;	M_pattern[2][0][5] = 0;
	M_pattern[2][0][6] = 0;	M_pattern[2][0][7] = 0;	M_pattern[2][0][8] = 0;


	M_pattern[2][1][0] = 1;	M_pattern[2][1][1] = 1;	M_pattern[2][1][2] = 0;
	M_pattern[2][1][3] = 0;	M_pattern[2][1][4] = 1;	M_pattern[2][1][5] = 1;
	M_pattern[2][1][6] = 0;	M_pattern[2][1][7] = 0;	M_pattern[2][1][8] = 0;


	M_pattern[2][2][0] = 0;	M_pattern[2][2][1] = 1;	M_pattern[2][2][2] = 0;
	M_pattern[2][2][3] = 0;	M_pattern[2][2][4] = 1;	M_pattern[2][2][5] = 1;
	M_pattern[2][2][6] = 0;	M_pattern[2][2][7] = 0;	M_pattern[2][2][8] = 1;


	M_pattern[2][3][0] = 0;	M_pattern[2][3][1] = 0;	M_pattern[2][3][2] = 1;
	M_pattern[2][3][3] = 0;	M_pattern[2][3][4] = 1;	M_pattern[2][3][5] = 1;
	M_pattern[2][3][6] = 0;	M_pattern[2][3][7] = 1;	M_pattern[2][3][8] = 0;






	M_pattern[3][0][0] = 0;	M_pattern[3][0][1] = 0;	M_pattern[3][0][2] = 1;
	M_pattern[3][0][3] = 0;	M_pattern[3][0][4] = 1;	M_pattern[3][0][5] = 1;
	M_pattern[3][0][6] = 1;	M_pattern[3][0][7] = 0;	M_pattern[3][0][8] = 0;


	M_pattern[3][1][0] = 0;	M_pattern[3][1][1] = 1;	M_pattern[3][1][2] = 1;
	M_pattern[3][1][3] = 0;	M_pattern[3][1][4] = 1;	M_pattern[3][1][5] = 0;
	M_pattern[3][1][6] = 1;	M_pattern[3][1][7] = 0;	M_pattern[3][1][8] = 0;


	M_pattern[3][2][0] = 0;	M_pattern[3][2][1] = 1;	M_pattern[3][2][2] = 1;
	M_pattern[3][2][3] = 0;	M_pattern[3][2][4] = 1;	M_pattern[3][2][5] = 1;
	M_pattern[3][2][6] = 1;	M_pattern[3][2][7] = 0;	M_pattern[3][2][8] = 0;


	M_pattern[3][3][0] = 1;	M_pattern[3][3][1] = 1;	M_pattern[3][3][2] = 0;
	M_pattern[3][3][3] = 0;	M_pattern[3][3][4] = 1;	M_pattern[3][3][5] = 0;
	M_pattern[3][3][6] = 0;	M_pattern[3][3][7] = 0;	M_pattern[3][3][8] = 1;


	M_pattern[3][4][0] = 1;	M_pattern[3][4][1] = 0;	M_pattern[3][4][2] = 0;
	M_pattern[3][4][3] = 1;	M_pattern[3][4][4] = 1;	M_pattern[3][4][5] = 0;
	M_pattern[3][4][6] = 0;	M_pattern[3][4][7] = 0;	M_pattern[3][4][8] = 1;


	M_pattern[3][5][0] = 1;	M_pattern[3][5][1] = 1;	M_pattern[3][5][2] = 0;
	M_pattern[3][5][3] = 1;	M_pattern[3][5][4] = 1;	M_pattern[3][5][5] = 0;
	M_pattern[3][5][6] = 0;	M_pattern[3][5][7] = 0;	M_pattern[3][5][8] = 1;


	M_pattern[3][6][0] = 0;	M_pattern[3][6][1] = 0;	M_pattern[3][6][2] = 1;
	M_pattern[3][6][3] = 1;	M_pattern[3][6][4] = 1;	M_pattern[3][6][5] = 0;
	M_pattern[3][6][6] = 1;	M_pattern[3][6][7] = 0;	M_pattern[3][6][8] = 0;


	M_pattern[3][7][0] = 0;	M_pattern[3][7][1] = 0;	M_pattern[3][7][2] = 1;
	M_pattern[3][7][3] = 0;	M_pattern[3][7][4] = 1;	M_pattern[3][7][5] = 0;
	M_pattern[3][7][6] = 1;	M_pattern[3][7][7] = 1;	M_pattern[3][7][8] = 0;


	M_pattern[3][8][0] = 0;	M_pattern[3][8][1] = 0;	M_pattern[3][8][2] = 1;
	M_pattern[3][8][3] = 1;	M_pattern[3][8][4] = 1;	M_pattern[3][8][5] = 0;
	M_pattern[3][8][6] = 1;	M_pattern[3][8][7] = 1;	M_pattern[3][8][8] = 0;


	M_pattern[3][9][0] = 1;	M_pattern[3][9][1] = 0;	M_pattern[3][9][2] = 0;
	M_pattern[3][9][3] = 0;	M_pattern[3][9][4] = 1;	M_pattern[3][9][5] = 1;
	M_pattern[3][9][6] = 0;	M_pattern[3][9][7] = 0;	M_pattern[3][9][8] = 1;


	M_pattern[3][10][0] = 1;	M_pattern[3][10][1] = 0;	M_pattern[3][10][2] = 0;
	M_pattern[3][10][3] = 0;	M_pattern[3][10][4] = 1;	M_pattern[3][10][5] = 0;
	M_pattern[3][10][6] = 0;	M_pattern[3][10][7] = 1;	M_pattern[3][10][8] = 1;


	M_pattern[3][11][0] = 1;	M_pattern[3][11][1] = 0;	M_pattern[3][11][2] = 0;
	M_pattern[3][11][3] = 0;	M_pattern[3][11][4] = 1;	M_pattern[3][11][5] = 1;
	M_pattern[3][11][6] = 0;	M_pattern[3][11][7] = 1;	M_pattern[3][11][8] = 1;





	M_pattern[4][0][0] = 1;	M_pattern[4][0][1] = 1;	M_pattern[4][0][2] = 0;
	M_pattern[4][0][3] = 1;	M_pattern[4][0][4] = 1;	M_pattern[4][0][5] = 0;
	M_pattern[4][0][6] = 0;	M_pattern[4][0][7] = 0;	M_pattern[4][0][8] = 0;


	M_pattern[4][1][0] = 1;	M_pattern[4][1][1] = 1;	M_pattern[4][1][2] = 0;
	M_pattern[4][1][3] = 1;	M_pattern[4][1][4] = 1;	M_pattern[4][1][5] = 0;
	M_pattern[4][1][6] = 1;	M_pattern[4][1][7] = 0;	M_pattern[4][1][8] = 0;


	M_pattern[4][2][0] = 1;	M_pattern[4][2][1] = 1;	M_pattern[4][2][2] = 0;
	M_pattern[4][2][3] = 1;	M_pattern[4][2][4] = 1;	M_pattern[4][2][5] = 0;
	M_pattern[4][2][6] = 0;	M_pattern[4][2][7] = 1;	M_pattern[4][2][8] = 0;


	M_pattern[4][3][0] = 1;	M_pattern[4][3][1] = 1;	M_pattern[4][3][2] = 0;
	M_pattern[4][3][3] = 1;	M_pattern[4][3][4] = 1;	M_pattern[4][3][5] = 0;
	M_pattern[4][3][6] = 1;	M_pattern[4][3][7] = 1;	M_pattern[4][3][8] = 0;


	M_pattern[4][4][0] = 1;	M_pattern[4][4][1] = 1;	M_pattern[4][4][2] = 0;
	M_pattern[4][4][3] = 1;	M_pattern[4][4][4] = 1;	M_pattern[4][4][5] = 0;
	M_pattern[4][4][6] = 0;	M_pattern[4][4][7] = 0;	M_pattern[4][4][8] = 1;


	M_pattern[4][5][0] = 1;	M_pattern[4][5][1] = 1;	M_pattern[4][5][2] = 0;
	M_pattern[4][5][3] = 1;	M_pattern[4][5][4] = 1;	M_pattern[4][5][5] = 0;
	M_pattern[4][5][6] = 1;	M_pattern[4][5][7] = 0;	M_pattern[4][5][8] = 1;


	M_pattern[4][6][0] = 1;	M_pattern[4][6][1] = 1;	M_pattern[4][6][2] = 0;
	M_pattern[4][6][3] = 1;	M_pattern[4][6][4] = 1;	M_pattern[4][6][5] = 0;
	M_pattern[4][6][6] = 0;	M_pattern[4][6][7] = 1;	M_pattern[4][6][8] = 1;


	M_pattern[4][7][0] = 1;	M_pattern[4][7][1] = 1;	M_pattern[4][7][2] = 0;
	M_pattern[4][7][3] = 1;	M_pattern[4][7][4] = 1;	M_pattern[4][7][5] = 0;
	M_pattern[4][7][6] = 1;	M_pattern[4][7][7] = 1;	M_pattern[4][7][8] = 1;


	M_pattern[4][8][0] = 1;	M_pattern[4][8][1] = 1;	M_pattern[4][8][2] = 0;
	M_pattern[4][8][3] = 1;	M_pattern[4][8][4] = 1;	M_pattern[4][8][5] = 1;
	M_pattern[4][8][6] = 0;	M_pattern[4][8][7] = 0;	M_pattern[4][8][8] = 0;


	M_pattern[4][9][0] = 1;	M_pattern[4][9][1] = 1;	M_pattern[4][9][2] = 0;
	M_pattern[4][9][3] = 1;	M_pattern[4][9][4] = 1;	M_pattern[4][9][5] = 1;
	M_pattern[4][9][6] = 1;	M_pattern[4][9][7] = 0;	M_pattern[4][9][8] = 0;


	M_pattern[4][10][0] = 1;	M_pattern[4][10][1] = 1;	M_pattern[4][10][2] = 0;
	M_pattern[4][10][3] = 1;	M_pattern[4][10][4] = 1;	M_pattern[4][10][5] = 1;
	M_pattern[4][10][6] = 0;	M_pattern[4][10][7] = 1;	M_pattern[4][10][8] = 0;


	M_pattern[4][11][0] = 1;	M_pattern[4][11][1] = 1;	M_pattern[4][11][2] = 0;
	M_pattern[4][11][3] = 1;	M_pattern[4][11][4] = 1;	M_pattern[4][11][5] = 1;
	M_pattern[4][11][6] = 1;	M_pattern[4][11][7] = 1;	M_pattern[4][11][8] = 0;


	M_pattern[4][12][0] = 1;	M_pattern[4][12][1] = 1;	M_pattern[4][12][2] = 0;
	M_pattern[4][12][3] = 1;	M_pattern[4][12][4] = 1;	M_pattern[4][12][5] = 1;
	M_pattern[4][12][6] = 0;	M_pattern[4][12][7] = 0;	M_pattern[4][12][8] = 1;


	M_pattern[4][13][0] = 1;	M_pattern[4][13][1] = 1;	M_pattern[4][13][2] = 0;
	M_pattern[4][13][3] = 1;	M_pattern[4][13][4] = 1;	M_pattern[4][13][5] = 1;
	M_pattern[4][13][6] = 1;	M_pattern[4][13][7] = 0;	M_pattern[4][13][8] = 1;


	M_pattern[4][14][0] = 1;	M_pattern[4][14][1] = 1;	M_pattern[4][14][2] = 0;
	M_pattern[4][14][3] = 1;	M_pattern[4][14][4] = 1;	M_pattern[4][14][5] = 1;
	M_pattern[4][14][6] = 0;	M_pattern[4][14][7] = 1;	M_pattern[4][14][8] = 1;


	M_pattern[4][15][0] = 1;	M_pattern[4][15][1] = 1;	M_pattern[4][15][2] = 0;
	M_pattern[4][15][3] = 1;	M_pattern[4][15][4] = 1;	M_pattern[4][15][5] = 1;
	M_pattern[4][15][6] = 1;	M_pattern[4][15][7] = 1;	M_pattern[4][15][8] = 1;


	M_pattern[4][16][0] = 1;	M_pattern[4][16][1] = 1;	M_pattern[4][16][2] = 1;
	M_pattern[4][16][3] = 1;	M_pattern[4][16][4] = 1;	M_pattern[4][16][5] = 0;
	M_pattern[4][16][6] = 0;	M_pattern[4][16][7] = 0;	M_pattern[4][16][8] = 0;


	M_pattern[4][17][0] = 1;	M_pattern[4][17][1] = 1;	M_pattern[4][17][2] = 1;
	M_pattern[4][17][3] = 1;	M_pattern[4][17][4] = 1;	M_pattern[4][17][5] = 0;
	M_pattern[4][17][6] = 1;	M_pattern[4][17][7] = 0;	M_pattern[4][17][8] = 0;


	M_pattern[4][18][0] = 1;	M_pattern[4][18][1] = 1;	M_pattern[4][18][2] = 1;
	M_pattern[4][18][3] = 1;	M_pattern[4][18][4] = 1;	M_pattern[4][18][5] = 0;
	M_pattern[4][18][6] = 0;	M_pattern[4][18][7] = 1;	M_pattern[4][18][8] = 0;


	M_pattern[4][19][0] = 1;	M_pattern[4][19][1] = 1;	M_pattern[4][19][2] = 1;
	M_pattern[4][19][3] = 1;	M_pattern[4][19][4] = 1;	M_pattern[4][19][5] = 0;
	M_pattern[4][19][6] = 1;	M_pattern[4][19][7] = 1;	M_pattern[4][19][8] = 0;


	M_pattern[4][20][0] = 1;	M_pattern[4][20][1] = 1;	M_pattern[4][20][2] = 1;
	M_pattern[4][20][3] = 1;	M_pattern[4][20][4] = 1;	M_pattern[4][20][5] = 0;
	M_pattern[4][20][6] = 0;	M_pattern[4][20][7] = 0;	M_pattern[4][20][8] = 1;


	M_pattern[4][21][0] = 1;	M_pattern[4][21][1] = 1;	M_pattern[4][21][2] = 1;
	M_pattern[4][21][3] = 1;	M_pattern[4][21][4] = 1;	M_pattern[4][21][5] = 0;
	M_pattern[4][21][6] = 1;	M_pattern[4][21][7] = 0;	M_pattern[4][21][8] = 1;


	M_pattern[4][22][0] = 1;	M_pattern[4][22][1] = 1;	M_pattern[4][22][2] = 1;
	M_pattern[4][22][3] = 1;	M_pattern[4][22][4] = 1;	M_pattern[4][22][5] = 0;
	M_pattern[4][22][6] = 0;	M_pattern[4][22][7] = 1;	M_pattern[4][22][8] = 1;


	M_pattern[4][23][0] = 1;	M_pattern[4][23][1] = 1;	M_pattern[4][23][2] = 1;
	M_pattern[4][23][3] = 1;	M_pattern[4][23][4] = 1;	M_pattern[4][23][5] = 0;
	M_pattern[4][23][6] = 1;	M_pattern[4][23][7] = 1;	M_pattern[4][23][8] = 1;


	M_pattern[4][24][0] = 1;	M_pattern[4][24][1] = 1;	M_pattern[4][24][2] = 1;
	M_pattern[4][24][3] = 1;	M_pattern[4][24][4] = 1;	M_pattern[4][24][5] = 1;
	M_pattern[4][24][6] = 0;	M_pattern[4][24][7] = 0;	M_pattern[4][24][8] = 0;


	M_pattern[4][25][0] = 1;	M_pattern[4][25][1] = 1;	M_pattern[4][25][2] = 1;
	M_pattern[4][25][3] = 1;	M_pattern[4][25][4] = 1;	M_pattern[4][25][5] = 1;
	M_pattern[4][25][6] = 1;	M_pattern[4][25][7] = 0;	M_pattern[4][25][8] = 0;


	M_pattern[4][26][0] = 1;	M_pattern[4][26][1] = 1;	M_pattern[4][26][2] = 1;
	M_pattern[4][26][3] = 1;	M_pattern[4][26][4] = 1;	M_pattern[4][26][5] = 1;
	M_pattern[4][26][6] = 0;	M_pattern[4][26][7] = 1;	M_pattern[4][26][8] = 0;


	M_pattern[4][27][0] = 1;	M_pattern[4][27][1] = 1;	M_pattern[4][27][2] = 1;
	M_pattern[4][27][3] = 1;	M_pattern[4][27][4] = 1;	M_pattern[4][27][5] = 1;
	M_pattern[4][27][6] = 1;	M_pattern[4][27][7] = 1;	M_pattern[4][27][8] = 0;


	M_pattern[4][28][0] = 1;	M_pattern[4][28][1] = 1;	M_pattern[4][28][2] = 1;
	M_pattern[4][28][3] = 1;	M_pattern[4][28][4] = 1;	M_pattern[4][28][5] = 1;
	M_pattern[4][28][6] = 0;	M_pattern[4][28][7] = 0;	M_pattern[4][28][8] = 1;


	M_pattern[4][29][0] = 1;	M_pattern[4][29][1] = 1;	M_pattern[4][29][2] = 1;
	M_pattern[4][29][3] = 1;	M_pattern[4][29][4] = 1;	M_pattern[4][29][5] = 1;
	M_pattern[4][29][6] = 1;	M_pattern[4][29][7] = 0;	M_pattern[4][29][8] = 1;


	M_pattern[4][30][0] = 1;	M_pattern[4][30][1] = 1;	M_pattern[4][30][2] = 1;
	M_pattern[4][30][3] = 1;	M_pattern[4][30][4] = 1;	M_pattern[4][30][5] = 1;
	M_pattern[4][30][6] = 0;	M_pattern[4][30][7] = 1;	M_pattern[4][30][8] = 1;


	M_pattern[4][31][0] = 1;	M_pattern[4][31][1] = 1;	M_pattern[4][31][2] = 1;
	M_pattern[4][31][3] = 1;	M_pattern[4][31][4] = 1;	M_pattern[4][31][5] = 1;
	M_pattern[4][31][6] = 1;	M_pattern[4][31][7] = 1;	M_pattern[4][31][8] = 1;





	M_pattern[5][0][0] = 0;	M_pattern[5][0][1] = 1;	M_pattern[5][0][2] = 0;
	M_pattern[5][0][3] = 1;	M_pattern[5][0][4] = 1;	M_pattern[5][0][5] = 1;
	M_pattern[5][0][6] = 0;	M_pattern[5][0][7] = 0;	M_pattern[5][0][8] = 0;


	M_pattern[5][1][0] = 0;	M_pattern[5][1][1] = 1;	M_pattern[5][1][2] = 0;
	M_pattern[5][1][3] = 1;	M_pattern[5][1][4] = 1;	M_pattern[5][1][5] = 1;
	M_pattern[5][1][6] = 1;	M_pattern[5][1][7] = 0;	M_pattern[5][1][8] = 0;


	M_pattern[5][2][0] = 1;	M_pattern[5][2][1] = 1;	M_pattern[5][2][2] = 0;
	M_pattern[5][2][3] = 1;	M_pattern[5][2][4] = 1;	M_pattern[5][2][5] = 1;
	M_pattern[5][2][6] = 0;	M_pattern[5][2][7] = 0;	M_pattern[5][2][8] = 0;


	M_pattern[5][3][0] = 1;	M_pattern[5][3][1] = 1;	M_pattern[5][3][2] = 0;
	M_pattern[5][3][3] = 1;	M_pattern[5][3][4] = 1;	M_pattern[5][3][5] = 1;
	M_pattern[5][3][6] = 1;	M_pattern[5][3][7] = 0;	M_pattern[5][3][8] = 0;





	M_pattern[5][4][2] = 0;	M_pattern[5][4][1] = 1;	M_pattern[5][4][0] = 0;
	M_pattern[5][4][3] = 1;	M_pattern[5][4][4] = 1;	M_pattern[5][4][5] = 1;
	M_pattern[5][4][8] = 0;	M_pattern[5][4][7] = 0;	M_pattern[5][4][6] = 0;


	M_pattern[5][5][2] = 0;	M_pattern[5][5][1] = 1;	M_pattern[5][5][0] = 0;
	M_pattern[5][5][3] = 1;	M_pattern[5][5][4] = 1;	M_pattern[5][5][5] = 1;
	M_pattern[5][5][8] = 1;	M_pattern[5][5][7] = 0;	M_pattern[5][5][6] = 0;


	M_pattern[5][6][2] = 1;	M_pattern[5][6][1] = 1;	M_pattern[5][6][0] = 0;
	M_pattern[5][6][3] = 1;	M_pattern[5][6][4] = 1;	M_pattern[5][6][5] = 1;
	M_pattern[5][6][8] = 0;	M_pattern[5][6][7] = 0;	M_pattern[5][6][6] = 0;


	M_pattern[5][7][2] = 1;	M_pattern[5][7][1] = 1;	M_pattern[5][7][0] = 0;
	M_pattern[5][7][3] = 1;	M_pattern[5][7][4] = 1;	M_pattern[5][7][5] = 1;
	M_pattern[5][7][8] = 1;	M_pattern[5][7][7] = 0;	M_pattern[5][7][6] = 0;





	M_pattern[5][8][0] = 0;	M_pattern[5][8][1] = 0;	M_pattern[5][8][2] = 0;
	M_pattern[5][8][3] = 1;	M_pattern[5][8][4] = 1;	M_pattern[5][8][5] = 1;
	M_pattern[5][8][6] = 0;	M_pattern[5][8][7] = 1;	M_pattern[5][8][8] = 0;


	M_pattern[5][9][0] = 0;	M_pattern[5][9][1] = 0;	M_pattern[5][9][2] = 0;
	M_pattern[5][9][3] = 1;	M_pattern[5][9][4] = 1;	M_pattern[5][9][5] = 1;
	M_pattern[5][9][6] = 1;	M_pattern[5][9][7] = 1;	M_pattern[5][9][8] = 0;


	M_pattern[5][10][0] = 1;	M_pattern[5][10][1] = 0;	M_pattern[5][10][2] = 0;
	M_pattern[5][10][3] = 1;	M_pattern[5][10][4] = 1;	M_pattern[5][10][5] = 1;
	M_pattern[5][10][6] = 0;	M_pattern[5][10][7] = 1;	M_pattern[5][10][8] = 0;


	M_pattern[5][11][0] = 1;	M_pattern[5][11][1] = 0;	M_pattern[5][11][2] = 0;
	M_pattern[5][11][3] = 1;	M_pattern[5][11][4] = 1;	M_pattern[5][11][5] = 1;
	M_pattern[5][11][6] = 1;	M_pattern[5][11][7] = 1;	M_pattern[5][11][8] = 0;





	M_pattern[5][12][2] = 0;	M_pattern[5][12][1] = 0;	M_pattern[5][12][0] = 0;
	M_pattern[5][12][3] = 1;	M_pattern[5][12][4] = 1;	M_pattern[5][12][5] = 1;
	M_pattern[5][12][8] = 0;	M_pattern[5][12][7] = 1;	M_pattern[5][12][6] = 0;


	M_pattern[5][13][2] = 0;	M_pattern[5][13][1] = 0;	M_pattern[5][13][0] = 0;
	M_pattern[5][13][3] = 1;	M_pattern[5][13][4] = 1;	M_pattern[5][13][5] = 1;
	M_pattern[5][13][8] = 1;	M_pattern[5][13][7] = 1;	M_pattern[5][13][6] = 0;


	M_pattern[5][14][2] = 1;	M_pattern[5][14][1] = 0;	M_pattern[5][14][0] = 0;
	M_pattern[5][14][3] = 1;	M_pattern[5][14][4] = 1;	M_pattern[5][14][5] = 1;
	M_pattern[5][14][8] = 0;	M_pattern[5][14][7] = 1;	M_pattern[5][14][6] = 0;


	M_pattern[5][15][2] = 1;	M_pattern[5][15][1] = 0;	M_pattern[5][15][0] = 0;
	M_pattern[5][15][3] = 1;	M_pattern[5][15][4] = 1;	M_pattern[5][15][5] = 1;
	M_pattern[5][15][8] = 1;	M_pattern[5][15][7] = 1;	M_pattern[5][15][6] = 0;





	M_pattern[5][16][0] = 0;	M_pattern[5][16][1] = 1;	M_pattern[5][16][6] = 0;
	M_pattern[5][16][3] = 1;	M_pattern[5][16][4] = 1;	M_pattern[5][16][5] = 0;
	M_pattern[5][16][2] = 0;	M_pattern[5][16][7] = 1;	M_pattern[5][16][8] = 0;


	M_pattern[5][17][0] = 0;	M_pattern[5][17][1] = 1;	M_pattern[5][17][6] = 0;
	M_pattern[5][17][3] = 1;	M_pattern[5][17][4] = 1;	M_pattern[5][17][5] = 0;
	M_pattern[5][17][2] = 1;	M_pattern[5][17][7] = 1;	M_pattern[5][17][8] = 0;


	M_pattern[5][18][0] = 1;	M_pattern[5][18][1] = 1;	M_pattern[5][18][6] = 0;
	M_pattern[5][18][3] = 1;	M_pattern[5][18][4] = 1;	M_pattern[5][18][5] = 0;
	M_pattern[5][18][2] = 0;	M_pattern[5][18][7] = 1;	M_pattern[5][18][8] = 0;


	M_pattern[5][19][0] = 1;	M_pattern[5][19][1] = 1;	M_pattern[5][19][6] = 0;
	M_pattern[5][19][3] = 1;	M_pattern[5][19][4] = 1;	M_pattern[5][19][5] = 0;
	M_pattern[5][19][2] = 1;	M_pattern[5][19][7] = 1;	M_pattern[5][19][8] = 0;





	M_pattern[5][20][6] = 0;	M_pattern[5][20][1] = 1;	M_pattern[5][20][0] = 0;
	M_pattern[5][20][3] = 1;	M_pattern[5][20][4] = 1;	M_pattern[5][20][5] = 0;
	M_pattern[5][20][8] = 0;	M_pattern[5][20][7] = 1;	M_pattern[5][20][2] = 0;


	M_pattern[5][21][6] = 0;	M_pattern[5][21][1] = 1;	M_pattern[5][21][0] = 0;
	M_pattern[5][21][3] = 1;	M_pattern[5][21][4] = 1;	M_pattern[5][21][5] = 0;
	M_pattern[5][21][8] = 1;	M_pattern[5][21][7] = 1;	M_pattern[5][21][2] = 0;


	M_pattern[5][22][6] = 1;	M_pattern[5][22][1] = 1;	M_pattern[5][22][0] = 0;
	M_pattern[5][22][3] = 1;	M_pattern[5][22][4] = 1;	M_pattern[5][22][5] = 0;
	M_pattern[5][22][8] = 0;	M_pattern[5][22][7] = 1;	M_pattern[5][22][2] = 0;


	M_pattern[5][23][6] = 1;	M_pattern[5][23][1] = 1;	M_pattern[5][23][0] = 0;
	M_pattern[5][23][3] = 1;	M_pattern[5][23][4] = 1;	M_pattern[5][23][5] = 0;
	M_pattern[5][23][8] = 1;	M_pattern[5][23][7] = 1;	M_pattern[5][23][2] = 0;





	M_pattern[5][24][6] = 0;	M_pattern[5][24][1] = 1;	M_pattern[5][24][0] = 0;
	M_pattern[5][24][3] = 0;	M_pattern[5][24][4] = 1;	M_pattern[5][24][5] = 1;
	M_pattern[5][24][8] = 0;	M_pattern[5][24][7] = 1;	M_pattern[5][24][2] = 0;


	M_pattern[5][25][6] = 0;	M_pattern[5][25][1] = 1;	M_pattern[5][25][0] = 0;
	M_pattern[5][25][3] = 0;	M_pattern[5][25][4] = 1;	M_pattern[5][25][5] = 1;
	M_pattern[5][25][8] = 1;	M_pattern[5][25][7] = 1;	M_pattern[5][25][2] = 0;


	M_pattern[5][26][6] = 1;	M_pattern[5][26][1] = 1;	M_pattern[5][26][0] = 0;
	M_pattern[5][26][3] = 0;	M_pattern[5][26][4] = 1;	M_pattern[5][26][5] = 1;
	M_pattern[5][26][8] = 0;	M_pattern[5][26][7] = 1;	M_pattern[5][26][2] = 0;


	M_pattern[5][27][6] = 1;	M_pattern[5][27][1] = 1;	M_pattern[5][27][0] = 0;
	M_pattern[5][27][3] = 0;	M_pattern[5][27][4] = 1;	M_pattern[5][27][5] = 1;
	M_pattern[5][27][8] = 1;	M_pattern[5][27][7] = 1;	M_pattern[5][27][2] = 0;





	M_pattern[5][28][0] = 0;	M_pattern[5][28][1] = 1;	M_pattern[5][28][6] = 0;
	M_pattern[5][28][3] = 0;	M_pattern[5][28][4] = 1;	M_pattern[5][28][5] = 1;
	M_pattern[5][28][2] = 0;	M_pattern[5][28][7] = 1;	M_pattern[5][28][8] = 0;


	M_pattern[5][29][0] = 0;	M_pattern[5][29][1] = 1;	M_pattern[5][29][6] = 0;
	M_pattern[5][29][3] = 0;	M_pattern[5][29][4] = 1;	M_pattern[5][29][5] = 1;
	M_pattern[5][29][2] = 1;	M_pattern[5][29][7] = 1;	M_pattern[5][29][8] = 0;


	M_pattern[5][30][0] = 1;	M_pattern[5][30][1] = 1;	M_pattern[5][30][6] = 0;
	M_pattern[5][30][3] = 0;	M_pattern[5][30][4] = 1;	M_pattern[5][30][5] = 1;
	M_pattern[5][30][2] = 0;	M_pattern[5][30][7] = 1;	M_pattern[5][30][8] = 0;


	M_pattern[5][31][0] = 1;	M_pattern[5][31][1] = 1;	M_pattern[5][31][6] = 0;
	M_pattern[5][31][3] = 0;	M_pattern[5][31][4] = 1;	M_pattern[5][31][5] = 1;
	M_pattern[5][31][2] = 1;	M_pattern[5][31][7] = 1;	M_pattern[5][31][8] = 0;





	M_pattern[6][0][0] = 1;	M_pattern[6][0][1] = 0;	M_pattern[6][0][2] = 1;
	M_pattern[6][0][3] = 0;	M_pattern[6][0][4] = 1;	M_pattern[6][0][5] = 0;
	M_pattern[6][0][6] = 0;	M_pattern[6][0][7] = 0;	M_pattern[6][0][8] = 1;
	M_pattern[6][1][0] = 1;	M_pattern[6][1][1] = 0;	M_pattern[6][1][2] = 1;
	M_pattern[6][1][3] = 0;	M_pattern[6][1][4] = 1;	M_pattern[6][1][5] = 0;
	M_pattern[6][1][6] = 0;	M_pattern[6][1][7] = 1;	M_pattern[6][1][8] = 0;
	M_pattern[6][2][0] = 1;	M_pattern[6][2][1] = 0;	M_pattern[6][2][2] = 1;
	M_pattern[6][2][3] = 0;	M_pattern[6][2][4] = 1;	M_pattern[6][2][5] = 0;
	M_pattern[6][2][6] = 0;	M_pattern[6][2][7] = 1;	M_pattern[6][2][8] = 1;
	M_pattern[6][3][0] = 1;	M_pattern[6][3][1] = 0;	M_pattern[6][3][2] = 1;
	M_pattern[6][3][3] = 0;	M_pattern[6][3][4] = 1;	M_pattern[6][3][5] = 0;
	M_pattern[6][3][6] = 1;	M_pattern[6][3][7] = 0;	M_pattern[6][3][8] = 0;
	M_pattern[6][4][0] = 1;	M_pattern[6][4][1] = 0;	M_pattern[6][4][2] = 1;
	M_pattern[6][4][3] = 0;	M_pattern[6][4][4] = 1;	M_pattern[6][4][5] = 0;
	M_pattern[6][4][6] = 1;	M_pattern[6][4][7] = 0;	M_pattern[6][4][8] = 1;
	M_pattern[6][5][0] = 1;	M_pattern[6][5][1] = 0;	M_pattern[6][5][2] = 1;
	M_pattern[6][5][3] = 0;	M_pattern[6][5][4] = 1;	M_pattern[6][5][5] = 0;
	M_pattern[6][5][6] = 1;	M_pattern[6][5][7] = 1;	M_pattern[6][5][8] = 0;
	M_pattern[6][6][0] = 1;	M_pattern[6][6][1] = 0;	M_pattern[6][6][2] = 1;
	M_pattern[6][6][3] = 0;	M_pattern[6][6][4] = 1;	M_pattern[6][6][5] = 0;
	M_pattern[6][6][6] = 1;	M_pattern[6][6][7] = 1;	M_pattern[6][6][8] = 1;
	M_pattern[6][7][0] = 1;	M_pattern[6][7][1] = 0;	M_pattern[6][7][2] = 1;
	M_pattern[6][7][3] = 0;	M_pattern[6][7][4] = 1;	M_pattern[6][7][5] = 1;
	M_pattern[6][7][6] = 0;	M_pattern[6][7][7] = 0;	M_pattern[6][7][8] = 1;
	M_pattern[6][8][0] = 1;	M_pattern[6][8][1] = 0;	M_pattern[6][8][2] = 1;
	M_pattern[6][8][3] = 0;	M_pattern[6][8][4] = 1;	M_pattern[6][8][5] = 1;
	M_pattern[6][8][6] = 0;	M_pattern[6][8][7] = 1;	M_pattern[6][8][8] = 0;
	M_pattern[6][9][0] = 1;	M_pattern[6][9][1] = 0;	M_pattern[6][9][2] = 1;
	M_pattern[6][9][3] = 0;	M_pattern[6][9][4] = 1;	M_pattern[6][9][5] = 1;
	M_pattern[6][9][6] = 0;	M_pattern[6][9][7] = 1;	M_pattern[6][9][8] = 1;
	M_pattern[6][10][0] = 1;	M_pattern[6][10][1] = 0;	M_pattern[6][10][2] = 1;
	M_pattern[6][10][3] = 0;	M_pattern[6][10][4] = 1;	M_pattern[6][10][5] = 1;
	M_pattern[6][10][6] = 1;	M_pattern[6][10][7] = 0;	M_pattern[6][10][8] = 0;
	M_pattern[6][11][0] = 1;	M_pattern[6][11][1] = 0;	M_pattern[6][11][2] = 1;
	M_pattern[6][11][3] = 0;	M_pattern[6][11][4] = 1;	M_pattern[6][11][5] = 1;
	M_pattern[6][11][6] = 1;	M_pattern[6][11][7] = 0;	M_pattern[6][11][8] = 1;
	M_pattern[6][12][0] = 1;	M_pattern[6][12][1] = 0;	M_pattern[6][12][2] = 1;
	M_pattern[6][12][3] = 0;	M_pattern[6][12][4] = 1;	M_pattern[6][12][5] = 1;
	M_pattern[6][12][6] = 1;	M_pattern[6][12][7] = 1;	M_pattern[6][12][8] = 0;
	M_pattern[6][13][0] = 1;	M_pattern[6][13][1] = 0;	M_pattern[6][13][2] = 1;
	M_pattern[6][13][3] = 0;	M_pattern[6][13][4] = 1;	M_pattern[6][13][5] = 1;
	M_pattern[6][13][6] = 1;	M_pattern[6][13][7] = 1;	M_pattern[6][13][8] = 1;
	M_pattern[6][14][0] = 1;	M_pattern[6][14][1] = 0;	M_pattern[6][14][2] = 1;
	M_pattern[6][14][3] = 1;	M_pattern[6][14][4] = 1;	M_pattern[6][14][5] = 0;
	M_pattern[6][14][6] = 0;	M_pattern[6][14][7] = 0;	M_pattern[6][14][8] = 1;
	M_pattern[6][15][0] = 1;	M_pattern[6][15][1] = 0;	M_pattern[6][15][2] = 1;
	M_pattern[6][15][3] = 1;	M_pattern[6][15][4] = 1;	M_pattern[6][15][5] = 0;
	M_pattern[6][15][6] = 0;	M_pattern[6][15][7] = 1;	M_pattern[6][15][8] = 0;
	M_pattern[6][16][0] = 1;	M_pattern[6][16][1] = 0;	M_pattern[6][16][2] = 1;
	M_pattern[6][16][3] = 1;	M_pattern[6][16][4] = 1;	M_pattern[6][16][5] = 0;
	M_pattern[6][16][6] = 0;	M_pattern[6][16][7] = 1;	M_pattern[6][16][8] = 1;
	M_pattern[6][17][0] = 1;	M_pattern[6][17][1] = 0;	M_pattern[6][17][2] = 1;
	M_pattern[6][17][3] = 1;	M_pattern[6][17][4] = 1;	M_pattern[6][17][5] = 0;
	M_pattern[6][17][6] = 1;	M_pattern[6][17][7] = 0;	M_pattern[6][17][8] = 0;
	M_pattern[6][18][0] = 1;	M_pattern[6][18][1] = 0;	M_pattern[6][18][2] = 1;
	M_pattern[6][18][3] = 1;	M_pattern[6][18][4] = 1;	M_pattern[6][18][5] = 0;
	M_pattern[6][18][6] = 1;	M_pattern[6][18][7] = 0;	M_pattern[6][18][8] = 1;
	M_pattern[6][19][0] = 1;	M_pattern[6][19][1] = 0;	M_pattern[6][19][2] = 1;
	M_pattern[6][19][3] = 1;	M_pattern[6][19][4] = 1;	M_pattern[6][19][5] = 0;
	M_pattern[6][19][6] = 1;	M_pattern[6][19][7] = 1;	M_pattern[6][19][8] = 0;
	M_pattern[6][20][0] = 1;	M_pattern[6][20][1] = 0;	M_pattern[6][20][2] = 1;
	M_pattern[6][20][3] = 1;	M_pattern[6][20][4] = 1;	M_pattern[6][20][5] = 0;
	M_pattern[6][20][6] = 1;	M_pattern[6][20][7] = 1;	M_pattern[6][20][8] = 1;
	M_pattern[6][21][0] = 1;	M_pattern[6][21][1] = 0;	M_pattern[6][21][2] = 1;
	M_pattern[6][21][3] = 1;	M_pattern[6][21][4] = 1;	M_pattern[6][21][5] = 1;
	M_pattern[6][21][6] = 0;	M_pattern[6][21][7] = 0;	M_pattern[6][21][8] = 1;
	M_pattern[6][22][0] = 1;	M_pattern[6][22][1] = 0;	M_pattern[6][22][2] = 1;
	M_pattern[6][22][3] = 1;	M_pattern[6][22][4] = 1;	M_pattern[6][22][5] = 1;
	M_pattern[6][22][6] = 0;	M_pattern[6][22][7] = 1;	M_pattern[6][22][8] = 0;
	M_pattern[6][23][0] = 1;	M_pattern[6][23][1] = 0;	M_pattern[6][23][2] = 1;
	M_pattern[6][23][3] = 1;	M_pattern[6][23][4] = 1;	M_pattern[6][23][5] = 1;
	M_pattern[6][23][6] = 0;	M_pattern[6][23][7] = 1;	M_pattern[6][23][8] = 1;
	M_pattern[6][24][0] = 1;	M_pattern[6][24][1] = 0;	M_pattern[6][24][2] = 1;
	M_pattern[6][24][3] = 1;	M_pattern[6][24][4] = 1;	M_pattern[6][24][5] = 1;
	M_pattern[6][24][6] = 1;	M_pattern[6][24][7] = 0;	M_pattern[6][24][8] = 0;
	M_pattern[6][25][0] = 1;	M_pattern[6][25][1] = 0;	M_pattern[6][25][2] = 1;
	M_pattern[6][25][3] = 1;	M_pattern[6][25][4] = 1;	M_pattern[6][25][5] = 1;
	M_pattern[6][25][6] = 1;	M_pattern[6][25][7] = 0;	M_pattern[6][25][8] = 1;
	M_pattern[6][26][0] = 1;	M_pattern[6][26][1] = 0;	M_pattern[6][26][2] = 1;
	M_pattern[6][26][3] = 1;	M_pattern[6][26][4] = 1;	M_pattern[6][26][5] = 1;
	M_pattern[6][26][6] = 1;	M_pattern[6][26][7] = 1;	M_pattern[6][26][8] = 0;
	M_pattern[6][27][0] = 1;	M_pattern[6][27][1] = 0;	M_pattern[6][27][2] = 1;
	M_pattern[6][27][3] = 1;	M_pattern[6][27][4] = 1;	M_pattern[6][27][5] = 1;
	M_pattern[6][27][6] = 1;	M_pattern[6][27][7] = 1;	M_pattern[6][27][8] = 1;
	M_pattern[6][28][0] = 1;	M_pattern[6][28][1] = 1;	M_pattern[6][28][2] = 1;
	M_pattern[6][28][3] = 0;	M_pattern[6][28][4] = 1;	M_pattern[6][28][5] = 0;
	M_pattern[6][28][6] = 0;	M_pattern[6][28][7] = 0;	M_pattern[6][28][8] = 1;
	M_pattern[6][29][0] = 1;	M_pattern[6][29][1] = 1;	M_pattern[6][29][2] = 1;
	M_pattern[6][29][3] = 0;	M_pattern[6][29][4] = 1;	M_pattern[6][29][5] = 0;
	M_pattern[6][29][6] = 0;	M_pattern[6][29][7] = 1;	M_pattern[6][29][8] = 0;
	M_pattern[6][30][0] = 1;	M_pattern[6][30][1] = 1;	M_pattern[6][30][2] = 1;
	M_pattern[6][30][3] = 0;	M_pattern[6][30][4] = 1;	M_pattern[6][30][5] = 0;
	M_pattern[6][30][6] = 0;	M_pattern[6][30][7] = 1;	M_pattern[6][30][8] = 1;
	M_pattern[6][31][0] = 1;	M_pattern[6][31][1] = 1;	M_pattern[6][31][2] = 1;
	M_pattern[6][31][3] = 0;	M_pattern[6][31][4] = 1;	M_pattern[6][31][5] = 0;
	M_pattern[6][31][6] = 1;	M_pattern[6][31][7] = 0;	M_pattern[6][31][8] = 0;
	M_pattern[6][32][0] = 1;	M_pattern[6][32][1] = 1;	M_pattern[6][32][2] = 1;
	M_pattern[6][32][3] = 0;	M_pattern[6][32][4] = 1;	M_pattern[6][32][5] = 0;
	M_pattern[6][32][6] = 1;	M_pattern[6][32][7] = 0;	M_pattern[6][32][8] = 1;
	M_pattern[6][33][0] = 1;	M_pattern[6][33][1] = 1;	M_pattern[6][33][2] = 1;
	M_pattern[6][33][3] = 0;	M_pattern[6][33][4] = 1;	M_pattern[6][33][5] = 0;
	M_pattern[6][33][6] = 1;	M_pattern[6][33][7] = 1;	M_pattern[6][33][8] = 0;
	M_pattern[6][34][0] = 1;	M_pattern[6][34][1] = 1;	M_pattern[6][34][2] = 1;
	M_pattern[6][34][3] = 0;	M_pattern[6][34][4] = 1;	M_pattern[6][34][5] = 0;
	M_pattern[6][34][6] = 1;	M_pattern[6][34][7] = 1;	M_pattern[6][34][8] = 1;
	M_pattern[6][35][0] = 1;	M_pattern[6][35][1] = 1;	M_pattern[6][35][2] = 1;
	M_pattern[6][35][3] = 0;	M_pattern[6][35][4] = 1;	M_pattern[6][35][5] = 1;
	M_pattern[6][35][6] = 0;	M_pattern[6][35][7] = 0;	M_pattern[6][35][8] = 1;
	M_pattern[6][36][0] = 1;	M_pattern[6][36][1] = 1;	M_pattern[6][36][2] = 1;
	M_pattern[6][36][3] = 0;	M_pattern[6][36][4] = 1;	M_pattern[6][36][5] = 1;
	M_pattern[6][36][6] = 0;	M_pattern[6][36][7] = 1;	M_pattern[6][36][8] = 0;
	M_pattern[6][37][0] = 1;	M_pattern[6][37][1] = 1;	M_pattern[6][37][2] = 1;
	M_pattern[6][37][3] = 0;	M_pattern[6][37][4] = 1;	M_pattern[6][37][5] = 1;
	M_pattern[6][37][6] = 0;	M_pattern[6][37][7] = 1;	M_pattern[6][37][8] = 1;
	M_pattern[6][38][0] = 1;	M_pattern[6][38][1] = 1;	M_pattern[6][38][2] = 1;
	M_pattern[6][38][3] = 0;	M_pattern[6][38][4] = 1;	M_pattern[6][38][5] = 1;
	M_pattern[6][38][6] = 1;	M_pattern[6][38][7] = 0;	M_pattern[6][38][8] = 0;
	M_pattern[6][39][0] = 1;	M_pattern[6][39][1] = 1;	M_pattern[6][39][2] = 1;
	M_pattern[6][39][3] = 0;	M_pattern[6][39][4] = 1;	M_pattern[6][39][5] = 1;
	M_pattern[6][39][6] = 1;	M_pattern[6][39][7] = 0;	M_pattern[6][39][8] = 1;
	M_pattern[6][40][0] = 1;	M_pattern[6][40][1] = 1;	M_pattern[6][40][2] = 1;
	M_pattern[6][40][3] = 0;	M_pattern[6][40][4] = 1;	M_pattern[6][40][5] = 1;
	M_pattern[6][40][6] = 1;	M_pattern[6][40][7] = 1;	M_pattern[6][40][8] = 0;
	M_pattern[6][41][0] = 1;	M_pattern[6][41][1] = 1;	M_pattern[6][41][2] = 1;
	M_pattern[6][41][3] = 0;	M_pattern[6][41][4] = 1;	M_pattern[6][41][5] = 1;
	M_pattern[6][41][6] = 1;	M_pattern[6][41][7] = 1;	M_pattern[6][41][8] = 1;
	M_pattern[6][42][0] = 1;	M_pattern[6][42][1] = 1;	M_pattern[6][42][2] = 1;
	M_pattern[6][42][3] = 1;	M_pattern[6][42][4] = 1;	M_pattern[6][42][5] = 0;
	M_pattern[6][42][6] = 0;	M_pattern[6][42][7] = 0;	M_pattern[6][42][8] = 1;
	M_pattern[6][43][0] = 1;	M_pattern[6][43][1] = 1;	M_pattern[6][43][2] = 1;
	M_pattern[6][43][3] = 1;	M_pattern[6][43][4] = 1;	M_pattern[6][43][5] = 0;
	M_pattern[6][43][6] = 0;	M_pattern[6][43][7] = 1;	M_pattern[6][43][8] = 0;
	M_pattern[6][44][0] = 1;	M_pattern[6][44][1] = 1;	M_pattern[6][44][2] = 1;
	M_pattern[6][44][3] = 1;	M_pattern[6][44][4] = 1;	M_pattern[6][44][5] = 0;
	M_pattern[6][44][6] = 0;	M_pattern[6][44][7] = 1;	M_pattern[6][44][8] = 1;
	M_pattern[6][45][0] = 1;	M_pattern[6][45][1] = 1;	M_pattern[6][45][2] = 1;
	M_pattern[6][45][3] = 1;	M_pattern[6][45][4] = 1;	M_pattern[6][45][5] = 0;
	M_pattern[6][45][6] = 1;	M_pattern[6][45][7] = 0;	M_pattern[6][45][8] = 0;
	M_pattern[6][46][0] = 1;	M_pattern[6][46][1] = 1;	M_pattern[6][46][2] = 1;
	M_pattern[6][46][3] = 1;	M_pattern[6][46][4] = 1;	M_pattern[6][46][5] = 0;
	M_pattern[6][46][6] = 1;	M_pattern[6][46][7] = 0;	M_pattern[6][46][8] = 1;
	M_pattern[6][47][0] = 1;	M_pattern[6][47][1] = 1;	M_pattern[6][47][2] = 1;
	M_pattern[6][47][3] = 1;	M_pattern[6][47][4] = 1;	M_pattern[6][47][5] = 0;
	M_pattern[6][47][6] = 1;	M_pattern[6][47][7] = 1;	M_pattern[6][47][8] = 0;
	M_pattern[6][48][0] = 1;	M_pattern[6][48][1] = 1;	M_pattern[6][48][2] = 1;
	M_pattern[6][48][3] = 1;	M_pattern[6][48][4] = 1;	M_pattern[6][48][5] = 0;
	M_pattern[6][48][6] = 1;	M_pattern[6][48][7] = 1;	M_pattern[6][48][8] = 1;
	M_pattern[6][49][0] = 1;	M_pattern[6][49][1] = 1;	M_pattern[6][49][2] = 1;
	M_pattern[6][49][3] = 1;	M_pattern[6][49][4] = 1;	M_pattern[6][49][5] = 1;
	M_pattern[6][49][6] = 0;	M_pattern[6][49][7] = 0;	M_pattern[6][49][8] = 1;
	M_pattern[6][50][0] = 1;	M_pattern[6][50][1] = 1;	M_pattern[6][50][2] = 1;
	M_pattern[6][50][3] = 1;	M_pattern[6][50][4] = 1;	M_pattern[6][50][5] = 1;
	M_pattern[6][50][6] = 0;	M_pattern[6][50][7] = 1;	M_pattern[6][50][8] = 0;
	M_pattern[6][51][0] = 1;	M_pattern[6][51][1] = 1;	M_pattern[6][51][2] = 1;
	M_pattern[6][51][3] = 1;	M_pattern[6][51][4] = 1;	M_pattern[6][51][5] = 1;
	M_pattern[6][51][6] = 0;	M_pattern[6][51][7] = 1;	M_pattern[6][51][8] = 1;
	M_pattern[6][52][0] = 1;	M_pattern[6][52][1] = 1;	M_pattern[6][52][2] = 1;
	M_pattern[6][52][3] = 1;	M_pattern[6][52][4] = 1;	M_pattern[6][52][5] = 1;
	M_pattern[6][52][6] = 1;	M_pattern[6][52][7] = 0;	M_pattern[6][52][8] = 0;
	M_pattern[6][53][0] = 1;	M_pattern[6][53][1] = 1;	M_pattern[6][53][2] = 1;
	M_pattern[6][53][3] = 1;	M_pattern[6][53][4] = 1;	M_pattern[6][53][5] = 1;
	M_pattern[6][53][6] = 1;	M_pattern[6][53][7] = 0;	M_pattern[6][53][8] = 1;
	M_pattern[6][54][0] = 1;	M_pattern[6][54][1] = 1;	M_pattern[6][54][2] = 1;
	M_pattern[6][54][3] = 1;	M_pattern[6][54][4] = 1;	M_pattern[6][54][5] = 1;
	M_pattern[6][54][6] = 1;	M_pattern[6][54][7] = 1;	M_pattern[6][54][8] = 0;
	M_pattern[6][55][0] = 1;	M_pattern[6][55][1] = 1;	M_pattern[6][55][2] = 1;
	M_pattern[6][55][3] = 1;	M_pattern[6][55][4] = 1;	M_pattern[6][55][5] = 1;
	M_pattern[6][55][6] = 1;	M_pattern[6][55][7] = 1;	M_pattern[6][55][8] = 1;



	M_pattern[6][56][0] = 1;	M_pattern[6][56][3] = 0;	M_pattern[6][56][6] = 1;
	M_pattern[6][56][1] = 0;	M_pattern[6][56][4] = 1;	M_pattern[6][56][7] = 0;
	M_pattern[6][56][2] = 0;	M_pattern[6][56][5] = 0;	M_pattern[6][56][8] = 1;
	M_pattern[6][57][0] = 1;	M_pattern[6][57][3] = 0;	M_pattern[6][57][6] = 1;
	M_pattern[6][57][1] = 0;	M_pattern[6][57][4] = 1;	M_pattern[6][57][7] = 0;
	M_pattern[6][57][2] = 0;	M_pattern[6][57][5] = 1;	M_pattern[6][57][8] = 0;
	M_pattern[6][58][0] = 1;	M_pattern[6][58][3] = 0;	M_pattern[6][58][6] = 1;
	M_pattern[6][58][1] = 0;	M_pattern[6][58][4] = 1;	M_pattern[6][58][7] = 0;
	M_pattern[6][58][2] = 0;	M_pattern[6][58][5] = 1;	M_pattern[6][58][8] = 1;
	M_pattern[6][59][0] = 1;	M_pattern[6][59][3] = 0;	M_pattern[6][59][6] = 1;
	M_pattern[6][59][1] = 0;	M_pattern[6][59][4] = 1;	M_pattern[6][59][7] = 0;
	M_pattern[6][59][2] = 1;	M_pattern[6][59][5] = 0;	M_pattern[6][59][8] = 0;
	M_pattern[6][60][0] = 1;	M_pattern[6][60][3] = 0;	M_pattern[6][60][6] = 1;
	M_pattern[6][60][1] = 0;	M_pattern[6][60][4] = 1;	M_pattern[6][60][7] = 0;
	M_pattern[6][60][2] = 1;	M_pattern[6][60][5] = 0;	M_pattern[6][60][8] = 1;
	M_pattern[6][61][0] = 1;	M_pattern[6][61][3] = 0;	M_pattern[6][61][6] = 1;
	M_pattern[6][61][1] = 0;	M_pattern[6][61][4] = 1;	M_pattern[6][61][7] = 0;
	M_pattern[6][61][2] = 1;	M_pattern[6][61][5] = 1;	M_pattern[6][61][8] = 0;
	M_pattern[6][62][0] = 1;	M_pattern[6][62][3] = 0;	M_pattern[6][62][6] = 1;
	M_pattern[6][62][1] = 0;	M_pattern[6][62][4] = 1;	M_pattern[6][62][7] = 0;
	M_pattern[6][62][2] = 1;	M_pattern[6][62][5] = 1;	M_pattern[6][62][8] = 1;
	M_pattern[6][63][0] = 1;	M_pattern[6][63][3] = 0;	M_pattern[6][63][6] = 1;
	M_pattern[6][63][1] = 0;	M_pattern[6][63][4] = 1;	M_pattern[6][63][7] = 1;
	M_pattern[6][63][2] = 0;	M_pattern[6][63][5] = 0;	M_pattern[6][63][8] = 1;
	M_pattern[6][64][0] = 1;	M_pattern[6][64][3] = 0;	M_pattern[6][64][6] = 1;
	M_pattern[6][64][1] = 0;	M_pattern[6][64][4] = 1;	M_pattern[6][64][7] = 1;
	M_pattern[6][64][2] = 0;	M_pattern[6][64][5] = 1;	M_pattern[6][64][8] = 0;
	M_pattern[6][65][0] = 1;	M_pattern[6][65][3] = 0;	M_pattern[6][65][6] = 1;
	M_pattern[6][65][1] = 0;	M_pattern[6][65][4] = 1;	M_pattern[6][65][7] = 1;
	M_pattern[6][65][2] = 0;	M_pattern[6][65][5] = 1;	M_pattern[6][65][8] = 1;
	M_pattern[6][66][0] = 1;	M_pattern[6][66][3] = 0;	M_pattern[6][66][6] = 1;
	M_pattern[6][66][1] = 0;	M_pattern[6][66][4] = 1;	M_pattern[6][66][7] = 1;
	M_pattern[6][66][2] = 1;	M_pattern[6][66][5] = 0;	M_pattern[6][66][8] = 0;
	M_pattern[6][67][0] = 1;	M_pattern[6][67][3] = 0;	M_pattern[6][67][6] = 1;
	M_pattern[6][67][1] = 0;	M_pattern[6][67][4] = 1;	M_pattern[6][67][7] = 1;
	M_pattern[6][67][2] = 1;	M_pattern[6][67][5] = 0;	M_pattern[6][67][8] = 1;
	M_pattern[6][68][0] = 1;	M_pattern[6][68][3] = 0;	M_pattern[6][68][6] = 1;
	M_pattern[6][68][1] = 0;	M_pattern[6][68][4] = 1;	M_pattern[6][68][7] = 1;
	M_pattern[6][68][2] = 1;	M_pattern[6][68][5] = 1;	M_pattern[6][68][8] = 0;
	M_pattern[6][69][0] = 1;	M_pattern[6][69][3] = 0;	M_pattern[6][69][6] = 1;
	M_pattern[6][69][1] = 0;	M_pattern[6][69][4] = 1;	M_pattern[6][69][7] = 1;
	M_pattern[6][69][2] = 1;	M_pattern[6][69][5] = 1;	M_pattern[6][69][8] = 1;
	M_pattern[6][70][0] = 1;	M_pattern[6][70][3] = 0;	M_pattern[6][70][6] = 1;
	M_pattern[6][70][1] = 1;	M_pattern[6][70][4] = 1;	M_pattern[6][70][7] = 0;
	M_pattern[6][70][2] = 0;	M_pattern[6][70][5] = 0;	M_pattern[6][70][8] = 1;
	M_pattern[6][71][0] = 1;	M_pattern[6][71][3] = 0;	M_pattern[6][71][6] = 1;
	M_pattern[6][71][1] = 1;	M_pattern[6][71][4] = 1;	M_pattern[6][71][7] = 0;
	M_pattern[6][71][2] = 0;	M_pattern[6][71][5] = 1;	M_pattern[6][71][8] = 0;
	M_pattern[6][72][0] = 1;	M_pattern[6][72][3] = 0;	M_pattern[6][72][6] = 1;
	M_pattern[6][72][1] = 1;	M_pattern[6][72][4] = 1;	M_pattern[6][72][7] = 0;
	M_pattern[6][72][2] = 0;	M_pattern[6][72][5] = 1;	M_pattern[6][72][8] = 1;
	M_pattern[6][73][0] = 1;	M_pattern[6][73][3] = 0;	M_pattern[6][73][6] = 1;
	M_pattern[6][73][1] = 1;	M_pattern[6][73][4] = 1;	M_pattern[6][73][7] = 0;
	M_pattern[6][73][2] = 1;	M_pattern[6][73][5] = 0;	M_pattern[6][73][8] = 0;
	M_pattern[6][74][0] = 1;	M_pattern[6][74][3] = 0;	M_pattern[6][74][6] = 1;
	M_pattern[6][74][1] = 1;	M_pattern[6][74][4] = 1;	M_pattern[6][74][7] = 0;
	M_pattern[6][74][2] = 1;	M_pattern[6][74][5] = 0;	M_pattern[6][74][8] = 1;
	M_pattern[6][75][0] = 1;	M_pattern[6][75][3] = 0;	M_pattern[6][75][6] = 1;
	M_pattern[6][75][1] = 1;	M_pattern[6][75][4] = 1;	M_pattern[6][75][7] = 0;
	M_pattern[6][75][2] = 1;	M_pattern[6][75][5] = 1;	M_pattern[6][75][8] = 0;
	M_pattern[6][76][0] = 1;	M_pattern[6][76][3] = 0;	M_pattern[6][76][6] = 1;
	M_pattern[6][76][1] = 1;	M_pattern[6][76][4] = 1;	M_pattern[6][76][7] = 0;
	M_pattern[6][76][2] = 1;	M_pattern[6][76][5] = 1;	M_pattern[6][76][8] = 1;
	M_pattern[6][77][0] = 1;	M_pattern[6][77][3] = 0;	M_pattern[6][77][6] = 1;
	M_pattern[6][77][1] = 1;	M_pattern[6][77][4] = 1;	M_pattern[6][77][7] = 1;
	M_pattern[6][77][2] = 0;	M_pattern[6][77][5] = 0;	M_pattern[6][77][8] = 1;
	M_pattern[6][78][0] = 1;	M_pattern[6][78][3] = 0;	M_pattern[6][78][6] = 1;
	M_pattern[6][78][1] = 1;	M_pattern[6][78][4] = 1;	M_pattern[6][78][7] = 1;
	M_pattern[6][78][2] = 0;	M_pattern[6][78][5] = 1;	M_pattern[6][78][8] = 0;
	M_pattern[6][79][0] = 1;	M_pattern[6][79][3] = 0;	M_pattern[6][79][6] = 1;
	M_pattern[6][79][1] = 1;	M_pattern[6][79][4] = 1;	M_pattern[6][79][7] = 1;
	M_pattern[6][79][2] = 0;	M_pattern[6][79][5] = 1;	M_pattern[6][79][8] = 1;
	M_pattern[6][80][0] = 1;	M_pattern[6][80][3] = 0;	M_pattern[6][80][6] = 1;
	M_pattern[6][80][1] = 1;	M_pattern[6][80][4] = 1;	M_pattern[6][80][7] = 1;
	M_pattern[6][80][2] = 1;	M_pattern[6][80][5] = 0;	M_pattern[6][80][8] = 0;
	M_pattern[6][81][0] = 1;	M_pattern[6][81][3] = 0;	M_pattern[6][81][6] = 1;
	M_pattern[6][81][1] = 1;	M_pattern[6][81][4] = 1;	M_pattern[6][81][7] = 1;
	M_pattern[6][81][2] = 1;	M_pattern[6][81][5] = 0;	M_pattern[6][81][8] = 1;
	M_pattern[6][82][0] = 1;	M_pattern[6][82][3] = 0;	M_pattern[6][82][6] = 1;
	M_pattern[6][82][1] = 1;	M_pattern[6][82][4] = 1;	M_pattern[6][82][7] = 1;
	M_pattern[6][82][2] = 1;	M_pattern[6][82][5] = 1;	M_pattern[6][82][8] = 0;
	M_pattern[6][83][0] = 1;	M_pattern[6][83][3] = 0;	M_pattern[6][83][6] = 1;
	M_pattern[6][83][1] = 1;	M_pattern[6][83][4] = 1;	M_pattern[6][83][7] = 1;
	M_pattern[6][83][2] = 1;	M_pattern[6][83][5] = 1;	M_pattern[6][83][8] = 1;
	M_pattern[6][84][0] = 1;	M_pattern[6][84][3] = 1;	M_pattern[6][84][6] = 1;
	M_pattern[6][84][1] = 0;	M_pattern[6][84][4] = 1;	M_pattern[6][84][7] = 0;
	M_pattern[6][84][2] = 0;	M_pattern[6][84][5] = 0;	M_pattern[6][84][8] = 1;
	M_pattern[6][85][0] = 1;	M_pattern[6][85][3] = 1;	M_pattern[6][85][6] = 1;
	M_pattern[6][85][1] = 0;	M_pattern[6][85][4] = 1;	M_pattern[6][85][7] = 0;
	M_pattern[6][85][2] = 0;	M_pattern[6][85][5] = 1;	M_pattern[6][85][8] = 0;
	M_pattern[6][86][0] = 1;	M_pattern[6][86][3] = 1;	M_pattern[6][86][6] = 1;
	M_pattern[6][86][1] = 0;	M_pattern[6][86][4] = 1;	M_pattern[6][86][7] = 0;
	M_pattern[6][86][2] = 0;	M_pattern[6][86][5] = 1;	M_pattern[6][86][8] = 1;
	M_pattern[6][87][0] = 1;	M_pattern[6][87][3] = 1;	M_pattern[6][87][6] = 1;
	M_pattern[6][87][1] = 0;	M_pattern[6][87][4] = 1;	M_pattern[6][87][7] = 0;
	M_pattern[6][87][2] = 1;	M_pattern[6][87][5] = 0;	M_pattern[6][87][8] = 0;
	M_pattern[6][88][0] = 1;	M_pattern[6][88][3] = 1;	M_pattern[6][88][6] = 1;
	M_pattern[6][88][1] = 0;	M_pattern[6][88][4] = 1;	M_pattern[6][88][7] = 0;
	M_pattern[6][88][2] = 1;	M_pattern[6][88][5] = 0;	M_pattern[6][88][8] = 1;
	M_pattern[6][89][0] = 1;	M_pattern[6][89][3] = 1;	M_pattern[6][89][6] = 1;
	M_pattern[6][89][1] = 0;	M_pattern[6][89][4] = 1;	M_pattern[6][89][7] = 0;
	M_pattern[6][89][2] = 1;	M_pattern[6][89][5] = 1;	M_pattern[6][89][8] = 0;
	M_pattern[6][90][0] = 1;	M_pattern[6][90][3] = 1;	M_pattern[6][90][6] = 1;
	M_pattern[6][90][1] = 0;	M_pattern[6][90][4] = 1;	M_pattern[6][90][7] = 0;
	M_pattern[6][90][2] = 1;	M_pattern[6][90][5] = 1;	M_pattern[6][90][8] = 1;
	M_pattern[6][91][0] = 1;	M_pattern[6][91][3] = 1;	M_pattern[6][91][6] = 1;
	M_pattern[6][91][1] = 0;	M_pattern[6][91][4] = 1;	M_pattern[6][91][7] = 1;
	M_pattern[6][91][2] = 0;	M_pattern[6][91][5] = 0;	M_pattern[6][91][8] = 1;
	M_pattern[6][92][0] = 1;	M_pattern[6][92][3] = 1;	M_pattern[6][92][6] = 1;
	M_pattern[6][92][1] = 0;	M_pattern[6][92][4] = 1;	M_pattern[6][92][7] = 1;
	M_pattern[6][92][2] = 0;	M_pattern[6][92][5] = 1;	M_pattern[6][92][8] = 0;
	M_pattern[6][93][0] = 1;	M_pattern[6][93][3] = 1;	M_pattern[6][93][6] = 1;
	M_pattern[6][93][1] = 0;	M_pattern[6][93][4] = 1;	M_pattern[6][93][7] = 1;
	M_pattern[6][93][2] = 0;	M_pattern[6][93][5] = 1;	M_pattern[6][93][8] = 1;
	M_pattern[6][94][0] = 1;	M_pattern[6][94][3] = 1;	M_pattern[6][94][6] = 1;
	M_pattern[6][94][1] = 0;	M_pattern[6][94][4] = 1;	M_pattern[6][94][7] = 1;
	M_pattern[6][94][2] = 1;	M_pattern[6][94][5] = 0;	M_pattern[6][94][8] = 0;
	M_pattern[6][95][0] = 1;	M_pattern[6][95][3] = 1;	M_pattern[6][95][6] = 1;
	M_pattern[6][95][1] = 0;	M_pattern[6][95][4] = 1;	M_pattern[6][95][7] = 1;
	M_pattern[6][95][2] = 1;	M_pattern[6][95][5] = 0;	M_pattern[6][95][8] = 1;
	M_pattern[6][96][0] = 1;	M_pattern[6][96][3] = 1;	M_pattern[6][96][6] = 1;
	M_pattern[6][96][1] = 0;	M_pattern[6][96][4] = 1;	M_pattern[6][96][7] = 1;
	M_pattern[6][96][2] = 1;	M_pattern[6][96][5] = 1;	M_pattern[6][96][8] = 0;
	M_pattern[6][97][0] = 1;	M_pattern[6][97][3] = 1;	M_pattern[6][97][6] = 1;
	M_pattern[6][97][1] = 0;	M_pattern[6][97][4] = 1;	M_pattern[6][97][7] = 1;
	M_pattern[6][97][2] = 1;	M_pattern[6][97][5] = 1;	M_pattern[6][97][8] = 1;
	M_pattern[6][98][0] = 1;	M_pattern[6][98][3] = 1;	M_pattern[6][98][6] = 1;
	M_pattern[6][98][1] = 1;	M_pattern[6][98][4] = 1;	M_pattern[6][98][7] = 0;
	M_pattern[6][98][2] = 0;	M_pattern[6][98][5] = 0;	M_pattern[6][98][8] = 1;
	M_pattern[6][99][0] = 1;	M_pattern[6][99][3] = 1;	M_pattern[6][99][6] = 1;
	M_pattern[6][99][1] = 1;	M_pattern[6][99][4] = 1;	M_pattern[6][99][7] = 0;
	M_pattern[6][99][2] = 0;	M_pattern[6][99][5] = 1;	M_pattern[6][99][8] = 0;
	M_pattern[6][100][0] = 1;	M_pattern[6][100][3] = 1;	M_pattern[6][100][6] = 1;
	M_pattern[6][100][1] = 1;	M_pattern[6][100][4] = 1;	M_pattern[6][100][7] = 0;
	M_pattern[6][100][2] = 0;	M_pattern[6][100][5] = 1;	M_pattern[6][100][8] = 1;
	M_pattern[6][101][0] = 1;	M_pattern[6][101][3] = 1;	M_pattern[6][101][6] = 1;
	M_pattern[6][101][1] = 1;	M_pattern[6][101][4] = 1;	M_pattern[6][101][7] = 0;
	M_pattern[6][101][2] = 1;	M_pattern[6][101][5] = 0;	M_pattern[6][101][8] = 0;
	M_pattern[6][102][0] = 1;	M_pattern[6][102][3] = 1;	M_pattern[6][102][6] = 1;
	M_pattern[6][102][1] = 1;	M_pattern[6][102][4] = 1;	M_pattern[6][102][7] = 0;
	M_pattern[6][102][2] = 1;	M_pattern[6][102][5] = 0;	M_pattern[6][102][8] = 1;
	M_pattern[6][103][0] = 1;	M_pattern[6][103][3] = 1;	M_pattern[6][103][6] = 1;
	M_pattern[6][103][1] = 1;	M_pattern[6][103][4] = 1;	M_pattern[6][103][7] = 0;
	M_pattern[6][103][2] = 1;	M_pattern[6][103][5] = 1;	M_pattern[6][103][8] = 0;
	M_pattern[6][104][0] = 1;	M_pattern[6][104][3] = 1;	M_pattern[6][104][6] = 1;
	M_pattern[6][104][1] = 1;	M_pattern[6][104][4] = 1;	M_pattern[6][104][7] = 0;
	M_pattern[6][104][2] = 1;	M_pattern[6][104][5] = 1;	M_pattern[6][104][8] = 1;
	M_pattern[6][105][0] = 1;	M_pattern[6][105][3] = 1;	M_pattern[6][105][6] = 1;
	M_pattern[6][105][1] = 1;	M_pattern[6][105][4] = 1;	M_pattern[6][105][7] = 1;
	M_pattern[6][105][2] = 0;	M_pattern[6][105][5] = 0;	M_pattern[6][105][8] = 1;
	M_pattern[6][106][0] = 1;	M_pattern[6][106][3] = 1;	M_pattern[6][106][6] = 1;
	M_pattern[6][106][1] = 1;	M_pattern[6][106][4] = 1;	M_pattern[6][106][7] = 1;
	M_pattern[6][106][2] = 0;	M_pattern[6][106][5] = 1;	M_pattern[6][106][8] = 0;
	M_pattern[6][107][0] = 1;	M_pattern[6][107][3] = 1;	M_pattern[6][107][6] = 1;
	M_pattern[6][107][1] = 1;	M_pattern[6][107][4] = 1;	M_pattern[6][107][7] = 1;
	M_pattern[6][107][2] = 0;	M_pattern[6][107][5] = 1;	M_pattern[6][107][8] = 1;
	M_pattern[6][108][0] = 1;	M_pattern[6][108][3] = 1;	M_pattern[6][108][6] = 1;
	M_pattern[6][108][1] = 1;	M_pattern[6][108][4] = 1;	M_pattern[6][108][7] = 1;
	M_pattern[6][108][2] = 1;	M_pattern[6][108][5] = 0;	M_pattern[6][108][8] = 0;
	M_pattern[6][109][0] = 1;	M_pattern[6][109][3] = 1;	M_pattern[6][109][6] = 1;
	M_pattern[6][109][1] = 1;	M_pattern[6][109][4] = 1;	M_pattern[6][109][7] = 1;
	M_pattern[6][109][2] = 1;	M_pattern[6][109][5] = 0;	M_pattern[6][109][8] = 1;
	M_pattern[6][110][0] = 1;	M_pattern[6][110][3] = 1;	M_pattern[6][110][6] = 1;
	M_pattern[6][110][1] = 1;	M_pattern[6][110][4] = 1;	M_pattern[6][110][7] = 1;
	M_pattern[6][110][2] = 1;	M_pattern[6][110][5] = 1;	M_pattern[6][110][8] = 0;
	M_pattern[6][111][0] = 1;	M_pattern[6][111][3] = 1;	M_pattern[6][111][6] = 1;
	M_pattern[6][111][1] = 1;	M_pattern[6][111][4] = 1;	M_pattern[6][111][7] = 1;
	M_pattern[6][111][2] = 1;	M_pattern[6][111][5] = 1;	M_pattern[6][111][8] = 1;



	M_pattern[6][112][6] = 1;	M_pattern[6][112][7] = 0;	M_pattern[6][112][8] = 1;
	M_pattern[6][112][3] = 0;	M_pattern[6][112][4] = 1;	M_pattern[6][112][5] = 0;
	M_pattern[6][112][0] = 0;	M_pattern[6][112][1] = 0;	M_pattern[6][112][2] = 1;
	M_pattern[6][113][6] = 1;	M_pattern[6][113][7] = 0;	M_pattern[6][113][8] = 1;
	M_pattern[6][113][3] = 0;	M_pattern[6][113][4] = 1;	M_pattern[6][113][5] = 0;
	M_pattern[6][113][0] = 0;	M_pattern[6][113][1] = 1;	M_pattern[6][113][2] = 0;
	M_pattern[6][114][6] = 1;	M_pattern[6][114][7] = 0;	M_pattern[6][114][8] = 1;
	M_pattern[6][114][3] = 0;	M_pattern[6][114][4] = 1;	M_pattern[6][114][5] = 0;
	M_pattern[6][114][0] = 0;	M_pattern[6][114][1] = 1;	M_pattern[6][114][2] = 1;
	M_pattern[6][115][6] = 1;	M_pattern[6][115][7] = 0;	M_pattern[6][115][8] = 1;
	M_pattern[6][115][3] = 0;	M_pattern[6][115][4] = 1;	M_pattern[6][115][5] = 0;
	M_pattern[6][115][0] = 1;	M_pattern[6][115][1] = 0;	M_pattern[6][115][2] = 0;
	M_pattern[6][116][6] = 1;	M_pattern[6][116][7] = 0;	M_pattern[6][116][8] = 1;
	M_pattern[6][116][3] = 0;	M_pattern[6][116][4] = 1;	M_pattern[6][116][5] = 0;
	M_pattern[6][116][0] = 1;	M_pattern[6][116][1] = 0;	M_pattern[6][116][2] = 1;
	M_pattern[6][117][6] = 1;	M_pattern[6][117][7] = 0;	M_pattern[6][117][8] = 1;
	M_pattern[6][117][3] = 0;	M_pattern[6][117][4] = 1;	M_pattern[6][117][5] = 0;
	M_pattern[6][117][0] = 1;	M_pattern[6][117][1] = 1;	M_pattern[6][117][2] = 0;
	M_pattern[6][118][6] = 1;	M_pattern[6][118][7] = 0;	M_pattern[6][118][8] = 1;
	M_pattern[6][118][3] = 0;	M_pattern[6][118][4] = 1;	M_pattern[6][118][5] = 0;
	M_pattern[6][118][0] = 1;	M_pattern[6][118][1] = 1;	M_pattern[6][118][2] = 1;
	M_pattern[6][119][6] = 1;	M_pattern[6][119][7] = 0;	M_pattern[6][119][8] = 1;
	M_pattern[6][119][3] = 0;	M_pattern[6][119][4] = 1;	M_pattern[6][119][5] = 1;
	M_pattern[6][119][0] = 0;	M_pattern[6][119][1] = 0;	M_pattern[6][119][2] = 1;
	M_pattern[6][120][6] = 1;	M_pattern[6][120][7] = 0;	M_pattern[6][120][8] = 1;
	M_pattern[6][120][3] = 0;	M_pattern[6][120][4] = 1;	M_pattern[6][120][5] = 1;
	M_pattern[6][120][0] = 0;	M_pattern[6][120][1] = 1;	M_pattern[6][120][2] = 0;
	M_pattern[6][121][6] = 1;	M_pattern[6][121][7] = 0;	M_pattern[6][121][8] = 1;
	M_pattern[6][121][3] = 0;	M_pattern[6][121][4] = 1;	M_pattern[6][121][5] = 1;
	M_pattern[6][121][0] = 0;	M_pattern[6][121][1] = 1;	M_pattern[6][121][2] = 1;
	M_pattern[6][122][6] = 1;	M_pattern[6][122][7] = 0;	M_pattern[6][122][8] = 1;
	M_pattern[6][122][3] = 0;	M_pattern[6][122][4] = 1;	M_pattern[6][122][5] = 1;
	M_pattern[6][122][0] = 1;	M_pattern[6][122][1] = 0;	M_pattern[6][122][2] = 0;
	M_pattern[6][123][6] = 1;	M_pattern[6][123][7] = 0;	M_pattern[6][123][8] = 1;
	M_pattern[6][123][3] = 0;	M_pattern[6][123][4] = 1;	M_pattern[6][123][5] = 1;
	M_pattern[6][123][0] = 1;	M_pattern[6][123][1] = 0;	M_pattern[6][123][2] = 1;
	M_pattern[6][124][6] = 1;	M_pattern[6][124][7] = 0;	M_pattern[6][124][8] = 1;
	M_pattern[6][124][3] = 0;	M_pattern[6][124][4] = 1;	M_pattern[6][124][5] = 1;
	M_pattern[6][124][0] = 1;	M_pattern[6][124][1] = 1;	M_pattern[6][124][2] = 0;
	M_pattern[6][125][6] = 1;	M_pattern[6][125][7] = 0;	M_pattern[6][125][8] = 1;
	M_pattern[6][125][3] = 0;	M_pattern[6][125][4] = 1;	M_pattern[6][125][5] = 1;
	M_pattern[6][125][0] = 1;	M_pattern[6][125][1] = 1;	M_pattern[6][125][2] = 1;
	M_pattern[6][126][6] = 1;	M_pattern[6][126][7] = 0;	M_pattern[6][126][8] = 1;
	M_pattern[6][126][3] = 1;	M_pattern[6][126][4] = 1;	M_pattern[6][126][5] = 0;
	M_pattern[6][126][0] = 0;	M_pattern[6][126][1] = 0;	M_pattern[6][126][2] = 1;
	M_pattern[6][127][6] = 1;	M_pattern[6][127][7] = 0;	M_pattern[6][127][8] = 1;
	M_pattern[6][127][3] = 1;	M_pattern[6][127][4] = 1;	M_pattern[6][127][5] = 0;
	M_pattern[6][127][0] = 0;	M_pattern[6][127][1] = 1;	M_pattern[6][127][2] = 0;
	M_pattern[6][128][6] = 1;	M_pattern[6][128][7] = 0;	M_pattern[6][128][8] = 1;
	M_pattern[6][128][3] = 1;	M_pattern[6][128][4] = 1;	M_pattern[6][128][5] = 0;
	M_pattern[6][128][0] = 0;	M_pattern[6][128][1] = 1;	M_pattern[6][128][2] = 1;
	M_pattern[6][129][6] = 1;	M_pattern[6][129][7] = 0;	M_pattern[6][129][8] = 1;
	M_pattern[6][129][3] = 1;	M_pattern[6][129][4] = 1;	M_pattern[6][129][5] = 0;
	M_pattern[6][129][0] = 1;	M_pattern[6][129][1] = 0;	M_pattern[6][129][2] = 0;
	M_pattern[6][130][6] = 1;	M_pattern[6][130][7] = 0;	M_pattern[6][130][8] = 1;
	M_pattern[6][130][3] = 1;	M_pattern[6][130][4] = 1;	M_pattern[6][130][5] = 0;
	M_pattern[6][130][0] = 1;	M_pattern[6][130][1] = 0;	M_pattern[6][130][2] = 1;
	M_pattern[6][131][6] = 1;	M_pattern[6][131][7] = 0;	M_pattern[6][131][8] = 1;
	M_pattern[6][131][3] = 1;	M_pattern[6][131][4] = 1;	M_pattern[6][131][5] = 0;
	M_pattern[6][131][0] = 1;	M_pattern[6][131][1] = 1;	M_pattern[6][131][2] = 0;
	M_pattern[6][132][6] = 1;	M_pattern[6][132][7] = 0;	M_pattern[6][132][8] = 1;
	M_pattern[6][132][3] = 1;	M_pattern[6][132][4] = 1;	M_pattern[6][132][5] = 0;
	M_pattern[6][132][0] = 1;	M_pattern[6][132][1] = 1;	M_pattern[6][132][2] = 1;
	M_pattern[6][133][6] = 1;	M_pattern[6][133][7] = 0;	M_pattern[6][133][8] = 1;
	M_pattern[6][133][3] = 1;	M_pattern[6][133][4] = 1;	M_pattern[6][133][5] = 1;
	M_pattern[6][133][0] = 0;	M_pattern[6][133][1] = 0;	M_pattern[6][133][2] = 1;
	M_pattern[6][134][6] = 1;	M_pattern[6][134][7] = 0;	M_pattern[6][134][8] = 1;
	M_pattern[6][134][3] = 1;	M_pattern[6][134][4] = 1;	M_pattern[6][134][5] = 1;
	M_pattern[6][134][0] = 0;	M_pattern[6][134][1] = 1;	M_pattern[6][134][2] = 0;
	M_pattern[6][135][6] = 1;	M_pattern[6][135][7] = 0;	M_pattern[6][135][8] = 1;
	M_pattern[6][135][3] = 1;	M_pattern[6][135][4] = 1;	M_pattern[6][135][5] = 1;
	M_pattern[6][135][0] = 0;	M_pattern[6][135][1] = 1;	M_pattern[6][135][2] = 1;
	M_pattern[6][136][6] = 1;	M_pattern[6][136][7] = 0;	M_pattern[6][136][8] = 1;
	M_pattern[6][136][3] = 1;	M_pattern[6][136][4] = 1;	M_pattern[6][136][5] = 1;
	M_pattern[6][136][0] = 1;	M_pattern[6][136][1] = 0;	M_pattern[6][136][2] = 0;
	M_pattern[6][137][6] = 1;	M_pattern[6][137][7] = 0;	M_pattern[6][137][8] = 1;
	M_pattern[6][137][3] = 1;	M_pattern[6][137][4] = 1;	M_pattern[6][137][5] = 1;
	M_pattern[6][137][0] = 1;	M_pattern[6][137][1] = 0;	M_pattern[6][137][2] = 1;
	M_pattern[6][138][6] = 1;	M_pattern[6][138][7] = 0;	M_pattern[6][138][8] = 1;
	M_pattern[6][138][3] = 1;	M_pattern[6][138][4] = 1;	M_pattern[6][138][5] = 1;
	M_pattern[6][138][0] = 1;	M_pattern[6][138][1] = 1;	M_pattern[6][138][2] = 0;
	M_pattern[6][139][6] = 1;	M_pattern[6][139][7] = 0;	M_pattern[6][139][8] = 1;
	M_pattern[6][139][3] = 1;	M_pattern[6][139][4] = 1;	M_pattern[6][139][5] = 1;
	M_pattern[6][139][0] = 1;	M_pattern[6][139][1] = 1;	M_pattern[6][139][2] = 1;
	M_pattern[6][140][6] = 1;	M_pattern[6][140][7] = 1;	M_pattern[6][140][8] = 1;
	M_pattern[6][140][3] = 0;	M_pattern[6][140][4] = 1;	M_pattern[6][140][5] = 0;
	M_pattern[6][140][0] = 0;	M_pattern[6][140][1] = 0;	M_pattern[6][140][2] = 1;
	M_pattern[6][141][6] = 1;	M_pattern[6][141][7] = 1;	M_pattern[6][141][8] = 1;
	M_pattern[6][141][3] = 0;	M_pattern[6][141][4] = 1;	M_pattern[6][141][5] = 0;
	M_pattern[6][141][0] = 0;	M_pattern[6][141][1] = 1;	M_pattern[6][141][2] = 0;
	M_pattern[6][142][6] = 1;	M_pattern[6][142][7] = 1;	M_pattern[6][142][8] = 1;
	M_pattern[6][142][3] = 0;	M_pattern[6][142][4] = 1;	M_pattern[6][142][5] = 0;
	M_pattern[6][142][0] = 0;	M_pattern[6][142][1] = 1;	M_pattern[6][142][2] = 1;
	M_pattern[6][143][6] = 1;	M_pattern[6][143][7] = 1;	M_pattern[6][143][8] = 1;
	M_pattern[6][143][3] = 0;	M_pattern[6][143][4] = 1;	M_pattern[6][143][5] = 0;
	M_pattern[6][143][0] = 1;	M_pattern[6][143][1] = 0;	M_pattern[6][143][2] = 0;
	M_pattern[6][144][6] = 1;	M_pattern[6][144][7] = 1;	M_pattern[6][144][8] = 1;
	M_pattern[6][144][3] = 0;	M_pattern[6][144][4] = 1;	M_pattern[6][144][5] = 0;
	M_pattern[6][144][0] = 1;	M_pattern[6][144][1] = 0;	M_pattern[6][144][2] = 1;
	M_pattern[6][145][6] = 1;	M_pattern[6][145][7] = 1;	M_pattern[6][145][8] = 1;
	M_pattern[6][145][3] = 0;	M_pattern[6][145][4] = 1;	M_pattern[6][145][5] = 0;
	M_pattern[6][145][0] = 1;	M_pattern[6][145][1] = 1;	M_pattern[6][145][2] = 0;
	M_pattern[6][146][6] = 1;	M_pattern[6][146][7] = 1;	M_pattern[6][146][8] = 1;
	M_pattern[6][146][3] = 0;	M_pattern[6][146][4] = 1;	M_pattern[6][146][5] = 0;
	M_pattern[6][146][0] = 1;	M_pattern[6][146][1] = 1;	M_pattern[6][146][2] = 1;
	M_pattern[6][147][6] = 1;	M_pattern[6][147][7] = 1;	M_pattern[6][147][8] = 1;
	M_pattern[6][147][3] = 0;	M_pattern[6][147][4] = 1;	M_pattern[6][147][5] = 1;
	M_pattern[6][147][0] = 0;	M_pattern[6][147][1] = 0;	M_pattern[6][147][2] = 1;
	M_pattern[6][148][6] = 1;	M_pattern[6][148][7] = 1;	M_pattern[6][148][8] = 1;
	M_pattern[6][148][3] = 0;	M_pattern[6][148][4] = 1;	M_pattern[6][148][5] = 1;
	M_pattern[6][148][0] = 0;	M_pattern[6][148][1] = 1;	M_pattern[6][148][2] = 0;
	M_pattern[6][149][6] = 1;	M_pattern[6][149][7] = 1;	M_pattern[6][149][8] = 1;
	M_pattern[6][149][3] = 0;	M_pattern[6][149][4] = 1;	M_pattern[6][149][5] = 1;
	M_pattern[6][149][0] = 0;	M_pattern[6][149][1] = 1;	M_pattern[6][149][2] = 1;
	M_pattern[6][150][6] = 1;	M_pattern[6][150][7] = 1;	M_pattern[6][150][8] = 1;
	M_pattern[6][150][3] = 0;	M_pattern[6][150][4] = 1;	M_pattern[6][150][5] = 1;
	M_pattern[6][150][0] = 1;	M_pattern[6][150][1] = 0;	M_pattern[6][150][2] = 0;
	M_pattern[6][151][6] = 1;	M_pattern[6][151][7] = 1;	M_pattern[6][151][8] = 1;
	M_pattern[6][151][3] = 0;	M_pattern[6][151][4] = 1;	M_pattern[6][151][5] = 1;
	M_pattern[6][151][0] = 1;	M_pattern[6][151][1] = 0;	M_pattern[6][151][2] = 1;
	M_pattern[6][152][6] = 1;	M_pattern[6][152][7] = 1;	M_pattern[6][152][8] = 1;
	M_pattern[6][152][3] = 0;	M_pattern[6][152][4] = 1;	M_pattern[6][152][5] = 1;
	M_pattern[6][152][0] = 1;	M_pattern[6][152][1] = 1;	M_pattern[6][152][2] = 0;
	M_pattern[6][153][6] = 1;	M_pattern[6][153][7] = 1;	M_pattern[6][153][8] = 1;
	M_pattern[6][153][3] = 0;	M_pattern[6][153][4] = 1;	M_pattern[6][153][5] = 1;
	M_pattern[6][153][0] = 1;	M_pattern[6][153][1] = 1;	M_pattern[6][153][2] = 1;
	M_pattern[6][154][6] = 1;	M_pattern[6][154][7] = 1;	M_pattern[6][154][8] = 1;
	M_pattern[6][154][3] = 1;	M_pattern[6][154][4] = 1;	M_pattern[6][154][5] = 0;
	M_pattern[6][154][0] = 0;	M_pattern[6][154][1] = 0;	M_pattern[6][154][2] = 1;
	M_pattern[6][155][6] = 1;	M_pattern[6][155][7] = 1;	M_pattern[6][155][8] = 1;
	M_pattern[6][155][3] = 1;	M_pattern[6][155][4] = 1;	M_pattern[6][155][5] = 0;
	M_pattern[6][155][0] = 0;	M_pattern[6][155][1] = 1;	M_pattern[6][155][2] = 0;
	M_pattern[6][156][6] = 1;	M_pattern[6][156][7] = 1;	M_pattern[6][156][8] = 1;
	M_pattern[6][156][3] = 1;	M_pattern[6][156][4] = 1;	M_pattern[6][156][5] = 0;
	M_pattern[6][156][0] = 0;	M_pattern[6][156][1] = 1;	M_pattern[6][156][2] = 1;
	M_pattern[6][157][6] = 1;	M_pattern[6][157][7] = 1;	M_pattern[6][157][8] = 1;
	M_pattern[6][157][3] = 1;	M_pattern[6][157][4] = 1;	M_pattern[6][157][5] = 0;
	M_pattern[6][157][0] = 1;	M_pattern[6][157][1] = 0;	M_pattern[6][157][2] = 0;
	M_pattern[6][158][6] = 1;	M_pattern[6][158][7] = 1;	M_pattern[6][158][8] = 1;
	M_pattern[6][158][3] = 1;	M_pattern[6][158][4] = 1;	M_pattern[6][158][5] = 0;
	M_pattern[6][158][0] = 1;	M_pattern[6][158][1] = 0;	M_pattern[6][158][2] = 1;
	M_pattern[6][159][6] = 1;	M_pattern[6][159][7] = 1;	M_pattern[6][159][8] = 1;
	M_pattern[6][159][3] = 1;	M_pattern[6][159][4] = 1;	M_pattern[6][159][5] = 0;
	M_pattern[6][159][0] = 1;	M_pattern[6][159][1] = 1;	M_pattern[6][159][2] = 0;
	M_pattern[6][160][6] = 1;	M_pattern[6][160][7] = 1;	M_pattern[6][160][8] = 1;
	M_pattern[6][160][3] = 1;	M_pattern[6][160][4] = 1;	M_pattern[6][160][5] = 0;
	M_pattern[6][160][0] = 1;	M_pattern[6][160][1] = 1;	M_pattern[6][160][2] = 1;
	M_pattern[6][161][6] = 1;	M_pattern[6][161][7] = 1;	M_pattern[6][161][8] = 1;
	M_pattern[6][161][3] = 1;	M_pattern[6][161][4] = 1;	M_pattern[6][161][5] = 1;
	M_pattern[6][161][0] = 0;	M_pattern[6][161][1] = 0;	M_pattern[6][161][2] = 1;
	M_pattern[6][162][6] = 1;	M_pattern[6][162][7] = 1;	M_pattern[6][162][8] = 1;
	M_pattern[6][162][3] = 1;	M_pattern[6][162][4] = 1;	M_pattern[6][162][5] = 1;
	M_pattern[6][162][0] = 0;	M_pattern[6][162][1] = 1;	M_pattern[6][162][2] = 0;
	M_pattern[6][163][6] = 1;	M_pattern[6][163][7] = 1;	M_pattern[6][163][8] = 1;
	M_pattern[6][163][3] = 1;	M_pattern[6][163][4] = 1;	M_pattern[6][163][5] = 1;
	M_pattern[6][163][0] = 0;	M_pattern[6][163][1] = 1;	M_pattern[6][163][2] = 1;
	M_pattern[6][164][6] = 1;	M_pattern[6][164][7] = 1;	M_pattern[6][164][8] = 1;
	M_pattern[6][164][3] = 1;	M_pattern[6][164][4] = 1;	M_pattern[6][164][5] = 1;
	M_pattern[6][164][0] = 1;	M_pattern[6][164][1] = 0;	M_pattern[6][164][2] = 0;
	M_pattern[6][165][6] = 1;	M_pattern[6][165][7] = 1;	M_pattern[6][165][8] = 1;
	M_pattern[6][165][3] = 1;	M_pattern[6][165][4] = 1;	M_pattern[6][165][5] = 1;
	M_pattern[6][165][0] = 1;	M_pattern[6][165][1] = 0;	M_pattern[6][165][2] = 1;
	M_pattern[6][166][6] = 1;	M_pattern[6][166][7] = 1;	M_pattern[6][166][8] = 1;
	M_pattern[6][166][3] = 1;	M_pattern[6][166][4] = 1;	M_pattern[6][166][5] = 1;
	M_pattern[6][166][0] = 1;	M_pattern[6][166][1] = 1;	M_pattern[6][166][2] = 0;
	M_pattern[6][167][6] = 1;	M_pattern[6][167][7] = 1;	M_pattern[6][167][8] = 1;
	M_pattern[6][167][3] = 1;	M_pattern[6][167][4] = 1;	M_pattern[6][167][5] = 1;
	M_pattern[6][167][0] = 1;	M_pattern[6][167][1] = 1;	M_pattern[6][167][2] = 1;



	M_pattern[6][168][6] = 1;	M_pattern[6][168][3] = 0;	M_pattern[6][168][0] = 1;
	M_pattern[6][168][7] = 0;	M_pattern[6][168][4] = 1;	M_pattern[6][168][1] = 0;
	M_pattern[6][168][8] = 0;	M_pattern[6][168][5] = 0;	M_pattern[6][168][2] = 1;
	M_pattern[6][169][6] = 1;	M_pattern[6][169][3] = 0;	M_pattern[6][169][0] = 1;
	M_pattern[6][169][7] = 0;	M_pattern[6][169][4] = 1;	M_pattern[6][169][1] = 0;
	M_pattern[6][169][8] = 0;	M_pattern[6][169][5] = 1;	M_pattern[6][169][2] = 0;
	M_pattern[6][170][6] = 1;	M_pattern[6][170][3] = 0;	M_pattern[6][170][0] = 1;
	M_pattern[6][170][7] = 0;	M_pattern[6][170][4] = 1;	M_pattern[6][170][1] = 0;
	M_pattern[6][170][8] = 0;	M_pattern[6][170][5] = 1;	M_pattern[6][170][2] = 1;
	M_pattern[6][171][6] = 1;	M_pattern[6][171][3] = 0;	M_pattern[6][171][0] = 1;
	M_pattern[6][171][7] = 0;	M_pattern[6][171][4] = 1;	M_pattern[6][171][1] = 0;
	M_pattern[6][171][8] = 1;	M_pattern[6][171][5] = 0;	M_pattern[6][171][2] = 0;
	M_pattern[6][172][6] = 1;	M_pattern[6][172][3] = 0;	M_pattern[6][172][0] = 1;
	M_pattern[6][172][7] = 0;	M_pattern[6][172][4] = 1;	M_pattern[6][172][1] = 0;
	M_pattern[6][172][8] = 1;	M_pattern[6][172][5] = 0;	M_pattern[6][172][2] = 1;
	M_pattern[6][173][6] = 1;	M_pattern[6][173][3] = 0;	M_pattern[6][173][0] = 1;
	M_pattern[6][173][7] = 0;	M_pattern[6][173][4] = 1;	M_pattern[6][173][1] = 0;
	M_pattern[6][173][8] = 1;	M_pattern[6][173][5] = 1;	M_pattern[6][173][2] = 0;
	M_pattern[6][174][6] = 1;	M_pattern[6][174][3] = 0;	M_pattern[6][174][0] = 1;
	M_pattern[6][174][7] = 0;	M_pattern[6][174][4] = 1;	M_pattern[6][174][1] = 0;
	M_pattern[6][174][8] = 1;	M_pattern[6][174][5] = 1;	M_pattern[6][174][2] = 1;
	M_pattern[6][175][6] = 1;	M_pattern[6][175][3] = 0;	M_pattern[6][175][0] = 1;
	M_pattern[6][175][7] = 0;	M_pattern[6][175][4] = 1;	M_pattern[6][175][1] = 1;
	M_pattern[6][175][8] = 0;	M_pattern[6][175][5] = 0;	M_pattern[6][175][2] = 1;
	M_pattern[6][176][6] = 1;	M_pattern[6][176][3] = 0;	M_pattern[6][176][0] = 1;
	M_pattern[6][176][7] = 0;	M_pattern[6][176][4] = 1;	M_pattern[6][176][1] = 1;
	M_pattern[6][176][8] = 0;	M_pattern[6][176][5] = 1;	M_pattern[6][176][2] = 0;
	M_pattern[6][177][6] = 1;	M_pattern[6][177][3] = 0;	M_pattern[6][177][0] = 1;
	M_pattern[6][177][7] = 0;	M_pattern[6][177][4] = 1;	M_pattern[6][177][1] = 1;
	M_pattern[6][177][8] = 0;	M_pattern[6][177][5] = 1;	M_pattern[6][177][2] = 1;
	M_pattern[6][178][6] = 1;	M_pattern[6][178][3] = 0;	M_pattern[6][178][0] = 1;
	M_pattern[6][178][7] = 0;	M_pattern[6][178][4] = 1;	M_pattern[6][178][1] = 1;
	M_pattern[6][178][8] = 1;	M_pattern[6][178][5] = 0;	M_pattern[6][178][2] = 0;
	M_pattern[6][179][6] = 1;	M_pattern[6][179][3] = 0;	M_pattern[6][179][0] = 1;
	M_pattern[6][179][7] = 0;	M_pattern[6][179][4] = 1;	M_pattern[6][179][1] = 1;
	M_pattern[6][179][8] = 1;	M_pattern[6][179][5] = 0;	M_pattern[6][179][2] = 1;
	M_pattern[6][180][6] = 1;	M_pattern[6][180][3] = 0;	M_pattern[6][180][0] = 1;
	M_pattern[6][180][7] = 0;	M_pattern[6][180][4] = 1;	M_pattern[6][180][1] = 1;
	M_pattern[6][180][8] = 1;	M_pattern[6][180][5] = 1;	M_pattern[6][180][2] = 0;
	M_pattern[6][181][6] = 1;	M_pattern[6][181][3] = 0;	M_pattern[6][181][0] = 1;
	M_pattern[6][181][7] = 0;	M_pattern[6][181][4] = 1;	M_pattern[6][181][1] = 1;
	M_pattern[6][181][8] = 1;	M_pattern[6][181][5] = 1;	M_pattern[6][181][2] = 1;
	M_pattern[6][182][6] = 1;	M_pattern[6][182][3] = 0;	M_pattern[6][182][0] = 1;
	M_pattern[6][182][7] = 1;	M_pattern[6][182][4] = 1;	M_pattern[6][182][1] = 0;
	M_pattern[6][182][8] = 0;	M_pattern[6][182][5] = 0;	M_pattern[6][182][2] = 1;
	M_pattern[6][183][6] = 1;	M_pattern[6][183][3] = 0;	M_pattern[6][183][0] = 1;
	M_pattern[6][183][7] = 1;	M_pattern[6][183][4] = 1;	M_pattern[6][183][1] = 0;
	M_pattern[6][183][8] = 0;	M_pattern[6][183][5] = 1;	M_pattern[6][183][2] = 0;
	M_pattern[6][184][6] = 1;	M_pattern[6][184][3] = 0;	M_pattern[6][184][0] = 1;
	M_pattern[6][184][7] = 1;	M_pattern[6][184][4] = 1;	M_pattern[6][184][1] = 0;
	M_pattern[6][184][8] = 0;	M_pattern[6][184][5] = 1;	M_pattern[6][184][2] = 1;
	M_pattern[6][185][6] = 1;	M_pattern[6][185][3] = 0;	M_pattern[6][185][0] = 1;
	M_pattern[6][185][7] = 1;	M_pattern[6][185][4] = 1;	M_pattern[6][185][1] = 0;
	M_pattern[6][185][8] = 1;	M_pattern[6][185][5] = 0;	M_pattern[6][185][2] = 0;
	M_pattern[6][186][6] = 1;	M_pattern[6][186][3] = 0;	M_pattern[6][186][0] = 1;
	M_pattern[6][186][7] = 1;	M_pattern[6][186][4] = 1;	M_pattern[6][186][1] = 0;
	M_pattern[6][186][8] = 1;	M_pattern[6][186][5] = 0;	M_pattern[6][186][2] = 1;
	M_pattern[6][187][6] = 1;	M_pattern[6][187][3] = 0;	M_pattern[6][187][0] = 1;
	M_pattern[6][187][7] = 1;	M_pattern[6][187][4] = 1;	M_pattern[6][187][1] = 0;
	M_pattern[6][187][8] = 1;	M_pattern[6][187][5] = 1;	M_pattern[6][187][2] = 0;
	M_pattern[6][188][6] = 1;	M_pattern[6][188][3] = 0;	M_pattern[6][188][0] = 1;
	M_pattern[6][188][7] = 1;	M_pattern[6][188][4] = 1;	M_pattern[6][188][1] = 0;
	M_pattern[6][188][8] = 1;	M_pattern[6][188][5] = 1;	M_pattern[6][188][2] = 1;
	M_pattern[6][189][6] = 1;	M_pattern[6][189][3] = 0;	M_pattern[6][189][0] = 1;
	M_pattern[6][189][7] = 1;	M_pattern[6][189][4] = 1;	M_pattern[6][189][1] = 1;
	M_pattern[6][189][8] = 0;	M_pattern[6][189][5] = 0;	M_pattern[6][189][2] = 1;
	M_pattern[6][190][6] = 1;	M_pattern[6][190][3] = 0;	M_pattern[6][190][0] = 1;
	M_pattern[6][190][7] = 1;	M_pattern[6][190][4] = 1;	M_pattern[6][190][1] = 1;
	M_pattern[6][190][8] = 0;	M_pattern[6][190][5] = 1;	M_pattern[6][190][2] = 0;
	M_pattern[6][191][6] = 1;	M_pattern[6][191][3] = 0;	M_pattern[6][191][0] = 1;
	M_pattern[6][191][7] = 1;	M_pattern[6][191][4] = 1;	M_pattern[6][191][1] = 1;
	M_pattern[6][191][8] = 0;	M_pattern[6][191][5] = 1;	M_pattern[6][191][2] = 1;
	M_pattern[6][192][6] = 1;	M_pattern[6][192][3] = 0;	M_pattern[6][192][0] = 1;
	M_pattern[6][192][7] = 1;	M_pattern[6][192][4] = 1;	M_pattern[6][192][1] = 1;
	M_pattern[6][192][8] = 1;	M_pattern[6][192][5] = 0;	M_pattern[6][192][2] = 0;
	M_pattern[6][193][6] = 1;	M_pattern[6][193][3] = 0;	M_pattern[6][193][0] = 1;
	M_pattern[6][193][7] = 1;	M_pattern[6][193][4] = 1;	M_pattern[6][193][1] = 1;
	M_pattern[6][193][8] = 1;	M_pattern[6][193][5] = 0;	M_pattern[6][193][2] = 1;
	M_pattern[6][194][6] = 1;	M_pattern[6][194][3] = 0;	M_pattern[6][194][0] = 1;
	M_pattern[6][194][7] = 1;	M_pattern[6][194][4] = 1;	M_pattern[6][194][1] = 1;
	M_pattern[6][194][8] = 1;	M_pattern[6][194][5] = 1;	M_pattern[6][194][2] = 0;
	M_pattern[6][195][6] = 1;	M_pattern[6][195][3] = 0;	M_pattern[6][195][0] = 1;
	M_pattern[6][195][7] = 1;	M_pattern[6][195][4] = 1;	M_pattern[6][195][1] = 1;
	M_pattern[6][195][8] = 1;	M_pattern[6][195][5] = 1;	M_pattern[6][195][2] = 1;
	M_pattern[6][196][6] = 1;	M_pattern[6][196][3] = 1;	M_pattern[6][196][0] = 1;
	M_pattern[6][196][7] = 0;	M_pattern[6][196][4] = 1;	M_pattern[6][196][1] = 0;
	M_pattern[6][196][8] = 0;	M_pattern[6][196][5] = 0;	M_pattern[6][196][2] = 1;
	M_pattern[6][197][6] = 1;	M_pattern[6][197][3] = 1;	M_pattern[6][197][0] = 1;
	M_pattern[6][197][7] = 0;	M_pattern[6][197][4] = 1;	M_pattern[6][197][1] = 0;
	M_pattern[6][197][8] = 0;	M_pattern[6][197][5] = 1;	M_pattern[6][197][2] = 0;
	M_pattern[6][198][6] = 1;	M_pattern[6][198][3] = 1;	M_pattern[6][198][0] = 1;
	M_pattern[6][198][7] = 0;	M_pattern[6][198][4] = 1;	M_pattern[6][198][1] = 0;
	M_pattern[6][198][8] = 0;	M_pattern[6][198][5] = 1;	M_pattern[6][198][2] = 1;
	M_pattern[6][199][6] = 1;	M_pattern[6][199][3] = 1;	M_pattern[6][199][0] = 1;
	M_pattern[6][199][7] = 0;	M_pattern[6][199][4] = 1;	M_pattern[6][199][1] = 0;
	M_pattern[6][199][8] = 1;	M_pattern[6][199][5] = 0;	M_pattern[6][199][2] = 0;
	M_pattern[6][200][6] = 1;	M_pattern[6][200][3] = 1;	M_pattern[6][200][0] = 1;
	M_pattern[6][200][7] = 0;	M_pattern[6][200][4] = 1;	M_pattern[6][200][1] = 0;
	M_pattern[6][200][8] = 1;	M_pattern[6][200][5] = 0;	M_pattern[6][200][2] = 1;
	M_pattern[6][201][6] = 1;	M_pattern[6][201][3] = 1;	M_pattern[6][201][0] = 1;
	M_pattern[6][201][7] = 0;	M_pattern[6][201][4] = 1;	M_pattern[6][201][1] = 0;
	M_pattern[6][201][8] = 1;	M_pattern[6][201][5] = 1;	M_pattern[6][201][2] = 0;
	M_pattern[6][202][6] = 1;	M_pattern[6][202][3] = 1;	M_pattern[6][202][0] = 1;
	M_pattern[6][202][7] = 0;	M_pattern[6][202][4] = 1;	M_pattern[6][202][1] = 0;
	M_pattern[6][202][8] = 1;	M_pattern[6][202][5] = 1;	M_pattern[6][202][2] = 1;
	M_pattern[6][203][6] = 1;	M_pattern[6][203][3] = 1;	M_pattern[6][203][0] = 1;
	M_pattern[6][203][7] = 0;	M_pattern[6][203][4] = 1;	M_pattern[6][203][1] = 1;
	M_pattern[6][203][8] = 0;	M_pattern[6][203][5] = 0;	M_pattern[6][203][2] = 1;
	M_pattern[6][204][6] = 1;	M_pattern[6][204][3] = 1;	M_pattern[6][204][0] = 1;
	M_pattern[6][204][7] = 0;	M_pattern[6][204][4] = 1;	M_pattern[6][204][1] = 1;
	M_pattern[6][204][8] = 0;	M_pattern[6][204][5] = 1;	M_pattern[6][204][2] = 0;
	M_pattern[6][205][6] = 1;	M_pattern[6][205][3] = 1;	M_pattern[6][205][0] = 1;
	M_pattern[6][205][7] = 0;	M_pattern[6][205][4] = 1;	M_pattern[6][205][1] = 1;
	M_pattern[6][205][8] = 0;	M_pattern[6][205][5] = 1;	M_pattern[6][205][2] = 1;
	M_pattern[6][206][6] = 1;	M_pattern[6][206][3] = 1;	M_pattern[6][206][0] = 1;
	M_pattern[6][206][7] = 0;	M_pattern[6][206][4] = 1;	M_pattern[6][206][1] = 1;
	M_pattern[6][206][8] = 1;	M_pattern[6][206][5] = 0;	M_pattern[6][206][2] = 0;
	M_pattern[6][207][6] = 1;	M_pattern[6][207][3] = 1;	M_pattern[6][207][0] = 1;
	M_pattern[6][207][7] = 0;	M_pattern[6][207][4] = 1;	M_pattern[6][207][1] = 1;
	M_pattern[6][207][8] = 1;	M_pattern[6][207][5] = 0;	M_pattern[6][207][2] = 1;
	M_pattern[6][208][6] = 1;	M_pattern[6][208][3] = 1;	M_pattern[6][208][0] = 1;
	M_pattern[6][208][7] = 0;	M_pattern[6][208][4] = 1;	M_pattern[6][208][1] = 1;
	M_pattern[6][208][8] = 1;	M_pattern[6][208][5] = 1;	M_pattern[6][208][2] = 0;
	M_pattern[6][209][6] = 1;	M_pattern[6][209][3] = 1;	M_pattern[6][209][0] = 1;
	M_pattern[6][209][7] = 0;	M_pattern[6][209][4] = 1;	M_pattern[6][209][1] = 1;
	M_pattern[6][209][8] = 1;	M_pattern[6][209][5] = 1;	M_pattern[6][209][2] = 1;
	M_pattern[6][210][6] = 1;	M_pattern[6][210][3] = 1;	M_pattern[6][210][0] = 1;
	M_pattern[6][210][7] = 1;	M_pattern[6][210][4] = 1;	M_pattern[6][210][1] = 0;
	M_pattern[6][210][8] = 0;	M_pattern[6][210][5] = 0;	M_pattern[6][210][2] = 1;
	M_pattern[6][211][6] = 1;	M_pattern[6][211][3] = 1;	M_pattern[6][211][0] = 1;
	M_pattern[6][211][7] = 1;	M_pattern[6][211][4] = 1;	M_pattern[6][211][1] = 0;
	M_pattern[6][211][8] = 0;	M_pattern[6][211][5] = 1;	M_pattern[6][211][2] = 0;
	M_pattern[6][212][6] = 1;	M_pattern[6][212][3] = 1;	M_pattern[6][212][0] = 1;
	M_pattern[6][212][7] = 1;	M_pattern[6][212][4] = 1;	M_pattern[6][212][1] = 0;
	M_pattern[6][212][8] = 0;	M_pattern[6][212][5] = 1;	M_pattern[6][212][2] = 1;
	M_pattern[6][213][6] = 1;	M_pattern[6][213][3] = 1;	M_pattern[6][213][0] = 1;
	M_pattern[6][213][7] = 1;	M_pattern[6][213][4] = 1;	M_pattern[6][213][1] = 0;
	M_pattern[6][213][8] = 1;	M_pattern[6][213][5] = 0;	M_pattern[6][213][2] = 0;
	M_pattern[6][214][6] = 1;	M_pattern[6][214][3] = 1;	M_pattern[6][214][0] = 1;
	M_pattern[6][214][7] = 1;	M_pattern[6][214][4] = 1;	M_pattern[6][214][1] = 0;
	M_pattern[6][214][8] = 1;	M_pattern[6][214][5] = 0;	M_pattern[6][214][2] = 1;
	M_pattern[6][215][6] = 1;	M_pattern[6][215][3] = 1;	M_pattern[6][215][0] = 1;
	M_pattern[6][215][7] = 1;	M_pattern[6][215][4] = 1;	M_pattern[6][215][1] = 0;
	M_pattern[6][215][8] = 1;	M_pattern[6][215][5] = 1;	M_pattern[6][215][2] = 0;
	M_pattern[6][216][6] = 1;	M_pattern[6][216][3] = 1;	M_pattern[6][216][0] = 1;
	M_pattern[6][216][7] = 1;	M_pattern[6][216][4] = 1;	M_pattern[6][216][1] = 0;
	M_pattern[6][216][8] = 1;	M_pattern[6][216][5] = 1;	M_pattern[6][216][2] = 1;
	M_pattern[6][217][6] = 1;	M_pattern[6][217][3] = 1;	M_pattern[6][217][0] = 1;
	M_pattern[6][217][7] = 1;	M_pattern[6][217][4] = 1;	M_pattern[6][217][1] = 1;
	M_pattern[6][217][8] = 0;	M_pattern[6][217][5] = 0;	M_pattern[6][217][2] = 1;
	M_pattern[6][218][6] = 1;	M_pattern[6][218][3] = 1;	M_pattern[6][218][0] = 1;
	M_pattern[6][218][7] = 1;	M_pattern[6][218][4] = 1;	M_pattern[6][218][1] = 1;
	M_pattern[6][218][8] = 0;	M_pattern[6][218][5] = 1;	M_pattern[6][218][2] = 0;
	M_pattern[6][219][6] = 1;	M_pattern[6][219][3] = 1;	M_pattern[6][219][0] = 1;
	M_pattern[6][219][7] = 1;	M_pattern[6][219][4] = 1;	M_pattern[6][219][1] = 1;
	M_pattern[6][219][8] = 0;	M_pattern[6][219][5] = 1;	M_pattern[6][219][2] = 1;
	M_pattern[6][220][6] = 1;	M_pattern[6][220][3] = 1;	M_pattern[6][220][0] = 1;
	M_pattern[6][220][7] = 1;	M_pattern[6][220][4] = 1;	M_pattern[6][220][1] = 1;
	M_pattern[6][220][8] = 1;	M_pattern[6][220][5] = 0;	M_pattern[6][220][2] = 0;
	M_pattern[6][221][6] = 1;	M_pattern[6][221][3] = 1;	M_pattern[6][221][0] = 1;
	M_pattern[6][221][7] = 1;	M_pattern[6][221][4] = 1;	M_pattern[6][221][1] = 1;
	M_pattern[6][221][8] = 1;	M_pattern[6][221][5] = 0;	M_pattern[6][221][2] = 1;
	M_pattern[6][222][6] = 1;	M_pattern[6][222][3] = 1;	M_pattern[6][222][0] = 1;
	M_pattern[6][222][7] = 1;	M_pattern[6][222][4] = 1;	M_pattern[6][222][1] = 1;
	M_pattern[6][222][8] = 1;	M_pattern[6][222][5] = 1;	M_pattern[6][222][2] = 0;
	M_pattern[6][223][6] = 1;	M_pattern[6][223][3] = 1;	M_pattern[6][223][0] = 1;
	M_pattern[6][223][7] = 1;	M_pattern[6][223][4] = 1;	M_pattern[6][223][1] = 1;
	M_pattern[6][223][8] = 1;	M_pattern[6][223][5] = 1;	M_pattern[6][223][2] = 1;






	M_pattern[7][0][0] = 0;	M_pattern[7][0][1] = 1;	M_pattern[7][0][2] = 0;
	M_pattern[7][0][3] = 0;	M_pattern[7][0][4] = 1;	M_pattern[7][0][5] = 1;
	M_pattern[7][0][6] = 1;	M_pattern[7][0][7] = 0;	M_pattern[7][0][8] = 0;
	M_pattern[7][1][0] = 1;	M_pattern[7][1][1] = 1;	M_pattern[7][1][2] = 0;
	M_pattern[7][1][3] = 0;	M_pattern[7][1][4] = 1;	M_pattern[7][1][5] = 1;
	M_pattern[7][1][6] = 1;	M_pattern[7][1][7] = 0;	M_pattern[7][1][8] = 0;
	M_pattern[7][2][0] = 0;	M_pattern[7][2][1] = 1;	M_pattern[7][2][2] = 0;
	M_pattern[7][2][3] = 0;	M_pattern[7][2][4] = 1;	M_pattern[7][2][5] = 1;
	M_pattern[7][2][6] = 1;	M_pattern[7][2][7] = 0;	M_pattern[7][2][8] = 1;
	M_pattern[7][3][0] = 1;	M_pattern[7][3][1] = 1;	M_pattern[7][3][2] = 0;
	M_pattern[7][3][3] = 0;	M_pattern[7][3][4] = 1;	M_pattern[7][3][5] = 1;
	M_pattern[7][3][6] = 1;	M_pattern[7][3][7] = 0;	M_pattern[7][3][8] = 1;



	M_pattern[7][4][2] = 0;	M_pattern[7][4][1] = 1;	M_pattern[7][4][0] = 0;
	M_pattern[7][4][5] = 0;	M_pattern[7][4][4] = 1;	M_pattern[7][4][3] = 1;
	M_pattern[7][4][8] = 1;	M_pattern[7][4][7] = 0;	M_pattern[7][4][6] = 0;
	M_pattern[7][5][2] = 1;	M_pattern[7][5][1] = 1;	M_pattern[7][5][0] = 0;
	M_pattern[7][5][5] = 0;	M_pattern[7][5][4] = 1;	M_pattern[7][5][3] = 1;
	M_pattern[7][5][8] = 1;	M_pattern[7][5][7] = 0;	M_pattern[7][5][6] = 0;
	M_pattern[7][6][2] = 0;	M_pattern[7][6][1] = 1;	M_pattern[7][6][0] = 0;
	M_pattern[7][6][5] = 0;	M_pattern[7][6][4] = 1;	M_pattern[7][6][3] = 1;
	M_pattern[7][6][8] = 1;	M_pattern[7][6][7] = 0;	M_pattern[7][6][6] = 1;
	M_pattern[7][7][2] = 1;	M_pattern[7][7][1] = 1;	M_pattern[7][7][0] = 0;
	M_pattern[7][7][5] = 0;	M_pattern[7][7][4] = 1;	M_pattern[7][7][3] = 1;
	M_pattern[7][7][8] = 1;	M_pattern[7][7][7] = 0;	M_pattern[7][7][6] = 1;



	M_pattern[7][8][8] = 0;	M_pattern[7][8][7] = 1;	M_pattern[7][8][6] = 0;
	M_pattern[7][8][5] = 0;	M_pattern[7][8][4] = 1;	M_pattern[7][8][3] = 1;
	M_pattern[7][8][2] = 1;	M_pattern[7][8][1] = 0;	M_pattern[7][8][0] = 0;
	M_pattern[7][9][8] = 1;	M_pattern[7][9][7] = 1;	M_pattern[7][9][6] = 0;
	M_pattern[7][9][5] = 0;	M_pattern[7][9][4] = 1;	M_pattern[7][9][3] = 1;
	M_pattern[7][9][2] = 1;	M_pattern[7][9][1] = 0;	M_pattern[7][9][0] = 0;
	M_pattern[7][10][8] = 0;	M_pattern[7][10][7] = 1;	M_pattern[7][10][6] = 0;
	M_pattern[7][10][5] = 0;	M_pattern[7][10][4] = 1;	M_pattern[7][10][3] = 1;
	M_pattern[7][10][2] = 1;	M_pattern[7][10][1] = 0;	M_pattern[7][10][0] = 1;
	M_pattern[7][11][8] = 1;	M_pattern[7][11][7] = 1;	M_pattern[7][11][6] = 0;
	M_pattern[7][11][5] = 0;	M_pattern[7][11][4] = 1;	M_pattern[7][11][3] = 1;
	M_pattern[7][11][2] = 1;	M_pattern[7][11][1] = 0;	M_pattern[7][11][0] = 1;



	M_pattern[7][12][6] = 0;	M_pattern[7][12][7] = 1;	M_pattern[7][12][8] = 0;
	M_pattern[7][12][3] = 0;	M_pattern[7][12][4] = 1;	M_pattern[7][12][5] = 1;
	M_pattern[7][12][0] = 1;	M_pattern[7][12][1] = 0;	M_pattern[7][12][2] = 0;
	M_pattern[7][13][6] = 1;	M_pattern[7][13][7] = 1;	M_pattern[7][13][8] = 0;
	M_pattern[7][13][3] = 0;	M_pattern[7][13][4] = 1;	M_pattern[7][13][5] = 1;
	M_pattern[7][13][0] = 1;	M_pattern[7][13][1] = 0;	M_pattern[7][13][2] = 0;
	M_pattern[7][14][6] = 0;	M_pattern[7][14][7] = 1;	M_pattern[7][14][8] = 0;
	M_pattern[7][14][3] = 0;	M_pattern[7][14][4] = 1;	M_pattern[7][14][5] = 1;
	M_pattern[7][14][0] = 1;	M_pattern[7][14][1] = 0;	M_pattern[7][14][2] = 1;
	M_pattern[7][15][6] = 1;	M_pattern[7][15][7] = 1;	M_pattern[7][15][8] = 0;
	M_pattern[7][15][3] = 0;	M_pattern[7][15][4] = 1;	M_pattern[7][15][5] = 1;
	M_pattern[7][15][0] = 1;	M_pattern[7][15][1] = 0;	M_pattern[7][15][2] = 1;





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