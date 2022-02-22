/**********************************************************
 * CStage
 *
 * class for Stage map
 *********************************************************/

#pragma once

#include "value.h"

class CStage {
 public:
  CStage();   // constructor
  ~CStage();  // destructor

 private:
  char m_cOriginStage[BLOCK_Y][BLOCK_X];  // map
  char m_cStage[BLOCK_Y][BLOCK_X];        // map
  POINT m_tStart;
  POINT m_tEnd;
  class CMonster** m_pMonsterArray;  // TODO: dynamic pointer array
  int m_iMonsterArrayCount;          // array size
  int m_iMonsterCount;

 public:
  POINT GetStart();
  POINT GetEnd();
  char GetBlock(int x, int y);
  void ChangeBlock(int x, int y, STAGE_BLOCK_TYPE eBlock);
  bool Init();
  bool Init(const char* pFileName);
  void Update();
  void Render();
  void ResetStage();
  class CMonster* CreateMonster(int x, int y);
  bool CheckMonster(int x, int y);
  int GetMonsterCount();
  class CMonster* GetMonster(int idx);
  void DeleteMonster(int idx);
};
