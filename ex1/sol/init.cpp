#include <iostream>
#include <fstream>

using namespace std;

int main(void){
	ofstream fout("init-data.txt");

	for (int i = 0; i<10; i++){
		double x = i;
		double y = 0.5*x-1.0;
		fout << x << " " << y << endl;
	}
	return 0;
}
