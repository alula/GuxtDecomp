#ifndef __PLAYRECORD_H__
#define __PLAYRECORD_H__

#include <windows.h>

BOOL InitPlayRecord();
void FreePlayRecord();
void NewPlayRecord();
BOOL ReadPlayRecord(const char *a1, BOOL *a2);

#endif