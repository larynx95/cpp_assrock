#pragma once

#include "value.h"

/* Forward declaration */
class CStage;

class CMapManager {
 private:
  CMapManager();   // private constructor
  ~CMapManager();  // private destructor

 private:
  // static member variable
  // must be initialized outside the class
  static CMapManager* m_pInst;

  // m_pStage is an array of pointers to CStage type instances
  CStage* m_pStage[STAGE_MAX_COUNT];

  // member variable for selecting a Stage
  int m_iEnableStage;

 public:
  static CMapManager* GetInst();  // static method
  static void DestroyInst();      // static method

 public:
  CStage* GetStage();

 public:
  bool Init();
  void Run(int iStage);
  void Render();
};
