#ifndef __BULLET_H__
#define __BULLET_H__

#include <windows.h>

#include "Object.h"

typedef Object Bullet;

struct BulletAttr
{
    unsigned int flag;
    unsigned char damage;
    unsigned char xoff;
    unsigned char yoff;
    unsigned char w;
    unsigned char h;
    short life;
};

extern Bullet BulletTbl[32];
extern BulletAttr BulletAttrTbl[9];

Bullet *GetBulletTbl();
void ResetBullet();
void LoadPximgBullet();
void ActBullet();
void HitBulletMap();
void MapCollideBulletProc(Object *bul, int a2, int a3, int a4);
void PutBullet(Bullet *bul);
int CountBullet(int type);
BOOL CreateBullet(int type, int x, int y, int a4, int a5, int max);

#endif