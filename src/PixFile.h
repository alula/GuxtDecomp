#ifndef __PIXFILE_H__
#define __PIXFILE_H__

#include <windows.h>
#include <stdio.h>

struct PixFile
{
  int type;
  FILE *fp;
  void *res;
  unsigned int bytesRead;
  unsigned int size;
};

BOOL OpenResource_(HMODULE hModule, LPCSTR lpName, LPCSTR lpType, PixFile *file);
int ReadFromFile(void *p, size_t size, int num, PixFile *_p_desc);
BOOL SeekResource(PixFile *file, int pos, int mode);
void CloseResource_(PixFile *a1);

#endif