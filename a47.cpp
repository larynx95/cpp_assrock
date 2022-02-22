/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec47. Double Linked List 1
https://www.youtube.com/watch?v=kJrsztu62Mc&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=47
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
enum OUTPUT_TYPE { OT_NONE, OT_OUTPUT, OT_INVERSE };

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
  _tagNode* pPrev;
} NODE, *PNODE;

typedef struct _tagList {
  PNODE pBegin;
  PNODE pEnd;
  int iSize;
} LIST, *PLIST;

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

void InputString(char* pString, int iSize) {
  cin.clear();
  cin.ignore(1024, '\n');
  cin.getline(pString, iSize - 1);
}

/* InitList

   This is Double Linked List (DLKLS, not circular).
   We can initialize it as a list of two nodes.

   pList->pBegin->pPrev                   pList->pEnd->pNext
   |                                                       |
   |       pList->pBegin           pList->pEnd             |
   |       |                       |                       |
   v       v                       v                       v
   NULL <- ┌──────────┬───────┐ -> ┌──────────┬───────┐ -> NULL
           | tStudent | pNext | <- | tStudent | pNext |
           └──────────┴───────┘    └──────────┴───────┘
*/
void InitList(PLIST pList) {
  pList->iSize = 0;

  pList->pBegin = new NODE;
  pList->pEnd = new NODE;

  pList->pBegin->pNext = pList->pEnd;
  pList->pEnd->pPrev = pList->pBegin;

  pList->pEnd->pNext = NULL;
  pList->pBegin->pPrev = NULL;
}

void DestoryList(PLIST pList) {
  PNODE pNode = pList->pBegin;

  while (pNode != NULL) {
    PNODE pNext = pNode->pNext;
    delete pNode;
    pNode = pNext;
  }

  pList->iSize = 0;
  pList->pBegin = NULL;
  pList->pEnd = NULL;
}

void Push_Back(PLIST pList) {
  system("clear");
  cout << "===== Add Record =====" << endl;

  // create a new STUDENT
  STUDENT tStudent = {};

  cout << "Name: ";
  InputString(tStudent.strName, NAME_SIZE);
  cout << "Number: ";
  tStudent.iNumber = InputInt();
  cout << "Kor: ";
  tStudent.iKor = InputInt();
  cout << "Eng: ";
  tStudent.iEng = InputInt();
  cout << "Math: ";
  tStudent.iMath = InputInt();
  tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
  tStudent.fAvg = tStudent.iTotal / 3.f;

  PNODE pNode = new NODE;
  pNode->tStudent = tStudent;

  PNODE pPrev = pList->pEnd->pPrev;
  pPrev->pNext = pNode;
  pNode->pPrev = pPrev;

  pNode->pNext = pList->pEnd;
  pList->pEnd->pPrev = pNode;
  ++pList->iSize;
}

void Push_Front(PLIST pList) {}

void OutputStudent(const PSTUDENT pStudent) {
  cout << "Number: " << pStudent->iNumber << endl;
  cout << "  Name: " << pStudent->strName << endl;
  cout << "  Kor: " << pStudent->iKor << endl;
  cout << "  Eng: " << pStudent->iEng << endl;
  cout << "  Math: " << pStudent->iMath << endl;
  cout << "  Total: " << pStudent->iTotal << endl;
  cout << "  Avg: " << pStudent->fAvg << endl << endl;
}

void Output(PLIST pList) {
  system("clear");
  cout << "===== Print Record =====" << endl;
  cout << "1. Print in order" << endl;
  cout << "2. Print reversed order" << endl;
  cout << "Select Menu: " << endl;
  int iMenu = InputInt();
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
        Push_Back(&tList);
      } break;
      case MM_DELETE: {
        Delete(&tList);
      } break;
      case MM_SEARCH: {
        Search(&tList);
      } break;
      case MM_OUTPUT: {
        Output(&tList);
      } break;
      case MM_EXIT: {
      } break;
    }
  }

  DestoryList(&tList);

  return 0;
}