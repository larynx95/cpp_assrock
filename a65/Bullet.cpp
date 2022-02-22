#include "Bullet.h"

CBullet::CBullet() {}

CBullet::~CBullet() {}

void CBullet::SetPos(int x, int y) {
  m_tPos.x = x;
  m_tPos.y = y;
}

POINT CBullet::GetPos() { return m_tPos; }
