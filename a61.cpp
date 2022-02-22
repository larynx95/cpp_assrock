/******************************************************************************
Assort Rock C/C++ Lectures, 2017.7

Lec61. Mario Game 1
https://www.youtube.com/watch?v=nD5OuMdS9FU&list=PL4SIC1d_ab-b4zy_3FDRIiohszShOZ0PK&index=61
******************************************************************************/

#include <iostream>

using namespace std;

#define SAFE_DELETE(p) \
  if (p) {             \
    delete p;          \
    p = NULL;          \
  }

// Stage Max Count
#define STAGE_MAX_COUNT 3

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
  CFileStream() : m_pFile(NULL), m_iFileSize(0), m_bOpen(false) {}

  ~CFileStream() { Close(); }

 private:
  FILE* m_pFile;
  int m_iFileSize;
  bool m_bOpen;

 public:
  bool Open(const char* pFileName, const char* pMode) {
    if (m_bOpen) return false;

    m_pFile = fopen(pFileName, pMode);

    if (!m_pFile) return false;

    // get the position of file cursor
    fseek(m_pFile, 0, SEEK_END);
    m_iFileSize = ftell(m_pFile);
    fseek(m_pFile, 0, SEEK_SET);

    m_bOpen = true;

    return true;
  }

  bool Close() {
    if (!m_bOpen) {
      return false;
    }

    m_bOpen = false;
    fclose(m_pFile);
    m_pFile = NULL;

    m_iFileSize = 0;

    return true;
  }

  void Read(void* pData, int iSize) {
    // if file is not opened, we can't read/write
    if (!m_bOpen) return;
    fread(pData, iSize, 1, m_pFile);
  }

  void Write(void* pData, int iSize) {
    if (!m_bOpen) return;
    fwrite(pData, iSize, 1, m_pFile);
  }

  void ReadLine(void* pData, int& iSize) {
    if (!m_bOpen) return;
    char cData;
    char* pChangeData = (char*)pData;
    iSize = 0;

    while (feof(m_pFile) == 0) {
      fread(&cData, 1, 1, m_pFile);
      if (cData == '\n') break;

      pChangeData[iSize] = cData;
      ++iSize;
    }
  }
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
    if (!file.Open(pFileName, "rt")) return false;

    for (int i = 0; i < 10; i++) {
      int iSize = 0;
      file.ReadLine(m_cStage[i], iSize);

      for (int j = 0; j < 50; ++j) {
        cout << m_cStage[i][j];
      }
      cout << endl;
    }
    cout << endl << endl;

    return true;
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

  ~CCore() { CMapManager::DestroyInst(); }

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
    return true;
  }

  void Run() {}
};

// ╔═════════════════════════════╗
// ║  Global Variables           ║
// ╚═════════════════════════════╝

CCore* CCore::m_pInst = NULL;
CMapManager* CMapManager::m_pInst = NULL;

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
