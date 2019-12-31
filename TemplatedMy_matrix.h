//
//  TemplatedMy_matrix.h
//  program1_part2
//
//  Created by Mikey Roush on 2/4/18.
//  Copyright © 2018 Michael Roush. All rights reserved.
//

#ifndef TemplatedMy_matrix_h
#define TemplatedMy_matrix_h

/* TemplatedTemplatedMy_matrix.h
 
 Header file for the class TemplatedMy_matrix
 
 Write your name and UIN here
 Mikey Roush
 825002600
 
 */

//***********************************************************
//Header
//***********************************************************

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;
// Definitions of user defined type exceptions
struct invalid_input : public exception {
    virtual const char* what() const throw()
    { return "Invalid matrix input"; }
};

struct incompatible_matrices : public exception {
    virtual const char* what() const throw()
    { return "Incompatible matrices"; }
};
template<typename T>
class TemplatedMy_matrix {
    
    //member variables
    int n, m;
    T **ptr;
    void allocate_memory();  // optional
    
public:
    //member functions
    TemplatedMy_matrix();  // default constructor
    TemplatedMy_matrix(int n1, int m1); // parameter constructor
    ~TemplatedMy_matrix(); // destructor
    TemplatedMy_matrix(const TemplatedMy_matrix& mat); // copy constructor
    TemplatedMy_matrix(TemplatedMy_matrix&& mat);  // move constructor (optional)
    TemplatedMy_matrix& operator=(const TemplatedMy_matrix& mat); //copy assignment operator
    TemplatedMy_matrix& operator=(TemplatedMy_matrix&& mat); // move assignment operator (optional)
    int number_of_rows() const;
    int number_of_columns() const;
    T* operator()(int i) const; // overloaded to access to ith row
    T& operator()(int i, int j); // overloaded to access (i,j) element
    T operator()(int i, int j) const; // overloaded to access (i,j) element
    T elem(int i, int j) const; // overloaded to access (i,j) element
    T& elem(int i, int j); // overloaded to access (i,j) element
};

// see the handout for the description of these operators
template<typename T>
ostream& operator<<(ostream& out, const TemplatedMy_matrix<T>& mat);
template<typename T>
istream& operator>>(istream& in, TemplatedMy_matrix<T>& mat);
template<typename T>
TemplatedMy_matrix<T> operator+(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2);
template<typename T>
TemplatedMy_matrix<T> operator*(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2);

#endif /* TemplatedMy_matrix_h */

//***********************************************************
//Class Definitions
//***********************************************************

