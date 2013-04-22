/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "all.hpp"
#include<cmath>
#include<iomanip>

int main(int argc, const char* argv[]) {
  cout << "================QR factorization==============" << endl;
  Matrix<> A, R;
  SqrMtrx<> Q;
  cin >> A;
  SqrMtrx<> B = A;
  unsigned it = 1000;
  B = B.QR_algorithm(it);
  cout << "A.QR_algorithm(" << it << "):\n" << B << endl;
  cout << "===============/QR factorization==============" << endl;

  return 0;
}
