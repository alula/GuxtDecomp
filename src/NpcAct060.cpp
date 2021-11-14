#include <windows.h>

#include "NpcAct060.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (0040D7E0) --------------------------------------------------------
void ActNpc060_PowerupBox(Object *o)
{
    static RECT rc[2] = {
        {240, 112, 256, 128},
        {240, 128, 256, 144},
    };

    int o_x; // [esp+4h] [ebp-8h] BYREF
    int o_y; // [esp+8h] [ebp-4h] BYREF

    o_x = o->x;
    o_y = o->y;
    SubStageXOScroll(&o_x, &o_y);

    if (o->life > 999)
    {
        if (o->state == 0)
        {
            o->state = 10;
            o->flag |= 1u;
        }

        if (++o->count3 > 8)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 1)
            o->count2 = 0;

        o->rect = rc[o->count2];
        if (o_y > 0x2C000)
            o->cond = 0;
    }
    else
    {
        PlaySound(11);
        AddScore(o->score);
        if (o->type2)
            CreateEntity(61, o_x, o_y, o->type2);
        if (o->score)
            SetCaret(0, o_x, o_y, o->score);
        CreateEntity(1, o_x, o_y, 0);
        o->cond = 0;
    }
}

//----- (0040D950) --------------------------------------------------------
void ActNpc061_PowerupStatic(Object *o)
{
    int v1; // [esp+0h] [ebp-3Ch]
    RECT v2[3] = {
        {240, 48, 256, 64},
        {240, 64, 256, 80},
        {240, 80, 256, 96},
    };

    int a1a = o->x;
    int a2 = o->y;
    SubStageXOScroll(&a1a, &a2);
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        o->state = 10;
        CreateEntity(62, 0, 0, (intptr_t)o);
        o->flag |= 2u;
    }
    if (++o->count3 > 2)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 2)
        o->count2 = 0;
LABEL_9:
    if (o->score)
    {
        if (++o->count1 == 16)
        {
            o->count1 = 0;
            --o->score;
        }
    }
    if (a2 > 0x2C000)
        o->cond = 0;
    o->rect = v2[o->count2];
}

//----- (0040DAD0) --------------------------------------------------------
void ActNpc063_BulletWhite(Object *o)
{
    static RECT rc[2] = {
        {112, 160, 128, 176},
        {112, 176, 128, 192},
    };
    int v1; // [esp+0h] [ebp-4h]

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        o->flag |= 0x43u;
        o->xm = 3 * GetCos(o->type2);
        o->ym = 3 * GetSin(o->type2);
        o->state = 10;
    }
    if (++o->count1 > 4 && (o->cond & 0xF0) != 0)
    {
        SetCaret(1, o->x, o->y, 0);
        PlaySound(20);
        o->cond = 0;
        return;
    }

    o->x += o->xm;
    o->y += o->ym;

LABEL_9:
    ++o->count3;
    if (o->x < -0x10000 || o->x > 0x2E000 || o->y < -0x10000 || o->y > 0x38000)
        o->cond = 0;

    o->rect = rc[o->count3 / 2 % 2];
}

//----- (0040DC40) --------------------------------------------------------
void ActNpc064_PowerupSpinner(Object *o)
{
    RECT rc[6] = {
        {48, 112, 72, 136},
        {72, 112, 96, 136},
        {96, 112, 120, 136},
        {48, 136, 72, 160},
        {72, 136, 96, 160},
        {96, 136, 120, 160},
    };

    if (o->life <= 994)
    {
        PlaySound(11);
        CreateEntity(7, o->x, o->y, o->type2);
        CreateEntity(1, o->x, o->y, 0);
        o->cond = 0;
        return;
    }

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = 0x28000;
        o->ym = -0x1800;
        CreateEntity(50, 0, 0, (intptr_t)o);

        o->life = 995;
        o->score = 0;
        PlaySound(26);

    case 10:
        o->ym += 113;
        if (++o->count3 > 2)
        {
            o->count3 = 0;
            ++o->count2;
        }
        if (o->count2 > 2)
            o->count2 = 0;

        if (o->ym <= 0)
            break;

    case 20:
        o->state = 30;
        o->flag |= 0x43u;
        o->damage = 1;

    case 30:
        o->ym += 42;
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
}

