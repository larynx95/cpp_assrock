/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec76. Stack
https://www.youtube.com/watch?v=nP7I2aTrJyk&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=76
******************************************************************************/

#include <cstring>
#include <iostream>

using namespace std;

template <typename T>
class CStackNode {
 private:
  CStackNode() : m_pNext(NULL) {}
  ~CStackNode() {}

 private:
  template <typename U>
  friend class CStack;

 private:
  T m_Data;
  CStackNode<T>* m_pNext;
};

template <typename T>
class CStack {
 public:
  CStack() {
    m_pBegin = new NODE;
    m_pEnd = new NODE;

    m_pBegin->m_pNext = m_pEnd;

    m_iSize = 0;
  }
  ~CStack() {
    PNODE pNode = m_pBegin;

    while (pNode) {
      PNODE pNext = pNode->m_pNext;
      delete pNode;
      pNode = pNext;
    }
  }

 private:
  typedef CStackNode<T> NODE;
  typedef CStackNode<T>* PNODE;

 private:
  PNODE m_pBegin;
  PNODE m_pEnd;
  unsigned int m_iSize;

 public:
  void push(const T& data) {
    PNODE pNode = new NODE;
    pNode->m_Data = data;

    PNODE pNext = m_pBegin->m_pNext;
    pNode->m_pNext = pNext;
    m_pBegin->m_pNext = pNode;
    ++m_iSize;
  }

  T pop() {
    if (empty()) return 0;

    PNODE pNode = m_pBegin->m_pNext;
    PNODE pNext = pNode->m_pNext;
    T data = pNode->m_Data;
    delete pNode;
    m_pBegin->m_pNext = pNext;
    --m_iSize;

    return data;
  }

  T top() {
    if (empty()) return 0;

    return m_pBegin->m_pNext->m_Data;
  }

  bool empty() { return m_iSize == 0; }
};

int main() {
  /* stack */
  CStack<int> stackInt;

  for (int i = 0; i < 10; i++) {
    stackInt.push(i + 1);
  }

  while (!stackInt.empty()) {
    cout << stackInt.pop() << " ";
  }

  return 0;
}