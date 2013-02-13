/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "matrixpp.hpp"
using namespace mtrx;

// prirazeni
template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> const & m) {
  if (this == &m) {
    return *this;
  }

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

  return *this;
}

// vypis matice
template<typename T>
ostream & operator<<(ostream & out, const Matrix<T> & m) {
  for (typename Matrix<T>::const_iterator it_m = m.begin(); it_m != m.end(); it_m++) {
    out << *it_m << "\t";
  }
  return out;
}

// zadavani polozek matice zvnejsku
template<typename T>
istream & operator>>(istream & in, Matrix<T> & m) {
  // rozmery
  unsigned h, w;
  in >> h >> w;

  // polozky
  Matrix<T> tmp_m(h, w);
  for (typename Matrix<T>::iterator it_m = tmp_m.begin(); it_m != tmp_m.end(); it_m++) {
    in >> *it_m;
  }
  m = tmp_m;
  return in;
}
