/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec10. for loop, nested for loop
https://www.youtube.com/watch?v=eZ74aRsbolw&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=10
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

int main() {
  /* for loop */

  for (int i = 0; i < 10; i++) {
    cout << i << " ";
  }
  cout << "" << endl;

  // multiplication table
  for (int i = 2; i < 10; i++) {
    cout << "2 * " << i << " = " << 2 * i << endl;
  }

  // print even numbers between 1 ~ 100
  for (int i = 2; i <= 101; i += 2) {
    cout << i << " ";
  }
  cout << "" << endl;

  // common divisiors of 3 and 7
  for (int i = 0; i <= 100; i++) {
    if (i % 3 == 0 && i % 7 == 0) {
      cout << i << " ";
    }
  }
  cout << "" << endl;

  return 0;
}