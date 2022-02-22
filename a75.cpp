/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec75. Vector
https://www.youtube.com/watch?v=ZMlKr55NwcI&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=75
******************************************************************************/

#include <cstring>
#include <iostream>

using namespace std;

template <typename T>
class CVectorNode {
 private:
  CVectorNode() {}

  ~CVectorNode() {}

 private:
  template <typename U>
  friend class CVector;

 private:
  T m_Data;
  int m_iIndex;
};

template <typename T>
class CVector {
 public:
  CVector() {
    m_iSize = 0;
    m_iCapacity = 2;
    m_pArray = new CVectorNode<T>[m_iCapacity + 2];
  }

  CVector(int iSize) {
    m_pArray = new NODE[iSize + 2];
    m_iCapacity = iSize;
    m_iSize = 0;
  }

  ~CVector() { delete[] m_pArray; }

 private:
  typedef CVectorNode<T> NODE;
  typedef CVectorNode<T>* PNODE;

 private:
  PNODE m_pArray;
  unsigned int m_iSize;
  unsigned int m_iCapacity;

 public:
  void push_back(const T& data) {
    if (full()) resize(m_iSize * 2);

    // index 0 is begin NODE
    m_pArray[m_iSize + 1].m_Data = data;
    m_pArray[m_iSize + 1].m_iIndex = m_iSize;
    ++m_iSize;
  }

  void resize(int iSize) {
    // including begin(idx 0), end(last idx) NODE
    PNODE pArray = new NODE[iSize + 2];
    memcpy(pArray + 1, m_pArray + 1, sizeof(NODE) * m_iSize);

    delete[] m_pArray;
    m_pArray = pArray;
    m_iCapacity = iSize;
  }

  bool full() { return m_iSize == m_iCapacity; }

  bool empty() { return m_iSize == 0; }

  unsigned int size() const { return m_iSize; }

  unsigned int capacity() const { return m_iCapacity; }

  T operator[](int idx) { return m_pArray[idx + 1].m_Data; }

  void reserve(int iSize) {
    delete[] m_pArray;
    m_pArray = new NODE[iSize + 2];

    m_iCapacity = iSize;
    m_iSize = 0;
  }
};

int main() {
  CVector<int> vecInt;

  vecInt.reserve(100);

  for (int i = 0; i < 10; ++i) {
    vecInt.push_back(i + 1);
  }

  for (int i = 0; i < vecInt.size(); ++i) {
    cout << vecInt[i] << " ";
  }
  return 0;
}