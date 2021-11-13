#include <windows.h>

#include "NpcAct000.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "Ship.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00403960) --------------------------------------------------------
void ActNpc000(Object *a1)
{
    RECT v1; // [esp+10h] [ebp-10h] BYREF

    a1->rect.left = 0;
    a1->rect.top = 0;
    a1->rect.right = 16;
    a1->rect.bottom = 16;
    if (a1->shock / 2 % 2)
    {
        a1->rect.top += 16;
        a1->rect.bottom += 16;
    }
    GetStageRect(&v1);
    if (a1->y > v1.bottom + 0x2000)
        a1->cond = 0;
}

//----- (00403A10) --------------------------------------------------------
void ActNpc001_Explode(Object *a1)
{
    int v1;     // ecx
    int v2;     // ecx
    RECT rc[7]; // [esp+0h] [ebp-70h]

    rc[0].left = 0;
    rc[0].top = 0;
    rc[0].right = 32;
    rc[0].bottom = 32;
    rc[1].left = 32;
    rc[1].top = 0;
    rc[1].right = 64;
    rc[1].bottom = 32;
    rc[2].left = 64;
    rc[2].top = 0;
    rc[2].right = 96;
    rc[2].bottom = 32;
    rc[3].left = 96;
    rc[3].top = 0;
    rc[3].right = 128;
    rc[3].bottom = 32;
    rc[4].left = 128;
    rc[4].top = 0;
    rc[4].right = 160;
    rc[4].bottom = 32;
    rc[5].left = 160;
    rc[5].top = 0;
    rc[5].right = 192;
    rc[5].bottom = 32;
    rc[6].left = 192;
    rc[6].top = 0;
    rc[6].right = 224;
    rc[6].bottom = 32;
    v1 = a1->count1;
    a1->count1 = v1 + 1;
    if (v1 >= 4)
        v2 = a1->y + 0x1000;
    else
        v2 = a1->y + 0x400;
    a1->y = v2;
    if (++a1->count3 > 2)
    {
        a1->count3 = 0;
        ++a1->count2;
    }
    if (a1->count2 <= 6)
        a1->rect = rc[a1->count2];
    else
        a1->cond = 0;
}

//----- (00403B90) --------------------------------------------------------
void ActNpc002_CloudL(Object *a1)
{
    a1->y += 0x800;
    if (a1->y > 0x2C000)
        a1->cond = 0;
    a1->rect.left = 0;
    a1->rect.top = 0;
    a1->rect.right = 48;
    a1->rect.bottom = 24;
}

//----- (00403C00) --------------------------------------------------------
void ActNpc003_CloudS(Object *a1)
{
    a1->y += 0x200;
    if (a1->y > 0x2C000)
        a1->cond = 0;
    a1->rect.left = 0;
    a1->rect.top = 24;
    a1->rect.right = 16;
    a1->rect.bottom = 32;
}

//----- (00403C70) --------------------------------------------------------
void ActNpc004_Puff(Object *a1)
{
    RECT v1[5]; // [esp+0h] [ebp-50h]

    v1[0].left = 0;
    v1[0].top = 56;
    v1[0].right = 8;
    v1[0].bottom = 64;
    v1[1].left = 8;
    v1[1].top = 56;
    v1[1].right = 16;
    v1[1].bottom = 64;
    v1[2].left = 16;
    v1[2].top = 56;
    v1[2].right = 24;
    v1[2].bottom = 64;
    v1[3].left = 24;
    v1[3].top = 56;
    v1[3].right = 32;
    v1[3].bottom = 64;
    v1[4].left = 32;
    v1[4].top = 56;
    v1[4].right = 40;
    v1[4].bottom = 64;
    a1->y += 0x2000;
    if (a1->y > 0x2C000)
        a1->cond = 0;
    if (++a1->count3 > 1)
    {
        a1->count3 = 0;
        ++a1->count2;
    }
    if (a1->count2 <= 4)
        a1->rect = v1[a1->count2];
    else
        a1->cond = 0;
}

