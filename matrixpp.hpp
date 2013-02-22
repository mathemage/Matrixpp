/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
/* HEADER FILE */
#ifndef _MATRIXPP_H
#define _MATRIXPP_H 1

#include<iostream>
using namespace std;

namespace mtrx {
  template<typename T> class Matrix;
  template<typename T> ostream & operator<<(ostream & out, const Matrix<T> & m);
  template<typename T> istream & operator>>(istream & in, Matrix<T> & m);

  // interface pro T <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  // T musi podporovat operace:
  // unarni operator-
  // multiplikativni invers
  template<typename T>
  struct Field {
    const T _zero;
    const T _one;
    T (*_plus)(const T & lhs, const T & rhs);
    T (*_times)(const T & lhs, const T & rhs);
    /*
    T _minus(const T & lhs, const T & rhs) {
      return _plus(lhs, _times(_minus_one, rhs));
    }  */

    Field(T zero, T one, T (*plus)(const T &, const T &), T
        (*times)(const T &, const T &)) :
      _zero(zero), _one(one), _plus(plus), _times(times) { }
  };

  // trida reprezentujici kontejner matic
  //template<typename T=double, Field<T>=fld_reals>
  template<typename T=double>
  class Matrix {
  private:
    T * _values;                                // 1-D vyska * sirka
    unsigned _height, _width;                   // nebo pres template<> ???
  public:
    unsigned get_width() const {return _width;}
    unsigned get_height() const {return _height;}

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(unsigned h=0, unsigned w=0, T * data=0) : _height(h), _width(w), _values(data) { } 
    Matrix & operator=(const Matrix & m);       // prirazeni
    Matrix(const Matrix & x) {                  // copy-constructor
      _values = 0;                              // kvuli dereferenci v delete - viz operator=
      *this = x;
    }
    ~Matrix() { if (0 != _values) delete [] _values; }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru
    typedef T * iterator;
    typedef const T * const_iterator;     // ukazatel na konstantni data
    // ===========================/NORMA: iteratory===============================

    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    iterator begin() { return _values; }
    const_iterator begin() const { return _values; }
    iterator end() { return _values + _height * _width; }
    const_iterator end() const { return _values + _height * _width; }
    // ===========================/NORMA: kontejnery===============================
    
    // ============================MATICOVE OPERACE===============================
    Matrix<T> mul_by_scal(const T & scalar);       // nasobeni skalarem
    Matrix transpose();                            // transposice
    Matrix gauss_elim();                           // Gaussova eliminace
    Matrix gauss_jord_elim();                      // Gaussova-Jordanova eliminace O(n^3)
    void LUP(Matrix & L, Matrix & U, Matrix & P);  // LUP dekomposice
    void QR(Matrix & Q, Matrix & R);               // QR dekomposice
    // ===========================/MATICOVE OPERACE===============================
    
    // vypis matice
    friend ostream & operator<< <>(ostream & out, const Matrix<T> & m);
    friend istream & operator>> <>(istream & in, Matrix<T> & m);
  };
    
  // soucet 2 matic
  template<typename T> Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y);
  // rozdil 2 matic
  template<typename T> Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y);
  // soucin 2 matic
  // ??? kontrola rozmeru + dle formule / Strassen ???
  template<typename T> Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y);
}

#include "matrixpp.tpp"         // implementacni soubor s definicemi
#endif
