#include <windows.h>

#include "NpcAct040.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00409D90) --------------------------------------------------------
void ActNpc040_GuxtFort(Object *o)
{
    static RECT rcGuxtFort[3] = {
        {80, 96, 96, 112},
        {96, 96, 112, 112},
        {112, 96, 128, 112},
    };

    int v1; // [esp+0h] [ebp-Ch]
    int x;  // [esp+4h] [ebp-8h] BYREF
    int y;  // [esp+8h] [ebp-4h] BYREF

    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    v1 = o->state;

    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 11)
            {
                if ((++o->count1 % 7) == 0)
                {
                    CreateEntity(13, x, y, (unsigned char)o->child);
                    PlaySound(7);
                }
                if (o->count1 == 21)
                {
                    o->count1 = -150;
                    o->state = 10;
                }
            }
            goto LABEL_15;
        }
    }
    else
    {
        o->state = 10;
        o->flag |= 1u;
    }
    if (++o->count1 == 50)
    {
        SetCaret(1, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }
    if (o->count1 == 66)
    {
        o->count1 = 0;
        o->state = 11;
        o->child = GetArktan(x - ship.x, y - ship.y, 64);
    }
LABEL_15:
    if (++o->count3 > 4)
    {
        o->count3 = 0;
        if (++o->count2 > 2)
            o->count2 = 0;
    }
    if (o->shock / 2 % 2)
    {
        o->rect = rcGuxtFort[2];
    }
    else
    {
        o->rect = rcGuxtFort[o->count2];
    }

    if (y > 0x2C000)
        o->cond = 0;
}

//----- (00409FB0) --------------------------------------------------------
void ActNpc041_CatEye(Object *o)
{
    unsigned char angle; // al
    int x;               // [esp+4h] [ebp-68h] BYREF
    int y;               // [esp+8h] [ebp-64h] BYREF
    RECT rc[5] = {
        {0, 80, 16, 96},
        {16, 80, 32, 96},
        {32, 80, 48, 96},
        {48, 80, 64, 96},
        {64, 80, 80, 96},
    };
    RECT rcStage; // [esp+5Ch] [ebp-10h] BYREF

    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->count1 = 50 * o->type2;
        goto LABEL_3;
    case 10:
    LABEL_3:
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
        if (o->count2 == 3)
        {
            o->state = 30;
            o->count1 = 0;
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
            o->flag |= 1u;
        }
        break;
    case 30:
        if (++o->count1 > 14)
        {
            o->state = 40;
            angle = GetArktan(x - ship.x, y - ship.y, 64);
            CreateEntity(14, x, y, angle);
            PlaySound(7);
        }
        break;
    default:
        break;
    }
    if (o->shock / 2 % 2)
        o->rect = rc[4];
    else
        o->rect = rc[o->count2];

    GetStageRect(&rcStage);
    if (o->y > rcStage.bottom + 0x2000)
        o->cond = 0;
}

//----- (0040A280) --------------------------------------------------------
void ActNpc042_Slider(Object *o)
{
    int v1; // [esp+0h] [ebp-40h]
    int x;  // [esp+4h] [ebp-3Ch] BYREF
    int y;  // [esp+8h] [ebp-38h] BYREF
    RECT rc[3] = {
        {0, 32, 32, 48},
        {32, 32, 64, 48},
        {64, 32, 96, 48},
    };
    unsigned char angle; // [esp+3Fh] [ebp-1h]

    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 20)
            {
                o->xm = 0;
                if (++o->count1 == 20)
                {
                    SetCaret(1, o->x, o->y, (intptr_t)o);
                    PlaySound(30);
                }
                if (o->count1 == 30)
                {
                    o->count1 = 0;
                    angle = 64;
                    if (ship.y < y)
                        angle += 0x80;
                    CreateEntity(13, x, y, angle);
                    PlaySound(7);
                }
            }
            goto LABEL_15;
        }
    }
    else
    {
        o->state = 10;
        o->flag |= 0x40u;
    }
    o->xm = 0;
    o->count2 = 0;
    if (ship.y - y < 0x14000)
    {
        o->state = 20;
        o->count1 = 0;
        o->count2 = 1;
        o->flag |= 3u;
        PlaySound(38);
    }

LABEL_15:
    if (x < ship.x - 0x400)
        o->xm = 0x100;
    if (x > ship.x + 0x400)
        o->xm = -0x100;
    o->x += o->xm;
    if (y > 0x2C000)
        o->cond = 0;
    if (o->shock / 2 % 2)
        o->rect = rc[2];
    else
        o->rect = rc[o->count2];
}