//----- (00403DA0) --------------------------------------------------------
void ActNpc005_Hanger(Object *o)
{
    int v1;     // ecx
    RECT v2[6]; // [esp+4h] [ebp-60h]

    v2[0].left = 0;
    v2[0].top = 0;
    v2[0].right = 24;
    v2[0].bottom = 24;
    v2[1].left = 24;
    v2[1].top = 0;
    v2[1].right = 48;
    v2[1].bottom = 24;
    v2[2].left = 48;
    v2[2].top = 0;
    v2[2].right = 72;
    v2[2].bottom = 24;
    v2[3].left = 72;
    v2[3].top = 0;
    v2[3].right = 96;
    v2[3].bottom = 24;
    v2[4].left = 96;
    v2[4].top = 0;
    v2[4].right = 120;
    v2[4].bottom = 24;
    v2[5].left = 120;
    v2[5].top = 0;
    v2[5].right = 144;
    v2[5].bottom = 24;
    if (o->life > 994)
    {
        switch (o->state)
        {
        case 0:
            o->state = 10;
            o->y = 0x28000;
            o->ym = -0x1800;
            PlaySound(26);
            goto LABEL_5;
        case 10:
        LABEL_5:
            o->ym += 0x71;
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
            if (ship.x >= o->x)
                v1 = o->xm + 0x20;
            else
                v1 = o->xm - 0x20;
            o->xm = v1;
            if (o->xm < -0x400)
                o->xm = -0x400;
            if (o->xm > 0x400)
                o->xm = 0x400;
            o->ym += 0x40;
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
        o->rect = v2[o->count2];
        if (o->life <= 997)
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
            o->xm *= 2;
            o->ym = -0x400;
        }
    }
    else
    {
        PlaySound(11);
        AddScore(o->score);
        CreateEntity(1, o->x, o->y, 0);
        SetCaret(0, o->x, o->y, o->score);
        o->cond = 0;
    }
}

//----- (00404200) --------------------------------------------------------
void ActNpc006_CloudGen(Object *a1)
{
    int x; // [esp+4h] [ebp-4h]

    if (++a1->count1 > 15)
    {
        a1->count1 = 0;
        if (++a1->state > 9)
            a1->state = 0;
    }
    if (!a1->count1)
    {
        x = GetRandom(120) << 10;
        switch (a1->state)
        {
        case 0:
        case 1:
        case 3:
        case 7:
            CreateEntity(2, x, -0x4000, 0);
            break;
        case 2:
        case 4:
            CreateEntity(3, x, -0x4000, 0);
            break;
        default:
            return;
        }
    }
}

//----- (00404340) --------------------------------------------------------
void ActNpc007_Powerup(Object *o)
{
    int v1;     // [esp+0h] [ebp-34h]
    RECT rc[3]; // [esp+4h] [ebp-30h]

    rc[0].left = 240;
    rc[0].top = 48;
    rc[0].right = 256;
    rc[0].bottom = 64;
    rc[1].left = 240;
    rc[1].top = 64;
    rc[1].right = 256;
    rc[1].bottom = 80;
    rc[2].left = 240;
    rc[2].top = 80;
    rc[2].right = 256;
    rc[2].bottom = 96;
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_11;
    }
    else
    {
        o->state = 10;
        o->ym = -0x200;
        PlaySound(26);
        CreateEntity(50, 0, 0, (intptr_t)o);
    }
    o->ym += 0x24;
    if (++o->count3 > 2)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 2)
        o->count2 = 0;
    if (o->y > 0x2C000)
        o->cond = 0;
LABEL_11:
    if (o->score)
    {
        if (++o->count1 == 16)
        {
            o->count1 = 0;
            --o->score;
        }
    }
    o->x += o->xm;
    o->y += o->ym;
    o->rect = rc[o->count2];
}

