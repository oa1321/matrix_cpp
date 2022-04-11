#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"
using namespace std;
#include <string>
#include <array>
#include <algorithm>

#include <sstream>
#include <fstream>
bool T = true;
bool F = false;

//row and column constructor
zich::Matrix::Matrix(int row, int col)
{   //check if row and col are valid not zero and not negative
    if (row <= 0 || col <= 0)
    {
        throw invalid_argument("row and col must be positive");
    }
    rows = row;
    columns = col;
    matrix = vector<double>((unsigned long)row*(unsigned long)col, 0);
}
//vector constructor
zich::Matrix::Matrix(const vector<double>& mat, int row, int col)
{   
    //check if row and col are valid not zero and not negative
    if (row <= 0 || col <= 0)
    {
        throw invalid_argument("row and col must be positive");
    }
    //check if the size of the vector is equal to the row and col meening yoy can create a matrix
    if (mat.size() != (unsigned long)row*(unsigned long)col)
    {
        throw invalid_argument("vector size must be equal to row*col");
    }
    rows = row;
    columns = col;
    matrix = mat;
    
}
//deep copy constructor
zich::Matrix::Matrix(const Matrix& matrix_to_copy)
{
    rows = matrix_to_copy.rows;
    columns = matrix_to_copy.columns;
    matrix = vector<double>(matrix_to_copy.matrix);
}
//destructor - not realy needed but good doing it anyway
zich::Matrix::~Matrix()
{
    rows = 0;
    columns = 0;
    matrix.clear();
}
//plus and minus operator overload
//simple plus operator
zich::Matrix zich::Matrix::operator+(zich::Matrix matrix_to_add)
{
    if(rows != matrix_to_add.rows || columns != matrix_to_add.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i) + matrix_to_add.matrix.at(i);
    }
    return result;
}
//plus equals operator
zich::Matrix zich::Matrix::operator+=(zich::Matrix matrix_to_add)
{
    if(rows != matrix_to_add.rows || columns != matrix_to_add.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) += matrix_to_add.matrix.at(i);
    }
    return *this;
}

zich::Matrix zich::Matrix::operator+()
{
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i);
    }
    return result;
}
//simple minus operator
zich::Matrix zich::Matrix::operator-(zich::Matrix matrix_to_subtract)
{
    if(rows != matrix_to_subtract.rows || columns != matrix_to_subtract.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i) - matrix_to_subtract.matrix.at(i);
    }
    return result;
}
//minus equals operator
zich::Matrix zich::Matrix::operator-=(zich::Matrix matrix_to_subtract)
{
    if(rows != matrix_to_subtract.rows || columns != matrix_to_subtract.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) -= matrix_to_subtract.matrix.at(i);
    }
    return *this;
}

//unary minus operator
zich::Matrix zich::Matrix::operator-()
{
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = -matrix.at(i);
    }
    return result;
}

//mult operator overload
//multiplication with double
zich::Matrix zich::operator*(double scalar, zich::Matrix matrix_to_mult){
    zich::Matrix result(matrix_to_mult.rows, matrix_to_mult.columns);
    for(unsigned long i = 0; i < matrix_to_mult.rows*matrix_to_mult.columns; i++)
    {
        result.matrix.at(i) = scalar * matrix_to_mult.matrix.at(i);
    }
    return result;
}

zich::Matrix zich::operator*(zich::Matrix matrix_to_mult, double scalar){
    zich::Matrix result(matrix_to_mult.rows, matrix_to_mult.columns);
    for(unsigned long i = 0; i < matrix_to_mult.rows*matrix_to_mult.columns; i++)
    {
        result.matrix.at(i) = scalar * matrix_to_mult.matrix.at(i);
    }
    return result;
}

//multiplication with matrix
zich::Matrix zich::Matrix::operator*(zich::Matrix matrix_to_multiply)
{
    if(columns != matrix_to_multiply.rows)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, matrix_to_multiply.columns);
    for(unsigned long i = 0; i < rows; i++)
    {
        for(unsigned long j = 0; j < matrix_to_multiply.columns; j++)
        {
            for(unsigned long k = 0; k < columns; k++)
            {
                result.matrix.at(i*(unsigned long)matrix_to_multiply.columns + j) += matrix.at(i*(unsigned long)columns + k) * matrix_to_multiply.matrix.at(k*(unsigned long)matrix_to_multiply.columns + j);
            }
        }
    }
    return result;
}
//mult equals operator with double
zich::Matrix zich::Matrix::operator*=(double scalar)
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) *= scalar;
    }
    return *this;
}
//mult equals operator with metrix
zich::Matrix zich::Matrix::operator*=(const zich::Matrix& matrix_to_multiply){
    zich::Matrix result(rows, columns);
    result = *this * matrix_to_multiply;
    // copy result to this
    //change metrix to be result
    rows = result.rows;
    columns = result.columns;
    matrix = result.matrix;

    return *this;
}
//++ and -- operator overload
zich::Matrix& zich::Matrix::operator++()
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i)++;
    }
    return *this;
}
//decrement operator
zich::Matrix& zich::Matrix::operator--()
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i)--;
    }
    return *this;
}
zich::Matrix zich::Matrix::operator++(int)
{
    zich::Matrix result = *this;
    ++(*this);
    return result;
}

zich::Matrix zich::Matrix::operator--(int)
{
  
    zich::Matrix result = *this;
    --(*this);
    return result;
}


