//
//  Exercise 8 - Question 2
//
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

int main() {
    
    // read in file
    vector<double> r;
    vector<double> Tr;
    ifstream infile("input_values.txt");
    double ri, Tri;
    while(infile >> ri >> Tri) {
        r.push_back(ri);
        Tr.push_back(Tri);
    }
    
    // TEST
    //for (int i = 0; i < r.size(); ++i) cout << r[i] << ", " << Tr[i] << endl;
    
    // integrate
    double thetap = 0.7051;
    int N = r.size()-1;
    double I1 = 0; // numerator
    double I2 = 0; // denominator
    for (int i = 0; i < N; ++i) {
        double deltai = r[i+1] - r[i];
        I1 += (Tr[i]*r[i]*thetap + Tr[i+1]*r[i+1]*thetap) * 0.5 * deltai;
        I2 += (r[i]*thetap + r[i+1]*thetap) * 0.5 * deltai;
    }
    
    // REPORT
    cout << "Temperature T = " << I1/I2 << endl;
    
    return 0;
}
