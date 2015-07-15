//
//  question1.cpp
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
#include <numeric>
#include <algorithm>
#include <cstdlib>

#include "2x2_matrix_inv.h"

using namespace std;

void initData(vector<double>& x, vector<double>& y)
{
    //  Check if the sizes of the vectors are the same
    // if not - write an error message
    // and abort the program
    assert(x.size() == y.size());
    
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = i;
        y[i] = 0.5*x[i] - 1.0;
    }
}

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

// Struct to store coefficients of a straight line
struct Line
{
    double a, b;           // a + b*x
    Line(double a, double b) : a(a), b(b) {};
    
    double eval(double x)
    {   
        return a + b*x;
    }
};

// Helper function
double sumOfSqr(double a, double b)
{
    return a + b*b;
}

Line lsqline(vector<double>& x, vector<double>& y)
{
    // Check sizes of the vectors
    assert(x.size() == y.size());
    vector<double> A(4), invA(4), Y(2);
    
    // Compute elements of 2x2 matrix and RHS vector Y
    double sumX  = accumulate(x.begin(), x.end(), 0.0);
    double sumY  = accumulate(y.begin(), y.end(), 0.0);
    double sumX2 = accumulate(x.begin(), x.end(), 0.0, sumOfSqr);
    
    double sumXY = 0;
    for (int i = 0; i < x.size(); i++)
        sumXY += x[i]*y[i];
    
    // Initialize the matrix with corresponding elements
    A[0] = x.size();
    A[1] = sumX;
    A[2] = sumX;
    A[3] = sumX2;
    
    Y[0] = sumY;
    Y[1] = sumXY;
    
    // Invert the matrix
    assert(invert_2x2_matrix(A, invA) == 0);
    
    // Multiply Y by inverse A on the left
    // and return the resulting parameters
    return Line(invA[0]*Y[0] + invA[1]*Y[1],
                invA[2]*Y[0] + invA[3]*Y[1]);
}

int main()
{
    // Define vectors containing data
    vector<double> x(10), y(10);
    vector<double> yNoise1(10), yNoise2(10), yNoise3(10), yOut(10);
    
    //  We will push vectors to the container
    // and then dump all of the contents of the container
    vector< vector<double> > container;
    
    // ***************************************
    // Subquestion a)
    initData(x, y);
    container.push_back(x);
    container.push_back(y);
    dump("data_straight.txt", container);
    
    //  Let's immediately initialize data for
    // subquestions e) and f)
    
    // Add noise for sq. c)
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yNoise1[i] = y[i] + 0.01*(0.2*drand48() - 0.1);
    container.push_back(yNoise1);
    dump("data_noise1.txt", container);
    
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yNoise2[i] = y[i] + 1.0*(0.2*drand48() - 0.1);
    container.push_back(yNoise2);
    dump("data_noise2.txt", container);
    
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yNoise3[i] = y[i] + 10.0*(0.2*drand48() - 0.1);
    container.push_back(yNoise3);
    dump("data_noise3.txt", container);
    
    // Outlier for sq. d)
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yOut[i] = y[i] * ( (i == 7) ? 0.5 : 1.0 );
    container.push_back(yOut);
    dump("data_out.txt", container);
    
    // ***************************************
    // Subquestion b)
    // Initialize fine mesh for visualizing
    // Just two points are enough to define a line
    vector<double> xViz(2), yViz(2);
    xViz[0] = -1;
    xViz[1] = 10;
    
    container.clear();
    container.push_back(xViz);
    Line lStr = lsqline(x, y);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = lStr.eval(xViz[i]);
    container.push_back(yViz);
    dump("lsq_straight.txt", container);
    
    // ***************************************
    // Subquestion c)
    container.resize(1);
    Line ln1 = lsqline(x, yNoise1);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = ln1.eval(xViz[i]);
    container.push_back(yViz);
    dump("lsq_noise1.txt", container);
    
    container.resize(1);
    Line ln2 = lsqline(x, yNoise2);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = ln2.eval(xViz[i]);
    container.push_back(yViz);
    dump("lsq_noise2.txt", container);
    
    container.resize(1);
    Line ln3 = lsqline(x, yNoise3);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = ln3.eval(xViz[i]);
    container.push_back(yViz);
    dump("lsq_noise3.txt", container);
    
    // ***************************************
    // Subquestion d)
    container.resize(1);
    Line lOut = lsqline(x, yOut);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = lOut.eval(xViz[i]);
    container.push_back(yViz);
    dump("lsq_out.txt", container);
    
    // Bingo!
    return 0;
}


