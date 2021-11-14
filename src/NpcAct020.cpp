#include <windows.h>

#include "NpcAct020.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00406450) --------------------------------------------------------
void ActNpc020_Asteroid_L(Object *o)
{
    static RECT rcAsteroidL[2] = {
        {0, 160, 32, 192},
        {32, 160, 64, 192},
    };

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
        {64, 176, 80, 192},
    };

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
        {0, 0, 0, 0},
    };

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
    int v2; // [esp+0h] [ebp-38h]
    RECT rc[3] = {
        {72, 0, 96, 24},
        {96, 0, 120, 24},
        {120, 0, 144, 24},
    };
    unsigned char angle; // [esp+37h] [ebp-1h]

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
        o->xm += 85;
    else
        o->xm -= 85;

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
    RECT rc[6] = {
        {0, 0, 24, 24},
        {24, 0, 48, 24},
        {48, 0, 72, 24},
        {72, 0, 96, 24},
        {96, 0, 120, 24},
        {120, 0, 144, 24},
    };
    unsigned char angle; // [esp+6Bh] [ebp-1h]

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = 0x28000;
        o->ym = -0x1800;
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
            o->xm += 64;
        else
            o->xm -= 64;

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
    int v2; // [esp+0h] [ebp-50h]
    RECT v3[4] = {
        {80, 0, 104, 24},
        {104, 0, 128, 24},
        {128, 0, 152, 24},
        {0, 0, 0, 0},
    };
    Object *child = (Object *)o->child;

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
        case 10:
            o->ym += 32;
            o->y += o->ym;
            if (o->ym > 512)
                o->state = 20;
            goto LABEL_40;
        case 20:
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
        case 30:
            o->ym -= 42;

            if (ship.x >= o->x)
                o->xm += 64;
            else
                o->xm -= 64;

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
        case 40:
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
    static RECT rcRHAsteroidL[3] = {
        {0, 160, 32, 192},
        {32, 160, 64, 192},
        {0, 0, 0, 0},
    };

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
            if (o->count1++ > 10)
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

//----- (004077A0) --------------------------------------------------------
void ActNpc028_RHAsteroidS(Object *o)
{
    static RECT rcRHAsteroidS[3] = {
        {0, 160, 64, 192},
        {64, 160, 80, 192},
        {0, 0, 0, 0},
    };

    int v1; // eax
    int v2; // [esp+0h] [ebp-4h]

    if (o->state >= 100 || o->life >= 94)
    {
        v2 = o->state;
        if (v2 == 1)
        {
            o->ym += 32;
            o->y += o->ym;
            if (o->y > 0x30000)
                o->cond = 0;
        }
        else if (v2 == 100)
        {
            if (o->count1++ > 10)
                o->cond = 0;
        }
        if (o->shock / 2 % 2)
            o->rect = rcRHAsteroidS[1];
        else
            o->rect = rcRHAsteroidS[o->count2];
    }
    else
    {
        PlaySound(14);
        CreateEntity(1, o->x, o->y, 0);
        o->state = 100;
        o->count2 = 2;
        o->shock = 0;
        o->flag &= ~3u;
    }
}

//----- (00407900) --------------------------------------------------------
void ActNpc029_Bullet2_(Object *a1)
{
    RECT rc[4] = {
        {176, 48, 184, 56},
        {184, 48, 192, 56},
        {192, 48, 200, 56},
        {200, 48, 208, 56},
    };

    if (a1->type2)
        a1->y -= 0x800;
    else
        a1->y += 0x800;

    if (a1->y > 0x2A000)
        a1->cond = 0;

    if (++a1->count3 > 1)
    {
        a1->count3 = 0;
        ++a1->count2;
    }

    if (a1->count2 <= 3)
        a1->rect = rc[a1->count2];
    else
        a1->cond = 0;
}

