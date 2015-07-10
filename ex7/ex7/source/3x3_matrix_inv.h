/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <cmath>
#include <vector>

using namespace std;

// Numbering of matrices:
//     mat[0] mat[1] mat[2]
// A = mat[3] mat[4] mat[5]
//     mat[6] mat[7] mat[8]

// Invert a matrix A using the Cramer's rule
int invert_3x3_matrix(vector<double> const & mat, vector<double> & inv_mat)
{
    double det = mat[0]*(mat[4]*mat[8] - mat[5]*mat[7])
        - mat[1]*(mat[3]*mat[8] - mat[5]*mat[6])
        + mat[2]*(mat[3]*mat[7] - mat[4]*mat[6]);
    if(fabs(det) < 1e-16) // if the determinant is too small, can't invert!
        return -1;

    double inv_det = 1.0/det;

    inv_mat[0] =  (mat[4]*mat[8] - mat[5]*mat[7])*inv_det;
    inv_mat[1] =  -(mat[1]*mat[8] - mat[2]*mat[7])*inv_det;
    inv_mat[2] =  (mat[1]*mat[5] - mat[2]*mat[4])*inv_det;
    inv_mat[3] =  -(mat[3]*mat[8] - mat[5]*mat[6])*inv_det;
    inv_mat[4] =  (mat[0]*mat[8] - mat[2]*mat[6])*inv_det;
    inv_mat[5] =  -(mat[0]*mat[5] - mat[2]*mat[3])*inv_det;
    inv_mat[6] =  (mat[3]*mat[7] - mat[4]*mat[6])*inv_det;
    inv_mat[7] =  -(mat[0]*mat[7] - mat[1]*mat[6])*inv_det;
    inv_mat[8] =  (mat[0]*mat[4] - mat[1]*mat[3])*inv_det;

    return 0;
}