//----- (0040A4F0) --------------------------------------------------------
void ActNpc043_Cycloid(Object *o)
{
    RECT rc[8] = {
        {112, 48, 128, 64},
        {128, 48, 144, 64},
        {144, 48, 160, 64},
        {160, 48, 176, 64},
        {176, 48, 192, 64},
        {192, 48, 208, 64},
        {208, 48, 224, 64},
        {224, 48, 240, 64},
    };

    if (o->type2)
    {
        switch (o->state)
        {
        case 0:
            o->state = 10;
            o->flag &= ~0x40u;
            o->count2 = 0;
            o->xm = 0;
            o->ym = -0x800;
            o->y = 0x2C000;
            PlaySound(26);
            goto LABEL_29;
        case 10:
        LABEL_29:
            if (o->y <= 0x7800)
            {
                o->state = 20;
                if (o->x <= 0xF000)
                {
                    o->count2 = 1;
                    o->xm = 0x599;
                }
                else
                {
                    o->count2 = 7;
                    o->xm = -0x599;
                }
                o->ym = -0x599;
            }
            goto LABEL_50;
        case 20:
            if (o->y <= 0x2000)
            {
                o->state = 30;
                o->count1 = 0;
                if (o->x > 0xF000)
                {
                LABEL_12:
                    o->count2 = 6;
                    o->xm = -0x800;
                    o->ym = 0;
                    o->child = (o->x - 0xF000) / 0x400;
                }
                else
                {
                    o->count2 = 2;
                    o->xm = 2048;
                    o->ym = 0;
                    o->child = (0xF000 - o->x) / 0x400;
                }
            }
            goto LABEL_50;
        case 30:
            if (++o->count1 > o->child)
            {
                o->state = 40;
                if (o->xm >= 0)
                    o->count2 = 3;
                else
                    o->count2 = 5;
                o->ym = 1433;
            }
            goto LABEL_50;
        case 40:
            if (o->y >= 0x5800)
            {
                o->state = 50;
                o->xm = 0;
                o->ym = 0x800;
                o->count2 = 4;
            }
            goto LABEL_50;
        case 50:
            if (o->y <= 0x2C000)
                goto LABEL_50;
            o->cond = 0;
            return;
        default:
            goto LABEL_50;
        }
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag &= ~0x40u;
        o->count2 = 4;
        o->xm = 0;
        o->ym = 2048;
        PlaySound(26);
        goto LABEL_4;
    case 10:
    LABEL_4:
        if (o->y >= 0x20800)
        {
            o->state = 20;
            if (o->x <= 0xF000)
            {
                o->count2 = 3;
                o->xm = 0x599;
            }
            else
            {
                o->count2 = 5;
                o->xm = -0x599;
            }
            o->ym = 1433;
        }
        break;
    case 20:
        if (o->y < 0x26000)
            break;
        o->state = 30;
        o->count1 = 0;
        if (o->x > 0xF000)
            goto LABEL_12;
        o->count2 = 2;
        o->xm = 2048;
        o->ym = 0;
        o->child = (0xF000 - o->x) / 0x400;
        break;
    case 30:
        if (++o->count1 > o->child)
        {
            o->state = 40;
            if (o->xm >= 0)
                o->count2 = 1;
            else
                o->count2 = 7;
            o->ym = -0x599;
        }
        break;
    case 40:
        if (o->y <= 0x22800)
        {
            o->state = 50;
            o->xm = 0;
            o->ym = -0x800;
            o->count2 = 0;
        }
        break;
    case 50:
        if (o->y >= -0x4000)
            break;
        o->cond = 0;
        return;
    default:
        break;
    }

LABEL_50:
    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];
    if (o->shock / 2 % 2)
    {
        o->rect.top += 16;
        o->rect.bottom += 16;
    }
}

