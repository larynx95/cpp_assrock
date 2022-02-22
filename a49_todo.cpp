/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec49. Double Linked List 3
https://www.youtube.com/watch?v=3xr5rYY-WXE&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=49
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10

enum MAIN_MENU {
  MM_NONE,
  MM_INSERT,
  MM_DELETE,
  MM_SEARCH,
  MM_OUTPUT,
  MM_SORT,
  MM_EXIT
};
enum OUTPUT_TYPE { OT_NONE, OT_OUTPUT, OT_INVERSE };
enum SORT_TYPE { ST_NONE, ST_NUMBER, ST_AVG };

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

int OutputMenu() {
  system("clear");
  cout << "1. Add" << endl;
  cout << "2. Delete" << endl;
  cout << "3. Search" << endl;
  cout << "4. Output" << endl;
  cout << "5. Sort" << endl;
  cout << "6. Exit" << endl;
  cout << "Select Menu: " << endl;

  int iInput = InputInt();

  if (iInput <= MM_NONE || iInput > MM_EXIT) {
    return MM_NONE;
  }
  return iInput;
}

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
  int iMenu;
  while (true) {
    system("clear");
    cout << "===== Print Record =====" << endl;
    cout << "1. Print in order" << endl;
    cout << "2. Print reversed order" << endl;
    cout << "Select Menu: ";
    iMenu = InputInt();
    if (iMenu > OT_NONE && iMenu <= OT_INVERSE) break;
  }

  PNODE pNode = NULL;

  switch (iMenu) {
    case OT_OUTPUT: {
      pNode = pList->pBegin->pNext;

      while (pNode != pList->pEnd) {
        OutputStudent(&pNode->tStudent);
        pNode = pNode->pNext;
      }
    } break;
    case OT_INVERSE: {
      pNode = pList->pEnd->pPrev;
      while (pNode != pList->pBegin) {
        OutputStudent(&pNode->tStudent);
        pNode = pNode->pPrev;
      }
    } break;
  }
  cout << "The number of students: " << pList->iSize << endl;
  system("read");
}

void Delete(PLIST pList) {
  system("clear");
  cout << "===== Delete Record =====" << endl;

  cout << "Enter name: ";
  char strName[NAME_SIZE] = {};
  InputString(strName, NAME_SIZE);

  PNODE pNode = pList->pBegin->pNext;

  while (pNode != pList->pEnd) {
    if (strcmp(pNode->tStudent.strName, strName) == 0) {
      pNode->pPrev->pNext = pNode->pNext;
      pNode->pNext->pPrev = pNode->pPrev;
      delete pNode;
      --pList->iSize;
      cout << strName << "'s record was deleted." << endl;
      system("read");
      return;
    }

    pNode = pNode->pNext;
  }
  cout << "No such record." << endl;
  system("read");
}

// TODO: Bubble sort
void Sort(PLIST pList) {
  system("clear");
  cout << "===== Sort Records =====" << endl;
  cout << "1. By Number" << endl;
  cout << "2. By Average" << endl;
  cout << "Select menu: ";
  int iInput = InputInt();

  if (iInput <= ST_NONE || iInput > ST_AVG) {
    cout << "Wrong Input" << endl;
    system("clear");
    return;
  }

  PNODE pFirst = pList->pBegin->pNext;
  PNODE pSecond = pFirst->pNext;

  while (pFirst != pList->pEnd->pPrev) {
    pSecond = pFirst->pNext;
    while (pSecond != pList->pEnd) {
      bool bSwap = false;
      switch (iInput) {
        case ST_NUMBER: {
          if (pFirst->tStudent.iNumber > pSecond->tStudent.iNumber) {
            bSwap = true;
          }
        } break;
        case ST_AVG: {
          if (pFirst->tStudent.fAvg > pSecond->tStudent.fAvg) {
            bSwap = true;
          }
        } break;
      }

      if (bSwap) {
        PNODE pFirstPrev = pFirst->pPrev;
        PNODE pFirstNext = pFirst->pNext;

        PNODE pSecondPrev = pSecond->pPrev;
        PNODE pSecondNext = pSecond->pNext;

        pFirstPrev->pNext = pSecond;
        pSecond->pPrev = pFirstPrev;

        if (pSecond != pFirstNext) {
          pFirstNext->pPrev = pSecond;
          pSecond->pNext = pFirstNext;

          pSecondPrev->pNext = pFirst;
          pFirst->pPrev = pSecondPrev;
        } else {
          pSecond->pNext = pFirst;
          pFirst->pPrev = pSecond;
        }

        pSecondNext->pPrev = pFirst;
        pFirst->pNext = pSecondNext;

        PNODE pTemp = pFirst;
        pFirst = pSecond;
        pSecond = pTemp;
      }
      pSecond = pSecond->pNext;
    }

    pFirst = pFirst->pNext;
  }
  cout << "Sorting Completed" << endl;
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
        Push_Back(&tList);
      } break;
      case MM_DELETE: {
        Delete(&tList);
      } break;
      case MM_SEARCH: {
        // Search(&tList);
      } break;
      case MM_OUTPUT: {
        Output(&tList);
      } break;
      case MM_SORT: {
        Sort(&tList);
      } break;
    }
  }

  DestoryList(&tList);

  return 0;
}