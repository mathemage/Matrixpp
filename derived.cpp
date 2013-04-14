/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"

int main() {
  cout << "========================================\nTrida Vect" << endl;
  Vect<> v1;
  cin >> v1;
  Vect<> v2(v1), v3;
  v3 = v2;
  cout << "v1:\n" << v1 << "\n\nv2:\n" << v2 << endl << endl;
  cout << "v3:\n" << v3 << endl;
  cout << "v1 " << ((v1==v3) ? "=" : "!") << "= v3" << endl;

  cout << "========================================\nTrida SqrMtrx" << endl;
  SqrMtrx<> sq1;
  cin >> sq1;
  SqrMtrx<> sq2(sq1), sq3;
  sq3 = sq2;
  cout << "sq1:\n" << sq1 << "\n\nsq2:\n" << sq2 << endl << endl;
  cout << "sq3:\n" << sq3 << endl;
  cout << "sq1 " << ((sq1==sq3) ? "=" : "!") << "= sq3" << endl;

  cout << endl;

  Matrix<> md1;
  cin >> md1;
  cout << "md1:\n" << md1 << endl;
  sq3 = md1;
  cout << "new sq3:\n" << sq3 << endl;
  cout << "sq3 " << ((sq3==md1) ? "=" : "!") << "= md1" << endl;

  return 0;
}