//----- (0040AB80) --------------------------------------------------------
void ActNpc044_Chester(Object *o)
{
    int v1;  // [esp+0h] [ebp-74h]
    int s_x; // [esp+4h] [ebp-70h] BYREF
    int s_y; // [esp+8h] [ebp-6Ch] BYREF
    RECT rc[6] = {
        {96, 32, 112, 48},
        {112, 32, 128, 48},
        {128, 32, 144, 48},
        {112, 32, 128, 48},
        {144, 32, 160, 48},
        {160, 32, 176, 48},
    };
    unsigned char v5; // [esp+73h] [ebp-1h]

    s_x = o->x;
    s_y = o->y;
    SubStageXOScroll(&s_x, &s_y);
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 20 && ++o->count1 > 24)
            {
                o->state = 10;
                o->count1 = 0;
                o->count2 = 0;
                o->count3 = 0;
                o->shock = 0;
                o->flag |= 8u;
                o->flag &= ~3u;
                v5 = GetArktan(s_x - ship.x, s_y - ship.y, 64);
                o->xm = GetCos(v5);
                o->ym = GetSin(v5);
                if (o->child > 6)
                    o->ym = 0x400;
            }
            goto LABEL_24;
        }
    }
    else
    {
        o->state = 10;
        o->count1 = -20;
        o->flag |= 0x48u;
        v5 = GetArktan(s_x - ship.x, s_y - ship.y, 64);
        o->xm = 2 * (GetCos(v5) / 3);
        o->ym = 2 * (GetSin(v5) / 3);
    }
    if ((o->cond & 0x10) != 0 && o->xm < 0)
    {
        o->xm = -o->xm;
    }
    else if ((o->cond & 0x40) != 0 && o->ym < 0)
    {
        o->ym = -o->ym;
    }
    else if ((o->cond & 0x20) != 0 && o->xm > 0)
    {
        o->xm = -o->xm;
    }
    else if ((o->cond & 0x80) != 0 && o->ym > 0)
    {
        o->ym = -o->ym;
    }
    o->cond &= ~0xF0u;
    if (++o->count1 > 36)
    {
        o->count1 = 0;
        o->state = 20;
        o->xm = 0;
        o->ym = 0;
        o->count2 = 4;
        ++o->child;
        o->flag &= ~8u;
        o->flag |= 3u;
        PlaySound(39);
    }
LABEL_24:
    o->x += o->xm;
    o->y += o->ym;
    if (o->state < 20)
    {
        if (++o->count3 > 3)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 3)
            o->count2 = 0;
    }
    if (o->shock / 2 % 2)
        o->rect = rc[5];
    else
        o->rect = rc[o->count2];
    if (s_y > 0x2A000)
        o->cond = 0;
}

//----- (0040AFD0) --------------------------------------------------------
void ActNpc045_Bonus(Object *o)
{
    RECT rc[2] = {
        {0, 0, 16, 16},
        {16, 0, 32, 16},
    };

    if (!o->state)
    {
        o->state = 10;
        o->count2 = o->type2;
        if (o->type2)
        {
            o->flag |= 0x10u;
            AddStageXOScroll(&o->x, &o->y);
        }
        else
        {
            o->score = 5;
            o->ym = 0x400;
        }
    }
    o->x += o->xm;
    o->y += o->ym;
    int sx = o->x;
    int sy = o->y;
    if ((o->flag & 0x10) != 0)
        SubStageXOScroll(&sx, &sy);
    if (sy > 0x2C000)
        o->cond = 0;
    o->rect = rc[o->count2];
}

//----- (0040B120) --------------------------------------------------------
void ActNpc046_BonusGen(Object *o)
{
    if (!o->type2 && ship.rot1 > 400)
    {
        CreateEntity(45, o->x, -8, 0);
        o->cond = 0;
    }
}

//----- (0040B170) --------------------------------------------------------
void ActNpc047_CloudXL(Object *o)
{
    RECT rc = {0, 80, 96, 128};

    o->y += 0x1000;
    if (o->y > 0x34000)
        o->cond = 0;

    o->rect = rc;
}

