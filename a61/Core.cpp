#include "Core.h"

#include "MapManager.h"

CCore* CCore::m_pInst = NULL;

CCore::CCore() {}

CCore::~CCore() { CMapManager::DestroyInst(); }

CCore* CCore::GetInst() {
  if (!m_pInst) m_pInst = new CCore;

  return m_pInst;
}

void CCore::DestroyInst() { SAFE_DELETE(m_pInst); }

bool CCore::Init() {
  if (!CMapManager::GetInst()->Init()) return false;

  return true;
}

void CCore::Run() {}
