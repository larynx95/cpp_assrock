/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec51. File IO
https://www.youtube.com/watch?v=kaD1Jl_7BBo&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=51
******************************************************************************/

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

void Test(int** pp) {
  //
  *pp = new int;
}

int main() {
  /*
           dptr     ptr      var
  name   : pp       p        a
  value  : 0x02     0x01     100 (integer)
  (deref)           *pp      *p
  Address: 0x03     0x02     0x01
  */

  // int* p = NULL;
  // p = new int;
  // Test(&p);

  /* fopen, fopen_s function
  - arg1: double pointer
  - arg2: file path as string
  - arg3: file mode r/w/a, t/b
  */

  FILE* pFile = NULL;
  pFile = fopen("hot.txt", "wt");

  if (pFile != NULL) {
    // fread, fread, fputs, fgets
    const char* pText = "abcd";

    /* fwrite function
    - arg1: memory address
    - arg2: memory size of variable type
    - arg3: the number of values
    - arg4: file stream
    */

    fwrite(pText, 1, 4, pFile);
    fclose(pFile);
    cout << "Success" << endl;
  }

  /* fread function */

  pFile = fopen("hot.txt", "rt");
  if (pFile) {
    char strText[5] = {};
    fread(strText, 1, 4, pFile);
    cout << strText << endl;
    fclose(pFile);
  }

  return 0;
}