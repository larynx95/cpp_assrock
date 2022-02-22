#include "FileStream.h"

// constructor
CFileStream::CFileStream() : m_pFile(NULL), m_iFileSize(0), m_bOpen(false) {}

// destructor
CFileStream::~CFileStream() { Close(); }

bool CFileStream::Open(const char* pFileName, const char* pMode) {
  // if file is opened, do not reopen the file
  if (m_bOpen) return false;

  // open file, error handling
  fopen_s(&m_pFile, pFileName, pMode);
  if (!m_pFile) return false;

  // get the position of file cursor
  fseek(m_pFile, 0, SEEK_END);
  m_iFileSize = ftell(m_pFile);
  fseek(m_pFile, 0, SEEK_SET);

  // file is now opened, return true
  m_bOpen = true;
  return true;
}

bool CFileStream::Close() {
  // if file is not opened, there's nothing to be closed
  if (!m_bOpen) return false;

  // close file
  fclose(m_pFile);
  m_bOpen = false;
  m_pFile = NULL;
  m_iFileSize = 0;

  return true;
}

void CFileStream::Read(void* pData, int iSize) {
  // if file is not opened, we can't read/write
  if (!m_bOpen) return;
  fread(pData, iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* pData, int& iSize) {
  // if file is not opened, we can't read anything
  if (!m_bOpen) return;

  // variables
  char cData = NULL;
  char* pChangeData = (char*)pData;
  iSize = 0;

  // read each character one by one up to line breaker
  while (feof(m_pFile) == 0) {
    fread(&cData, 1, 1, m_pFile);
    if (cData == '\n') break;

    pChangeData[iSize] = cData;
    ++iSize;  // increase iSize var with its reference
  }
}

void CFileStream::Write(void* pData, int iSize) {
  // if file is not opened, we can't read/write
  if (!m_bOpen) return;
  fread(pData, iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* pData, int& iSize) {
  if (!m_bOpen) return;

  char* pBuffer = new char[iSize + 1];
  pBuffer[iSize] = '\n';
  /*
  char* pBuffer = (char*)pData;
  *(pBuffer + iSize) = '\n';
  */

  fwrite(pData, iSize + 1, 1, m_pFile);

  delete[] pBuffer;
}
