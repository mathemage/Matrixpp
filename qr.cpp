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
  Vect<> v;
  cin >> v;
  cout << "v:\n" << v << endl;

  SqrMtrx<> Q;
  Matrix<> R;
  v.QR(Q, R);
  cout << "Q:\n" << Q << endl;
  cout << "R:\n" << R << endl;
  cout << "Q*R:\n" << Q*R << endl;

  // rozklad pro matice obecnych dimensi
  Matrix<> A;
  cin >> A;
  A.QR(Q, R);
  cout << setprecision(20);
  cout << "Q:\n" << Q << endl;
  cout << "R:\n" << R << endl;
  cout << "A:\n" << A << endl;
  cout << "Q * R:\n" << Q * R << endl;
  cout << "===============/QR factorization==============" << endl;

  return 0;
}
