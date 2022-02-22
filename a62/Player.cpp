#include "Player.h"

int CPlayer::GetX() { return m_iX; }

int CPlayer::GetY() { return m_iY; }

void CPlayer::SetPos(int x, int y) {
  m_iX = x;
  m_iY = y;
}

bool CPlayer::Init() {
  m_iX = 4;
  m_iY = 8;
  return true;
}

void CPlayer::Update() {
  if (GetAsyncKeyState('A') & 0x8000) {
    --m_iX;
    if (m_iX < 0) m_iX = 0;
  }
  if (GetAsyncKeyState('D') & 0x8000) {
    ++m_iX;
    if (m_iX >= 50) m_iX = 49;
  }
  if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
  }
}