template<typename T>
TemplatedMy_matrix<T>::TemplatedMy_matrix() //default constructor
{
    n = 0;
    m = 0;
    ptr = nullptr;
}
template<typename T>
void TemplatedMy_matrix<T>::allocate_memory()
{
    ptr = new T*[n];
    for (int i = 0; i < n; i++)
        ptr[i] = new T[m];
}
template<typename T>
TemplatedMy_matrix<T>::TemplatedMy_matrix(int n1, int m1) //parameter constructor
{
    n = n1;
    m = m1;
    allocate_memory();
}
template<typename T>
TemplatedMy_matrix<T>::TemplatedMy_matrix(const TemplatedMy_matrix& mat) //copy constructor
{
    n = mat.number_of_rows();
    m = mat.number_of_columns();
    allocate_memory();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            ptr[i][j] = mat.elem(i,j);
    }
}
template<typename T>
TemplatedMy_matrix<T>::TemplatedMy_matrix(TemplatedMy_matrix&& mat) // move constructor (optional)
{
    n = mat.n;
    m = mat.m;
    ptr = mat.ptr;
    mat.ptr = nullptr;
}
template<typename T>
TemplatedMy_matrix<T>::~TemplatedMy_matrix() //destructor
{
    if (ptr != nullptr){
        for (int i = 0; i < n; ++i)
            delete[] ptr[i];
    }
    delete[] ptr;
}
template<typename T>
TemplatedMy_matrix<T>& TemplatedMy_matrix<T>::operator=(const TemplatedMy_matrix& mat) //copy assignment operator
{
    if (n != mat.number_of_rows() || m != mat.number_of_columns()){
        this->~TemplatedMy_matrix();
        n = mat.number_of_rows();
        m = mat.number_of_columns();
        allocate_memory();
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            ptr[i][j] = mat.elem(i,j);
    }
    return *this;
}
template<typename T>
TemplatedMy_matrix<T>& TemplatedMy_matrix<T>::operator=(TemplatedMy_matrix&& mat) // move assignment operator (optional)
{
    swap(ptr,mat.ptr);
    swap(n, mat.n);
    swap(m, mat.m);
    return *this;
}
template<typename T>
int TemplatedMy_matrix<T>::number_of_rows() const
{
    return n;
}
template<typename T>
int TemplatedMy_matrix<T>::number_of_columns() const
{
    return m;
}
template<typename T>
T* TemplatedMy_matrix<T>::operator()(int i) const
{
    return ptr[i];
}
template<typename T>
T TemplatedMy_matrix<T>::operator()(int i, int j) const
{
    return ptr[i][j];
}
template<typename T>
T& TemplatedMy_matrix<T>::operator()(int i, int j)
{
    return ptr[i][j];
}
template<typename T>
T TemplatedMy_matrix<T>::elem(int i, int j) const
{
    if (i < 0 || i >= n) throw out_of_range("Out of range");
    if (j < 0 || j >= m) throw out_of_range("Out of range");
    return ptr[i][j];
}
template<typename T>
T& TemplatedMy_matrix<T>::elem(int i, int j)
{
    if (i < 0 || i >= n) throw out_of_range("Out of range");
    if (j < 0 || j >= m) throw out_of_range("Out of range");
    return ptr[i][j];
}
template<typename T>
ostream& operator<<(ostream& out, const TemplatedMy_matrix<T>& mat)
{
    for (int i = 0; i < mat.number_of_rows(); ++i){
        for (int j = 0; j < mat.number_of_columns(); ++j)
            out << mat.elem(i, j) << " ";
        out << endl;
    }
    out << endl;
    return out;
}
template<typename T>
istream& operator>>(istream& in, TemplatedMy_matrix<T>& mat)
{
    int n, m;
    in >> n >> m;
    
    if (n != mat.number_of_rows() || m != mat.number_of_columns()){
        TemplatedMy_matrix<T> mat2(n,m);
        mat = move(mat2);
    }
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            in >> mat.elem(i,j);
    }
    return in;
}
template<typename T>
TemplatedMy_matrix<T> operator+(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2)
{
    if (mat1.number_of_rows() != mat2.number_of_rows() || mat1.number_of_columns() != mat2.number_of_columns())
        throw out_of_range("Must be same size");
    TemplatedMy_matrix<T> newMatrix(mat1.number_of_columns(),mat1.number_of_columns());
    for (int i = 0; i < mat1.number_of_rows(); ++i){
        for (int j = 0; j < mat1.number_of_columns(); ++j)
            newMatrix(i,j) = mat1(i,j) + mat2(i,j);
    }
    return newMatrix;
}
template<typename T>
TemplatedMy_matrix<T> operator*(const TemplatedMy_matrix<T>& mat1, const TemplatedMy_matrix<T>& mat2)
{
    if (mat1.number_of_columns() != mat2.number_of_rows())
        throw out_of_range("Not compatible");
    TemplatedMy_matrix<T> newMatrix(mat1.number_of_rows(),mat2.number_of_columns());
    for (int i = 0; i < mat1.number_of_rows(); ++i){
        for (int j = 0; j < mat2.number_of_columns(); ++j){
            for (int k = 0; k < mat1.number_of_columns(); ++k)
                newMatrix(i,j) += mat1(i,k) * mat2(k,j);
        }
    }
    return newMatrix;
}

