/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec20. Student Records 1
https://www.youtube.com/watch?v=3kH8y7gp0Kg&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=20
******************************************************************************/

#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define NAME_SIZE 32

struct _tagStudent {        // total 56 bytes
  char strName[NAME_SIZE];  // 32 bytes
  int iNumber;              // 4 bytes
  int iKor;                 // 4 bytes
  int iEng;                 // 4 bytes
  int iMath;                // 4 bytes
  int iTotal;               // 4 bytes
  float fAvg;               // 4 bytes
};

int main() {
  /* declaration */
  _tagStudent tStudent = {};
  _tagStudent tStudentArr[100] = {};

  /* accessing member */
  tStudent.iKor = 100;  // number
  // tStudent.strName = "abcdef";  // error!

  /* string is special */
  strcpy(tStudent.strName, "hello");
  cout << "name: " << tStudent.strName << endl;
  cout << "number: " << tStudent.iNumber << endl;
  cout << "Korean: " << tStudent.iKor << endl;
  cout << "English: " << tStudent.iEng << endl;
  cout << "Math: " << tStudent.iMath << endl;
  cout << "Total: " << tStudent.iTotal << endl;
  cout << "Average: " << tStudent.fAvg << endl;

  strcat(tStudent.strName, " World");
  cout << "name: " << tStudent.strName << endl;
  cout << "length: " << strlen(tStudent.strName) << endl;

  cout << "Enter a name: ";
  char strName[NAME_SIZE] = {};
  cin >> strName;

  if (strcmp(tStudent.strName, strName) == 0) {
    cout << "You've found the student." << endl;
  } else {
    cout << "No student with that name" << endl;
  }

  return 0;
}