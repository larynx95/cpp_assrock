/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec15. Puzzle
https://www.youtube.com/watch?v=umpMT1xql0I&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=15
******************************************************************************/

#include <time.h>
#include <windows.h>

#include <climits>
#include <iostream>
using namespace std;

int main() {
  /* Puzzle */

  srand((unsigned int)time(0));

  int iNumber[25] = {};

  for (int i = 0; i < 24; i++) {
    iNumber[i] = i + 1;
  }

  iNumber[24] = INT_MAX;  // the last element
  int iStarIndex = 24;

  // shuffling
  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 24;
    idx2 = rand() % 24;

    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;
  }

  while (true) {
    system("clear");

    // print 5 * 5 table
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (iNumber[i * 5 + j] == INT_MAX)
          cout << "*";
        else
          cout << iNumber[i * 5 + j] << "\t";
      }
      cout << endl;
    }

    // Conditions for ending game
    bool bWin = true;

    for (int i = 0; i < 24; i++) {
      if (iNumber[i] != i + 1) {
        bWin = false;
        break;
      }
      if (bWin == true) {
        cout << "You completed Puzzle!" << endl;
        break;
      }
    }

    cout << "w: up, s: down, a: left, d: right, q: end" << endl;
    cout << "Enter a character: ";
    // getch : takes one character
    // return the character and terminate without Enter
    char cInput = getchar();
    cout << endl;

    if (cInput == 'q' || cInput == 'Q') break;

    switch (cInput) {
      case 'w':
      case 'W':
        if (iStarIndex > 4) {
          iNumber[iStarIndex] = iNumber[iStarIndex - 5];
          iNumber[iStarIndex - 5] = INT_MAX;
          iStarIndex -= 5;
        }
        break;
      case 's':
      case 'S':
        if (iStarIndex < 20) {
          iNumber[iStarIndex] = iNumber[iStarIndex + 5];
          iNumber[iStarIndex + 5] = INT_MAX;
          iStarIndex += 5;
        }
        break;
      case 'a':
      case 'A':
        if (iStarIndex % 5 != 0) {
          iNumber[iStarIndex] = iNumber[iStarIndex - 1];
          iNumber[iStarIndex - 1] = INT_MAX;
          --iStarIndex;
        }
        break;
      case 'd':
      case 'D':
        if (iStarIndex % 5 != 4) {
          iNumber[iStarIndex] = iNumber[iStarIndex + 1];
          iNumber[iStarIndex + 1] = INT_MAX;
          ++iStarIndex;
        }
        break;
    }
  }

  cout << "Game End" << endl;

  return 0;
}