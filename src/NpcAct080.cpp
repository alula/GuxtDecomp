#include <windows.h>

#include "NpcAct080.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00410ED0) --------------------------------------------------------
void ActNpc080(Object *o)
{
    static RECT rc = {144, 40, 152, 48};

    int v1;           // [esp+0h] [ebp-Ch]
    Object *parent;   // [esp+4h] [ebp-8h]
    unsigned char v3; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_7;
    }
    else
    {
        o->state = 10;
        o->child = parent->child++;
        if (parent->child == 20)
            parent->child = 0;
    }
    v3 = (unsigned char)((o->child % 4) * 0x40 + parent->rot1);
    o->x = parent->x + parent->count3 * GetCos(v3) * (o->child / 4 + 5) / 4 / 11;
    o->y = parent->y + parent->count3 * GetSin(v3) * (o->child / 4 + 5) / 4 / 11;

LABEL_7:
    o->rect = rc;
}

//----- (00411020) --------------------------------------------------------
void ActNpc081_SpaceAmeba(Object *o)
{
    static RECT rc[4] = {
        {0, 104, 16, 120},
        {16, 104, 32, 120},
        {32, 104, 48, 120},
        {48, 104, 64, 120},
    };
    int v1;              // [esp+0h] [ebp-10h]
    int o_x;             // [esp+4h] [ebp-Ch] BYREF
    int o_y;             // [esp+8h] [ebp-8h] BYREF
    unsigned char angle; // [esp+Fh] [ebp-1h]

    o_x = o->x;
    o_y = o->y;
    SubStageXOScroll(&o_x, &o_y);

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 20 && ++o->count1 > 24)
            {
                o->state = 10;
                o->count1 = 0;
                o->count3 = 0;
                o->shock = 0;
                angle = GetArktan(o_x - ship.x, o_y - ship.y, 0x40);
                o->xm = GetCos(angle);
                o->ym = GetSin(angle);
                if (o->child > 6)
                    o->ym = 1024;
            }
            goto LABEL_16;
        }
    }
    else
    {
        o->state = 10;
        o->count1 = -10;
        o->flag |= 0x40u;
        angle = GetArktan(o_x - ship.x, o_y - ship.y, 0x40);
        o->xm = 2 * (GetCos(angle) / 3);
        o->ym = 2 * (GetSin(angle) / 3);
    }

    o->cond &= ~0xF0u;

    if (++o->count1 > 24)
    {
        o->count1 = 0;
        o->state = 20;
        o->xm = 0;
        o->ym = 0;
        ++o->child;
        o->flag |= 3u;
        PlaySound(42);
    }

    if (++o->count3 > 3)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 2)
        o->count2 = 0;

LABEL_16:
    o->x += o->xm;
    o->y += o->ym;

    if (o->shock / 2 % 2)
    {
        o->rect = rc[3];
    }
    else
    {
        o->rect = rc[o->count2];
    }

    if ((o->flag & 1) == 0)
    {
        o->rect.top += 16;
        o->rect.bottom += 16;
    }
    if (o_y > 0x2A000)
        o->cond = 0;
}

//----- (00411320) --------------------------------------------------------
void ActNpc082(Object *o)
{
    intptr_t v3;      // [esp-4h] [ebp-10h]
    Object *parent;   // [esp+4h] [ebp-8h]
    unsigned char v5; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;

    o->x = parent->x;
    o->y = parent->y - 2048;

    switch (parent->state)
    {
    case 30:
        if (++o->count1 >= 48 && (o->count1 % 16) == 0)
        {
            CreateEntity(63, o->x, o->y, GetArktan(o->x - ship.x, o->y - ship.y, 64));
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(36);
        }
        if (o->count1 > 112)
            o->count1 = 16;
        break;
    case 110:
    case 111:
    case 112:
    case 113:
    case 120:
    case 121:
    case 122:
    case 123:
        if (parent->life < 680)
        {
            if (++o->count1 >= 48 && !(o->count1 % 16))
            {
                v3 = GetArktan(o->x - ship.x, o->y - ship.y, 64);
                CreateEntity(63, o->x, o->y, v3);
                SetCaret(1, o->x, o->y, (intptr_t)o);
                PlaySound(36);
            }
            if (o->count1 > 112)
                o->count1 = 16;
        }
        else
        {
            if (++o->count1 >= 70)
            {
                v5 = GetArktan(o->x - ship.x, o->y - 1024 - ship.y, 64);
                CreateEntity(13, o->x, o->y - 1024, v5);
                CreateEntity(13, o->x, o->y - 1024, v5 - 10);
                CreateEntity(13, o->x, o->y - 1024, v5 + 10);
                SetCaret(1, o->x, o->y, (intptr_t)o);
                PlaySound(36);
                o->count1 = 0;
            }
            if (o->count1 == 50)
            {
                SetCaret(4, o->x, o->y - 1024, (intptr_t)o);
                PlaySound(31);
            }
        }
        break;
    case 200:
        if (parent->count1 == 20)
        {
            SetCaret(4, o->x, o->y - 1024, (intptr_t)o);
            PlaySound(31);
        }
        if (parent->count1 > 50 && parent->count1 < 150 && !(parent->count1 % 6))
        {
            CreateEntity(63, o->x, o->y, 192);
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(36);
        }
        break;
    case 210:
        if (++o->count1 > 32)
        {
            o->count1 = GetRandom(32);
            CreateEntity(83, GetRandom(120) * 0x400, -8192, 0);
        }
        break;
    default:
        return;
    }
}

