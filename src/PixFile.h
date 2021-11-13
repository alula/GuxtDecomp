#ifndef __PIXFILE_H__
#define __PIXFILE_H__

#include <stdio.h>

struct PixFile
{
  char type;
  FILE *fp;
  void* res;
  unsigned int bytesRead;
  unsigned int size;
};

#endif