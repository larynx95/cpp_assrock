/**********************************************************
 * CMonster
 *
 * class for Monster
 *********************************************************/

#pragma once

#include "value.h"

class CMonster {
 public:
  CMonster();
  ~CMonster();

 private:
  POINT m_tPos;
  int m_iDir;  // movement direction
  int m_iSpeed;
  int m_iFrameCount;

 public:
  POINT GetPos();
  void SetPos(int x, int y);
  bool Init();
  void Update();
};