//----- (00407A30) --------------------------------------------------------
void ActNpc030_Elka(Object *o)
{
    int v1; // [esp+0h] [ebp-70h]
    RECT rc[6] = {
        {152, 0, 184, 32},
        {184, 0, 216, 32},
        {216, 0, 248, 32},
        {152, 32, 184, 64},
        {184, 32, 216, 64},
        {216, 32, 248, 64},
    };
    unsigned char v3; // [esp+6Fh] [ebp-1h]

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = -16384;
        o->ym = 1024;
        o->child = o->life - 18;
        goto LABEL_3;
    case 10:
    LABEL_3:
        o->y += o->ym;
        if (o->y > 0x22000)
            o->ym -= 42;
        if (o->ym < 0)
        {
            o->ym = 0;
            if (o->x <= 0xF000)
            {
                o->state = 25;
                o->xm = 512;
            }
            else
            {
                o->state = 20;
                o->xm = -512;
            }
        }
        break;
    case 20:
        o->x += o->xm;
        if (o->x < 0x4000)
            o->xm += 42;
        if (o->xm > 0)
        {
            o->xm = 0;
            o->state = 30;
            o->ym = -1024;
        }
        break;
    case 25:
        o->x += o->xm;
        if (o->x > 0x1A000)
            o->xm -= 42;
        if (o->xm < 0)
        {
            o->xm = 0;
            o->state = 30;
            o->ym = -1024;
        }
        break;
    case 30:
        o->y += o->ym;
        if (o->y < 0x6000)
            o->ym += 42;
        if (o->ym > 0)
        {
            o->ym = 0;
            if (o->x <= 0xF000)
            {
                o->state = 40;
                o->xm = 512;
            }
            else
            {
                o->state = 40;
                o->xm = -512;
            }
        }
        break;
    case 40:
        o->x += o->xm;
        if (o->x < -0x4000 || o->x > 0x22000)
            o->cond = 0;
        break;
    default:
        break;
    }
    v1 = o->rot1;
    if (v1)
    {
        if (v1 == 1 && ++o->count1 > 16)
        {
            o->rot1 = 0;
            o->child = o->life - 18;
            v3 = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            CreateEntity(13, o->x, o->y, v3);
            PlaySound(7);
        }
    }
    else if (o->life < o->child)
    {
        o->count1 = 0;
        o->rot1 = 1;
        SetCaret(1, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }
    if (o->shock / 2 % 2)
    {
        o->rect = rc[5];
    }
    else if (o->rot1 == 1)
    {
        o->rect = rc[0];
    }
    else
    {
        o->rect = rc[4 - (o->life - o->child) / 4];
    }
}

//----- (00407EE0) --------------------------------------------------------
void ActNpc031_Sodi(Object *o)
{
    RECT rc[2];       // [esp+4h] [ebp-24h]
    unsigned char v2; // [esp+27h] [ebp-1h]

    rc[0].left = 0;
    rc[0].top = 112;
    rc[0].right = 24;
    rc[0].bottom = 136;
    rc[1].left = 24;
    rc[1].top = 112;
    rc[1].right = 48;
    rc[1].bottom = 136;

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->ym = 1024;
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (++o->count1 > 60 || o->shock)
        {
            o->state = 20;
            o->count1 = 0;
        }
        goto LABEL_14;
    case 20:
        o->ym -= 64;
        if (o->ym <= 0)
        {
            o->state = 30;
            o->ym = 0;
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
        }
        goto LABEL_14;
    case 30:
        if (++o->count1 == 16)
        {
            o->state = 40;
            o->ym = -2048;
            o->flag &= ~0x40u;
            o->count2 = 1;
            v2 = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            CreateEntity(13, o->x, o->y, v2);
            PlaySound(7);
        }
        goto LABEL_12;
    case 40:
    LABEL_12:
        if (o->y >= -0x4000)
            goto LABEL_14;
        o->cond = 0;
        break;
    default:
    LABEL_14:
        o->y += o->ym;
        o->rect = rc[o->count2];
        if (o->shock / 2 % 2)
        {
            o->rect.top += 24;
            o->rect.bottom += 24;
        }
        break;
    }
}

