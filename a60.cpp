/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec60. Class - linked list
https://www.youtube.com/watch?v=5d72Cbd-YrM&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=60
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <functional>
#include <iostream>
using namespace std;

class ClistNode {
 public:
  ClistNode() : m_pNext(NULL), m_pPrev(NULL) {}

  ~ClistNode() {}

 public:
  int m_iData;
  ClistNode* m_pNext;
  ClistNode* m_pPrev;
};

class Clist {
 public:
  Clist() {
    m_pBegin = new ClistNode;
    m_pEnd = new ClistNode;

    m_pBegin->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = m_pBegin;

    m_iSize = 0;
  }

  ~Clist() {
    clear();
    delete m_pBegin;
    delete m_pEnd;
  }

 private:
  ClistNode* m_pBegin;
  ClistNode* m_pEnd;
  int m_iSize;

 public:
  void push_back(int iData) {
    ClistNode* pNode = new ClistNode;
    pNode->m_iData = iData;
    ClistNode* pPrev = m_pEnd->m_pPrev;

    pPrev->m_pNext = pNode;
    pNode->m_pPrev = pPrev;

    pNode->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = pNode;

    ++m_iSize;
  }

  int pop_back() {
    ClistNode* pPrev = m_pEnd->m_pPrev;
    if (pPrev == m_pBegin) return INT_MAX;
    int iData = pPrev->m_iData;

    ClistNode* pPrevP = pPrev->m_pPrev;
    pPrevP->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = pPrevP;

    --m_iSize;

    delete pPrev;
    return iData;
  }

  bool empty() { return m_iSize == 0; }

  void clear() {
    ClistNode* pNode = m_pBegin->m_pNext;

    while (pNode != m_pEnd) {
      ClistNode* pNext = pNode->m_pNext;
      delete pNode;
      pNode = pNext;
    }

    m_pBegin->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = m_pBegin;

    m_iSize = 0;
  }
};

int main() {
  //
  Clist list;

  for (int i = 0; i < 100; ++i) {
    list.push_back(i);
  }

  while (!list.empty()) {
    cout << list.pop_back() << " ";
  }
  return 0;
}