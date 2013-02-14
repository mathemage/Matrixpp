/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "matrixpp.hpp"
using namespace mtrx;

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
  Matrix<T> res = *this;
  for (iterator it = res.begin(); it != res.end(); it++) {
    *it = (*it) * scalar;
  }
  return res;
}
