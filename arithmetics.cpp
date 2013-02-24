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
  Matrix<> md;
  cin >> mi >> md;
  cout << "Vstupni matice: " << endl;
  cout << mi << endl << endl << md << endl << endl;

  cout << "Skalarni nasobek: " << endl;
  cout << mi.mul_by_scal(-1) << endl << endl << md.mul_by_scal(20) << endl << endl;

  cout << "Field of reals: " << endl;
  double pi = 3.14;
  double e = 2.71;
  cout << fld_reals._zero << endl;
  cout << fld_reals._one << endl;
  cout << fld_reals._plus(e, pi) << endl;
  cout << fld_reals._times(e, pi) << endl;
  cout << fld_reals._minus(e) << endl;
  cout << fld_reals._minus(pi) << endl;
  cout << fld_reals.subtract(e, pi) << endl;
  cout << fld_reals._rec(pi) << endl;
  //cout << fld_reals.reciprocal(0) << endl;
  cout << "Prime field of order " << _order_ << ": " << endl;
  cout << pf._minus(-79) << endl;
  cout << pf._plus(-79, 132) << endl;
  cout << pf._times(-78, 134) << endl;
  cout << pf._rec(29) << endl;
  
  return 0;
}
