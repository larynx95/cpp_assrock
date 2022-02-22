/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec13. Lotto
https://www.youtube.com/watch?v=GsOYRfBUMtU&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=13
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

int main() {
  /* Lotto */
  system("cls");

  srand((unsigned int)time(0));

  // Numbers can be overlapped
  int iLottto[45] = {};
  for (int i = 0; i < 6; i++) {
    cout << (rand() % 45 + 1) << " ";
  }
  cout << endl;

  // Unique numbers by sfuffling
  int iLotto[45] = {};
  for (int i = 0; i < 45; i++) {
    iLotto[i] = i + 1;
  }

  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 45;
    idx2 = rand() % 45;

    iTemp = iLotto[idx1];
    iLotto[idx1] = iLotto[idx2];
    iLotto[idx2] = iTemp;
  }

  for (int i = 0; i < 6; i++) {
    cout << iLotto[i] << " ";
  }
  cout << endl;

  return 0;
}