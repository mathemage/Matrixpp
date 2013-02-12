/******************************************************************************
      Copyright (C) 2013 Karel Ha <mathemage@gmail.com>

 Distributed under the terms of the GNU General Public License (GPL)
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
                 http://www.gnu.org/licenses/
******************************************************************************/
#include "main.hpp"
#include "matrixpp.hpp"

using namespace mtrx;

int main(int argc, const char* argv[]) {
  vector<string> args(argv, argv+argc);
  
  cout << "Matrix++ run with arguments: ";
  for (int i = 0; i < args.size(); i++) {
    cout << args[i] << endl;
  }
  
  return 0;
}
