#include "Stage.h"

#include "FileStream.h"
#include "ObjectManager.h"
#include "Player.h"

/**********************************************************
 * constructor & destructor
 *********************************************************/

CStage::CStage() {}

CStage::~CStage() {}

/**********************************************************
 * GetStart
 *********************************************************/

POINT CStage::GetStart() { return m_tStart; }

/**********************************************************
 * GetEnd
 *********************************************************/

POINT CStage::GetEnd() { return m_tEnd; }

/**********************************************************
 * GetBlock
 *********************************************************/

char CStage::GetBlock(int x, int y) { return m_cStage[y][x]; }

/**********************************************************
 * ChangeBlock
 *********************************************************/

void CStage::ChangeBlock(int x, int y, STAGE_BLOCK_TYPE eBlock) {
  m_cStage[y][x] = eBlock;
}

/**********************************************************
 * Init
 *********************************************************/

/* initialize Stage map */
bool CStage::Init() { return true; }

/* Init
 * initialize Stage map (overloaded with one argument)
 * read a Stage text file, then create a 2-D char array
 */
bool CStage::Init(const char* pFileName) {
  CFileStream file;

  if (!file.Open(pFileName, "rt")) {
    return false;
  }

  for (int i = 0; i < BLOCK_Y; i++) {
    int iSize = 0;
    file.ReadLine(m_cOriginStage[i], iSize);

    for (int j = 0; j < 50; ++j) {
      m_cStage[i][j] = m_cOriginStage[i][j];
      if (m_cOriginStage[i][j] == SBT_START) {
        m_tStart.x = j;
        m_tStart.y = i;
      } else if (m_cOriginStage[i][j] == SBT_END) {
        m_tEnd.x = j;
        m_tEnd.y = i;
      }
    }
  }

  return true;
}

/**********************************************************
 * Render
 *********************************************************/

void CStage::Render() {
  CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

  int iX = pPlayer->GetX();
  int iY = pPlayer->GetY();

  // display cropped Stage on the screen
  int iYCount = iY + (RENDER_BLOCK_Y / 2);
  if (iYCount >= BLOCK_Y) {
    iYCount = BLOCK_Y - 1;
  }

  int iXCount = iX + RENDER_BLOCK_X;
  if (iXCount >= BLOCK_X) {
    iXCount = BLOCK_X;
  }

  for (int i = iYCount - (RENDER_BLOCK_Y - 1); i <= iYCount; ++i) {
    int iXMin = iX;

    if (iXMin > BLOCK_X - RENDER_BLOCK_X) {
      iXMin = BLOCK_X - RENDER_BLOCK_X;
    }

    for (int j = iX; j < iXCount; ++j) {
      if ((i == iY || i == iY - 1 && pPlayer->GetBigItemEnable()) && j == iX)
        cout << "$ ";
      else if (CObjectManager::GetInst()->CheckBullet(j, i)) {
        cout << "x ";
      } else if (m_cStage[i][j] == SBT_WALL)
        cout << "# ";
      else if (m_cStage[i][j] == SBT_ROAD)
        cout << "  ";
      else if (m_cStage[i][j] == SBT_START) {
        cout << "S ";
      } else if (m_cStage[i][j] == SBT_END) {
        cout << "E ";
      } else if (m_cStage[i][j] == SBT_COIN)
        cout << "@ ";
      else if (m_cStage[i][j] == SBT_ITEM_BULLET) {
        cout << "G ";
      } else if (m_cStage[i][j] == SBT_ITEM_BIG)
        cout << "B ";
    }
    cout << endl;
  }
}

/**********************************************************
 * ResetStage
 *********************************************************/

void CStage::ResetStage() {
  for (int i = 0; i < BLOCK_Y; ++i) {
    for (int j = 0; j < BLOCK_X; ++j) {
      m_cStage[i][j] = m_cOriginStage[i][j];
    }
  }
}
