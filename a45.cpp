/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec45. Single Linked List 2
https://www.youtube.com/watch?v=Z63JuYlptx4&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=45
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

void InputString(char* pString, int iSize) {
  cin.clear();
  cin.ignore(1024, '\n');
  cin.getline(pString, iSize - 1);
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

void Insert(PLIST pList) {
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

  // create a new NODE with new STUDENT
  PNODE pNode = new NODE;  // Memory allocation
  pNode->pNext = NULL;
  pNode->tStudent = tStudent;

  // check if a new NODE is the first element in the LIST
  if (pList->pBegin == NULL) {
    pList->pBegin = pNode;
  } else {
    pList->pEnd->pNext = pNode;
  }

  // move pEnd pointer to the last NODE just added now
  pList->pEnd = pNode;
  ++pList->iSize;
}

void ClearList(PLIST pList) {
  PNODE pNode = pList->pBegin;
  while (pNode != NULL) {
    PNODE pNext = pNode->pNext;
    delete pNode;
    pNode = pNext;
  }
  pList->pBegin = NULL;
}

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
  cout << "===== Delete Record =====" << endl;

  PNODE pNode = pList->pBegin;

  while (pNode != NULL) {
    OutputStudent(&pNode->tStudent);
    pNode = pNode->pNext;
  }

  cout << "The number of students: " << pList->iSize << endl;
  system("read");
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
        Insert(&tList);
      } break;
      case MM_DELETE: {
      } break;
      case MM_SEARCH: {
      } break;
      case MM_OUTPUT: {
        Output(&tList);
      } break;
      case MM_EXIT: {
      } break;
    }
  }

  return 0;
}