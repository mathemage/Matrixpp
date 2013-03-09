/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
/* IMPLEMENTATION FILE */
namespace mtrx {
  template<typename T>
  T Field<T>::_rec(const T & rhs) {             // s kontrolou na nenulovost
    try {
      if (_zero == rhs) {
        throw InverseOfNullException();
      } else {
        return _reciprocal(rhs);
      }
    }
    catch (exception & e) {
      cerr << "Exception caught: \"" << e.what() << "\"" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // ==========================PREDDEFINOVANA TELESA===========================
  // TELESO REALNYCH CISEL
  double minus_double(const double & rhs) { return - rhs; }
  double reciprocal_double(const double & rhs) { return 1 / rhs; }
  double plus_double(const double & lhs, const double & rhs) { return lhs + rhs; }
  double times_double(const double & lhs, const double & rhs) { return lhs * rhs; }
  bool equals_double(const double & lhs, const double & rhs) { return lhs == rhs; }
  Field<double> fld_reals(0, 1, minus_double, reciprocal_double,  plus_double,
      times_double, equals_double);

  // PRVOTELESO
  // vysledek modula mezi hodnotami prvotelesa
  int mod(const int & value, int modulo) { return (value % modulo + modulo) % modulo; }
  template<int Order> int minus_pf(const int & rhs) { return mod(-rhs, Order); }

  template<int Order>
  int reciprocal_pf(const int & rhs) {     // rozsireny Eukliduv algoritmus s Bezoutovy koeficienty
    int divisor = mod(rhs, Order);
    if (0 == divisor) {
      throw InverseOfNullException();
    }
    int dividend = Order;
    int remainder;
    int bezout1 = 0; int bezout2 = 1;      // predposledni a posledni Bezoutuv koeficient

    while (divisor > 1) {
      bezout1 = bezout1 - (dividend / divisor) * bezout2;
      swap(bezout1, bezout2);
      remainder = dividend % divisor;
      dividend = divisor;
      divisor = remainder;
    }
    return mod(bezout2, Order);
  }

  template<int Order>
  int plus_pf(const int & lhs, const int & rhs) {
    return mod(mod(lhs,Order)+mod(rhs,Order), Order);
  }

  template<int Order>
  int times_pf(const int & lhs, const int & rhs) {
    return mod(mod(lhs,Order)*mod(rhs,Order), Order);
  }

  template<int Order>
  bool equals_pf(const int & lhs, const int & rhs) {
    return (lhs - rhs) % Order == 0;
  }

  // teleso zbytkovych trid radu "_order_"
  const int _order_ = 5;
  Field<int> pf(0, 1, minus_pf<_order_>, reciprocal_pf<_order_>, plus_pf<_order_>, times_pf<_order_>, equals_pf<_order_>);
  // =========================/PREDDEFINOVANA TELESA===========================

  // defaultni konstruktor "Matrix" - zabaleni dat do objektu tridy
  template<typename T>
  Matrix<T>::Matrix(const Field<T> & fld=fld_reals, unsigned h=0, unsigned w=0, T * data=0) :
    _fld(&fld), _height(h), _width(w), _values(data) { } 

  // rovnost matic
  template<typename T>
  bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
    if (_height == rhs.get_height() && _width == rhs.get_width() && _fld == rhs._fld) {
      typename Matrix<T>::const_iterator it_r = rhs.cbegin();
      for (typename Matrix<T>::const_iterator it_m = cbegin(); it_m != cend(); it_m++, it_r++) {
        if (!_fld->_equals(*it_r, *it_m)) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

  // vypis matice
  template<typename T>
  ostream & operator<<(ostream & out, const Matrix<T> & m) {
    int i = 0;                                   // pocitadlo pro odradkovani
    for (typename Matrix<T>::const_iterator it_m = m.begin(); it_m != m.end(); it_m++) {
      out << *it_m;
      // tabelator / novy radek
      if (0 == ++i % m.get_width() && i != m.get_width() * m.get_height()) {
        out << endl;
      } else {
        out << "\t";
      }
    }
    return out;
  }
  
  // zadavani polozek matice zvnejsku
  template<typename T>
  istream & operator>>(istream & in, Matrix<T> & m) {
    // rozmery
    // ??? vyjimka pro kontrolu ???
    in >> m._height >> m._width;

    // polozky
    if (0 != m._values) {
      delete [] m._values;
    }
    m._values = new T [m._height*m._width];
    for (typename Matrix<T>::iterator it_m = m.begin(); it_m != m.end(); it_m++) {
      in >> *it_m;
    }
    return in;
  }

  template<typename T>
  Matrix<T> & Matrix<T>::operator=(const Matrix<T> & m) {      // prirazeni
    if (this != &m) {
      _fld = m._fld;
      _height = m.get_height();
      _width = m.get_width();

      // puvodni data
      if (0 != _values) {
        delete [] _values;
      }
      _values = new T [_height*_width];

      iterator it = this->begin();
      for (const_iterator it_m = m.begin(); it_m != m.end(); it_m++, it++) {
        *it = *it_m;
      }
    }
    return *this;
  }

  template<typename T>
  Matrix<T> Matrix<T>::mul_by_scal(const T & scalar) const {          // nasobeni skalarem
    Matrix<T> res(*this);
    for (iterator it = res.begin(); it != res.end(); it++) {
      *it = _fld->_times(*it, scalar);
    }
    return res;
  }

  template<typename T>
  Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y) {
    try {
      if (x.get_height() != y.get_height() || x.get_width() != y.get_width()) {
        throw MismatchedDimException();
      } else if (x._fld != y._fld) {
        throw MismatchedFieldException();
      }

      Matrix<T> res(x);
      typename Matrix<T>::const_iterator ity = y.cbegin();
      for (typename Matrix<T>::iterator itx = res.begin(); itx != res.end(); itx++, ity++) {
        *itx = res._fld->_plus(*itx, *ity);
      }
      return res;
    }
    catch (exception & e) {
      cerr << "Exception caught: \"" << e.what() << "\"" << endl;
      exit(EXIT_FAILURE);
    }
  }

  template<typename T>
  Matrix<T> operator-(const Matrix<T> & x, const Matrix<T> & y) {
    const T minus_one = y._fld->_minus(y._fld->_one);
    return x + y.mul_by_scal(minus_one);
  }

  template<typename T>
  Matrix<T> operator*(const Matrix<T> & x, const Matrix<T> & y) {
    int x_h = x.get_height();
    int y_w = y.get_width();
    try {
      if (y.get_height() != x.get_width()) {
        throw MismatchedDimException();
      } else if (x._fld != y._fld) {
        throw MismatchedFieldException();
      }

      T * data = new T [x_h*y_w];
      Matrix<T> res(*x._fld, x_h, y_w, data);
      /*
      typename Matrix<T>::const_iterator ity = y.cbegin();
      for (typename Matrix<T>::iterator itx = res.begin(); itx != res.end(); itx++, ity++) {
        *itx = res._fld->_plus(*itx, *ity);
      }  */
      return res;
    }
    catch (exception & e) {
      cerr << "Exception caught: \"" << e.what() << "\"" << endl;
      exit(EXIT_FAILURE);
    }
  }
}
