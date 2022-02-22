/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec77. Queue
https://www.youtube.com/watch?v=FBtir_M_Xig&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=77
******************************************************************************/

#include <cstring>
#include <iostream>

using namespace std;

template <typename T>
class CQueueNode {
 private:
  CQueueNode() : m_pNext(NULL), m_pPrev(NULL) {}
  ~CQueueNode() {}

 private:
  template <typename U>
  friend class CQueue;

 private:
  T m_Data;
  CQueueNode<T>* m_pNext;
  CQueueNode<T>* m_pPrev;
};

template <typename T>
class CQueue {
 public:
  CQueue() {
    m_pBegin = new NODE;
    m_pEnd = new NODE;

    m_pBegin->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = m_pBegin;

    m_iSize = 0;
  }
  ~CQueue() {}

 private:
  typedef CQueueNode<T> NODE;
  typedef CQueueNode<T>* PNODE;

 private:
  PNODE m_pBegin;
  PNODE m_pEnd;
  unsigned int m_iSize;

 public:
  void push(const T& data) {
    PNODE pNode = new NODE;

    pNode->m_Data = data;

    PNODE pPrev = m_pEnd->m_pPrev;

    pPrev->m_pNext = pNode;
    pNode->m_pPrev = pPrev;

    pNode->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = pNode;

    ++m_iSize;
  }

  bool empty() { return m_iSize == 0; }

  T pop() {
    if (empty()) return 0;

    PNODE pNode = m_pBegin->m_pNext;

    T data = pNode->m_Data;

    m_pBegin->m_pNext = pNode->m_pNext;
    pNode->m_pNext->m_pPrev = m_pBegin;

    delete pNode;
    --m_iSize;

    return data;
  }
};

template <typename T, int SIZE = 100>  // <-- Notice this!!
class CCircleQueue {
 public:
  CCircleQueue() {
    m_iSize = 0;
    m_iHead = 0;
    m_iTail = 0;
  }
  ~CCircleQueue() {}

 private:
  T m_Data[SIZE + 1];
  unsigned int m_iSize;
  unsigned int m_iHead;
  unsigned int m_iTail;

 public:
  void push(const T& data) {
    if (full()) return;

    int idx = (m_iTail + 1) % (SIZE + 1);

    m_Data[idx] = data;
    m_iTail = idx;
    ++m_iSize;
  }

  T pop() {
    if (empty()) return 0;

    int idx = (m_iHead + 1) % (SIZE + 1);

    T data = m_Data[idx];

    m_iHead = idx;
    --m_iSize;

    return data;
  }

  bool empty() { return m_iSize == 0; }

  bool full() { return m_iSize == SIZE; }
};

int main() {
  CCircleQueue<int, 10> queue;

  for (int i = 0; i < 10; ++i) {
    queue.push(i + 1);
  }

  for (int i = 0; i < 3; ++i) {
    cout << queue.pop() << " ";
  }
  cout << endl;

  for (int i = 0; i < 4; ++i) {
    queue.push(i + 1);
  }

  while (!queue.empty()) {
    cout << queue.pop() << " ";
  }
  cout << endl;

  return 0;
}
