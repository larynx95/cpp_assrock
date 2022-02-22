/**********************************************************
 * CFileStream
 *
 * class for I/O utility functions
 *********************************************************/

#pragma once

#include "value.h"

class CFileStream {
 public:
  CFileStream();   // constructor
  ~CFileStream();  // destructor

 private:
  FILE* m_pFile;    // file pointer
  int m_iFileSize;  // file size
  bool m_bOpen;     // check if file is opened

 public:
  bool Open(const char* pFileName, const char* pMode);
  bool Close();
  void Read(void* pData, int iSize);
  void Write(void* pData, int iSize);
  void ReadLine(void* pData, int& iSize);
  void WriteLine(void* pData, int& iSize);
};
