#pragma once
#include "Player.h"

class CObjectManager {
 private:
  CObjectManager();
  ~CObjectManager();

 private:
  static CObjectManager* m_pInst;

  // class forward declaration
  CPlayer* m_pPlayer;

 public:
  // static method
  static CObjectManager* GetInst();
  static void DestroyInst();
  bool Init();

 public:
  // TODO:forward declaration??
  class CPlayer* GetPlayer() {
    return m_pPlayer;
  }
};
