#include <iostream>

using namespace std;

int main() {
  std::locale::global(std::locale(""));
  string a("Вико - ползучее Ыыко!");
  cout << a << endl;
}
