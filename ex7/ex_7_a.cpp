//
//  main.cpp
//  Exercise 7 - Question 1(a)
//
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include "3x3_matrix_inv.h"

using namespace std;

void calculate_Residuals( vector<double> & F, vector<double> & x )
{
    // FILL HERE divert(-1)
    F[0] = x[0]*exp(0.1*x[1]) + 0.1*x[2] - 100.;
    F[1] = x[0]*exp(0.2*x[1]) + 0.2*x[2] - 120.;
    F[2] = x[0]*exp(0.3*x[1]) + 0.3*x[2] - 150.;
    // divert(0)
}

void calculate_Jacobian( vector<double> & J, vector<double> & x )
{
    // FILL HERE divert(-1)
    J[0] = exp(0.1*x[1]);
    J[1] = 0.1*x[0]*exp(0.1*x[1]);
    J[2] = 0.1;
    J[3] = exp(0.2*x[1]);
    J[4] = 0.2*x[0]*exp(0.2*x[1]);
    J[5] = 0.2;
    J[6] = exp(0.3*x[1]);
    J[7] = 0.3*x[0]*exp(0.3*x[1]);
    J[8] = 0.3;
    // divert(0)
}

void solve_system( vector<double> & y, vector<double> & J, vector<double> & F )
{
    // Invert J, store result in J_inv
    vector<double> J_inv(9);
    assert(invert_3x3_matrix(J, J_inv) == 0);
    
    // Solve linear system: y = - J_inv * F
    // FILL HERE divert(-1)
    y[0] = -(J_inv[0]*F[0] + J_inv[1]*F[1] + J_inv[2]*F[2]);
    y[1] = -(J_inv[3]*F[0] + J_inv[4]*F[1] + J_inv[5]*F[2]);
    y[2] = -(J_inv[6]*F[0] + J_inv[7]*F[1] + J_inv[8]*F[2]);
    // divert(0)
}

double calculate_error( vector<double> & y )
{
    return sqrt(y[0]*y[0] + y[1]*y[1] + y[2]*y[2]);
}

void update_solution( vector<double> & x_curr, vector<double> & x_prev, vector<double> & y )
{
    for( unsigned i = 0; i < x_curr.size(); ++i ) {
        // FILL HERE divert(-1)
        x_curr[i] = x_prev[i] + y[i];
        // divert(0)
    }
}

void print_solution( unsigned k, vector<double> & x, double error )
{
    if( k == 1 )
    cout << "\n" << setw(5) << "iter" << setw(15) << "k_1" << setw(15) << "k_2" << setw(15) << "k_3" << setw(15) << "error" << endl;
    cout << setw(5) << k << setw(15) << x[0] << setw(15) << x[1] << setw(15) << x[2] << setw(15) << error << endl;
}


int main()
{
    vector<double> x_prev(3);       // vector with values of unknowns on previous iteration
    vector<double> x_curr(3);       // vector with unknowns
    vector<double> F(3);            // vector with residuals
    vector<double> J(9);            // vector with elements of Jacobian matrix
    vector<double> y(3);            // vector with difference
    const double tol = 1.e-5;       // tolerance of the method
    const unsigned k_max = 20;      // maximum number of iterations
    
    
    // Newton's method:
    
    // Initial guess
    x_curr[0] = 80;
    x_curr[1] = 10;
    x_curr[2] = 1;
    
    unsigned k = 1;
    while( k <= k_max )
    {
        // Update initial values
        x_prev = x_curr;
        
        // Calculate Residuals
        calculate_Residuals( F, x_prev );
        
        // Compute the Jacobian
        calculate_Jacobian( J, x_prev );
        
        // Solve the linear system
        solve_system( y, J, F );
        
        // Update of solution
        update_solution( x_curr, x_prev, y );
        
        // Calculate and print solution on screen
        double error = calculate_error( y );
        print_solution( k, x_curr, error );
        
        // Check if we have comvergence of the solution
        if( error < tol ) break;
        
        ++k;
    }
    
    return 0;
}
