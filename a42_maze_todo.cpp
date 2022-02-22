/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec42. Maze Game 5
https://www.youtube.com/watch?v=vl9cOaR-RjE&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=42
******************************************************************************/

// TODO: Debug this!!

#include <conio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

struct _tagPoint {
  int x;
  int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer {
  _tagPoint tPos;
  bool bWallPush;
  bool bPushOnOff;
  bool bTransparency;
  int iBombPower;
} PLAYER, *PPLAYER;

void SetMaze(char Maze[20][21], PPLAYER pPlayer, PPOINT pStartPos,
             PPOINT pEndPos) {
  pStartPos->x = 0;
  pStartPos->y = 0;

  pPlayer->tPos = *pStartPos;

  pEndPos->x = 19;
  pEndPos->y = 19;

  // 0: wall, 1: road, 2: start, 3: end, 4: bomb power
  // 5: push, 6: transparency, 7: worm hole
  strcpy(Maze[0], "21100000000000000000");
  strcpy(Maze[1], "00111111111100000000");
  strcpy(Maze[2], "00100010000111111100");
  strcpy(Maze[3], "01100010000000000100");
  strcpy(Maze[4], "01000011110001111100");
  strcpy(Maze[5], "0100000001111000000");
  strcpy(Maze[6], "01100000001000000000");
  strcpy(Maze[7], "00100000001111111000");
  strcpy(Maze[8], "00001111000000001000");
  strcpy(Maze[9], "01111001111111111000");
  strcpy(Maze[10], "01000000000000000000");
  strcpy(Maze[11], "01111100111111100000");
  strcpy(Maze[12], "00000111100000111110");
  strcpy(Maze[13], "01111100000000000010");
  strcpy(Maze[14], "01000000001111111110");
  strcpy(Maze[15], "01111110001000000000");
  strcpy(Maze[16], "00000010011000000000");
  strcpy(Maze[17], "01111110010000000000");
  strcpy(Maze[18], "01000000011111000000");
  strcpy(Maze[19], "11000000000001111113");
}

void Output(char Maze[20][21], PPLAYER pPlayer, int iBombCount) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (Maze[i][j] == '4') {
        cout << "B ";
      } else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i) {
        cout << "* ";
      } else if (Maze[i][j] == '0') {
        cout << "# ";
      } else if (Maze[i][j] == '1') {
        cout << "  ";
      } else if (Maze[i][j] == '2') {
        cout << "S ";
      } else if (Maze[i][j] == '3') {
        cout << "E ";
      } else if (Maze[i][j] == '4') {
        cout << "W ";
      } else if (Maze[i][j] == '5') {
        cout << "P ";
      } else if (Maze[i][j] == '6') {
        cout << "T ";
      }
    }
    cout << endl;
  }
  cout << endl << endl;

  cout << "Bomb Remained: " << iBombCount << ", ";
  cout << "Bomb Power: " << pPlayer->iBombPower << endl;

  cout << "Transparent: ";
  if (pPlayer->bTransparency)
    cout << "ON,  ";
  else
    cout << "OFF,  ";

  cout << "Wall Push: ";
  if (pPlayer->bWallPush) {
    cout << "Possible / ";
    if (pPlayer->bPushOnOff)
      cout << "ON,  " << endl;
    else
      cout << "OFF  " << endl;
  }
}

bool AddItem(char cItemType, PPLAYER pPlayer) {
  if (cItemType == '5') {
    if (pPlayer->iBombPower < 5) ++pPlayer->iBombPower;
    return true;
  } else if (cItemType == '6') {
    pPlayer->bWallPush = true;
    pPlayer->bPushOnOff = true;
    return true;
  } else if (cItemType == '7') {
    pPlayer->bTransparency = true;
    return true;
  }
  return false;
}

void MoveUp(char Maze[20][21], PPLAYER pPlayer) {
  if (pPlayer->tPos.y - 1 >= 0) {
    if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
        Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4') {
      --pPlayer->tPos.y;
    }
    // if possible wall pusing, above wall
    else if (pPlayer->bWallPush &&
             Maze[pPlayer->tPos.y][pPlayer->tPos.x] != '0') {
      // if wall push is ON state
      if (pPlayer->bPushOnOff) {
        // if two steps above is wall or road
        if (pPlayer->tPos.y - 2 >= 0) {
          // if two steps above is wall (can't push condition)
          if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0') {
            if (pPlayer->bTransparency) {
              --pPlayer->tPos.y;
            }
          }
          // if two steps above is road
          else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '1') {
            // make two steps above road into wall
            Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
            // make above wall into road
            Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
            // move player
            --pPlayer->tPos.y;
          }
        }
      }
      // if wall push is OFF state
      else if (pPlayer->bTransparency) {
        --pPlayer->tPos.y;
      }
    } else if (pPlayer->bTransparency) {
      --pPlayer->tPos.y;
    }

    if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
      Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
    }
  }
}

void MoveDown(char Maze[20][21], PPLAYER pPlayer) {
  if (pPlayer->tPos.y + 1 < 20) {
    if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
        Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4') {
      ++pPlayer->tPos.y;
    } else if (pPlayer->bTransparency) {
      ++pPlayer->tPos.y;
    }

    if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
      Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
    }
  }
}

void MoveLeft(char Maze[20][21], PPLAYER pPlayer) {
  if (pPlayer->tPos.x - 1 < 20) {
    if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
        Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4') {
      --pPlayer->tPos.x;
    } else if (pPlayer->bTransparency) {
      --pPlayer->tPos.x;
    }

    if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
      Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
    }
  }
}

