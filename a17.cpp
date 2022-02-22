/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec17. Bingo Game 2
https://www.youtube.com/watch?v=epr8XllRCkc&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=17
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

  int iBingo = 0;

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

    cout << "Bingo: " << iBingo << endl;
    if (iBingo >= 5) break;

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

    iBingo = 0;

    // horizontal, vertical
    int iStar1 = 0, iStar2 = 0;
    for (int i = 0; i < 5; i++) {
      iStar1 = iStar2 = 0;
      for (int j = 0; j < 5; j++) {
        // rows
        if (iNumber[i * 5 + j] == INT_MAX) ++iStar1;
        // columns
        if (iNumber[j * 5 + i] == INT_MAX) ++iStar2;
      }

      if (iStar1 == 5) ++iBingo;
      if (iStar2 == 5) ++iBingo;
    }

    // diagonal: Lt.Upper -> Rt.Lower
    iStar1 = 0;
    for (int i = 0; i < 25; i += 6) {
      if (iNumber[i] == INT_MAX) ++iStar1;
    }

    if (iStar1 == 5) ++iBingo;

    // diagonal: Rt.Upper -> Lt.Lower
    iStar1 = 0;
    for (int i = 4; i <= 20; i += 4) {
      if (iNumber[i] == INT_MAX) ++iStar1;
    }

    if (iStar1 == 5) ++iBingo;
  }

  return 0;
}