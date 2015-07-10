//
//  main.cpp
//  exercise10
//
//  Created by Dmitry Alexeev on 11/05/15.
//  Copyright (c) 2015 Dmitry Alexeev. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

//  Write vectors in data column by column
// (it is easier to plot later on)
void dump(const string fname, vector< vector<double> >& data)
{
    // Check if the sizes of all vectors are the same
    for (int i = 1; i < data.size(); i++)
        assert(data[i-1].size() == data[i].size());
    
    if (data.size() == 0) return;
    int n = data[0].size();
    
    // Open the file and check that we can write in it
    ofstream fout(fname.c_str());
    assert(fout.good());
    
    for (int line = 0; line < n; line ++)
    {
        for (int i = 0; i < data.size(); i++)
            fout << data[i][line] << "  ";
        fout << endl;
    }
    
    //  File will be closed and saved by the destructor
    // when fout object leaves the scope
}

// Integration function
// e^(-x^2)
double func(double x)
{
    return M_2_SQRTPI * exp(-x*x);
}

// Intergate according to Romberg method
// Output intermediate integrals and errors if verbose == true
// exact is only used if verbose is set to true
double integrateRomberg(int maxk, double a, double b, bool verbose, double exact)
{
    // Arrays to store intermediate results
    int maxlogn = maxk;
    int shift = maxlogn + 1;
    int maxn = pow(2, maxlogn);
    vector<double> I((maxlogn+1)*(maxk+1));
    vector<double> f(maxn+1);
    
    // Precompute the function on certain points
    double hmin = (b-a) / maxn;
    for (int i=0; i<=maxn; i++)
        f[i] = func(a + i*hmin);
    
    // Compute level 0 integrals
    // ln always means log2(n), so 2^ln = n
    for (int ln=0; ln<=maxlogn; ln++)
    {
        const int n = pow(2, ln);
        const int step = maxn / n;
        double res = 0;
        
        for (int i=step; i<maxn; i+=step)
            res += f[i];
        
        I[ln] = 0.5*(b - a)/n * (f[0] + f[maxn] + 2*res);
    }
    
    // Advance to higher precision according to Romberg
    for (int k=1; k<=maxk; k++)
        for (int ln=0; ln<=maxlogn - k; ln++)
        {
            double _4k = pow(4, k);
            I[ln + shift*k] = (_4k * I[ln+1 + shift*(k-1)] - I[ln + shift*(k-1)]) / (_4k - 1);
        }

    if (verbose)
    {
        // Output integrals
        cout << "Computed integrals:" << endl;
        cout.precision(10);
        for (int ln=0; ln<=maxlogn; ln++)
        {
            for (int k=0; k<=maxk; k++)
                if (ln <= maxk - k)
                {
                    cout << "I(" << right << setw(3) << (1<<ln) << "," << setw(2) << k << "): ";
                    cout << setw(12) << left << I[ln + shift*k] << "      ";
                }
            cout << endl;
        }
        
        // Output errors
        cout << scientific << endl;
        cout.precision(6);
        
        cout << "Errors: " << endl;
        for (int ln=0; ln<=maxlogn; ln++)
        {
            for (int k=0; k<=maxk; k++)
                if (ln <= maxk - k)
                {
                    cout << "E(" << right << setw(3) << (1<<ln) << "," << setw(2) << k << "): ";
                    cout << setw(12) << left << fabs(exact - I[ln + shift*k]) << "      ";
                }
            cout << endl;
        }
    }
    
    return I[0 + maxlogn*maxk];
}

int main(int argc, const char * argv[])
{
    
    // Show the integration of erf(0.5) in details
    integrateRomberg(4, 0, 0.5, true, erf(0.5));
    
    int resolution = 100;
    vector<double> xViz(resolution), yViz(resolution);
    for (int i=0; i<resolution; i++)
    {
        xViz[i] = i / (double) resolution;
        yViz[i] = 1200 - 400 * integrateRomberg(4, 0, 2*xViz[i], false, 0);
    }
    
    vector< vector<double> > container;
    container.push_back(xViz);
    container.push_back(yViz);
    dump("vel.txt", container);
    
    return 0;
}
