#include "Monster.h"

#include "MapManager.h"
#include "Stage.h"

CMonster::CMonster() {}

CMonster::~CMonster() {}

POINT CMonster::GetPos() { return m_tPos; }

void CMonster::SetPos(int x, int y) {
  m_tPos.x = x;
  m_tPos.y = y;
}

bool CMonster::Init() {
  m_tPos.x = 0;
  m_tPos.y = 0;

  m_iDir = -1;  // leftward

  return true;
}

void CMonster::Update() {
  CStage* pStage = CMapManager::GetInst()->GetStage();

  if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y + 1) != SBT_WALL) {
    m_iDir *= -1;  // change direction
  } else if (pStage->GetBlock(m_tPos.x + m_iDir, m_tPos.y) == SBT_WALL) {
    m_iDir *= -1;
  }

  m_tPos.x += m_iDir;
}
