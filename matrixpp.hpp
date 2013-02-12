/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#ifndef _MATRIXPP_H
#define _MATRIXPP_H 1

namespace mtrx {
  // trida reprezentujici kontejner matic
  // ??? interface pro T ??? <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  template <typename T>
  class Matrix {
  private:
    T ** values;            // 1-D vyska * sirka
    //bool notAMatrix;      // spatne rozmery u soucinu matic (anebo vyjimka ???)
    int height, width;      // nebo pres template<> ???
    
    // ============================NORMA: kontejnery===============================
    // ===========================/NORMA: kontejnery===============================
  public:
    int get_width() {return width;}
    int get_height() {return height;}

    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(int h=0, int w=0, T ** data=0) : height(h), width(w), values(data) { }

    // prirazeni
    Matrix & operator=(const Matrix<T> & m) : height(m.get_height()), width(m.get_width()) {
      values = new T [height*width];
      it = this->begin();
      for (Matrix::iterator it_m = m.begin(); current != m.end(); it_m++, it++) {
    // !!! - dereference pointeru pro kopirovani dat
        it = it_m;
      }
    }

    // copy-constructor
    Matrix(const Matrix<T> & x) {
      *this = x;
    }

    ~Matrix() {
      delete [] values;
    }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    // ===========================/NORMA: kontejnery===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru ???
    // po radcich ??? po sloupcich ??? diagonala ???
    // reversni ???
    typedef T * iterator;
    typedef const T * const_iterator;
    // ===========================/NORMA: iteratory===============================

    // ============================MATICOVE OPERACE===============================
    Matrix<T> mul_by_scal(const T & scalar);          // nasobeni skalarem
    Matrix<T> transpose();                            // transposice
    Matrix<T> gauss_elim();                           // Gaussova eliminace
    Matrix<T> gauss_jord_elim();                      // Gaussova-Jordanova eliminace O(n^3)
    void LUP(Matrix<T> L, Matrix<T> U, Matrix<T> P);  // LUP dekomposice
    // ===========================/MATICOVE OPERACE===============================
  };

  // trida representujici kontejner ctvercovych matic
  // dedicnost???
  template <typename T>
  class SqrMatrixpp : public Matrixpp {
  public:
    // ============================KANONICKA FORMA===============================
    // konstruktor
    LNum(int size=32) : size_(size) {
      digits_.resize(size, 0);
    }

    // prirazeni
    LNum & operator=(const LNum & x) {
      size_ = x.get_size();
      digits_.resize(size_, 0);
      for (int i = 0; i < size_ && i < x.get_size(); i++) {
        digits_[i] = x[i];
      }
    }

    // copy-constructor
    LNum(const LNum & x) {
      *this = x;
    }

    ~LNum() {
      digits_.clear();
    }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================MATICOVE OPERACE===============================
    T det();                             // determinant <- via GE nebo LUP rozklad
    // ============================MATICOVE OPERACE===============================
  }

  // trida representujici kontejner regularnich/invertibilnich matic
  template <typename T>
  class InvMatrixpp : public SqrMatrixpp {
  public:
    // ============================KANONICKA FORMA===============================
    // konstruktor
    LNum(int size=32) : size_(size) {
      digits_.resize(size, 0);
    }

    // prirazeni
    LNum & operator=(const LNum & x) {
      size_ = x.get_size();
      digits_.resize(size_, 0);
      for (int i = 0; i < size_ && i < x.get_size(); i++) {
        digits_[i] = x[i];
      }
    }

    // copy-constructor
    LNum(const LNum & x) {
      *this = x;
    }

    ~LNum() {
      digits_.clear();
    }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================MATICOVE OPERACE===============================
    Matrix<T> inverse();                          // inverse <- via GE nebo LUP rozklad
    // ============================MATICOVE OPERACE===============================
  }

  // vypis matice cisla
  template <typename T>
  friend std::ostream & operator<<(std::ostream & out, const Matrixpp<T> & num);

  // soucet 2 matic
  template <typename T>
  Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y);

  // rozdil 2 matic
  template <typename T>
  Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y);

  // soucin 2 matic
  // ??? kontrola dimensi + dle formule / Strassen ???
  template <typename T>
  Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y);
}

#endif
