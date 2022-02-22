/**********************************************************
 * CObjectManager
 *
 * class for managing objects (CPlayer, CBullet)
 *********************************************************/

#pragma once
#include "Player.h"

class CObjectManager {
 private:
  CObjectManager();
  ~CObjectManager();

 private:
  static CObjectManager* m_pInst;  // static member variable

  // class forward declaration
  class CPlayer* m_pPlayer;                    // ptr pointing to CPlayer
  class CBullet* m_pBullet[BULLET_COUNT_MAX];  // ptr array pointing to CBullet

  int m_iCurBulletCount;  // current number of bullets

 public:
  // static method
  static CObjectManager* GetInst();
  static void DestroyInst();

  // methods
  bool Init();
  void Update();
  bool CreateBullet(POINT tPos);
  bool CheckBullet(int x, int y);

 public:
  // TODO:forward declaration??
  class CPlayer* GetPlayer() {
    return m_pPlayer;
  }
};