//----- (0040B1E0) --------------------------------------------------------
void ActNpc048_Gimmick(Object *a1)
{
    int s_x; // [esp+14h] [ebp-48h] BYREF
    int s_y; // [esp+18h] [ebp-44h] BYREF
    RECT v4[4] = {
        {192, 0, 208, 16},
        {208, 0, 224, 16},
        {224, 0, 240, 16},
        {240, 0, 256, 16},
    };
    s_x = a1->x;
    s_y = a1->y;
    SubStageXOScroll(&s_x, &s_y);
    switch (a1->state)
    {
    case 0:
        a1->state = 10;
        a1->count2 = a1->type2;
        a1->flag |= 3u;
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (a1->shock)
        {
            a1->state = 20;
            a1->flag &= ~1u;
            a1->flag |= 8u;
        }
        goto LABEL_44;
    case 20:
        if (a1->count1 >= 12)
        {
            a1->state = 30;
            a1->flag |= 1u;
            a1->flag &= ~8u;
        LABEL_27:
            switch (a1->type2)
            {
            case 0:
                if (ship.x > s_x - 0x4000)
                    a1->state = 40;
                break;
            case 1:
                if (ship.y > s_y - 0x4000)
                    a1->state = 40;
                break;
            case 2:
                if (ship.x < s_x + 0x4000)
                    a1->state = 40;
                break;
            case 3:
                if (ship.y < s_y + 0x4000)
                    a1->state = 40;
                break;
            default:
                break;
            }
            if (a1->state == 40)
            {
                a1->count1 = 0;
                PlaySound(30);
                SetCaret(1, a1->x, a1->y, (intptr_t)a1);
            }
        }
        else
        {
            if (a1->count1 >= 4)
            {
                switch (a1->type2)
                {
                case 0:
                    a1->x += 0x800;
                    break;
                case 1:
                    a1->y += 0x800;
                    break;
                case 2:
                    a1->x -= 0x800;
                    break;
                case 3:
                    a1->y -= 0x800;
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (a1->type2)
                {
                case 0:
                    a1->x += 0x1000;
                    break;
                case 1:
                    a1->y += 0x1000;
                    break;
                case 2:
                    a1->x -= 0x1000;
                    break;
                case 3:
                    a1->y -= 0x1000;
                    break;
                default:
                    break;
                }
            }
            if (a1->count1 == 4)
            {
                switch (a1->type2)
                {
                case 0:
                    a1->count2 = 2;
                    break;
                case 1:
                    a1->count2 = 3;
                    break;
                case 2:
                    a1->count2 = 0;
                    break;
                case 3:
                    a1->count2 = 1;
                    break;
                default:
                    break;
                }
            }
            ++a1->count1;
        }
    LABEL_44:
        a1->rect = v4[a1->count2];
        if (a1->shock / 2 % 2)
        {
            a1->rect.top += 32;
            a1->rect.bottom += 32;
        }
        else if (a1->state >= 30)
        {
            a1->rect.top += 16;
            a1->rect.bottom += 16;
        }
        if (s_y > 0x2C000)
            a1->cond = 0;
        return;
    case 30:
        goto LABEL_27;
    case 40:
        if (++a1->count1 == 14)
        {
            CreateEntity(14, s_x, s_y, GetArktan(s_x - ship.x, s_y - ship.y, 64));
            PlaySound(7);
        }
        goto LABEL_44;
    default:
        goto LABEL_44;
    }
}

//----- (0040B6B0) --------------------------------------------------------
void ActNpc049_Boss3(Object *o)
{
    int v3;  // edx
    int v4;  // [esp-8h] [ebp-28h]
    int v5;  // [esp-8h] [ebp-28h]
    int i;   // [esp+4h] [ebp-1Ch]
    int s_x; // [esp+8h] [ebp-18h] BYREF
    int s_y; // [esp+Ch] [ebp-14h] BYREF
    RECT rcBoss = {0, 64, 64, 120};

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 2u;
        o->y -= 28672;
        CreateEntity(51, 0, 0, (intptr_t)o);
        CreateEntity(52, 0, 0, (intptr_t)o);
        CreateEntity(53, 0, 0, (intptr_t)o);
        s_x = o->x;
        s_y = o->y;
        SubStageXOScroll(&s_x, &s_y);
        CreateEntity(54, s_x - 13312, s_y, (intptr_t)o);
        CreateEntity(54, s_x + 13312, s_y, (intptr_t)o);
        s_x = o->x - 40960;
        s_y = o->y + 12288;
        SubStageXOScroll(&s_x, &s_y);
        CreateEntity(55, s_x, s_y, (intptr_t)o);
        s_x = o->x + 40960;
        s_y = o->y + 12288;
        SubStageXOScroll(&s_x, &s_y);
        CreateEntity(55, s_x, s_y, (intptr_t)o);
        s_x = o->x - 40960;
        s_y = o->y - 4096;
        SubStageXOScroll(&s_x, &s_y);
        CreateEntity(57, s_x, s_y, (intptr_t)o);
        s_x = o->x + 40960;
        s_y = o->y - 4096;
        SubStageXOScroll(&s_x, &s_y);
        CreateEntity(57, s_x, s_y, (intptr_t)o);
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (o->count1++ > 200)
        {
            o->count1 = 0;
            o->state = 20;
            o->child = 1;
        }
        goto LABEL_18;
    case 20:
        if (o->child >= 4)
            goto LABEL_7;
        goto LABEL_18;
    case 100:
    LABEL_7:
        o->state = 110;
        o->count1 = 0;
        PlayLoopSound(32);
        goto LABEL_8;
    case 110:
    LABEL_8:
        if (++o->count1 < 60)
            goto LABEL_18;
        o->xm = 0;
        o->ym = 341;
        o->state = 120;
        PlaySound(12);
        if ((ship.cond & 2) == 0)
        {
            AddScore(o->score);
            s_x = o->x;
            s_y = o->y;
            SubStageXOScroll(&s_x, &s_y);
            SetCaret(0, s_x, s_y, o->score);
            SetShipInvincibility();
        }
        for (i = 0; i < 15; ++i)
        {
            v4 = o->y + ((GetRandom(48) - 20) << 10);
            CreateEntity(1, o->x + ((GetRandom(48) - 24) << 10), v4, 0);
        }
    LABEL_14:
        if (++o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            v5 = o->y + ((GetRandom(64) - 32) << 10);
            v3 = (GetRandom(64) - 32) << 10;
            CreateEntity(1, o->x + v3, v5, 0);
        }
        if (++o->count3 <= 250)
        {
        LABEL_18:
            o->rect = rcBoss;
        }
        else
        {
            o->state = 121;
            CheckStageClear(3);
            StopLoopSound(32);
        }
        return;
    case 120:
        goto LABEL_14;
    default:
        goto LABEL_18;
    }
}

