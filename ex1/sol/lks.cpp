#include <iostream>
#include <fstream>

using namespace std;

int main (void){
	int k = 10; //k: degree of polynomial
	double x0; //Starting point
	int step = 220; //Numbers of steps

	ofstream fout("lk10.txt");
	size_t size = 10;

	double lk = 1.0;

	double *x = new double[size];
	double *y = new double[size];

	for (int i = 0; i < size; i++)
	{
		x[i] = i;
		y[i] = 0.5*x[i]-1.0;
	}

	for (int j = 0; j < step; j++){
		double lk = 1.0;
		x0 = 0.05*j-1.0;
		for (int i = 0; i < size; i++)	{
		if(i!=k) {lk *= (x0-x[i])/(x[k]-x[i]);}
		}
		fout << x0 << " " << lk << endl;
	}

	delete [] x;
	delete [] y;
	return 0;
}