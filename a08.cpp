/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec08. switch, enum
https://www.youtube.com/watch?v=vLxGf_QNv5s&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=8
******************************************************************************/

#include <iostream>
using namespace std;

enum NUM { NUM_0 = 10, NUM_1, NUM_2 = 0x0010, NUM_3 };

int main() {
  /* switch: check the value, not condition */

  int iNumber;
  cout << "Enter a number: " << endl;
  cin >> iNumber;

  switch (iNumber) {
    case NUM_0: {
      cout << "You've entered 10." << endl;
      cout << "We need a block wrapping two-more lines" << endl;
      break;
    }
    case 2:
      cout << "You've entered 2." << endl;
      break;
    case 3:
      cout << "You've entered 3." << endl;
      break;
    default:
      cout << "Other number" << endl;
      break;
  }

  /* enum type variable */

  NUM eNum;                             // always 4 bytes
  cout << sizeof(NUM) << endl;          // 4
  cout << typeid(eNum).name() << endl;  // NUM

  return 0;
}