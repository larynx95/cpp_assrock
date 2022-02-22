/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec06. if statement
https://www.youtube.com/watch?v=A_Ky-hFIOd4&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=6
******************************************************************************/

#include <iostream>

using namespace std;

int main() {
  /* if */
  const int iAttack = 0x00000001;
  const int iArmor = 0x00000002;
  const int iHP = 0x00000004;
  const int iMP = 0x00000008;
  const int iCritical = 0x00000016;

  int iBuf = iAttack | iHP | iCritical;

  if (iBuf & iAttack != 0) {
    cout << "There's Attack buf." << endl;
  }

  if (iBuf & iHP != 0)
    // Code block can be omitted with One-line.
    cout << "There's HP buf." << endl;

  if (iBuf & iMP != 0) cout << "There's MP buf." << endl;

  if (iBuf & iCritical != 0) cout << "There's Critical buf." << endl;

  /* else */

  return 0;
}