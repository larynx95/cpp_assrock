
#pragma once

#include <Windows.h>

#include <iostream>

using namespace std;

#define SAFE_DELETE(p) \
  if (p) {             \
    delete p;          \
    p = NULL;          \
  }

// Stage Max Count
#define STAGE_MAX_COUNT 3
#define JUMP_BLOCK_MAX 2
#define BLOCK_X 50
#define BLOCK_Y 10

enum STAGE_BLOCK_TYPE {
  SBT_WALL = '0',
  SBT_ROAD = '1',
  SBT_START = '2',
  SBT_END = '3',
  SBT_COIN = '4'
};

enum { JD_STOP, JD_UP, JD_DOWN };

static int InputInt() {
  int iInput;
  cin >> iInput;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    return INT_MAX;
  }
  return iInput;
}
