#include <iostream>

#include "Queue.h"
using namespace std;

int main() {
  CCircleQueue<int, 10> queue;

  for (int i = 0; i < 10; ++i) {
    queue.push(i + 1);
  }

  for (int i = 0; i < 3; ++i) {
    cout << queue.pop() << " ";
  }
  cout << endl;

  for (int i = 0; i < 4; ++i) {
    queue.push(i + 1);
  }

  while (!queue.empty()) {
    cout << queue.pop() << " ";
  }
  cout << endl;

  return 0;
}