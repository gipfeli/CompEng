#include <iostream>
#include <fstream>

using namespace std;

int main(void){
	ofstream fout("data-straight.txt");

	size_t size = 10;

	double *x = new double[size];
	double *y = new double[size];

	for (int i = 0; i<10; i++){
		double x[i] = i;
		double y[i] = 0.5*x[i]-1.0;
		fout << x[i] << " " << y[i] << endl;
	}

	return 0;
}