//----- (00408150) --------------------------------------------------------
void ActNpc032_Boss2(Object *o)
{
    int v1;            // eax
    unsigned short v2; // ax
    unsigned short v3; // ax
    int v4;            // [esp-8h] [ebp-28h]
    int v5;            // [esp-8h] [ebp-28h]
    intptr_t v6;       // [esp+0h] [ebp-20h]
    int i;             // [esp+8h] [ebp-18h]
    int v8;            // [esp+Ch] [ebp-14h]
    int v9;            // [esp+Ch] [ebp-14h]

    if (o->state < 100 && o->count4 == 3)
    {
        o->state = 100;
        o->flag &= ~2u;
        SetShipInvincibility();
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->ym = 0x200;
        o->y = -0x10000;
        CreateEntity(36, 0, 0, (intptr_t)o);
        CreateEntity(36, 0, 0, (intptr_t)o);
        CreateEntity(34, 0, 0, (intptr_t)o);
        CreateEntity(33, 0, 0, (intptr_t)o);
        CreateEntity(33, 0, 0, (intptr_t)o);
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (o->y > 0x10000)
        {
            o->ym -= 2;
            if (o->ym < 0)
            {
                o->ym = 0;
                o->state = 11;
            }
        }
        goto LABEL_50;
    case 11:
        if (++o->count1 > 40)
        {
            o->state = 20;
            o->ym = -512;
        }
        goto LABEL_50;
    case 20:
        v8 = 0;
        if (ship.y >= 0x14000)
        {
            if (o->y < 0xA000)
                v8 = 1;
        }
        else if (o->y < 0x14000)
        {
            v8 = 1;
        }
        if (v8)
        {
            o->ym += 4;
            if (o->ym > 0)
            {
                o->ym = 0;
                o->state = 21;
            }
        }
        goto LABEL_50;
    case 21:
        if (++o->count1 > 40)
        {
            o->count1 = 0;
            o->state = 30;
            o->ym = 512;
        }
        goto LABEL_50;
    case 30:
        v9 = 0;
        if (ship.y >= 0x14000)
        {
            if (o->y > 0x12000)
                v9 = 1;
        }
        else if (o->y > 0x1D000)
        {
            v9 = 1;
        }
        if (v9)
        {
            o->ym -= 4;
            if (o->ym < 0)
            {
                o->ym = 0;
                o->state = 31;
            }
        }
        goto LABEL_50;
    case 31:
        if (++o->count1 > 40)
        {
            o->count1 = 0;
            o->state = 20;
            o->ym = -512;
        }
        goto LABEL_50;
    case 100:
        o->state = 110;
        o->count1 = 0;
        o->xm = 0;
        o->ym = 0;
        PlayLoopSound(32);
        goto LABEL_40;
    case 110:
    LABEL_40:
        if (o->count1++ < 60)
            goto LABEL_50;
        o->xm = 0;
        o->ym = 341;
        o->state = 120;
        o->count1 = -2;
        PlaySound(12);
        if ((ship.cond & 2) == 0)
        {
            AddScore(o->score);
            SetCaret(0, o->x, o->y - 0x2000, o->score);
            SetShipInvincibility();
        }
        for (i = 0; i < 15; ++i)
        {
            v4 = o->y + ((GetRandom(48) - 20) << 10);
            v2 = GetRandom(48);
            CreateEntity(1, o->x + ((v2 - 24) << 10), v4, 0);
        }
    LABEL_46:
        if (++o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            v5 = o->y + ((GetRandom(64) - 32) << 10);
            v3 = GetRandom(64);
            CreateEntity(1, o->x + ((v3 - 32) << 10), v5, 0);
        }
        if (o->y <= 0x36000)
        {
        LABEL_50:
            if (o->count4 > 0 && o->state >= 20 && o->state < 40)
            {
                v6 = o->child;
                if (v6)
                {
                    if (v6 == 1)
                    {
                        o->xm += 2;
                        if (o->xm > 0x100)
                            o->xm = 0x100;
                        if (o->x > 0x16000)
                            o->child = 0;
                    }
                }
                else
                {
                    o->xm -= 2;
                    if (o->xm < -256)
                        o->xm = -256;
                    if (o->x < 0x8000)
                        o->child = 1;
                }
            }
            o->x += o->xm;
            o->y += o->ym;
            o->rect.left = 80;
            o->rect.top = 48;
            o->rect.right = 136;
            o->rect.bottom = 96;
            if (o->shock / 2 % 2)
            {
                o->rect.top += 48;
                o->rect.bottom += 48;
            }
        }
        else
        {
            o->cond = 0;
            CheckStageClear(2);
            StopLoopSound(32);
        }
        return;
    case 120:
        goto LABEL_46;
    default:
        goto LABEL_50;
    }
}

//----- (004087A0) --------------------------------------------------------
void ActNpc033_Boss2RocketSpawner(Object *o)
{
    RECT rc[2] = {
        {0, 0, 40, 104},
        {40, 0, 80, 104},
    };
    int v1;     // [esp+0h] [ebp-2Ch]
    int px;     // [esp+24h] [ebp-8h]
    Object *v3; // [esp+28h] [ebp-4h]

    v3 = (Object *)o->type2;
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        o->child = dword_44C268;
        dword_44C268 = (dword_44C268 + 1) % 2;
        if (o->child)
            o->rot1 = -100;
        o->state = 10;
    }
    if (v3->state >= 40)
        o->state = 20;
