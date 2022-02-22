/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec33. Functions
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=33
******************************************************************************/

#include <string.h>
#include <time.h>

#include <iostream>

using namespace std;

int Sum(int a, int b) { return a + b; }

void OutputText() { cout << "Output: " << endl; }

void OutputText(int num) { cout << "Output: " << num << endl; }

int OutputText(int a, int b) {
  cout << "Side Effect" << endl;
  return a + b;
}

/* default value */
void Output(int iNum1, int iNum2 = 10) {
  cout << iNum1 << endl;
  cout << iNum2 << endl;
}

void Output(int iNum) { cout << iNum << endl; }

int main() {
  /* functions */

  cout << Sum(10, 20) << endl;

  /* function overloading - parametric polymorphism */

  OutputText();
  OutputText(1234);
  OutputText(10, 20);
  cout << OutputText(10, 20) << endl;

  /* lexical scope - global variable, local variable */

  {
    int iNum1 = 1234;
    // The value of iNum1 can only be used within this block.
  }

  /* default value*/

  // Output(10);  // more than two overloaded fx !! Error!!

  return 0;
}
