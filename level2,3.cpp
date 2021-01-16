/*--------------------------------------------------------------------------------------------------------------------------
* file name  :	level 2_3.cpp
* Author     :	OUN
* Created on :	June 22, 2019
* description:	c++ program to do Matrix operations. The program use
				a defined string format to represent the matrix in the user input and output
				sections.
				supporting two levels
					level 2 power, transpose and Determinant opirations
					level 3 inverseinverse and Divide opirations
--------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include <iostream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>
using namespace std;
/*-------------------------------------------------GLOPAL VARIABLES--------------------------------------------------------*/
float inv[100][100];

/*-----------------------------------------------FUNCTIONS DEFINITIONS-----------------------------------------------------*/
float determinant(float matrix[100][100], int n) {
	float det = 0;
	if (n == 2) {
		float det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
		return det;
	}
	else {
		float mat[100][100];
		int nn = n;
		for (int k = 0; k < nn; k++) {
			for (int i = 1; i < nn; i++) {
				int column = 0;
				for (int j = 0; j < nn; j++) {
					if (column < k) {
						mat[i - 1][column] = matrix[i][j];
					}
					else {
						mat[i - 1][column] = matrix[i][j + 1];
					}
					column++;
				}
			}
			det += pow((-1), k) * matrix[0][k] * determinant(mat, n - 1);
		}
	}
	return det;
}

void inverse(float matrex[100][100], int n) {
	float mat[100][100], mat2[100][100], adj[100][100];
	if (n == 2) {
		adj[0][0] = matrex[1][1];
		adj[0][1] = -matrex[0][1];
		adj[1][0] = -matrex[1][0];
		adj[1][1] = matrex[0][0];
	}
	else {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				int subi = 0;
				for (int i = 0; i < n; i++) {
					if (i == y)
						continue;
					int subj = 0;
					for (int j = 0; j < n; j++) {
						if (j == x)
							continue;
						mat[subi][subj] = matrex[i][j];
						subj++;
					}
					subi++;
				}
				mat2[y][x] = pow(-1, (x + y)) * determinant(mat, n - 1);
			}
		}
		for (int k = 0; k < n; k++) {
			for (int l = 0; l < n; l++) {
				adj[l][k] = mat2[k][l];
			}
		}
	}
	float det = determinant(matrex, n);
	if (det != 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				inv[i][j] = adj[i][j] / det;
			}
		}
	}
	else cout << "ERROR";
}


