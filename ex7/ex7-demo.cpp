//
// Demo for Newton's method
// 
// Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // setup
    const int maxsteps = 10;
    const double tol = 1e-10;
    
    // initial guess
    double x = 2;
    
    for (int i = 0; i < maxsteps; ++i) {
        // compute f(x)
        double fx = x*x - 5;
        // compute f'(x)
        double fpx = 2*x;
        // report
        cout << i << ": x = " << x << ", f(x) = " << fx << endl;
        // get update
        double y = -fx/fpx;
        // update x
        x = x + y;
        // did we converge?
        if (abs(y) < tol) break;
    }
    
    return 0;
}
