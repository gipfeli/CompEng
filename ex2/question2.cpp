//
//  question2.cpp
//  exercise2
//
//  Created by Dmitry Alexeev on 11/03/15.
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "3x3_matrix_inv.h"

using namespace std;

void initData(vector<double>& x, vector<double>& y, vector<double>& z)
{
    //  Check if the sizes of the vectors are the same
    // if not - write an error message
    // and abort the program
    assert(x.size() == y.size() && x.size() == z.size());
    
    // Initialize points on a uniform mesh
    for (int iv = 0; iv < x.size(); iv++)
    {
        // note: we assume data on a 10x10 grid (iv is in [0,99])
        int i = iv % 10;  // i in [0,9]
        int j = iv / 10;  // j in [0,9]
        x[iv] = i*0.1;
        y[iv] = j*0.1;
        z[iv] = x[iv] + y[iv];
    }
}

// Struct to store coefficients of a plane
struct Plane
{
    double a, b, c;           // a + b*x + c*y
    Plane(double a, double b, double c) : a(a), b(b), c(c) {};
    Plane() : a(0), b(0), c(0) {};
    
    Plane& operator=(const Plane& p)
    {
        if (this != &p)
            a = p.a; b = p.b; c = p.c;
        return *this;
    }
};

Plane lsqplane(vector<double>& x, vector<double>& y, vector<double>& z)
{
    // Check sizes of the vectors
    assert(x.size() == y.size());
    vector<double> A(9, 0), invA(9), Z(3, 0);
    
    // Compute elements of 3x3 matrix and RHS vector Y
    
    double sumXY = 0;
    for (int i = 0; i < x.size(); i++)
        sumXY += x[i]*y[i];
    
    // Fill A and Z with corresponding elements
    A[0] = x.size();
    for (int i = 0; i < x.size(); i++)
    {
        A[1] = A[3] = A[1] + x[i];
        A[2] = A[6] = A[2] + y[i];
        A[4] += x[i]*x[i];
        A[5] = A[7] = A[5] + x[i]*y[i];
        A[8] += y[i]*y[i];
        
        Z[0] += z[i];
        Z[1] += z[i]*x[i];
        Z[2] += z[i]*y[i];
    }
    
    // Invert the matrix
    assert(invert_3x3_matrix(A, invA) == 0);
    
    // Multiply Z by inverse A on the left
    // and return the resulting parameters
    return Plane(invA[0]*Z[0] + invA[1]*Z[1] + invA[2]*Z[2],
                 invA[3]*Z[0] + invA[4]*Z[1] + invA[5]*Z[2],
                 invA[6]*Z[0] + invA[7]*Z[1] + invA[8]*Z[2]);
}

int main()
{
    // Define vectors containing data
    int N = 100;
    vector<double> x(N), y(N), z(N), zNoise(N);
    
    // ***************************************
    // Subquestion b)
    // We're using two levels of noise
    initData(x, y, z);
    
    Plane p;
    cout << fixed << setprecision(5) << setw(9);
    
    for (int i = 0; i < z.size(); i++)
        zNoise[i] = z[i] + (0.2*drand48() - 0.1);
    p = lsqplane(x, y, zNoise);
    cout << "Fitted plane with N = " << N << " and noise of +-0.1:" << endl;
    cout << "   " << p.a << " + " << p.b << " * x + " << p.c << " * y" << endl << endl;
    
    for (int i = 0; i < z.size(); i++)
        zNoise[i] = z[i] + 10*(0.2*drand48() - 0.1);
    p = lsqplane(x, y, zNoise);
    cout << "Fitted plane with N = " << N << " and noise of +-1.0:" << endl;
    cout << "   " << p.a << " + " << p.b << " * x + " << p.c << " * y" << endl << endl;
   
    // ***************************************
    // Subquestion c)
    // N is decreased to 10, still we're using two noise magnitudes
    N = 10;
    x.resize(N);
    y.resize(N);
    z.resize(N);
    zNoise.resize(N);
    for (int i=0; i<N; i++)
    {
        x[i] = drand48();
        y[i] = drand48();
        z[i] = x[i] + y[i];
    }
    
    for (int i = 0; i < z.size(); i++)
        zNoise[i] = z[i] + (0.2*drand48() - 0.1);
    p = lsqplane(x, y, zNoise);
    cout << "Fitted plane with N = " << N << " and noise of +-0.1:" << endl;
    cout << "   " << p.a << " + " << p.b << " * x + " << p.c << " * y" << endl << endl;
    
    for (int i = 0; i < z.size(); i++)
        zNoise[i] = z[i] + 10*(0.2*drand48() - 0.1);
    p = lsqplane(x, y, zNoise);
    cout << "Fitted plane with N = " << N << " and noise of +-1.0:" << endl;
    cout << "   " << p.a << " + " << p.b << " * x + " << p.c << " * y" << endl << endl;

    
    // Bingo!
    return 0;
}