LABEL_9:
    if (o->child)
    {
        o->x = v3->x + 0x8000;
        o->rect = rc[0];
    }
    else
    {
        o->x = v3->x - 0x8000;
        o->rect = rc[1];
    }

    o->y = v3->y + 0x2000;
    if (v3->state < 100)
        ++o->rot1;
    if (o->rot1 >= 200)
    {
        o->rot1 = 0;
        if (o->child)
            px = o->x + 1024;
        else
            px = o->x;
        if (ship.y <= o->y)
        {
            CreateEntity(35, px, o->y - 3072, 3);
            CreateEntity(35, px, o->y - 3072, 4);
            CreateEntity(35, px, o->y - 3072, 5);
        }
        else
        {
            CreateEntity(35, px, o->y - 3072, 0);
            CreateEntity(35, px, o->y - 3072, 1);
            CreateEntity(35, px, o->y - 3072, 2);
        }
        SetCaret(1, px, o->y - 3072, (intptr_t)o);
        PlaySound(36);
    }
    if ((v3->cond & 1) == 0 || v3->type != 32)
        o->cond = 0;
}

//----- (00408A30) --------------------------------------------------------
void ActNpc034_B2ExplosionSpawner_(Object *o)
{
    int v2; // [esp-8h] [ebp-40h]
    RECT rc[3] = {
        {80, 96, 120, 144},
        {120, 96, 160, 144},
        {0, 0, 0, 0},
    };

    Object *v4 = (Object *)o->type2;

    switch (o->state)
    {
    case 0:
        if (v4->state >= 20)
        {
            o->flag &= ~8u;
            o->flag |= 1u;
            o->state = 20;
            o->count2 = 1;
            PlaySound(38);
        }
        goto LABEL_4;
    case 20:
    LABEL_4:
        if (o->life < 872)
        {
            o->state = 30;
            o->count1 = 0;
            o->flag &= ~3u;
        }
        break;
    case 30:
        if (!(o->count1 % 10))
        {
            v2 = o->y + ((GetRandom(48) - 32) << 10);
            CreateEntity(1, o->x + ((GetRandom(32) - 16) << 10), v2, 0);
            PlaySound(26);
        }
        if (++o->count1 > 50)
        {
            o->state = 40;
            o->count2 = 2;
            o->shock = 0;
            CreateEntity(1, o->x + 0x1000, o->y - 0x4000, 0);
            CreateEntity(1, o->x - 0x2000, o->y, 0);
            CreateEntity(1, o->x + 0x3000, o->y + 0x2000, 0);
            PlaySound(11);
            v4->count4 = 1;
            ClearReplaceNpChar(6, 0);
        }
        goto LABEL_11;
    case 40:
    LABEL_11:
        if (v4->state == 120)
        {
            o->state = 100;
            o->count2 = 2;
            o->xoff = 0x2000;
            o->yoff = 0x1000;
        }
        break;
    default:
        break;
    }
    o->x = v4->x;
    o->y = v4->y - 0x1800;

    o->rect = rc[o->count2];

    if (o->shock / 2 % 2)
    {
        o->rect.left += 40;
        o->rect.right += 40;
    }

    if ((v4->cond & 1) == 0 || v4->type != 32)
        o->cond = 0;
}

