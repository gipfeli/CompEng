/* Code for the Computational Methods for Engineering Applications class
 * Created by P--
 * Copyright (c) CSElab, ETH Zürich, 2015
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include <numeric>

// GSL library
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_multimin.h>

using namespace std;

#include "optim.h"

// GSL adaptation for numerical optimization
// Adapted from P++ P-- P4U

int main(int argc, char * argv[])
{
    // pass the file name to read the data from as a command line argument argv[1]
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <fitnum> -values 1 or 2 or 3" << endl;
        return -1;
    }

    // storage for the interpolation nodes
    vector<double> x;
    vector<double> y;

    // read the data points (x_i,y_i,z_i)
    ifstream infile;
    infile.open("ex6_data.txt");

    double xi, yi;
    while(infile >> xi >> yi)
    {
        x.push_back(xi);
        y.push_back(yi);
    }

    if(x.empty() || y.empty())
    {
        cout << "No data read from file ex6_data.txt, stop." << endl;
        return -1;
    }

    // three different function types to plot
    int fitnum = atoi(argv[1]);

    // pass the file name to read the data from as a command line argument argv[1]
    if(fitnum != 1 && fitnum != 2 && fitnum != 3 )
    {
        cout << "Usage: - Are you retarded? " << argv[0] << " <fitnum> -values 1 or 2 or 3" << endl;
        return -1;
    }
  
    // FILL HERE: Leave-One-Out Cross-Validation divert(-1)
    // vector that will keep all the Sum of Squared Errors
    vector<double> allSSE;
  
    // Leave-One-Out Cross-Validation
    for(int i=0; i<x.size(); ++i)
    {
        // data for the CV: each time remove one point
        vector<double> x_in;
        vector<double> y_in;
        for(int j=0; j<x.size(); ++j)
        {
            if (j!=i)
            {
                x_in.push_back(x[j]);
                y_in.push_back(y[j]);
            }
        }

        vector<double> x_out(1,x[i]);
        vector<double> y_out(1,0);

        // perform the interpolation
        interpolate(fitnum, x_in, y_in, x_out, y_out);

        // cross-validation error
        double ssepred = pow(y_out[0]-y[i], 2);
        allSSE.push_back(ssepred);
    }

    double MSELOO = accumulate(allSSE.begin(), allSSE.end(), 0.0) / allSSE.size();
    cout << "THE MEAN MSE VALUE IS :"<< MSELOO <<"\t" << "over a data sample of " << allSSE.size()  << endl;
    cout << "Note: You used Fit Function No:" << fitnum << endl;
    // divert(0)

    // now compute the interpolated function f with all the points and store the (t,f(t))
    // values on a fine mesh

    // visualisation grid for the fitted function
    int N_vis = 100;
    vector<double> x_vis(N_vis,0);
    vector<double> y_vis(N_vis,0);

    // visualisation nodes for x
    double min_x = *min_element(x.begin(), x.end());
    double max_x = *max_element(x.begin(), x.end());
    double h_x = (max_x-min_x)/(N_vis-1);
    for(int i=0; i<N_vis; ++i)
        x_vis[i] = min_x + i*h_x;

    // get the values of the interpolation function on the visualisation grid
    interpolate(fitnum, x, y, x_vis, y_vis);

    // file to dump the result
    string filename = string("ex6_result_case")+string(argv[1])+string(".txt");

    // Now also dump a file with the fit results for plotting
    ofstream outfile;
    outfile.open(filename.c_str());

    for(int i=0; i<N_vis; ++i)
        outfile << x_vis[i] << " " << y_vis[i] << endl;

    return 0;
}
