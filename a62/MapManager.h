#pragma once

#include "value.h"

class CStage;
class CMapManager {
 private:
  CMapManager();
  ~CMapManager();

 private:
  static CMapManager* m_pInst;
  CStage* m_pStage[STAGE_MAX_COUNT];

 public:
  static CMapManager* GetInst();
  static void DestroyInst();

 public:
  bool Init();
  void Run();
  void Render();
};
