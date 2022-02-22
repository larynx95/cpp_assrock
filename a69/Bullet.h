/**********************************************************
 * CBullet
 *
 * class for CBullet object
 *********************************************************/

#pragma once

#include "MapManager.h"
#include "Monster.h"
#include "Stage.h"
#include "value.h"

class CBullet {
 public:
  CBullet();   // constructor
  ~CBullet();  // destructor

 private:
  POINT m_tPos;  // position of a bullet
  int m_iDist;   // distance

 public:
  POINT GetPos();             // getter
  void SetPos(int x, int y);  // setter
  bool GetEnable();
  bool Init();    // initialize instance
  void Update();  // update position of bullet
};
