#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

namespace zich
{
    class Matrix
    {
        public:
            int rows;
            int columns;
            vector<double> matrix;
            Matrix();
            Matrix(int, int);
            Matrix(const vector<double>& matrix , int rows, int columns);
            Matrix(const Matrix&);
            ~Matrix();
            //basic plus and minus oprator and equals operator
            Matrix operator+(Matrix);
            Matrix operator+=(Matrix);
            Matrix operator+();
            

            Matrix operator-(Matrix);
            Matrix operator-=(Matrix);
            Matrix operator-();
            
      

            //basic multiplication with double (shood allow 3*mat and mat*3)
            friend Matrix operator*(double, Matrix);
            friend Matrix operator*(Matrix, double);
            Matrix operator*=(double);


            //matrix multiplication
            Matrix operator*(Matrix);
            Matrix operator*=(const Matrix&);

            //++ and -- operator
            Matrix& operator++();
            Matrix operator++(int);
            Matrix& operator--();
            Matrix operator--(int);
            //comp oprator
            friend bool operator==(const Matrix&, const Matrix&);
            friend bool operator!=(const Matrix&, const Matrix&);
            friend bool operator<(const Matrix&, const Matrix&);
            friend bool operator>(const Matrix&, const Matrix&);
            friend bool operator<=(const Matrix&, const Matrix&);
            friend bool operator>=(const Matrix&, const Matrix&);

            //input and output operator
            friend ostream& operator<<(ostream&, Matrix);
            friend istream& operator>>(istream&, Matrix&);
    };
} 
