#pragma once
#include "Player.h"

class CObjectManager {
 private:
  CObjectManager();
  ~CObjectManager();

 private:
  static CObjectManager* m_pInst;

  // class forward declaration
  class CPlayer* m_pPlayer;
  class CBullet* m_pBullet[BULLET_COUNT_MAX];
  int m_iCurBulletCount;

 public:
  // static method
  static CObjectManager* GetInst();
  static void DestroyInst();
  bool Init();
  bool CreateBullet();

 public:
  // TODO:forward declaration??
  class CPlayer* GetPlayer() {
    return m_pPlayer;
  }
};
