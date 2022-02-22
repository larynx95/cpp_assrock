#pragma once

#include "value.h"

class CStage {
 public:
  CStage();
  ~CStage();

 private:
  char m_cStage[10][50];

 public:
  bool Init();
  bool Init(const char* pFileName);
  void Render();
};
