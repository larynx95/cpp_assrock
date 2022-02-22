/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec31. Pointer
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=31
******************************************************************************/

#include <string.h>
#include <time.h>

#include <iostream>

using namespace std;

struct _tagStudent {
  int iKor;
  int iEng;
  int iMath;
  int iTotal;
  float fAvg;
};

int main() {
  /* character pointer, string literal, const

  StackOverflow: const char * const versus const char *?
  https://stackoverflow.com/questions/4949254/const-char-const-versus-const-char

  const char * str : can't change the value of variable
                     which the pointer is pointing
  char const * str : can't change the value of the pointer
  const char const * str : both

  char* STR            : I can change which char STR points to,
                         and I can modify the char to which it points.

  const char* STR      : I can change which char STR points to,
                         but I cannot modify the char to which it points.

  char* const STR      : I cannot change which char STR points to,
                         but I can modify the char to which it points.

  const char* const STR: I cannot change which char STR points to,
                         nor can I modify the char to which it points.
  */

  const char *pText = "text line";  // string literal, immutable
  cout << pText << endl;
  cout << (int *)pText << endl;

  pText = "abcd";
  cout << pText << endl;
  cout << (int *)pText << endl;

  pText = "abcdef";
  cout << pText << endl;
  cout << (int *)pText << endl;

  /* pointer to structure */

  _tagStudent tStudent = {};
  _tagStudent *pStudent = &tStudent;

  tStudent.iKor = 100;

  (*pStudent).iKor = 50;
  cout << tStudent.iKor << endl;

  pStudent->iKor = 80;
  cout << tStudent.iKor << endl;

  /* void pointer
  Dereferencing is not allowed.
  */

  int iNum = 100;
  void *pVoid = &iNum;
  cout << "Address of iNum: " << pVoid << endl;

  // void pointer should be type-converted
  // before it is assigned to another pointer variable.
  int *pConvert = (int *)pVoid;
  *pConvert = 10101010;

  return 0;
}
