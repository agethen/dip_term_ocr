#include <iostream>
#include <cmath>
#include <cstring>
#include "new_setup.cc"
using namespace std;

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
			M[i * width + j] = 0;
			G[i * width + j] = 0;
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
unsigned char hit_miss::check_for_noise(int h, int w)
{
	int sum = 0, br = 0;
	int *tmp = new int [9];
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		{
			if(((h + i) >= 0) && ((w + j) >= 0) && ((h + i) < height) && ((w + j) < width) && (i != 0) && (j != 0))
			{
				sum += ((int)M[(h + i) * width + w + j]);
				tmp[3 * (i + 1) + j + 1] = ((int)M[(h + i) * width + w + j]);
			}
			else
				tmp[3 * (i + 1) + j + 1] = 0;
		}
	if(sum <= 2)
		return M[h * width + w];
	else
		if((8 - 2 * sum) != 1)
			return M[h * width + w];
		else
			if((tmp[5] == 0) || (tmp[7] == 0) || ((tmp[1] == 0) && (tmp[3] == 0)))
				if ((tmp[1] == 0) || (tmp[3] == 0) || ((tmp[5] == 0) && (tmp[7] == 0)))
				{
					return 0;
				}
				else
					return M[h * width + w];
			else
				return M[h * width + w];

}
void hit_miss::denoise()
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			if(M[i * width + j] == 1)
				G[i * width + j] = (unsigned char)check_for_noise(i, j);
		}
	return;
}
void hit_miss::skeleton()
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			if(buf[i * width + j] == 1)
				M[i * width + j] = check_for_hit(i, j);
		}
	return;
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
	if((w == weight) && (h == height))
	{
		memcpy( input, G, w * h * sizeof(unsigned char) );
	}
	else
	{
		fprintf(stderr, "width or height doesn't match!\n");
		return;
	}
}
/*
int main()
{
	setup_matrix();
	cBitmap character("./Letters/B.bmp");
	int w = character.getWidth();
	int h = character.getHeight();
	int b = character.getBPP();
	unsigned char *J = new unsigned char[w * h * b];
	character.getBitmap(J, sizeof(char) * (w * h * b));
	hit_miss Kick(J, w, h, b);
	Kick.show();
	Kick.skeleton();
	Kick.denoise();
	Kick.show_M();
	Kick.show_G();

}
*/
