/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main(int argc, const char* argv[]) {
  //Matrix<> md;
  //Matrix<> md2(md);
  //Matrix<> md2(fld_reals2);
  //md2 = md;

  Vect<> u, v;
  cin >> v;
  cout << "v:\n" << v << endl;
  cout << "outer_product:\n" << v.outer_product() << endl;
  cout << "inner_product:\n" << v.inner_product() << endl;
  cout << "norm_squared:\n" << v.norm_squared() << endl;
  cout << "unit_matrix:\n" << unit_matrix(6, fld_reals) << endl;

  cin >> u;
  cout << "u:\n" << u << endl;
  u = u.mul_by_scal(v.norm_squared() / u.norm_squared());
  cout << "u':\n" << u << endl;
  Vect<> diff = u-v;
  SqrMtrx<> haus = diff.Householder();
  cout << "haus:\n" << haus << endl;
  cout << "haus * u:\n" << haus * u << endl;
  cout << "v:\n" << v << endl;

  return 0;
}
