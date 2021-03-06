#ifndef __CARET_H__
#define __CARET_H__

#include <windows.h>

#include "Object.h"

typedef Object Caret;

struct CaretAttr
{
  unsigned char xoff;
  unsigned char yoff;
  unsigned char surf_no;
};

extern Caret g_Carets[32];

void ResetCaret();
void ResetCaret2();
void ActCaret();
void PutCaret(RECT *rcView);
BOOL SetCaret(int type, int x, int y, intptr_t param);

#endif