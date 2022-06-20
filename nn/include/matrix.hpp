//
// Created by anmc on 22-6-16.
//

#ifndef NN_MATRIX_HPP
#define NN_MATRIX_HPP

#include <iostream>

#include "error.hpp"

template<class T>
class matrix {
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const matrix<U>& m);
public:

    explicit matrix(int rows = 0, int columns = 0);

    matrix(const matrix<T>&);

    ~matrix() { delete [] element; }

    int rows() const { return _rows; }

    int cols() const { return _columns; }

    T& operator() (int i, int j) const;

    matrix<T>& operator=(const matrix<T>&);

    matrix<T> operator+() const;

    matrix<T> operator+(const matrix<T>&) const;

    matrix<T> operator-() const;

    matrix<T> operator-(const matrix<T>&) const;

    matrix<T> operator*(const matrix<T>&) const;

    matrix<T> operator+=(const T&);

private:

    T *element;

    int _rows, _columns;

};

template<class T>
matrix<T>::matrix(int rows, int columns) {

    if (rows < 0 || columns < 0)

        throw std::exception();//("Rows and columns must be >= 0");

    if ((rows == 0 || columns == 0) && (rows != 0 || columns != 0))

        throw std::exception();//std::string("Either both or neither rows and columns should be zero");

    _rows = rows;
    _columns = columns;

    element = new T [_rows * _columns];

}

template<class T>
matrix<T>::matrix(const matrix<T> &m) {

    _rows = m.rows();
    _columns = m.cols();

    element = new T [_rows * _columns];

    std::copy(m.element, m.element + _rows * _columns, element);

}

template<class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &m) {

    if (this != m) {

        delete [] element;

        _rows = m.rows();
        _columns = m.cols();

        element = new T [_rows * _columns];

        std::copy(m.element, m.element + _rows * _columns, element);
    }

    return *this;
}

template<class T>
T &matrix<T>::operator()(int i, int j) const {

    if ( i < 1 || i > _rows || j < 1 || j > _columns)
        throw std::exception();//std::string("Matrix Index Out Of Bounds");

    return element[(i - 1) * _columns + j - 1];
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &m) const {

    if (_rows != m._rows || _columns != m._columns)
        throw std::exception();//std::string("Matrix Size Mismatch");

    matrix<T> w(_rows, _columns);
    for (int i = 0; i < _rows * _columns; i++)
        w.element[i] = element[i] + m.element[i];

    return w;

}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &m) const {

    if (_rows != m._rows || _columns != m._columns)
        throw std::exception();//std::string("Matrix Size Mismatch");

    matrix<T> w(_rows, _columns);
    for (int i = 0; i < _rows * _columns; i++)
        w.element[i] = element[i] - m.element[i];

    return w;

}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T> &m) const {

    if (_columns != m._rows)
        throw std::exception();//std::string("Matrix Size Mismatch");

    matrix<T> w(_rows, m._columns);

    int ct = 0, cm = 0, cw = 0;

    for (int i = 1; i <= _rows; i ++) {

        for (int j = 1; j < m._columns; j ++) {

            T sum = element[ct] * m.element[cm];

            for (int k = 2; k <= _columns; k ++) {

                ct ++;

                cm += m._columns;

                sum += element[cw ++] * m.element[cm];

            }

            w.element[cw++] = sum;

            ct -= _columns - 1;
            cm = j;

        }

        ct += _columns;
        cm = 0;

    }

    return w;

}

template<class T>
matrix<T> matrix<T>::operator+=(const T &m) {

    return this + m;

}

template<class T>
std::ostream &operator<<(std::ostream& out, const matrix<T>& m) {

    out << m._rows << " x " << m._columns;

    out << std::endl;

    for (int i = 1; i <= m._rows; i ++) {

        for (int j = 1; j <= m._columns; j ++) {

            out << m(i, j) << " ";

        }

        out << std::endl;

    }

    out << std::endl;

    return out;
}


#endif //NN_MATRIX_HPP