//----- (00408D70) --------------------------------------------------------
void ActNpc035_B2Rocket(Object *o)
{
    RECT rc[6] = {
        {152, 64, 168, 80},
        {168, 64, 184, 80},
        {184, 64, 200, 80},
        {200, 64, 216, 80},
        {216, 64, 232, 80},
        {232, 64, 248, 80},
    };

    switch (o->state)
    {
    case 0:
        o->state = 10;
        switch (o->type2)
        {
        case 0:
        case 1:
        case 2:
            o->ym = -2048;
            break;
        case 3:
        case 4:
        case 5:
            o->count2 = 3;
            o->ym = 2048;
            break;
        default:
            goto LABEL_5;
        }
        goto LABEL_5;
    case 10:
    LABEL_5:
        if (o->y < 0 || o->y >= 0x28000)
        {
            o->state = 20;
            switch (o->type2)
            {
            case 0:
                o->count2 = 3;
                o->ym = 0x400;
                break;
            case 1:
                o->count2 = 4;
                o->ym = 0x2CC;
                o->xm = -0x400;
                break;
            case 2:
                o->count2 = 5;
                o->ym = 0x2CC;
                o->xm = 0x400;
                break;
            case 3:
                o->count2 = 0;
                o->ym = -0x400;
                break;
            case 4:
                o->count2 = 1;
                o->ym = -0x2CC;
                o->xm = -0x400;
                break;
            case 5:
                o->count2 = 2;
                o->ym = -0x2CC;
                o->xm = 0x400;
                break;
            default:
                break;
            }

            if (!o->type2 || o->type2 == 3)
            {
                SetCaret(1, o->x, o->y, (intptr_t)o);
                PlaySound(12);
            }
        }
        break;
    case 20:
        if (++o->count1 > 30)
        {
            o->count1 = 0;
            o->state = 30;
            switch (o->type2)
            {
            case 0:
            case 1:
            case 2:
                o->count2 = 3;
                o->ym = 0x400;
                break;
            case 3:
            case 4:
            case 5:
                o->count2 = 0;
                o->ym = -0x400;
                break;
            default:
                break;
            }
            o->xm = 0;
        }
        break;
    case 30:
        if (!(++o->count1 % 3))
        {
            switch (o->type2)
            {
            case 0:
            case 1:
            case 2:
                CreateEntity(29, o->x, o->y - 0x2000, 1);
                break;
            case 3:
            case 4:
            case 5:
                CreateEntity(29, o->x, o->y + 0x2000, 0);
                break;
            default:
                goto LABEL_28;
            }
        }
        break;
    default:
        break;
    }
LABEL_28:
    switch (o->type2)
    {
    case 0:
    case 1:
    case 2:
        if (o->y > 0x2C000)
            o->cond = 0;
        break;
    case 3:
    case 4:
    case 5:
        if (o->y < -0x4000)
            o->cond = 0;
        break;
    default:
        break;
    }
    if (o->x < -0x400 || o->x > 0x1E400)
        o->cond = 0;

    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];

    if (o->state != 30)
    {
        if (o->count3++ / 2 % 2)
        {
            o->rect.top += 16;
            o->rect.bottom += 16;
        }
    }
}

//----- (00409260) --------------------------------------------------------
void ActNpc036_Boss2Eye(Object *o)
{
    intptr_t v1; // [esp+0h] [ebp-30h]
    RECT rc[2] = {
        {136, 48, 152, 64},
        {0, 0, 0, 0},
    };

    Object *parent = (Object *)o->type2;
    unsigned char angle; // [esp+2Fh] [ebp-1h]

    if (o->state >= 30 && o->state < 40 && o->life < 918)
    {
        o->state = 100;
        o->count2 = 1;
        o->shock = 0;
        o->flag &= ~3u;
        CreateEntity(1, o->x, o->y, 0);
        PlaySound(12);
        ++parent->count4;
    }
    switch (o->state)
    {
    case 0:
        o->child = byte_44C26C;
        byte_44C26C = (byte_44C26C + 1) % 2;
        if (o->child)
            o->count1 = -50;
        else
            o->count1 = -100;
        o->state = 10;
        goto LABEL_10;
    case 10:
    LABEL_10:
        if (parent->state >= 20)
            o->state = 20;
        goto LABEL_42;
    case 20:
        if (++o->count1 >= 80)
        {
            o->count1 = 0;
            o->state = 21;
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
        }
        if (parent->count4)
            o->state = 29;
        goto LABEL_42;
    case 21:
        if (++o->count1 >= 20)
        {
            angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            CreateEntity(13, o->x, o->y, angle);
            PlaySound(7);
            o->count1 = 0;
            o->state = 20;
        }
        if (parent->count4)
            o->state = 29;
        goto LABEL_42;
    case 29:
        o->state = 30;
        o->count1 = 0;
        o->flag |= 3u;
        if (o->child)
            o->count1 = 25;
        goto LABEL_25;
    case 30:
    LABEL_25:
        if (++o->count1 >= 30)
        {
            o->count1 = 0;
            o->state = 31;
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
        }
        goto LABEL_42;
    case 31:
        if (++o->count1 >= 20)
        {
            angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
            if (parent->count4 >= 2)
            {
                angle += 8;
                CreateEntity(13, o->x, o->y, angle);
                angle -= 16;
            }
            CreateEntity(13, o->x, o->y, angle);
            PlaySound(7);
            if (++o->rot1 < 4)
            {
                o->count1 = 0;
            }
            else
            {
                o->rot1 = 0;
                if (parent->count4 >= 2)
                    o->count1 = -100;
                else
                    o->count1 = -200;
            }
            o->state = 30;
        }
        goto LABEL_42;
    case 100:
        if (parent->state != 120)
            goto LABEL_42;

        o->state = 110;
        o->life = 100;
        o->flag |= 1u;
        o->destroyHitVoice = 4;
        o->w = 6144;
        o->h = 6144;
    LABEL_40:
        if (o->life <= 52)
        {
            o->state = 120;
            CreateEntity(7, o->x, o->y, 2);
            o->flag &= ~1u;
            PlaySound(11);
            CreateEntity(1, o->x, o->y, 0);
        }
    LABEL_42:
        v1 = o->child;
        if (v1)
        {
            if (v1 == 1)
            {
                o->x = parent->x + 0xC00;
                o->y = parent->y - 0x2C00;
            }
        }
        else
        {
            o->x = parent->x - 0x800;
            o->y = parent->y + 0x1800;
        }
        o->rect = rc[o->count2];
        if (o->shock / 2 % 2)
        {
            o->rect.top += 16;
            o->rect.bottom += 16;
        }
        return;
    case 110:
        goto LABEL_40;
    default:
        goto LABEL_42;
    }
}

