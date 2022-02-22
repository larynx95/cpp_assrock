/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec12. Do-while, Arrays
https://www.youtube.com/watch?v=8xePxXJeP6g&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=12
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

int main() {
  /* do-while */

  int iNumber = 0;

  do {
    cout << iNumber << endl;
  } while (iNumber > 0);

  /* Arrays */

  int iArray[3];

  for (int i = 0; i < 3; i++) {
    iArray[i] = i;
  }

  /* 2D-Arrays */

  int iArray2[3][3];

  return 0;
}