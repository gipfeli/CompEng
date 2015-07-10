//
//  Exercise 9
//
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

// NOTE: needs gsl: use g++ ex9.cpp -lgsl -lgslcblas
#include "ex9-hidden.h"

using namespace std;

int main() {
    
    // read in file
    vector<double> x;
    vector<double> y;
    ifstream infile("peak.txt");
    double xi, yi;
    while(infile >> xi >> yi) {
        x.push_back(xi);
        y.push_back(yi);
    }
    
    // setup and solve system
    int N = x.size();
    int d = 2;
    vector<double> t(N+d+1); // knot vector
    vector<double> p(N);     // stores result
    MyMatrix A(N,N);         // NxN matrix for system to solve
    
    // define knot vector
    if (d == 1) {
        t[0] = x[0] - (x[1] - x[0]);
        for (int i = 1; i <= N; ++i) {
            t[i] = x[i-1];
        }
        t[N+1] = x[N-1] + (x[N-1] - x[N-2]);
    } else if (d == 2) {
        t[0] = x[0] - 100*(x[1] - x[0]);
        t[1] = x[0] - 100*(x[1] - x[0]);
        for (int i = 2; i <= N; ++i) {
            t[i] = (x[i-2] + x[i-1])/2;
        }
        t[N+1] = x[N-1] + 100*(x[N-1] - x[N-2]);
        t[N+2] = x[N-1] + 100*(x[N-1] - x[N-2]);
    } else if (d == 3) {
        t[0] = x[0] - 100*(x[1] - x[0]);
        t[1] = x[0] - 100*(x[1] - x[0]);
        for (int i = 2; i <= N+1; ++i) {
            t[i] = x[i-2];
        }
        t[N+2] = x[N-1] + 100*(x[N-1] - x[N-2]);
        t[N+3] = x[N-1] + 100*(x[N-1] - x[N-2]);
    } else {
        assert(false);
    }
    
    // define system -> loop over rows and columns of matrix
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            A(r,c) = Bspline(c+1, d, t, x[r]);
        }
    }
    
    // solve system
    A.solve(p, y);
    
    // output on fine mesh
    int Nvis = x.size()*10;
    double left = x[0];
    double right = x[N-1];
    double h = (right-left)/(Nvis-1);
    ofstream ofile("peak_out.txt");
    for (int i = 0; i < Nvis; ++i) {
        double xvis = left + i*h;
        double yvis = 0;
        for (int i = 0; i < N; ++i) {
            yvis += p[i] * Bspline(i+1, d, t, xvis);
        }
        ofile << xvis << " " << yvis << endl;
    }
    
    return 0;
}
