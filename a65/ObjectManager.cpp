#include "ObjectManager.h"

#include "Bullet.h"
#include "Player.h"

/* initialize static member variable */
CObjectManager* CObjectManager::m_pInst = NULL;

/* constructor */
CObjectManager::CObjectManager() { m_pPlayer = NULL; }

/* destructor */
CObjectManager::~CObjectManager() {
  SAFE_DELETE(m_pPlayer);
  for (int i = 0; i < m_iCurBulletCount; ++i) {
    SAFE_DELETE(m_pBullet[i]);
  }
}

/* Init */
bool CObjectManager::Init() {
  m_pPlayer = new CPlayer;
  m_pPlayer->Init();

  // initialize memory
  memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX);
  m_iCurBulletCount = 0;

  return true;
}

bool CObjectManager::CreateBullet() {
  if (m_iCurBulletCount == BULLET_COUNT_MAX) return false;

  CBullet* pBullet = new CBullet;

  if (!pBullet->Init()) {
    SAFE_DELETE(pBullet);
    return false;
  }

  m_pBullet[m_iCurBulletCount] = pBullet;
  ++m_iCurBulletCount;

  return true;
}

/* GetInst */
CObjectManager* CObjectManager::GetInst() {
  if (!m_pInst) m_pInst = new CObjectManager;
  return m_pInst;
}

/* DestroyInst */
void CObjectManager::DestroyInst() { SAFE_DELETE(m_pInst); }
