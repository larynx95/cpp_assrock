/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec35. Text RPG again with Functions
https://www.youtube.com/watch?v=KLrkgbELqnU&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=35
******************************************************************************/

#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10

const int g_iLevelUpExp[LEVEL_MAX] = {4000,  10000,  20000,  35000,  50000,
                                      70000, 100000, 150000, 200000, 400000};

enum MAIN_MENU { MM_NONE, MM_MAP, MM_STORE, MM_INVENTORY, MM_EXIT };
enum MAP_TYPE { MT_NONE, MT_EASY, MT_NORMAL, MT_HARD, MT_BACK };
enum JOB { JOB_NONE, JOB_KNIGHT, JOB_ARCHER, JOB_WIZARD, JOB_END };
enum BATTLE { BATTLE_NONE, BATTLE_ATTACK, BATTLE_BACK };
enum ITEM_TYPE { IT_NONE, IT_WEAPON, IT_ARMOR, IT_BACK };
enum STORE_MENU { SM_NONE, SM_WEAPON, SM_ARMOR, SM_BACK };
enum EQUIP { EQ_WEAPON, EQ_ARMOR, EQ_MAX };

struct _tagItem {
  char strName[NAME_SIZE];
  char strTypeName[NAME_SIZE];
  ITEM_TYPE eType;
  int iMin;
  int iMax;
  int iPrice;
  int iSell;
  char strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory {
  _tagItem tItem[INVENTORY_MAX];
  int iItemCount;
  int iGold;
};

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
  _tagItem tEquip[EQ_MAX];
  bool bEquip[EQ_MAX];
  _tagInventory tInventory;
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
  int iLevel;
  int iExp;
  int iGoldMin;
  int iGoldMax;
};

struct _tagLevelUpStatus {
  int iAttackMin;
  int iAttackMax;
  int iArmorMin;
  int iArmorMax;
  int iHPMin;
  int iHPMax;
  int iMPMin;
  int iMPMax;
};

int InputInt() {
  int iInput;
  cin >> iInput;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(1024, '\n');
    return INT_MAX;
  }
  return iInput;
}

int OutputMainMenu() {
  system("clear");
  cout << "*************************** Lobby ***************************"
       << endl;
  cout << "1. Map" << endl;
  cout << "2. Store" << endl;
  cout << "3. Inventory" << endl;
  cout << "4. Exit" << endl;
  cout << "Select Menu: ";
  int iMenu = InputInt();
  if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT) {
    return MM_NONE;
  }
  return iMenu;
}

int OutputMapMenu() {
  system("clear");
  cout << "*************************** Map ***************************" << endl;
  cout << "1. Easy" << endl;
  cout << "2. Normal" << endl;
  cout << "3. Difficult" << endl;
  cout << "4. Back to main menu" << endl;
  cout << "Select Menu: ";
  int iMenu = InputInt();
  if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK) {
    return MT_BACK;
  }
  return iMenu;
}

int SelectJob() {
  int iJob = JOB_NONE;
  while (iJob == JOB_NONE) {
    system("clear");
    cout << "1. Knight" << endl;
    cout << "2. Archer" << endl;
    cout << "3. Wizard" << endl;
    cout << "Select your job: ";
    iJob = InputInt();

    if (iJob <= JOB_NONE || iJob >= JOB_END) iJob = JOB_NONE;
  }
  return iJob;
}

void SetPlayer(_tagPlayer* pPlayer) {
  cout << "Name: ";
  cin.getline(pPlayer->strName, NAME_SIZE - 1);
  pPlayer->eJob = (JOB)SelectJob();

  pPlayer->iLevel = 1;
  pPlayer->iExp = 0;
  pPlayer->tInventory.iGold = 10000;

  switch (pPlayer->eJob) {
    case JOB_KNIGHT:
      strcpy(pPlayer->strJobName, "Knight");
      pPlayer->iAttackMin = 5;
      pPlayer->iAttackMax = 10;
      pPlayer->iArmorMin = 15;
      pPlayer->iArmorMax = 20;
      pPlayer->iHPMax = 500;
      pPlayer->iHP = 500;
      pPlayer->iMP = 100;
      pPlayer->iMPMax = 100;
      break;
    case JOB_ARCHER:
      strcpy(pPlayer->strJobName, "Archer");
      pPlayer->iAttackMin = 10;
      pPlayer->iAttackMax = 15;
      pPlayer->iArmorMin = 10;
      pPlayer->iArmorMax = 15;
      pPlayer->iHPMax = 400;
      pPlayer->iHP = 400;
      pPlayer->iMP = 200;
      pPlayer->iMPMax = 200;
      break;
    case JOB_WIZARD:
      strcpy(pPlayer->strJobName, "Wizard");
      pPlayer->iAttackMin = 15;
      pPlayer->iAttackMax = 20;
      pPlayer->iArmorMin = 5;
      pPlayer->iArmorMax = 10;
      pPlayer->iHPMax = 300;
      pPlayer->iHP = 300;
      pPlayer->iMP = 300;
      pPlayer->iMPMax = 300;
      break;
  }
}