//----- (004044E0) --------------------------------------------------------
void ActNpc008_Climber(Object *o)
{
    RECT rc[3]; // [esp+4h] [ebp-30h]

    rc[0].left = 0;
    rc[0].top = 48;
    rc[0].right = 16;
    rc[0].bottom = 64;
    rc[1].left = 16;
    rc[1].top = 48;
    rc[1].right = 32;
    rc[1].bottom = 64;
    rc[2].left = 32;
    rc[2].top = 48;
    rc[2].right = 48;
    rc[2].bottom = 64;
    switch (o->state)
    {
    case 0:
        o->y = 0x2C000;
        o->ym = -0x400;
        PlaySound(26);
        o->state = 10;
        o->count2 = 2;
        goto LABEL_3;
    case 10:
    LABEL_3:
        o->ym += 32;
        if (o->ym <= -0x200)
            goto LABEL_9;
        o->state = 20;
        o->count2 = 0;
    LABEL_5:
        o->ym += 32;
        if (o->ym > 0x200)
        {
            o->state = 30;
            o->count2 = 1;
        LABEL_7:
            o->ym += 32;
            if (o->ym > 0x400)
            {
                o->state = 10;
                o->ym = -0x800;
                o->count2 = 2;
            }
        }
    LABEL_9:
        o->x += o->xm;
        o->y += o->ym;
        o->rect = rc[o->count2];
        if (o->shock / 2 % 2)
        {
            o->rect.top += 16;
            o->rect.bottom += 16;
            o->ym = -0x400;
        }
        if (o->y < -0x4000)
            o->cond = 0;
        return;
    case 20:
        goto LABEL_5;
    case 30:
        goto LABEL_7;
    default:
        goto LABEL_9;
    }
}

//----- (00404710) --------------------------------------------------------
void ActNpc009_Kagome(Object *o)
{
    unsigned char v1; // [esp+17h] [ebp-1h]

    switch (o->state)
    {
    case 0:
        if ((KagomeCount & 1) != 0)
            o->life = 8;
        else
            o->life = 4;
        o->child = 16 * (KagomeCount++ & 0xF);
        o->rot1 = 0x800;
        o->state = 10;
        goto LABEL_6;
    case 10:
    LABEL_6:
        if (o->type2)
            o->rot1 -= 16;
        else
            o->rot1 -= 8;
        if (o->rot1 > 0x2A0)
            goto LABEL_15;
        o->state = 20;
        o->count1 = 0;
    LABEL_11:
        if (++o->count1 >= 150)
        {
            o->state = 30;
        LABEL_13:
            o->rot1 += 8;
            if (o->rot1 >= 0xA00)
                o->cond = 0;
        }
    LABEL_15:
        o->child += 2;
        o->child %= 256;
        v1 = o->child;
        o->x = o->rot1 * GetCos(v1) / 16 + 0xF000;
        o->y = o->rot1 * GetSin(v1) / 16 + 0x1E000;
        o->rect.left = 48;
        o->rect.top = 48;
        o->rect.right = 64;
        o->rect.bottom = 64;
        o->rect.left += 16 * ((o->life - 2) / 2);
        o->rect.right += 16 * ((o->life - 2) / 2);
        if (o->shock / 2 % 2)
        {
            o->rect.top += 16;
            o->rect.bottom += 16;
        }
        return;
    case 20:
        goto LABEL_11;
    case 30:
        goto LABEL_13;
    default:
        goto LABEL_15;
    }
}

