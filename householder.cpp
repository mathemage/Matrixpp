/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"
#include<iomanip>

int main() {
  cout << std::setprecision(8);

  cout << "================Vect features=================" << endl;
  Vect<> u, v;
  cin >> v;
  cout << "v:\n" << v << endl;
  cout << "outer_product:\n" << v.outer_product() << endl;
  cout << "inner_product:\n" << v.inner_product() << endl;
  cout << "unit_matrix:\n" << unit_matrix(6, fld_reals) << endl;
  cout << "===============/Vect features=================" << endl;

  cout << endl;

  cout << "================Haus features=================" << endl;
  cin >> u;
  cout << "u:\n" << u << endl;
  u = u.mul_by_scal(sqrt(v.norm_squared()) / sqrt(u.norm_squared()));
  cout << "u':\n" << u << endl;
  Vect<> diff = u-v;
  SqrMtrx<> haus = diff.Householder();
  cout << "haus:\n" << haus << endl;
  cout << "haus * u:\n" << haus * u << endl;
  cout << "v:\n" << v << endl;
  cout << "===============/Haus features=================" << endl;

  cout << endl;

  cout << "================Haus_can features=============" << endl;
  cout << "sqrt(v.norm_squared):\n" << sqrt(v.norm_squared()) << endl;
  cout << "v.Householder_canon():\n" << v.Householder_canon() << endl;
  cout << "v.Householder_canon() * v:\n" << v.Householder_canon() * v << endl;

  Vect<> canonic = v.e1_reflection();        // "norma"-nasobek vektoru e_1
  cout << "canonic:\n" << canonic << endl;
  cout << "canonic.Householder_canon():\n" << canonic.Householder_canon() << endl;
  cout << "===============/Haus_can features=============" << endl;

  return 0;
}
