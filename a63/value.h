
#pragma once

#include <Windows.h>

#include <iostream>

using namespace std;

// macro for freeing memory space
#define SAFE_DELETE(p) \
  if (p) {             \
    delete p;          \
    p = NULL;          \
  }

#define STAGE_MAX_COUNT 3  // the maximum number of stages
#define JUMP_BLOCK_MAX 2   // the maximum jump height
#define BLOCK_X 50         // width of stage map
#define BLOCK_Y 10         // height of stage map

enum STAGE_BLOCK_TYPE {
  // enum for displaying map with symbols
  SBT_WALL = '0',
  SBT_ROAD = '1',
  SBT_START = '2',
  SBT_END = '3',
  SBT_COIN = '4'
};

enum {
  // enum for direction of jump
  JD_STOP,
  JD_UP,
  JD_DOWN
};

// get user input (integer value)
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