//----- (0040DFC0) --------------------------------------------------------
void ActNpc065_ClimberShoot(Object *o)
{
    int v1;  // [esp+0h] [ebp-6Ch]
    int s_x; // [esp+4h] [ebp-68h] BYREF
    int s_y; // [esp+8h] [ebp-64h] BYREF
    RECT rc[6] = {
        {0, 0, 16, 24},
        {16, 0, 32, 24},
        {32, 0, 48, 24},
        {48, 0, 64, 24},
        {64, 0, 80, 24},
        {80, 0, 96, 24},
    };

    s_x = o->x;
    s_y = o->y;

    SubStageXOScroll(&s_x, &s_y);

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 20)
            {
                if (++o->count3 > 1)
                {
                    o->count3 = 0;
                    ++o->count2;
                }
                if (o->count2 > 4)
                    o->count2 = 3;
                o->ym += 64;
                if (++o->count1 == 10)
                {
                    SetCaret(1, o->x, o->y, (intptr_t)o);
                    PlaySound(30);
                }
                if (o->count1 == 26)
                {
                    o->child = GetArktan(s_x - ship.x, s_y - ship.y, 64);
                    CreateEntity(13, s_x, s_y, LOBYTE(o->child));
                    PlaySound(7);
                }
                if (s_y > 0x2C000)
                    o->cond = 0;
            }
            goto LABEL_23;
        }
    }
    else
    {
        o->state = 10;
        o->y = 0x2C000;
        AddStageXOScroll(0, &o->y);
    }
    if (++o->count3 > 1)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 2)
        o->count2 = 0;

    o->ym = -0xC00;
    s_x = o->x;
    s_y = o->y;

    SubStageXOScroll(&s_x, &s_y);

    if (s_y < 0x8000)
    {
        o->state = 20;
        o->ym = -0xE00;
        o->count2 = 3;
        PlaySound(26);
        CreateEntity(1, s_x, s_y, 0);
        o->flag |= 3u;
    }

LABEL_23:
    o->y += o->ym;
    if (o->shock / 2 % 2)
        o->rect = rc[5];
    else
        o->rect = rc[o->count2];
}

//----- (0040E320) --------------------------------------------------------
void ActNpc066_Tri(Object *o)
{
    RECT rc[3] = {
        {0, 24, 32, 48},
        {32, 24, 64, 48},
        {64, 24, 96, 48},
    };
    unsigned char angle; // [esp+37h] [ebp-1h]

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->child = o->x;
        o->y = 0x1E000;
        o->flag &= ~3u;
        o->flag |= 8u;
        if (o->x >= 0xF000)
            o->rot1 = 0x22000;
        else
            o->rot1 = -0x4000;
        o->ym = -0x400;
        goto LABEL_6;
    case 10:
    LABEL_6:
        o->x = o->rot1 + ++o->count1 * (o->child - o->rot1) / 80;
        if (o->count1 >= 80)
        {
            o->count1 = 0;
            o->state = 20;
            o->count2 = 1;
            o->ym = -0x100;
            o->flag |= 3u;
            o->flag &= ~8u;
            SetCaret(1, o->x, o->y - 0x400, (intptr_t)o);
            PlaySound(30);
        }
        break;
    case 20:
        if (++o->count1 == 16)
        {
            angle = GetArktan(o->x - ship.x, o->y - 0x400 - ship.y, 64);
            CreateEntity(13, o->x, o->y - 0x400, angle);
            CreateEntity(13, o->x, o->y - 0x400, angle - 10);
            CreateEntity(13, o->x, o->y - 0x400, angle + 10);
            PlaySound(7);
        }
        if (o->count1 > 66)
            o->state = 30;
        break;
    case 30:
        o->ym -= 32;
        if (o->y < -0x4000)
            o->cond = 0;
        break;
    default:
        break;
    }
    o->y += o->ym;
    if (o->shock / 2 % 2)
        o->rect = rc[2];
    else
        o->rect = rc[o->count2];
}

