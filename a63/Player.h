#pragma once
#include "value.h"

class CPlayer {
 public:
  CPlayer();   // constructor
  ~CPlayer();  // destructor

 private:
  POINT m_tPos;
  bool m_bJump;
  int m_iJumpDir;
  int m_iJumpState;

 public:
  int GetX();
  int GetY();
  void SetPos(int x, int y);
  bool Init();
  void Update();
};
