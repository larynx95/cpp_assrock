/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec30. Pointer Basics
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=30
******************************************************************************/

#include <string.h>
#include <time.h>

#include <iostream>

using namespace std;

int main() {
  /* pointer (64bits) */

  cout << sizeof(int *) << endl;     // 8
  cout << sizeof(char *) << endl;    // 8
  cout << sizeof(double *) << endl;  // 8

  /* address, pointer, variable

  var/ptr        address          value
  ------------------------------------------
  pNum           0xffffcc00       0xffffcc0c
  iNum           0xffffcc0c       100

  A: 0xffffcc00          A: 0xffffcc0c
  N: pNum                N: iNum
  V: 0xffffcc0c    --->  V: 100
  */

  int iNum = 100;
  int *pNum = &iNum;

  cout << "Address of iNum: " << &iNum << endl;  // 0xffffcc0c
  cout << "Value of pNum: " << pNum << endl;     // 0xffffcc0c
  cout << "Address of pNum: " << &pNum << endl;  // 0xffffcc00

  /* dereferencing */

  cout << "*pNum: " << *pNum << endl;  // 100
  *pNum = 1234;
  cout << "*pNum: " << *pNum << endl;  // 1234

  /* pointer & array */

  int iArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << "Address of array: " << iArr << endl;
  cout << "Address of array: " << &iArr[0] << endl;

  int *pArr = iArr;
  cout << pArr[2] << endl;

  /* pointer arithmetics */

  cout << pArr << endl;
  cout << pArr + 2 << endl;
  cout << *pArr << endl;
  cout << *(pArr + 2) << endl;

  return 0;
}
