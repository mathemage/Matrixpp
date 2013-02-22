/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
/* IMPLEMENTATION FILE */
namespace mtrx {
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
      _height = m.get_height();
      _width = m.get_width();

      // puvodni data
      if (0 != _values) {
        cout << *this;
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

  /* 
  // soucet 2 matic
  template<typename T>
  Matrix<T> operator+(const Matrix<T> & x, const Matrix<T> & y) {
    try {
      se
    }
  }
  */

  template<typename T>
  Matrix<T> Matrix<T>::mul_by_scal(const T & scalar) {          // nasobeni skalarem
    Matrix<T> res(*this);
    for (iterator it = res.begin(); it != res.end(); it++) {
      *it = (*it) * scalar;
    }
    return res;
  }

  // ====================PREDDEFINOVANE OPERACE PRO TELESA=====================
  double plus_double(const double & lhs, const double & rhs) {
    return lhs + rhs;
  }

  double times_double(const double & lhs, const double & rhs) {
    return lhs * rhs;
  }

  Field<double> fld_reals(0, 1, plus_double, times_double);
  // ===================/PREDDEFINOVANE OPERACE PRO TELESA=====================
}
