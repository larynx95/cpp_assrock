#include "Core.h"

#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

/**********************************************************
 * initializing static member variable
 *********************************************************/

CCore* CCore::m_pInst = NULL;

/**********************************************************
 * constructor & destructor
 *********************************************************/

CCore::CCore() { srand((unsigned int)time(0)); }

CCore::~CCore() {
  CMapManager::DestroyInst();
  CObjectManager::DestroyInst();
}

/**********************************************************
 * getter & setter
 *********************************************************/

CCore* CCore::GetInst() {
  if (!m_pInst) m_pInst = new CCore;

  return m_pInst;
}

/**********************************************************
 * DestroyInst - destroy instance
 *********************************************************/

void CCore::DestroyInst() { SAFE_DELETE(m_pInst); }

/**********************************************************
 * Init - initialize instance
 *********************************************************/

bool CCore::Init() {
  // initialize CMapManager instance
  if (!CMapManager::GetInst()->Init()) return false;

  // initiialize CObjectManager instance
  if (!CObjectManager::GetInst()->Init()) return false;

  return true;
}

/**********************************************************
 * Run
 *********************************************************/

void CCore::Run() {
  while (true) {
    int iStage = OutputMenu();

    if (iStage == 4)
      break;
    else if (iStage == 0)
      continue;

    CMapManager::GetInst()->Run(iStage - 1);
  }
}

/**********************************************************
 * OutputMenu
 *********************************************************/

int CCore::OutputMenu() {
  system("cls");
  cout << "1. Stage 01" << endl;
  cout << "2. Stage 02" << endl;
  cout << "3. Stage 03" << endl;
  cout << "4. Exit" << endl;
  cout << "Select stage: ";
  int iInput = InputInt();

  if (iInput < 1 || iInput > 4) return 0;

  return iInput;
}
