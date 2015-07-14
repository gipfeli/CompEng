/* Code for the Computational Methods for Engineering Applications class
 * Copyright CSElab, ETH Zürich, 2015
 */

#include <iostream>

// This file must (!) be included in order to use the 2x2 matrix inversion
#include "2x2_matrix_inv.h"

int main()
{
	// allocate matrices: original, inverted, their product
	// Every matrix A is stored in a vector V row-wise, i.e.
	// A_{i,j} -> V[i*2+j]

	vector<double> mat(4);
	vector<double> inv_mat(4);
	vector<double> prod_mat(4);

	// initialize the original matrix
	mat[0] = 1; mat[1] = 2;
	mat[2] = 3; mat[3] = 4;

	// output the original matrix
	cout << "Original matrix:" << endl << 
		mat[0] << " " << mat[1] << endl << 
		mat[2] << " " << mat[3] << endl;

	// invert mat, store result in inv_mat
	if(invert_2x2_matrix(mat, inv_mat) < 0)
	{
		// investion failed
		cout << "Error inverting matrix, stop." << endl;
		return -1;
	}

	// output the inverted matrix
	cout << "Inverted matrix:" << endl << 
		inv_mat[0] << " " << inv_mat[1] << endl << 
		inv_mat[2] << " " << inv_mat[3] << endl;

	// check if mat*inv_mat = I
	mult_2x2_matrices(mat, inv_mat, prod_mat);

	cout << "Product of matrices:" << endl << 
		prod_mat[0] << " " << prod_mat[1] << endl << 
		prod_mat[2] << " " << prod_mat[3] << endl;

	return 0;
}
