#include "geometry.hh"

using namespace std;

Geometry feature;

Geometry geometry( cBitmap * bitmap )
{
	Pixel p;
	int x;
	Geometry geo;
	int sum = 0, wx = 0, wy = 0;

	int width = bitmap->getWidth();
	int height = bitmap->getHeight();

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			bitmap->getPixel( i, j, p );
			if( p.r == 0 ) x = 1; else x = 0;
			sum += x;
			wx += i * x;
			wy += i * x;
		}
	geo.area = sum;
	geo.wc_x = int(wx / (sum * 1.0));
	geo.wc_y = int(wy / (sum * 1.0));
	double avg = 0, max = 0;
	int num_dists = 0;
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			bitmap->getPixel( i, j, p );
			if( p.r == 0 ) x = 1; else x = 0;
			if(x)
			{
				double tmp = sqrt((i - geo.wc_x) * (i - geo.wc_x) + (j - geo.wc_y) * (j - geo.wc_y));
				avg += tmp;
				num_dists++;
				if(tmp > max)
				{
					max = tmp;
				}
			}
		}
	geo.Max_dis = max;

	if( num_dists > 0 )
	 geo.avg_dis = avg/num_dists;
        else
	 geo.avg_dis = 0;

	return geo;
}

void computeGeometry( cBitmap * bitmap ){
 feature = geometry( bitmap );
}

double getAverageDistance(){ return feature.avg_dis; }
double getMaximumDistance(){ return feature.Max_dis; }
double getArea(){ return feature.area; }
void getWeightCenter( pair<int,int> & a ){ a.first = feature.wc_x; a.second = feature.wc_y; }
