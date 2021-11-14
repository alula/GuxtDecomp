#include <windows.h>

#include "NpcAct020.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "Ship.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00406450) --------------------------------------------------------
void ActNpc020_Asteroid_L(Object *o)
{
    static RECT rcAsteroidL[2] = {
        {0, 160, 32, 192},
        {32, 160, 64, 192}};

    int v1; // [esp+0h] [ebp-4h]

    if (o->life < 82)
    {
        CreateEntity(23, o->x - 0x1000, o->y - 0x1000, 0);
        CreateEntity(23, o->x + 0x1000, o->y - 0x1000, 1);
        CreateEntity(23, o->x - 0x1000, o->y + 0x1000, 2);
        CreateEntity(23, o->x + 0x1000, o->y + 0x1000, 3);
        PlaySound(12);
        CreateEntity(1, o->x, o->y, 0);
        o->cond = 0;
        ++asteroidsKilled;
        bonusAzaX = o->x;
        bonusAzaY = o->y - 0x2000;
        return;
    }
    v1 = o->state;
    if (!v1)
    {
        o->state = 1;
        o->y -= 0x2000;
        o->ym = 0x400;
    LABEL_7:
        o->y += o->ym;
        if (o->y > 0x2C000)
            o->cond = 0;
        goto LABEL_9;
    }
    if (v1 == 1)
        goto LABEL_7;
LABEL_9:
    if (o->shock / 2 % 2)
        o->rect = rcAsteroidL[1];
    else
        o->rect = rcAsteroidL[0];
}

//----- (00406630) --------------------------------------------------------
void ActNpc021_Asteroid_S(Object *o)
{
    static RECT rcAsteroidS[2] = {
        {64, 160, 80, 176},
        {64, 176, 80, 192}};

    int v1; // [esp+0h] [ebp-4h]

    v1 = o->state;
    if (v1)
    {
        if (v1 != 1)
            goto LABEL_7;
    }
    else
    {
        o->state = 1;
        o->ym = 0x400;
    }
    o->y += o->ym;
    if (o->y > 0x2C000)
        o->cond = 0;

LABEL_7:
    if (o->shock / 2 % 2)
        o->rect = rcAsteroidS[1];
    else
        o->rect = rcAsteroidS[0];
}

//----- (00406700) --------------------------------------------------------
void ActNpc022_ScrollSpdSet(Object *o)
{
    SetScrollSpeed(-1024 * o->type2 / 100);
    o->cond = 0;
}

//----- (00406730) --------------------------------------------------------
void ActNpc023_Asteroid_SGravity(Object *o)
{
    static RECT rcAsteroidSGravity[3] = {
        {64, 160, 80, 176},
        {64, 176, 80, 192},
        {0, 0, 0, 0}};

    int v1; // [esp+4h] [ebp-4h]

    v1 = o->state;
    if (v1)
    {
        if (v1 != 1)
            goto LABEL_11;
    }
    else
    {
        o->state = 1;
        switch (o->type2)
        {
        case 0:
            o->ym = -614;
            o->xm = -113;
            break;
        case 1:
            o->ym = -921;
            o->xm = 102;
            break;
        case 2:
            o->ym = -512;
            o->xm = -341;
            break;
        case 3:
            o->ym = -819;
            o->xm = 256;
            break;
        default:
            break;
        }
    }
    o->ym += 32;
    o->x += o->xm;
    o->y += o->ym;
    if (o->y > 0x2C000)
        o->cond = 0;

LABEL_11:
    if (o->shock / 2 % 2)
    {
        o->rect = rcAsteroidSGravity[1];
    }
    else
    {
        o->rect = rcAsteroidSGravity[o->count2];
    }
}

//----- (004068A0) --------------------------------------------------------
void ActNpc024_Hanger_Wave(Object *o)
{
    int v1;              // edx
    int v2;              // [esp+0h] [ebp-38h]
    RECT rc[3];          // [esp+4h] [ebp-34h]
    unsigned char angle; // [esp+37h] [ebp-1h]

    rc[0].left = 72;
    rc[0].top = 0;
    rc[0].right = 96;
    rc[0].bottom = 24;
    rc[1].left = 96;
    rc[1].top = 0;
    rc[1].right = 120;
    rc[1].bottom = 24;
    rc[2].left = 120;
    rc[2].top = 0;
    rc[2].right = 144;
    rc[2].bottom = 24;
    v2 = o->state;
    if (v2)
    {
        if (v2 != 10)
            goto LABEL_20;
    }
    else
    {
        o->state = 10;
        o->y = -4096;
        o->ym = 1024;
        o->child = o->x;
        if (o->x >= 61440)
            o->xm = -2048;
        else
            o->xm = 2048;
    }
    if (++o->count1 == 20)
        o->flag |= 3u;
    if (++o->count3 > 2)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 2)
        o->count2 = 0;
    if (o->child >= o->x)
        v1 = o->xm + 85;
    else
        v1 = o->xm - 85;
    o->xm = v1;
    if (o->xm < -2048)
        o->xm = -2048;
    if (o->xm > 2048)
        o->xm = 2048;
