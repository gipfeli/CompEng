/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <cmath>
#include <vector>

using namespace std;

// Invert a matrix A using the Cramer's rule
int invert_2x2_matrix(vector<double> const & mat, vector<double> & inv_mat)
{
    double det = mat[0]*mat[3] - mat[1]*mat[2];
    if(fabs(det) < 1e-16) // if the determinant is too small, can't invert!
        return -1;

    double inv_det = 1.0/det;

    inv_mat[0] =  mat[3]*inv_det;
    inv_mat[1] = -mat[1]*inv_det;
    inv_mat[2] = -mat[2]*inv_det;
    inv_mat[3] =  mat[0]*inv_det;

    return 0;
}

// Multiply a by b, store the result in res
void mult_2x2_matrices(vector<double> const & a,
                       vector<double> const & b,
                       vector<double> & res)
{
    res[0] = a[0]*b[0] + a[1]*b[2];
    res[1] = a[0]*b[1] + a[1]*b[3];
    res[2] = a[2]*b[0] + a[3]*b[2];
    res[3] = a[2]*b[1] + a[3]*b[3];
}