//----- (004049A0) --------------------------------------------------------
void ActNpc011_Wing(Object *o)
{
    int v1;           // [esp+0h] [ebp-1Ch]
    int state;        // [esp+4h] [ebp-18h]
    unsigned char v3; // [esp+1Bh] [ebp-1h]

    state = o->state;
    if (state)
    {
        if (state != 10)
            goto LABEL_24;
    }
    else
    {
        CreateEntity(12, -1, 0, (intptr_t)o);
        CreateEntity(12, 1, 0, (intptr_t)o);
        o->state = 10;
        o->y = 0x2A000;
        if (o->type2)
            o->ym = -0x200;
        else
            o->ym = -0x100;
        o->xm = 0;
    }
    if (++o->count1 == 143)
    {
        SetCaret(1, o->x, o->y, (intptr_t)o);
        PlaySound(30);
    }
    if (o->count1 > 162 && !(o->count1 % 6))
    {
        v1 = ++o->child % 3;
        if (v1)
        {
            if (v1 == 1)
            {
                v3 = 62;
            }
            else if (v1 == 2)
            {
                v3 = 66;
            }
        }
        else
        {
            v3 = 64;
        }
        if (ship.y < o->y)
            v3 += 0x80;
        CreateEntity(13, o->x, o->y, v3);
        PlaySound(7);
    }
    if (o->count1 > 187)
        o->count1 = 0;

LABEL_24:
    if ((o->count1 % 6) == 0)
        CreateEntity(29, o->x, o->y + 0x2000, 0);

    o->x += o->xm;
    o->y += o->ym;
    o->rect.left = 0;
    o->rect.top = 32;
    o->rect.right = 40;
    o->rect.bottom = 48;
    if (o->shock / 2 % 2)
    {
        o->rect.top += 16;
        o->rect.bottom += 16;
    }
    if (o->y < -0x2000)
        o->cond = 0;
}

//----- (00404C10) --------------------------------------------------------
void ActNpc012_WingCorpse(Object *o)
{
    int v1; // [esp+0h] [ebp-4h]

    v1 = o->state;
    if (!v1)
    {
        o->child = o->x;
        o->state = 10;
        goto LABEL_5;
    }
    if (v1 == 10)
    {
    LABEL_5:
        if (o->child >= 0)
            o->x = ((Object *)o->type2)->x + 0x2C00;
        else
            o->x = ((Object *)o->type2)->x - 0x2C00;
        o->y = ((Object *)o->type2)->y;
    }

    if ((((Object *)o->type2)->cond & 1) == 0 || ((Object *)o->type2)->type != 11)
        o->cond = 0;
}

//----- (00404CB0) --------------------------------------------------------
void ActNpc013_Bullet(Object *a1)
{
    int v1;     // [esp+0h] [ebp-44h]
    RECT v2[4]; // [esp+4h] [ebp-40h]

    v2[0].left = 144;
    v2[0].top = 32;
    v2[0].right = 160;
    v2[0].bottom = 48;
    v2[1].left = 160;
    v2[1].top = 32;
    v2[1].right = 176;
    v2[1].bottom = 48;
    v2[2].left = 176;
    v2[2].top = 32;
    v2[2].right = 192;
    v2[2].bottom = 48;
    v2[3].left = 192;
    v2[3].top = 32;
    v2[3].right = 208;
    v2[3].bottom = 48;
    v1 = a1->state;
    if (!v1)
    {
        a1->xm = 2 * GetCos(a1->type2);
        a1->ym = 2 * GetSin(a1->type2);
        a1->state = 10;
        goto LABEL_5;
    }
    if (v1 == 10)
    {
    LABEL_5:
        a1->x += a1->xm;
        a1->y += a1->ym;
    }
    if (++a1->count3 > 1)
    {
        a1->count3 = 0;
        ++a1->count2;
    }
    if (a1->count2 > 3)
        a1->count2 = 0;
    if (a1->x < (signed int)-0x10000u || a1->x > 0x2E000 || a1->y < (signed int)-0x10000u || a1->y > 0x38000)
        a1->cond = 0;

    a1->rect = v2[a1->count2];
}

