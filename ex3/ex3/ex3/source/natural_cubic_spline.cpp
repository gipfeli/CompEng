/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <assert.h>

// This file must (!) be included in order to use the Thomas algorithm
#include "solve_tridiag.h"

// Interpolate the data set (x,y) with the natural cubic spline. 
// Return the values of the interpolation function in the x_vis.
void interpolate_natural_cubic_spline(
    // input
    vector<double> const & x,
    vector<double> const & y,
    int l_clamped,
    int r_clamped,
    vector<double> const & x_vis,
    // output
    vector<double> & y_vis
    )
{
    // Assemble the system; note that it is a tridiagonal one, so we store it as 3 vectors 

    int N = x.size();

    vector<double> lower(N-1);
    vector<double> diag(N);
    vector<double> upper(N-1);
    vector<double> rhs(N);

    // FILL HERE: fill in the matrix 

    // Solve the system and store the result in d
    vector<double> d(N,0);
    solve_thomas(lower,diag,upper,rhs,d);

    // FILL HERE: Evaluate the interpolation function on the visualisation grid (x_vis,y_vis) 
}

int main(int argc, char * argv[])
{
    // pass the file name to read the data from as a command line argument argv[1]
    if(argc != 5)
    {
        cout << "Usage: " << argv[0] << " <filename> <vis.grid size> <left clamped?> <right clamped?>" << endl;
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
    
    int l_clamped = atoi(argv[3]);
    int r_clamped = atoi(argv[4]);
    interpolate_natural_cubic_spline(x,y,l_clamped,r_clamped,x_vis,y_vis);

    // write data to the output file
    ofstream outfile;
    outfile.open((string("spline_")+filename).c_str());
    for(int i=0; i<N_vis; ++i)
        outfile << x_vis[i] << " " << y_vis[i] << endl;

    return 0;
}