//----- (0040BB80) --------------------------------------------------------
void ActNpc050_62_PowerupHelper(Object *o)
{
    RECT rc = {0, 0, 16, 16};
    Object *parent = (Object *)o->type2;

    if (!o->state)
    {
        o->state = 10;
        o->count2 = parent->type2 - 1;
    }

    o->x = parent->x;
    o->y = parent->y;
    o->rect = rc;
    o->rect.left = 16 * (parent->type2 - 1);
    o->rect.right = o->rect.left + 16;

    if (parent->num >= o->num || (parent->cond & 1) == 0)
        o->cond = 0;
}

static RECT rcB3Eyes[6] = {
    {96, 48, 112, 64},
    {112, 48, 128, 64},
    {128, 48, 144, 64},
    {144, 48, 160, 64},
    {160, 48, 176, 64},
    {0, 0, 0, 0},
};

//----- (0040BC50) --------------------------------------------------------
void ActNpc051_B3Eye1_(Object *o)
{
    int x; // [esp+4h] [ebp-Ch] BYREF
    int y; // [esp+8h] [ebp-8h] BYREF
    Object *parent = (Object *)o->type2;

    o->x = parent->x;
    o->y = parent->y + 0x3800;
    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    if (o->state < 100 && o->life < 900)
    {
        o->state = 100;
        o->count1 = 0;
        o->shock = 0;
        o->count2 = 5;
        parent->child = 2;
        o->flag &= ~1u;
        CreateEntity(1, x, y, 0);
        PlaySound(12);
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 0xAu;
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (parent->child == 1)
            o->state = 18;
        goto LABEL_30;
    case 18:
        if (++o->count1 > 50)
        {
            o->state = 19;
            o->flag &= ~8u;
            o->flag |= 1u;
            PlaySound(38);
        }
        goto LABEL_30;
    case 19:
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 == 3)
        {
            o->state = 20;
            o->count1 = 0;
            CreateEntity(14, x, y, 64);
        }
        goto LABEL_30;
    case 20:
        switch (++o->count1)
        {
        case 149:
            CreateEntity(18, x, y, 0);
            CreateEntity(18, x, y, 1);
            CreateEntity(18, x, y, 2);
            break;
        case 150:
            CreateEntity(18, x, y, 0);
            CreateEntity(18, x, y, 1);
            CreateEntity(18, x, y, 2);
            o->count1 = 0;
            break;
        case 148:
            PlaySound(9);
            break;
        case 130:
            SetCaret(4, o->x, o->y, (intptr_t)o);
            PlaySound(31);
            break;
        }
        goto LABEL_30;
    case 100:
        if (parent->state != 120)
            goto LABEL_30;
        o->state = 110;
        o->life = 100;
        o->flag |= 1u;
        o->destroyHitVoice = 4;
        o->w = 6144;
        o->h = 6144;
    LABEL_28:
        if (o->life <= 52)
        {
            o->state = 120;
            CreateEntity(7, x, y, 2);
            o->flag &= ~1u;
            PlaySound(11);
            CreateEntity(1, x, y, 0);
        }
    LABEL_30:
        if (o->count2 == 5 || !(o->shock / 2 % 2))
        {
            o->rect = rcB3Eyes[o->count2];
        }
        else
        {
            o->rect = rcB3Eyes[4];
        }
        return;
    case 110:
        goto LABEL_28;
    default:
        goto LABEL_30;
    }
}

