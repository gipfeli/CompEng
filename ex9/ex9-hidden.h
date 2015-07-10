//
//  Exercise 9
//
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <vector>
#include <cassert>
#include <string.h>

// GSL library
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

using namespace std;

// B-spline: evaluate B_{i,d,t}(x)
// i in [1,N], t of size N+d+1
double Bspline(int i, int d, const vector<double>& t, double x) {
    if (d == 0) {
        if (t[i-1] <= x && x < t[i]) return 1;
        else return 0;
    } else {
        double res = 0;
        double Btmp = Bspline(i, d-1, t, x);
        if (Btmp != 0) res += Btmp * (x - t[i-1]) / (t[i-1+d] - t[i-1]);
        Btmp = Bspline(i+1, d-1, t, x);
        if (Btmp != 0) res += Btmp * (t[i+d] - x) / (t[i+d] - t[i]);
        return res;
    }
}

// MyMatrix
class MyMatrix {
    // data
    vector<double> dat;
    int N,M;
    
public:
    // construct N x M matrix
    MyMatrix(int N, int M): dat(N*M), N(N), M(M) { }
    
    // access
    double& operator()(int r, int c) { return dat[r*M + c]; }
    double operator()(int r, int c) const { return dat[r*M + c]; }
    
    // solve A p = q for p
    void solve(vector<double>& p, const vector<double>& q) {
        assert(N==M); // only for square matrices
        
        gsl_matrix * A_gsl = gsl_matrix_alloc(N,N);
        memcpy(A_gsl->data, &dat[0], N*N*sizeof(double));
        gsl_vector * q_gsl = gsl_vector_alloc(N);
        memcpy(q_gsl->data, &q[0], N*sizeof(double));
        
        gsl_permutation * prm = gsl_permutation_alloc(N);
        int signum;
        gsl_linalg_LU_decomp(A_gsl, prm, &signum);
        
        gsl_vector * p_gsl = gsl_vector_alloc(N);
        gsl_linalg_LU_solve(A_gsl, prm, q_gsl, p_gsl);
        
        p.resize(N);
        memcpy(&p[0], p_gsl->data, N*sizeof(double));
    }
};
