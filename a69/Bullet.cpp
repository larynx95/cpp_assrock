#include "Bullet.h"

/**********************************************************
 * constructor & destructor
 *********************************************************/

CBullet::CBullet() {}
CBullet::~CBullet() {}

/**********************************************************
 * getter & setter
 *********************************************************/

POINT CBullet::GetPos() { return m_tPos; }

void CBullet::SetPos(int x, int y) {
  m_tPos.x = x;
  m_tPos.y = y;
}

/**********************************************************
 * GetEnable
 *********************************************************/

bool CBullet::GetEnable() {
  // if not zero, bullet can move rightward
  return m_iDist != 0;
}

/**********************************************************
 * Init - initializer
 *********************************************************/

bool CBullet::Init() {
  m_tPos.x = 0;
  m_tPos.y = 0;
  m_iDist = 8;
  return true;
}

/**********************************************************
 * Update - update position of bullet
 *********************************************************/

void CBullet::Update() {
  CStage* pStage = CMapManager::GetInst()->GetStage();

  // get the position where a bullet should be
  POINT tNextPos = m_tPos;
  tNextPos.x++;

  // check if Bullet and Monster are in the same position
  for (int i = 0; i < pStage->GetMonsterCount(); ++i) {
    CMonster* pMonster = pStage->GetMonster(i);

    POINT tMonsterPos = pMonster->GetPos();
    if (tMonsterPos.x == m_tPos.x && tMonsterPos.y == m_tPos.y ||
        tMonsterPos.x == tNextPos.x && tMonsterPos.y == tNextPos.y) {
      // delete the Monster in the array
      pStage->DeleteMonster(i);

      // delete the Bullet
      m_iDist = 0;
      return;
    }
  }

  // bullet can't go through the wall
  if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL) {
    // move a bullet to the right
    m_tPos.x++;
    --m_iDist;
  } else {
    m_iDist = 0;
  }
}