//----- (004117C0) --------------------------------------------------------
void ActNpc083_B4Bullet(Object *o)
{
    static RECT rc[2] = {
        {112, 160, 128, 176},
        {112, 176, 128, 192},
    };

    int v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_8;
    }
    else
    {
        o->state = 10;
        o->ym = 1024;
    }
    if (++o->count1 == 32)
        o->flag |= 3u;

    o->x += o->xm;
    o->y += o->ym;

LABEL_8:
    ++o->count3;
    if (o->x < -0x10000 || o->x > 0x2E000 || o->y < -0x10000 || o->y > 0x38000)
        o->cond = 0;
    o->rect = rc[o->count3 / 3 % 2];
}

//----- (004118D0) --------------------------------------------------------
void ActNpc084_Square(Object *o)
{
    static RECT rc[16] = {
        {0, 0, 16, 16},
        {16, 0, 32, 16},
        {32, 0, 48, 16},
        {48, 0, 64, 16},
        {0, 16, 16, 32},
        {16, 16, 32, 32},
        {32, 16, 48, 32},
        {48, 16, 64, 32},
        {0, 32, 16, 48},
        {16, 32, 32, 48},
        {32, 32, 48, 48},
        {48, 32, 64, 48},
        {0, 48, 16, 64},
        {16, 48, 32, 64},
        {32, 48, 48, 64},
        {48, 48, 64, 64},
    };

    unsigned char v4; // [esp+7h] [ebp-1h]

    switch (o->state)
    {
    case 0:
        PlaySound(26);
        o->state = 10;
        o->child = o->x;
        o->rot1 = o->type2 << 14;
        o->x = 2 * o->x - 0xF000;
        o->y = -0x2000;
        goto LABEL_3;
    case 10:
    LABEL_3:
        o->x += (o->child - o->x) / 8;
        o->y += (o->rot1 - o->y) / 8;
        if (++o->count1 > 10)
            o->flag |= 3u;
        if (o->count1 <= 100)
        {
            if (o->life < 998)
            {
                o->state = 20;
                o->life = 2;
                v4 = GetArktan(o->x - ship.x, o->y - ship.y, 64);
                o->xm = -3 * GetCos(v4);
                o->ym = -3 * GetSin(v4);
                o->child = v4;
            }

            if (o->count3++ > 0)
            {
                o->count3 = 0;
                ++o->count2;
            }
            if (o->count2 > 3)
                o->count2 = 0;
        }
        else
        {
            o->state = 30;
            o->life = 4;
        }
        break;
    case 20:
        o->xm += GetCos(o->child) / 8;
        o->ym += GetSin(o->child) / 8;
        o->x += o->xm;
        o->y += o->ym;

        if (o->count3++ > 0)
        {
            o->count3 = 0;
            ++o->count2;
        }

        if (o->count2 > 11)
            o->count2 = 8;

        if (o->x < -0x10000 || o->x > 0x2E000 || o->y < -0x10000 || o->y > 0x38000)
            o->cond = 0;
        break;
    case 30:
        o->ym += 0x80;
        o->y += o->ym;
        if (o->y < -0x10000 || o->y > 0x38000)
            o->cond = 0;

        if (o->count3++ > 0)
        {
            o->count3 = 0;
            ++o->count2;
        }

        if (o->count2 > 3)
            o->count2 = 0;

        break;
    default:
        break;
    }

    o->rect = rc[o->count2];
    if (o->shock / 2 % 2)
        o->rect = rc[o->count2 % 4 + 12];
    else
        o->rect = rc[o->count2];
}