//----- (0040E670) --------------------------------------------------------
void ActNpc067_GuxtTank(Object *o)
{
    int v1; // ecx
    int v2; // [esp+0h] [ebp-40h]
    int x;  // [esp+4h] [ebp-3Ch] BYREF
    int y;  // [esp+8h] [ebp-38h] BYREF
    RECT rc[3] = {
        {0, 48, 32, 64},
        {32, 48, 64, 64},
        {64, 48, 96, 64},
    };
    unsigned char angle; // [esp+3Fh] [ebp-1h]

    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    v2 = o->state;
    if (v2)
    {
        if (v2 != 10)
            goto LABEL_18;
    }
    else
    {
        o->state = 10;
        o->flag |= 1u;
        if (x >= 0xF000)
        {
            o->x = 0x22000;
            o->xm = -0x200;
        }
        else
        {
            o->x = -0x4000;
            o->xm = 0x200;
        }
        AddStageXOScroll(&o->x, 0);
        o->y += o->type2 << 13;
    }
    if (++o->count1 == 50)
    {
        SetCaret(1, o->x, o->y - 0x400, (intptr_t)o);
        PlaySound(30);
    }
    else if (o->count1 == 66)
    {
        angle = GetArktan(x - ship.x, y - 0x400 - ship.y, 64);
        CreateEntity(13, x, y - 0x400, angle);
        PlaySound(7);
    }

    if (o->count3++ > 0)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 1)
        o->count2 = 0;
    o->x += o->xm;

    if (y > 0x2C000)
        o->cond = 0;

LABEL_18:
    if (o->shock / 2 % 2)
        o->rect = rc[2];
    else
        o->rect = rc[o->count2];

    if (o->xm > 0)
    {
        o->rect.top += 16;
        o->rect.bottom += 16;
    }
}

