/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main() {
  Matrix<int> mi(pf);
  Matrix<> md;
  cout << "md is " << (md.empty() ? "empty" : "non-void") << endl;
  cin >> mi >> md;
  cout << "md is " << (md.empty() ? "empty" : "non-void") << endl;
  cout << "mi:\n" << mi << "\nmd:\n" << md << endl;

  cout << "Skalarni nasobek: " << endl;
  cout << mi.mul_by_scal(-1) << endl << endl << md.mul_by_scal(20) << endl;

  cout << "Soucet matic: " << endl;
  Matrix<int> mi2(pf);
  cin >> mi2;
  cout << "mi:\n" << mi << endl;
  cout << "mi2:\n" << mi2 << endl;
  swap(mi2, mi);
  cout << "mi:\n" << mi << endl;
  cout << "mi2:\n" << mi2 << endl;
  cout << "mi + mi2:\n" << mi + mi2 << endl;
  cout << "mi - mi2:\n" << mi - mi2 << endl;

  cout << endl;

  Matrix<> md2;
  cin >> md2;
  cout << "md:\n" << md << endl;
  cout << "md2:\n" << md2 << endl;
  cout << "md + md2:\n" << md + md2 << endl;
  cout << "md - md2:\n" << md - md2 << endl;

  cout << "Podmatice: " << endl;
  cout << "md.subblock(1, 1, 2, 3):\n" << md.subblock(1, 1, 2, 3) << endl;
  cout << "md.subblock(2, 1, 4, 4):\n" << md.subblock(2, 1, 4, 4) << endl;
  
  for (int i = 0; i < md.get_width(); i++) {
    cout << i << ". column:\n" << md.column(i) << endl << endl;
  }

  cout << "Rovnost matic: " << endl;
  cin >> mi2;
  cout << ((md != md2) ? "md != md2" : "md == md2") << endl;
  cout << ((mi == mi2) ? "mi == mi2" : "mi != mi2") << endl;

  cout << "Velikost matic: " << endl;
  cout << "mi: " << mi.size() << endl;
  cout << "md: " << md.max_size() << endl;

  cout << "Iteratory matic: " << endl;
  int m = 3;
  Matrix<int>::const_iterator iti = mi.begin();
  cout << "mi:\n" << mi << endl;
  cout << "mi[" << m << "]: " << iti[m] << endl;
  cout << "mi[" << m-3 << "]: " << iti[m-3] << endl;
  cout << "mi[" << m << "] >= mi[" << m-3 << "] is " << (iti[m] >= iti[m-3] ? "true" : "false") << endl;

  cout << "Transposice: " << endl;
  cout << "mi2:\n" << mi2 << endl;
  cout << "mi2^T:\n" << mi2.transpose() << endl;
  
  return 0;
}
