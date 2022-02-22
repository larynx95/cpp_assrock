/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec23. Text RPG 1
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=23
******************************************************************************/

#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

enum MAIN_MENU { MM_NONE, MM_MAP, MM_STORE, MM_INVENTORY, MM_EXIT };
enum MAP_TYPE { MT_NONE, MT_EASY, MT_NORMAL, MT_HARD, MT_BACK };
enum JOB { JOB_NONE, JOB_KNIGHT, JOB_ARCHER, JOB_WIZARD, JOB_END };

#define NAME_SIZE 32

struct _tagPlayer {
  char strName[NAME_SIZE];
  char strJobName[NAME_SIZE];
  JOB eJob;
  int iAttackMin;
  int iAttackMax;
  int iArmorMin;
  int iArmorMax;
  int iHP;
  int iHPMax;
  int iMP;
  int iMPMax;
  int iExp;
  int iLevel;
};

struct _tagMonster {
  char strName[NAME_SIZE];
  int iAttackMin;
  int iAttackMax;
  int iArmorMin;
  int iArmorMax;
  int iHP;
  int iHPMax;
  int iMP;
  int iMPMax;
  int iExp;
  int iLevel;
  int iGoldMin;
  int iGoldMax;
};

int main() {
  /* Text RPG */

  srand((unsigned int)time(0));

  _tagPlayer tPlayer = {};

  cout << "Name: ";
  cin.getline(tPlayer.strName, NAME_SIZE - 1);

  int iJob = JOB_NONE;
  while (iJob == JOB_NONE) {
    system("clear");
    cout << "1. Knight" << endl;
    cout << "2. Archer" << endl;
    cout << "3. Wizard" << endl;
    cout << "Select Your Job: ";
    cin >> iJob;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    } else if (iJob <= JOB_NONE || iJob >= JOB_END) {
      iJob = JOB_NONE;
    }
  }

  tPlayer.iLevel = 1;
  tPlayer.iExp = 0;
  tPlayer.eJob = (JOB)iJob;

  switch (tPlayer.eJob) {
    case JOB_KNIGHT:
      strcpy(tPlayer.strJobName, "Knight");
      tPlayer.iAttackMin = 5;
      tPlayer.iAttackMax = 10;
      tPlayer.iArmorMin = 15;
      tPlayer.iArmorMax = 20;
      tPlayer.iHP = 500;
      tPlayer.iHPMax = 500;
      tPlayer.iMP = 100;
      tPlayer.iMPMax = 100;
      break;
    case JOB_ARCHER:
      strcpy(tPlayer.strJobName, "Archer");
      tPlayer.iAttackMin = 10;
      tPlayer.iAttackMax = 15;
      tPlayer.iArmorMin = 10;
      tPlayer.iArmorMax = 15;
      tPlayer.iHP = 400;
      tPlayer.iHPMax = 400;
      tPlayer.iMP = 200;
      tPlayer.iMPMax = 200;
      break;
    case JOB_WIZARD:
      strcpy(tPlayer.strJobName, "Wizard");
      tPlayer.iAttackMin = 15;
      tPlayer.iAttackMax = 20;
      tPlayer.iArmorMin = 5;
      tPlayer.iArmorMax = 10;
      tPlayer.iHP = 300;
      tPlayer.iHPMax = 300;
      tPlayer.iMP = 300;
      tPlayer.iMPMax = 300;
      break;
    default:
      break;
  }

  // creating Monsters
  _tagMonster tMonsterArr[MT_BACK - 1] = {};

  // Goblin
  strcpy(tMonsterArr[0].strName, "Goblin");
  tMonsterArr[0].iAttackMin = 20;
  tMonsterArr[0].iAttackMax = 30;
  tMonsterArr[0].iArmorMin = 2;
  tMonsterArr[0].iArmorMax = 5;
  tMonsterArr[0].iHP = 100;
  tMonsterArr[0].iHPMax = 100;
  tMonsterArr[0].iMP = 100;
  tMonsterArr[0].iMPMax = 100;
  tMonsterArr[0].iExp = 1000;
  tMonsterArr[0].iLevel = 1;
  tMonsterArr[0].iGoldMin = 500;
  tMonsterArr[0].iGoldMax = 1500;

  // Troll
  strcpy(tMonsterArr[1].strName, "Troll");
  tMonsterArr[1].iAttackMin = 80;
  tMonsterArr[1].iAttackMax = 130;
  tMonsterArr[1].iArmorMin = 60;
  tMonsterArr[1].iArmorMax = 90;
  tMonsterArr[1].iHP = 2000;
  tMonsterArr[1].iHPMax = 2000;
  tMonsterArr[1].iMP = 100;
  tMonsterArr[1].iMPMax = 100;
  tMonsterArr[1].iExp = 7000;
  tMonsterArr[1].iLevel = 5;
  tMonsterArr[1].iGoldMin = 6000;
  tMonsterArr[1].iGoldMax = 8000;

  // Goblin
  strcpy(tMonsterArr[2].strName, "Dragon");
  tMonsterArr[2].iAttackMin = 250;
  tMonsterArr[2].iAttackMax = 500;
  tMonsterArr[2].iArmorMin = 200;
  tMonsterArr[2].iArmorMax = 400;
  tMonsterArr[2].iHP = 30000;
  tMonsterArr[2].iHPMax = 30000;
  tMonsterArr[2].iMP = 20000;
  tMonsterArr[2].iMPMax = 20000;
  tMonsterArr[2].iExp = 30000;
  tMonsterArr[2].iLevel = 10;
  tMonsterArr[2].iGoldMin = 20000;
  tMonsterArr[2].iGoldMax = 50000;

  while (true) {
    system("clear");
    cout << "~~~~~ Main Menu ~~~~~" << endl;
    cout << "1. Map" << endl;
    cout << "2. Store" << endl;
    cout << "3. Inventory" << endl;
    cout << "4. Exit" << endl;
    cout << "Select Menu: ";

    int iMenu;
    cin >> iMenu;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (iMenu == MM_EXIT) break;

    switch (iMenu) {
      case MM_MAP:
        while (true) {
          system("clear");
          cout << "~~~~~ Map Menu ~~~~~" << endl;
          cout << "1-1. Easy" << endl;
          cout << "1-2. Normal" << endl;
          cout << "1-3. Difficult" << endl;
          cout << "1-4. Back" << endl;
          cout << "Select map: ";
          cin >> iMenu;

          if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
          }

          if (iMenu == MT_BACK) break;

          // index of array of Monster = index of Menu - 1
          _tagMonster tMonster = tMonsterArr[iMenu - 1];

          while (true) {
            switch (iMenu) {
              case MT_EASY:
                cout << "~~~~~  EASY ~~~~~" << endl;
                break;
              case MT_NORMAL:
                cout << "~~~~~  NORMAL ~~~~~" << endl;
                break;
              case MT_HARD:
                cout << "~~~~~  HARD ~~~~~" << endl;
                break;
            }
          }
        }
        break;
      case MM_STORE:
        break;
      case MM_INVENTORY:
        break;
      default:
        cout << "Wrong selection." << endl;
    }
  }

  return 0;
}