int main() {

	int arr1[100], arr2[100];
	string str1, str2;
	string str4, str5;
	int row1 = 0, column1 = 0, j1 = 0;
	int row2 = 0, column2 = 0, j2 = 0;
	float mtx1[100][100];
	float mtx2[100][100];
	int power = 0;
	float det = 0;



	/*-------------------------------------------------INPUT--------------------------------------------------------*/
	getline(cin, str1);
	for (int i = 0; i < str1.length() - 1; i++) {
		if (str1[i] == ';') {
			row1++;
			j1++;
			column1 = 0;
		}
		if (str1[i] == ' ' || str1[i] == '[' || str1[i] == ';') {
			str2 = str1.substr(i + 1, str1.find(' ', i + 1) - i | str1.find(']', i + 1) - i | str1.find(';', i + 1) - i);
			mtx1[row1][column1] = atof(str2.c_str());
			arr1[j1] = column1;
			column1++;


		}
	}
	row1++;

	/*-------------------------------------------------chick data of matrix 1--------------------------------------------------------*/

	for (int q = 0; q < j1; q++) {
		if (arr1[q] != arr1[q + 1]) {
			cout << "ERROR";
			return 0;
		}
	}


	string operat;
	getline(cin, operat);



	if (operat == "^") {
		cin >> power;
	}

	else if (operat == "+" || operat == "-" || operat == "*" || operat == "/") {
		getline(cin, str4);

		for (int i = 0; i < str4.length() - 1; i++) {
			if (str4[i] == ';') {
				row2++;
				j2++;
				column2 = 0;
			}
			if (str4[i] == ' ' || str4[i] == '[' || str4[i] == ';') {
				str5 = str4.substr(i + 1, str4.find(' ', i + 1) - i | str4.find(']', i + 1) - i | str4.find(';', i + 1) - i);
				mtx2[row2][column2] = atof(str5.c_str());
				arr2[j2] = column2;
				column2++;
			}
		}
		row2++;
		/*-------------------------------------------------chick data of matrix 2--------------------------------------------------------*/

		for (int q = 0; q < j2; q++) {
			if (arr2[q] != arr2[q + 1]) {
				cout << "ERROR";
				return 0;
			}
		}
	}


	/*-------------------------------------------------------------chick-----------------------------------------------------------------*/

	if ((operat == "+" || operat == "-") && (row1 != row2 || column1 != column2)) {
		cout << "ERROR";
		return 0;
	}
	if ((operat == "*" || operat == "/") && column1 != row2) {
		cout << "ERROR";
		return 0;
	}
	if ((operat == "^" || operat == "D" || operat == "I") && row1 != column1) {
		cout << "ERROR";
		return 0;
	}
	/*--------------------------------------------------------OPIRATIONS LEVEL 2---------------------------------------------------------*/
	float ans[100][100];
	float row_ans = 0, column_ans = 0, res = 0;


	/*
	-- POWER
	*/
	if (operat == "^") {
		row_ans = row1;
		column_ans = column1;
		float mtx3[100][100];
		for (int k = 0; k < row_ans; k++) {
			for (int l = 0; l < column_ans; l++) {
				mtx3[k][l] = mtx1[k][l];
			}
		}
		for (int j = 0; j < power - 1; j++) {
			for (int k = 0; k < row_ans; k++) {
				for (int l = 0; l < column_ans; l++) {
					for (int m = 0; m < row_ans; m++) {
						res += mtx3[k][m] * mtx1[m][l];
					}
					ans[k][l] = res;
					res = 0;
				}
			}
			for (int k = 0; k < row_ans; k++) {
				for (int l = 0; l < column_ans; l++) {
					mtx3[k][l] = ans[k][l];
				}
			}


		}
	}
	/*
	-- TRANSPOSE
	*/
	if (operat == "T") {
		row_ans = row1;
		column_ans = column1;
		for (int k = 0; k < row_ans; k++) {
			for (int l = 0; l < column_ans; l++) {
				ans[l][k] = mtx1[k][l];
			}
		}
		row_ans = column1;
		column_ans = row1;
	}
	/*
	-- DETRMENATION
	*/
	if (operat == "D") {
		det = determinant(mtx1, row1);
	}
	/*--------------------------------------------------------OPIRATIONS LEVEL 1---------------------------------------------------------*/

	/*
	-- Inverse
	*/
	if (operat == "I") {
		inverse(mtx1, row1);
		for (int  i= 0; i < row1; i++) {
			for (int j = 0; j < row1; j++) {
				ans[i][j]= inv[i][j];
			}
		}
		row_ans = row1;
		column_ans = column1;
	}
	/*
	-- Divide by another Matrix
	*/
	if (operat == "/") {
		inverse(mtx2, row2);
		row_ans = row1;
		column_ans = column2;
		for (int k = 0; k < row_ans; k++) {
			for (int l = 0; l < column_ans; l++) {
				for (int m = 0; m < row2; m++) {
					res += mtx1[k][m] * inv[m][l];
				}
				ans[k][l] = res;
				res = 0;
			}
		}
	}


	/*--------------------------------------------------------OUTPUT---------------------------------------------------------*/
	if (operat != "D") {
		string str = "[";
		ostringstream ss;
		for (int j = 0; j < row_ans; j++) {
			for (int k = 0; k < column_ans; k++) {
				ss << ans[j][k];
				if (k == column_ans - 1)
					break;
				else
					ss << " ";
			}
			if (j == row_ans - 1)
				break;
			else
				ss << ";";
		}
		ss << "]";
		str.append(ss.str());
		cout << str;
	}
	else
		cout << det;


	return 0;
}