_tagMonster CreateMonster(char* pName, int iAttackMin, int iAttackMax,
                          int iArmorMin, int iArmorMax, int iHP, int iMP,
                          int iLevel, int iExp, int iGoldMin, int iGoldMax) {
  _tagMonster tMonster = {};
  strcpy(tMonster.strName, pName);
  tMonster.iAttackMin = iAttackMin;
  tMonster.iAttackMax = iAttackMax;
  tMonster.iArmorMin = iArmorMin;
  tMonster.iArmorMax = iArmorMax;
  tMonster.iHP = iHP;
  tMonster.iHPMax = iHP;
  tMonster.iMP = iMP;
  tMonster.iMPMax = iMP;
  tMonster.iExp = iExp;
  tMonster.iLevel = iLevel;
  tMonster.iGoldMin = iGoldMin;
  tMonster.iGoldMax = iGoldMax;

  return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr) {
  pMonsterArr[0] =
      CreateMonster("Goblin", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
  pMonsterArr[1] =
      CreateMonster("Troll", 80, 130, 50, 90, 2000, 100, 5, 7000, 6000, 8000);
  pMonsterArr[2] = CreateMonster("Dragon", 250, 500, 200, 400, 30000, 20000, 10,
                                 30000, 20000, 50000);
}

void OutputBattleTag(int iMenu) {
  switch (iMenu) {
    case MT_EASY:
      cout << "***** Easy *****" << endl;
      break;
    case MT_NORMAL:
      cout << "***** Normal *****" << endl;
      break;
    case MT_HARD:
      cout << "***** Difficult *****" << endl;
      break;
  }
}

void OutputPlayer(_tagPlayer* pPlayer) {
  cout << "========== Player ==========" << endl;
  cout << "Name: " << pPlayer->strName << "\tJob: " << pPlayer->strJobName
       << endl;
  cout << "Level: " << pPlayer->iLevel << "\tEXP: " << pPlayer->iExp << " / "
       << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

  // player's attack ability will increased with a weapon
  if (pPlayer->bEquip[EQ_WEAPON] == true) {
    cout << "Attack: " << pPlayer->iAttackMin << " + "
         << pPlayer->tEquip[EQ_WEAPON].iMin << " - " << pPlayer->iAttackMax
         << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
  }

  else {
    cout << "Attack: " << pPlayer->iAttackMin << " - " << pPlayer->iAttackMax;
  }

  // Armor increases player's defence
  if (pPlayer->bEquip[EQ_ARMOR] == true) {
    cout << "\tDefence : " << pPlayer->iArmorMin << " + "
         << pPlayer->tEquip[EQ_ARMOR].iMin << " - " << pPlayer->iArmorMax
         << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
  }

  else {
    cout << "\tDefence: " << pPlayer->iArmorMin << " - " << pPlayer->iArmorMax
         << endl;
  }

  cout << "HP: " << pPlayer->iHP << " / " << pPlayer->iHPMax
       << "\tMANA: " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

  if (pPlayer->bEquip[EQ_WEAPON])
    cout << "Equipped Weapon: " << pPlayer->tEquip[EQ_WEAPON].strName;

  else
    cout << "No Equipped Weapon";

  if (pPlayer->bEquip[EQ_ARMOR])
    cout << "\tEquipped Armor: " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

  else
    cout << "\tNo Equipped Armor" << endl;

  cout << "Money: " << pPlayer->tInventory.iGold << " Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster) {
  cout << "========== Monster ==========" << endl;
  cout << "Name: " << pMonster->strName << "\tLevel: " << pMonster->iHPMax
       << endl;
  cout << "Attack: " << pMonster->iAttackMin << " - " << pMonster->iAttackMax
       << "\tDefence : " << pMonster->iArmorMin << " - " << pMonster->iArmorMax
       << endl;
  cout << "HP: " << pMonster->iHP << " / " << pMonster->iHPMax
       << "\tMANA: " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
  cout << "EXP: " << pMonster->iExp << "\tGOLD : " << pMonster->iGoldMin
       << " - " << pMonster->iGoldMax << endl
       << endl;
}

int OutputBattleMenu() {
  cout << "1. ATTACK" << endl;
  cout << "2. RUN AWAY" << endl;
  cout << "Select Menu: ";
  int iMenu = InputInt();

  if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK) {
    return BATTLE_NONE;
  }

  return iMenu;
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu) {
  _tagMonster tMonster = pMonsterArr[iMenu - 1];

  while (true) {
    system("clear");
    OutputBattleTag(iMenu);

    OutputPlayer(pPlayer);
    OutputMonster(&tMonster);

    switch (OutputBattleMenu()) {
      case BATTLE_ATTACK:
        break;
      case BATTLE_BACK:
        return;
    }
  }
}

void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr) {
  bool bLoop = true;
  while (bLoop) {
    int iMenu = OutputMainMenu();
    if (MT_BACK == iMenu) return;

    RunBattle(pPlayer, pMonsterArr, iMenu);
  }
}

int main() {
  srand((unsigned int)time(0));

  _tagPlayer tPlayer = {};
  SetPlayer(&tPlayer);

  _tagMonster tMonsterArr[MT_BACK - 1] = {};
  SetMonster(tMonsterArr);

  bool bLoop = true;
  while (bLoop) {
    switch (OutputMainMenu()) {
      case MM_MAP: {
        RunMap(&tPlayer, tMonsterArr);
      } break;
      case MM_STORE: {
      } break;
      case MM_INVENTORY: {
      } break;
      case MM_EXIT: {
        bLoop = false;
      } break;
    }
  }

  return 0;
}