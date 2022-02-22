/**********************************************************
 * CPlayer
 *
 * class for CPlayer object
 *********************************************************/

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
  int m_iScore;
  bool m_bComplete;
  bool m_bBulletFire;
  bool m_bBigItem;

 public:
  int GetX();
  int GetY();
  void SetPos(int x, int y);
  int GetScore();
  bool GetComplete();
  bool GetBigItemEnable();
  bool Init();
  void Update();
  void Reset();
};
