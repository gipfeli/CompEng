/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <cmath>
#include <vector>

using namespace std;

// Invert a matrix A using the Cramer's rule
int invert_3x3_matrix(double mat[], double inv_mat[])
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

// Multiply a by b, store the result in res
void mult_3x3_matrices(double a[], double b[], double res[])
{
	res[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
	res[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
	res[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];
	res[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
	res[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
	res[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];
	res[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
	res[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
	res[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
}
