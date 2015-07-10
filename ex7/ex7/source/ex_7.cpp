//
//  main.cpp
//  Exercise 7
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
    // FILL HERE 
}

void calculate_Jacobian( vector<double> & J, vector<double> & x )
{
    // FILL HERE 
}

void solve_system( vector<double> & y, vector<double> & J, vector<double> & F )
{
    // Invert J, store result in J_inv
    vector<double> J_inv(9);
    assert(invert_3x3_matrix(J, J_inv) == 0);
    
    // Solve linear system: y = - J_inv * F
    // FILL HERE 
}

double calculate_error( vector<double> & y )
{
    return sqrt(y[0]*y[0] + y[1]*y[1] + y[2]*y[2]);
}

void update_solution( vector<double> & x_curr, vector<double> & x_prev, vector<double> & y )
{
    for( unsigned i = 0; i < x_curr.size(); ++i ) {
        // FILL HERE 
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
