#pragma once

#include "value.h"

class CStage {
 public:
  CStage();   // constructor
  ~CStage();  // destructor

 private:
  char m_cStage[BLOCK_Y][BLOCK_X];  // map
  POINT m_tStart;
  POINT m_tEnd;

 public:
  POINT GetStart();
  POINT GetEnd();
  char GetBlock(int x, int y);
  bool Init();
  bool Init(const char* pFileName);
  void Render();
};
