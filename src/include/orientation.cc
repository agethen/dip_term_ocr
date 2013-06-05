#include "orientation.hh"
#include "setup.hh"
using namespace std;

Moment::Moment(unsigned char *buf, int width, int height){
	M_u = new double*[4];
	M = new double*[4];

	U = new double*[4];
	U_u = new double*[4];
	inertia = new double*[2];
	for(int i = 0; i < 4; i++)
	{
		M_u[i] = new double[4];
		M[i] = new double[4];
		U_u[i] = new double[4];
		U[i] = new double[4];
	}
	for(int m = 0; m < 4; m++)
		for(int n = 0; n < 4; n++)
		{
			if((m + n) > 3)
			{
				M_u[m][n] = 0;
				M[m][n] = 0;
			}
			else
			{
				double sum = 0;
				for(int i = 0; i < height; i++)
					for(int j = 0; j < width; j++)
					{
						double x = j - 0.5;
						double y = height + 0.5 - i;
						sum += buf[i * width + j] * pow(double(x), double(m)) * pow(double(y), double(n));
					}
				M_u[m][n] = sum;
				M[m][n] = sum / pow(double(width), double(m)) / pow(double(height), double(n));
			}
		}
	for(int m = 0; m < 4; m++)
		for(int n = 0; n < 4; n++)
		{
			if((m + n) > 3)
			{
				U_u[m][n] = 0;
				U[m][n] = 0;
			}
			else
			{
				double sum = 0;
				for(int i = 0; i < height; i++)
					for(int j = 0; j < width; j++)
					{
						double x = j - 0.5;
						double y = height + 0.5 - i;
						sum += buf[i * width + j] * pow(double(x - M[1][0] / M[0][0]), double(m)) * pow(double(y - M[0][1] / M[0][0]), double(n));
					}
				U_u[m][n] = sum;
				U[m][n] = sum / pow(double(width), double(m)) / pow(double(height), double(n));
			}
		}

}
void Moment::eigenvalue()
{
	for(int  i = 0; i < 2; i++)
	{
		inertia[i] = new double [2];
	}
	inertia[0][0] = U[2][0];
	inertia[0][1] = U[1][1];
	inertia[1][0] = U[1][1];
	inertia[1][1] = U[0][2];
	double l_1 = 0.5 * (U[2][0] + U[0][2]) + 0.5 * sqrt(pow(double(U[2][0]), 2.0) + pow(double(U[0][2]), 2.0) - 2.0 * U[2][0] * U[0][2] + 4 * pow(double(U[1][1]), 2.0));
	double l_2 = 0.5 * (U[2][0] + U[0][2]) - 0.5 * sqrt(pow(double(U[2][0]), 2.0) + pow(double(U[0][2]), 2.0) - 2.0 * U[2][0] * U[0][2] + 4 * pow(double(U[1][1]), 2.0));
	if(l_1 < l_2)
	{
		Lamda.l_min = l_1;
		Lamda.l_max = l_2;
	}
	else
	{
		Lamda.l_max = l_1;
		Lamda.l_min = l_2;
	}
	Lamda.theta = atan((Lamda.l_max - U[0][2]) / U[1][1]);
	return;
}
void Moment::print_eigenvalue()
{
	fprintf(stderr, "%lf %lf %lf\n", Lamda.l_max, Lamda.l_min, Lamda.theta);
}
Moment::~Moment()
{
	for(int i = 0; i < 4; i++)
	{
		delete [] M[i];
		delete [] M_u[i];
		delete [] U[i];
		delete [] U_u[i];
	}
	delete [] M;
	delete [] M_u;
	delete [] U;
	delete [] U_u;
	for(int  i = 0; i < 2; i++)
		delete [] inertia[i];
	delete [] inertia;
}
int main()
{
	char filename[64];
    	strcpy( filename, "../../Letters/A.bmp" );

	setup_matrix();
	cBitmap character(filename);
	int w = character.getWidth();
	int h = character.getHeight();
	int b = character.getBPP();

	//NOTE: getBitmap() always uses sizeof(Pixel) Bytes per Pixel (as of now: 4 Bytes), no matter what the BPP is.
	//getBPP() purpose is solely to remember the original bytes per pixel.
	unsigned char *J = new unsigned char[w * h * sizeof(Pixel)];	
	character.getBitmap(J, sizeof(char) * (w * h * sizeof(Pixel)));
	hit_miss Kick(J, w, h, sizeof(Pixel));
	//Kick.show();
	for(int i = 0; i < 2; i++)
	{
		Kick.skeleton();
		Kick.shift();
	//	Kick.show();	
	}
	Kick.skeleton();
	//Kick.show();
	Kick.Bridge();
	//Kick.show_G();
	Kick.getShrunk(J, w, h);
	Moment moment(J, w, h);
	moment.eigenvalue();
	moment.print_eigenvalue();
	delete[] J;
}