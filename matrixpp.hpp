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
#include<exception>
#include<cstdlib>
using namespace std;

namespace mtrx {
  template<typename T> class Matrix;
  template<typename T> ostream & operator<<(ostream & out, const Matrix<T> & m);
  template<typename T> istream & operator>>(istream & in, Matrix<T> & m);

  // =================================vyjimky===================================
  struct InverseOfNullException : public exception {
    const char * what () const throw () {
      return "Inversion of null element!";
    }
  };

  struct MismatchedDimException : public exception {
    const char * what () const throw () {
      return "Mismatched dimensions!";
    }
  };

  struct MismatchedFieldException : public exception {
    const char * what () const throw () {
      return "Mismatched fields of matrices!";
    }
  };
  // =================================vyjimky===================================

  // interface pro T <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  template<typename T>
  struct Field {
    const T _zero;
    const T _one;
    T (*_minus)(const T &);                   // unarni minus
    T (*_reciprocal)(const T &);              // multiplikativni invers
    T (*_plus)(const T &, const T &);
    T (*_times)(const T &, const T &);
    T _rec(const T & rhs);                    // multiplikatvni invers

    Field(T zero, T one, T (*minus)(const T &), T (*reciprocal)(const T &), T
        (*plus)(const T &, const T &), T (*times)(const T &, const T &)) :
      _zero(zero), _one(one), _minus(minus), _reciprocal(reciprocal),
      _plus(plus), _times(times) { }

    T subtract(const T & lhs, const T & rhs) {// binarni minus
      return _plus(lhs, _minus(rhs));
    }
  };

  // trida reprezentujici kontejner matic
  //template<typename T=double, Field<T>=fld_reals>
  template<typename T=double>
  class Matrix {
  private:
    unsigned _height, _width;
    T * _values;                                // 1-D vyska * sirka
  public:
    const Field<T> * _fld;                      // teleso, nad nimz se operuje

    unsigned get_width() const {return _width;}
    unsigned get_height() const {return _height;}

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(const Field<T> & fld, unsigned h, unsigned w, T * data);
    Matrix & operator=(const Matrix & m);       // prirazeni
    Matrix(const Matrix & m) {                  // copy-constructor
      _values = 0;                              // kvuli dereferenci v delete - viz operator=
      *this = m;
    }
    ~Matrix() { if (0 != _values) delete [] _values; }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru
    typedef T * iterator;
    typedef const T * const_iterator;           // ukazatel na konstantni data
    // ===========================/NORMA: iteratory===============================

    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    iterator begin() { return _values; }
    const_iterator begin() const { return _values; }
    iterator end() { return _values + _height * _width; }
    const_iterator end() const { return _values + _height * _width; }
    const_iterator cbegin() const { return _values; }
    const_iterator cend() const { return _values + _height * _width; }
    // ===========================/NORMA: kontejnery===============================
    
    // ============================MATICOVE OPERACE===============================
    Matrix mul_by_scal(const T & scalar);       // nasobeni skalarem
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
