#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> //For drand48(): generate random numbers between (0,1)

#include "3x3_matrix_inv_mod.h"

size_t size1 = 100; //N=100 points
size_t size2 = 10;  //N=10 points

const size_t sizemat = 9; //3x3 matrix
const size_t sizevec = 3; //3x1 vector

int param = 1; //use it to change size of the array size
double n = 1; //Noise-level: 1, 10

int main(void){

	ofstream fout("data-field-nois.etxt");
	int size; 

	if (param == 0)
	{
		size = size1;
	} else {
		size = size2;
	}

	double  *x = new double[size];
	double  *y = new double[size];
	double  *z = new double[size];
	double  *zNoise = new double[size];

	cout << fixed << setprecision(5) << setw(9);

	//Init data
	for (int iv = 0; iv < size; iv++)
	 {
	 	// note: we assume data on a 10x10 grid (iv is in [0,99])
        int i = iv % 10;  // i in [0,9]
        int j = iv / 10;  // j in [0,9]
        x[iv] = drand48();
        y[iv] = drand48();
        z[iv] = x[iv] + y[iv];
        zNoise[iv] = z[iv] + n*(0.2*drand48() - 0.1);
        fout << x[iv] << " " << y[iv] << " " << z[iv] << endl;
	 } 

	 //Matrix 								Schema A 	|	Schema Z
	 double A[sizemat];				//		0	3	6	|		0
	 double invA[sizemat];			//		1	4	7	|		1
	 double Z[sizevec];				// 		2	5	8	|		2

	 for (int i = 0; i < sizemat; ++i)
	 {
	 	A[i] = 0;
	 	Z[i] = 0; 
	 }

	 //Fill Matrix H = M^T M
	 A[0] = size;
	 for (int i = 0; i < size; i++)
	 {
	 	A[1] = A[3] = A[1] + x[i];
	 	A[2] = A[6] = A[2] + y[i];
	 	A[5] = A[7] = A[5] + x[i]*y[i];
	 	A[4] += x[i]*x[i];
	 	A[8] += y[i]*y[i];

	 	Z[0] += zNoise[i];
	 	Z[1] += zNoise[i]*x[i];
	 	Z[2] += zNoise[i]*y[i];
	 }

	 invert_3x3_matrix(A, invA);

	 double a = invA[0]*Z[0] + invA[1]*Z[1] + invA[2]*Z[2];
	 double b = invA[3]*Z[0] + invA[4]*Z[1] + invA[5]*Z[2];
	 double c = invA[6]*Z[0] + invA[7]*Z[1] + invA[8]*Z[2];

	 // cout << a << " + " << b << " * x + " << c << " * y" << endl;

// Delete dynamic array
	delete [] x;
	delete [] y;
	delete [] z;

	return 0;
}