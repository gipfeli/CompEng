//
//  main.cpp
//  exercise1
//
//  Created by Dmitry Alexeev on 04/03/15.
//  Copyright (c) 2015 CSE Lab, ETH Zurich. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <cstdlib>

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

// Basis functions
double lk(double x0, vector<double>& x, int k)
{
    double res = 1.0;
    
    for (int i = 0; i < x.size(); i++)
        if (i != k) res *= (x0 - x[i]) / (x[k] - x[i]);
    
    return res;
}

double lagrange(double x0, vector<double>& x, vector<double>& y)
{
    assert(x.size() == y.size());

    double res = 0;
    for (int k = 0; k < x.size(); k++)
        res += y[k] * lk(x0, x, k);
    return res;
}

int main()
{
    // Define vectors containing data
    vector<double> x(10), y(10), yNoise(10), yOut(10);
    
    //  We will push vectors to the container
    // and then dump all of the contents of the container
    vector< vector<double> > container;
    
    // ***************************************
    // Subquestion a)
    initData(x, y);
    container.push_back(x);
    container.push_back(y);
    dump("data_line.txt", container);
    
    //  Let's immediately initialize data for
    // subquestions e) and f)
    
    // Add noise for sq. e)
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yNoise[i] = y[i] + 0.2*drand48() - 0.1;
    container.push_back(yNoise);
    dump("data_noise.txt", container);
    
    // Outlier for sq. f)
    container.resize(1);
    for (int i = 0; i < y.size(); i++)
        yOut[i] = y[i] * ( (i == 7) ? 0.5 : 1.0 );
    container.push_back(yOut);
    dump("data_out.txt", container);

    // ***************************************
    // Subquestion b) - c)
    // Initialize fine mesh for visualizing
    vector<double> xViz(220), yViz(220);
    for (int i = 0; i < xViz.size(); i++)
        xViz[i] = 0.05 * i - 1.0;
    
    container.clear();
    container.push_back(xViz);
    for (int k = 0; k < 10; k++)
    {
        //  Calculate yk on a fine mesh
        // and push results to the container
        for (int i = 0; i < xViz.size(); i++)
            yViz[i] = lk(xViz[i], x, k);
        container.push_back(yViz);
    }
    dump("lks.txt", container);
    
    // ***************************************
    // Subquestion d)
    container.resize(1);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = lagrange(xViz[i], x, y);
    container.push_back(yViz);
    dump("lagrange.txt", container);
    
    // ***************************************
    // Subquestion e)
    container.resize(1);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = lagrange(xViz[i], x, yNoise);
    container.push_back(yViz);
    dump("lagrange_noise.txt", container);
    
    // ***************************************
    // Subquestion f)
    container.resize(1);
    for (int i = 0; i < xViz.size(); i++)
        yViz[i] = lagrange(xViz[i], x, yOut);
    container.push_back(yViz);
    dump("lagrange_out.txt", container);
    
    // Bingo!
    return 0;
}


