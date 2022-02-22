/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec57. Class - constructor
https://www.youtube.com/watch?v=KevgB75oxi4&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=57
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

class CTracer {
 public:
  CTracer() {
    // constructor
    cout << "Constructor" << endl;
    strcpy(m_strName, "tracer");
  }

  CTracer(const char* pName) {
    // constructor overload
    cout << "Constructor - ov" << endl;
    strcpy(m_strName, pName);
  }

  CTracer(const char* pName, int iFlash, int iBack)
      : m_iBack(iBack), m_iFlash(iFlash) {
    // constructor overload with initializer
    strcpy(m_strName, pName);
    cout << "Constructor - ov, init" << endl;
  }

  ~CTracer() {
    // destructor
    cout << "Destructor" << endl;
  }

  char m_strName[32];

 public:
  int m_iAttack;
  int m_iHP;

 private:
  int m_iFlash;
  int m_iBack;

 public:
  void Output() {
    cout << "Tracer Output" << endl;
    cout << "Name : " << m_strName << endl;
  }
};

int main() {
  /**/

  CTracer tr1;
  tr1.Output();

  CTracer tr2("Hello");
  tr2.Output();

  CTracer tr3("World", 100, 200);
  tr2.Output();

  return 0;
}