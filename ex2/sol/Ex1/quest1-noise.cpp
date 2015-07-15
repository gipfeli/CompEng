#include <iostream>
#include <fstream>
#include <numeric>
#include <stdlib.h>

#include "2x2_matrix_inv_mod.h"

using namespace std;

//Eqs: y = a + bx
double a = -1.0;
double b = 0.5;

// Helper function
double sumOfSqr(double a, double b)
{
    return a + b*b;
}

size_t size = 10;
double n = 0.01; //Noise-level: 0, 0.01, 1, 10

int main(void){
	ofstream fout1("data-noise1.txt");

//Init data	

	double *x = new double[size];
	double *y = new double[size];
	double *yNoise = new double[size];

	for (int i = 0; i < size; i++)
	{
		x[i] = i;
		y[i] = a + b*x[i];
		yNoise[i] = y[i] + n*(0.2*drand48() - 0.1);
 		fout1 << x[i] << " " << yNoise[i] << endl;
	}


	ofstream fout2("lsq-noise1.txt");

	double A[4];
	double invA[4];
	double Y[2];

	double sumX  = accumulate(x, x+size, 0.0);
	double sumY  = accumulate(yNoise, yNoise+size, 0.0);
	double sumX2 = accumulate(x, x+size, 0.0, sumOfSqr);

	double sumXY = 0;
	for (int i = 0; i < size; i++)
	{	;
		sumXY += x[i]*yNoise[i];
	}

	A[0] = size;
	A[1] = sumX;
    A[2] = sumX;
    A[3] = sumX2;
    
    Y[0] = sumY;
    Y[1] = sumXY;

    invert_2x2_matrix(A, invA);

 //   cout << "Inverted matrix:" << endl << invA[0] << " " << invA[1] << endl << invA[2] << " " << invA[3] << endl;

    a = invA[0]*Y[0] + invA[1]*Y[1];
    b = invA[2]*Y[0] + invA[3]*Y[1];

    // cout << a << " " << b << endl;

    double xDraw[2]; //2 Points
    xDraw[0] = -1;
    xDraw[1] = 10;
    fout2 << xDraw[0] << " " << a+b*xDraw[0] << endl;
    fout2 << xDraw[1] << " " << a+b*xDraw[1] << endl;

//Delete the dynamic arrays
	delete [] x;
	delete [] y;

	return 0;
}
