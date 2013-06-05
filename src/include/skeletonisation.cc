#include "skeletonisation.hh"

#include "setup.hh"

#include "viewer.hh"

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
int hit_miss::skeleton()
{
	int count_eroded = 0;
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

			if( buf[i*width+j] != G[i*width+j] )
			 count_eroded++;
		}
 return count_eroded;
}
int hit_miss::Bridge()
{
	int changes = 0;						//Were there any changes?

	//unsigned char *tmp = new unsigned char[9];			//tmp does not seem to do anything?
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
							//tmp[(1 + k) * 3 + 1 + l] = M[(k + i) * width + l + j];
						}
						else
						{
							//tmp[(1 + k) * 3 + 1 + l] = 0;
						}
					}
				G[i * width + j] = hash_lut_bridge[sum];
				if( G[i*width+j] == 1 ) changes++;
			}
		}
	//delete[] tmp;
	return changes;
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

void hit_miss::exportToBitmap( cBitmap * target ){
 Pixel p;

 //Bitmap maybe uninitialized
 target->setWidth( width );
 target->setHeight( height );
 target->setBPP( 3 );

 target->allocateMemory();

 for( int i = 0; i < height; i++ ){
  for( int j = 0; j < width; j++ ){
   if( buf[i*width+j] == 1 ){			//Black pixel
    memset( &p, 0, sizeof( struct Pixel ) );	
   }else{					//White pixel
    p.r = 255;
    p.g = 255;
    p.b = 255;
    p.a = 0;
   }

   target->setPixel( j, i, p );
  }
 }
}

int main( int argc, char ** argv)
{
	char filename[64];
    	strcpy( filename, "../../Letters/B.bmp" );

	setup_matrix();
	cBitmap * character = new cBitmap(argv[1]);
	hit_miss Kick( character );

	Kick.show();
	int result;
	int i = 0;
	//Question: According to p419, 2nd paragraph, we should erode until nothing changes anymore. Atm, we get an empty image from that though
	//Is this solely due to the additional hit matrices?
	do
	{
		result = Kick.skeleton();
		Kick.show();
		Kick.shift();
//For testing purposes
i++; if( i >= 3 ) break;
	}while( result );

	Kick.skeleton();

	while( Kick.Bridge() ){} //Repeat calling Bridge() as long as pixels are changed

	Kick.show_G();

	Kick.exportToBitmap( character );

	/* Just for testing */
	unsigned char * t = (unsigned char*) malloc( character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	character->getBitmap( t, character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	glutViewer( t, character->getWidth(), character->getHeight(), argc, argv, 400, 400 );
	free( t );

	delete character;
}
