//
//  main.cpp
//  Exercise 7 - Question 1(b)
//
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

int main()
{
    vector<double> K(3);        // values of k1, k2, k3, from question 1(a)
    double x_prev;              // value of unknown on previous iteration
    double x_curr;              // unknowns
    double F;                   // residual
    double J;                   // Jacobian "matrix"
    double y;                   // difference
    const double tol = 1.e-5;     // tolerance of the method
    const unsigned k_max = 20;    // maximum number of iterations
    
    
    // Set values of k1, k2, k3 from question 1(a)
    K[0] = 87.7129;
    K[1] = 2.59695;
    K[2] = -137.228;


    // Newton's method:
    
    // Initial guess
    x_curr = 2;
    
    unsigned k = 1;
    while( k <= k_max )
    {
        // Update initial values
        x_prev = x_curr;
        
        // Calculate Residuals
        F = -50000/(M_PI*x_prev*x_prev) + K[0]*exp(K[1]*x_prev) + K[2]*x_prev;
        
        // Compute the Jacobian
        J = 100000/(M_PI*x_prev*x_prev*x_prev) + K[0]*K[1]*exp(K[1]*x_prev) + K[2];
        
        // Update of solution
        assert( J != 0 );
        x_curr = x_prev - F / J;
        
        // Calculate error
        double error = sqrt( (x_curr-x_prev) * (x_curr-x_prev) );
        
        // Print solution
        if( k==1 )
            cout << setw(5) << "iter" << setw(15) << "solution" << setw(15) << "error" << endl;
        cout << setw(5) << k << setw(15) << x_curr << setw(15) << error << endl;
        
        // Check if we have comvergence of the solution
        if( error < tol ) break;
        
        ++k;
    }
    
    return 0;
}
