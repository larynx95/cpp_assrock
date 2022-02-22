/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec58. Class - function pointer
https://www.youtube.com/watch?v=DJkDwCpjz5Q&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=58
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <functional>
#include <iostream>
using namespace std;

int Sum(int a, int b) {
  cout << a + b << endl;
  return a + b;
}

int OutSum(int a, int b) {
  cout << a - b << endl;
  return a - b;
}

float TestFunc(float a) {
  cout << a << endl;
  return a;
}

void Output() {
  // void fx
  cout << "Golbal fx (void)" << endl;
}

class CHanzo {
 public:
  CHanzo() { m_iTest = 10; }

  ~CHanzo() {}

 public:
  int m_iTest;

 public:
  void Output() {
    // "this" can be omitted.
    cout << "Member fx: " << this->m_iTest << endl;
  }
};

int main() {
  /* function pointer */

  int (*pFunc)(int, int) = Sum;
  cout << pFunc(10, 20) << endl;

  pFunc = OutSum;
  cout << pFunc(10, 20) << endl;

  void (*pFunc1)() = Output;
  pFunc1();

  /* creating some instances */

  CHanzo hanzo1, hanzo2;

  hanzo1.m_iTest = 100;
  hanzo2.m_iTest = 200;

  hanzo1.Output();
  hanzo2.Output();

  /* pointer to method */

  void (CHanzo::*pFunc2)() = &CHanzo::Output;

  (hanzo1.*pFunc2)();
  function<void()> func;
  function<void()> func1;

  /* c++11 function  */

  func = bind(Output);
  func1 = bind(&CHanzo::Output, &hanzo1);

  cout << "===== Functional =====" << endl;
  func();
  func1();

  function<int(int, int)> func3;
  function<float(float)> func4;

  // using placeholders
  func3 = bind(OutSum, placeholders::_1, placeholders::_2);
  func3(10, 20);
  func3 = bind(OutSum, placeholders::_2, placeholders::_1);
  func3(10, 20);

  func4 = bind(TestFunc, placeholders::_1);
  func4(2.14f);

  return 0;
}