void MoveRight(char Maze[20][21], PPLAYER pPlayer) {
  if (pPlayer->tPos.x + 1 < 20) {
    if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
        Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4') {
      ++pPlayer->tPos.x;
    } else if (pPlayer->bTransparency) {
      ++pPlayer->tPos.x;
    }

    if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
      Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
    }
  }
}

void MovePlayer(char Maze[20][21], PPLAYER pPlayer, char cInput) {
  switch (cInput) {
    case 'w':
    case 'W': {
      MoveUp(Maze, pPlayer);
    } break;
    case 's':
    case 'S': {
      MoveDown(Maze, pPlayer);
    } break;
    case 'a':
    case 'A': {
      MoveLeft(Maze, pPlayer);
    } break;
    case 'd':
    case 'D': {
      MoveRight(Maze, pPlayer);
    } break;
  }
}

void CreateBomb(char Maze[20][21], const PPLAYER pPlayer, PPOINT pBombArr,
                int* pBombCount) {
  if (*pBombCount == 5)
    return;
  else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0') {
    return;
  }

  for (int i = 0; i < *pBombCount; i++) {
    if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
      return;
    }
  }

  pBombArr[*pBombCount] = pPlayer->tPos;
  ++(*pBombCount);

  Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[20][21], PPLAYER pPlayer, PPOINT pBombArr,
          int* pBombCount) {
  for (int j = 1; j <= pPlayer->iBombPower; j++) {
    for (int i = 0; i < *pBombCount; i++) {
      // if player was hit by explosion
      if (pPlayer->tPos.x == pBombArr[i].x &&
          pPlayer->tPos.y == pBombArr[i].y) {
        pPlayer->tPos.x = 0;
        pPlayer->tPos.y = 0;
      }

      // When a bomb explodes, then it will vanish.
      Maze[pBombArr[i].y][pBombArr[i].x] = '1';

      // Upper-margin check
      if (pBombArr[i].y - j >= 0) {
        if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0') {
          // break walls above
          Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';

          // generate items randomly
          if (rand() % 100 < 20) {
            int iPercent = rand() % 100;
            if (iPercent < 80) {
              Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
            } else if (iPercent < 60) {
              Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
            } else
              Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
          }
        }

        // if player was hit by explosion
        if (pPlayer->tPos.x == pBombArr[i].x &&
            pPlayer->tPos.y == pBombArr[i].y - j) {
          pPlayer->tPos.x = 0;
          pPlayer->tPos.y = 0;
        }
      }

      // Lower-margin check
      if (pBombArr[i].y + 1 < 20) {
        if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0') {
          // break walls below
          Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';

          // generate items randomly
          if (rand() % 100 < 20) {
            int iPercent = rand() % 100;
            if (iPercent < 80) {
              Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
            } else if (iPercent < 60) {
              Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
            } else
              Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
          }
        }

        // if player was hit by explosion
        if (pPlayer->tPos.x == pBombArr[i].x &&
            pPlayer->tPos.y == pBombArr[i].y + j) {
          pPlayer->tPos.x = 0;
          pPlayer->tPos.y = 0;
        }
      }

      // Lt-margin check
      if (pBombArr[i].x - j >= 0) {
        if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0') {
          // break left walls
          Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';

          // generate items randomly
          if (rand() % 100 < 20) {
            int iPercent = rand() % 100;
            if (iPercent < 80) {
              Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
            } else if (iPercent < 60) {
              Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
            } else
              Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
          }
        }

        // if player was hit by explosion
        if (pPlayer->tPos.x == pBombArr[i].x - j &&
            pPlayer->tPos.y == pBombArr[i].y) {
          pPlayer->tPos.x = 0;
          pPlayer->tPos.y = 0;
        }
      }

      // Rt-margin check
      if (pBombArr[i].x + j < 20) {
        if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0') {
          // break right walls
          Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';

          // generate items randomly
          if (rand() % 100 < 20) {
            int iPercent = rand() % 100;
            if (iPercent < 80) {
              Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
            } else if (iPercent < 60) {
              Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
            } else
              Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
          }
        }

        // if player was hit by explosion
        if (pPlayer->tPos.x == pBombArr[i].x + j &&
            pPlayer->tPos.y == pBombArr[i].y) {
          pPlayer->tPos.x = 0;
          pPlayer->tPos.y = 0;
        }
      }
    }
  }
}

int main() {
  // radndom seed
  srand((unsigned int)time(0));

  // 20 * 20 maze
  //          ypos xpos
  char strMaze[20][21];

  PLAYER tPlayer = {};
  POINT tStarPos;
  POINT tEndPos;

  tPlayer.iBombPower = 1;
  int iBombCount = 0;
  POINT tBombPos[5];

  // create a maze
  SetMaze(strMaze, &tPlayer, &tStarPos, &tEndPos);

  while (true) {
    system("clear");
    Output(strMaze, &tPlayer, 5 - iBombCount);

    if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
      cout << "Game End" << endl;
      break;
    }

    cout << "t: Drop Bomb, u: Ignite Bomb, i: Wall Push" << endl;
    cout << "w: Up, s: Down, a: Left, d: Right (q: Quit)" << endl;
    cout << "Enter a Key: ";
    char cInput = getch();

    if (cInput == 'q' || cInput == 'Q')
      break;
    else if (cInput == 'b' || cInput == 'B') {
      CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
    } else if (cInput == 'e' || cInput == 'E') {
      Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
      iBombCount = 0;
    } else if (cInput == 'i' || cInput == 'I') {
      if (tPlayer.bWallPush) {
        tPlayer.bPushOnOff != tPlayer.bPushOnOff;
      }
    } else
      MovePlayer(strMaze, &tPlayer, cInput);
  }

  return 0;
}