//----- (0040C0D0) --------------------------------------------------------
void ActNpc052_B3Eye2_(Object *o)
{
    int x; // [esp+4h] [ebp-Ch] BYREF
    int y; // [esp+8h] [ebp-8h] BYREF
    Object *parent = (Object *)o->type2;

    o->x = parent->x;
    o->y = parent->y + 1024;
    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    if (o->state < 100 && o->life < 900)
    {
        o->state = 100;
        o->count1 = 0;
        o->shock = 0;
        o->count2 = 5;
        parent->child = 3;
        o->flag &= ~1u;
        CreateEntity(1, x, y, 0);
        PlaySound(12);
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 8u;
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (parent->child == 2)
            o->state = 18;
        goto LABEL_30;
    case 18:
        if (++o->count1 > 50)
        {
            o->state = 19;
            o->flag &= ~8u;
            o->flag |= 3u;
            PlaySound(38);
        }
        goto LABEL_30;
    case 19:
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 == 3)
        {
            o->state = 20;
            o->count1 = 0;
            CreateEntity(14, x, y, 64);
        }
        goto LABEL_30;
    case 20:
        switch (++o->count1)
        {
        case 149:
            CreateEntity(18, x, y, 0);
            break;
        case 150:
            CreateEntity(18, x, y, 0);
            o->count1 = 0;
            break;
        case 148:
            PlaySound(9);
            break;
        case 130:
            SetCaret(4, o->x, o->y, (intptr_t)o);
            PlaySound(31);
            break;
        }
        goto LABEL_30;
    case 100:
        if (parent->state != 120)
            goto LABEL_30;
        o->state = 110;
        o->life = 100;
        o->flag |= 1u;
        o->destroyHitVoice = 4;
        o->w = 6144;
        o->h = 6144;
    LABEL_28:
        if (o->life <= 52)
        {
            o->state = 120;
            CreateEntity(7, x, y, 2);
            o->flag &= ~1u;
            PlaySound(11);
            CreateEntity(1, x, y, 0);
        }
    LABEL_30:
        if (o->count2 == 5 || !(o->shock / 2 % 2))
            o->rect = rcB3Eyes[o->count2];
        else
            o->rect = rcB3Eyes[4];
        return;
    case 110:
        goto LABEL_28;
    default:
        goto LABEL_30;
    }
}

//----- (0040C500) --------------------------------------------------------
void ActNpc053_B3Eye3_(Object *o)
{
    unsigned char angle; // [esp+7h] [ebp-Dh]
    int x;               // [esp+8h] [ebp-Ch] BYREF
    int y;               // [esp+Ch] [ebp-8h] BYREF
    Object *parent = (Object *)o->type2;

    o->x = parent->x;
    o->y = parent->y - 0x3000;
    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    if (o->state < 100 && o->life < 900)
    {
        o->state = 100;
        o->count1 = 0;
        o->shock = 0;
        o->count2 = 5;
        parent->child = 4;
        o->flag &= ~1u;
        CreateEntity(1, x, y, 0);
        PlaySound(12);
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 8u;
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (parent->child == 3)
            o->state = 18;
        goto LABEL_34;
    case 18:
        if (++o->count1 > 50)
        {
            o->state = 19;
            o->flag &= ~8u;
            o->flag |= 3u;
            PlaySound(38);
        }
        goto LABEL_34;
    case 19:
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 == 3)
        {
            o->state = 20;
            o->count1 = 0;
            CreateEntity(14, x, y, 64);
        }
        goto LABEL_34;
    case 20:
        switch (++o->count1)
        {
        case 50:
            angle = GetArktan(x - ship.x, y - ship.y, 64);
            CreateEntity(13, x, y, angle);
            CreateEntity(13, x, y, angle - 8);
            CreateEntity(13, x, y, angle + 8);
            CreateEntity(13, x, y, angle - 16);
            CreateEntity(13, x, y, angle + 16);
            PlaySound(7);
            break;
        case 34:
            SetCaret(1, o->x, o->y, (intptr_t)o);
            PlaySound(30);
            break;
        case 166:
            o->count1 = 0;
            break;
        case 150:
        case 156:
        case 162:
            CreateEntity(63, x - 0x4400, y + 0x7000, o->child);
            CreateEntity(63, x + 0x4400, y + 0x7000, o->rot1);
            PlaySound(36);
            break;
        case 130:
            SetCaret(1, o->x - 0x4400, o->y + 0x7000, (intptr_t)o);
            SetCaret(1, o->x + 0x4400, o->y + 0x7000, (intptr_t)o);
            PlaySound(31);
            SetCaret(5, ship.x, ship.y, 0);
            o->child = GetArktan(x - 0x4400 - ship.x, y + 0x7000 - ship.y, 64);
            o->rot1 = GetArktan(x + 0x4400 - ship.x, y + 0x7000 - ship.y, 64);
            break;
        }
        goto LABEL_34;
    case 100:
        if (parent->state != 120)
            goto LABEL_34;
        o->state = 110;
        o->life = 100;
        o->flag |= 1u;
        o->destroyHitVoice = 4;
        o->w = 6144;
        o->h = 6144;
    LABEL_32:
        if (o->life <= 52)
        {
            o->state = 120;
            CreateEntity(7, x, y, 2);
            o->flag &= ~1u;
            PlaySound(11);
            CreateEntity(1, x, y, 0);
        }
    LABEL_34:
        if (o->count2 == 5 || !(o->shock / 2 % 2))
            o->rect = rcB3Eyes[o->count2];
        else
            o->rect = rcB3Eyes[4];
        return;
    case 110:
        goto LABEL_32;
    default:
        goto LABEL_34;
    }
}

