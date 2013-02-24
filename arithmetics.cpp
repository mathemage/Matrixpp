/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main(int argc, const char* argv[]) {
  Matrix<int> mi(pf);
  Matrix<> md;
  cin >> mi >> md;
  cout << "Vstupni matice: " << endl;
  cout << mi << endl << endl << md << endl << endl;

  cout << "Skalarni nasobek: " << endl;
  cout << mi.mul_by_scal(-1) << endl << endl << md.mul_by_scal(20) << endl << endl;
  
  return 0;
}
