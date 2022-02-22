/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec07. Random number
https://www.youtube.com/watch?v=xJtmRDDpQIA&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=7
******************************************************************************/

#include <time.h>

#include <iostream>

using namespace std;

int main() {
  /* Random number */

  // generate ranodm table
  srand((unsigned int)time(0));

  cout << rand() << endl;
  cout << rand() << endl;
  cout << rand() << endl;

  cout << rand() % 100 << endl;            // 0 ~ 99
  cout << rand() % 101 << endl;            // 0 ~ 100
  cout << rand() % 101 + 100 << endl;      // 100 ~ 200
  cout << rand() % 10000 / 100.f << endl;  // 0 ~ 99.99

  int iUpgrade = 0;
  cout << "Enter Upgrade state:  " << endl;
  cin >> iUpgrade;

  float fPercent = rand() % 10000 / 100.f;

  // probability of fortification
  // if iUpgrade is 0 ~ 3, then 100%
  // if iUpgrade is 4 ~ 6, then 40%
  // if iUpgrade is 7 ~ 9, then 10%
  // if iUpgrade is 10 ~ 13, then 1%
  // if iUpgrade is 14 ~ 15, then 0.01%

  cout << "Upgrade: " << iUpgrade << endl;
  cout << "Percent: " << fPercent << endl;

  if (iUpgrade <= 3)
    cout << "Fortification was successful!" << endl;
  else if (4 <= iUpgrade && iUpgrade <= 6) {
    if (fPercent < 40.f)
      cout << "Fortification was successful!" << endl;
    else
      cout << "Fortification was failed!" << endl;
  } else if (7 <= iUpgrade && iUpgrade <= 9) {
    if (fPercent < 10.f)
      cout << "Fortification was successful!" << endl;
    else
      cout << "Fortification was failed!" << endl;
  } else if (10 <= iUpgrade && iUpgrade <= 13) {
    if (fPercent < 1.f)
      cout << "Fortification was successful!" << endl;
    else
      cout << "Fortification was failed!" << endl;
  } else if (14 <= iUpgrade && iUpgrade <= 15) {
    if (fPercent < 0.01f)
      cout << "Fortification was successful!" << endl;
    else
      cout << "Fortification was failed!" << endl;
  }

  return 0;
}