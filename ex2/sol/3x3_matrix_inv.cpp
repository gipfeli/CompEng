/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <iostream>

// This file must (!) be included in order to use the 3x3 matrix inversion
#include "3x3_matrix_inv.h"

int main()
{
	// allocate matrices: original, inverted, their product
	// Every matrix A is stored in a vector V row-wise, i.e.
	// A_{i,j} -> V[i*3+j]

	vector<double> mat(9);
	vector<double> inv_mat(9);
	vector<double> prod_mat(9);

	// initialize the original matrix
	mat[0] = 1; mat[1] = 2; mat[2] = 3;
	mat[3] = 1; mat[4] = 2; mat[5] = 4;
	mat[6] = 1; mat[7] = 4; mat[8] = 5;

	// output the original matrix
	cout << "Original matrix:" << endl << 
		mat[0] << " " << mat[1] << " " << mat[2] << endl << 
		mat[3] << " " << mat[4] << " " << mat[5] << endl << 
		mat[6] << " " << mat[7] << " " << mat[8] << endl;

	// invert mat, store result in inv_mat
	if(invert_3x3_matrix(mat, inv_mat) < 0)
	{
		// investion failed
		cout << "Error inverting matrix, stop." << endl;
		return -1;
	}

	// output the inverted matrix
	cout << "Inverted matrix:" << endl << 
		inv_mat[0] << " " << inv_mat[1] << " " << inv_mat[2] << endl << 
		inv_mat[3] << " " << inv_mat[4] << " " << inv_mat[5] << endl << 
		inv_mat[6] << " " << inv_mat[7] << " " << inv_mat[8] << endl;

	// check if mat*inv_mat = I
	mult_3x3_matrices(mat, inv_mat, prod_mat);

	cout << "Product of matrices:" << endl << 
		prod_mat[0] << " " << prod_mat[1] << " " << prod_mat[2] << endl << 
		prod_mat[3] << " " << prod_mat[4] << " " << prod_mat[5] << endl << 
		prod_mat[6] << " " << prod_mat[7] << " " << prod_mat[8] << endl;

	return 0;
}
