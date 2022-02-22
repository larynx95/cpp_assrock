#pragma once
#include "value.h"

class CPlayer {
 public:
  CPlayer(){};
  ~CPlayer(){};

 private:
  int m_iX;
  int m_iY;

 public:
  int GetX();
  int GetY();
  void SetPos(int x, int y);
  bool Init();
  void Update();
};