//----- (0040E910) --------------------------------------------------------
void ActNpc068_MedusaEye(Object *o)
{
    static RECT rcMedusaEye[6] = {
        {144, 96, 160, 112},
        {160, 96, 176, 112},
        {176, 96, 192, 112},
        {192, 96, 208, 112},
        {208, 96, 224, 112},
        {224, 96, 240, 112},
    };

    int x;        // [esp+4h] [ebp-18h] BYREF
    int y;        // [esp+8h] [ebp-14h] BYREF
    RECT rcStage; // [esp+Ch] [ebp-10h] BYREF

    x = o->x;
    y = o->y;
    SubStageXOScroll(&x, &y);
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->count1 = 25 * o->type2;
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
        if (o->count2 == 2)
        {
            o->state = 30;
            o->count1 = 0;
            SetCaret(4, o->x, o->y, (intptr_t)o);
            PlaySound(31);
            o->flag |= 1u;
        }
        break;
    case 30:
        if (++o->count1 > 14 && !(o->count1 % 16))
        {
            CreateEntity(13, x, y, GetArktan(x - ship.x, y - ship.y, 64));
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
    if (o->shock / 2 % 2)
        o->rect = rcMedusaEye[5];
    else
        o->rect = rcMedusaEye[o->count2];

    GetStageRect(&rcStage);

    if (o->y > rcStage.bottom + 0x2000)
        o->cond = 0;
}

//----- (0040EBB0) --------------------------------------------------------
void ActNpc069_GuxtMine(Object *o)
{
    static RECT rcGuxtMine[4] = {
        {96, 0, 112, 24},
        {112, 0, 128, 24},
        {128, 0, 144, 24},
        {144, 0, 160, 24},
    };

    int v1;  // [esp+0h] [ebp-10h]
    int i;   // [esp+4h] [ebp-Ch]
    int s_x; // [esp+8h] [ebp-8h] BYREF
    int s_y; // [esp+Ch] [ebp-4h] BYREF

    if (o->state < 100 && o->life <= 86)
    {
        o->state = 100;
        o->count1 = 0;
        o->shock = 0;
        o->flag &= ~1u;
        SetCaret(4, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }

    v1 = o->state;
    if (!v1)
    {
        o->state = 10;
        o->child = o->life - 24;
        o->flag |= 1u;
    LABEL_13:
        if (o->state == 100)
        {
            o->rect = rcGuxtMine[1];
        }
        else if (o->state == 110)
        {
            o->rect = rcGuxtMine[3];
        }
        else if (o->shock / 2 % 2)
        {
            o->rect = rcGuxtMine[2];
        }
        else
        {
            o->rect = rcGuxtMine[0];
        }

        s_y = o->y;
        SubStageXOScroll(0, &s_y);

        if (s_y >= 0x2C000)
            o->cond = 0;
        return;
    }

    if (v1 != 100)
        goto LABEL_13;

    if (++o->count1 < 14)
        goto LABEL_13;

    s_x = o->x;
    s_y = o->y;

    SubStageXOScroll(&s_x, &s_y);

    for (i = 0; i < 4; ++i)
        CreateEntity(13, s_x, s_y, i * 0x40 + 0x20);

    PlaySound(12);
    CreateEntity(1, s_x, s_y, 0);
    AddScore(o->score);
    SetCaret(0, s_x, s_y, o->score);

    o->state = 110;
}

//----- (0040EE30) --------------------------------------------------------
void ActNpc070_BlendyGen(Object *o)
{
    static RECT rcBlendyGen[3] = {
        {144, 48, 168, 72},
        {120, 48, 144, 72},
        {96, 48, 120, 72},
    };

    if (!o->state)
    {
        o->state = 10;
        o->y = -0xC000;
        o->child = 2;
        o->rot1 = o->life--;
        if ((o->type2 & 0x100) != 0)
            o->count4 = 0x400;
        else
            o->count4 = 0x100;

        o->type2 = (unsigned char)o->type2;

        CreateEntity(71, 0, 0, (intptr_t)o);
        CreateEntity(71, 0, 0, (intptr_t)o);
        CreateEntity(71, 0, 0, (intptr_t)o);
        CreateEntity(71, 0, 0, (intptr_t)o);
    }
    o->y += o->count4;
    if (o->y > 0x34000)
        o->cond = 0;

    o->rect = rcBlendyGen[3 * o->life / o->rot1];

    if (o->shock / 2 % 2)
    {
        o->rect.top += 24;
        o->rect.bottom += 24;
    }
}

//----- (0040EFA0) --------------------------------------------------------
void ActNpc071_Blendy(Object *o)
{
    static RECT rcBlendy[3] = {
        {144, 40, 152, 48},
        {144, 24, 160, 40},
        {160, 24, 176, 40},
    };

    int v1;           // [esp+0h] [ebp-Ch]
    Object *parent;   // [esp+4h] [ebp-8h]
    unsigned char v3; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;
    v1 = o->state;
    if (!v1)
    {
        o->state = 10;
        if (parent->type2 < 8)
        {
            o->child = 32 * parent->type2;
            o->xm = 2;
        }
        else
        {
            o->child = 32 * (parent->type2 - 8);
            o->xm = -2;
        }
        if (parent->child >= 5)
        {
            o->rot1 = 40;
            o->count2 = 1;
            o->flag |= 0xAu;
            o->xoff = 0x2000;
            o->yoff = 0x2000;
        }
        else
        {
            o->rot1 = 8 * parent->child;
        }
        o->count4 = parent->num;
        ++parent->child;
        goto LABEL_12;
    }
    if (v1 == 10)
    {
    LABEL_12:
        if (o->count4 == parent->num && parent->cond)
        {
            o->child += o->xm;
            ++o->count3;
            o->child %= 256;
            v3 = o->child;
            o->x = parent->x + o->rot1 * GetCos(v3);
            o->y = parent->y + o->rot1 * GetSin(v3);
            goto LABEL_23;
        }
        if (o->y > 0x2A000)
        {
            o->cond = 0;
            goto LABEL_23;
        }
        o->state = 100;
        o->count1 = 4 * o->rot1 / 4 - 16;
        o->flag &= ~2u;
        o->count3 = 0;
        goto LABEL_18;
    }
    if (v1 != 100)
    {
    LABEL_23:
        if (o->count2)
        {
            o->rect = rcBlendy[o->count3++ / 4 % 2 + 1];
        }
        else
        {
            o->rect = rcBlendy[0]; // rcBlendy[0]
        }
        return;
    }
LABEL_18:
    if (--o->count1 >= 1)
        goto LABEL_23;
    if (o->rot1 == 40)
    {
        PlaySound(13);
        CreateEntity(1, o->x, o->y, 0);
    }
    else
    {
        PlaySound(15);
        SetCaret(2, o->x, o->y, 0);
    }
    o->cond = 0;
}

//----- (0040F290) --------------------------------------------------------
void ActNpc072_Cycloid2(Object *o)
{
    static RECT rcCycloid[8] = {
        {112, 80, 128, 96},
        {128, 80, 144, 96},
        {144, 80, 160, 96},
        {160, 80, 176, 96},
        {176, 80, 192, 96},
        {192, 80, 208, 96},
        {208, 80, 224, 96},
        {224, 80, 240, 96},
    };

    int v1;              // [esp+0h] [ebp-8h]
    unsigned char angle; // [esp+6h] [ebp-2h]
    unsigned char v3;    // [esp+7h] [ebp-1h]
    unsigned char v4;    // [esp+7h] [ebp-1h]

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 != 20)
                goto LABEL_14;
            goto LABEL_10;
        }
    }
    else
    {
        o->state = 10;
        o->child = 64;
        o->y = -0x2000;
        o->flag |= 2u;
        PlaySound(26);
    }
    if (o->y < 0x6000)
        goto LABEL_14;
    o->state = 20;
    if (o->x >= 0xF000)
        o->rot1 = 8;
    else
        o->rot1 = -8;
