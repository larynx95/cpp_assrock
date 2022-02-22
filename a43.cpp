/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec43. Dynamic Allocation
https://www.youtube.com/watch?v=iwKSTUfs1gw&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=43
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

int main() {
  /* new, malloc */

  int* pNumber = new int;  // allocate
  *pNumber = 100;          // access memory space
  delete pNumber;          // deallocate

  int* pArray = new int[100];
  pArray[1] = 300;
  delete[] pArray;

  return 0;
}