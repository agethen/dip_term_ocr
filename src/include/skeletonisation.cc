#include "skeletonisation.hh"

#include "setup.hh"

using namespace std;

extern int * x_map;
extern int * hash_lut_hit;
extern int * hash_lut_M;

hit_miss::hit_miss(unsigned char *input_rgb, int w, int h, int b)
{
	width = w;
	height = h;
	buf = new unsigned char[width * height];
	M = new unsigned char[width * height];
	G = new unsigned char[width * height];
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			double sum = 0;
			for(int k = 0; k < 3; k++)
			{
				sum += (double)(input_rgb[i * width * b + j * b + k] * input_rgb[i * width * b + j * b + k]);
			}
			if(sqrt(sum / 3.0) < 128)
				buf[i * width + j] = 1;
			else
				buf[i * width + j] = 0;
		}
	bond = new int[9];
	bond[0] = 1;	bond[1] = 2;	bond[2] = 1;
	bond[3] = 2;	bond[4] = 0;	bond[5] = 2;
	bond[6] = 1;	bond[7] = 2;	bond[8] = 1;
}
hit_miss::~hit_miss()
{
	delete(buf);
	delete(bond);
}
unsigned char hit_miss::check_for_hit(int h, int w)
{
	int sum = 0, br = 0;
	int *tmp = new int [9];
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		{
			if(((h + i) >= 0) && ((w + j) >= 0) && ((h + i) < height) && ((w + j) < width))
			{
				sum += (int)bond[(i + 1) * 3 + j + 1] * buf[(h + i) * width + w + j];
				tmp[3 * (i + 1) + j + 1] = (int)buf[(h + i) * width + w + j];
			}
			else
				tmp[3 * (i + 1) + j + 1] = 0;
		}
	int counter = 0;
	for(int i = 0; i < 9; i++)
		counter += x_map[i] * tmp[i];
	delete(tmp);
	return (unsigned char)hash_lut_hit[counter];
}
unsigned char hit_miss::check_for_M_hit(int h, int w)
{
	int sum = 0, br = 0;
	int *tmp = new int [9];
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		{
			if(((h + i) >= 0) && ((w + j) >= 0) && ((h + i) < height) && ((w + j) < width))
			{
				sum += (int)bond[(i + 1) * 3 + j + 1] * (((int)M[(h + i) * width + w + j]) / 2);
				tmp[3 * (i + 1) + j + 1] = (((int)M[(h + i) * width + w + j]) / 2);
			}
			else
				tmp[3 * (i + 1) + j + 1] = 0;
		}
	int counter = 0;
	for(int i = 0; i < 9; i++)
		counter += x_map[i] * tmp[i];
	delete(tmp);
	return (unsigned char)hash_lut_M[counter];
}
void hit_miss::skeleton()
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			if(buf[i * width + j] == 1)
				M[i * width + j] = buf[i * width + j] + check_for_hit(i, j);
			else
				M[i * width + j] = 0;
		}
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			if(M[i * width + j] == 2)
				G[i * width + j] = check_for_M_hit(i, j);
			else
				G[i * width + j] = M[i * width + j];
		}

	
}
void hit_miss::shift()
{
	memcpy(buf, G, width * height * sizeof(unsigned char));
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			M[i * width + j] = 0;
			G[i * width + j] = 0;
		}
	return;
}
void hit_miss::show()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			fprintf(stderr, "%u ", buf[i * width + j]);
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");
}
void hit_miss::show_M()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			fprintf(stderr, "%u ", M[i * width + j]);
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");
}
void hit_miss::show_G()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			fprintf(stderr, "%u ", G[i * width + j]);
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");
}
void hit_miss::getShrunk(unsigned char* input, int w, int h)
{
	if((w == width) && (h == height))
	{
		memcpy( input, G, w * h * sizeof(unsigned char) );
	}
	else
	{
		fprintf(stderr, "width or height doesn't match!\n");
		return;
	}
}

	int main()
	{
		char filename[64];
	        strcpy( filename, "../../Letters/B.bmp" );
		setup_matrix();
		cBitmap character(filename);
		int w = character.getWidth();
		int h = character.getHeight();
		int b = character.getBPP();
		unsigned char *J = new unsigned char[w * h * b];
		character.getBitmap(J, sizeof(char) * (w * h * b));
		hit_miss Kick(J, w, h, b);
		Kick.show();
		Kick.skeleton();
		Kick.show_G();
	}
