/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec16. Bingo Game 1
https://www.youtube.com/watch?v=fG3asvf83us&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=16
******************************************************************************/

#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

int main() {
  /* Bingo */

  srand((unsigned int)time(0));
  int iNumber[25] = {};

  for (int i = 0; i < 25; i++) {
    iNumber[i] = i + 1;
  }

  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 25;
    idx2 = rand() % 25;

    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;
  }

  while (true) {
    system("clear");

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (iNumber[i * 5 + j] == INT_MAX) {
          cout << "*\t";
        } else
          cout << iNumber[i * 5 + j] << "\t";
      }
      cout << endl;
    }

    cout << "Enter a number: ";
    int iInput;
    cin >> iInput;

    if (iInput == 0)
      break;
    else if (iInput < 1 || iInput > 25)
      continue;

    // overlapping numbers
    bool bAcc = true;

    for (int i = 0; i < 25; i++) {
      if (iInput == iNumber[i]) {
        bAcc = false;

        iNumber[i] = INT_MAX;
        break;
      }
    }

    if (bAcc) continue;
  }
  return 0;
}