LABEL_10:
    o->child += o->rot1;
    o->child = (unsigned char)(o->child & 0xff);
    if (++o->count1 > 50)
    {
        v3 = o->child;
        angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
        if (v3 <= angle + 8 && v3 > angle - 8)
        {
            o->state = 30;
            o->child = angle;
        }
    }
LABEL_14:
    v4 = o->child;
    o->x += 3 * GetCos(v4);
    o->y += 3 * GetSin(v4);

    // this is probably a bug in original code
    if (o->state == 30 && (o->x < -0x2000 || o->x > 0x20000 || o->x < -0x2000 || o->x > 0x20000))
    {
        o->cond = 0;
    }
    else
    {
        o->count2 = (((unsigned char)(o->child & 0xff) + 16) / 32 + 2) % 8;
        o->rect = rcCycloid[o->count2];

        if (o->life != 5)
        {
            if (o->shock / 2 % 2)
            {
                o->rect.top -= 16;
                o->rect.bottom -= 16;
            }
            else
            {
                o->rect.top -= 32;
                o->rect.bottom -= 32;
            }
        }
    }
}

//----- (0040F510) --------------------------------------------------------
void ActNpc073_Cycloid2Gen(Object *o)
{
    if (++o->count1 % 8 == 1)
        CreateEntity(72, o->x, o->y, 0);
    if (o->count1 > 24)
        o->cond = 0;
}

//----- (0040F570) --------------------------------------------------------
void ActNpc074_PowerupHidden(Object *o)
{
    int s_x; // [esp+4h] [ebp-8h] BYREF
    int s_y; // [esp+8h] [ebp-4h] BYREF

    s_x = o->x;
    s_y = o->y;
    SubStageXOScroll(&s_x, &s_y);

    if (o->life > 952)
    {
        if (!o->state)
        {
            o->state = 10;
            o->flag |= 1u;
        }
        if (s_y > 0x2C000)
            o->cond = 0;
    }
    else
    {
        PlaySound(11);
        AddScore(o->score);

        if (o->type2)
            CreateEntity(61, s_x, s_y, o->type2);
        if (o->score)
            SetCaret(0, s_x, s_y, o->score);

        CreateEntity(1, s_x, s_y, 0);
        o->cond = 0;
    }
}

