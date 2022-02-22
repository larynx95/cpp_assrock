
#include "Core.h"

/**********************************************************
 * main
 *********************************************************/

int main() {
  if (!CCore::GetInst()->Init()) {
    cout << "Initialization Failed!" << endl;
    CCore::DestroyInst();

    return 0;
  }

  CCore::GetInst()->Run();

  CCore::DestroyInst();

  return 0;
}
