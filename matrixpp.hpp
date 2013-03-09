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
#include<iterator>
using namespace std;

namespace mtrx {
  // =================================forward declaration=======================
  template<typename T> class Matrix;
  template<typename T> ostream & operator<<(ostream & out, const Matrix<T> & m);
  template<typename T> istream & operator>>(istream & in, Matrix<T> & m);
  // ================================/forward declaration=======================

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

  struct OutOfRangeException : public exception {
    const char * what () const throw () {
      return "Indices out of range!";
    }
  };
  // =================================vyjimky===================================

  // INTERFACE PRO T <- uzavrenost na +,-,* 
  template<typename T>
  struct Field {
    const T _zero;
    const T _one;
    T (*_minus)(const T &);                   // unarni minus
    T (*_reciprocal)(const T &);              // multiplikativni invers
    T (*_plus)(const T &, const T &);
    T (*_times)(const T &, const T &);
    bool (*_equals)(const T &, const T &);    // rovnost prvku telesa
    T _rec(const T & rhs);                    // multiplikatvni invers s kontrolou na nenulovost

    // konstruktor
    Field(T zero, T one, T (*minus)(const T &), T (*reciprocal)(const T &), T
        (*plus)(const T &, const T &), T (*times)(const T &, const T &), bool
        equals(const T &, const T &)) :
      _zero(zero), _one(one), _minus(minus), _reciprocal(reciprocal),
      _plus(plus), _times(times), _equals(equals) { }

    T subtract(const T & lhs, const T & rhs) {// binarni minus
      return _plus(lhs, _minus(rhs));
    }
  };

  // KONTEJNER MATIC
  template<typename T=double>
  class Matrix {
  private:
    unsigned _height, _width;
    T * _values;                                // 1-D vyska * sirka
  public:
    const Field<T> * _fld;                      // teleso, nad nimz se operuje

    unsigned get_width() const { return _width; }
    unsigned get_height() const { return _height; }
    // prvek s indexy (i,j), zacatek od (0,0)
    T at(unsigned i, unsigned j) const {
      try {
        if (i >= _height || j >= _width) {
          throw OutOfRangeException();
        } else {
          return _values[i*_width+j];
        }
      }
      catch (exception & e) {
        cerr << "Exception caught: \"" << e.what() << "\"" << endl;
        exit(EXIT_FAILURE);
      }
    }

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(const Field<T> & fld, unsigned h, unsigned w, T * values);
    Matrix & operator=(const Matrix & m);       // prirazeni
    Matrix(const Matrix & m) {                  // copy-constructor
      _values = 0;                              // kvuli dereferenci v delete - viz operator=
      *this = m;
    }
    ~Matrix() { if (0 != _values) delete [] _values; }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru (bidirectional)
    typedef T * iterator;
    typedef const T * const_iterator;           // ukazatel na konstantni data
    // ===========================/NORMA: iteratory===============================

    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    typedef T & reference;
    typedef const T & const_reference;
    typedef ptrdiff_t difference_type;
    typedef difference_type size_type;
    const_iterator begin() const { return _values; }
    iterator begin() { return _values; }
    iterator end() { return _values + _height * _width; }
    const_iterator end() const { return _values + _height * _width; }
    const_iterator cbegin() const { return const_cast<Matrix const &>(*this).begin(); }
    const_iterator cend() const { return const_cast<Matrix const &>(*this).end(); }
    bool operator==(const Matrix & rhs) const;
    bool operator!=(const Matrix & rhs) const { return !(*this == rhs); }
    void swap(Matrix & rhs);
    size_type size() { return end() - begin(); }
    size_type max_size() { return size(); }
    bool empty() { return begin() == end(); }
    // ===========================/NORMA: kontejnery===============================
    
    // ============================MATICOVE OPERACE===============================
    Matrix mul_by_scal(const T & scalar) const;          // nasobeni skalarem
    Matrix transpose() const;                            // transposice
    Matrix gauss_elim() const;                           // Gaussova eliminace
    Matrix gauss_jord_elim() const;                      // Gaussova-Jordanova eliminace O(n^3)
    void LUP(Matrix & L, Matrix & U, Matrix & P) const;  // LUP dekomposice
    void QR(Matrix & Q, Matrix & R) const;               // QR dekomposice
    // ===========================/MATICOVE OPERACE===============================
    
    // vypis matice
    friend ostream & operator<< <>(ostream & out, const Matrix<T> & m);
    friend istream & operator>> <>(istream & in, Matrix<T> & m);
  };
    
  // prohozeni dvou matic
  template<typename T> void swap(Matrix<T> & lhs, Matrix<T> & rhs) { lhs.swap(rhs); }
  // soucet dvou matic
  template<typename T> Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y);
  // rozdil dvou matic
  template<typename T> Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y);
  // soucin dvou matic
  // ??? kontrola rozmeru + dle formule / Strassen ???
  template<typename T> Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y);
}

#include "matrixpp.tpp"         // implementacni soubor s definicemi
#endif
