#include "skeletonisation.hh"

#include "setup.hh"

//#include "viewer.hh"

using namespace std;

extern int * x_map;
extern int * hash_lut_hit;
extern int * hash_lut_M;
extern int * hash_lut_bridge;
extern int * hash_lut_cross;

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
			if(buf[i * width + j] == 1)
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
							sum += x_map[(1 + k) * 3 + 1 + l] * (int)buf[(k + i) * width + l + j];
							//tmp[(1 + k) * 3 + 1 + l] = M[(k + i) * width + l + j];
						}
						else
						{
							//tmp[(1 + k) * 3 + 1 + l] = 0;
						}
					}
				G[i * width + j] = hash_lut_bridge[sum];
				if( G[i*width+j] != buf[i*width+j] ) changes++;
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
void hit_miss::crosser()
{
	vector <int> crossers;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(buf[i * width + j])
			{
				int count = 0;
				for(int k = -1; k < 2; k++)
					for(int l = -1; l < 2; l++)
					{
						if(((i + k) >= 0) && ((i + k) < height) && ((j + l) >= 0) && ((j + l) < width))
						{
							count += x_map[(k + 1) * 3 + l + 1] * (int)buf[(i + k) * width + j + l];
						}
					}
				if(hash_lut_cross[count])
				{
					crossers.push_back(i * width + j);
				}
			}
		}
	}
	check_cross(crossers);
	return;	
}
void hit_miss::check_cross(vector<int> crossers)
{

	while(crossers.size() != 0)
	{
		vector <int> tmp;
		int x = crossers[0] / width, y = crossers[0] % width;
		tmp.push_back(crossers[0]);
		for(int j = 1; j < crossers.size(); j++)
		{

			int len = sqrt((x - crossers[j] / width) * (x - crossers[j] / width) + (y - crossers[j] % width) * (y - crossers[j] % width));
			if(len <= 5.0)
			{
				tmp.push_back(crossers[j]);
				crossers.erase(crossers.begin() + j);
				j--;
			}
		}
		crossers.erase(crossers.begin());
		
		clusters.push_back(tmp);
	} 
	/*
	for(int i = 0; i < clusters.size(); i++)
	{
		if(clusters[i].size() == 1)
		{
			int counter = 0, line = 0;
			for(int j = -1; j < 2; j++)
				for(int k = -1; k < 2; k++)
				{
					int tmp = (clusters[i][0] / width + j) * width + (clusters[i][0] % width + k);
					
					if((buf[tmp]) && ((j != 0) || (k != 0)))
					{
						line ++;
						M[clusters[i][0]] = 1;
						int ll = iter(i, clusters[i][0], tmp);
						if(ll < 5)
						{
							counter ++;
						}
					}
				}
			if((line - counter) == 1)
			{
				clusters.erase(clusters.begin() + i);
				i--;
			}
		}
	}*/
	for(int i = 0; i < clusters.size(); i++)
	{
		for(int j = 0; j < clusters[i].size(); j++)
		{
			fprintf(stderr, "%d ", clusters[i][j]);
		}
		fprintf(stderr, "\n");
	}
	return;
}
int hit_miss::iter(int pile, int prev, int pos)
{
	
	for(int i = 0; i < clusters.size(); i++)
	{
		if(i != pile)
		{
			for(int j = 0; j < clusters[i].size(); j++)
			{
				if(clusters[i][j] == pos)
					return 1;
			}
		}
	}
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		{
			if((i != 0) || (j != 0))
			{
				int tmp = (pos / width + i) * width + (pos % width + j);
				if((buf[tmp]) && (tmp != prev) && (M[tmp] != 1))
				{
					M[tmp] = 1;
					return 1 + iter(pile, pos, tmp);
				}
			}
		}
	return 1;
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

/*

int main( int argc, char ** argv)
{
	char filename[64];
    	strcpy( filename, "../../Letters/B.bmp" );

	setup_matrix();
	cBitmap * character = new cBitmap(argv[1]);
	hit_miss Kick( character );

	int result;
	int i = 0;
	//Question: According to p419, 2nd paragraph, we should erode until nothing changes anymore. Atm, we get an empty image from that though
	//Is this solely due to the additional hit matrices?
	do
	{
		result = Kick.skeleton();
		//Kick.show_M();
		Kick.shift();

//For testing purposes
//i++; if( i >= 3 ) break;

	}while( result );


	Kick.Bridge();
	Kick.shift();
	Kick.show();
	Kick.crosser();
	Kick.exportToBitmap( character );
	
	//Just for testing
	unsigned char * t = (unsigned char*) malloc( character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	character->getBitmap( t, character->getWidth()*character->getHeight()*sizeof( struct Pixel ) );
	glutViewer( t, character->getWidth(), character->getHeight(), argc, argv, 400, 400 );
	free( t );

	delete character;
}

*/