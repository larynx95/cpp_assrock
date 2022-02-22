#include "Stage.h"

#include "FileStream.h"
#include "ObjectManager.h"
#include "Player.h"

/* constructor */
CStage::CStage() {}

/* destructor */
CStage::~CStage() {}

POINT CStage::GetStart() { return m_tStart; }

POINT CStage::GetEnd() { return m_tEnd; }

char CStage::GetBlock(int x, int y) { return m_cStage[y][x]; }

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
    file.ReadLine(m_cStage[i], iSize);

    for (int j = 0; j < 50; ++j) {
      if (m_cStage[i][j] == SBT_START) {
        m_tStart.x = j;
        m_tStart.y = i;
      } else if (m_cStage[i][j] == SBT_END) {
        m_tEnd.x = j;
        m_tEnd.y = i;
      }
    }
  }

  return true;
}

/* Render
 * render a cropped screen
 */
void CStage::Render() {
  CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

  int iX = pPlayer->GetX();
  int iY = pPlayer->GetY();

  // display cropped Stage on the screen
  for (int i = iY - 2; i <= iY + 1; ++i) {
    for (int j = iX; j < iX + 10; ++j) {
      if (i == iY && j == iX)
        cout << "$ ";
      else if (m_cStage[i][j] == SBT_WALL)
        cout << "# ";
      else if (m_cStage[i][j] == SBT_ROAD)
        cout << "  ";
      else if (m_cStage[i][j] == SBT_START) {
        cout << "S ";
      } else if (m_cStage[i][j] == SBT_END) {
        cout << "E ";
      } else if (m_cStage[i][j] == SBT_COIN)
        cout << "@ ";
    }
    cout << endl;
  }
}
