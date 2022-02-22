/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec34. Bingo Game Again
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=34
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

void SetNumber(int *pArray);
void Shuffle(int *pArray);
AI_MODE SelectAIMode();
void OutputNumber(int *pArray, int iBingo);
bool ChangeNumber(int *pArray, int iInput);
int SelectAINumber(int *pArray, AI_MODE eMode);
int BingoCounting(int *pArray);
int BingoCountingH(int *pArray);
int BingoCountingV(int *pArray);
int BingoCountingLTD(int *pArray);
int BingoCountingRTD(int *pArray);

int main() {
  srand((unsigned int)time(0));
  int iNumber[25] = {};
  int iAINumber[25] = {};

  SetNumber(iNumber);
  SetNumber(iAINumber);

  Shuffle(iNumber);
  Shuffle(iAINumber);

  int iBingo = 0, iAIBingo = 0;
  AI_MODE eAIMode = SelectAIMode();

  while (true) {
    system("clear");

    // print Player's Bingo table
    cout << "~~~~~~~~ Player ~~~~~~~" << endl;
    OutputNumber(iNumber, iBingo);

    // print AI Player's Bingo table
    cout << "~~~~~~~~ AI Player ~~~~~~~" << endl;

    switch (eAIMode) {
      case AM_EASY:
        cout << "AIMode: EASY" << endl;
        break;
      case AM_HARD:
        cout << "AIMode: Hard" << endl;
        break;
    }

    OutputNumber(iAINumber, iAIBingo);

    // conditions for winning this game
    if (iBingo >= 5) {
      cout << "Player wins!" << endl;
      break;
    } else if (iAIBingo >= 5) {
      cout << "AI Player wins!" << endl;
      break;
    }

    // user input & validation
    cout << "Enter a number: (0: quit) ";
    int iInput;
    cin >> iInput;

    if (iInput == 0)
      break;
    else if (iInput < 1 || iInput > 25)
      continue;

    // check whether the number is already used
    bool bAcc = ChangeNumber(iNumber, iInput);
    if (bAcc) continue;

    ChangeNumber(iAINumber, iInput);

    iInput = SelectAINumber(iAINumber, eAIMode);

    ChangeNumber(iNumber, iInput);
    ChangeNumber(iAINumber, iInput);

    // bingo calculation
    iBingo = BingoCounting(iNumber);
    iAIBingo = BingoCounting(iAINumber);
  }
  return 0;
}

void SetNumber(int *pArray) {
  for (int i = 0; i < 25; i++) {
    pArray[i] = i + 1;
  }
}

void Shuffle(int *pArray) {
  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 25;
    idx2 = rand() % 25;
    iTemp = pArray[idx1];
    pArray[idx1] = pArray[idx2];
    pArray[idx2] = iTemp;
  }
}

AI_MODE SelectAIMode() {
  int eAIMode;
  while (true) {
    cout << "1. Easy" << endl;
    cout << "2. Hard" << endl;
    cout << "Select AI mode: ";
    cin >> eAIMode;

    if (eAIMode > AM_EASY || eAIMode <= AM_HARD) {
      break;
    }
  }

  return (AI_MODE)eAIMode;
}

void OutputNumber(int *pArray, int iBingo) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (pArray[i * 5 + j] == INT_MAX) {
        cout << "*\t";
      } else
        cout << pArray[i * 5 + j] << "\t";
    }
    cout << endl;
  }
  cout << "Player's Bingo: " << iBingo << endl;
}

bool ChangeNumber(int *pArray, int iInput) {
  for (int i = 0; i < 25; i++) {
    if (iInput == pArray[i]) {
      pArray[i] = INT_MAX;
      return false;
    }
  }
  return true;
}

int SelectAINumber(int *pArray, AI_MODE eMode) {
  int iNonSelectCount;
  int iNonSelect[25] = {};

  switch (eMode) {
    case AM_EASY:
      iNonSelectCount = 0;
      for (int i = 0; i < 25; i++) {
        if (pArray[i] != INT_MAX) {
          iNonSelect[iNonSelectCount] = pArray[i];
          iNonSelectCount++;
        }
      }
      return iNonSelect[rand() % iNonSelectCount];
    case AM_HARD:
      // Select the line with highest probability
      // to complete all five stars.
      int iLine = 0;
      int iStarCount = 0;
      int iSaveCount = 0;

      // find a line with most stars in rows
      for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
          if (pArray[i * 5 + j] == INT_MAX) {
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
          if (pArray[j * 5 + i] == INT_MAX) {
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
        if (pArray[i] == INT_MAX) ++iStarCount;
      }

      if (iStarCount < 5 && iSaveCount < iStarCount) {
        iLine = LN_LT;
        iSaveCount = iStarCount;
      }

      // find a line with most stars in diagonal (Rt.Upper -> Lt.Lower)
      iStarCount = 0;
      for (int i = 4; i <= 20; i += 4) {
        if (pArray[i] == INT_MAX) ++iStarCount;
      }

      if (iStarCount < 5 && iSaveCount < iStarCount) {
        iLine = LN_RT;
        iSaveCount = iStarCount;
      }

      //
      if (iLine <= LN_H5) {
        for (int i = 0; i < 5; ++i) {
          if (pArray[iLine * 5 + i] != INT_MAX) {
            return pArray[iLine * 5 + i];
          }
        }
      } else if (iLine <= LN_V5) {
        for (int i = 0; i < 5; i++) {
          if (pArray[i * 5 + (iLine - 5)] != INT_MAX) {
            return pArray[i * 5 + (iLine - 5)];
          }
        }
      } else if (iLine == LN_LT) {
        for (int i = 0; i < 25; i += 6) {
          if (pArray[i] != INT_MAX) {
            return pArray[i];
          }
        }
      } else if (iLine == LN_RT) {
        for (int i = 4; i <= 20; i += 4) {
          if (pArray[i] != INT_MAX) {
            return pArray[i];
          }
        }
      }
      break;
  }
  return -1;
}

int BingoCounting(int *pArray) {
  int iBingo = 0;
  iBingo += BingoCountingH(pArray) + BingoCountingV(pArray) +
            BingoCountingLTD(pArray) + BingoCountingRTD(pArray);
  return iBingo;
}

int BingoCountingH(int *pArray) {
  int iStar1 = 0, iBingo = 0;

  for (int i = 0; i < 5; i++) {
    iStar1 = 0;
    for (int j = 0; j < 5; j++) {
      if (pArray[i * 5 + j] == INT_MAX) ++iStar1;
    }
    if (iStar1 == 5) ++iBingo;
  }
  return iBingo;
}

int BingoCountingV(int *pArray) {
  int iStar1 = 0, iBingo = 0;

  for (int i = 0; i < 5; i++) {
    iStar1 = 0;
    for (int j = 0; j < 5; j++) {
      if (pArray[j * 5 + i] == INT_MAX) ++iStar1;
    }
    if (iStar1 == 5) ++iBingo;
  }
  return iBingo;
}

int BingoCountingLTD(int *pArray) {
  int iStar1 = 0, iBingo = 0;
  for (int i = 0; i < 25; i += 6) {
    if (pArray[i] == INT_MAX) ++iStar1;
  }
  if (iStar1 == 5) ++iBingo;
  return iBingo;
}

int BingoCountingRTD(int *pArray) {
  int iStar1 = 0, iBingo = 0;
  for (int i = 4; i < 21; i += 4) {
    if (pArray[i] == INT_MAX) ++iStar1;
  }
  if (iStar1 == 5) ++iBingo;
  return iBingo;
}