LABEL_20:
    if (o->type2)
    {
        if (++o->rot1 == 12)
        {
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
        }
        if (o->rot1 == 31)
        {
            angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            CreateEntity(13, o->x, o->y, angle);
            PlaySound(7);
        }
    }
    if (o->y > 0x2B000)
        o->cond = 0;
    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];
    if (o->life < 4)
    {
        o->rect.left += 72;
        o->rect.right += 72;
    }
    if (o->shock / 2 % 2)
    {
        o->rect.top += 24;
        o->rect.bottom += 24;
    }
}

//----- (00406B90) --------------------------------------------------------
void ActNpc025_Hanger_Shoot(Object *o)
{
    int v1;              // edx
    RECT rc[6];          // [esp+4h] [ebp-68h]
    unsigned char angle; // [esp+6Bh] [ebp-1h]

    rc[0].left = 0;
    rc[0].top = 0;
    rc[0].right = 24;
    rc[0].bottom = 24;
    rc[1].left = 24;
    rc[1].top = 0;
    rc[1].right = 48;
    rc[1].bottom = 24;
    rc[2].left = 48;
    rc[2].top = 0;
    rc[2].right = 72;
    rc[2].bottom = 24;
    rc[3].left = 72;
    rc[3].top = 0;
    rc[3].right = 96;
    rc[3].bottom = 24;
    rc[4].left = 96;
    rc[4].top = 0;
    rc[4].right = 120;
    rc[4].bottom = 24;
    rc[5].left = 120;
    rc[5].top = 0;
    rc[5].right = 144;
    rc[5].bottom = 24;
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = 0x28000;
        o->ym = -0x1800u;
        if (o->type2)
        {
            o->life = 1;
            o->score = 0;
        }
        PlaySound(26);
        goto LABEL_5;
    case 0xA:
    LABEL_5:
        o->ym += 113;
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 2)
            o->count2 = 0;
        if (o->ym > 0)
            goto LABEL_10;
        break;
    case 0x14:
    LABEL_10:
        o->state = 30;
        o->count1 = 0;
        o->flag |= 3u;
        o->damage = 1;
        SetCaret(1, o->x, o->y, (intptr_t)o);
        PlaySound(30);
        goto LABEL_11;
    case 0x1E:
    LABEL_11:
        if (ship.x >= o->x)
            v1 = o->xm + 64;
        else
            v1 = o->xm - 64;
        o->xm = v1;
        if (o->xm < -1024)
            o->xm = -1024;
        if (o->xm > 1024)
            o->xm = 1024;
        o->ym += 42;
        if (o->ym > 1536)
            o->ym = 1536;
        if (++o->count1 == 5)
        {
            angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            CreateEntity(13, o->x, o->y, angle);
            PlaySound(7);
        }
        if (++o->count3 > 1)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 5)
            o->count2 = 3;
        if (o->y > 0x2C000)
            o->cond = 0;
        break;
    default:
        break;
    }

    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];

    if (o->life < 4)
    {
        if (o->state >= 20)
        {
            o->rect.left += 72;
            o->rect.right += 72;
        }
        else
        {
            o->rect.top += 24;
            o->rect.bottom += 24;
        }
    }
    if (o->shock / 2 % 2)
    {
        o->rect.top += 24;
        o->rect.bottom += 24;
        o->ym = -1024;
    }
}

