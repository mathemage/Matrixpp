/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main() {
  Matrix<> md, md2;
  cout << "Soucin matic: " << endl;
  cin >> md >> md2;
  cout << "md:\n" << md << endl;
  cout << "md2:\n" << md2 << endl;
  cout << "md * md2:\n" << md * md2 << endl;

  return 0;
}
