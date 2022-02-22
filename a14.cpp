/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec13. Baseball Game
https://www.youtube.com/watch?v=cZVwzDcE8zY&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=14
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

int main() {
  /* Baseball Game 1 */

  srand((unsigned int)time(0));

  int iNumber[9] = {};

  for (int i = 0; i < 9; i++) {
    iNumber[i] = i + 1;
  }

  int iTemp, idx1, idx2;
  for (int i = 0; i < 100; i++) {
    idx1 = rand() % 9;
    idx2 = rand() % 9;

    iTemp = iNumber[idx1];
    iNumber[idx1] = iNumber[idx2];
    iNumber[idx2] = iTemp;
  }

  cout << iNumber[0] << "\t" << iNumber[1] << "\t" << iNumber[2] << endl;

  int iStrike = 0, iBall = 0;
  int iInput[3];

  while (true) {
    cout << "Enter thre numbers bw 1 ~ 9: ";
    cin >> iInput[0] >> iInput[1] >> iInput[2];

    if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0) {
      break;
    } else if (iInput[0] < 0 || iInput[0] > 9 || iInput[1] < 0 ||
               iInput[1] > 9 || iInput[2] < 0 || iInput[2] > 9) {
      cout << "Wrong number!" << endl;
      continue;
    } else if (iInput[0] == iInput[1] || iInput[0] == iInput[2] ||
               iInput[1] == iInput[2]) {
      cout << "Numbers you've entered are overlapped!" << endl;
      continue;
    }

    iStrike = iBall = 0;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (iNumber[i] == iInput[j]) {
          if (i == j)
            ++iStrike;
          else
            ++iBall;
          break;
        }
      }
    }

    if (iStrike == 3) {
      cout << "Correct numbers." << endl;
      break;
    } else if (iStrike == 0 && iBall == 0)
      cout << "Out" << endl;
    else
      cout << iStrike << " strike " << iBall << " ball" << endl;
  }

  /* Baseball Game 2 */

  /*
  int Player1, Player2, Player3;
  int Computer1, Computer2, Computer3;
  int count = 1;
  int strike = 0;
  int ball = 0;

  srand((unsigned int)time(0));
  Computer1 = rand() % 9 + 1;
  Computer2 = rand() % 9 + 1;
  Computer3 = rand() % 9 + 1;

  cout << "Let's start baseball game!" << endl;

  while (true) {
    cout << "Enter a number bw 1 ~ 9: ";
    cin >> Player1;
    cin >> Player2;
    cin >> Player3;

    if (Computer1 == Player1)
      strike++;
    else if (Computer1 == Player2)
      ball++;
    else if (Computer1 == Player3)
      ball++;

    if (Computer2 == Player2)
      strike++;
    else if (Computer2 == Player3)
      ball++;
    else if (Computer2 == Player3)
      ball++;

    if (Computer3 == Player3)
      strike++;
    else if (Computer3 == Player2)
      ball++;
    else if (Computer3 == Player1)
      ball++;

    cout << "Strikes: " << strike << endl;
    cout << "Balls: " << strike << endl;

    if (strike == 3) break;
    count++;
  }
  */

  return 0;
}