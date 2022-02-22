#include "ObjectManager.h"

#include "Bullet.h"
#include "Player.h"

/**********************************************************
 * initializing static member variable
 *********************************************************/

CObjectManager* CObjectManager::m_pInst = NULL;

/**********************************************************
 * constructor & destructor
 *********************************************************/

CObjectManager::CObjectManager() { m_pPlayer = NULL; }

CObjectManager::~CObjectManager() {
  SAFE_DELETE(m_pPlayer);
  for (int i = 0; i < m_iCurBulletCount; ++i) {
    SAFE_DELETE(m_pBullet[i]);  // m_pBullet is "ptr array" to CBullet type
  }
}

/**********************************************************
 * Init
 *********************************************************/

bool CObjectManager::Init() {
  m_pPlayer = new CPlayer;
  m_pPlayer->Init();

  // initialize ptr array to zero all at once
  memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX);
  m_iCurBulletCount = 0;

  return true;
}

/**********************************************************
 * Update
 *********************************************************/

void CObjectManager::Update() {
  // a. update player
  m_pPlayer->Update();  // <-- from CMapManager

  // b. update bullets
  for (int i = 0; i < m_iCurBulletCount; ++i) {
    m_pBullet[i]->Update();
  }

  // bullet distance
  for (int i = 0; i < m_iCurBulletCount;) {
    if (!m_pBullet[i]->GetEnable()) {
      delete m_pBullet[i];
      for (int j = i; j < m_iCurBulletCount - 1; ++j) {
        m_pBullet[j] = m_pBullet[j + 1];
      }

      // set the Bullet with the last index to NULL
      m_pBullet[m_iCurBulletCount - 1] = NULL;
      --m_iCurBulletCount;
    } else {
      ++i;
    }
  }
}

/**********************************************************
 * CreateBullet
 *********************************************************/

bool CObjectManager::CreateBullet(POINT tPos) {
  // if already max bullets
  if (m_iCurBulletCount == BULLET_COUNT_MAX) return false;

  // create CBullet instance
  CBullet* pBullet = new CBullet;

  // initialize CBullet instance
  if (!pBullet->Init()) {
    SAFE_DELETE(pBullet);
    return false;
  }

  pBullet->SetPos(tPos.x, tPos.y);

  m_pBullet[m_iCurBulletCount] = pBullet;
  ++m_iCurBulletCount;

  return true;
}

/**********************************************************
 * CheckBullet
 *********************************************************/

bool CObjectManager::CheckBullet(int x, int y) {
  for (int i = 0; i < m_iCurBulletCount; ++i) {
    if (m_pBullet[i]->GetPos().x == x && m_pBullet[i]->GetPos().y == y) {
      return true;
    }
  }

  return false;
}

/**********************************************************
 * GetInst
 *********************************************************/

CObjectManager* CObjectManager::GetInst() {
  if (!m_pInst) m_pInst = new CObjectManager;
  return m_pInst;
}

/**********************************************************
 * DestroyInst
 *********************************************************/

void CObjectManager::DestroyInst() { SAFE_DELETE(m_pInst); }
