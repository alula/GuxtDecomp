#include <windows.h>

#include "Bullet.h"
#include "Caret.h"
#include "Game.h"
#include "GameAttr.h"
#include "Object.h"
#include "TrigFuncs.h"
#include "Ship.h"
#include "Stage.h"
#include "Sound.h"

Bullet BulletTbl[32];
BulletAttr BulletAttrTbl[9] =
    {
        {0u, 4u, 4u, 4u, 2u, 2u, 1},
        {0u, 2u, 4u, 4u, 2u, 4u, 1},
        {0u, 4u, 4u, 4u, 2u, 4u, 1},
        {0u, 2u, 4u, 4u, 2u, 4u, 1},
        {0u, 0u, 0u, 0u, 0u, 0u, 100},
        {0u, 2u, 4u, 4u, 4u, 4u, 100},
        {0u, 3u, 4u, 4u, 3u, 3u, 1},
        {104u, 2u, 4u, 8u, 2u, 3u, 100},
        {40u, 8u, 20u, 20u, 18u, 18u, 100}};

//----- (004016B0) --------------------------------------------------------
void ActBullet0(Bullet *a1)
{
    switch (a1->type2)
    {
    case 0:
        a1->ym = -8192;
        break;
    case 6:
        a1->xm = 6144;
        a1->ym = 6144;
        break;
    case 8:
        a1->ym = 0x2000;
        break;
    case 0xA:
        a1->xm = -6144;
        a1->ym = 6144;
        break;
    default:
        break;
    }
    a1->x += a1->xm;
    a1->y += a1->ym;
    a1->rect.left = 64;
    a1->rect.top = 0;
    a1->rect.right = 72;
    a1->rect.bottom = 8;
    a1->rect.left += 8 * (a1->type2 % 8);
    a1->rect.right += 8 * (a1->type2 % 8);
}

//----- (004017E0) --------------------------------------------------------
void ActBullet1(Bullet *a1)
{
    switch (a1->type2)
    {
    case 0:
        a1->ym = -0x1800u;
        break;
    case 1:
        a1->ym = -0x1400u;
        a1->xm = 0xC00;
        break;
    case 2:
        a1->ym = -0x1000u;
        a1->xm = 0x1000;
        break;
    case 3:
        a1->ym = -0xC00u;
        a1->xm = 0x1400;
        break;
    case 6:
        a1->xm = 0x1000;
        a1->ym = 0x1000;
        break;
    case 8:
        a1->ym = 0x1800;
        break;
    case 0xA:
        a1->xm = -0x1000u;
        a1->ym = 0x1000;
        break;
    case 0xD:
        a1->ym = -0xC00u;
        a1->xm = -0x1400u;
        break;
    case 0xE:
        a1->ym = -0x1000u;
        a1->xm = -0x1000u;
        break;
    case 0xF:
        a1->ym = -0x1400u;
        a1->xm = -0xC00u;
        break;
    default:
        break;
    }
    switch (a1->type2)
    {
    case 0:
    case 8:
        a1->w = 0;
        a1->h = 0x1000;
        break;
    case 4:
    case 0xC:
        a1->w = 0x1000;
        a1->h = 0;
        break;
    default:
        a1->w = 0x800;
        a1->h = 0x800;
        break;
    }
    a1->x += a1->xm;
    a1->y += a1->ym;
    a1->rect.left = 0;
    a1->rect.top = 8;
    a1->rect.right = 8;
    a1->rect.bottom = 16;
    a1->rect.left += 8 * (a1->type2 % 8);
    a1->rect.right += 8 * (a1->type2 % 8);
}

//----- (00401A30) --------------------------------------------------------
void ActBullet2(Bullet *a1)
{
    switch (a1->type2)
    {
    case 0:
        a1->ym = -6144;
        break;
    case 1:
        a1->ym = -5120;
        a1->xm = 3072;
        break;
    case 2:
        a1->ym = -4096;
        a1->xm = 4096;
        break;
    case 3:
        a1->ym = -3072;
        a1->xm = 5120;
        break;
    case 6:
        a1->xm = 4096;
        a1->ym = 4096;
        break;
    case 8:
        a1->ym = 6144;
        break;
    case 0xA:
        a1->xm = -4096;
        a1->ym = 4096;
        break;
    case 0xD:
        a1->ym = -3072;
        a1->xm = -5120;
        break;
    case 0xE:
        a1->ym = -4096;
        a1->xm = -4096;
        break;
    case 0xF:
        a1->ym = -5120;
        a1->xm = -3072;
        break;
    default:
        break;
    }
    a1->x += a1->xm;
    a1->y += a1->ym;
    a1->rect.left = 0;
    a1->rect.top = 16;
    a1->rect.right = 8;
    a1->rect.bottom = 24;
    a1->rect.left += 8 * (a1->type2 % 16);
    a1->rect.right += 8 * (a1->type2 % 16);
}

