# Matrix-operations
C++ program to do Matrix operations
The program use a defined string format to represent the matrix in the user input and output sections.
the string representation of the Matrix is :
[10 2.13 3;-5 0 4;16.5 1 8]

General Constraints:
1- User can input matrices of any size up to 100 x 100.
2- All values are of float data types.
3- Any error in user input, the program will output the word “ERROR” in uppercase letters and exits. List of Errors includes the following:
  a. Any missing or unexpected input in the entered string matrix.
  b. Invalid corresponding matrices size in +, -, * , / operators.
  c. Non square matrix in Inverse and Power operators.
  d. Non integer positive power in power operator.

Example (Add Operator)
input
[1 -2.5 3;4 5.25 6;7 8 9.12]
+
[3 4.2 10.2;12 -1 0;67 2 13]
output
[4 1.7 13.2;16 4.25 6;74 10 22.12]
