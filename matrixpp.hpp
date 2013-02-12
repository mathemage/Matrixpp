#ifndef _MATRIXPP_H
#define _MATRIXPP_H 1

namespace matrixpp {
  // trida reprezentujici kontejner matic
  // ??? interface pro T ??? <- uzavrenost na +,-,* 
  // ??? via ABC (virtual operator+,-,*) - viz http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
  template <typename T>
  class Matrix {
  private:
    T * values;             // 1-D vyska * sirka
    bool notAMatrix;        // spatne rozmery u soucinu matic (anebo vyjimka ???)
    int height, width;      // nebo pres template<> ???
    
    // ============================NORMA: kontejnery===============================
    // ===========================/NORMA: kontejnery===============================
  public:
    // ============================KANONICKA FORMA===============================
    // defaultni konstruktor - zabaleni dat do objektu tridy
    Matrix(int h=0, int w=0, T * data=0) : height(h), width(w), values(data) { }

    // prirazeni
    Matrix & operator=(const Matrix<T> & x) {
      T * current = values;
      copy
    // !!!
    }

    // copy-constructor
    Matrix(const Matrix<T> & x) {
      *this = x;
    }

    ~Matrix() {
      digits_.clear();
    }
    // ===========================/KANONICKA FORMA===============================
    
    // ============================NORMA: kontejnery===============================
    typedef T value_type;
    // ===========================/NORMA: kontejnery===============================
    
    // ============================NORMA: iteratory===============================
    // iteratory z pointeru ???
    // po radcich ??? po sloupcich ??? diagonala ???
    // reversni ???
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
