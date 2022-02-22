#include "Player.h"

#include "MapManager.h"
#include "Stage.h"

/* constructor */
CPlayer::CPlayer() {}

/* destructor */
CPlayer::~CPlayer() {}

/* getter methods for getting x, y coordinates */
int CPlayer::GetX() { return m_tPos.x; }
int CPlayer::GetY() { return m_tPos.y; }

/* setter */
void CPlayer::SetPos(int x, int y) {
  m_tPos.x = x;
  m_tPos.y = y;
}

/* Init */
bool CPlayer::Init() {
  m_tPos.x = 0;
  m_tPos.y = 8;
  m_bJump = false;
  m_iJumpDir = JD_STOP;
  m_iJumpState = 0;
  return true;
}

/* Update */
void CPlayer::Update() {
  CStage* pStage = CMapManager::GetInst()->GetStage();
  // when press 'A'
  if (GetAsyncKeyState('A') & 0x8000) {
    if (pStage->GetBlock(m_tPos.x - 1, m_tPos.y) != SBT_WALL) {
      --m_tPos.x;
      if (m_tPos.x < 0) m_tPos.x = 0;
    }
  }

  // when press 'D'
  if (GetAsyncKeyState('D') & 0x8000) {
    if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL) {
      ++m_tPos.x;
      if (m_tPos.x >= 50) m_tPos.x = 49;
    }
  }

  // when press space bar
  if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump) {
    m_bJump = true;
    m_iJumpDir = JD_UP;
    m_iJumpState = 0;
  }

  if (m_bJump) {
    CStage* pStage = CMapManager::GetInst()->GetStage();
    switch (m_iJumpDir) {
      // if player jumps
      case JD_UP: {
        // increase jump height
        ++m_iJumpState;

        // if jump height is max
        if (m_iJumpState > JUMP_BLOCK_MAX) {
          m_iJumpState = JUMP_BLOCK_MAX;
          m_iJumpDir = JD_DOWN;
        } else if (pStage->GetBlock(m_tPos.x, m_tPos.y - 1) == SBT_WALL) {
          --m_iJumpState;
          m_iJumpDir = JD_DOWN;
        } else {
          --m_tPos.y;
        }
      } break;
      case JD_DOWN: {
        if (m_tPos.y >= BLOCK_Y) {
          cout << "Player died." << endl;
          system("pause");
          m_tPos.y = BLOCK_Y - 1;
        } else if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) == SBT_WALL) {
          m_iJumpDir = JD_STOP;
          m_bJump = false;
        } else {
          ++m_tPos.y;
        }
      } break;
    }
  }

  //
}
