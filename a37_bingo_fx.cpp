/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec37. Text RPG again with Functions 3
https://www.youtube.com/watch?v=G50luIpRacM&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=37
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

const int g_iLevelUpExp[LEVEL_MAX] = {4000,  10000,  20000,  35000,  50000,
                                      70000, 100000, 150000, 200000, 400000};
_tagLevelUpStatus g_tLvUpTable[JOB_END - 1] = {};

/* function prototypes */

int InputInt();
int OutputMainMenu();
int OutputMapMenu();
int SelectJob();
void SetPlayer(_tagPlayer* pPlayer);
_tagMonster CreateMonster(const char* pName, int iAttackMin, int iAttackMax,
                          int iArmorMin, int iArmorMax, int iHP, int iMP,
                          int iLevel, int iExp, int iGoldMin, int iGoldMax);
void SetMonster(_tagMonster* pMonsterArr);
void OutputBattleTag(int iMenu);
_tagLevelUpStatus CreateLvUpSatus(int iAttackMin, int iAttackMax, int iArmorMin,
                                  int iArmorMax, int iHPMin, int iHPMax,
                                  int iMPMin, int iMPMax);
void OutputPlayer(_tagPlayer* pPlayer);
void OutputMonster(_tagMonster* pMonster);
int OutputBattleMenu();
void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster);
void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu);
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr);
int OutputStoreMenu();
int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore,
                        int iItemCount);
void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount,
             int iStoreType);
void RunStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor);

_tagItem CreateItem(const char* pName, ITEM_TYPE eType, int iMin, int iMax,
                    int iPrice, int iSell, const char* pDesc);
int OutputInventory(_tagPlayer* pPlayer);
EQUIP ComputeEquipType(ITEM_TYPE eType);
void RunInventory(_tagPlayer* pPlayer);

/* main function */

int main() {
  srand((unsigned int)time(0));

  _tagPlayer tPlayer = {};
  SetPlayer(&tPlayer);

  _tagMonster tMonsterArr[MT_BACK - 1] = {};
  SetMonster(tMonsterArr);

  g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpSatus(4, 10, 8, 16, 50, 100, 10, 20);
  g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpSatus(10, 15, 5, 10, 30, 60, 30, 50);
  g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpSatus(15, 20, 3, 7, 20, 40, 50, 100);

  _tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
  _tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

  tStoreWeapon[0] =
      CreateItem("Wooden Blade", IT_WEAPON, 5, 10, 1000, 500, "Blade");
  tStoreWeapon[1] =
      CreateItem("Long Bow", IT_WEAPON, 20, 10, 7000, 3500, "Bow");
  tStoreWeapon[2] =
      CreateItem("Wooden Club", IT_WEAPON, 90, 150, 30000, 15000, "Club");

  tStoreArmor[0] =
      CreateItem("Fabric Armor", IT_ARMOR, 5, 10, 1000, 500, "Fabric Armor");
  tStoreArmor[1] = CreateItem("Leather Armor", IT_ARMOR, 20, 10, 7000, 3500,
                              "Leather Armor");
  tStoreArmor[2] = CreateItem("Full Plate Armor", IT_ARMOR, 90, 150, 30000,
                              1500, "Steel Armor");

  bool bLoop = true;
  while (bLoop) {
    switch (OutputMainMenu()) {
      case MM_MAP: {
        RunMap(&tPlayer, tMonsterArr);
      } break;
      case MM_STORE: {
        RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
      } break;
      case MM_INVENTORY: {
        RunInventory(&tPlayer);
      } break;
      case MM_EXIT: {
        bLoop = false;
      } break;
    }
  }

  return 0;
}

/* function definitions */

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
  cout << "***** Lobby *****" << endl;
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
  cout << "***** Map *****" << endl;
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

