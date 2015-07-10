
//
//  q2.cpp
//  exercise11
//
//  Created by Jonas Sukys on May 18, 2015.
//  Copyright (c) 2015 Jonas Sukys. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <iostream>

int evaluations = 0;
int maxDepth    = 0;

// Recursive Simpson's quadrature
double RecursiveSimpsons (double (*f)(double), double a, double b, double epsilon,
                         double S, double fa, double fm, double fb, int depth = 1) {
  // compute middle point
  double m = (a + b) / 2;
  
  // compute interval width
  double h = b - a;
  
  // compute midpoints of two refined intervals (left and right)
  double ml = (a + m)/2, mr = (m + b)/2;
  
  // evaluate function at new points ml and mr
  double fml = f(ml), fmr = f(mr);
  
  // evaluate Simpson's rule in both refined intervals
  double Sl = h / 12 * (fa + 4*fml + fm);
  double Sr = h / 12 * (fm + 4*fmr + fb);
  
  // compute the composite Simpson's rule for the refined intervals
  double Sf = Sl + Sr;
  
  // use Richardson extrapolation to estimate the error
  double error = (Sf - S);
  
  // if accuracy is reached, return the result obtained by Richardson extrapolation
  if ( fabs (error) <= epsilon || depth == 100 ) {
    evaluations += 1;
    if (depth > maxDepth)
      maxDepth = depth;
    return Sf;
  }
  
  // otherwise, refine the interval into two intervals [a, m] and [m, b]
  return   RecursiveSimpsons(f, a, m, epsilon / 2, Sl, fa, fml, fm, depth + 1)
         + RecursiveSimpsons(f, m, b, epsilon / 2, Sr, fm, fmr, fb, depth + 1);
}

// Adaptive Simpson's quadrature for interval [a, b] and tolerance eps
double adaptiveSimpsons (double (*f)(double), double a, double b, double epsilon) {
  
  // compute middle point
  double m = (a + b)/2;
  
  // compute interval width
  double h = b - a;
  
  // evaluate function at a, b, c
  double fa = f(a), fb = f(b), fm = f(m);
  
  // evaluate Simpson's rule
  double S = h / 6 * (fa + 4*fm + fb);
  
  // recursively perform adaptive Simpson's quadrature
  return RecursiveSimpsons (f, a, b, epsilon, S, fa, fm, fb);
}

double f (double x) { return exp(-3 * x) * sin (4*x); }

int main() {
  
  double a = 0;
  double b = 4;
  double epsilon = 1e-6;
  
  std::cout.precision (16);
  std::cout << "Adaptive: I = " << adaptiveSimpsons (f, a, b, epsilon);
  std::cout << " | " << evaluations << " evaluations";
  std::cout << " | max depth: " << maxDepth << std::endl;
  
  return 0;
}