//----- (00409870) --------------------------------------------------------
void ActNpc037_Stars_(Object *o)
{
    RECT rc[3] = {
        {0, 64, 16, 80},
        {16, 64, 32, 80},
        {32, 64, 48, 80},
    };

    o->y += 0x100;
    if (o->y > 0x2C000)
        o->cond = 0;

    o->rect = rc[o->type2];
}

//----- (00409920) --------------------------------------------------------
void ActNpc038_StarGen(Object *o)
{
    int size; // [esp+4h] [ebp-4h]

    if (++o->count1 > 30)
    {
        o->count1 = 0;
        if (++o->state > 9)
            o->state = 0;
    }

    if (o->count1)
        return;

    switch (o->state)
    {
    case 0:
        size = 1;
        break;
    case 1:
        size = 2;
        break;
    case 2:
        size = 0;
        break;
    case 3:
        size = 1;
        break;
    case 4:
        size = 0;
        break;
    case 7:
        size = 2;
        break;
    default:
        size = 4;
        break;
    }

    if (size != 4)
    {
        CreateEntity(37, GetRandom(120) << 10, -0x4000, size);
    }
}

//----- (00409A20) --------------------------------------------------------
void ActNpc039_Elka2(Object *o)
{
    int v2; // [esp+0h] [ebp-70h]
    int i;  // [esp+4h] [ebp-6Ch]
    int x;  // [esp+8h] [ebp-68h] BYREF
    int y;  // [esp+Ch] [ebp-64h] BYREF

    RECT rc[6] = {
        {0, 0, 32, 32},
        {32, 0, 64, 32},
        {64, 0, 96, 32},
        {96, 0, 128, 32},
        {128, 0, 160, 32},
        {160, 0, 192, 32},
    };

    if (o->state < 100 && o->life <= 50)
    {
        o->state = 100;
        o->count1 = 0;
        o->shock = 0;
        o->flag &= ~1u;
        o->flag |= 2u;
        SetCaret(4, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }

    v2 = o->state;
    if (!v2)
    {
        o->state = 10;
        o->child = o->life - 24;
        o->flag |= 3u;
        o->y -= 0x2000;
    LABEL_9:
        if (o->shock)
        {
            y = o->y;
            SubStageXOScroll(0, &y);
            if (y >= ship.y)
                o->y += 0x100;
            else
                o->y -= 0x100;
        }
        goto LABEL_20;
    }
    if (v2 == 10)
        goto LABEL_9;
    if (v2 != 100 || (++o->count1, o->count1 < 14))
    {
    LABEL_20:
        if (o->state < 100)
        {
            if (o->shock / 2 % 2)
                o->rect = rc[5];
            else
                o->rect = rc[(100 - o->life) / 10];
        }
        else
        {
            o->rect = rc[0];
        }
        y = o->y;
        SubStageXOScroll(0, &y);
        if (y >= 0x2C000)
            o->cond = 0;
        return;
    }

    x = o->x;
    y = o->y;

    SubStageXOScroll(&x, &y);

    for (i = 0; i < 8; ++i)
        CreateEntity(14, x, y, (unsigned char)(32 * i));

    PlaySound(13);
    CreateEntity(1, x, y, 0);

    AddScore(o->score);
    SetCaret(0, x, y, o->score);

    o->cond = 0;
}