/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec40. Maze Game 3
https://www.youtube.com/watch?v=Sa25EQQMapE&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=40
******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define KEY_UP 24
#define KEY_DOWN 25
#define KEY_LEFT 27
#define KEY_RIGHT 26

struct _tagPoint {
  int x;
  int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

void SetMaze(char Maze[20][21], PPOINT pPlayerPos, PPOINT pStartPos,
             PPOINT pEndPos) {
  pStartPos->x = 0;
  pStartPos->y = 0;

  *pPlayerPos = *pStartPos;

  pEndPos->x = 19;
  pEndPos->y = 19;

  // 0: wall, 1: road, 2: start, 3: end, 4: bomb
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

void Output(char Maze[20][21], PPOINT pPlayerPos, int iBombCount) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 21; j++) {
      if (Maze[i][j] == '4') {
        cout << "☢ ";
      } else if (pPlayerPos->x == j && pPlayerPos->y == i) {
        cout << "P ";
      } else if (Maze[i][j] == '0') {
        cout << "▉ ";
      } else if (Maze[i][j] == '1') {
        cout << "  ";
      } else if (Maze[i][j] == '2') {
        cout << "* ";
      } else if (Maze[i][j] == '3') {
        cout << "E ";
      }
    }
    cout << endl;
  }
  cout << endl << endl;

  cout << "Bombs: " << iBombCount << endl;
}

void MoveUp(char Maze[20][21], PPOINT pPlayerPos) {
  if (pPlayerPos->y - 1 >= 0) {
    if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0' &&
        Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4') {
      --pPlayerPos->y;
    }
  }
}

void MoveDown(char Maze[20][21], PPOINT pPlayerPos) {
  if (pPlayerPos->y + 1 < 20) {
    if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0' &&
        Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4') {
      ++pPlayerPos->y;
    }
  }
}

void MoveLeft(char Maze[20][21], PPOINT pPlayerPos) {
  if (pPlayerPos->x - 1 < 20) {
    if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0' &&
        Maze[pPlayerPos->y][pPlayerPos->x - 1] != '4') {
      --pPlayerPos->x;
    }
  }
}

void MoveRight(char Maze[20][21], PPOINT pPlayerPos) {
  if (pPlayerPos->x + 1 < 20) {
    if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0' &&
        Maze[pPlayerPos->y][pPlayerPos->x + 1] != '4') {
      ++pPlayerPos->x;
    }
  }
}

void MovePlayer(char Maze[20][21], PPOINT pPlayerPos, char cInput) {
  switch (cInput) {
    case 'w':
    case 'W': {
      MoveUp(Maze, pPlayerPos);
    } break;
    case 's':
    case 'S': {
      MoveDown(Maze, pPlayerPos);
    } break;
    case 'a':
    case 'A': {
      MoveLeft(Maze, pPlayerPos);
    } break;
    case 'd':
    case 'D': {
      MoveRight(Maze, pPlayerPos);
    } break;
  }
}

void CreateBomb(char Maze[20][21], const PPOINT pPlayer, PPOINT pBombArr,
                int* pBombCount) {
  if (*pBombCount == 5) return;

  for (int i = 0; i < *pBombCount; i++) {
    if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y) {
      return;
    }
  }

  pBombArr[*pBombCount] = *pPlayer;
  ++(*pBombCount);

  Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char Maze[20][21], PPOINT pPlayer, PPOINT pBombArr, int* pBombCount) {
  for (int i = 0; i < *pBombCount; i++) {
    Maze[pBombArr[i].y][pBombArr[i].x] = '1';

    // Upper-margin check
    if (pBombArr[i].y - 1 >= 0) {
      if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0') {
        Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';
      }

      // if player was hit by explosion
      if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1) {
        pPlayer->x = 0;
        pPlayer->y = 0;
      }
    }

    // Lower-margin check
    if (pBombArr[i].y + 1 < 20) {
      if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0') {
        Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';
      }

      // if player was hit by explosion
      if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1) {
        pPlayer->x = 0;
        pPlayer->y = 0;
      }
    }

    // Lt-margin check
    if (pBombArr[i].x - 1 >= 0) {
      if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0') {
        Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';
      }

      // if player was hit by explosion
      if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y) {
        pPlayer->x = 0;
        pPlayer->y = 0;
      }
    }

    // Rt-margin check
    if (pBombArr[i].x + 1 < 20) {
      if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0') {
        Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
      }

      // if player was hit by explosion
      if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y) {
        pPlayer->x = 0;
        pPlayer->y = 0;
      }
    }
  }
}

int main() {
  // 20 * 20 maze
  //          ypos xpos
  char strMaze[20][21];

  POINT tPlayerPos;
  POINT tStarPos;
  POINT tEndPos;

  int iBombCount = 0;
  POINT tBombPos[5];

  // create a maze
  SetMaze(strMaze, &tPlayerPos, &tStarPos, &tEndPos);

  while (true) {
    system("clear");
    Output(strMaze, &tPlayerPos, 5 - iBombCount);

    if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y) {
      cout << "Game End" << endl;
      break;
    }

    cout << "t: Drop Bomb, u: Ignite Bomb" << endl;
    cout << "w: Up, s: Down, a: Left, d: Right (q: Quit)" << endl;
    cout << "Enter a Key: ";
    char cInput = getch();

    if (cInput == 'q' || cInput == 'Q')
      break;
    else if (cInput == 't' || cInput == 'T') {
      CreateBomb(strMaze, &tPlayerPos, tBombPos, &iBombCount);
    } else if (cInput == 'u' || cInput == 'U') {
      Fire(strMaze, &tPlayerPos, tBombPos, &iBombCount);
      iBombCount = 0;
    } else
      MovePlayer(strMaze, &tPlayerPos, cInput);
  }

  return 0;
}