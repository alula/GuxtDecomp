#ifndef __CARET_H__
#define __CARET_H__

#include <windows.h>

struct Caret
{
  int cond;
  int x;
  int y;
  int xm;
  int ym;
  int xoff;
  int yoff;
  int w;
  int h;
  int surf;
  int type;
  int state;
  int count1;
  int count2;
  int count3;
  int life;
  int damage;
  int flag;
  int shock;
  int score;
  int type2;
  int child;
  int rot1;
  int count4;
  int num;
  int destroyHitVoice;
  RECT rect;
};

struct CaretAttr
{
  unsigned char xoff;
  unsigned char yoff;
  unsigned char surf_no;
};

extern Caret g_Carets[32];

BOOL SetCaret(int type, int x, int y, int param);

#endif