//----- (00404E50) --------------------------------------------------------
void ActNpc014_BulletSlow(Object *o)
{
    int v1;     // [esp+0h] [ebp-44h]
    RECT v2[4]; // [esp+4h] [ebp-40h]

    v2[0].left = 144;
    v2[0].top = 32;
    v2[0].right = 160;
    v2[0].bottom = 48;
    v2[1].left = 160;
    v2[1].top = 32;
    v2[1].right = 176;
    v2[1].bottom = 48;
    v2[2].left = 176;
    v2[2].top = 32;
    v2[2].right = 192;
    v2[2].bottom = 48;
    v2[3].left = 192;
    v2[3].top = 32;
    v2[3].right = 208;
    v2[3].bottom = 48;
    v1 = o->state;
    if (!v1)
    {
        o->xm = GetCos(o->type2);
        o->ym = GetSin(o->type2);
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
    if (o->x < -65536 || o->x > 188416 || o->y < -65536 || o->y > 229376)
        o->cond = 0;
    o->rect = v2[o->count2];
}

//----- (00404FE0) --------------------------------------------------------
void ActNpc010_Unused_(Object *o)
{
    static RECT Npc10Rect[5] = {
        {192, 112, 208, 128},
        {208, 112, 224, 128},
        {224, 112, 240, 128},
        {192, 128, 208, 144},
        {208, 128, 224, 144}};

    if (!o->state)
    {
        o->flag |= 0x10u;
        o->state = 10;
    }
    if (++o->count3 > 2)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 < 5)
        o->rect = Npc10Rect[o->count2];
    else
        o->cond = 0;
}

