//
//  Lagrange for Ex3
//
//  Created by Dmitry Alexeev on 04/03/15. Modified by Lina Kulakova on 18/03/15.
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Basis functions
double lk(double x0, vector<double>& x, int k)
{
    double res = 1.0;
    
    for (int i = 0; i < x.size(); i++)
        if (i != k) res *= (x0 - x[i]) / (x[k] - x[i]);
    
    return res;
}

double lagrange(double x0, vector<double>& x, vector<double>& y)
{
    assert(x.size() == y.size());

    double res = 0;
    for (int k = 0; k < x.size(); k++)
        res += y[k] * lk(x0, x, k);
    return res;
}

int main(int argc, char * argv[])
{
    // check if we have all the necessary command line arguments
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <filename> <vis.grid size>" << endl;
        return -1;
    }

    // storage for the interpolation nodes
    vector<double> x;
    vector<double> y;

    // read the data points (x_i,y_i)
    string filename(argv[1]);
    ifstream infile;
    infile.open(filename.c_str());

    double xi, yi;
    while(infile >> xi >> yi)
    {
        x.push_back(xi);
        y.push_back(yi);
    }

    if(x.empty() || y.empty())
    {
        cout << "No data read from file " << filename << ", stop." << endl;
        return -1;
    }

    // compute the interpolation function f and store the (x,f(x)) 
    // values on a fine mesh
    int N_vis = atoi(argv[2]);
    vector<double> x_vis(N_vis,0);
    vector<double> y_vis(N_vis,0);

    double left = *min_element(x.begin(), x.end());
    double right = *max_element(x.begin(), x.end());
    double h = (right-left)/(N_vis-1);
    for(int i=0; i<x_vis.size(); ++i)
        x_vis[i] = left + i*h;
 
    for (int i = 0; i < N_vis; i++)
        y_vis[i] = lagrange(x_vis[i], x, y);

    // write data to the output file
    ofstream outfile;
    outfile.open((string("lagrange_")+filename).c_str());
    for(int i=0; i<N_vis; ++i)
        outfile << x_vis[i] << " " << y_vis[i] << endl;

    return 0;
}
