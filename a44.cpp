/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec44. Single Linked List 1
https://www.youtube.com/watch?v=H2C8imDSAgU&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=44
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10

enum MAIN_MENU { MM_NONE, MM_INSERT, MM_DELETE, MM_SEARCH, MM_OUTPUT, MM_EXIT };

typedef struct _tagStudent {
  char strName[NAME_SIZE];
  int iNumber;
  int iKor;
  int iEng;
  int iMath;
  int iTotal;
  float fAvg;
} STUDENT, *PSTUDENT;

typedef struct _tagNode {
  STUDENT tStudent;
  _tagNode* pNext;
} NODE, *PNODE;

typedef struct _tagList {
  PNODE pBegin;
  PNODE pEnd;
  int iSize;
} LIST, *PLIST;

void InitList(PLIST pList) {
  // initializing pointer
  pList->pBegin = NULL;
  pList->pEnd = NULL;
  pList->iSize = 0;
}

int InputInt() {
  int iInput;
  cin >> iInput;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    return INT_MAX;
  }
  return iInput;
}

int OutputMenu() {
  system("clear");
  cout << "1. Add" << endl;
  cout << "2. Delete" << endl;
  cout << "3. Search" << endl;
  cout << "4. Output" << endl;
  cout << "5. Exit" << endl;
  cout << "Select Menu: " << endl;

  int iInput = InputInt();

  if (iInput <= MM_NONE || iInput > MM_EXIT) {
    return MM_NONE;
  }
  return iInput;
}

int main() {
  /* Sinlge Linked List */

  LIST tList;
  InitList(&tList);

  while (true) {
    int iMenu = OutputMenu();
    if (iMenu == MM_EXIT) break;

    switch (iMenu) {
      case MM_INSERT: {
      } break;
      case MM_DELETE: {
      } break;
      case MM_SEARCH: {
      } break;
      case MM_OUTPUT: {
      } break;
      case MM_EXIT: {
      } break;
    }
  }

  return 0;
}