//----- (0040CB00) --------------------------------------------------------
void ActNpc054_B3BulletBlocker_(Object *o)
{
    o->flag |= 8u;
}

//----- (0040CB20) --------------------------------------------------------
void ActNpc055_B3Target__(Object *a1)
{
    unsigned char v1; // al
    int x;            // [esp+4h] [ebp-60h] BYREF
    int y;            // [esp+8h] [ebp-5Ch] BYREF
    RECT rc[5] = {
        {96, 64, 112, 80},
        {112, 64, 128, 80},
        {128, 64, 144, 80},
        {144, 64, 160, 80},
        {160, 64, 176, 80},
    };
    Object *parent = (Object *)a1->type2;

    x = a1->x;
    y = a1->y;
    SubStageXOScroll(&x, &y);
    if (a1->state < 100 && parent->child > 1)
    {
        a1->state = 100;
        a1->count1 = 0;
        a1->shock = 0;
        a1->flag &= ~1u;
    }
    switch (a1->state)
    {
    case 0:
        a1->state = 10;
        a1->flag |= 8u;
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (parent->child == 1)
        {
            a1->state = 19;
            a1->flag &= ~8u;
            a1->flag |= 1u;
            PlaySound(38);
        }
        break;
    case 19:
        if (++a1->count3 > 2)
        {
            a1->count3 = 0;
            ++a1->count2;
        }
        if (a1->count2 == 2)
            a1->state = 20;
        break;
    case 20:
        if (++a1->count1 == 86)
        {
            SetCaret(1, a1->x, a1->y, (intptr_t)a1);
            PlaySound(30);
        }
        if (a1->count1 == 100)
        {
            a1->count1 = 0;
            v1 = GetArktan(x - ship.x, y - ship.y, 64);
            CreateEntity(14, x, y, v1);
            PlaySound(7);
        }
        if (a1->life < 912)
        {
            a1->state = 90;
            a1->count2 = 3;
            AddScore(a1->score);
            SetCaret(0, a1->x, a1->y, a1->score);
            CreateEntity(1, x, y, 0);
            PlaySound(12);
            a1->flag &= ~1u;
        }
        break;
    case 100:
        if (++a1->count1 > 50)
        {
            CreateEntity(1, x, y, 0);
            PlaySound(14);
            a1->cond = 0;
        }
        break;
    default:
        break;
    }
    if (a1->shock / 2 % 2)
        a1->rect = rc[4];
    else
        a1->rect = rc[a1->count2];
}

//----- (0040CF20) --------------------------------------------------------
void ActNpc056_Checkpoint(Object *o)
{
    if (!o->state)
    {
        o->state = 10;
        SetCheckpointScroll();
        SetCaret(3, 0, 0, 1);
        PlaySound(43);
    }
    o->y += 0x400;
    if (o->y > 0x2A000)
        o->cond = 0;
}

