/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec46. Single Linked List 3
https://www.youtube.com/watch?v=-UYby26BGug&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=46
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

void Search(PLIST pList) {
  system("clear");
  cout << "===== Search Record =====" << endl;

  cout << "Enter Name:";
  char strName[NAME_SIZE] = {};
  InputString(strName, NAME_SIZE);

  PNODE pNode = pList->pBegin;

  while (pNode != NULL) {
    if (strcmp(pNode->tStudent.strName, strName) == 0) {
      OutputStudent(&pNode->tStudent);
      system("read");
      return;
    }
    pNode = pNode->pNext;
  }

  cout << "No student with that name." << endl;
  system("read");
}

/* Deleting Node
1. When pList is empty

2. When pList is not empty

  We need three pointer variables for deleting a NODE,
  - pNode: current NODE which we are focusing on
  - pNext: the next NODE of current NODE (pNode)
  - pPrev: the previous NODE of current NODE (pNode)
  We need "pPrev" and "pNext" pointer variables
  because we should link them when "pNode" is deleted.

1) Initial state

  pPrev = NULL

  pList->pBegin                                   pList->pEnd
  |  == pNode                                     |
  v                                               v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

2) Search and Delete

  (1) When the first NODE of pList is the one which we want to delete

  pList->pBegin           pNext                   pList->pEnd
  |  == pNode             |                       |
  v                       v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

  pNode                   pNext                   pList->pEnd
  |                       |  == pList->pBegin     |
  v                       v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

  pNode (deleted)         pNext                   pList->pEnd
                          |  == pList->pBegin     |
                          v                       v
  ┌----------┬-------┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └----------┴-------┘    └──────────┴───────┘    └──────────┴───────┘

                          pList->pBegin           pList->pEnd
                          |  == pNode == pPrev    |
                          v                       v
  ┌----------┬-------┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └----------┴-------┘    └──────────┴───────┘    └──────────┴───────┘

                          pList->pBegin           pList->pEnd
                          |  == pNode == pPrev    |
                          v                       v
                          ┌──────────┬───────┐    ┌──────────┬───────┐
                          | tStudent | pNext | -> | tStudent | pNext | -> NULL
                          └──────────┴───────┘    └──────────┴───────┘

  (2) when the NODE we want to delete is not the first NODE

  pList->pBegin           pNext                   pList->pEnd
  |  == pNode             |                       |
  v                       v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pNext                   pList->pEnd
  |  == pPrev             |  == pNode             |
  v                       v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pNode                   pList->pEnd
  |  == pPrev             |                       |  == pNext
  v                       v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pNode (deleted)         pList->pEnd
  |  == pPrev                                     |  == pNext
  v                                               v
  ┌──────────┬───────┐    ┌----------┬-------┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └----------┴-------┘    └──────────┴───────┘

  pList->pBegin           pNode (deleted)         pList->pEnd
  |  == pPrev                                     |  == pNext
  v                                               v
  ┌──────────┬───────┐                            ┌──────────┬───────┐
  | tStudent | pNext | -------------------------> | tStudent | pNext | -> NULL
  └──────────┴───────┘                            └──────────┴───────┘

  pList->pBegin           pList->pEnd
  |  == pPrev             |  == pNext == pNode
  v                       v
  ┌──────────┬───────┐    ┌──────────┬───────┐
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pList->pEnd
  |  == pPrev             |  == pNode             pNext
  v                       v                       |
  ┌──────────┬───────┐    ┌──────────┬───────┐    v
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pList->pEnd
  |                       |  == pPrev             pNode
  v                       v                       |
  ┌──────────┬───────┐    ┌──────────┬───────┐    v
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘

  (3) When the last NODE of pList is the one which we want to delete

  pList->pBegin           pList->pEnd
  |  == pPrev             |  == pNode             pNext
  v                       v                       |
  ┌──────────┬───────┐    ┌──────────┬───────┐    v
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pNode
  |  == pPrev             |                       pNext
  v  == pList->pEnd       v                       |
  ┌──────────┬───────┐    ┌──────────┬───────┐    v
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └──────────┴───────┘

  pList->pBegin           pNode (deleted)
  |  == pPrev                                     pNext
  v  == pList->pEnd                               |
  ┌──────────┬───────┐    ┌----------┬-------┐    v
  | tStudent | pNext | -> | tStudent | pNext | -> NULL
  └──────────┴───────┘    └----------┴-------┘

  pList->pBegin
  |  == pPrev             pNext
  v  == pList->pEnd       |  == pNode
  ┌──────────┬───────┐    v
  | tStudent | pNext | -> NULL
  └──────────┴───────┘
*/

void Delete(PLIST pList) {
  system("clear");
  cout << "===== Delete Record =====" << endl;

  // user input
  cout << "Enter Name: ";
  char strName[NAME_SIZE] = {};
  InputString(strName, NAME_SIZE);

  // pointer variables for moving focus
  PNODE pNode = pList->pBegin;
  PNODE pPrev = NULL;

  while (pNode != NULL) {
    // string comparison
    if (strcmp(pNode->tStudent.strName, strName) == 0) {
      // pointer variable for focusing current NODE
      // pNext and pList->pNext are not the same!!
      PNODE pNext = pNode->pNext;

      // when the first NODE is to be deleted
      if (pPrev == NULL) {
        delete pNode;           // delete current NODE
        pList->pBegin = pNext;  // move the pBegin ptr to the next NODE

        // when ptr points the last NODE
        if (pNext == NULL) {
          pList->pEnd = NULL;
        }
      }

      // when the NODE to be deleted is not the first NODE
      else {
        delete pNode;
        pPrev->pNext = pNext;

        // when the NODE to be deleted is the last NODE
        if (pNext == NULL) pList->pEnd = pPrev;
      }

      cout << "Deleted: " << strName << endl;
      --pList->iSize;
      system("read");
      return;
    }

    // moving foucs to the next NODE
    pPrev = pNode;
    pNode = pNode->pNext;
  }

  // when pList has no NODE
  cout << "He or she is not exist in Student database." << endl;
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

  return 0;
}