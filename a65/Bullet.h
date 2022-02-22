#pragma once

#include "value.h"

class CBullet {
 public:
  CBullet();
  ~CBullet();

 private:
  POINT m_tPos;

 public:
  void SetPos(int x, int y);
  POINT GetPos();
  bool Init();
  void Update();
};
