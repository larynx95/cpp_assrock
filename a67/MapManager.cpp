#include "MapManager.h"

#include "ObjectManager.h"
#include "Player.h"
#include "Stage.h"

/**********************************************************
 * initializing static member variable
 *********************************************************/

CMapManager* CMapManager::m_pInst = NULL;

/**********************************************************
 * constructor & destructor
 *********************************************************/

CMapManager::CMapManager() {
  for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
    m_pStage[i] = NULL;
  }
}

CMapManager::~CMapManager() {
  for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
    SAFE_DELETE(m_pStage[i]);
  }
}

/**********************************************************
 * GetInst
 *********************************************************/

CMapManager* CMapManager::GetInst() {
  // unless an instance was already created
  if (!m_pInst) m_pInst = new CMapManager;
  return m_pInst;
}

/**********************************************************
 * DestroyInst
 *********************************************************/

void CMapManager::DestroyInst() { SAFE_DELETE(m_pInst); }

/**********************************************************
 * GetStage
 *********************************************************/

CStage* CMapManager::GetStage() { return m_pStage[m_iEnableStage]; }

/**********************************************************
 * Init
 *********************************************************/

bool CMapManager::Init() {
  // array of names of Stage maps
  const char* pStageFile[3] = {"Stage1.txt", "Stage1.txt", "Stage1.txt"};

  // initialize CStage instances
  for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
    m_pStage[i] = new CStage;

    if (!m_pStage[i]->Init(pStageFile[i])) return false;
  }

  return true;
}

/**********************************************************
 * Run
 *********************************************************/

void CMapManager::Run(int iStage) {
  CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
  m_iEnableStage = iStage;

  m_pStage[iStage]->ResetStage();

  pPlayer->SetPos(m_pStage[iStage]->GetStart().x,
                  m_pStage[iStage]->GetStart().y);

  while (true) {
    system("cls");

    if (GetAsyncKeyState('Q') & 0x8000) break;

    CObjectManager::GetInst()->Update();
    // pPlayer->Update();  // --> move to CObjectmanager
    m_pStage[iStage]->Render();
    cout << "Score: " << pPlayer->GetScore() << endl;

    if (pPlayer->GetComplete()) {
      cout << "Complete!" << endl;
      pPlayer->Reset();
      break;
    }

    Sleep(100);
  }
}

/**********************************************************
 * Render
 *********************************************************/

void CMapManager::Render() { m_pStage[0]->Render(); }