//----- (0040F660) --------------------------------------------------------
void ActNpc075_PowerupAsteroid(Object *o)
{
    static RECT rc[2] = {
        {80, 160, 112, 192},
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
        CreateEntity(7, o->x, o->y, o->type2);
        o->cond = 0;
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
    {
        o->rect = rc[1];
    }
    else
    {
        o->rect = rc[0];
    }
}

//----- (0040F830) --------------------------------------------------------
void ActNpc076_Boss4(Object *o)
{

    static RECT rcBoss4 = {0, 80, 48, 128};
    int v3; // [esp-8h] [ebp-14h]
    int v4; // [esp+4h] [ebp-8h]
    int i;  // [esp+8h] [ebp-4h]

    if ((o->state == 112 || o->state == 122) && (o->flag & 8) != 0 && o->life <= 680 && o->x == 61440)
    {
        o->count1 = 0;
        o->state = 200;
    }
    if (o->state == 210 && (o->flag & 8) != 0 && o->life <= 520)
    {
        o->state = 300;
        o->count1 = 0;
        o->xm = 0;
        o->ym = 0;
        PlayLoopSound(32);
    }
    v4 = o->state;
    if (v4 > 112)
    {
        switch (v4)
        {
        case 113:
            goto LABEL_78;
        case 120:
            o->state = 120;
            if (o->x >= 0x17000)
                goto LABEL_86;
            o->x += 0x200;
            goto LABEL_139;
        case 121:
        LABEL_86:
            o->state = 121;
            if (o->y <= 0x7000)
                goto LABEL_88;
            o->y -= 0x400;
            goto LABEL_139;
        case 122:
        LABEL_88:
            o->state = 122;
            if (o->x <= 0x7000)
                goto LABEL_90;
            o->x -= 0x200;
            goto LABEL_139;
        case 123:
        LABEL_90:
            o->state = 123;
            if (o->y >= 0x21000)
            {
                o->state = 120;
                if (o->life > 680 && (o->flag & 8) != 0)
                {
                    PlaySound(38);
                    o->flag &= ~8u;
                    o->flag |= 1u;
                }
            }
            else
            {
                o->y += 0x400;
            }
            goto LABEL_139;
        case 200:
            o->rot1 -= 4;
            if (o->rot1 < 0)
                o->rot1 += 0x100;
            if (++o->count1 > 200)
            {
                o->count1 = 0;
                o->state = 210;
                PlaySound(38);
                o->flag &= ~8u;
                o->flag |= 1u;
                if (o->x >= ship.x)
                    o->xm = 0x400;
                else
                    o->xm = -0x400;
                o->ym = 0;
            }
            goto LABEL_139;
        case 210:
            o->rot1 += 8;
            if (o->rot1 >= 0x100)
                o->rot1 -= 256;
            if (o->x < ship.x)
                o->xm += 16;
            if (o->x > ship.x)
                o->xm -= 16;
            if (o->xm > 0x400)
                o->xm = 0x400;
            if (o->xm < -0x400)
                o->xm = -0x400;
            o->x += o->xm;
            if (o->y < ship.y)
                o->ym += 4;
            if (o->y > ship.y)
                o->ym -= 4;
            if (o->ym > 0x100)
                o->ym = 0x100;
            if (o->ym < -0x100)
                o->ym = -0x100;
            o->y += o->ym;
            goto LABEL_139;
        case 300:
            if (--o->rot1 < 0)
                o->rot1 += 0x100;
            ++o->count1;
            if (o->x > 0x14000)
                o->x -= 0x200;
            if (o->x < 0xA000)
                o->x += 0x200;
            if (o->count1 < 50)
                goto LABEL_139;
            PlaySound(12);
            SetShipInvincibility();
            o->state = 310;
            o->count4 = 0;
            goto LABEL_131;
        case 310:
        LABEL_131:
            o->rot1 -= 2;
            if (o->rot1 < 0)
                o->rot1 += 0x100;
            if (++o->count4 < 200)
                goto LABEL_139;
            o->count4 = 0;
            o->state = 320;
            o->ym = 0x200;
        LABEL_135:
            o->rot1 -= 8;
            if (o->rot1 < 0)
                o->rot1 += 0x100;

            o->ym -= 0x20;
            o->y += o->ym;

            if (o->count4++ != 100)
                goto LABEL_139;

            CheckStageClear(4);
            StopLoopSound(32);
            break;
        case 320:
            goto LABEL_135;
        default:
            goto LABEL_139;
        }
    }
    else
    {
        if (v4 == 112)
        {
        LABEL_76:
            o->state = 112;
            if (o->x >= 0x17000)
            {
            LABEL_78:
                o->state = 113;
                if (o->y >= 0x21000)
                {
                    o->state = 110;
                    if (o->life > 680 && (o->flag & 8) != 0)
                    {
                        PlaySound(38);
                        o->flag &= ~8u;
                        o->flag |= 1u;
                    }
                }
                else
                {
                    o->y += 0x400;
                }
            }
            else
            {
                o->x += 0x200;
            }
        }
        else
        {
            switch (v4)
            {
            case 0:
                o->state = 10;
                o->y = -0x8000;
                o->ym = 0x100;
                o->flag |= 0xAu;
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(78, 0, -0x4000, (intptr_t)o);
                CreateEntity(77, 0, -0x4000, (intptr_t)o);
                CreateEntity(77, 0, -0x4000, (intptr_t)o);
                CreateEntity(77, 0, -0x4000, (intptr_t)o);
                CreateEntity(77, 0, -0x4000, (intptr_t)o);
                CreateEntity(82, 0, -0x4000, (intptr_t)o);
                for (i = 0; i < 20; ++i)
                    CreateEntity(80, 0, -0x4000, (intptr_t)o);
                o->count3 = 48;
                goto LABEL_19;
            case 10:
            LABEL_19:
                if (o->y > 24576)
                    o->ym -= 4;
                o->y += o->ym;
                if (!o->ym)
                {
                    o->state = 11;
                    CreateEntity(79, 0, -0x4000, (intptr_t)o);
                    CreateEntity(79, 0, -0x4000, (intptr_t)o);
                    CreateEntity(79, 0, -0x4000, (intptr_t)o);
                    CreateEntity(79, 0, -0x4000, (intptr_t)o);
                }
                break;
            case 11:
                o->rot1 -= 2;
                if (o->rot1 < 0)
                    o->rot1 += 256;
                if (o->count3 >= 256)
                    o->state = 12;
                else
                    ++o->count3;
                break;
            case 12:
                o->rot1 -= 4;
                if (o->rot1 < 0)
                    o->rot1 += 256;
                if (++o->count1 > 100)
                {
                    o->count1 = 0;
                    o->state = 20;
                    o->flag &= ~8u;
                    o->flag |= 1u;
                    PlaySound(38);
                }
                break;
            case 20:
                o->rot1 -= 2;
                if (o->rot1 < 0)
                    o->rot1 += 256;
                if (o->y >= 0x1F000)
                {
                    if (o->ym)
                        o->ym -= 4;
                    else
                        o->state = 21;
                }
                else if (o->ym < 256)
                {
                    o->ym += 4;
                }
                o->y += o->ym;
                break;
            case 21:
                o->rot1 -= 2;
                if (o->rot1 < 0)
                    o->rot1 += 256;
                if (o->count3 <= 96)
                {
                    if ((o->flag & 8) != 0)
                    {
                        if (ship.x >= 0xF000)
                            o->state = 120;
                        else
                            o->state = 110;
                    }
                    else
                    {
                        PlaySound(31);
                        SetCaret(4, o->x, o->y, (intptr_t)o);
                        o->state = 30;
                    }
                }
                else
                {
                    --o->count3;
                }
                break;
            case 30:
                if (--o->rot1 < 0)
                    o->rot1 += 256;
                if (o->y <= 0x9000)
                {
                    if (o->ym)
                    {
                        o->ym += 4;
                    }
                    else if ((o->flag & 8) != 0)
                    {
                        if (ship.x <= 0xF000)
                            o->state = 122;
                        else
                            o->state = 112;
                    }
                    else
                    {
                        o->state = 31;
                    }
                }
                else if (o->ym > -0x100)
                {
                    o->ym -= 4;
                }
                o->y += o->ym;
                break;
            case 31:
                o->rot1 -= 2;
                if (o->rot1 < 0)
                    o->rot1 += 256;
                if (o->count3 >= 256)
                    o->state = 20;
                else
                    ++o->count3;
                break;
            case 110:
                o->state = 110;
                if (o->x <= 0x7000)
                    goto LABEL_74;
                o->x -= 512;
                break;
            case 111:
            LABEL_74:
                o->state = 111;
                if (o->y <= 0x7000)
                    goto LABEL_76;
                o->y -= 1024;
                break;
            default:
                break;
            }
        }
    LABEL_139:
        if (o->state > 300 && ++o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            CreateEntity(1, o->x + ((GetRandom(48) - 24) << 10), o->y + ((GetRandom(48) - 32) << 10), 0);
        }

        o->rect = rcBoss4;

        switch (o->state)
        {
        case 110:
            if (--o->rot1 < 0)
                o->rot1 += 256;
            break;
        case 111:
            o->rot1 -= 2;
            if (o->rot1 < 0)
                o->rot1 += 256;
            break;
        case 112:
            if (--o->rot1 < 0)
                o->rot1 += 256;
            break;
        case 113:
            o->rot1 -= 2;
            if (o->rot1 < 0)
                o->rot1 += 256;
            break;
        case 120:
            if (++o->rot1 >= 256)
                o->rot1 -= 256;
            break;
        case 121:
            o->rot1 += 2;
            if (o->rot1 >= 256)
                o->rot1 -= 256;
            break;
        case 122:
            if (++o->rot1 >= 256)
                o->rot1 -= 256;
            break;
        case 123:
            o->rot1 += 2;
            if (o->rot1 >= 256)
                o->rot1 -= 256;
            break;
        default:
            break;
        }

        if (o->shock / 2 % 2)
        {
            o->rect.left += 48;
            o->rect.right += 48;
        }
    }
}

//----- (00410810) --------------------------------------------------------
void ActNpc077(Object *o)
{
    static RECT rc[6] = {
        {96, 96, 112, 112},
        {112, 96, 128, 112},
        {128, 96, 144, 112},
        {144, 96, 160, 112},
        {160, 96, 176, 112},
        {0, 0, 0, 0},
    };
    Object *parent = (Object *)o->type2;

    if (o->state >= 100)
    {
        if (!(o->count1++ % 6))
            CreateEntity(29, o->x, o->y, 0);
    }
    else
    {
        if (parent->life < 1000 - 160 * (o->child + 1))
            o->state = 30;
        switch (o->state)
        {
        case 0:
            o->state = 10;
            o->child = parent->child++;
            if (parent->child == 4)
                parent->child = 0;
            goto LABEL_7;
        case 10:
        LABEL_7:
            if ((parent->flag & 1) == 0)
                break;
            o->state = 11;
        LABEL_9:
            if (o->count2 >= 3)
            {
                o->state = 20;
            }
            else if (++o->count3 > 1)
            {
                o->count3 = 0;
                ++o->count2;
            }
            break;
        case 11:
            goto LABEL_9;
        case 20:
            if ((parent->flag & 1) != 0)
                break;
            o->state = 21;
        LABEL_16:
            if (o->count2 <= 0)
            {
                o->state = 10;
            }
            else if (++o->count3 > 1)
            {
                o->count3 = 0;
                --o->count2;
            }
            break;
        case 21:
            goto LABEL_16;
        case 30:
            CreateEntity(1, o->x, o->y, 0);
            PlaySound(11);
            o->state = 100;
            parent->flag &= ~1u;
            parent->flag |= 8u;
            PlaySound(38);
            break;
        default:
            break;
        }
    }
    switch (o->child)
    {
    case 0:
        o->x = parent->x - 0x3800;
        o->y = parent->y + 0x2800;
        break;
    case 1:
        o->x = parent->x + 0x3C00;
        o->y = parent->y + 0x2800;
        break;
    case 2:
        o->x = parent->x - 0x1400;
        o->y = parent->y + 0x4000;
        break;
    case 3:
        o->x = parent->x + 0x1800;
        o->y = parent->y + 0x4000;
        break;
    default:
        break;
    }
    if (o->state == 100)
    {
        o->rect = rc[5];
    }
    else if (parent->shock / 2 % 2)
    {
        o->rect = rc[4];
    }
    else
    {
        o->rect = rc[o->count2];
    }
}

//----- (00410BB0) --------------------------------------------------------
void ActNpc078(Object *o)
{
    static RECT rc[3] = {
        {152, 40, 160, 48},
        {160, 40, 168, 48},
        {168, 40, 176, 48},
    };

    int v1;           // [esp+0h] [ebp-Ch]
    Object *parent;   // [esp+4h] [ebp-8h]
    unsigned char v3; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
        {
            if (v1 == 20 && o->life < 968)
            {
                o->state = 30;
                o->shock = 0;
                o->count2 = 1;
                o->flag &= ~3u;
                SetCaret(1, o->x, o->y, (intptr_t)o);
                PlaySound(11);
            }
            goto LABEL_13;
        }
    }
    else
    {
        o->state = 10;
        o->child = 32 * parent->child++;
        if (parent->child == 8)
            parent->child = 0;
        o->flag |= 0xAu;
    }
    if (parent->state == 12)
    {
        o->state = 20;
        o->flag &= ~8u;
        o->flag |= 1u;
    }

LABEL_13:
    o->child += 4;
    o->child %= 256;
    v3 = o->child;
    o->x = parent->x + 24 * GetCos(v3);
    o->y = parent->y + 24 * GetSin(v3);
    if (o->shock / 2 % 2)
        o->rect = rc[2];
    else
        o->rect = rc[o->count2];
}

//----- (00410DA0) --------------------------------------------------------
void ActNpc079(Object *o)
{
    static RECT rc[2] = {
        {144, 24, 160, 40},
        {160, 24, 176, 40},
    };

    int v1;           // [esp+0h] [ebp-Ch]
    Object *parent;   // [esp+4h] [ebp-8h]
    unsigned char v3; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_8;
    }
    else
    {
        o->state = 10;
        o->child = parent->child++;
        if (parent->child == 4)
            parent->child = 0;
        o->flag |= 0xAu;
    }

    v3 = (unsigned char)(o->child * 0x40 + parent->rot1);
    o->x = parent->x + parent->count3 * GetCos(v3) / 4;
    o->y = parent->y + parent->count3 * GetSin(v3) / 4;

LABEL_8:
    o->rect = rc[o->count3++ / 2 % 2];
}