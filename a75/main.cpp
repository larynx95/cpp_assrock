#include < iostream>

#include "Vector.h"

using namespace std;

int main() {
  CVector<int> vecInt;

  vecInt.reserve(100);

  for (int i = 0; i < 10; ++i) {
    vecInt.push_back(i + 1);
  }

  for (int i = 0; i < vecInt.size(); ++i) {
    cout << vecInt[i] << " ";
  }
  return 0;
}