_tagMonster CreateMonster(const char* pName, int iAttackMin, int iAttackMax,
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

_tagLevelUpStatus CreateLvUpSatus(int iAttackMin, int iAttackMax, int iArmorMin,
                                  int iArmorMax, int iHPMin, int iHPMax,
                                  int iMPMin, int iMPMax) {
  _tagLevelUpStatus tStatus = {};

  tStatus.iAttackMin = iAttackMin;
  tStatus.iAttackMax = iAttackMax;
  tStatus.iArmorMin = iArmorMin;
  tStatus.iArmorMax = iArmorMax;
  tStatus.iHPMin = iHPMin;
  tStatus.iHPMax = iHPMax;
  tStatus.iMPMin = iMPMin;
  tStatus.iMPMax = iMPMax;

  return tStatus;
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

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster) {
  int iAttackMin = pPlayer->iAttackMin;
  int iAttackMax = pPlayer->iAttackMax;

  // if player equipped with a weapon
  if (pPlayer->bEquip[EQ_WEAPON]) {
    iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
    iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
  }

  int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
  int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
               pMonster->iArmorMin;

  int iDamage = iAttack - iArmor;
  iDamage = iDamage < 1 ? 1 : iDamage;

  // decrease Monster's HP
  pMonster->iHP -= iDamage;

  cout << pPlayer->strName << " gave " << iDamage << " damages to "
       << pMonster->strName << endl;

  // Moster died.
  if (pMonster->iHP <= 0) {
    cout << pMonster->strName << " died." << endl;

    pPlayer->iExp += pMonster->iExp;
    int iGold = (rand() % (pMonster->iGoldMax - pMonster->iGoldMin + 1) +
                 pMonster->iGoldMin);
    pPlayer->tInventory.iGold += iGold;

    cout << "You've got " << pMonster->iExp << " EXP." << endl;
    cout << "You've got " << iGold << " Golds." << endl;

    pMonster->iHP = pMonster->iHPMax;
    pMonster->iMP = pMonster->iMPMax;

    // check whether the player satisfied the condition for
    // level-up
    if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1]) {
      pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];
      ++pPlayer->iLevel;
      cout << "Level-UP!!" << endl;

      int iJobIndex = pPlayer->eJob - 1;
      int iHPUp = rand() % (g_tLvUpTable[iJobIndex].iHPMax -
                            g_tLvUpTable[iJobIndex].iHPMin + 1) +
                  g_tLvUpTable[iJobIndex].iHPMin;
      int iMPUp = rand() % (g_tLvUpTable[iJobIndex].iMPMax -
                            g_tLvUpTable[iJobIndex].iMPMin + 1) +
                  g_tLvUpTable[iJobIndex].iMPMin;

      pPlayer->iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
      pPlayer->iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
      pPlayer->iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
      pPlayer->iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;

      pPlayer->iHPMax += iHPUp;
      pPlayer->iMPMax += iMPUp;

      pPlayer->iHP = pPlayer->iHPMax;
      pPlayer->iMP = pPlayer->iMPMax;
    }
  }

  // monster's counter-attack
  iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
            pMonster->iAttackMin;

  int iArmorMin = pPlayer->iArmorMin;
  int iArmorMax = pPlayer->iArmorMax;

  if (pPlayer->bEquip[EQ_ARMOR]) {
    iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
    iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
  }

  iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

  iDamage = iAttack - iArmor;
  iDamage = iDamage < 1 ? 1 : iDamage;

  // decrease player's HP
  pPlayer->iHP -= iDamage;

  cout << pMonster->strName << " gave " << iDamage << " damages to "
       << pPlayer->strName << endl;

  // Player died.
  if (pPlayer->iHP <= 0) {
    cout << pPlayer->strName << " Died." << endl;

    int iExp = pPlayer->iExp * 0.1f;
    int iGold = pPlayer->tInventory.iGold * 0.1f;

    pPlayer->iExp -= iExp;
    pPlayer->tInventory.iGold -= iGold;

    cout << "You've lost " << iExp << " EXp." << endl;
    cout << "You've lost " << iGold << " Golds." << endl;

    pPlayer->iHP = pPlayer->iHPMax;
    pPlayer->iMP = pPlayer->iMPMax;
  }
  return;
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu) {
  _tagMonster tMonster = pMonsterArr[iMenu - 1];

  while (true) {
    system("clear");
    OutputBattleTag(iMenu);

    OutputPlayer(pPlayer);
    OutputMonster(&tMonster);

    switch (OutputBattleMenu()) {
      case BATTLE_ATTACK: {
        Battle(pPlayer, &tMonster);
        system("read");
      } break;
      case BATTLE_BACK:
        return;
    }
  }
}

void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr) {
  bool bLoop = true;
  while (bLoop) {
    int iMenu = OutputMapMenu();
    if (MT_BACK == iMenu) return;

    RunBattle(pPlayer, pMonsterArr, iMenu);
  }
}

int OutputStoreMenu() {
  system("clear");
  while (true) {
    cout << "***** STORE *****" << endl;
    cout << "1. Weapon" << endl;
    cout << "2. Armor" << endl;
    cout << "3. Previous Menu" << endl;
    cout << "Select Menu: ";
    int iMenu = InputInt();

    if (iMenu < SM_NONE || iMenu > SM_BACK) return SM_NONE;

    return iMenu;
  }
}

int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore,
                        int iItemCount) {
  for (int i = 0; i < iItemCount; ++i) {
    cout << i + 1 << ". Name: " << pStore[i].strName
         << "\tKind: " << pStore[i].strTypeName << endl;
    cout << "Attack: " << pStore[i].iMin << " - " << pStore[i].iMax << endl;
    cout << "Price: " << pStore[i].iPrice << "\tSell: " << pStore[i].iSell
         << endl;
    cout << "Description: " << pStore[i].strDesc << endl << endl;
  }

  cout << iItemCount + 1 << ". Previous Menu" << endl;
  cout << "Money: " << pInventory->iGold << " Gold" << endl;
  cout << "Remaining slots: " << INVENTORY_MAX - pInventory->iItemCount << endl;
  cout << "Select what you want to buy: ";
  int iMenu = InputInt();
  if (iMenu < 1 || iMenu > iItemCount + 1) return INT_MAX;
  return iMenu;
}

