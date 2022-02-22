#include "MapManager.h"

#include "ObjectManager.h"
#include "Player.h"
#include "Stage.h"

/* initialize static member variable */
CMapManager* CMapManager::m_pInst = NULL;

/* constructor */
CMapManager::CMapManager() {
  for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
    m_pStage[i] = NULL;
  }
}

/* destructor */
CMapManager::~CMapManager() {
  for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
    SAFE_DELETE(m_pStage[i]);
  }
}

/* GetInst
 * get new instance of CMapManager class
 */
CMapManager* CMapManager::GetInst() {
  // unless an instance was already created
  if (!m_pInst) m_pInst = new CMapManager;
  return m_pInst;
}

/* DestroyInst
 * destroy instance
 */
void CMapManager::DestroyInst() { SAFE_DELETE(m_pInst); }

CStage* CMapManager::GetStage() { return m_pStage[m_iEnableStage]; }

/* Init
 * Initialize
 */
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

void CMapManager::Run(int iStage) {
  CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
  m_iEnableStage = iStage;

  m_pStage[iStage]->ResetStage();

  pPlayer->SetPos(m_pStage[iStage]->GetStart().x,
                  m_pStage[iStage]->GetStart().y);

  while (true) {
    system("cls");

    if (GetAsyncKeyState('Q') & 0x8000) break;

    pPlayer->Update();
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

void CMapManager::Render() { m_pStage[0]->Render(); }
