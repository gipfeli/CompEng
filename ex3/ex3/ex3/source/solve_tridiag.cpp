/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <iostream>

// This file must (!) be included in order to use the Thomas algorithm
#include "solve_tridiag.h"

int main()
{
    // initialise a NxN tridiagonal matrix by setting the vectors of
    // lower-diagonal, diagonal and upper-diagonal elements
    int N = 10;
    vector<double> lower(N-1,1);
    vector<double> diag(N,2);
    vector<double> upper(N-1,1);

    // initialize the RHS
    vector<double> rhs(N,4);
    rhs[0] = 3;
    rhs[N-1] = 3;

    // workspace for the solution
    vector<double> solution(N,0);

    if(solve_thomas(lower,diag,upper,rhs,solution) < 0)
    {
        cout << "Error solving system, stop." << endl;
        return -1;
    }

    // print the error
    cout << "l2 error: " << get_l2_error(lower,diag,upper,rhs,solution) << endl;

    return 0;
}
