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
#include<cmath>
using namespace std;

namespace mtrx {
  // =================================forward declaration=======================
  template<typename T> class Matrix;
  template<typename T> class SqrMtrx;
  template<typename T> class Vect;
  template<typename T> ostream & operator<<(ostream & out, const Matrix<T> & m);
  template<typename T> istream & operator>>(istream & in, Matrix<T> & m);
  // ================================/forward declaration=======================

  // =================================vyjimky===================================
  void display_exception(exception & e) {
    cerr << "An exception has occured: \"" << e.what() << "\"" << endl;
    exit(EXIT_FAILURE);
  }

  struct InverseOfNullException : public exception {
    const char * what () const throw () {
      return "Field inversion of null element!";
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

  struct NotAVectorException : public MismatchedDimException {
    const char * what () const throw () {
      std::string msg(MismatchedDimException::what());
      msg.append(" Not a vector!");
      return msg.c_str();
    }
  };

  struct NotASqrMtrxException : public MismatchedDimException {
    const char * what () const throw () {
      std::string msg(MismatchedDimException::what());
      msg.append(" Not a square matrix!");
      return msg.c_str();
    }
  };
  // =================================vyjimky===================================

  // =================================interface===================================
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
    T _rec(const T & rhs) const;              // multiplikatvni invers s kontrolou na nenulovost

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
  // ================================/interface===================================

  // =================================tridy matic=================================
  // KONTEJNER MATIC
  template<typename T=double>
  class Matrix {
  protected:
    unsigned _height, _width;
    T * _values;                                // 1-D vyska * sirka
  public:
    const Field<T> * const _fld;                // teleso, nad nimz se operuje (const nezmenitelne)

    unsigned get_height() const { return _height; }
    unsigned get_width() const { return _width; }
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
        display_exception(e);
      }
    }
    virtual bool is_valid() {                   // viz operator>>
      if (_height * _width == size()) {
        return true;
      } else {
        throw MismatchedDimException();
      }
    }

    // ============================KANONICKA ČÁST===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(const Field<T> & fld, unsigned h, unsigned w, T * values);
    Matrix & operator=(const Matrix & m);       // prirazeni
    Matrix(const Matrix & m) : _fld(m._fld) {   // copy-constructor
      _values = 0;                              // kvuli dereferenci v delete - viz operator=
      *this = m;
    }
    ~Matrix() { if (0 != _values) delete [] _values; }
    // ===========================/KANONICKA ČÁST===============================
    
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
    iterator begin() { return _values; }
    const_iterator begin() const { return _values; }
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
    Matrix mul_by_scal(const T & scalar) const;                             // nasobeni skalarem
    Matrix transpose() const;                                               // transposice
    Matrix subblock(unsigned u, unsigned l, unsigned d, unsigned r) const;  // souvisla podmatice
    Vect<T> column(unsigned j) const {                                      // j-ty sloupec
      Vect<T> col = subblock(0, j, _height-1, j);
      return col;
    }
    Matrix round_to_zeroes() const;                                         // zaokrouhleni cisel blizkych nule
    void LUP(Matrix & L, Matrix & U, Matrix & P) const;                     // LUP dekomposice - [TO BE IMPLEMENTED]
    void QR(SqrMtrx<T> & Q, Matrix & R) const;                              // QR dekomposice
    // ===========================/MATICOVE OPERACE===============================
    
    // vypis matice
    friend ostream & operator<< <>(ostream & out, const Matrix<T> & m);
    friend istream & operator>> <>(istream & in, Matrix<T> & m);
  };
    
  // prohozeni dvou matic -- zapis "swap(a, b)" namisto "a.swap(b)" pro moznou konversi
  template<typename T> void swap(Matrix<T> & lhs, Matrix<T> & rhs) { lhs.swap(rhs); }
  // soucet dvou matic
  template<typename T> Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y);
  // rozdil dvou matic
  template<typename T> Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y);
  // soucin dvou matic
  template<typename T> Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y);

  // VEKTOR Z MATICE
  template<typename T=double>
  class Vect : public Matrix<T> {
  private:
    // non-dependent names -> dependent names
    using Matrix<T>::_height;
    using Matrix<T>::_width;
    using Matrix<T>::_values;
  public:
    using Matrix<T>::_fld;
    using Matrix<T>::begin;
    using Matrix<T>::transpose;
    bool is_valid() {                           // viz operator>>
      if (1 == _width) {
        return true;
      } else {
        throw NotAVectorException();
      }
    }

    // ============================KANONICKA ČÁST===============================
    // defaultni konstruktor - implicitni sirka 1
    Vect(const Field<T> & fld, unsigned h, T * values);
    Vect & operator=(const Vect & v);           // prirazeni
    Vect(const Vect & v) : Matrix<T>(v) { }     // copy-constructor
    // ===========================/KANONICKA ČÁST===============================
    
    operator Matrix<T>() {                      // conversion operator
      Matrix<T> m(_fld, _height, 1, _values);
      return m;
    }

    Vect(const Matrix<T> & m);                  // conversion constructor
    
    // ============================PRO QR-ROZKLAD================================
    SqrMtrx<T> outer_product() {
      return *this * this->transpose();
    }
    SqrMtrx<T> inner_product() {
      return this->transpose() * *this;
    }
    T norm_squared() {
      return this->inner_product().at(0, 0);
    }
    Vect e1_reflection();                       // "norma" nasobek vektoru e_1
    SqrMtrx<T> Householder();                   // matice Housholderovy reflexe
    SqrMtrx<T> Householder_canon();             // Housholderova reflexe do nasobku vektoru e_1
    // ===========================/PRO QR-ROZKLAD================================
  };

  // CTVERCOVE MATICE
  template<typename T=double>
  class SqrMtrx : public Matrix<T> {
  private:
    // non-dependent names -> dependent names
    using Matrix<T>::_height;
    using Matrix<T>::_width;
    using Matrix<T>::_values;
  public:
    using Matrix<T>::_fld;
    virtual bool is_valid() {                   // viz operator>>
      if (_height == _width) {
        return true;
      } else {
        throw NotASqrMtrxException();
      }
    }

    // ============================KANONICKA ČÁST===============================
    // defaultni konstruktor - implicitne stejne rozmery
    SqrMtrx(const Field<T> & fld, unsigned dim, T * values);
    SqrMtrx & operator=(const SqrMtrx & r);           // prirazeni
    SqrMtrx(const SqrMtrx & v) : Matrix<T>(v) { }     // copy-constructor
    // ===========================/KANONICKA ČÁST===============================
    
    operator Matrix<T>() {                         // conversion operator
      Matrix<T> m(_fld, _height, _height, _values);
      return m;
    }
    SqrMtrx(const Matrix<T> & m);                  // conversion constructor
    SqrMtrx QR_algorithm(unsigned iterations_count); // QR algoritmus pro zadany pocet iteraci
  };

  // ================================/tridy matic=================================

  const double epsilon = 0.00009;               // hranice pro zaokrouhleni na nulu
}

#include "matrixpp.tpp"         // implementacni soubor s definicemi
#endif
