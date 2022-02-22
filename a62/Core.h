#pragma once

#include "value.h"

class CCore {
 private:
  CCore();
  ~CCore();

 private:
  static CCore* m_pInst;

 public:
  static CCore* GetInst();
  static void DestroyInst();

 public:
  bool Init();

  void Run();
};
