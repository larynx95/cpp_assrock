/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec32. Pointer - double
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=32
******************************************************************************/

#include <string.h>
#include <time.h>

#include <iostream>

using namespace std;

struct _tagStudent {
  int iKor;
  int iEng;
  int iMath;
  int iTotal;
  float fAvg;
};

int main() {
  /* double pointer */

  int iNumber = 1111;
  iNumber = 2222;
  int *pNum = &iNumber;

  int **ppNum = &pNum;

  *pNum = 3333;

  cout << "iNumber: " << iNumber << endl;              // 3333
  cout << "Address of iNumber: " << &iNumber << endl;  // 0xffffcc0c
  cout << "*pNum: " << *pNum << endl;                  // 3333
  cout << "pNum value: " << pNum << endl;              // 0xffffcc0c
  cout << "Address of pNum: " << &pNum << endl;        // 0xffffcc00
  cout << "&ppNum: " << &ppNum << endl;                // 0xffffcbf8
  cout << "ppNum: " << ppNum << endl;                  // 0xffffcc00
  cout << "*ppNum: " << *ppNum << endl;                // 0xffffcc0c
  cout << "**ppNum: " << **ppNum << endl;              // 3333

  /*
  N: name, V: value, A: ddress
  A: (1)       (2)       (3)
  N: ppNum     pNum      iNumber
  V: (2)       (3)       3333
  */

  return 0;
}
