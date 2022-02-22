#include "Stage.h"

#include "FileStream.h"
#include "ObjectManager.h"
#include "Player.h"

CStage::CStage() {}

CStage::~CStage() {}

bool CStage::Init() { return true; }

bool CStage::Init(const char* pFileName) {
  CFileStream file;
  if (!file.Open(pFileName, "rt")) {
    return false;
  }

  for (int i = 0; i < BLOCK_Y; i++) {
    int iSize = 0;
    file.ReadLine(m_cStage[i], iSize);

    /*
    // print Stage
    for (int j = 0; j < BLOCK_X; ++j) {
      cout << m_cStage[i][j];
    }*/
  }
  return true;
}

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
      else if (m_cStage[i][j] == SBT_START)
        cout << "S ";
      else if (m_cStage[i][j] == SBT_END)
        cout << "E ";
      else if (m_cStage[i][j] == SBT_COIN)
        cout << "@ ";
    }
    cout << endl;
  }
}
