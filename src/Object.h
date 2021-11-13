#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <windows.h>

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
    int type2;
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
int CountNpCharType(int type);
void ClearReplaceNpChar(int a1, int a2);

void HitMapGeneric(Object *o, void (*func)(Object *, int, int, int), int a3);

extern Object EntityTbl[256];
extern int EntityCreateCount;
extern char KagomeCount;

#endif