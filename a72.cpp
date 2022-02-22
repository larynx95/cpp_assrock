/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec72. Template
https://www.youtube.com/watch?v=kMY49xIjKZo&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=72
******************************************************************************/

#include <iostream>

using namespace std;

template <typename T>
void OutputType() {
  cout << typeid(T).name() << endl;
}

template <typename T>
void OutputData(T data) {
  cout << "Output Data: " << endl;
  cout << typeid(T).name() << " - ";
  cout << data << endl;
}

typedef struct _tagStudent {
} STUDENT, *PSTUDENT;

class CTemplate {
 public:
  CTemplate() {}
  ~CTemplate() {}

 public:
  template <class T, class T1>
  void Output(T a, T1 b) {
    cout << a << endl;
    cout << b << endl;
  }
};

template <typename T>
class CTemplate1 {
 public:
  CTemplate1() { cout << "Template1 class type: " << typeid(T).name() << endl; }
  ~CTemplate1() {}

 private:
  T m_Data;

 public:
  void Output() {
    cout << typeid(T).name() << endl;
    cout << m_Data << endl;
  }
};

class CCar {
  CCar() {}
  ~CCar() {}
};

int main() {
  OutputType<int>();      // i
  OutputType<float>();    // f
  OutputType<STUDENT>();  // 11_tagStudent
  OutputType<CCar>();     // 4CCar

  OutputData(10);     // i - 10
  OutputData(10.3);   // d - 10.3
  OutputData('a');    // c - a
  OutputData("abc");  // PKc - abc

  CTemplate tem;
  tem.Output(10, 3.14f);  // 10  3.14

  CTemplate1<int> tem1;
  tem1.Output();

  CTemplate1<CTemplate> temp2;

  return 0;
}