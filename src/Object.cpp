#include <windows.h>

#include "Object.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Stage.h"
#include "Sound.h"

unsigned int backgroundColor;

//----- (004015B0) --------------------------------------------------------
void SetBackgroundColor()
{
    backgroundColor = ConvertRGBToNative(0xA0u);
}

//----- (004015D0) --------------------------------------------------------
void PutObject(RECT *rcView, Object *obj, int frame_x, int frame_y)
{
    int x;  // [esp+0h] [ebp-8h]
    int xa; // [esp+0h] [ebp-8h]
    int y;  // [esp+4h] [ebp-4h]
    int ya; // [esp+4h] [ebp-4h]

    if ((obj->cond & 1) == 0)
        return;

    x = obj->x - obj->xoff;
    y = obj->y - obj->yoff;
    if (x < 0)
        x -= 1023;
    if (y < 0)
        y -= 1023;
    if ((obj->flag & 0x10) != 0)
    {
        xa = x / 1024 - frame_x;
        ya = y / 1024 - frame_y;
    }
    else
    {
        xa = x / 1024;
        ya = y / 1024;
    }

    PutBitmap3(rcView, xa, ya, &obj->rect, obj->surf);
}

//----- (00403170) --------------------------------------------------------
Object *GetNpcTable()
{
    return EntityTbl;
}

//----- (00403180) --------------------------------------------------------
void ResetEntities()
{
    EntityCreateCount = 0;
    memset(EntityTbl, 0, sizeof(EntityTbl));
}

//----- (004031B0) --------------------------------------------------------
void LoadPximgEntities()
{
    LoadPximg("enemy_generic", 5);
    LoadPximg("power", 15);
    LoadPximg("caret", 7);
    LoadPximg("popup", 8);
    LoadPximg("bonus", 14);
    ResetEntities();
}

