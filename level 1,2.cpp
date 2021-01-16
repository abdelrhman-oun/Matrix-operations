/*--------------------------------------------------------------------------------------------------------------------------
* file name  :	level 1_2.cpp
* Author     :	OUN
* Created on :	June 22, 2019
* description:	c++ program to do Matrix operations. The program use
				a defined string format to represent the matrix in the user input and output
				sections.
				supporting two levels 
					level 1 add, subtract and multiply opirations
					level 2 power, transpose and Determinant opirations
--------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include <iostream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>


/*-----------------------------------------------FUNCTIONS DEFINITIONS-----------------------------------------------------*/

float determinant(float matrix[100][100], int n) {
	float det = 0;
	float submatrix[100][100];
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}
	return det;
}


using namespace std;
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



	/*----------------------------------------------- INPUT -----------------------------------------------------*/
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

	/*----------------------------------------------- chick data of matrix 1 -----------------------------------------------------*/

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

		/*----------------------------------------------- chick data of matrix 2 -----------------------------------------------------*/
		for (int q = 0; q < j2; q++) {
			if (arr2[q] != arr2[q + 1]) {
				cout << "ERROR";
				return 0;
			}
		}
	}


	/*----------------------------------------------- chick -----------------------------------------------------*/

	if ((operat == "+" || operat == "-") && (row1 != row2 || column1 != column2)) {
		cout << "ERROR";
		return 0;
	}
	if (operat == "*" && column1 != row2) {
		cout << "ERROR";
		return 0;
	}
	if ((operat == "^" || operat == "D") && row1 != column1) {
		cout << "ERROR";
		return 0;
	}



	/*----------------------------------------------- OPIRATINOS LEVEL 1 -----------------------------------------------------*/
	float ans[100][100];
	float row_ans = 0, column_ans = 0, res = 0;
	if (operat == "+") {
		row_ans = row1;
		column_ans = column1;
		for (int j = 0; j < row_ans; j++) {
			for (int k = 0; k < column_ans; k++)
				ans[j][k] = mtx1[j][k] + mtx2[j][k];
		}
	}
	else if (operat == "-") {
		row_ans = row1;
		column_ans = column1;
		for (int j = 0; j < row_ans; j++) {
			for (int k = 0; k < column_ans; k++)
				ans[j][k] = mtx1[j][k] - mtx2[j][k];
		}
	}
	else if (operat == "*") {
		row_ans = row1;
		column_ans = column2;
		for (int k = 0; k < row_ans; k++) {
			for (int l = 0; l < column_ans; l++) {
				for (int m = 0; m < row2; m++) {
					res += mtx1[k][m] * mtx2[m][l];
				}
				ans[k][l] = res;
				res = 0;
			}
		}
	}
	/*----------------------------------------------- OPIRATINOS LEVEL 2 -----------------------------------------------------*/

	/*
		-- POWER
		*/
	else if (operat == "^") {
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
	/*----------------------------------------------- OPIRATINOS LEVEL 3 -----------------------------------------------------*/







	/*----------------------------------------------------- OUTPUT -----------------------------------------------------------*/
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