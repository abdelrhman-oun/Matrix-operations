
/*--------------------------------------------------------------------------------------------------------------------------
* file name  :	pounas.cpp
* Author     :	OUN
* Created on :	June 22, 2019
* description:	c++ program to do Matrix operations. The program use
				a defined string format to represent the matrix in the user input and output
				sections.
				supporting complex values in the matrix elements
--------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include <iostream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>
using namespace std;

/*----------------------------------------------------CLASSES------------------------------------------------------------*/

class Complex {
	float real;
	float imag;
public:
	Complex() {
		real = 0;
		imag = 0;
	}
	Complex(float i, float j) {
		real = i;
		imag = j;
	}
	void set_real(float i) {
		real = i;
	}
	void set_imag(float i) {
		imag = i;
	}
	float get_real() {
		return real;
	}
	float get_imag() {
		return imag;
	}
	void set_str(string str) {
		real = atof(str.c_str());
		for (int i = 1; i < str.length(); i++) {
			if (str[i] == '+') {
				string x = str.substr(str.find("+"));
				imag = atof(x.c_str());
				break;
			}
			else if (str[i] == '-') {
				string x = str.substr(str.find("-",1));
				imag = atof(x.c_str());
				break;
			}
		}
	}
	string get_str() {
		string str;
		ostringstream ss;
		ss << real;
		if (imag >= 0)ss << "+";
		ss << imag << "i";
		str.append(ss.str());
		return str;
	}
	void reset() {
		real = 0;
		imag = 0;
	}
	void add(Complex i, Complex j) {
		real = i.real + j.real;
		imag = i.imag + j.imag;
	}
	void sub(Complex i, Complex j) {
		real = i.real - j.real;
		imag = i.imag - j.imag;
	}
	void mul(Complex i, Complex j) {
		real = (i.real * j.real) - (i.imag * j.imag);
		imag = (i.real * j.imag) + (i.imag * j.real);
	}
	void print() {
		cout << real << "+i" << imag;
	}
};
/*-----------------------------------------------FUNCTIONS DEFINITIONS-----------------------------------------------------*/

int main() {
	int arr1[100], arr2[100];
	string str1, str2;
	string str4, str5;
	int row1 = 0, column1 = 0, j1 = 0;
	int row2 = 0, column2 = 0, j2 = 0;
	Complex mtx1[100][100];
	Complex mtx2[100][100];
	int power = 0;
	float det = 0;



	/*-----------------------------------------------INPUT-----------------------------------------------------*/
	getline(cin, str1);
	for (int i = 0; i < str1.length() - 1; i++) {
		if (str1[i] == ';') {
			row1++;
			j1++;
			column1 = 0;
		}
		if (str1[i] == ' ' || str1[i] == '[' || str1[i] == ';') {
			str2 = str1.substr(i + 1, str1.find(' ', i + 1) - i | str1.find(']', i + 1) - i | str1.find(';', i + 1) - i);
			mtx1[row1][column1].set_str(str2);
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

	getline(cin, str4);

	for (int i = 0; i < str4.length() - 1; i++) {
		if (str4[i] == ';') {
			row2++;
			j2++;
			column2 = 0;
		}
		if (str4[i] == ' ' || str4[i] == '[' || str4[i] == ';') {
			str5 = str4.substr(i + 1, str4.find(' ', i + 1) - i | str4.find(']', i + 1) - i | str4.find(';', i + 1) - i);
			mtx2[row2][column2].set_str(str5);
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

	/*-------------------------------------------------------------chick-----------------------------------------------------------------*/

	if ((operat == "+" || operat == "-") && (row1 != row2 || column1 != column2)) {
		cout << "ERROR";
		return 0;
	}
	if (operat == "*" && column1 != row2) {
		cout << "ERROR";
		return 0;
	}
	/*--------------------------------------------------------OPIRATIONS LEVEL 1---------------------------------------------------------*/
	Complex ans[100][100];
	float row_ans = 0, column_ans = 0;
	Complex res1, res2;
	if (operat == "+") {
		row_ans = row1;
		column_ans = column1;
		for (int j = 0; j < row_ans; j++) {
			for (int k = 0; k < column_ans; k++)
				ans[j][k].add(mtx1[j][k], mtx2[j][k]);
		}
	}
	else if (operat == "-") {
		row_ans = row1;
		column_ans = column1;
		for (int j = 0; j < row_ans; j++) {
			for (int k = 0; k < column_ans; k++)
				ans[j][k].sub(mtx1[j][k], mtx2[j][k]);
		}
	}
	else if (operat == "*") {
		row_ans = row1;
		column_ans = column2;
		for (int k = 0; k < row_ans; k++) {
			for (int l = 0; l < column_ans; l++) {
				for (int m = 0; m < row2; m++) {
					res1.mul(mtx1[k][m], mtx2[m][l]);
					res2.add(res2, res1);
				}
				ans[k][l] = res2;
				res2.reset();
			}
		}
	}



	/*--------------------------------------------------------OUTPUT---------------------------------------------------------*/
	string str = "[", str2;
	ostringstream ss;
	for (int j = 0; j < row_ans; j++) {
		for (int k = 0; k < column_ans; k++) {
			str2 = ans[j][k].get_str();
			ss << str2;
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

	return 0;
}