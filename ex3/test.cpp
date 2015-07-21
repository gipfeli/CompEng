#include <iostream>
#include <fstream>

using namespace std;

int main (void){

    ifstream f;
    f.open("peak.txt");

    if(f.fail()) // checks to see if file opended 
    { 
      cout << "error" << endl; 
      return 1; // no point continuing if the file didn't open...
    } 

    size_t lines_count =0;
    string line;
    while (std::getline(f , line))
        ++lines_count;

    size_t size = lines_count;

    double x[size];
    double y[size];

    int num = 0;

    while(!f.eof()) // reads file to end of *file*, not line
    { 
         f >> x[num]; // read first column number
         f >> y[num]; // read second column number
         cout << x[num] << " " << y[num] << endl;
         ++num;
    }

    /*for (int j = 0; j < step; j++){
        double res = 0.0;
        // double lk = 1.0;
        x0 = 0.05*j-1.0;
    for (int k = 0; k < size; k++){
        double lk = 1.0;
        for (int i = 0; i < size; i++)  {
        if(i!=k) {lk *= (x0-x[i])/(x[k]-x[i]);}
        }
        res += y[k]*lk;
    }
        // cout << x0 << " " << res << endl;
    }*/

    return 0;
}