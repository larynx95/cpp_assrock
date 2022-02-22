/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec74. Template, double linked list
https://www.youtube.com/watch?v=1qpaYlk7A00&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=74
******************************************************************************/

#include <iostream>

using namespace std;

// ╔═══════════════════════════════════════════╗
// ║  CListNode Class                          ║
// ╚═══════════════════════════════════════════╝

template <typename T>
class CListNode {
 private:
  CListNode() {
    m_pNext = NULL;
    m_pPrev = NULL;
  }
  ~CListNode() {}

 private:
  // Error
  // declaration of template parameter ‘T’ shadows template parameter
  // Fix: T -> U
  template <typename U>
  friend class CLinkedList;

  template <typename U>
  friend class CListIterator;

  template <typename U>
  friend class CReverseIterator;

  T m_Data;
  CListNode<T>* m_pNext;
  CListNode<T>* m_pPrev;
};

// ╔═══════════════════════════════════════════╗
// ║  CListIterator Class                      ║
// ╚═══════════════════════════════════════════╝

template <typename T>
class CListIterator {
 public:
  CListIterator() {}
  ~CListIterator() {}

 private:
  typedef CListNode<T> NODE;
  typedef CListNode<T>* PNODE;

  template <typename U>
  friend class CLinkedList;

  PNODE m_pNode;

 public:
  bool operator==(const CListIterator<T>& iter) {
    return m_pNode == iter.m_pNode;
  }

  bool operator!=(const CListIterator<T>& iter) {
    return m_pNode != iter.m_pNode;
  }

  void operator++() { m_pNode = m_pNode->m_pNext; }

  void operator--() { m_pNode = m_pNode->m_pPrev; }

  T operator*() { return m_pNode->m_Data; }
};

// ╔═══════════════════════════════════════════╗
// ║  CReverseIterator Class                   ║
// ╚═══════════════════════════════════════════╝

template <typename T>
class CReverseIterator {
 public:
  CReverseIterator() {}
  ~CReverseIterator() {}

 private:
  template <typename U>
  friend class CLinkedList;

 private:
  typedef CListNode<T> NODE;
  typedef CListNode<T>* PNODE;
  PNODE m_pNode;

 public:
  // reference is faster than copying structure argument
  bool operator==(const CReverseIterator<T>& iter) {
    return m_pNode == iter.m_pNode;
  }

  bool operator!=(const CReverseIterator<T>& iter) {
    return m_pNode != iter.m_pNode;
  }

  void operator++() { m_pNode = m_pNode->m_pPrev; }

  void operator--() { m_pNode = m_pNode->m_pNext; }

  // dereferencing operator overload
  T operator*() { return m_pNode->m_Data; }
};

// ╔═══════════════════════════════════════════╗
// ║  CLinkedList Class                        ║
// ╚═══════════════════════════════════════════╝

template <typename T>
class CLinkedList {
 public:
  CLinkedList() {
    m_pBegin = new NODE;
    m_pEnd = new NODE;

    m_pBegin->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = m_pBegin;

    m_iSize = 0;
  }
  ~CLinkedList() {
    clear();
    delete m_pBegin;
    delete m_pEnd;
    m_iSize = 0;
  }

 private:
  typedef CListNode<T> NODE;
  typedef CListNode<T>* PNODE;

  PNODE m_pBegin;
  PNODE m_pEnd;
  unsigned int m_iSize;

 public:
  // TODO: inner class
  typedef CListIterator<T> iterator;
  typedef CReverseIterator<T> rev_iterator;

 public:
  void push_back(const T& data) {
    PNODE pNode = new NODE;
    pNode->m_Data = data;

    PNODE pPrev = m_pEnd->m_pPrev;

    pPrev->m_pNext = pNode;
    pNode->m_pPrev = pPrev;

    pNode->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = pNode;
    ++m_iSize;
  }

  void push_front(const T& data) {
    PNODE pNode = new NODE;
    pNode->m_Data = data;

    PNODE pFirst = m_pBegin->m_pNext;

    pFirst->m_pPrev = pNode;
    pNode->mpNext = pFirst;

    pNode->m_pPrev = m_pBegin;
    m_pBegin->m_pNext = pNode;
    ++m_iSize;
  }

  // const after member fx: "can't change the value of member var"
  unsigned int size() const { return m_iSize; }

  bool empty() const { return m_iSize == 0; }

  void clear() {
    PNODE pNode = m_pBegin->m_pNext;
    while (pNode != m_pEnd) {
      PNODE pNext = pNode->m_pNext;
      delete pNode;
      pNode = pNext;
    }

    m_pBegin->m_pNext = m_pEnd;
    m_pEnd->m_pPrev = m_pBegin;
    m_iSize = 0;
  }

  iterator begin() {
    iterator iter;
    iter.m_pNode = m_pBegin->m_pNext;
    return iter;
  }

  iterator end() {
    iterator iter;
    iter.m_pNode = m_pEnd;
    return iter;
  }

  rev_iterator rbegin() {
    rev_iterator iter;
    iter.m_pNode = m_pEnd->m_pPrev;
    return iter;
  }

  rev_iterator rend() {
    rev_iterator iter;
    iter.m_pNode = m_pBegin;
    return iter;
  }
};

// ╔═══════════════════════════════════════════╗
// ║  main function                            ║
// ╚═══════════════════════════════════════════╝

int main() {
  CLinkedList<int> listInt;
  CLinkedList<float> listFloat;

  for (int i = 0; i < 100; ++i) {
    listInt.push_back(i + 1);
  }
  cout << listInt.size() << endl;

  CLinkedList<int>::iterator iter;
  for (iter = listInt.begin(); iter != listInt.end(); ++iter) {
    cout << *iter << " ";
  }
  cout << endl;

  CLinkedList<int>::rev_iterator riter;
  for (riter = listInt.rbegin(); riter != listInt.rend(); ++riter) {
    cout << *riter << " ";
  }
  cout << endl;

  return 0;
}