//----- (00411D00) --------------------------------------------------------
void ActNpc085_CloudDarkL(Object *o)
{
    RECT rc = {64, 0, 112, 24};

    o->y += 0xC00;
    if (o->y > 0x2C000)
        o->cond = 0;

    o->rect = rc;
}

//----- (00411D70) --------------------------------------------------------
void ActNpc086_CloudDarkS(Object *o)
{
    RECT rc = {64, 24, 88, 40};

    o->y += 0x800;
    if (o->y > 0x2C000)
        o->cond = 0;

    o->rect = rc;
}

//----- (00411DE0) --------------------------------------------------------
void ActNpc087_CloudDarkGen(Object *o)
{
    if (++o->count1 > 12)
    {
        o->count1 = 0;
        if (++o->state > 9)
            o->state = 0;
    }
    if (o->count1 != 0)
        return;

    int x = GetRandom(120) << 10;

    switch (o->state)
    {
    case 0:
    case 1:
    case 3:
    case 7:
        CreateEntity(85, x, -0x4000, 0);
        break;
    case 2:
    case 4:
        CreateEntity(86, x, -0x4000, 0);
        break;
    default:
        return;
    }
}

//----- (00411F20) --------------------------------------------------------
void ActNpc088_MissilePot(Object *o)
{
    static RECT rcMissilePot[2] = {
        {112, 0, 144, 32},
        {112, 32, 144, 64},
    };

    int v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_17;
    }
    else
    {
        CreateEntity(89, -1, 0, (intptr_t)o);
        CreateEntity(89, 1, 0, (intptr_t)o);
        o->state = 10;
        if (o->x >= 0x14000)
        {
            o->x = 0x22000;
            o->xm = -0x100;
        }
        else
        {
            o->x = -0x4000;
            o->xm = 0x100;
        }
        o->ym = 0x100;
        if (o->type2)
            o->y = 0x6000;
        else
            o->y = -0x4000;
    }
    if (++o->count1 == 143)
    {
        SetCaret(1, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }
    if (o->count1 > 162 && !(o->count1 % 6))
    {
        CreateEntity(90, o->x, o->y - 0x2000, ++o->child % 6);
        PlaySound(20);
    }
    if (o->count1 > 206)
        o->count1 = 0;
LABEL_17:
    if (!(o->count1 % 6))
        CreateEntity(29, o->x, o->y + 0x2000, 0);
    o->x += o->xm;
    o->y += o->ym;

    if (o->shock / 2 % 2)
        o->rect = rcMissilePot[1];
    else
        o->rect = rcMissilePot[0];

    if (++o->count3 > 100 && (o->x < -0x4000 || o->x > 0x22000))
        o->cond = 0;
}

//----- (00412190) --------------------------------------------------------
void ActNpc089(Object *o)
{
    int v1; // [esp+0h] [ebp-4h]
    Object *parent;

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        o->child = o->x;
        o->state = 10;
    }

    parent = (Object *)o->type2;
    if (o->child >= 0)
        o->x = parent->x + 10240;
    else
        o->x = parent->x - 10240;

    o->y = parent->y;

LABEL_9:
    if ((parent->cond & 1) == 0 || parent->type != 88)
        o->cond = 0;
}

//----- (00412230) --------------------------------------------------------
void ActNpc090_Missile(Object *o)
{
    static RECT rc[2] = {
        {64, 40, 72, 64},
        {72, 40, 80, 64},
    };

    int v2; // [esp+4h] [ebp-4h]

    v2 = o->state;
    if (v2)
    {
        if (v2 != 10)
            goto LABEL_21;
    }
    else
    {
        switch (o->type2)
        {
        case 0:
            o->xm = -0x100;
            o->ym = -0x600;
            break;
        case 1:
            o->xm = 0x100;
            o->ym = -0x600;
            break;
        case 2:
            o->xm = -0x155;
            o->ym = -0x400;
            break;
        case 3:
            o->xm = 0x155;
            o->ym = -0x400;
            break;
        case 4:
            o->xm = -0x200;
            o->ym = -0x200;
            break;
        case 5:
            o->xm = 0x200;
            o->ym = -0x200;
            break;
        default:
            break;
        }
        o->state = 10;
    }

    o->ym += 0x40;
    if (o->ym >= 0x400)
    {
        o->xm = 0;
    }
    else
    {
        if (ship.x >= o->x)
            o->xm += 0xA;
        else
            o->xm -= 0xA;
    }

    if (++o->count2 > 1)
        o->count2 = 0;

    o->x += o->xm;
    o->y += o->ym;
LABEL_21:
    if (o->y >= 0x2B000)
        o->cond = 0;

    o->rect = rc[o->count2];
}