//----- (00405090) --------------------------------------------------------
void ActNpc015_Boss1(Object *o)
{
    int v1;              // eax
    int v2;              // eax
    int v3;              // ecx
    unsigned __int16 v4; // ax
    unsigned __int16 v5; // ax
    int v6;              // [esp-8h] [ebp-24h]
    int v7;              // [esp-8h] [ebp-24h]
    int i;               // [esp+4h] [ebp-18h]
    unsigned __int8 v9;  // [esp+1Bh] [ebp-1h]

    if (o->state < 100 && o->life < 872)
    {
        o->state = 100;
        SetShipInvincibility();
        o->flag &= ~1u;
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y = 0x30000;
        o->ym = -0x100u;
        o->xm = 0;
        CreateEntity(16, o->x - 0x5C00, o->y + 0x800, (int)o);
        CreateEntity(16, o->x + 0x5C00, o->y + 0x800, (int)o);
        CreateEntity(16, o->x - 0x9C00, o->y - 0x400, (int)o);
        CreateEntity(16, o->x + 0x9C00, o->y - 0x400, (int)o);
        CreateEntity(17, 0, 0, (int)o);
        return;
    case 10:
        if (o->y > 0xF000)
            goto LABEL_42;
        o->state = 20;
        goto LABEL_8;
    case 20:
    LABEL_8:
        if (++o->ym < 0)
            goto LABEL_42;
        o->ym = 0;
        o->state = 30;
        o->count1 = -10;
        PlaySound(38);
    LABEL_10:
        if (++o->count1 >= 50)
        {
            o->state = 40;
            o->count1 = -50;
        LABEL_12:
            if (o->x <= 0x8000)
                o->state = 41;
            else
                o->xm -= 16;
            if (o->y >= 0x8000)
                v1 = o->ym - 8;
            else
                v1 = o->ym + 8;
            o->ym = v1;
        }
        goto LABEL_42;
    case 30:
        goto LABEL_10;
    case 40:
        goto LABEL_12;
    case 41:
        if (o->x >= 90112)
            o->state = 40;
        else
            o->xm += 0x10;
        if (o->y >= 0x8000)
            v2 = o->ym - 8;
        else
            v2 = o->ym + 8;
        o->ym = v2;
        goto LABEL_42;
    case 100:
        o->state = 110;
        o->count1 = 0;
        o->xm = 0;
        o->ym = 0;
        PlayLoopSound(32);
        goto LABEL_27;
    case 110:
    LABEL_27:
        v3 = o->count1;
        o->count1 = v3 + 1;
        if (v3 < 60)
            goto LABEL_42;
        if (o->x >= 0xF000)
            o->xm = -0x100u;
        else
            o->xm = 0x100;
        o->ym = 341;
        o->state = 120;
        o->count1 = -2;
        PlaySound(12);
        if ((ship.cond & 2) == 0)
        {
            AddScore(o->score);
            SetCaret(0, o->x, o->y - 0x2000, o->score);
        }
        for (i = 0; i < 20; ++i)
        {
            v6 = o->y + ((GetRandom(16) - 4) << 10);
            v4 = GetRandom(96);
            CreateEntity(1, o->x + ((v4 - 48) << 10), v6, 0);
        }
    LABEL_36:
        if (++o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            v7 = o->y + ((GetRandom(16) - 4) << 10);
            v5 = GetRandom(96);
            CreateEntity(1, o->x + ((v5 - 48) << 10), v7, 0);
        }
        if (o->y < 139264)
            goto LABEL_42;
        o->state = 130;
        CreateEntity(6, 0, 0, 0);
    LABEL_40:
        if (o->y <= 188416)
        {
        LABEL_42:
            if (o->state >= 40 && o->state < 100)
            {
                if (++o->count1 > 319)
                    o->count1 = 0;
                if ((o->flag & 1) != 0)
                {
                    if (++o->child == 149)
                    {
                        CreateEntity(18, o->x, o->y, 0);
                        CreateEntity(18, o->x, o->y, 1);
                        CreateEntity(18, o->x, o->y, 2);
                    }
                    else if (o->child == 150)
                    {
                        CreateEntity(18, o->x - o->xm, o->y, 0);
                        CreateEntity(18, o->x - o->xm, o->y, 1);
                        CreateEntity(18, o->x - o->xm, o->y, 2);
                    }
                    switch (o->child)
                    {
                    case 0x1E:
                        SetCaret(1, o->x, o->y, (int)o);
                        PlaySound(30);
                        break;
                    case 0x32:
                        v9 = GetArktan(o->x - ship.x, o->y - ship.y, 64);
                        CreateEntity(13, o->x, o->y, v9);
                        CreateEntity(13, o->x, o->y, v9 - 16);
                        CreateEntity(13, o->x, o->y, v9 + 16);
                        PlaySound(7);
                        break;
                    case 0x94:
                        PlaySound(9);
                        break;
                    case 0x82:
                        SetCaret(4, o->x, o->y, (int)o);
                        PlaySound(31);
                        break;
                    case 0x96:
                        o->child = 0;
                        break;
                    }
                }
            }
            if (o->xm > 256)
                o->xm = 256;
            if (o->xm < -256)
                o->xm = -256;
            if (o->ym > 341)
                o->ym = 341;
            if (o->ym < -341)
                o->ym = -341;
            o->x += o->xm;
            o->y += o->ym;
            o->rect.left = 48;
            o->rect.top = 0;
            o->rect.right = 184;
            o->rect.bottom = 32;
            if (o->shock / 2 % 2)
            {
                o->rect.top += 32;
                o->rect.bottom += 32;
            }
        }
        else
        {
            o->cond = 0;
            CheckStageClear(1);
            StopLoopSound(32);
        }
        return;
    case 120:
        goto LABEL_36;
    case 130:
        goto LABEL_40;
    default:
        goto LABEL_42;
    }
}

