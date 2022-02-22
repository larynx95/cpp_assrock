#include < iostream>

#include "Stack.h"
#include "Vector.h"

using namespace std;

int main() {
  /* vector */
  CVector<int> vecInt;

  vecInt.reserve(100);

  for (int i = 0; i < 10; ++i) {
    vecInt.push_back(i + 1);
  }

  for (int i = 0; i < vecInt.size(); ++i) {
    cout << vecInt[i] << " ";
  }
  cout << endl;

  /* stack */

  CStack<int> stackInt;

  for (int i = 0; i < 10; i++) {
    stackInt.push(i + 1);
  }

  while (!stackInt.empty()) {
    cout << stackInt.pop() << " ";
  }

  return 0;
}