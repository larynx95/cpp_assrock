/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec05. Bitwise Operations, Shift
https://www.youtube.com/watch?v=cRhzlq6ROdo&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=5
******************************************************************************/

#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  /* constant */

  // constant : immutable
  // must be initialized at the same time as declaration

  const int iAttack = 0x00000001;
  const int iArmor = 0x00000002;
  const int iHP = 0x00000004;
  const int iMP = 0x00000008;
  const int iCritical = 0x00000016;

  /* We can store a specific information in bitwise numbers */

  //  iBuf = 001     | 00100 | 10000  = 10101
  int iBuf = iAttack | iHP | iCritical;

  // 10101 & 00001 = 1
  cout << "Attack: " << (iBuf & iAttack) << endl;
  // 10101 & 00010 = 0
  cout << "Armor : " << (iBuf & iArmor) << endl;
  cout << "HP : " << (iBuf & iHP) << endl;
  cout << "MP : " << (iBuf & iMP) << endl;
  cout << "Critical : " << (iBuf & iCritical) << endl;

  /* We can turn off a specific item by exclusive OR (XOR)
     We can also turn the item on again by XOR
  */

  // 10101 ^ 00100 = 10001
  iBuf ^= iHP;

  // 10001 ^ 00100 = 10101
  iBuf ^= iHP;

  /* shift operation: <<, >>
     << : fast multiplication
     >> : fast division
  */

  // 10100 << 2 = 1010000    = 80   20 * 2^2
  // 10100 << 3 = 10100000   = 160  20 * 2^3
  // 10100 << 4 = 101000000  = 320  20 * 2^4
  // 10100 << 5 = 1010000000 = 640  20 * 2^5
  cout << "20 << 2: " << (20 << 2) << endl;
  cout << "20 << 3: " << (20 << 3) << endl;
  cout << "20 << 4: " << (20 << 4) << endl;
  cout << "20 << 5: " << (20 << 5) << endl;

  // 10100 >> 2 = 101 = 5
  // 10100 >> 3 = 10  = 2
  // 10100 >> 4 = 1   = 1
  // 10100 >> 5 = 0   = 0
  cout << "20 >> 2: " << (20 >> 2) << endl;
  cout << "20 >> 3: " << (20 >> 3) << endl;
  cout << "20 >> 4: " << (20 >> 4) << endl;
  cout << "20 >> 5: " << (20 >> 5) << endl;

  /* Dividing memory space (4 bytes to 2 bytes)
    Decimal 187, 13560 to binary:
      187 % 2 = 1     13560 % 2 = 0
      93  % 2 = 1      6780 % 2 = 0
      46  % 2 = 0      3390 % 2 = 0
      23  % 2 = 1      1695 % 2 = 1
      11  % 2 = 1       847 % 2 = 1
      5   % 2 = 1       423 % 2 = 1
      2   % 2 = 0       211 % 2 = 1
      1                 105 % 2 = 1
      => 10111011        52 % 2 = 0
                         26 % 2 = 0
                         13 % 2 = 1
                          6 % 2 = 0
                          3 % 2 = 1
                          1
                          ;=> 11010011111000

    Four bytes (32 bits) can be divided into tw0 16 bits spaces.

      4 bytes memory (32 bits)
    ┌──────────────────────┬──────────────────────┐
    |  2 bystes            | 2 bytes              |
    |  1 byte    1 byte    | 1 byte    1 byte     |
    |  16 bits             | 16 bits              |
    |  8 bits    8 bits    | 8 bits    8 bits     |
    |  0x00000000          |                      |
    |  0x0000              | 0x0000               |
    |  0x00      0x00      | 0x00      0x00       |
    |  0x0  0x0  0x0  0x0  | 0x0  0x0  0x0  0x0   |
    |  0000 0000 0000 0000 | 0000 0000 0000 0000  |
    └──────────────────────┴──────────────────────┘

      By int iNumber = iHigh;
    ┌─────────────────────┬───────────────────────┐
    | 0000 0000 0000 0000 | 0000 0000 1011 1011   |
    └─────────────────────┴───────────────────────┘

      By iNumber <<= 16;
    ┌─────────────────────┬───────────────────────┐
    | 0000 0000 1011 1011 | 0000 0000 0000 0000   |
    └─────────────────────┴───────────────────────┘

      By iNumber |= iLow;
    ┌─────────────────────┬───────────────────────┐
    | 0000 0000 1011 1011 | 0011 0100 1111 1000   |
    └─────────────────────┴───────────────────────┘
  */

  int iHigh = 187;
  int iLow = 13650;
  int iNumber = iHigh;

  iNumber <<= 16;
  iNumber |= iLow;

  cout << "High : " << (iNumber >> 16) << endl;
  cout << "Low : " << (iNumber & 0x0000ffff) << endl;

  /* increment, decrement operators */

  iNumber = 10;
  ++iNumber;
  iNumber++;
  cout << ++iNumber << endl;  // 13
  cout << iNumber++ << endl;  // 13
  cout << iNumber << endl;    // 14

  system("read");
  return 0;
}