//----- (00401C10) --------------------------------------------------------
void ActBullet3(Bullet *a1)
{
    int v1; // ecx
    int v2; // [esp+4h] [ebp-14h]

    v1 = a1->count1;
    a1->count1 = v1 + 1;
    if (v1 == 3)
    {
        if (a1->type2)
        {
            if (a1->type2 == 3)
                a1->x += 3072;
            else
                a1->x -= 2048;
            a1->y += 2048;
        }
        else
        {
            a1->x = a1->x;
        }
        a1->type2 = 0;
    }
    v2 = a1->type2;
    if (v2)
    {
        if (v2 == 3)
        {
            a1->ym = -3072;
            a1->xm = 6144;
        }
        else if (v2 == 13)
        {
            a1->ym = -3072;
            a1->xm = -6144;
        }
    }
    else
    {
        a1->ym = -8192;
        a1->xm = 0;
    }
    switch (a1->type2)
    {
    case 0:
    case 8:
        a1->w = 0;
        a1->h = 4096;
        break;
    case 4:
    case 0xC:
        a1->w = 4096;
        a1->h = 0;
        break;
    default:
        a1->w = 2048;
        a1->h = 2048;
        break;
    }
    a1->x += a1->xm;
    a1->y += a1->ym;
    a1->rect.left = 0;
    a1->rect.top = 24;
    a1->rect.right = 8;
    a1->rect.bottom = 32;
    a1->rect.left += 8 * (a1->type2 % 8);
    a1->rect.right += 8 * (a1->type2 % 8);
}

//----- (00401E20) --------------------------------------------------------
void ActBullet4(Bullet *a1)
{
    if (++a1->count1 < 7)
        CreateBullet(3, a1->x, a1->y, a1->type2, a1->count4 + 10, 10);

    if (a1->count1 >= 15)
        a1->cond = 0;
}

//----- (00401E80) --------------------------------------------------------
void ActBullet5(Bullet *a1)
{
    int v1;             // [esp+0h] [ebp-8h]
    unsigned __int8 v2; // [esp+7h] [ebp-1h]

    v1 = a1->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        a1->state = 10;
        a1->cond |= 4u;
        if (a1->type2)
            a1->child = 128;
    }
    if (a1->count1 < 40)
        ++a1->count1;
    a1->child += 8;
    a1->child %= 256;
    v2 = a1->child;
    a1->x = ship.x + a1->count1 * GetCos(v2) / 2;
    a1->y = ship.y + a1->count1 * GetSin(v2) / 2;

LABEL_9:
    a1->life = 100;
    a1->rect.left = 104;
    a1->rect.top = 0;
    a1->rect.right = 112;
    a1->rect.bottom = 8;
}

//----- (00401FA0) --------------------------------------------------------
void ActBullet6(Bullet *a1)
{
    if (!a1->state)
    {
        a1->rect.left = 112;
        a1->rect.top = 0;
        a1->rect.right = 120;
        a1->rect.bottom = 8;
        a1->xm = 6 * GetCos(a1->type2);
        a1->ym = 6 * GetSin(a1->type2);
    }
    a1->x += a1->xm;
    a1->y += a1->ym;
}

//----- (00402040) --------------------------------------------------------
void ActBullet7(Bullet *a1)
{
    RECT rc[2]; // [esp+0h] [ebp-20h]

    rc[0].left = 88;
    rc[0].top = 0;
    rc[0].right = 96;
    rc[0].bottom = 16;
    rc[1].left = 96;
    rc[1].top = 0;
    rc[1].right = 104;
    rc[1].bottom = 16;
    if ((a1->cond & 8) != 0)
    {
        a1->cond = 0;
        CreateBullet(8, a1->x, a1->y, 0, a1->count4, 10);
    }
    else
    {
        a1->ym -= 256;
        a1->xm = 0;
        a1->x += a1->xm;
        a1->y += a1->ym;
        a1->rect = rc[++a1->count2 % 2];
    }
}

