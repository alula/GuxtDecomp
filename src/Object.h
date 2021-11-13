#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <windows.h>
#include <stdint.h>

struct Object
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
    // this field stores pointers sometimes
    intptr_t type2;
    int child;
    int rot1;
    int count4;
    int num;
    int destroyHitVoice;
    RECT rect;
};

struct NpcAttr
{
    unsigned char flag;
    unsigned char unk;
    unsigned char score;
    unsigned char damage;
    unsigned char xoff;
    unsigned char yoff;
    unsigned char w;
    unsigned char h;
    unsigned short life;
    unsigned char surf;
    unsigned char destroyHitVoice;
};

void SetBackgroundColor();

void PutObject(RECT *rcView, Object *obj, int frame_x, int frame_y);

Object *GetNpcTable();
void ResetEntities();
void LoadPximgEntities();
void ActNpc();
void HitEntityMap();
void MapCollideEntityProc(Object *a1, int a2, int a3, int a4);
void PutNpChar2(RECT *rcView);
void PutNpChar(RECT *rcView);

void CreateEntity(int type, int x, int y, intptr_t type2);
void DamageNpChar(Object *o, int dmg);
int CountNpCharType(int type);
void ClearReplaceNpChar(int a1, int a2);

void HitNpCharBullet();
void HitShipPowerup();
void HitMapGeneric(Object *o, void (*func)(Object *, int, int, int), int a3);

extern Object EntityTbl[256];
extern int EntityCreateCount;
extern char KagomeCount;

#endif