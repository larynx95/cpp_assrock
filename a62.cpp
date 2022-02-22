/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec62. Mario Game 2
https://www.youtube.com/watch?v=ZYbnnXW2Gzc&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=62
******************************************************************************/

#include <windows.h>

#include <iostream>

using namespace std;

#define SAFE_DELETE(p) \
  if (p) {             \
    delete p;          \
    p = NULL;          \
  }

// Stage Max Count
#define STAGE_MAX_COUNT 3

enum STAGE_BLOCK_TYPE {
  SBT_WALL = '0',
  SBT_ROAD = '1',
  SBT_START = '2',
  SBT_END = '3',
  SBT_COIN = '4'
};

// ╔═════════════════════════════╗
// ║  CFileStream class          ║
// ╚═════════════════════════════╝

/* CFileStream Class
- fields    FILE* m_pFile;
            int m_iFileSize;
            bool m_bOpen;
- methods   bool Open(const char* pFileName, const char* pMode)
            bool Close()
            void Read(void* pData, int iSize)
            void Write(void* pData, int iSize)
            void ReadLine(void* pData, int& iSize)
*/

class CFileStream {
 public:
  // constructor
  CFileStream() : m_pFile(NULL), m_iFileSize(0), m_bOpen(false) {}

  // destructor
  ~CFileStream() { Close(); }

 private:
  FILE* m_pFile;
  int m_iFileSize;
  bool m_bOpen;

 public:
  // open file
  bool Open(const char* pFileName, const char* pMode) {
    // if file is already opened
    if (m_bOpen) return false;

    // open file
    m_pFile = fopen(pFileName, pMode);
    if (!m_pFile) return false;

    // get the size of file
    fseek(m_pFile, 0, SEEK_END);
    m_iFileSize = ftell(m_pFile);

    // move cursor back to the beginning
    fseek(m_pFile, 0, SEEK_SET);
    m_bOpen = true;

    return true;
  }

  // close file
  bool Close() {
    // if there's no opened file
    if (!m_bOpen) return false;

    // close file
    fclose(m_pFile);
    m_bOpen = false;
    m_pFile = NULL;
    m_iFileSize = 0;

    return true;
  }

  // read file
  void Read(void* pData, int iSize) {
    // if file is not opened, we can't read
    if (!m_bOpen) return;

    // else, read file
    fread(pData, iSize, 1, m_pFile);
  }

  // write file
  void Write(void* pData, int iSize) {
    // if file is not opened, we can't write
    if (!m_bOpen) return;

    // else, write pData to the file
    fwrite(pData, iSize, 1, m_pFile);
  }

  // read a line
  void ReadLine(void* pData, int& iSize) {
    // if file is not opened
    if (!m_bOpen) return;

    // local variables
    char cData;
    char* pChangeData = (char*)pData;
    iSize = 0;

    // read characters up to line breaker
    while (feof(m_pFile) == 0) {
      fread(&cData, 1, 1, m_pFile);

      if (cData == '\n') break;

      pChangeData[iSize] = cData;
      ++iSize;
    }
  }

  void WriteLine(void* pData, int iSize) {
    if (!m_bOpen) return;

    char* pBuffer = new char[iSize + 1];
    *(pBuffer + iSize) = '\n';

    /* same code, but dangerous
    char* pBuffer = (char*)pData;
    pBuffer[iSize] = '\n';
    */

    fwrite(pBuffer, iSize + 1, 1, m_pFile);

    delete[] pBuffer;
  }
};

// ╔═════════════════════════════╗
// ║  Player class               ║
// ╚═════════════════════════════╝

class CPlayer {
 public:
  CPlayer() {}

  ~CPlayer() {}

 private:
  int m_iX;
  int m_iY;

 public:
  // getters and setters
  int GetX() { return m_iX; }
  int GetY() { return m_iY; }

  void SetPos(int x, int y) {
    m_iX = x;
    m_iY = y;
  }

  bool Init() {
    m_iX = 0;
    m_iY = 8;
    return true;
  }

  void Update() {
    if (GetAsyncKeyState('A') & 0x8000) {
      --m_iX;
      if (m_iX < 0) m_iX = 0;
    }
    if (GetAsyncKeyState('D') & 0x8000) {
      ++m_iX;
      if (m_iX >= 50) m_iX = 49;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
    }
  }
};

// ╔═════════════════════════════╗
// ║  CObjectManager class       ║
// ╚═════════════════════════════╝

class CObjectManager {
 private:
  CObjectManager() { m_pPlayer = NULL; }
  ~CObjectManager() { SAFE_DELETE(m_pPlayer); }

 private:
  static CObjectManager* m_pInst;
  CPlayer* m_pPlayer;

 public:
  static CObjectManager* GetInst() {
    if (!m_pInst) m_pInst = new CObjectManager;
    return m_pInst;
  }

