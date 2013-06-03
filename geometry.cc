#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
struct Geometry
{
	double avg_dis; // average distance from the centre of mass
	double Max_dis; // maximum distance from the centre of mass
	int area;		// area of the character
	int wc_x;		// weight centre of character in the x direction
	int wc_y;		// weight centre of character in the y direction
};
//The input chunk should be bitwise image
Geometry geometry(unsigned char* input, int width, int height)
{
	Geometry geo;
	int sum = 0, wx = 0, wy = 0;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			sum += (int)input[i * width + j];
			wx += i * (int)input[i * width + j];
			wy += i * (int)input[i * width + j];
		}
	geo.area = sum;
	geo.wc_x = int(wx / (sum * 1.0));
	geo.wc_y = int(wy / (sum * 1.0));
	double avg = 0, max = 0;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			if(input[i * width + j])
			{
				double tmp = sqrt((i - geo.wc_x) * (i - geo.wc_x) + (j - geo.wc_y) * (j - geo.wc_y));
				avg += tmp;
				if(tmp > max)
				{
					max = tmp;
				}
			}
		}
	geo.Max_dis = max;
	geo.avg_dis = avg;
	return geo;
}