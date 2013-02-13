/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#ifndef _MATRIXPP_H
#define _MATRIXPP_H 1

#include<iostream>
using namespace std;

namespace mtrx {
  // trida reprezentujici kontejner matic
  // ??? interface pro T ??? <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  template<typename T>
  class Matrix {
  private:
    T * values;             // 1-D vyska * sirka
    //bool notAMatrix;      // spatne rozmery u soucinu matic (anebo vyjimka ???)
    unsigned height, width;      // nebo pres template<> ???
    
    // ============================NORMA: kontejnery===============================
    // ===========================/NORMA: kontejnery===============================
  public:
    unsigned get_width() const {return width;}
    unsigned get_height() const {return height;}

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(unsigned h=0, unsigned w=0, T * data=0) : height(h), width(w), values(data) { } 
    Matrix & operator=(const Matrix & m) {      // prirazeni
      if (this != &m) {
        height = m.get_height();
        width = m.get_width();

        // puvodni data
        if (0 != m.values) {
          delete [] values;
        }
        values = new T [height*width];

        Matrix<T>::iterator it = this->begin();
        for (Matrix<T>::const_iterator it_m = m.begin(); it_m != m.end(); it_m++, it++) {
          *it = *it_m;
        }
      }
      return *this;
    }
    Matrix(const Matrix & x) { *this = x; }     // copy-constructor
    ~Matrix() { delete [] values; }
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
    Matrix mul_by_scal(const T & scalar);          // nasobeni skalarem
    Matrix transpose();                            // transposice
    Matrix gauss_elim();                           // Gaussova eliminace
    Matrix gauss_jord_elim();                      // Gaussova-Jordanova eliminace O(n^3)
    void LUP(Matrix & L, Matrix & U, Matrix & P);  // LUP dekomposice
    void QR(Matrix & Q, Matrix & R);                  // QR dekomposice
    // ===========================/MATICOVE OPERACE===============================
    
    // vypis matice
    friend ostream & operator<<(ostream & out, const Matrix & m) {
      for (typename Matrix<T>::const_iterator it_m = m.begin(); it_m != m.end(); it_m++) {
        out << *it_m << "\t";
      }
      return out;
    }
    
    // zadavani polozek matice zvnejsku
    friend istream & operator>>(istream & in, Matrix & m) {
      // rozmery
      // ??? vyjimka pro kontrolu ???
      in >> m.height >> m.width;

      // polozky
      if (0 != m.values) {
        delete [] m.values;
      }
      m.values = new T [m.height*m.width];
      cout << "allocated " << m.height*m.width << endl;
      for (typename Matrix<T>::iterator it_m = m.begin(); it_m != m.end(); it_m++) {
        in >> *it_m;
        cout << "wrote " << *it_m << " @ " << it_m << endl;
      }
      return in;
    }
  };

  // soucet 2 matic
  template<typename T> Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y);
  // rozdil 2 matic
  template<typename T> Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y);
  // soucin 2 matic
  // ??? kontrola rozmeru + dle formule / Strassen ???
  template<typename T> Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y);
}

#endif
