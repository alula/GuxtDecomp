#ifndef __TEXT_H__
#define __TEXT_H__

#include <windows.h>

void PutNumber(RECT *rcView, int x, int y, signed int value, char flags, unsigned int surf);

int PutTextObject(RECT *rcView, int pos_x, int pos_y, const char *text, int a5, int surf_src);

#endif