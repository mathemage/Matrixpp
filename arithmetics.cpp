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

  cout << "Soucet matic: " << endl;
  Matrix<int> mi2(pf);
  cin >> mi2;
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

  /*
  cout << "Soucin matic: " << endl;
  cin >> md >> md2;
  cout << "md * md2:\n" << md * md2 << endl;
  */

  cout << "mi:\n" << mi << endl;
  cin >> mi2;
  cout << "shift:\n" << mi2 << endl;
  mi2 = mi + mi2;
  cout << "mi2:\n" << mi2 << endl;
  cout << "Rovnost matic: " << endl;
  cout << ((md == md2) ? "md == md2" : "md != md2") << endl;
  cout << ((mi == mi2) ? "mi == mi2" : "mi != mi2") << endl;
  
  return 0;
}
