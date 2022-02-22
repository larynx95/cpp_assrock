/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec70. Inheritance
https://www.youtube.com/watch?v=nh3WN3hkGME&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=70
******************************************************************************/

#include <iostream>

using namespace std;

/**********************************************************
 * CParent Class
 *********************************************************/

class CParent {
 public:
  CParent() { cout << "Constructor - CParent" << endl; }
  ~CParent() { cout << "Destructor - Cparent" << endl; }

 public:
  int m_iA;  // public - visible to all

 protected:
  int m_iB;  // protected - visible to inherited class

 private:
  int m_iC;  // private - visible only to self

 public:
  void OutputAll() {  // public method
    cout << "A: " << m_iA << endl;
    cout << "B: " << m_iB << endl;
    cout << "C: " << m_iC << endl;
  }

 protected:
  void ProtectedOutputAll() {  // public method
    cout << "A: " << m_iA << endl;
    cout << "B: " << m_iB << endl;
    cout << "C: " << m_iC << endl;
  }
};

/**********************************************************
 * CChild Class (inherit Cparent - public )
 *********************************************************/

class CChild : public CParent {
 public:
  CChild() {
    m_iB = 200;
    // m_iC = 300;  // impossible, private field
    cout << "  Constructor - CChild" << endl;
    ProtectedOutputAll();
  }
  ~CChild() { cout << "  Destructor - CChild" << endl; }

 protected:
  int m_iD;
};

/**********************************************************
 * CPrivateChild Class (inherit Cparent - private)
 *********************************************************/

class CPrivateChild : private CParent {
 public:
  CPrivateChild() {
    m_iA = 100;
    m_iB = 200;
    // m_iC = 300;  // impossible, private field
    cout << "  Constructor - CPrivateChild" << endl;
  }
  ~CPrivateChild() { cout << "  Destructor - CPrivateChild" << endl; }

 private:
  int m_iD;
};

/**********************************************************
 * CGrandChild Class (inherit CChild - public)
 *********************************************************/

class CGrandChild : public CChild {
 public:
  CGrandChild() {
    m_iD = 500;
    cout << "    Constructor - CGrandChild" << endl;
  }
  ~CGrandChild() { cout << "    Destructor - CGrandChild" << endl; }

 private:
  int m_iE;
};

/**********************************************************
 * main function
 *********************************************************/

int main() {
  CParent parent;
  CChild child;
  CPrivateChild pchild;
  CGrandChild gchild;

  parent.m_iA = 100;
  child.m_iA = 200;
  child.OutputAll();
  // child.ProtectedOutputAll();
  // pchild.m_iA = 300;  // impossible, private inheritance
  // pchild.OutputAll();    // impossible. private inheritance

  return 0;
}
