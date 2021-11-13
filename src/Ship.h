#ifndef __SHIP_H__
#define __SHIP_H__

#include <windows.h>

struct Ship
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

extern Ship ship;

Ship *GetShip();
void ResetShip();

void LoadPximgPlayerInit();

void KillShip();
void ShipStateEndingProc();
void SetShipInvincibility();
void SetShipEnding();
int LoadPximgCharactor();

#endif