//----- (00406FB0) --------------------------------------------------------
void ActNpc026_RockHugger(Object *o)
{
    int v1;        // ecx
    int v2;        // [esp+0h] [ebp-50h]
    RECT v3[4];    // [esp+8h] [ebp-48h]
    Object *child; // [esp+4Ch] [ebp-4h]

    v3[0].left = 80;
    v3[0].top = 0;
    v3[0].right = 104;
    v3[0].bottom = 24;
    v3[1].left = 104;
    v3[1].top = 0;
    v3[1].right = 128;
    v3[1].bottom = 24;
    v3[2].left = 128;
    v3[2].top = 0;
    v3[2].right = 152;
    v3[2].bottom = 24;
    v3[3].left = 0;
    v3[3].top = 0;
    v3[3].right = 0;
    v3[3].bottom = 0;
    child = (Object *)o->child;
    if (o->life > 96)
    {
        switch (o->state)
        {
        case 0:
            o->state = 10;
            o->ym = -1024;
            o->y = 200704;
            PlaySound(26);
            v2 = o->type2;
            if (v2)
            {
                if (v2 != 1)
                {
                    if (v2 == 2)
                        o->state = 30;
                    goto LABEL_40;
                }
                o->child = (intptr_t)CreateEntity(28, o->x, o->y - 10240, 0);
                if (o->child)
                {
                    o->y -= 0x4000;
                    goto LABEL_40;
                }
                o->cond = 0;
            }
            else
            {
                o->child = (intptr_t)CreateEntity(27, o->x, o->y - 0x4000, 0);
                if (o->child)
                    goto LABEL_40;
                o->cond = 0;
            }
            return;
        case 0xA:
            o->ym += 32;
            o->y += o->ym;
            if (o->ym > 512)
                o->state = 20;
            goto LABEL_40;
        case 0x14:
            o->ym -= 42;
            if (o->type2)
            {
                if (o->ym < -1024)
                    o->ym = -1024;
            }
            else if (o->ym < -512)
            {
                o->ym = -512;
            }
            o->y += o->ym;
            o->x += o->xm;
            goto LABEL_40;
        case 0x1E:
            o->ym -= 42;
            if (ship.x >= o->x)
                v1 = o->xm + 64;
            else
                v1 = o->xm - 64;
            o->xm = v1;
            if (o->xm < -1024)
                o->xm = -1024;
            if (o->xm > 1024)
                o->xm = 1024;
            o->y += o->ym;
            o->x += o->xm;
            if (o->ym < -512)
            {
                o->state = 40;
                o->count2 = 2;
                o->y += 3072;
                o->xm = 0;
            }
            goto LABEL_40;
        case 0x28:
            o->ym -= 42;
            o->y += o->ym;
            o->x += o->xm;
            goto LABEL_40;
        default:
        LABEL_40:
            if ((o->state == 10 || o->state == 20) && child)
            {
                if (child->state < 100)
                {
                    if (o->y >= 0x4000)
                    {
                        if (o->type2)
                            child->y = o->y - 10240;
                        else
                            child->y = o->y - 0x4000;
                    }
                    else
                    {
                        child->state = 1;
                        o->state = 30;
                        o->count2 = 1;
                        o->score = 1;
                        o->ym = 1024;
                    }
                }
                else
                {
                    o->state = 30;
                    o->count2 = 1;
                    o->score = 1;
                    o->ym = 1024;
                }
            }
            if (!(++o->count1 % 6))
                CreateEntity(29, o->x, o->y + 0x2000, 0);
            if (o->state >= 30 && o->count1 % 6 == 3)
                CreateEntity(29, o->x, o->y + 4096, 0);
            if (o->y < -12288)
                o->cond = 0;
            o->rect = v3[o->count2];
            if (o->shock / 2 % 2)
            {
                o->rect.top += 24;
                o->rect.bottom += 24;
            }
            break;
        }
    }
    else
    {
        AddScore(o->score);
        SetCaret(0, o->x, o->y - 0x4000, o->score);
        CreateEntity(1, o->x, o->y - 4096, 0);
        PlaySound(11);
        if (o->state == 20 || o->state == 10)
        {
            if (child)
            {
                child->state = 1;
                child->ym = 0;
            }
        }
        o->cond = 0;
    }
}

//----- (00407580) --------------------------------------------------------
void ActNpc027_RHAsteroidL(Object *o)
{
    static RECT rcRHAsteroidL[4] = {
        {0, 160, 32, 192},
        {32, 160, 64, 192},
        {0, 0, 0, 0},
        {64, 160, 80, 176}};

    int v1; // eax
    int v2; // [esp+0h] [ebp-4h]

    if (o->state >= 100 || o->life >= 82)
    {
        v2 = o->state;
        if (v2 == 1)
        {
            o->ym += 0x20;
            o->y += o->ym;
            if (o->y > 0x30000)
                o->cond = 0;
        }
        else if (v2 == 100)
        {
            v1 = o->count1;
            o->count1 = v1 + 1;
            if (v1 > 10)
                o->cond = 0;
        }
        if (o->shock / 2 % 2)
            o->rect = rcRHAsteroidL[1];
        else
            o->rect = rcRHAsteroidL[o->count2];
    }
    else
    {
        CreateEntity(23, o->x - 0x1800, o->y - 0x1800, 0);
        CreateEntity(23, o->x + 0x1800, o->y - 0x1800, 1);
        CreateEntity(23, o->x - 0x1800, o->y + 0x1800, 2);
        CreateEntity(23, o->x + 0x1800, o->y + 0x1800, 3);
        PlaySound(12);
        CreateEntity(1, o->x, o->y, 0);
        o->state = 100;
        o->count2 = 2;
        o->shock = 0;
        o->flag &= ~3u;
        ++asteroidsKilled;
        bonusAzaX = o->x;
        bonusAzaY = o->y - 0x2000;
    }
}