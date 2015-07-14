#include <iostream>

using namespace std;

int main (void){
	size_t size = 10;

	int k = 0; //k: degree of polynomial
	double x0 = -0.9; //Starting point

	double lk = 1.0;

	double *x = new double[size];
	double *y = new double[size];

	for (int i = 0; i < size; i++)
	{
		x[i] = i;
		y[i] = 0.5*x[i]-1.0;
		cout << x[i] << " " << y[i] << endl;		
	}

	cout << "---------------" << endl;
	cout << x0 << " " << x[k] << endl;

	for (int i = 0; i < size; i++)
	{
		if(i!=k) {
			lk *= (x0-x[i])/(x[k]-x[i]);	
			cout << "(" << x0 << "-" << x[i] << ")/(" << x[k] << "-" << x[i] << ") "; //Debug in Wolframalpha or calculator
		}
	}
	cout << "= " << lk << endl;

	delete [] x;
	delete [] y;
	return 0;
}