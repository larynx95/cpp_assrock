/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec38. Maze Game 1
https://www.youtube.com/watch?v=l6n8iT9s4J8&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=38

https://blog.naver.com/lmj3322/221401213574
https://github.com/Yumin2019/TextMaze
******************************************************************************/

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

void SetMaze(char Maze[20][21]) {
  // 0: wall, 1: road, 2: start, 3: end
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

void Output(char Maze[20][21]) {
  system("clear");
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 21; j++) {
      if (Maze[i][j] == '0') {
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
  cout << endl;
}

int main() {
  // 20 * 20 maze
  char strMaze[20][21];

  SetMaze(strMaze);

  while (true) {
    Output(strMaze);
    cout << "w: Up, s: Down, a: Left, d: Right (q: Quit)" << endl;
    cout << "Enter a Key: ";
    char cInput = getch();

    if (cInput == 'q' || cInput == 'Q') break;
  }

  return 0;
}