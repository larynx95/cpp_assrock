#include "Stage.h"

#include "FileStream.h"

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

    for (int j = 0; j < BLOCK_X; ++j) {
      cout << m_cStage[i][j];
    }
    cout << endl;
  }
  cout << endl;

  return true;
}