Object EntityTbl[256];
int EntityCreateCount;
char KagomeCount;
static NpcAttr NpcAttrTbl[122] =
    {
        {16u, 3u, 1u, 1u, 8u, 8u, 7u, 7u, 6, 5u, 0u},
        {0u, 8u, 0u, 0u, 16u, 16u, 0u, 0u, 0, 7u, 0u},
        {0u, 3u, 0u, 0u, 24u, 16u, 0u, 0u, 0, 6u, 0u},
        {0u, 2u, 0u, 0u, 8u, 4u, 0u, 0u, 0, 6u, 0u},
        {0u, 5u, 0u, 0u, 4u, 4u, 0u, 0u, 0, 7u, 0u},
        {0u, 6u, 2u, 0u, 12u, 12u, 8u, 8u, 1000, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {2u, 8u, 4u, 0u, 8u, 8u, 8u, 8u, 0, 5u, 0u},
        {67u, 5u, 1u, 1u, 8u, 8u, 5u, 5u, 3, 5u, 0u},
        {67u, 5u, 1u, 1u, 8u, 8u, 6u, 6u, 8, 5u, 0u},
        {0u, 9u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 3u, 1u, 20u, 8u, 5u, 4u, 24, 6u, 1u},
        {10u, 4u, 0u, 1u, 0u, 0u, 6u, 2u, 0, 6u, 0u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {0u, 4u, 7u, 1u, 68u, 16u, 7u, 6u, 1000, 6u, 2u},
        {0u, 4u, 3u, 1u, 8u, 8u, 4u, 3u, 100, 6u, 0u},
        {0u, 4u, 0u, 1u, 12u, 20u, 12u, 16u, 100, 6u, 3u},
        {2u, 8u, 0u, 1u, 8u, 8u, 2u, 4u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {67u, 4u, 0u, 1u, 8u, 8u, 5u, 5u, 6, 5u, 3u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 5u, 0u, 1u, 8u, 8u, 5u, 5u, 6, 5u, 3u},
        {0u, 6u, 1u, 1u, 12u, 12u, 8u, 8u, 6, 5u, 0u},
        {0u, 6u, 1u, 0u, 12u, 12u, 8u, 8u, 6, 5u, 0u},
        {67u, 5u, 2u, 1u, 12u, 12u, 8u, 8u, 100, 6u, 0u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {67u, 4u, 0u, 1u, 8u, 8u, 5u, 5u, 100, 5u, 3u},
        {0u, 8u, 0u, 0u, 4u, 4u, 0u, 0u, 0, 7u, 0u},
        {67u, 4u, 4u, 1u, 16u, 16u, 12u, 12u, 36, 6u, 2u},
        {67u, 6u, 2u, 1u, 12u, 12u, 10u, 8u, 10, 5u, 1u},
        {0u, 4u, 7u, 1u, 28u, 24u, 0u, 0u, 1000, 6u, 2u},
        {10u, 4u, 0u, 1u, 20u, 52u, 9u, 36u, 0, 6u, 0u},
        {10u, 4u, 0u, 1u, 20u, 24u, 12u, 15u, 1000, 6u, 3u},
        {67u, 6u, 0u, 1u, 8u, 8u, 4u, 4u, 1, 6u, 3u},
        {0u, 4u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 2u},
        {0u, 0u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 7u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {16u, 4u, 4u, 1u, 16u, 16u, 12u, 12u, 100, 6u, 2u},
        {16u, 3u, 2u, 1u, 8u, 8u, 7u, 7u, 10, 5u, 3u},
        {16u, 3u, 2u, 1u, 8u, 8u, 7u, 7u, 6, 5u, 3u},
        {16u, 4u, 3u, 1u, 16u, 8u, 8u, 6u, 24, 6u, 1u},
        {67u, 5u, 1u, 1u, 8u, 8u, 5u, 5u, 2, 5u, 0u},
        {16u, 5u, 2u, 1u, 8u, 8u, 6u, 6u, 2, 6u, 0u},
        {2u, 8u, 4u, 0u, 8u, 8u, 6u, 6u, 0, 14u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 4u, 0u, 0u, 48u, 40u, 0u, 0u, 0, 6u, 0u},
        {16u, 3u, 3u, 1u, 8u, 8u, 6u, 6u, 6, 6u, 3u},
        {16u, 3u, 7u, 1u, 32u, 28u, 16u, 16u, 0, 6u, 3u},
        {0u, 9u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 15u, 0u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 5u, 0u, 0u, 0u, 0u, 6u, 16u, 0, 6u, 2u},
        {16u, 3u, 3u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 3u},
        {0u, 9u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 8u, 0u},
        {16u, 4u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 6u, 3u},
        {16u, 3u, 0u, 0u, 8u, 8u, 6u, 6u, 4, 6u, 0u},
        {0u, 6u, 1u, 0u, 12u, 12u, 8u, 8u, 3, 5u, 0u},
        {16u, 3u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 5u, 3u},
        {16u, 3u, 0u, 1u, 8u, 8u, 8u, 8u, 1, 5u, 3u},
        {16u, 4u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 15u, 0u},
        {0u, 8u, 0u, 1u, 8u, 8u, 3u, 3u, 1, 5u, 3u},
        {0u, 6u, 0u, 0u, 12u, 12u, 8u, 8u, 1000, 5u, 0u},
        {16u, 3u, 2u, 1u, 8u, 12u, 6u, 10u, 3, 6u, 0u},
        {67u, 5u, 3u, 1u, 16u, 12u, 10u, 8u, 10, 6u, 1u},
        {16u, 3u, 2u, 1u, 16u, 8u, 15u, 6u, 14, 6u, 1u},
        {16u, 3u, 4u, 1u, 8u, 8u, 7u, 7u, 40, 5u, 3u},
        {16u, 3u, 1u, 1u, 8u, 12u, 7u, 7u, 100, 6u, 3u},
        {67u, 5u, 4u, 1u, 12u, 12u, 9u, 9u, 96, 6u, 3u},
        {0u, 4u, 0u, 1u, 4u, 4u, 4u, 4u, 0, 6u, 1u},
        {67u, 6u, 1u, 1u, 8u, 8u, 5u, 5u, 5, 5u, 0u},
        {0u, 4u, 0u, 1u, 4u, 4u, 4u, 4u, 0, 6u, 1u},
        {16u, 3u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 5u, 3u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {0u, 7u, 0u, 1u, 24u, 24u, 16u, 16u, 1000, 6u, 2u},
        {0u, 8u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 2u},
        {0u, 4u, 0u, 1u, 4u, 4u, 3u, 3u, 1000, 6u, 3u},
        {0u, 6u, 0u, 1u, 8u, 8u, 3u, 3u, 1000, 6u, 3u},
        {0u, 5u, 0u, 1u, 4u, 4u, 3u, 3u, 1000, 6u, 3u},
        {16u, 5u, 1u, 1u, 8u, 8u, 6u, 6u, 2, 6u, 0u},
        {0u, 8u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 2u},
        {0u, 8u, 0u, 1u, 8u, 8u, 5u, 5u, 1, 5u, 3u},
        {0u, 6u, 1u, 1u, 8u, 8u, 5u, 5u, 1000, 6u, 0u},
        {0u, 3u, 0u, 0u, 24u, 16u, 0u, 0u, 0, 6u, 0u},
        {0u, 2u, 0u, 0u, 8u, 4u, 0u, 0u, 0, 6u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 3u, 1u, 16u, 16u, 5u, 4u, 24, 6u, 2u},
        {10u, 4u, 0u, 1u, 0u, 0u, 5u, 7u, 0, 6u, 0u},
        {67u, 5u, 0u, 1u, 4u, 12u, 2u, 5u, 1, 6u, 3u},
        {0u, 2u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 4u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 4u, 2u, 1u, 8u, 12u, 7u, 7u, 1000, 6u, 0u},
        {0u, 3u, 0u, 1u, 8u, 12u, 5u, 5u, 1000, 6u, 0u},
        {0u, 2u, 0u, 1u, 8u, 12u, 5u, 5u, 1000, 6u, 0u},
        {16u, 3u, 0u, 1u, 8u, 8u, 8u, 8u, 14, 6u, 3u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {16u, 3u, 4u, 1u, 8u, 8u, 7u, 7u, 40, 5u, 3u},
        {16u, 4u, 7u, 1u, 16u, 12u, 7u, 7u, 1000, 6u, 5u},
        {16u, 4u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 2u},
        {0u, 0u, 0u, 0u, 8u, 8u, 0u, 0u, 1, 7u, 0u},
        {34u, 8u, 0u, 1u, 8u, 8u, 3u, 3u, 8, 7u, 4u},
        {34u, 8u, 0u, 1u, 4u, 4u, 2u, 2u, 1000, 7u, 0u},
        {34u, 8u, 0u, 1u, 4u, 4u, 2u, 2u, 1000, 7u, 4u},
        {0u, 3u, 5u, 0u, 8u, 8u, 6u, 6u, 0, 14u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 5u, 7u, 1u, 24u, 24u, 16u, 16u, 1000, 6u, 2u},
        {0u, 4u, 4u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 1u},
        {0u, 6u, 0u, 1u, 8u, 8u, 5u, 5u, 1000, 6u, 2u},
        {2u, 7u, 0u, 1u, 4u, 20u, 0u, 4u, 0, 5u, 0u},
        {0u, 6u, 0u, 1u, 12u, 16u, 8u, 8u, 1000, 6u, 7u},
        {0u, 6u, 0u, 1u, 8u, 8u, 0u, 0u, 1000, 6u, 2u},
        {34u, 7u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 7u, 0u},
        {0u, 8u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 7u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 3u, 0u, 0u, 48u, 36u, 0u, 0u, 0, 6u, 0u},
        {0u, 6u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 4u, 0u},
        {16u, 3u, 5u, 1u, 8u, 8u, 6u, 6u, 1000, 14u, 3u}};

//----- (00403440) --------------------------------------------------------
void __cdecl CreateEntity(int type, int x, int y, int type2)
{
    int i;          // [esp+8h] [ebp-Ch]
    NpcAttr *eAttr; // [esp+Ch] [ebp-8h]
    Object *ePtr;   // [esp+10h] [ebp-4h]

    eAttr = &NpcAttrTbl[type];
    for (i = (eAttr->unk << 8) / 10; i < 256 && (EntityTbl[i].cond & 1) != 0; ++i)
        ;
    if (i != 256)
    {
        ePtr = &EntityTbl[i];
        memset(ePtr, 0, sizeof(Object));
        ePtr->cond = 1;
        ePtr->flag = eAttr->flag;
        ePtr->xoff = eAttr->xoff << 10;
        ePtr->yoff = eAttr->yoff << 10;
        ePtr->w = eAttr->w << 10;
        ePtr->h = eAttr->h << 10;
        ePtr->life = eAttr->life;
        ePtr->score = eAttr->score;
        ePtr->damage = eAttr->damage;
        ePtr->surf = eAttr->surf;
        ePtr->destroyHitVoice = eAttr->destroyHitVoice;
        ePtr->type = type;
        ePtr->type2 = type2;
        if ((ePtr->flag & 0x10) != 0)
            AddStageXOScroll(&x, &y);
        ePtr->x = x;
        ePtr->y = y;
        ePtr->num = EntityCreateCount++;
    }
}

//----- (00403840) --------------------------------------------------------
int CountNpCharType(int type)
{
    int i;  // [esp+0h] [ebp-8h]
    int v3; // [esp+4h] [ebp-4h]

    v3 = 0;
    for (i = 0; i < 256; ++i)
    {
        if ((EntityTbl[i].cond & 1) != 0 && EntityTbl[i].type == type)
            ++v3;
    }
    return v3;
}

//----- (004038A0) --------------------------------------------------------
void ClearReplaceNpChar(int a1, int a2)
{
    int i;  // [esp+0h] [ebp-Ch]
    int v3; // [esp+4h] [ebp-8h] BYREF
    int v4; // [esp+8h] [ebp-4h] BYREF

    for (i = 0; i < 256; ++i)
    {
        if ((EntityTbl[i].cond & 1) != 0 && EntityTbl[i].type == a1)
        {
            EntityTbl[i].cond = 0;
            if (a2)
            {
                v3 = EntityTbl[i].x;
                v4 = EntityTbl[i].y;
                if ((EntityTbl[i].flag & 0x10) != 0)
                    SubStageXOScroll(&v3, &v4);
                CreateEntity(1, v3, v4, 0);
            }
        }
    }
}

//----- (00418510) --------------------------------------------------------
void HitMapGeneric(Object *o, void (*func)(Object *, int, int, int), int a3)
{
    int v3[8];  // [esp+8h] [ebp-58h]
    int i;      // [esp+28h] [ebp-38h]
    int v5;     // [esp+2Ch] [ebp-34h]
    int v6;     // [esp+30h] [ebp-30h]
    int ow;     // [esp+34h] [ebp-2Ch]
    int v8;     // [esp+38h] [ebp-28h]
    int x;      // [esp+3Ch] [ebp-24h]
    int ox;     // [esp+40h] [ebp-20h] BYREF
    int attr_;  // [esp+44h] [ebp-1Ch]
    int oy;     // [esp+48h] [ebp-18h] BYREF
    int v13;    // [esp+4Ch] [ebp-14h]
    int y;      // [esp+50h] [ebp-10h]
    int flag;   // [esp+54h] [ebp-Ch]
    int oh;     // [esp+58h] [ebp-8h]
    int direct; // [esp+5Ch] [ebp-4h]

    direct = 0;
    flag = 0;
    ox = o->x;
    oy = o->y;
    ow = o->w;
    oh = o->h;
    if ((o->flag & 0x10) == 0)
        AddStageXOScroll(&ox, &oy);
    x = (ox + 0x2000) / 0x4000;
    y = (oy + 0x2000) / 0x4000;
    if ((GetTile(x - 1, y - 1) & 1) != 0)
        direct |= 1u;
    if ((GetTile(x, y - 1) & 1) != 0)
        direct |= 2u;
    if ((GetTile(x - 1, y) & 1) != 0)
        direct |= 4u;
    if ((GetTile(x, y) & 1) != 0)
        direct |= 8u;
    if (a3)
        direct = 128;
    switch (direct)
    {
    case 0:
        break;
    case 3:
        if (oy - oh < y << 14)
        {
            oy = oh + (y << 14);
            flag |= 0x40u;
        }
        break;
    case 5:
        if (ox - ow < x << 14)
        {
            ox = ow + (x << 14);
            flag |= 0x10u;
        }
        break;
    case 10:
        if (ow + ox > x << 14)
        {
            ox = (x << 14) - ow;
            flag |= 0x20u;
        }
        break;
    case 12:
        if (oh + oy > y << 14)
        {
            oy = (y << 14) - oh;
            flag |= 0x80u;
        }
        break;
    default:
        v3[0] = -1;
        v3[1] = -1;
        v3[2] = 1;
        v3[3] = 0;
        v3[4] = -1;
        v3[5] = 1;
        v3[6] = 1;
        v3[7] = 0;
        for (i = 0; i < 4; ++i)
        {
            x += v3[2 * i];
            y += v3[2 * i + 1];
            attr_ = GetTile(x, y);
            if ((attr_ & 1) != 0 && ow + ox > x << 14 && ox - ow <= (x << 14) + 0x4000 && oh + oy > y << 14 && oy - oh <= (y << 14) + 0x4000)
            {
                v13 = (x << 14) + 0x2000;
                v8 = (y << 14) + 0x2000;
                v5 = ox - v13;
                if (ox - v13 < 0)
                    v5 = -v5;
                v6 = oy - v8;
                if (oy - v8 < 0)
                    v6 = -v6;
                if (16 * v5 / (ow + 0x2000) <= 16 * v6 / (oh + 0x2000))
                {
                    if (oy >= v8)
                    {
                        oy = v8 + oh + 0x2000;
                        flag |= 0x40u;
                    }
                    else
                    {
                        oy = v8 - (oh + 0x2000);
                        flag |= 0x80u;
                    }
                }
                else if (ox >= v13)
                {
                    ox = v13 + ow + 0x2000;
                    flag |= 0x10u;
                }
                else
                {
                    ox = v13 - (ow + 0x2000);
                    flag |= 0x20u;
                }
                if ((attr_ & 2) != 0 && a3)
                {
                    ShiftTile(x, y);
                    CreateEntity(10, (16 * x + 8) << 10, (16 * y + 8) << 10, 0);
                    PlaySound(15);
                    goto end;
                }
            }
        }
        break;
    }
end:
    if (flag)
    {
        if ((o->flag & 0x10) == 0)
            SubStageXOScroll(&ox, &oy);
        func(o, ox, oy, flag);
    }
}