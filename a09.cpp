/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec09. while, scissor-rock-paper game
https://www.youtube.com/watch?v=HWUVM5LpsjI&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=9
******************************************************************************/

#include <time.h>

#include <iostream>
using namespace std;

enum SRP { SRP_S = 1, SRP_R, SRP_P, SRP_END };

int main() {
  /* while, for loops */

  int iNumber = 0;
  while (iNumber < 10) {
    cout << iNumber << endl;
    ++iNumber;
    if (iNumber == 4) break;
  }

  system("cls");

  /* Scissors-rock-paper */

  srand((unsigned int)time(0));
  int iPlayer, iAI;

  while (true) {
    cout << "1. Scissors" << endl;
    cout << "2. Rock" << endl;
    cout << "3. Paper" << endl;
    cout << "4. End Geme" << endl;
    cout << "Select Menu: " << endl;
    cin >> iPlayer;

    if (iPlayer < SRP_S || iPlayer > SRP_END) {
      cout << "Wrong value." << endl;
      system("pause");
      continue;
    } else if (iPlayer == SRP_END)
      break;

    iAI = rand() % 3 + SRP_S;

    switch (iAI) {
      case SRP_S:
        cout << "AI: Scissors" << endl;
        break;
      case SRP_R:
        cout << "AI: Rock" << endl;
        break;
      case SRP_P:
        cout << "AI: Paper" << endl;
        break;
    }

    int iWin = iPlayer - iAI;
    if (iWin == 1 || iWin == -2)
      cout << "Player wins!" << endl;
    else if (iWin == 0)
      cout << "Draw!" << endl;
    else
      cout << "AI wins!" << endl;
  }

  return 0;
}