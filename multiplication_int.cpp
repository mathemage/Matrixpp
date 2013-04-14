/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main() {
  Matrix<int> mi(pf), mi2(pf);
  cout << "Soucin matic: " << endl;
  cin >> mi >> mi2;
  cout << "mi:\n" << mi << endl;
  cout << "mi2:\n" << mi2 << endl;
  cout << "mi * mi2:\n" << mi * mi2 << endl;

  return 0;
}
