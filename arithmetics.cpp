/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main(int argc, const char* argv[]) {
  Matrix<int> mi;
  Matrix<double> md;
  cin >> mi >> md;
  cout << mi << md;
  cout << mi.mul_by_scal(-1) << endl << md.mul_by_scal(20) << endl;
  
  return 0;
}