//----- (00405900) --------------------------------------------------------
void ActNpc016_Boss1Eye(Object *a1)
{
    RECT v2[3];            // [esp+4h] [ebp-38h]
    Object *v3;            // [esp+34h] [ebp-8h]
    unsigned __int8 angle; // [esp+3Bh] [ebp-1h]

    v2[0].left = 0;
    v2[0].top = 64;
    v2[0].right = 16;
    v2[0].bottom = 80;
    v2[1].left = 32;
    v2[1].top = 64;
    v2[1].right = 48;
    v2[1].bottom = 80;
    v2[2].left = 64;
    v2[2].top = 64;
    v2[2].right = 80;
    v2[2].bottom = 80;
    v3 = (Object *)a1->type2;
    switch (a1->state)
    {
    case 0:
        a1->child = a1->x - v3->x;
        a1->rot1 = a1->y - v3->y;
        static unsigned char byte_44C265 = 0;
        a1->count4 = byte_44C265;
        byte_44C265 = (byte_44C265 + 1) % 4;
        a1->state = 10;
        a1->flag |= 0xAu;
        goto LABEL_3;
    case 10:
    LABEL_3:
        a1->x = a1->child + v3->x;
        a1->y = a1->rot1 + v3->y;
        if (v3->state != 30 && v3->count1 != 20)
            goto LABEL_20;
        a1->state = 20;
        a1->count2 = 1;
        a1->flag &= 0xFFFFFFF7;
        a1->flag |= 1u;
        SetCaret(1, a1->x, a1->y, (int)a1);
    LABEL_6:
        angle = GetArktan(a1->x - ship.x, a1->y - ship.y, 64);
        a1->x = a1->child + v3->x + 4 * GetCos(angle);
        a1->y = a1->rot1 + v3->y + 4 * GetSin(angle);
        if (v3->state >= 40 && v3->state < 100 && v3->count1 / 39 == a1->count4)
        {
            if (v3->count1 % 39)
            {
                if (v3->count1 % 39 == 20)
                {
                    angle = GetArktan(a1->x - ship.x, a1->y - ship.y, 64);
                    CreateEntity(13, a1->x, a1->y, angle);
                    PlaySound(7);
                }
            }
            else
            {
                SetCaret(1, a1->x, a1->y, (int)a1);
                PlaySound(30);
            }
        }
        if (v3->state == 110 && v3->count1 / 10 == a1->count4)
        {
            a1->score = 4;
        }
        else if (a1->life > 64)
        {
            goto LABEL_20;
        }
        ++v3->rot1;
        a1->state = 100;
        a1->count2 = 2;
        a1->shock = 0;
        a1->flag &= 0xFFFFFFFE;
        AddScore(a1->score);
        SetCaret(0, a1->x, a1->y - 24576, a1->score);
        CreateEntity(1, a1->x, a1->y, 0);
        PlaySound(11);
    LABEL_18:
        a1->x = a1->child + v3->x;
        a1->y = a1->rot1 + v3->y;
        if (!(a1->count1++ % 6))
            CreateEntity(29, a1->x, a1->y + 0x2000, 0);
    LABEL_20:
        a1->rect = v2[a1->count2];
        if (a1->shock / 2 % 2)
        {
            a1->rect.left += 16;
            a1->rect.right += 16;
        }
        if ((v3->cond & 1) == 0 || v3->type != 15)
            a1->cond = 0;
        return;
    case 20:
        goto LABEL_6;
    case 100:
        goto LABEL_18;
    default:
        goto LABEL_20;
    }
}

