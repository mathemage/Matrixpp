#include "main.hpp"
#include "matrixpp.hpp"

int main(int argc, const char* argv[]) {
  vector<string> args(argv, argv+argc);
  
  cout << "Matrix++ run with arguments: ";
  for (int i = 0; i < args.size(); i++) {
    cout << args[i] << endl;
  }
  
  return 0;
}