//----- (00402150) --------------------------------------------------------
void ActBullet8(Bullet *a1)
{
    static RECT rcBullet8[6] =
        {
            {0, 48, 40, 88},
            {40, 48, 80, 88},
            {80, 48, 120, 88},
            {0, 88, 40, 128},
            {40, 88, 80, 128},
            {80, 88, 120, 128}};

    if (a1->state)
    {
        a1->damage = 0;
        if (++a1->count2 > 5)
            a1->cond = 0;
    }
    else
    {
        ++a1->state;
        PlaySound(14);
    }
    a1->rect = rcBullet8[a1->count2];
}

//----- (004021D0) --------------------------------------------------------
Bullet *GetBulletTbl()
{
    return BulletTbl;
}

//----- (004021E0) --------------------------------------------------------
void ResetBullet()
{
    int i; // [esp+0h] [ebp-8h]

    memset(BulletTbl, 0, sizeof(BulletTbl));
    for (i = 0; i < 32; ++i)
        ;
}

//----- (00402230) --------------------------------------------------------
void LoadPximgBullet()
{
    LoadPximg("bullet", 2);
    ResetBullet();
}

static void (*bulletFuncTbl[9])(Bullet *) = {
    ActBullet0,
    ActBullet1,
    ActBullet2,
    ActBullet3,
    ActBullet4,
    ActBullet5,
    ActBullet6,
    ActBullet7,
    ActBullet8};

//----- (00402250) --------------------------------------------------------
void ActBullet()
{
    for (int i = 0; i < 32; ++i)
    {
        Bullet *bul = &BulletTbl[i];
        if ((bul->cond & 1) != 0)
        {
            bulletFuncTbl[bul->type](bul);
            if ((bul->cond & 2) != 0)
                bul->cond &= ~1u;
            if ((bul->cond & 4) == 0 && (bul->x < -0x2000u || bul->x > 0x20000 || bul->y < -0x2000u || bul->y > 0x2A000))
                bul->cond &= ~1u;
        }
    }
}

//----- (00402310) --------------------------------------------------------
void HitBulletMap()
{
    for (int i = 0; i < 32; ++i)
    {
        if ((BulletTbl[i].cond & 1) != 0)
            HitMapGeneric(&BulletTbl[i], MapCollideBulletProc, 1);
    }
}

//----- (00402360) --------------------------------------------------------
void MapCollideBulletProc(Bullet *bul, int a2, int a3, int a4)
{
    if ((bul->cond & 4) == 0)
    {
        if ((bul->flag & 0x20) != 0)
        {
            bul->cond |= 8u;
        }
        else
        {
            bul->cond = 0;
            SetCaret(2, bul->x, bul->y, 0);
            PlaySound(37);
        }
    }
}

//----- (004023C0) --------------------------------------------------------
void PutBullet(RECT *rcView)
{
    for (int i = 0; i < 32; ++i)
        PutObject(rcView, &BulletTbl[i], GetStageXOffset() / 1024, GetStageScroll() / 1024);
}

//----- (00402430) --------------------------------------------------------
int CountBullet(int type)
{
    int i;  // [esp+0h] [ebp-8h]
    int v3; // [esp+4h] [ebp-4h]

    v3 = 0;
    for (i = 0; i < 32; ++i)
    {
        if ((BulletTbl[i].cond & 1) != 0 && BulletTbl[i].count4 == type)
            ++v3;
    }
    return v3;
}

//----- (00402490) --------------------------------------------------------
BOOL CreateBullet(int type, int x, int y, int a4, int a5, int max)
{
    int i;             // [esp+0h] [ebp-Ch]
    BulletAttr *bAttr; // [esp+4h] [ebp-8h]
    Bullet *bul;       // [esp+8h] [ebp-4h]

    if (CountBullet(a5) >= max)
        return 0;
    for (i = 0; i < 32 && (BulletTbl[i].cond & 1) != 0; ++i)
        ;
    if (i == 32)
        return 0;
    bul = &BulletTbl[i];
    bAttr = &BulletAttrTbl[type];
    memset(bul, 0, sizeof(Bullet));
    bul->surf = 2;
    bul->type = type;
    bul->cond = 1;
    bul->flag = bAttr->flag | 4;
    bul->x = x;
    bul->y = y;
    bul->type2 = a4;
    bul->xoff = bAttr->xoff << 10;
    bul->yoff = bAttr->yoff << 10;
    bul->w = bAttr->w << 10;
    bul->h = bAttr->h << 10;
    bul->life = bAttr->life;
    bul->damage = bAttr->damage;
    bul->count4 = a5;
    return 1;
}