//----- (00412400) --------------------------------------------------------
void ActNpc091(Object *o)
{
    static RECT rc[2] = {
        {48, 64, 64, 80},
        {64, 64, 96, 80},
    };

    o->y += 0x1000;
    if (o->y > 0x2A000)
        o->cond = 0;

    o->rect = rc[o->type2];
}

//----- (00412460) --------------------------------------------------------
void ActNpc092_BGRock(Object *o)
{
    int x; // [esp+4h] [ebp-4h]

    if (++o->child == 30)
        ship.flag |= 0x100u;

    if (++o->count1 > 10)
    {
        o->count1 = 0;
        if (++o->state > 9)
            o->state = 0;
    }
    if (!o->count1)
    {
        x = (GetRandom(136) << 10) - 0x4000;
        switch (o->state)
        {
        case 0:
        case 1:
        case 3:
        case 7:
            CreateEntity(91, x, -0x4000, 0);
            break;
        case 2:
        case 4:
            CreateEntity(91, x, -0x4000, 1);
            break;
        default:
            return;
        }
    }
}

//----- (004125D0) --------------------------------------------------------
void ActNpc093_ClearRockCloudGen(Object *o)
{
    ClearReplaceNpChar(87, 0);
    ClearReplaceNpChar(92, 0);
    o->cond = 0;
}

//----- (00412600) --------------------------------------------------------
void ActNpc094_SandStamper(Object *o)
{
    static RECT rc[4] = {
        {144, 0, 160, 24},
        {160, 0, 176, 24},
        {176, 0, 192, 24},
        {232, 0, 248, 24},
    };

    unsigned char angle; // [esp+7h] [ebp-1h]

    if (o->state < 20 && o->life <= 976)
    {
        o->state = 20;
        PlaySound(11);
        CreateEntity(1, o->x, o->y, 0);
        SetCaret(0, o->x, o->y, o->score);
        AddScore(o->score);
        o->flag &= ~1u;
        o->flag |= 8u;
    }
    switch (o->state)
    {
    case 0:
        CreateEntity(95, o->x, o->y, (intptr_t)o);
        o->state = 10;
        o->rot1 = o->y - 0x4000;
        o->flag |= 3u;
        o->count4 = 0;
        o->count3 = -0xC00;
        if (!o->type2)
            CreateEntity(96, o->x, o->y + 0xC00, (intptr_t)o);
        PlaySound(20);

    case 10:
        if (o->type2)
        {
            o->rot1 += 0x800;
        }
        else
        {
            if (o->rot1 < 0xA000)
                o->rot1 += 0x100;
            else
                o->rot1 += 0x400;
        }
        o->count3 += 128;
        o->count4 += o->count3;
        if (o->count4 > 0)
        {
            o->count4 = 0;
            o->count3 = -0xC00;
            if (!o->type2)
                CreateEntity(96, o->x, o->y + 0xC00, (intptr_t)o);
            PlaySound(20);
        }
        goto LABEL_24;
    case 20:
        o->rot1 += 512;
        o->count3 += 128;
        o->count4 += o->count3;
        if (o->count4 <= 0)
            goto LABEL_24;
        o->count4 = 0;
        PlaySound(20);
        CreateEntity(1, o->x, o->y + 0x2800, 0);
        o->state = 30;
        o->ym = 0;
    LABEL_21:
        o->ym += 0x100;
        if (o->ym > 0x1000)
            o->ym = 0x1000;
        o->rot1 += o->ym;
    LABEL_24:
        if (o->state < 20)
        {
            if (++o->count1 == 350)
            {
                SetCaret(1, o->x, o->y - 0x800, (intptr_t)o);
                PlaySound(30);
            }
            if (o->count1 == 370)
            {
                o->count1 = 0;
                angle = GetArktan(o->x - ship.x, o->y - 0x800 - ship.y, 64);
                CreateEntity(13, o->x, o->y - 0x800, angle);
                angle += 12;
                CreateEntity(13, o->x, o->y - 0x800, angle);
                CreateEntity(13, o->x, o->y - 0x800, (unsigned char)(angle - 24));
                PlaySound(7);
            }
        }
        if (o->rot1 > 0x30000)
            o->cond = 0;
        o->y = o->rot1 + o->count4 / 2;
        if (o->state < 20)
        {
            if (o->shock / 2 % 2)
                o->rect = rc[2];
            else
                o->rect = rc[++o->count2 % 2];
        }
        else
        {
            o->rect = rc[3];
        }
        return;
    case 30:
        goto LABEL_21;
    default:
        goto LABEL_24;
    }
}

