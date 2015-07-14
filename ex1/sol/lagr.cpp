#include <iostream>
#include <fstream>

using namespace std;

int main (void){
	double x0 = -1; //Starting point
	int step = 220; //Numbers of steps

	ofstream fout("lagr.txt");
	size_t size = 10;

	double *x = new double[size];
	double *y = new double[size];

	for (int i = 0; i < size; i++)
	{
		x[i] = i;
		y[i] = 0.5*x[i]-1.0;
	}

	for (int j = 0; j < step; j++){
		double res = 0.0;
		double lk = 1.0;
		x0 = 0.05*j-1.0;
	for (int k = 0; k < size; k++){
		double lk = 1.0;
		for (int i = 0; i < size; i++)	{
		if(i!=k) {lk *= (x0-x[i])/(x[k]-x[i]);}
		}
		res += y[k]*lk;
	}
		fout << x0 << " " << res << endl;
	}

	delete [] x;
	delete [] y;
	return 0;
}