#include "ObjectManager.h"

#include "Player.h"

/* initialize static member variable */
CObjectManager* CObjectManager::m_pInst = NULL;

/* constructor */
CObjectManager::CObjectManager() { m_pPlayer = NULL; }

/* destructor */
CObjectManager::~CObjectManager() { SAFE_DELETE(m_pPlayer); }

/* Init */
bool CObjectManager::Init() {
  m_pPlayer = new CPlayer;
  m_pPlayer->Init();
  return true;
}

/* GetInst */
CObjectManager* CObjectManager::GetInst() {
  if (!m_pInst) m_pInst = new CObjectManager;
  return m_pInst;
}

/* DestroyInst */
void CObjectManager::DestroyInst() { SAFE_DELETE(m_pInst); }
