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

// Interpolate the data set (x,y) with the natural cubic spline. divert(-1)
// The function assumes that the values in x are sorted and there are no entries in x with the same value.
// divert(0)
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
    // Assemble the system; note that it is a tridiagonal one, so we store it as 3 vectors divert(-1)
    /* Solve the system for {d_i},i=1,...,N, from which the coefficients {a_0,a_1,a_2,a_3}
     * of every spline P_i(x) = a_0 + a_1(x-x_i) + a_2(x-x_i)^3 + a_3(x_{i+1}-x)^3 
     * on the interval [x_i,x_{i+1}] can be obtained as:
     * a_0 = y_i - d_i *(x_{i+1}-x_i)^2/6
     * a_1 = (y_{i+1}-y_i)/(x_{i+1}-x_i) - (d_{i+1}-d_i)*(x_{i+1}-x_i)/6
     * a_2 = d_{i+1}/(6*(x_{i+1}-x_i))
     * a_3 = d_i/(6*(x_{i+1}-x_i))
     * The system for d_i is:
     * d_1 = 0 or 2*d_1/(x_2-x_1) + (x_2-x_1)*d_2 = 6*(y_2-y_1)/(x_2-x_1)
     * (x_{i}-x_{i-1})*d_{i-1} + 2*(x_{i+1}-x_{i-1})*d_i + (x_{i+1}-x_i)*d_{i+1} = 
     *        6*(y_{i+1}-y_i)/(x_{i+1}-x_i) - 6*(y_i-y_{i-1})/(x_i-x_{i-1}), i=2,...,N-1
     * d_N = 0 or (x_{N}-x_{N-1})*d_{N-1} + 2*(x_{N}-x_{N-1})*d_{N} = -6*(y_{N}-y_{N-1})/(x_{N}-x_{N-1})
     */
    // divert(0)

    int N = x.size();

    vector<double> lower(N-1);
    vector<double> diag(N);
    vector<double> upper(N-1);
    vector<double> rhs(N);

    // FILL HERE: fill in the matrix divert(-1)
    if(l_clamped == 0)
    {
        diag[0] = 1;
        upper[0] = 0;
        rhs[0] = 0;
    }
    else
    {
        double dx = x[1]-x[0];
        assert(fabs(dx) > 0);
        diag[0] = 2*dx;
        upper[0] = dx;
        rhs[0] = 6*(y[1]-y[0])/dx;
    }

    for(int i=1; i<N-1; ++i)
    {
        double dx[] = {x[i]-x[i-1], x[i+1]-x[i]};
        assert(fabs(dx[0]) > 0 && fabs(dx[1]) > 0);
        lower[i-1] = dx[0];
        diag[i] = 2*(dx[0]+dx[1]);
        upper[i] = dx[1];
        rhs[i] = 6*( (y[i+1]-y[i])/dx[1] - (y[i]-y[i-1])/dx[0] );
        // cout << i << " " << lower[i] << " " << diag[i] << " " << upper[i] << endl;
    }

    if(r_clamped == 0)
    {
        lower[N-2] = 0;
        diag[N-1] = 1;
        rhs[N-1] = 0;
    }
    else
    {
        double dx = x[N-1]-x[N-2];
        assert(fabs(dx) > 0);
        lower[N-2] = dx;
        diag[N-1] = 2*dx;
        rhs[N-1] = -6*(y[N-1]-y[N-2])/dx;
    }
    // divert(0)

    // Solve the system and store the result in d
    vector<double> d(N,0);
    solve_thomas(lower,diag,upper,rhs,d);

    // FILL HERE: Evaluate the interpolation function on the visualisation grid (x_vis,y_vis) divert(-1)
    int k = 0;
    double ak[4]; // interpolation coefficients
    for(int i=0; i<x_vis.size(); ++i)
    {
        // find an interval [x[k-1],x[k]] to which x_vis[i] belongs
        int flag = 0; // indicates that we switched to a new interval
        while(x_vis[i]>x[k] && k<N)
        {
            k++;
            flag = 1;
        }
        if(flag)
        {
            // we are now at a new interval, recompute the interpolation coefficients
            double dxk = x[k]-x[k-1];
            ak[0] = y[k-1]-d[k-1]*dxk*dxk/6.0;
            ak[1] = (y[k]-y[k-1])/dxk - (d[k]-d[k-1])*dxk/6.0;
            ak[2] = d[k]/(6.0*dxk);
            ak[3] = d[k-1]/(6.0*dxk);
            /*cout << "ak[0] = " << y[k-1] << " - 1/6 * " << d[k-1] << " * " << dxk << "^2 = " << ak[0] << endl;
            cout << x[k-1] << " " << x[k] << " " << x[k+1] << endl;
            cout << y[k-1] << " " << y[k] << " " << y[k+1] << endl;
            cout << endl;*/
            // cout << ak[0] << " " << ak[1] << " " << ak[2] << " " << ak[3] << endl;
        }

        if(k == 0)
            y_vis[i] = y[0];
        else if(k == N)
            y_vis[i] = y[N-1];
        else
        {
            double dxik[2] = {x_vis[i]-x[k-1], x[k]-x_vis[i]};

            // evaluate the interpolation polynomial
            y_vis[i] = ak[0] + dxik[0]*( ak[1] + dxik[0]*dxik[0]*ak[2] )+ dxik[1]*dxik[1]*dxik[1]*ak[3];
        }
    }
    // divert(0)
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