void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount,
             int iStoreType) {
  while (true) {
    system("clear");
    switch (iStoreType) {
      case SM_WEAPON: {
        cout << "***** Weapon Store *****" << endl;
      } break;
      case SM_ARMOR: {
        cout << "***** Armor Store *****" << endl;
      } break;
    }
    int iInput = OutputStoreItemList(pInventory, pStore, iItemCount);

    if (iInput == INT_MAX) {
      cout << "Wrong Input" << endl;
      system("read");
      continue;
    } else if (iInput == iItemCount + 1)
      break;

    int iIndex = iInput - 1;

    // check if inventory is full
    if (pInventory->iItemCount == INVENTORY_MAX) {
      cout << "Inventory is full." << endl;
      system("read");
      continue;
    }

    // not enough money
    else if (pInventory->iGold < pStore[iIndex].iPrice) {
      cout << "Not enough money" << endl;
      system("read");
      continue;
    }

    pInventory->tItem[pInventory->iItemCount] = pStore[iIndex];
    ++pInventory->iItemCount;

    // decrease money
    pInventory->iGold -= pStore[iIndex].iPrice;

    cout << "You just bought " << pStore[iIndex].strName << "." << endl;
    system("read");
  }
}

void RunStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor) {
  while (true) {
    switch (OutputStoreMenu()) {
      case SM_WEAPON: {
        BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
      } break;
      case SM_ARMOR: {
        BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
      } break;
      case SM_BACK: {
        return;
      }
    }
  }
}

_tagItem CreateItem(const char* pName, ITEM_TYPE eType, int iMin, int iMax,
                    int iPrice, int iSell, const char* pDesc) {
  _tagItem tItem = {};

  strcpy(tItem.strName, pName);
  strcpy(tItem.strDesc, pDesc);

  tItem.eType = eType;
  switch (eType) {
    case IT_WEAPON: {
      strcpy(tItem.strTypeName, "Weapon");
    } break;
    case IT_ARMOR: {
      strcpy(tItem.strTypeName, "Armor");
    } break;
  }

  tItem.iMin = iMin;
  tItem.iMax = iMax;
  tItem.iPrice = iPrice;
  tItem.iSell = iSell;

  return tItem;
}

int OutputInventory(_tagPlayer* pPlayer) {
  system("clear");
  cout << "***** INVENTORY *****" << endl;

  OutputPlayer(pPlayer);

  for (int i = 0; i < pPlayer->tInventory.iItemCount; ++i) {
    cout << i + 1 << ". Name: " << pPlayer->tInventory.tItem[i].strName
         << "\tKind: " << pPlayer->tInventory.tItem[i].strTypeName << endl;
    cout << "Attack: " << pPlayer->tInventory.tItem[i].iMin << " - "
         << pPlayer->tInventory.tItem[i].iMax << endl;
    cout << "Price: " << pPlayer->tInventory.tItem[i].iPrice << "\tSell  "
         << pPlayer->tInventory.tItem[i].iSell << endl;
    cout << "Description: " << pPlayer->tInventory.tItem[i].strDesc << endl
         << endl;
  }

  cout << pPlayer->tInventory.iItemCount + 1 << ". Previous Menu" << endl;
  cout << "Select item which you want to equip with: ";
  int iMenu = InputInt();
  if (iMenu < 1 || iMenu > pPlayer->tInventory.iItemCount + 1) {
    return INT_MAX;
  }
  return iMenu;
}

EQUIP ComputeEquipType(ITEM_TYPE eType) {
  EQUIP eq;
  switch (eType) {
    case IT_WEAPON:
      eq = EQ_WEAPON;
      break;
    case IT_ARMOR:
      eq = EQ_ARMOR;
      break;
  }
  return eq;
}

void RunInventory(_tagPlayer* pPlayer) {
  while (true) {
    int iInput = OutputInventory(pPlayer);
    if (iInput == INT_MAX)
      continue;
    else if (iInput == pPlayer->tInventory.iItemCount + 1)
      break;

    int idx = iInput - 1;

    EQUIP eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

    if (pPlayer->bEquip[eq] == true) {
      _tagItem tSwap = pPlayer->tEquip[eq];
      pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
      pPlayer->tInventory.tItem[idx] = tSwap;
    }

    else {
      pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

      for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; ++i) {
        pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
      }

      --pPlayer->tInventory.iItemCount;

      pPlayer->bEquip[eq] = true;
    }

    cout << pPlayer->tEquip[eq].strName << " was equipped." << endl;

    system("read");
  }
}