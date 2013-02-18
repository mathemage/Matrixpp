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

  // T musi podporovat operace:
  // operator+
  // operator-
  // unarni operator-
  // multiplikativni invers
  template<typename T>
  class Field {
  private:
    T _minus_one;
  public:
  }

  // trida reprezentujici kontejner matic
  // ??? interface pro T ??? <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  template<typename T, Field<T>>
  class Matrix {
  private:
    T * values;             // 1-D vyska * sirka
    //bool notAMatrix;      // spatne rozmery u soucinu matic (anebo vyjimka ???)
    unsigned height, width;      // nebo pres template<> ???
  public:
    unsigned get_width() const {return width;}
    unsigned get_height() const {return height;}

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(unsigned h=0, unsigned w=0, T * data=0) : height(h), width(w), values(data) { } 
    Matrix & operator=(const Matrix & m);       // prirazeni
    Matrix(const Matrix & x) {                  // copy-constructor
      values = 0;                               // kvuli dereferenci v delete - viz operator=
      *this = x;
    }
    ~Matrix() { if (0 != values) delete [] values; }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru
    typedef T * iterator;
    typedef const T * const_iterator;     // ukazatel na konstantni data
    // ===========================/NORMA: iteratory===============================

    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    iterator begin() { return values; }
    const_iterator begin() const { return values; }
    iterator end() { return values + height * width; }
    const_iterator end() const { return values + height * width; }
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
