/**********************************************************
 * CCore
 *
 * class for core mechanism
 *********************************************************/

#pragma once

#include "value.h"

class CCore {
 private:
  CCore();   // private constructor
  ~CCore();  // private destructor

 private:
  static CCore* m_pInst;

 private:
  int OutputMenu();

 public:
  static CCore* GetInst();
  static void DestroyInst();

 public:
  bool Init();
  void Run();
};
