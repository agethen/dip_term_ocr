#include "skeletonisation.hh"

#include "setup.hh"

using namespace std;

extern int * x_map;
extern int * hash_lut_hit;
extern int * hash_lut_M;
extern int * hash_lut_bridge;


hit_miss::hit_miss( cBitmap * bitmap )
{
	Pixel p;
	width = bitmap->getWidth();
	height = bitmap->getHeight();

	buf = new unsigned char[width * height];
	M = new unsigned char[width * height];
	G = new unsigned char[width * height];

	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			double sum = 0;
			bitmap->getPixel( j, i, p );
			sum += (double)(p.r * p.r);
			sum += (double)(p.g * p.g);
			sum += (double)(p.b * p.b);

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
	delete[] buf;
	delete[] M;
	delete[] G;
	delete[] bond;
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
	delete[] tmp;
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
	delete[] tmp;
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
void hit_miss::Bridge()
{
	unsigned char *tmp = new unsigned char[9];
	memcpy(M, G, width * height * sizeof(unsigned char));
	memset(G, 0, width * height * sizeof(unsigned char));
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			if(M[i * width + j] == 1)
			{
				G[i * width + j] = 1;
			}
			else
			{
				int sum = 0;
				
				for(int k = -1; k < 2; k++)
					for(int l = -1; l < 2; l++)
					{
						if(((k + i) >= 0) && ((l + j) >= 0) && ((k + i) < height) && ((l + j) < width))
						{
							sum += x_map[(1 + k) * 3 + 1 + l] * (int)M[(k + i) * width + l + j];
							tmp[(1 + k) * 3 + 1 + l] = M[(k + i) * width + l + j];
						}
						else
						{
							tmp[(1 + k) * 3 + 1 + l] = 0;
						}
					}
				G[i * width + j] = hash_lut_bridge[sum];
			}
		}
	delete[] tmp;
	return;
}
void hit_miss::shift()
{
	memcpy(buf, G, width * height * sizeof(unsigned char));
	memset(M, 0, width * height * sizeof(unsigned char));
	memset(G, 0, width * height * sizeof(unsigned char));
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
	cBitmap * character = new cBitmap(filename);
	hit_miss Kick( character );

	Kick.show();
	for(int i = 0; i < 2; i++)
	{
		Kick.skeleton();
		Kick.show();
		Kick.shift();
	}
	Kick.skeleton();
	Kick.Bridge();
	Kick.show_G();

	delete character;
}