//----- (0040CF90) --------------------------------------------------------
void ActNpc057_Boss3TurretSpawner(Object *o)
{
    int s_x; // [esp+4h] [ebp-3Ch] BYREF
    int s_y; // [esp+8h] [ebp-38h] BYREF
    RECT rc[3] = {
        {192, 48, 208, 64},
        {208, 48, 224, 64},
        {224, 48, 240, 64},
    };
    Object *parent = (Object *)o->type2;

    s_x = o->x;
    s_y = o->y;
    SubStageXOScroll(&s_x, &s_y);

    switch (o->state)
    {
    case 0:
        o->state = 10;
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (parent->child == 2)
        {
            o->state = 19;
            PlaySound(38);
        }
        break;
    case 19:
        if (++o->count3 > 1)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 == 2)
        {
            o->state = 20;
            if (s_x < 61440)
                o->count1 = 80;
        }
        break;
    case 20:
        if (++o->count1 == 160)
        {
            o->count1 = 0;
            CreateEntity(58, s_x, s_y - 0x2800, 0);
        }
        if (parent->child != 2)
            o->state = 30;
        break;
    default:
        break;
    }

    o->rect = rc[o->count2];
}

//----- (0040D170) --------------------------------------------------------
void __cdecl ActNpc058_B3Turret(Object *o)
{
    int v2; // [esp+0h] [ebp-3Ch]
    int x;  // [esp+4h] [ebp-38h] BYREF
    int y;  // [esp+8h] [ebp-34h] BYREF
    RECT rc[3] = {
        {192, 64, 208, 80},
        {208, 64, 224, 80},
        {224, 64, 240, 80},
    };

    v2 = o->state;
    if (v2)
    {
        if (v2 == 10)
        {
            o->y += 0x200;
            ++o->count1;
            x = o->x;
            y = o->y;
            SubStageXOScroll(&x, &y);
            if (o->count1 == 136)
            {
                SetCaret(1, o->x, o->y, (intptr_t)o);
                PlaySound(30);
            }
            if (o->count1 == 150)
            {
                o->count1 = 0;
                CreateEntity(14, x, y, GetArktan(x - ship.x, y - ship.y, 64));
                PlaySound(7);
            }
            if (y > 0x2C000)
                o->cond = 0;
        }
    }
    else
    {
        o->y += 0x400;
        ++o->count1;
        ++o->count3;
        if (o->count1 > 20)
        {
            o->count1 = 100;
            o->state = 0;
            o->state = 10;
            o->flag |= 1u;
        }
    }
    ++o->count3;
    if (++o->count3 > 1)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 1)
        o->count2 = 0;

    if (o->shock / 2 % 2)
        o->rect = rc[2];
    else
        o->rect = rc[o->count2];
}

//----- (0040D3F0) --------------------------------------------------------
void ActNpc059_PowerupSpinnerShield(Object *o)
{
    RECT rc[6] = {
        {0, 24, 24, 48},
        {24, 24, 48, 48},
        {48, 24, 72, 48},
        {144, 0, 168, 24},
        {168, 0, 192, 24},
        {192, 0, 216, 24},
    };

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = 0x28000;
        o->ym = -0x1800;
        if (o->type2)
        {
            CreateEntity(50, 0, 0, (intptr_t)o);
            o->life = 1;
            o->score = 0;
        }
        PlaySound(26);
        goto LABEL_5;
    case 10:
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
    case 20:
    LABEL_10:
        o->state = 30;
        o->flag |= 0x43u;
        o->damage = 1;
        goto LABEL_11;
    case 30:
    LABEL_11:
        if (o->type2)
        {
            o->ym += 42;
        }
        else
        {
            if (ship.x >= o->x)
                o->xm += 0x20;
            else
                o->xm -= 0x20;

            if (o->xm < -0x400)
                o->xm = -0x400;
            if (o->xm > 0x400)
                o->xm = 0x400;
            o->ym += 0x40;
        }
        if (++o->count3 > 1)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 5)
            o->count2 = 3;
        if ((o->cond & 0x10) != 0)
        {
            o->cond &= ~0x10u;
            o->xm = 0x400;
        }
        if ((o->cond & 0x20) != 0)
        {
            o->cond &= ~0x20u;
            o->xm = -0x400;
        }
        if ((o->cond & 0x40) != 0)
        {
            o->cond &= ~0x40u;
            o->ym = 0x400;
        }
        if ((o->cond & 0x80) != 0)
        {
            o->cond &= ~0x80u;
            o->ym = -0x400;
        }
        if (o->y > 0x2C000)
            o->cond = 0;
        break;
    default:
        break;
    }
    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];
    if (o->shock / 2 % 2)
    {
        o->rect.top += 24;
        o->rect.bottom += 24;
        o->xm *= 2;
        o->ym = -0x400;
    }
}
