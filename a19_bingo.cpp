/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec19. Bingo Game 4
https://www.youtube.com/watch?v=3kH8y7gp0Kg&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=19
******************************************************************************/

#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

enum AI_MODE { AM_EASY = 1, AM_HARD };

enum LINE_NUMBER {
  LN_H1,
  LN_H2,
  LN_H3,
  LN_H4,
  LN_H5,
  LN_V1,
  LN_V2,
  LN_V3,
  LN_V4,
  LN_V5,
  LN_LT,
  LN_RT,
};

int main() {
  /* Bingo */

  srand((unsigned int)time(0));
  int iNumber[25] = {};
  int iAINumber[25] = {};

  for (int i = 0; i < 25; i++) {
    iNumber[i] = i + 1;
    iAINumber[i] = i + 1;
  }

  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 25;
    idx2 = rand() % 25;
    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;

    idx1 = rand() % 25;
    idx2 = rand() % 25;
    iTemp = iAINumber[idx1];
    iAINumber[idx1] = iAINumber[idx2];
    iAINumber[idx2] = iTemp;
  }

  int iBingo = 0, iAIBingo = 0;
  int iAIMode;

  // set AI difficulty
  while (true) {
    cout << "1. Easy" << endl;
    cout << "2. Hard" << endl;
    cout << "Select AI mode: ";
    cin >> iAIMode;

    if (iAIMode > AM_EASY || iAIMode <= AM_HARD) {
      break;
    }
  }

  // AI_EASY mode
  // Collect unselected numbers and randomly select one of them.
  int iNonSelect[25] = {};
  int iNonSelectCont = 0;

  while (true) {
    system("clear");

    // print Player's Bingo table
    cout << "~~~~~~~~ Player ~~~~~~~" << endl;

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (iNumber[i * 5 + j] == INT_MAX) {
          cout << "*\t";
        } else
          cout << iNumber[i * 5 + j] << "\t";
      }
      cout << endl;
    }
    cout << "Player's Bingo: " << iBingo << endl;

    // print AI Player's Bingo table
    cout << "~~~~~~~~ AI Player ~~~~~~~" << endl;

    switch (iAIMode) {
      case AM_EASY:
        cout << "AIMode: EASY" << endl;
        break;
      case AM_HARD:
        cout << "AIMode: Hard" << endl;
        break;
    }

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (iAINumber[i * 5 + j] == INT_MAX) {
          cout << "*\t";
        } else
          cout << iAINumber[i * 5 + j] << "\t";
      }
      cout << endl;
    }
    cout << "AI Player's Bingo: " << iAIBingo << endl;

    // conditions for winning this game
    if (iBingo >= 5) {
      cout << "Player wins!" << endl;
      break;
    } else if (iAIBingo >= 5) {
      cout << "AI Player wins!" << endl;
      break;
    }

    // user input & validation
    cout << "Enter a number: ";
    int iInput;
    cin >> iInput;

    if (iInput == 0)
      break;
    else if (iInput < 1 || iInput > 25)
      continue;

    // overlapping numbers
    bool bAcc = true;  // if the same numbers are entered

    for (int i = 0; i < 25; i++) {
      if (iInput == iNumber[i]) {
        bAcc = false;

        iNumber[i] = INT_MAX;
        break;
      }
    }
    if (bAcc) continue;

    for (int i = 0; i < 25; i++) {
      if (iInput == iAINumber[i]) {
        iAINumber[i] = INT_MAX;
        break;
      }
    }

    // AI's turn!
    switch (iAIMode) {
      case AM_EASY:
        iNonSelectCont = 0;
        for (int i = 0; i < 25; i++) {
          if (iAINumber[i] != INT_MAX) {
            iNonSelect[iNonSelectCont] = iAINumber[i];
            iNonSelectCont++;
          }
        }
        iInput = iNonSelect[rand() % iNonSelectCont];
        break;
      case AM_HARD:
        // Select the line with highest probability
        // to complete all five stars.
        int iLine = 0;
        int iStarCount = 0;
        int iSaveCount = 0;

        // find a line with most stars in rows
        for (int i = 0; i < 5; ++i) {
          for (int j = 0; j < 5; ++j) {
            if (iAINumber[i * 5 + j] == INT_MAX) {
              ++iStarCount;
            }
          }

          if (iStarCount < 5 && iSaveCount < iStarCount) {
            iLine = i;
            iSaveCount = iStarCount;
          }
        }

        // find a line with most stars in columns and rows
        // comparing the line we've already found in above for-loop
        for (int i = 0; i < 5; i++) {
          iStarCount = 0;
          for (int j = 0; j < 5; j++) {
            if (iAINumber[j * 5 + i] == INT_MAX) {
              ++iStarCount;
            }
          }

          if (iStarCount < 5 && iSaveCount < iStarCount) {
            iLine = i + 5;
            iSaveCount = iStarCount;
          }
        }

        // find a line with most stars in diagonal (Lt.Upper -> Rt.Lower)
        iStarCount = 0;
        for (int i = 0; i < 25; i += 6) {
          if (iAINumber[i] == INT_MAX) ++iStarCount;
        }

        if (iStarCount < 5 && iSaveCount < iStarCount) {
          iLine = LN_LT;
          iSaveCount = iStarCount;
        }

        // find a line with most stars in diagonal (Rt.Upper -> Lt.Lower)
        iStarCount = 0;
        for (int i = 4; i <= 20; i += 4) {
          if (iAINumber[i] == INT_MAX) ++iStarCount;
        }

        if (iStarCount < 5 && iSaveCount < iStarCount) {
          iLine = LN_RT;
          iSaveCount = iStarCount;
        }

        //
        if (iLine <= LN_H5) {
          for (int i = 0; i < 5; ++i) {
            if (iAINumber[iLine * 5 + i] != INT_MAX) {
              iInput = iAINumber[iLine * 5 + i];
              break;
            }
          }
        } else if (iLine <= LN_V5) {
          for (int i = 0; i < 5; i++) {
            if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX) {
              iInput = iAINumber[i * 5 + (iLine - 5)];
              break;
            }
          }
        } else if (iLine == LN_LT) {
          for (int i = 0; i < 25; i += 6) {
            if (iAINumber[i] != INT_MAX) {
              iInput = iAINumber[i];
              break;
            }
          }
        } else if (iLine == LN_RT) {
          for (int i = 4; i <= 20; i += 4) {
            if (iAINumber[i] != INT_MAX) {
              iInput = iAINumber[i];
              break;
            }
          }
        }

        break;
    }

    for (int i = 0; i < 25; i++) {
      if (iNumber[i] == iInput) {
        iNumber[i] = INT_MAX;
        break;
      }
    }

    for (int i = 0; i < 25; i++) {
      if (iAINumber[i] == iInput) {
        iAINumber[i] = INT_MAX;
        break;
      }
    }

    // bingo calculation
    iBingo = 0;
    iAIBingo = 0;

    // horizontal, vertical
    int iStar1 = 0, iStar2 = 0;
    int iAIStar1 = 0, iAIStar2 = 0;

    for (int i = 0; i < 5; i++) {
      iStar1 = iStar2 = 0;
      iAIStar1 = iAIStar2 = 0;
      for (int j = 0; j < 5; j++) {
        // rows
        if (iNumber[i * 5 + j] == INT_MAX) ++iStar1;
        // columns
        if (iNumber[j * 5 + i] == INT_MAX) ++iStar2;
      }

      for (int j = 0; j < 5; j++) {
        // rows
        if (iAINumber[i * 5 + j] == INT_MAX) ++iAIStar1;
        // columns
        if (iAINumber[j * 5 + i] == INT_MAX) ++iAIStar2;
      }

      if (iStar1 == 5) ++iBingo;
      if (iStar2 == 5) ++iBingo;
      if (iAIStar1 == 5) ++iAIBingo;
      if (iAIStar2 == 5) ++iAIBingo;
    }

    // diagonal: Lt.Upper -> Rt.Lower
    iStar1 = 0;
    iAIStar1 = 0;
    for (int i = 0; i < 25; i += 6) {
      if (iNumber[i] == INT_MAX) ++iStar1;
    }

    for (int i = 0; i < 25; i += 6) {
      if (iAINumber[i] == INT_MAX) ++iAIStar1;
    }

    if (iStar1 == 5) ++iBingo;
    if (iAIStar1 == 5) ++iAIBingo;

    // diagonal: Rt.Upper -> Lt.Lower
    iStar1 = 0;
    iAIStar1 = 0;
    for (int i = 4; i <= 20; i += 4) {
      if (iNumber[i] == INT_MAX) ++iStar1;
      if (iAINumber[i] == INT_MAX) ++iAIStar1;
    }

    if (iStar1 == 5) ++iBingo;
    if (iAIStar1 == 5) ++iAIBingo;
  }

  return 0;
}