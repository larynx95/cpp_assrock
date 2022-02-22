#include "Player.h"

#include "MapManager.h"
#include "ObjectManager.h"
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

int CPlayer::GetScore() { return m_iScore; }

bool CPlayer::GetComplete() { return m_bComplete; }

/* Init */
bool CPlayer::Init() {
  m_tPos.x = 0;
  m_tPos.y = 8;
  m_bJump = false;
  m_iJumpDir = JD_STOP;
  m_iJumpState = 0;
  m_iScore = 0;
  m_bComplete = false;
  m_bBulletFire = false;
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
      if (m_tPos.x >= BLOCK_X) m_tPos.x = 49;
    }
  }

  // when press space bar
  if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump) {
    m_bJump = true;
    m_iJumpDir = JD_UP;
    m_iJumpState = 0;
  }

  // if space bar was pressed
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
          // break upper wall, get random item
          srand((unsigned int)time(0));
          int iRand = rand() % 100;
          STAGE_BLOCK_TYPE eBlockType;
          if (iRand < 90)
            eBlockType = SBT_ITEM_BULLET;
          else
            eBlockType = SBT_ITEM_BIG;

          pStage->ChangeBlock(m_tPos.x, m_tPos.y - 1, eBlockType);
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
        } else
          ++m_tPos.y;
      } break;
    }
  }

  if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) != SBT_WALL && !m_bJump) {
    ++m_tPos.y;
  }

  // take coins
  STAGE_BLOCK_TYPE eCurBlockType =
      (STAGE_BLOCK_TYPE)pStage->GetBlock(m_tPos.x, m_tPos.y);

  if (eCurBlockType == SBT_COIN) {
    pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
    m_iScore += 1000;
  } else if (eCurBlockType == SBT_ITEM_BULLET) {
    m_bBulletFire = true;
    pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
  } else if (pStage->GetBlock(m_tPos.x, m_tPos.y) == SBT_END) {
    m_bComplete = true;
  }

  // when player died
  if (m_tPos.y >= BLOCK_Y) {
    cout << "Player died." << endl;
    m_tPos = pStage->GetStart();
    m_iScore = 0;
    pStage->ResetStage();
    system("pause");
  }

  // fire bullet
  if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_bBulletFire) {
    CObjectManager::GetInst()->CreateBullet();
  }
}

void CPlayer::Reset() {
  m_bComplete = false;
  m_bBulletFire = false;
  m_iScore = 0;
}
