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

  Vect<> v;
  cin >> v;
  cout << "v:\n" << v << endl;
  cout << "outer_product:\n" << v.outer_product() << endl;
  cout << "inner_product:\n" << v.inner_product() << endl;
  cout << "norm_squared:\n" << v.norm_squared() << endl;

  return 0;
}