//comp operator overload
//equality operator

bool zich::operator==(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2)
{
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        if(matrix_1.matrix.at(i) != matrix_2.matrix.at(i))
        {
            return F;
        }
    }
    return T;
}

//inequality operator
bool zich::operator!=(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2)
{
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        if(matrix_1.matrix.at(i) != matrix_2.matrix.at(i))
        {
            return T;
        }
    }
    return F;
}
//more than operator - if the sum of all elements is greater than the other matrix
bool zich::operator>(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2)
{
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        sum_1 += matrix_1.matrix.at(i);
    }
    for(unsigned long i = 0; i < matrix_2.rows*matrix_2.columns; i++)
    {
        sum_2 += matrix_2.matrix.at(i);
    }
    if(sum_1 > sum_2)
    {
        return T;
    }
    return F;
}
//less than operator - if the sum of all elements is greater than the other matrix
bool zich::operator<(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2)
{
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        sum_1 += matrix_1.matrix.at(i);
    }
    for(unsigned long i = 0; i < matrix_2.rows*matrix_2.columns; i++)
    {
        sum_2 += matrix_2.matrix.at(i);
    }
    if(sum_1 < sum_2)
    {
        return T;
    }
    return F;
}
//more than or equal operator - using the opreator > and == from above 
bool zich::operator>=(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2){
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        sum_1 += matrix_1.matrix.at(i);
    }
    for(unsigned long i = 0; i < matrix_2.rows*matrix_2.columns; i++)
    {
        sum_2 += matrix_2.matrix.at(i);
    }
    if(sum_1 >= sum_2)
    {
        return T;
    }
    return F;
}

bool zich::operator<=(const zich::Matrix& matrix_1, const zich::Matrix& matrix_2){
    if(matrix_1.rows != matrix_2.rows || matrix_1.columns != matrix_2.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(unsigned long i = 0; i < matrix_1.rows*matrix_1.columns; i++)
    {
        sum_1 += matrix_1.matrix.at(i);
    }
    for(unsigned long i = 0; i < matrix_2.rows*matrix_2.columns; i++)
    {
        sum_2 += matrix_2.matrix.at(i);
    }
    if(sum_1 <= sum_2)
    {
        return T;
    }
    return F;
}
//output operator
ostream& zich::operator<<(ostream& out, zich::Matrix matrix_to_print)
{
    for(unsigned long i = 0; i < matrix_to_print.rows; i++)
    {
        out << "[";
        for(unsigned long j = 0; j < matrix_to_print.columns; j++)
        {
            if(j<matrix_to_print.columns-1)
            {
                out << matrix_to_print.matrix.at(i*(unsigned long)matrix_to_print.columns + j) << " ";
            }
            else
            {
                out << matrix_to_print.matrix.at(i*(unsigned long)matrix_to_print.columns + j);
            }
        }
        if (i<matrix_to_print.rows-1)
        {
            out << "]" << endl;
        }
        else
        {
            out << "]";
        }
    }
    return out;
}
void find_row_find_col(string str_mat, int& row, int& col){
    int row_num = 0;
    int col_num = 0;
    int open_bracket = 0;
    int close_bracket = 0;

    unsigned long int i = 0;
    while(i < str_mat.length()){
        if(str_mat[i] == ','){
            row_num++;
        }
        //check if after evry comma ther is a space
        if(i + 1 < str_mat.length() && str_mat[i] == ','){
            if(str_mat[i+1] != ' '){
                throw invalid_argument("Invalid matrix");
            }
        }
        i++;
    }
    row_num++;
    i = 0;
    while(i < str_mat.length()){
        if(str_mat[i] == '['){
            open_bracket++;
        }
        else if(str_mat[i] == ']'){
            break;
        }
        if (open_bracket == 1){
            if(str_mat[i] == ' '){
                col_num++;
            }
        }
        
        i++;
    }
    col_num++;
    row = row_num;
    col = col_num;

    cout << "row: " << row_num << endl;
    cout << "col: " << col_num << endl;
}
//input operator v1
istream& zich::operator>>(istream& input, zich::Matrix& matrix_to_input)
{   
    string str;
    getline(input, str);
    int row = 0;
    int col = 0;
    find_row_find_col(str, row, col);
    istringstream str_input{str};
    //temp vecttor 
    vector<double> temp_vector;
    //strip_whitespace(line);
    char dummy = ' ';
    for(unsigned long i = 0; i < row; i++)
    {
        cout << i << endl;
        str_input >> dummy;
        cout << dummy << endl;
        //check if dummy is [
        
        if(dummy != '[')
        {
            throw invalid_argument("Matrix not opend error");

        }

        for(unsigned long j = 0; j < col; j++)
        {   
            double temp = 0;
            str_input >> temp;
            temp_vector.push_back(temp);
        }
        
        str_input >> dummy;
        cout << dummy << endl;
        //check if dummy is ]
        if(dummy != ']')
        {
            throw invalid_argument("Matrix not closed properly");
        }
        if(i<matrix_to_input.rows-1)
        {
            str_input >> dummy;
            cout << dummy << endl;
            //check if dummy is , (seperator)
            if(dummy != ',')
            {
                throw invalid_argument("Matrix not spaced properly");
            }
            
            
        }
        

    }
    matrix_to_input.matrix = temp_vector;
    matrix_to_input.columns = col;
    matrix_to_input.rows = row;

    return input;
}