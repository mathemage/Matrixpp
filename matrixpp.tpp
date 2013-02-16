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
    in >> m.height >> m.width;

    // polozky
    if (0 != m.values) {
      delete [] m.values;
    }
    m.values = new T [m.height*m.width];
    for (typename Matrix<T>::iterator it_m = m.begin(); it_m != m.end(); it_m++) {
      in >> *it_m;
    }
    return in;
  }

  template<typename T>
  Matrix<T> & Matrix<T>::operator=(const Matrix<T> & m) {      // prirazeni
    if (this != &m) {
      height = m.get_height();
      width = m.get_width();

      // puvodni data
      if (0 != values) {
        cout << *this;
        delete [] values;
      }
      values = new T [height*width];

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
}