//----- (00412B20) --------------------------------------------------------
void ActNpc095(Object *o)
{
    RECT rc = {208, 0, 232, 32};
    Object *parent = (Object *)o->type2;

    o->x = parent->x + -parent->count4 / 4;
    o->y = parent->y + -parent->count4 / 3 + 0xC00;
    if (parent->state == 30)
        o->y += 0x1000;

    o->rect = rc;
    if (parent->num >= o->num || (parent->cond & 1) == 0)
        o->cond = 0;
}

//----- (00412BF0) --------------------------------------------------------
void ActNpc096_Stamp(Object *a1)
{
    static RECT rc = {192, 0, 208, 24};
    a1->y += 0x1000;
    if (a1->y > 0x2B000)
        a1->cond = 0;

    a1->rect = rc;
}

//----- (00412C50) --------------------------------------------------------
void ActNpc097_Brick(Object *o)
{
    static RECT rcBrick[3] = {
        {144, 24, 160, 40},
        {160, 24, 176, 40},
        {176, 24, 192, 40},
    };

    if (!o->state)
    {
        o->state = 1;
        o->flag |= 1u;
    }

    o->rect = rcBrick[2 - o->life / 5];
}

//----- (00412CC0) --------------------------------------------------------
void ActNpc098_BulletSquare(Object *o)
{
    static RECT rcBulletSquare[4] = {
        {136, 56, 152, 72},
        {152, 56, 168, 72},
        {136, 72, 152, 88},
        {152, 72, 168, 88},
    };

    int v1; // [esp+0h] [ebp-4h]

    v1 = o->state;
    if (!v1)
    {
        o->xm = GetCos(o->type2) / 2;
        o->ym = GetSin(o->type2) / 2;
        o->state = 10;
        goto LABEL_5;
    }
    if (v1 == 10)
    {
    LABEL_5:
        o->x += o->xm;
        o->y += o->ym;
    }
    if (++o->count3 > 0)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 3)
        o->count2 = 0;

    if (o->x < -0x10000 || o->x > 0x2E000 || o->y < -0x10000 || o->y > 0x38000)
        o->cond = 0;

    o->rect = rcBulletSquare[o->count2];
}

//----- (00412DF0) --------------------------------------------------------
void ActNpc099_BulletSquareGen(Object *o)
{
    static RECT rc[5] = {
        {144, 112, 160, 128},
        {160, 112, 176, 128},
        {176, 112, 192, 128},
        {144, 128, 160, 144},
        {160, 128, 176, 144},
    };

    int s_x; // [esp+4h] [ebp-18h] BYREF
    int s_y; // [esp+8h] [ebp-14h] BYREF
    RECT a1; // [esp+Ch] [ebp-10h] BYREF

    s_x = o->x;
    s_y = o->y;
    SubStageXOScroll(&s_x, &s_y);

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->count1 = 25 * o->type2;
    case 10:
        if (!--o->count1)
        {
            o->state = 20;
            PlaySound(38);
        }
        break;
    case 20:
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 == 2)
        {
            o->state = 30;
            o->count1 = 0;
            SetCaret(4, o->x, o->y, (intptr_t)o);
        }
        break;
    case 30:
        if (++o->count1 > 14 && !(o->count1 % 41))
        {
            CreateEntity(98, s_x, s_y, GetArktan(s_x - ship.x, s_y - ship.y, 64));
            PlaySound(7);
        }
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 4)
            o->count2 = 2;
        break;
    default:
        break;
    }

    o->rect = rc[o->count2];

    GetStageRect(&a1);
    if (o->y > a1.bottom + 0x10000)
        o->cond = 0;
}