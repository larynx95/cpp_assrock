/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec56. Reference
https://www.youtube.com/watch?v=rUVllGnQ2MY&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=56
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

int main() {
  /* reference */

  int iNumA = 100;
  int &iRefNum = iNumA;

  cout << iRefNum << endl;  // 100
  cout << iNumA << endl;    // 100
  iRefNum = 1234;
  cout << iRefNum << endl;  // 1234
  cout << iNumA << endl;    // 1234

  int iNumB = 9999;
  iRefNum = iNumB;
  cout << iNumA << endl;    // 9999
  cout << iNumB << endl;    // 9999
  cout << iRefNum << endl;  // 9999

  return 0;
}