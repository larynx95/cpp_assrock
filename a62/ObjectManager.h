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
  // static methods
  static CObjectManager* GetInst() {
    if (!m_pInst) m_pInst = new CObjectManager;
    return m_pInst;
  }

  static void DestroyInst() { SAFE_DELETE(m_pInst); }

  // member functions
  bool Init();

  // TODO: What is this?
  class CPlayer* GetPlayer() {
    return m_pPlayer;
  }
};
