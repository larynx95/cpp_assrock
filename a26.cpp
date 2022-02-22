/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec26. Text RPG 4
https://www.youtube.com/watch?v=MbrjzBaab9U&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=26
******************************************************************************/

#include <string.h>
#include <time.h>

#include <climits>
#include <iostream>
using namespace std;

enum MAIN_MENU { MM_NONE, MM_MAP, MM_STORE, MM_INVENTORY, MM_EXIT };
enum MAP_TYPE { MT_NONE, MT_EASY, MT_NORMAL, MT_HARD, MT_BACK };
enum JOB { JOB_NONE, JOB_KNIGHT, JOB_ARCHER, JOB_WIZARD, JOB_END };
enum BATTLE { BATTLE_NONE, BATTLE_ATTACK, BATTLE_BACK };
enum ITEM_TYPE { IT_NONE, IT_WEAPON, IT_ARMOR, IT_BACK };
enum STORE_MENU { SM_NONE, SM_WEAPON, SM_ARMOR, SM_BACK };

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3

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
  int iGold;
  _tagItem tItem[INVENTORY_MAX];
  int iItemCount;
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
  int iExp;
  int iLevel;
  int iGoldMin;
  int iGoldMax;
};

int main() {
  // random seed
  srand((unsigned int)time(0));

  // create a player
  _tagPlayer tPlayer = {};
  cout << "Name: ";
  cin.getline(tPlayer.strName, NAME_SIZE - 1);

  // select player's job
  int iJob = JOB_NONE;
  while (iJob == JOB_NONE) {
    system("clear");
    cout << "1. Knight" << endl;
    cout << "2. Archer" << endl;
    cout << "3. Wizard" << endl;
    cout << "Select Your Job: ";
    cin >> iJob;

    // check validity of user input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    } else if (iJob <= JOB_NONE || iJob >= JOB_END) {
      iJob = JOB_NONE;
    }
  }

  // set player's basic stats
  tPlayer.iLevel = 1;
  tPlayer.iExp = 0;
  tPlayer.eJob = (JOB)iJob;
  tPlayer.tInventory.iGold = 10000;

  // set player's detailed stats
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

  // Dragon
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

  // list of store items
  _tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
  _tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

  strcpy(tStoreWeapon[0].strName, "Katana");
  strcpy(tStoreWeapon[0].strTypeName, "One-hand");
  strcpy(tStoreWeapon[0].strDesc, "simple one-handed sword");
  tStoreWeapon[0].eType = IT_WEAPON;
  tStoreWeapon[0].iMin = 1;
  tStoreWeapon[0].iMax = 5;
  tStoreWeapon[0].iPrice = 100;
  tStoreWeapon[0].iSell = 50;

  strcpy(tStoreWeapon[1].strName, "Mace");
  strcpy(tStoreWeapon[1].strTypeName, "One-hand");
  strcpy(tStoreWeapon[1].strDesc, "simple one-handed mace");
  tStoreWeapon[1].eType = IT_WEAPON;
  tStoreWeapon[1].iMin = 1;
  tStoreWeapon[1].iMax = 5;
  tStoreWeapon[1].iPrice = 50;
  tStoreWeapon[1].iSell = 10;

  strcpy(tStoreWeapon[2].strName, "Axe");
  strcpy(tStoreWeapon[2].strTypeName, "Two-hand");
  strcpy(tStoreWeapon[2].strDesc, "simple two-handed axe");
  tStoreWeapon[2].eType = IT_WEAPON;
  tStoreWeapon[2].iMin = 1;
  tStoreWeapon[2].iMax = 5;
  tStoreWeapon[2].iPrice = 200;
  tStoreWeapon[2].iSell = 100;

  strcpy(tStoreArmor[0].strName, "Shield");
  strcpy(tStoreArmor[0].strTypeName, "Hand-held");
  strcpy(tStoreArmor[0].strDesc, "simple one-handed shield");
  tStoreArmor[0].eType = IT_WEAPON;
  tStoreArmor[0].iMin = 1;
  tStoreArmor[0].iMax = 5;
  tStoreArmor[0].iPrice = 100;
  tStoreArmor[0].iSell = 50;

  strcpy(tStoreArmor[1].strName, "Helmet");
  strcpy(tStoreArmor[1].strTypeName, "Head Gear");
  strcpy(tStoreArmor[1].strDesc, "simple helmet");
  tStoreArmor[1].eType = IT_WEAPON;
  tStoreArmor[1].iMin = 1;
  tStoreArmor[1].iMax = 5;
  tStoreArmor[1].iPrice = 50;
  tStoreArmor[1].iSell = 10;

  strcpy(tStoreArmor[2].strName, "Plate");
  strcpy(tStoreArmor[2].strTypeName, "Body Gear");
  strcpy(tStoreArmor[2].strDesc, "simple body armor");
  tStoreArmor[2].eType = IT_WEAPON;
  tStoreArmor[2].iMin = 1;
  tStoreArmor[2].iMax = 5;
  tStoreArmor[2].iPrice = 200;
  tStoreArmor[2].iSell = 100;

  while (true) {
    // main menus
    system("clear");
    cout << "~~~~~ Main Menu ~~~~~" << endl;
    cout << "1. Map" << endl;
    cout << "2. Store" << endl;
    cout << "3. Inventory" << endl;
    cout << "4. Exit" << endl;
    cout << "Select Menu: ";

    int iMenu;
    cin >> iMenu;

    // check the validity of user input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    // exit game
    if (iMenu == MM_EXIT) break;

    // map menus
    switch (iMenu) {
      case MM_MAP: {
        while (true) {
          system("clear");
          cout << "~~~~~ Map Menu ~~~~~" << endl;
          cout << "1. Easy" << endl;
          cout << "2. Normal" << endl;
          cout << "3. Difficult" << endl;
          cout << "4. Back" << endl;
          cout << "Select map: ";
          cin >> iMenu;

          // check the validity of user input
          if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
          }

          // player decided to run away
          if (iMenu == MT_BACK) break;

          // index of array of Monster = index of Menu - 1
          _tagMonster tMonster = tMonsterArr[iMenu - 1];

          while (true) {
            // show the difficulty level of current map (monster)
            system("clear");
            switch (iMenu) {
              case MT_EASY:
                cout << endl << "~~~~~  EASY ~~~~~" << endl;
                break;
              case MT_NORMAL:
                cout << endl << "~~~~~  NORMAL ~~~~~" << endl;
                break;
              case MT_HARD:
                cout << endl << "~~~~~  HARD ~~~~~" << endl;
                break;
            }

            // print player's data
            cout << "Player's Data  >>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "Name: " << tPlayer.strName << "\t"
                 << "Job: " << tPlayer.strJobName << endl;
            cout << "Level: " << tPlayer.iLevel << "\t"
                 << "Exp: " << tPlayer.iExp << endl;
            cout << "Attack: " << tPlayer.iAttackMin << " ~ "
                 << tPlayer.iAttackMax << endl;
            cout << "Armor: " << tPlayer.iArmorMin << " ~ " << tPlayer.iArmorMax
                 << endl;
            cout << "HP: " << tPlayer.iHP << " / " << tPlayer.iHPMax << endl;
            cout << "MANA: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
            cout << "Gold: " << tPlayer.tInventory.iGold << endl << endl;

            // print monster's data
            cout << "Monster's Data  >>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            cout << "Name: " << tMonster.strName << endl;
            cout << "Level: " << tMonster.iLevel << "\t"
                 << "Exp: " << tMonster.iExp << endl;
            cout << "Attack: " << tMonster.iAttackMin << " ~ "
                 << tMonster.iAttackMax << endl;
            cout << "Armor: " << tMonster.iArmorMin << " ~ "
                 << tMonster.iArmorMax << endl;
            cout << "HP: " << tMonster.iHP << " ~ " << tMonster.iHPMax << endl;
            cout << "MANA: " << tMonster.iMP << " ~ " << tMonster.iMPMax
                 << endl;
            cout << "Gold: " << tMonster.iGoldMin << " ~ " << tMonster.iGoldMax
                 << endl
                 << endl;

            // get player's decision
            cout << "1. Attack" << endl;
            cout << "2. Retreat" << endl;
            cout << "Select Menu: ";
            int iDecision;
            cin >> iDecision;
            if (cin.fail()) {
              // invalid user input
              cin.clear();
              cin.ignore(1024, '\n');
              continue;
            } else if (iDecision == BATTLE_BACK)
              // player decided to run away
              break;

            //
            switch (iDecision) {
              case BATTLE_ATTACK: {
                // Player's attack
                int iAttack =
                    rand() % (tPlayer.iAttackMax - tPlayer.iAttackMin + 1) +
                    tPlayer.iAttackMin;
                int iArmor =
                    rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
                    tMonster.iArmorMin;
                int iDamage = iAttack - iArmor;
                iDamage = iDamage < 1 ? 1 : iDamage;
                tMonster.iHP -= iDamage;
                cout << endl << "Combat Result ===== " << endl;
                cout << tPlayer.strName << " gave " << iDamage << " damages to "
                     << tMonster.strName << "." << endl
                     << endl;

                // monster died
                if (tMonster.iHP < 0) {
                  cout << tMonster.strName << " died!" << endl;
                  tPlayer.iExp += tMonster.iExp;
                  int iGold =
                      rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
                      tMonster.iGoldMin;
                  tPlayer.tInventory.iGold += iGold;
                  cout << "You've got " << tMonster.iExp << " EXPs." << endl;
                  cout << "You've got  " << iGold << " Golds." << endl << endl;

                  // restore Monster's stats to initial values
                  tMonster.iHP = tMonster.iHPMax;
                  tMonster.iMP = tMonster.iMPMax;
                }

                // Monster's turn
                iAttack =
                    rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
                    tMonster.iAttackMin;
                iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMin + 1) +
                         tPlayer.iArmorMin;
                iDamage = iAttack - iArmor;
                iDamage = iDamage < 1 ? 1 : iDamage;

                tPlayer.iHP -= iDamage;
                cout << tMonster.strName << " gave " << iDamage
                     << " damages to " << tPlayer.strName << "." << endl;

                // when the player died
                if (tPlayer.iHP <= 0) {
                  cout << tPlayer.strName << " died." << endl;

                  int iExp = tPlayer.iExp * 0.1f;
                  int iGold = tPlayer.tInventory.iGold * 0.1f;

                  tPlayer.iExp -= iExp;
                  tPlayer.tInventory.iGold -= iGold;

                  cout << "Player " << tPlayer.strName << " lost " << iExp
                       << " Exp." << endl;
                  cout << "Player " << tPlayer.strName << " lost " << iGold
                       << " Golds." << endl;

                  // restore player's stats to initial values
                  tPlayer.iHP = tPlayer.iHPMax;
                  tPlayer.iMP = tPlayer.iMPMax;
                }
                system("read");
              } break;
              case BATTLE_BACK:
                break;
              default:
                break;
            }
          }
        }
        break;
        case MM_STORE: {
          while (true) {
            system("clear");
            cout << "***** STORE *****" << endl;
            cout << "1. Weapon" << endl;
            cout << "2. Armor" << endl;
            cout << "3. Back" << endl;
            cout << "Select menu: ";
            cin >> iMenu;

            if (cin.fail()) {
              cin.clear();
              cin.ignore(1024, '\n');
              continue;
            } else if (iMenu == SM_BACK)
              break;

            switch (iMenu) {
              case SM_WEAPON: {
                system("clear");
                cout << "[ STORE - weapons ]" << endl;
                for (int i = 0; i < STORE_WEAPON_MAX; i++) {
                  cout << i + 1 << ". Name: " << tStoreWeapon[i].strName
                       << "\tKind: " << tStoreWeapon[i].strTypeName << endl;
                  cout << "Damage: " << tStoreWeapon[i].iMin << " ~ "
                       << tStoreWeapon[i].iMax << endl;
                  cout << "Price: " << tStoreWeapon[i].iPrice
                       << "Sell: " << tStoreWeapon[i].iSell << endl;
                  cout << "Description: " << tStoreWeapon[i].strDesc << endl
                       << endl;
                }

                cout << STORE_WEAPON_MAX + 1 << ". BACK" << endl;
                cout << "Money: " << tPlayer.tInventory.iGold << " Golds"
                     << endl;
                cout << "Inventory slots remained: "
                     << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;

                cout << "Which item do you want: ";
                cin >> iMenu;
                if (cin.fail()) {
                  cin.clear();
                  cin.ignore(1024, '\n');
                  continue;
                } else if (iMenu == STORE_WEAPON_MAX + 1) {
                  break;
                } else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1) {
                  cout << "Wrong selection" << endl;
                  system("read");
                  continue;
                }

                // get the index of list of store items
                int iWeaponIndex = iMenu - 1;

                // check whether inventory is full
                if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
                  cout << "Inventory is full" << endl;
                  system("read");
                  continue;
                } else if (tPlayer.tInventory.iGold <
                           tStoreWeapon[iWeaponIndex].iPrice) {
                  cout << "Not enough money" << endl;
                  system("read");
                  continue;
                }

                // add item
                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
                    tStoreWeapon[iWeaponIndex];
                ++tPlayer.tInventory.iItemCount;

                // pay
                tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;
                cout << "You've purchased "
                     << tStoreWeapon[iWeaponIndex].strName << "." << endl;
                cout << "Money: " << tPlayer.tInventory.iGold << endl;
                system("read");
              } break;
              case SM_ARMOR: {
                system("clear");
                cout << "[ STORE - armor ]" << endl;

                for (int i = 0; i < STORE_ARMOR_MAX; i++) {
                  cout << i + 1 << ". Name: " << tStoreArmor[i].strName
                       << "\tKind: " << tStoreArmor[i].strTypeName << endl;
                  cout << "Damage: " << tStoreArmor[i].iMin << " ~ "
                       << tStoreArmor[i].iMax << endl;
                  cout << "Price: " << tStoreArmor[i].iPrice
                       << "Sell: " << tStoreArmor[i].iSell << endl;
                  cout << "Description: " << tStoreArmor[i].strDesc << endl
                       << endl;
                }

                cout << STORE_ARMOR_MAX + 1 << ". BACK" << endl;
                cout << "Money: " << tPlayer.tInventory.iGold << " Golds"
                     << endl;
                cout << "Inventory slots remained: "
                     << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;

                cout << "Which item do you want: ";
                cin >> iMenu;
                if (cin.fail()) {
                  cin.clear();
                  cin.ignore(1024, '\n');
                  continue;
                } else if (iMenu == STORE_ARMOR_MAX + 1) {
                  break;
                } else if (iMenu < 1 || iMenu > STORE_ARMOR_MAX + 1) {
                  cout << "Wrong selection" << endl;
                  system("read");
                  continue;
                }

                // get the index of list of store items
                int iArmorIndex = iMenu - 1;

                // check whether inventory is full
                if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
                  cout << "Inventory is full" << endl;
                  system("read");
                  continue;
                } else if (tPlayer.tInventory.iGold <
                           tStoreArmor[iArmorIndex].iPrice) {
                  cout << "Not enough money" << endl;
                  system("read");
                  continue;
                }

                // add item
                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
                    tStoreArmor[iArmorIndex];
                ++tPlayer.tInventory.iItemCount;

                // pay
                tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;
                cout << "You've purchased " << tStoreArmor[iArmorIndex].strName
                     << "." << endl;
                cout << "Money: " << tPlayer.tInventory.iGold << endl;
                system("read");
              } break;
              case SM_BACK: {
              } break;
            }
          }
        } break;
        case MM_INVENTORY: {
          system("clear");
          cout << "***** INVENTORY *****" << endl;

          // print player's data
          cout << "Player's Data  >>>>>>>>>>>>>>>>>>>>>>>>" << endl;
          cout << "Name: " << tPlayer.strName << "\t"
               << "Job: " << tPlayer.strJobName << endl;
          cout << "Level: " << tPlayer.iLevel << "\t"
               << "Exp: " << tPlayer.iExp << endl;
          cout << "Attack: " << tPlayer.iAttackMin << " ~ "
               << tPlayer.iAttackMax << endl;
          cout << "Armor: " << tPlayer.iArmorMin << " ~ " << tPlayer.iArmorMax
               << endl;
          cout << "HP: " << tPlayer.iHP << " / " << tPlayer.iHPMax << endl;
          cout << "MANA: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
          cout << "Gold: " << tPlayer.tInventory.iGold << endl << endl;

          for (int i = 0; i < tPlayer.tInventory.iItemCount; i++) {
            cout << i + 1 << ". Name: " << tPlayer.tInventory.tItem[i].strName
                 << "\tKind: " << tPlayer.tInventory.tItem[i].strTypeName
                 << endl;
            cout << "Damage: " << tPlayer.tInventory.tItem[i].iMin << " ~ "
                 << tPlayer.tInventory.tItem[i].iMax << endl;
            cout << "Price: " << tPlayer.tInventory.tItem[i].iPrice
                 << "Sell: " << tPlayer.tInventory.tItem[i].iSell << endl;
            cout << "Description: " << tPlayer.tInventory.tItem[i].strDesc
                 << endl
                 << endl;
          }
          system("read");
        } break;
        case MM_EXIT: {
        } break;
        default:
          cout << "Wrong selection." << endl;
      }
    }
  }

  return 0;
}