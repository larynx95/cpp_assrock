/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec21. Student Records 2
https://www.youtube.com/watch?v=3kH8y7gp0Kg&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=21
******************************************************************************/

#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10
#define PHONE_SIZE 14
#define ADDRESS_SIZE 128

struct _tagStudent {
  char strName[NAME_SIZE];
  char strAddress[ADDRESS_SIZE];
  char strPhoneNumber[PHONE_SIZE];
  int iNumber;
  int iKor;
  int iEng;
  int iMath;
  int iTotal;
  float fAvg;
};

enum MENU {
  MENU_NONE,
  MENU_INSERT,
  MENU_DELETE,
  MENU_SEARCH,
  MENU_OUTPUT,
  MENU_EXIT
};

int main() {
  /**/
  _tagStudent tStudentArr[STUDENT_MAX] = {};
  int iStudentCount = 0;
  int iStdNumber = 1;

  while (true) {
    system("clear");

    cout << "1. Add" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout << "4. Output" << endl;
    cout << "Select Menu: ";
    int iMenu;
    cin >> iMenu;

    if (cin.fail()) {
      // flushing the error buffer
      cin.clear();
      // There is '\n' in input buffer, find and delete it.
      cin.ignore(1024, '\n');
      continue;
    }

    if (iMenu == MENU_EXIT) break;

    switch (iMenu) {
      // system("clear");

      if (iStudentCount == STUDENT_MAX) break;

      case MENU_INSERT:
        cout << "~~~~~~ Add ~~~~~~" << endl;
        cout << "Name: ";
        cin >> tStudentArr[iStudentCount].strName;

        cout << "Address: ";
        // cin >> tStudentArr[iStudentCount].strAddress;
        cin.ignore(1024, '\n');
        cin.getline(tStudentArr[iStudentCount].strAddress, ADDRESS_SIZE);

        cout << "Phone: " << endl;
        cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

        cout << "Korean: ";
        cin >> tStudentArr[iStudentCount].iKor;

        cout << "English: ";
        cin >> tStudentArr[iStudentCount].iEng;

        cout << "Math: ";
        cin >> tStudentArr[iStudentCount].iMath;

        tStudentArr[iStudentCount].iTotal = tStudentArr[iStudentCount].iKor +
                                            tStudentArr[iStudentCount].iEng +
                                            tStudentArr[iStudentCount].iMath;

        tStudentArr[iStudentCount].fAvg =
            tStudentArr[iStudentCount].iTotal / 3.0;

        tStudentArr[iStudentCount].iNumber = iStdNumber;
        ++iStdNumber;
        ++iStudentCount;

        cout << "A student was added successfully." << endl;
        break;
      case MENU_DELETE:
        break;
      case MENU_SEARCH:
        break;
      case MENU_OUTPUT:
        cout << "~~~~~~ output ~~~~~~" << endl;
        for (int i = 0; i < iStudentCount; ++i) {
          cout << "Name: " << tStudentArr[i].strName << endl;
          cout << "Phone: " << tStudentArr[i].strPhoneNumber << endl;
          cout << "Address: " << tStudentArr[i].strAddress << endl;
          cout << "Number: " << tStudentArr[i].iNumber << endl;
          cout << "Korean: " << tStudentArr[i].iKor << endl;
          cout << "English: " << tStudentArr[i].iEng << endl;
          cout << "Math: " << tStudentArr[i].iMath << endl;
          cout << "Total: " << tStudentArr[i].iTotal << endl;
          cout << "Average: " << tStudentArr[i].fAvg << endl;
        }
        break;
      default:
        cout << "Wrong menu" << endl;
    }
  }

  return 0;
}