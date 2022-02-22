/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec11. print stars (for loop)
https://www.youtube.com/watch?v=7ZaxEB3A2kg&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=11
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

int main() {
  /* for loop */

  // pyramid
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < i + 1; j++) {
      cout << "*";
    }
    cout << endl;
  }

  // pyramid, upside down
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5 - i; j++) {
      cout << "*";
    }
    cout << endl;
  }

  // pyramid, aligned midline
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3 - i; ++j) {
      cout << " ";
    }

    for (int j = 0; j < i * 2 + 1; ++j) {
      cout << "*";
    }

    cout << endl;
  }

  return 0;
}