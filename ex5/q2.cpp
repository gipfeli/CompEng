/* Code for the Computational Methods for Engineering Applications class
 * Created by Lina Kulakova
 * Copyright (c) CSElab, ETH Zürich, 2015
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string.h>

// GSL library
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

using namespace std;

// Interpolate the data set (x,y,z) with the data-driven RBF.
// Return the values of the interpolation function in the points (x_vis,y_viz).
void interpolate_rbf(
    // input
    vector<double> const & x,
    vector<double> const & y,
    vector<double> const & z,
    double sigma_x,
    double sigma_y,
    vector<double> const & x_vis,
    vector<double> const & y_vis,
    // output
    vector<double> & z_vis
    )
{
    // Assemble the system
    // See the lecture notes for details

    int N = x.size();

    vector<double> A(N*N,0);

    // FILL HERE: fill in the matrix divert(-1)
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            double t = (gsl_ran_gaussian_pdf(x[i]-x[j],sigma_x)*
                gsl_ran_gaussian_pdf(y[i]-y[j],sigma_y));

            // treshold coordinates
            if(fabs(t)>1e-16)
                A[i*N+j] = t;
        }
    // divert(0)

    // Solve the system Ad = z, store the result in a vector d
    gsl_matrix * A_gsl = gsl_matrix_alloc(N,N);
    memcpy(A_gsl->data, &A[0], N*N*sizeof(double));
    gsl_vector * z_gsl = gsl_vector_alloc(N);
    memcpy(z_gsl->data, &z[0], N*sizeof(double));

    gsl_permutation * p_gsl = gsl_permutation_alloc(N);
    int signum;
    gsl_linalg_LU_decomp(A_gsl, p_gsl, &signum);

    gsl_vector * d_gsl = gsl_vector_alloc(N);
    gsl_linalg_LU_solve(A_gsl, p_gsl, z_gsl, d_gsl);

    vector<double> d(N,0);
    memcpy(&d[0], d_gsl->data, N*sizeof(double));

    // Evaluate the interpolation function on the visualisation grid (x_vis,y_vis,z_vis).
    // Remember that z_vis[i*N_vis+j]=f(x_vis[i],y_vis[j])
    int N_vis_x = x_vis.size();
    int N_vis_y = y_vis.size();
    for(int i=0; i<N_vis_x; ++i)
        for(int j=0; j<N_vis_y; ++j)
            {
                double t = 0;
                // loop over all the data points
                for(int k=0; k<N; ++k)
                    t += d[k]*gsl_ran_gaussian_pdf(x_vis[i]-x[k],sigma_x)*
                        gsl_ran_gaussian_pdf(y_vis[j]-y[k],sigma_y);

                z_vis[i*N_vis_y+j] = t;
            }
}

int main(int argc, char * argv[])
{
    // pass the file name to read the data from as a command line argument argv[1]
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <sigma_x> <sigma_y>" << endl;
        return -1;
    }

    // storage for the interpolation nodes
    vector<double> x;
    vector<double> y;
    vector<double> z;

    // read the data points (x_i,y_i,z_i)
    ifstream infile;
    infile.open("q2-data.txt");

    double xi, yi, zi;
    while(infile >> xi >> yi >> zi)
    {
        x.push_back(xi);
        y.push_back(yi);
        z.push_back(zi);
    }

    if(x.empty() || y.empty() || z.empty())
    {
        cout << "No data read from file q2-data.txt, stop." << endl;
        return -1;
    }

    // compute the interpolation function f and store the (x,y,f(x,y)) 
    // values on a fine mesh
    int N_vis_x = 100;
    int N_vis_y = 100;
    vector<double> x_vis(N_vis_x,0);
    vector<double> y_vis(N_vis_y,0);
    // z[i*N_vis_y+j] = f(x[i],y[j])
    vector<double> z_vis(N_vis_x*N_vis_y,0);

    // visualisation nodes for x
    double min_x = *min_element(x.begin(), x.end());
    double max_x = *max_element(x.begin(), x.end());
    double h_x = (max_x-min_x)/(N_vis_x-1);
    for(int i=0; i<x_vis.size(); ++i)
        x_vis[i] = min_x + i*h_x;

    // visualisation nodes for y
    double min_y = *min_element(y.begin(), y.end());
    double max_y = *max_element(y.begin(), y.end());
    double h_y = (max_y-min_y)/(N_vis_y-1);
    for(int i=0; i<y_vis.size(); ++i)
        y_vis[i] = min_y + i*h_y;

    double sigma_x = atof(argv[1]);
    double sigma_y = atof(argv[2]);
    interpolate_rbf(x,y,z,sigma_x,sigma_y,x_vis,y_vis,z_vis);

    // write data to the output file
    ofstream outfile;
    outfile.open("q2-result.txt");
    for(int i=0; i<N_vis_x; ++i)
        for(int j=0; j<N_vis_y; ++j)
            outfile << x_vis[i] << " " << y_vis[j] << " " << z_vis[i*N_vis_y+j] << endl;

    return 0;
}
