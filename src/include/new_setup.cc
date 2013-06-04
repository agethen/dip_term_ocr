#include "new_setup.hh"

using namespace std;

unsigned char ***hit_matrices;
vector<int> num;
int *x_map = new int[9];
int *hash_lut_hit = new int[1024];

void setup_matrix()
{
	x_map[5] = 2;	x_map[2] = 4;	x_map[1] = 8;
	x_map[0] = 16;	x_map[3] = 32;	x_map[6] = 64;
	x_map[7] = 128;	x_map[8] = 512;	x_map[4] = 0;
	num.push_back(4);	num.push_back(4);	num.push_back(4);	num.push_back(4);
	num.push_back(4);	num.push_back(4);	num.push_back(4);	num.push_back(4);
	hit_matrices = new unsigned char **[8];
	for(int i = 0; i < num.size(); i++)
	{
		hit_matrices[i] = new unsigned char *[num[i]];
		for(int j = 0; j < num[i]; j++)
		{
			hit_matrices[i][j] = new unsigned char[9];
		}
	}


	hit_matrices[0][0][0] = 0;	hit_matrices[0][0][1] = 0;	hit_matrices[0][0][2] = 0;
	hit_matrices[0][0][3] = 0;	hit_matrices[0][0][4] = 1;	hit_matrices[0][0][5] = 0;
	hit_matrices[0][0][6] = 1;	hit_matrices[0][0][7] = 1;	hit_matrices[0][0][8] = 1;


	hit_matrices[0][1][0] = 0;	hit_matrices[0][1][1] = 0;	hit_matrices[0][1][2] = 0;
	hit_matrices[0][1][3] = 1;	hit_matrices[0][1][4] = 1;	hit_matrices[0][1][5] = 0;
	hit_matrices[0][1][6] = 1;	hit_matrices[0][1][7] = 1;	hit_matrices[0][1][8] = 1;


	hit_matrices[0][2][0] = 0;	hit_matrices[0][2][1] = 0;	hit_matrices[0][2][2] = 0;
	hit_matrices[0][2][3] = 0;	hit_matrices[0][2][4] = 1;	hit_matrices[0][2][5] = 1;
	hit_matrices[0][2][6] = 1;	hit_matrices[0][2][7] = 1;	hit_matrices[0][2][8] = 1;


	hit_matrices[0][3][0] = 0;	hit_matrices[0][3][1] = 0;	hit_matrices[0][3][2] = 0;
	hit_matrices[0][3][3] = 1;	hit_matrices[0][3][4] = 1;	hit_matrices[0][3][5] = 1;
	hit_matrices[0][3][6] = 1;	hit_matrices[0][3][7] = 1;	hit_matrices[0][3][8] = 1;





	hit_matrices[1][0][0] = 0;	hit_matrices[1][0][1] = 0;	hit_matrices[1][0][2] = 0;
	hit_matrices[1][0][3] = 1;	hit_matrices[1][0][4] = 1;	hit_matrices[1][0][5] = 0;
	hit_matrices[1][0][6] = 1;	hit_matrices[1][0][7] = 1;	hit_matrices[1][0][8] = 0;


	hit_matrices[1][1][0] = 1;	hit_matrices[1][1][1] = 0;	hit_matrices[1][1][2] = 0;
	hit_matrices[1][1][3] = 1;	hit_matrices[1][1][4] = 1;	hit_matrices[1][1][5] = 0;
	hit_matrices[1][1][6] = 1;	hit_matrices[1][1][7] = 1;	hit_matrices[1][1][8] = 0;


	hit_matrices[1][2][0] = 0;	hit_matrices[1][2][1] = 0;	hit_matrices[1][2][2] = 0;
	hit_matrices[1][2][3] = 1;	hit_matrices[1][2][4] = 1;	hit_matrices[1][2][5] = 0;
	hit_matrices[1][2][6] = 1;	hit_matrices[1][2][7] = 1;	hit_matrices[1][2][8] = 1;


	hit_matrices[1][3][0] = 1;	hit_matrices[1][3][1] = 0;	hit_matrices[1][3][2] = 0;
	hit_matrices[1][3][3] = 1;	hit_matrices[1][3][4] = 1;	hit_matrices[1][3][5] = 0;
	hit_matrices[1][3][6] = 1;	hit_matrices[1][3][7] = 1;	hit_matrices[1][3][8] = 1;





	hit_matrices[2][0][0] = 1;	hit_matrices[2][0][1] = 0;	hit_matrices[2][0][2] = 0;
	hit_matrices[2][0][3] = 1;	hit_matrices[2][0][4] = 1;	hit_matrices[2][0][5] = 0;
	hit_matrices[2][0][6] = 1;	hit_matrices[2][0][7] = 0;	hit_matrices[2][0][8] = 0;


	hit_matrices[2][1][0] = 1;	hit_matrices[2][1][1] = 1;	hit_matrices[2][1][2] = 0;
	hit_matrices[2][1][3] = 1;	hit_matrices[2][1][4] = 1;	hit_matrices[2][1][5] = 0;
	hit_matrices[2][1][6] = 1;	hit_matrices[2][1][7] = 0;	hit_matrices[2][1][8] = 0;


	hit_matrices[2][2][0] = 1;	hit_matrices[2][2][1] = 0;	hit_matrices[2][2][2] = 0;
	hit_matrices[2][2][3] = 1;	hit_matrices[2][2][4] = 1;	hit_matrices[2][2][5] = 0;
	hit_matrices[2][2][6] = 1;	hit_matrices[2][2][7] = 1;	hit_matrices[2][2][8] = 0;


	hit_matrices[2][3][0] = 1;	hit_matrices[2][3][1] = 1;	hit_matrices[2][3][2] = 0;
	hit_matrices[2][3][3] = 1;	hit_matrices[2][3][4] = 1;	hit_matrices[2][3][5] = 0;
	hit_matrices[2][3][6] = 1;	hit_matrices[2][3][7] = 1;	hit_matrices[2][3][8] = 0;





	hit_matrices[3][0][0] = 1;	hit_matrices[3][0][1] = 1;	hit_matrices[3][0][2] = 0;
	hit_matrices[3][0][3] = 1;	hit_matrices[3][0][4] = 1;	hit_matrices[3][0][5] = 0;
	hit_matrices[3][0][6] = 0;	hit_matrices[3][0][7] = 0;	hit_matrices[3][0][8] = 0;


	hit_matrices[3][1][0] = 1;	hit_matrices[3][1][1] = 1;	hit_matrices[3][1][2] = 1;
	hit_matrices[3][1][3] = 1;	hit_matrices[3][1][4] = 1;	hit_matrices[3][1][5] = 0;
	hit_matrices[3][1][6] = 0;	hit_matrices[3][1][7] = 0;	hit_matrices[3][1][8] = 0;


	hit_matrices[3][2][0] = 1;	hit_matrices[3][2][1] = 1;	hit_matrices[3][2][2] = 0;
	hit_matrices[3][2][3] = 1;	hit_matrices[3][2][4] = 1;	hit_matrices[3][2][5] = 0;
	hit_matrices[3][2][6] = 1;	hit_matrices[3][2][7] = 0;	hit_matrices[3][2][8] = 0;


	hit_matrices[3][3][0] = 1;	hit_matrices[3][3][1] = 1;	hit_matrices[3][3][2] = 1;
	hit_matrices[3][3][3] = 1;	hit_matrices[3][3][4] = 1;	hit_matrices[3][3][5] = 0;
	hit_matrices[3][3][6] = 1;	hit_matrices[3][3][7] = 0;	hit_matrices[3][3][8] = 0;





	hit_matrices[4][0][0] = 0;	hit_matrices[4][0][1] = 0;	hit_matrices[4][0][2] = 0;
	hit_matrices[4][0][3] = 0;	hit_matrices[4][0][4] = 1;	hit_matrices[4][0][5] = 1;
	hit_matrices[4][0][6] = 0;	hit_matrices[4][0][7] = 1;	hit_matrices[4][0][8] = 1;


	hit_matrices[4][1][0] = 0;	hit_matrices[4][1][1] = 0;	hit_matrices[4][1][2] = 1;
	hit_matrices[4][1][3] = 0;	hit_matrices[4][1][4] = 1;	hit_matrices[4][1][5] = 1;
	hit_matrices[4][1][6] = 0;	hit_matrices[4][1][7] = 1;	hit_matrices[4][1][8] = 1;


	hit_matrices[4][2][0] = 0;	hit_matrices[4][2][1] = 0;	hit_matrices[4][2][2] = 0;
	hit_matrices[4][2][3] = 0;	hit_matrices[4][2][4] = 1;	hit_matrices[4][2][5] = 1;
	hit_matrices[4][2][6] = 1;	hit_matrices[4][2][7] = 1;	hit_matrices[4][2][8] = 1;


	hit_matrices[4][3][0] = 0;	hit_matrices[4][3][1] = 0;	hit_matrices[4][3][2] = 1;
	hit_matrices[4][3][3] = 0;	hit_matrices[4][3][4] = 1;	hit_matrices[4][3][5] = 1;
	hit_matrices[4][3][6] = 1;	hit_matrices[4][3][7] = 1;	hit_matrices[4][3][8] = 1;





	hit_matrices[5][0][0] = 1;	hit_matrices[5][0][1] = 1;	hit_matrices[5][0][2] = 1;
	hit_matrices[5][0][3] = 0;	hit_matrices[5][0][4] = 1;	hit_matrices[5][0][5] = 0;
	hit_matrices[5][0][6] = 0;	hit_matrices[5][0][7] = 0;	hit_matrices[5][0][8] = 0;


	hit_matrices[5][1][0] = 1;	hit_matrices[5][1][1] = 1;	hit_matrices[5][1][2] = 1;
	hit_matrices[5][1][3] = 1;	hit_matrices[5][1][4] = 1;	hit_matrices[5][1][5] = 0;
	hit_matrices[5][1][6] = 0;	hit_matrices[5][1][7] = 0;	hit_matrices[5][1][8] = 0;


	hit_matrices[5][2][0] = 1;	hit_matrices[5][2][1] = 1;	hit_matrices[5][2][2] = 1;
	hit_matrices[5][2][3] = 0;	hit_matrices[5][2][4] = 1;	hit_matrices[5][2][5] = 1;
	hit_matrices[5][2][6] = 0;	hit_matrices[5][2][7] = 0;	hit_matrices[5][2][8] = 0;


	hit_matrices[5][3][0] = 1;	hit_matrices[5][3][1] = 1;	hit_matrices[5][3][2] = 1;
	hit_matrices[5][3][3] = 1;	hit_matrices[5][3][4] = 1;	hit_matrices[5][3][5] = 1;
	hit_matrices[5][3][6] = 0;	hit_matrices[5][3][7] = 0;	hit_matrices[5][3][8] = 0;





	hit_matrices[6][0][0] = 0;	hit_matrices[6][0][1] = 1;	hit_matrices[6][0][2] = 1;
	hit_matrices[6][0][3] = 0;	hit_matrices[6][0][4] = 1;	hit_matrices[6][0][5] = 1;
	hit_matrices[6][0][6] = 0;	hit_matrices[6][0][7] = 0;	hit_matrices[6][0][8] = 0;


	hit_matrices[6][1][0] = 1;	hit_matrices[6][1][1] = 1;	hit_matrices[6][1][2] = 1;
	hit_matrices[6][1][3] = 0;	hit_matrices[6][1][4] = 1;	hit_matrices[6][1][5] = 1;
	hit_matrices[6][1][6] = 0;	hit_matrices[6][1][7] = 0;	hit_matrices[6][1][8] = 0;


	hit_matrices[6][2][0] = 0;	hit_matrices[6][2][1] = 1;	hit_matrices[6][2][2] = 1;
	hit_matrices[6][2][3] = 0;	hit_matrices[6][2][4] = 1;	hit_matrices[6][2][5] = 1;
	hit_matrices[6][2][6] = 0;	hit_matrices[6][2][7] = 0;	hit_matrices[6][2][8] = 1;


	hit_matrices[6][3][0] = 1;	hit_matrices[6][3][1] = 1;	hit_matrices[6][3][2] = 1;
	hit_matrices[6][3][3] = 0;	hit_matrices[6][3][4] = 1;	hit_matrices[6][3][5] = 1;
	hit_matrices[6][3][6] = 0;	hit_matrices[6][3][7] = 0;	hit_matrices[6][3][8] = 1;





	hit_matrices[7][0][0] = 0;	hit_matrices[7][0][1] = 0;	hit_matrices[7][0][2] = 1;
	hit_matrices[7][0][3] = 0;	hit_matrices[7][0][4] = 1;	hit_matrices[7][0][5] = 1;
	hit_matrices[7][0][6] = 0;	hit_matrices[7][0][7] = 0;	hit_matrices[7][0][8] = 1;


	hit_matrices[7][1][0] = 0;	hit_matrices[7][1][1] = 1;	hit_matrices[7][1][2] = 1;
	hit_matrices[7][1][3] = 0;	hit_matrices[7][1][4] = 1;	hit_matrices[7][1][5] = 1;
	hit_matrices[7][1][6] = 0;	hit_matrices[7][1][7] = 0;	hit_matrices[7][1][8] = 1;


	hit_matrices[7][2][0] = 0;	hit_matrices[7][2][1] = 0;	hit_matrices[7][2][2] = 1;
	hit_matrices[7][2][3] = 0;	hit_matrices[7][2][4] = 1;	hit_matrices[7][2][5] = 1;
	hit_matrices[7][2][6] = 0;	hit_matrices[7][2][7] = 1;	hit_matrices[7][2][8] = 1;


	hit_matrices[7][3][0] = 0;	hit_matrices[7][3][1] = 1;	hit_matrices[7][3][2] = 1;
	hit_matrices[7][3][3] = 0;	hit_matrices[7][3][4] = 1;	hit_matrices[7][3][5] = 1;
	hit_matrices[7][3][6] = 0;	hit_matrices[7][3][7] = 1;	hit_matrices[7][3][8] = 1;



	x_map[5] = 2;	x_map[2] = 4;	x_map[1] = 8;
	x_map[0] = 16;	x_map[3] = 32;	x_map[6] = 64;
	x_map[7] = 128;	x_map[8] = 512;	x_map[4] = 0;

	for(int i = 0; i < 1024; ++i)
	{
		hash_lut_hit[i] = 1;
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
			hash_lut_hit[counter] = 0;
		}
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

