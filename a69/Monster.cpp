#include "Monster.h"

#include "MapManager.h"
#include "Stage.h"

/**********************************************************
 * constructor & destructor
 *********************************************************/

CMonster::CMonster() {}

CMonster::~CMonster() {}

/**********************************************************
 * getter & setter
 *********************************************************/

POINT CMonster::GetPos() { return m_tPos; }

void CMonster::SetPos(int x, int y) {
  m_tPos.x = x;
  m_tPos.y = y;
}

/**********************************************************
 * Init
 *********************************************************/

bool CMonster::Init() {
  m_tPos.x = 0;
  m_tPos.y = 0;
  m_iFrameCount = 0;

  m_iDir = -1;  // leftward
  m_iSpeed = 3;

  return true;
}

/**********************************************************
 * Update
 *********************************************************/

void CMonster::Update() {
  ++m_iFrameCount;
  if (m_iFrameCount == m_iSpeed) {
    m_iFrameCount = 0;

    CStage* pStage = CMapManager::GetInst()->GetStage();

    if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y + 1) != SBT_WALL) {
      m_iDir *= -1;  // change direction
    } else if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y) == SBT_WALL) {
      m_iDir *= -1;
    }

    m_tPos.x += m_iDir;
  }
}