//----- (00405DE0) --------------------------------------------------------
void ActNpc017_Boss1BigEye(Object *o)
{
    unsigned __int16 v1; // ax
    int v2;              // [esp-8h] [ebp-40h]
    RECT rc[3];          // [esp+4h] [ebp-34h]
    Object *parent;      // [esp+34h] [ebp-4h]

    rc[0].left = 96;
    rc[0].top = 80;
    rc[0].right = 120;
    rc[0].bottom = 128;
    rc[1].left = 0;
    rc[1].top = 0;
    rc[1].right = 0;
    rc[1].bottom = 0;
    rc[2].left = 80;
    rc[2].top = 64;
    rc[2].right = 96;
    rc[2].bottom = 80;
    parent = (Object *)o->type2;
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 0xAu;
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (parent->state < 40)
            goto LABEL_20;
        o->state = 20;
        o->flag &= ~8u;
        o->flag |= 1u;
    LABEL_5:
        if (o->life <= 52 || parent->rot1 >= 4)
        {
            o->state = 30;
            o->count1 = 0;
            o->flag &= ~1u;
        LABEL_8:
            if (!(o->count1 % 10))
            {
                v2 = o->y + ((GetRandom(48) - 32) << 10);
                v1 = GetRandom(32);
                CreateEntity(1, o->x + ((v1 - 16) << 10), v2, 0);
                PlaySound(26);
            }
            if (++o->count1 >= 50)
            {
                o->state = 40;
                o->count2 = 1;
                o->shock = 0;
                CreateEntity(1, o->x + 0x1000, o->y - 0x4000, 0);
                CreateEntity(1, o->x - 0x2000, o->y, 0);
                CreateEntity(1, o->x + 0x3000, o->y + 0x2000, 0);
                PlaySound(11);
                parent->flag |= 3u;
                ClearReplaceNpChar(6, 0);
            LABEL_12:
                if (parent->state == 120)
                {
                    o->state = 100;
                    o->count2 = 2;
                    o->xoff = 0x2000;
                    o->yoff = 0x1000;
                LABEL_14:
                    if (parent->state == 120 && parent->count1 == -1)
                    {
                        o->state = 110;
                        o->life = 100;
                        o->flag |= 1u;
                        o->destroyHitVoice = 4;
                        o->w = 0x1800;
                        o->h = 0x2000;
                    LABEL_18:
                        if (o->life <= 52)
                        {
                            o->state = 120;
                            CreateEntity(7, o->x, o->y, 2);
                            o->flag &= ~1u;
                            PlaySound(11);
                            CreateEntity(1, o->x, o->y, 0);
                        }
                    }
                }
            }
        }
    LABEL_20:
        o->x = parent->x;
        o->y = parent->y - 0x1800;
        o->rect = rc[o->count2];
        if (o->state == 20 && o->shock / 2 % 2)
        {
            o->rect.left += 24;
            o->rect.right += 24;
        }
        if ((parent->cond & 1) == 0 || parent->type != 15)
            o->cond = 0;
        return;
    case 20:
        goto LABEL_5;
    case 30:
        goto LABEL_8;
    case 40:
        goto LABEL_12;
    case 100:
        goto LABEL_14;
    case 110:
        goto LABEL_18;
    default:
        goto LABEL_20;
    }
}

//----- (00406240) --------------------------------------------------------
void ActNpc018_BulletLong(Object *a1)
{
    int v1;     // edx
    int v2;     // [esp+0h] [ebp-34h]
    RECT v3[3]; // [esp+4h] [ebp-30h]

    v3[0].left = 0;
    v3[0].top = 96;
    v3[0].right = 16;
    v3[0].bottom = 112;
    v3[1].left = 32;
    v3[1].top = 96;
    v3[1].right = 48;
    v3[1].bottom = 112;
    v3[2].left = 64;
    v3[2].top = 96;
    v3[2].right = 80;
    v3[2].bottom = 112;
    if (!a1->type2)
    {
        a1->count2 = 2;
        a1->y += 0x1000;
        goto LABEL_16;
    }
    v2 = a1->state;
    if (v2)
    {
        if (v2 != 10)
        {
            if (v2 != 20)
                goto LABEL_16;
        LABEL_13:
            a1->y += 0x1000;
            goto LABEL_16;
        }
    LABEL_11:
        if (++a1->count1 == 1)
            goto LABEL_16;
        a1->state = 20;
        a1->count2 = 2;
        a1->y += 0x1000;
        goto LABEL_13;
    }
    if (a1->type2 == 1)
        v1 = a1->x - 0x2000;
    else
        v1 = a1->x + 0x2000;
    a1->x = v1;
    a1->y += 4096;
    if (++a1->count1 >= 5)
    {
        a1->state = 10;
        a1->count1 = 0;
        a1->count2 = 1;
        goto LABEL_11;
    }
LABEL_16:
    if (a1->y > 0x2A000)
        a1->cond = 0;
    a1->rect = v3[a1->count2];
    if (a1->type2 == 2 && a1->count2 < 2)
    {
        a1->rect.left += 16;
        a1->rect.right += 16;
    }
}

//----- (00406430) --------------------------------------------------------
void ActNpc019_BGM(Object *a1)
{
    ChangeMusic(a1->type2);
    a1->cond = 0;
}