/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec71. Inheritance Polymorphism
https://www.youtube.com/watch?v=UmDLnhLs_S0&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=71
******************************************************************************/

#include <iostream>

using namespace std;

class CParent {
 public:
  CParent() {  // constructor
    cout << "Constructor - CParent" << endl;
  }
  virtual ~CParent() {  // destructor - virtual
    cout << "Destructor - Cparent" << endl;
  }

 public:
  int m_iA;

 protected:
  int m_iB;

 private:
  int m_iC;

 public:
  void OutputAll() {
    cout << "A: " << m_iA << endl;
    cout << "B: " << m_iB << endl;
    cout << "C: " << m_iC << endl;
  }

  virtual void OutputPure() {}

 protected:
  void ProtectedOutputAll() {
    cout << "A: " << m_iA << endl;
    cout << "B: " << m_iB << endl;
    cout << "C: " << m_iC << endl;
  }
};

class CChild : public CParent {
 public:
  CChild() {
    // constructor
    m_iB = 200;
    // m_iC = 300;  // impossible, private field
    cout << "  Constructor - CChild" << endl;
    // ProtectedOutputAll();
  }
  virtual ~CChild() {
    // destructor
    cout << "  Destructor - CChild" << endl;
  }

 protected:
  int m_iD;

 public:
  void ChildOutput() { cout << "  Fx - Child Output" << endl; }

  // pure virtual function
  virtual void OutputPure() {}
};

class CPChild : private CParent {
 public:
  CPChild() {
    // constructor
    m_iA = 100;
    m_iB = 200;
    // m_iC = 300;  // impossible, private field
    cout << "  Constructor - CPChild" << endl;
  }
  ~CPChild() { cout << "  Destructor - CPChild" << endl; }

 private:
  int m_iD;

 public:
  virtual void OutputPure() {}
};

class CGChild : public CChild {
 public:
  CGChild() {
    // constructor
    m_iD = 500;
    cout << "    Constructor - CGChild" << endl;
  }
  ~CGChild() {
    // destructor
    cout << "    Destructor - CGChild" << endl;
  }

 private:
  int m_iE;
};

int main() {
  /* polymorphism - UP/DOWN casting
  - TODO: Which is possible?
  -       Which is dangerous?
  */

  CParent* pParent = new CChild;         // up-casting
  CChild* pChild = (CChild*)pParent;     // down-casting
  CPChild* pPChild = (CPChild*)pParent;  // not good

  /* type conversion */

  // pParent->ChildOutput();          // need type casting
  ((CChild*)pParent)->ChildOutput();  // type conversion

  // CParent* pParent1 = new CPChild; // impossible
  CParent* pParent2 = new CGChild;

  CParent* pParentArr[2] = {};
  cout << "===== creating instance of CChild =====" << endl;
  pParentArr[0] = new CChild;
  cout << "===== creating instance of CGChild =====" << endl;
  pParentArr[1] = new CGChild;

  /* Destructing instances may be problematic.
     This problem can be solved with virtual function.
     TODO: Compare the results with or without virtual fx.
  */

  cout << "===== delete pParent =====" << endl;
  delete pParent;  // only CParent's destructor will be called
  cout << "===== delete pParent2 =====" << endl;
  delete pParent2;

  for (int i = 0; i < 2; ++i) {
  }

  return 0;
}