  static void DestroyInst() { SAFE_DELETE(m_pInst); }

  bool Init() {
    m_pPlayer = new CPlayer;
    m_pPlayer->Init();
    return true;
  }

  CPlayer* GetPlayer() { return m_pPlayer; }
};

// ╔═════════════════════════════╗
// ║  CStage class               ║
// ╚═════════════════════════════╝

/* CStage Class
- fields    char m_cStage[10][50]
- methods   bool Init()
            bool Init(const char* pFileName)
*/

class CStage {
 public:
  CStage() {}
  ~CStage() {}

 private:
  char m_cStage[10][50];

 public:
  bool Init() { return true; }

  bool Init(const char* pFileName) {
    CFileStream file;
    // if file is not properly opened
    if (!file.Open(pFileName, "rt")) return false;

    // read a Stage file (member array), initialize it
    for (int i = 0; i < 10; i++) {
      int iSize = 0;
      file.ReadLine(m_cStage[i], iSize);
    }

    return true;
  }

  void Render() {
    CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

    int iX = pPlayer->GetX();
    int iY = pPlayer->GetY();

    // 0: wall, 1: road, 2: start, 3: end, 4: coin
    for (int i = iY - 2; i <= iY + 1; ++i) {
      for (int j = iX; j < iX + 10; ++j) {
        if (i == iY && j == iX)
          cout << "$ ";
        else if (m_cStage[i][j] == SBT_WALL)
          cout << "# ";
        else if (m_cStage[i][j] == SBT_ROAD)
          cout << "  ";
        else if (m_cStage[i][j] == SBT_START)
          cout << "S ";
        else if (m_cStage[i][j] == SBT_END)
          cout << "E ";
        else if (m_cStage[i][j] == SBT_COIN)
          cout << "@ ";
      }
      cout << endl;
    }
  }
};

// ╔═════════════════════════════╗
// ║  CMapmanger class           ║
// ╚═════════════════════════════╝

/* CMapManager Class
- fields    static CMapManager* m_pInst
- methods   static CMapManager* GetInst()
            static void DestroyInst()
            bool Init()
*/

class CMapManager {
 private:
  CMapManager() {
    for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
      m_pStage[i] = NULL;
    }
  }

  ~CMapManager() {
    for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
      SAFE_DELETE(m_pStage[i]);
    }
  }

 private:
  static CMapManager* m_pInst;
  CStage* m_pStage[STAGE_MAX_COUNT];

 public:
  static CMapManager* GetInst() {
    if (!m_pInst) m_pInst = new CMapManager;
    return m_pInst;
  }

  static void DestroyInst() { SAFE_DELETE(m_pInst); }

  bool Init() {
    const char* pStageFile[3] = {"Stage1.txt", "Stage1.txt", "Stage1.txt"};

    for (int i = 0; i < STAGE_MAX_COUNT; ++i) {
      m_pStage[i] = new CStage;
      if (!m_pStage[i]->Init(pStageFile[i])) return false;
    }
    return true;
  }

  void Run() {}

  void Render() { m_pStage[0]->Render(); }
};

// ╔═════════════════════════════╗
// ║  CCore class                ║
// ╚═════════════════════════════╝

/* CCore Class
- fields    static CCore* m_pInst
- methods   static CCore* GetInst()
            static void DestroyInst()
            bool Init()
            void Run()
*/

class CCore {
 private:
  CCore() {}

  ~CCore() {
    CMapManager::DestroyInst();
    CObjectManager::DestroyInst();
  }

 private:
  static CCore* m_pInst;

 public:
  static CCore* GetInst() {
    if (!m_pInst) m_pInst = new CCore;
    return m_pInst;
  }

  static void DestroyInst() { SAFE_DELETE(m_pInst); }

  bool Init() {
    if (!CMapManager::GetInst()->Init()) return false;
    if (!CObjectManager::GetInst()->Init()) return false;
    return true;
  }

  void Run() {
    // CMapManager::GetInst()->Render();
    CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

    while (true) {
      system("clear");
      pPlayer->Update();
      CMapManager::GetInst()->Render();
      Sleep(100);
    }
  }
};

// ╔═════════════════════════════╗
// ║  Global Variables           ║
// ╚═════════════════════════════╝

CCore* CCore::m_pInst = NULL;
CMapManager* CMapManager::m_pInst = NULL;
CObjectManager* CObjectManager::m_pInst = NULL;

// ╔═════════════════════════════╗
// ║  Main function              ║
// ╚═════════════════════════════╝

int main() {
  if (!CCore::GetInst()->Init()) {
    cout << "Initialization Failed!!" << endl;
    CCore::DestroyInst();
    return 0;
  }

  CCore::GetInst()->Run();

  CCore::DestroyInst();

  return 0;
}
