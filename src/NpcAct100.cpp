#include <windows.h>

#include "NpcAct100.h"

#include "Caret.h"
#include "Ending.h"
#include "Fade.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00413030) --------------------------------------------------------
void ActNpc100_Boss5(Object *o)
{
    static RECT rc[8] = {
        {0, 80, 32, 104},
        {32, 80, 64, 104},
        {64, 80, 96, 104},
        {96, 80, 128, 104},
        {128, 80, 160, 104},
        {160, 80, 192, 104},
        {192, 80, 224, 104},
        {224, 80, 256, 104},
    };

    int v6;    // [esp-8h] [ebp-20h]
    int v7;    // [esp-8h] [ebp-20h]
    int i;     // [esp+4h] [ebp-14h]
    int x;     // [esp+8h] [ebp-10h] BYREF
    int y;     // [esp+Ch] [ebp-Ch] BYREF
    int angle; // [esp+10h] [ebp-8h]
    int v12;   // [esp+14h] [ebp-4h]

    x = o->x;
    y = o->y;

    SubStageXOScroll(&x, &y);
    v12 = (1000 - o->life) / 50;

    if (o->life < 800)
        o->life = 800;

    if (v12 > 3)
        v12 = 3;

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->y -= 0x8400;
        o->flag |= 8u;
        x = o->x - 0x4800;
        y = o->y + 0x5400;
        SubStageXOScroll(&x, &y);
        CreateEntity(101, x, y, (intptr_t)o);
        x = o->x + 0x4800;
        y = o->y + 0x5400;
        SubStageXOScroll(&x, &y);
        CreateEntity(101, x, y, (intptr_t)o);
        x = o->x - 0xB000;
        y = o->y + 0x2400;
        SubStageXOScroll(&x, &y);
        CreateEntity(101, x, y, (intptr_t)o);
        x = o->x + 0xB000;
        y = o->y + 0x2400;
        SubStageXOScroll(&x, &y);
        CreateEntity(101, x, y, (intptr_t)o);

    case 10:

        if (o->child < 4)
            goto LABEL_40;
        o->state = 11;
        o->count1 = 0;
    LABEL_9:
        if (++o->count1 < 200)
            goto LABEL_40;
        o->state = 15;
        PlaySound(38);
    LABEL_11:
        if (++o->count3 > 3)
        {
            ++o->count2;
            o->count3 = 0;
        }
        if (o->count2 < 3)
            goto LABEL_40;
        o->state = 20;
        o->flag &= ~8u;
        o->flag |= 1u;
    LABEL_15:
        if (o->count1 == 200)
        {
            PlaySound(31);
            SetCaret(4, x, y + 2048, 0);
            ++o->count1;
        }
        if (o->count1 == 216)
        {
            ++o->count1;
            PlaySound(9);

            angle = GetArktan(x - ship.x, y + 0x400 - ship.y, 64);
            CreateEntity(104, x, y + 0x800, angle);

            x += 2 * GetCos(o->type2);
            y += 2 * GetSin(o->type2);
            CreateEntity(104, x, y + 0x800, angle);

            o->count1 = 0;
            ++o->count1;
        }
        else if (!o->shock)
        {
            ++o->count1;
        }
        if (v12 < 3)
            goto LABEL_40;
        o->state = 110;
        o->count1 = 0;
        o->flag &= ~1u;
        CreateEntity(1, x, y, 0);
        PlaySound(13);
        PlayLoopSound(32);
        if (!GetInScoreAttack())
            SetShipInvincibility();
    LABEL_24:
        if (o->count1++ < 60)
            goto LABEL_40;
        o->state = 120;
        o->child = 0;
        PlaySound(12);
        SetScrollSpeed(-256);
        if ((ship.cond & 2) == 0)
        {
            AddScore(o->score);
            SetCaret(0, x, y + 0x6000, o->score);
        }
        for (i = 0; i < 20; ++i)
        {
            v6 = y + ((GetRandom(16) - 4) << 10);
            CreateEntity(1, x + ((GetRandom(96) - 48) << 10), v6, 0);
        }
    LABEL_30:
        ++o->child;
        ++o->count1;
        if (o->child == 150)
            SetScrollSpeed(-512);
        if (o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            v7 = y + ((GetRandom(16) - 4) << 10);
            CreateEntity(1, x + ((GetRandom(96) - 48) << 10), v7, 0);
        }
        if (y < 0x22000)
            goto LABEL_40;
        o->state = 130;
    LABEL_36:
        if (y <= 0x2E000)
        {
        LABEL_40:
            if (o->state >= 20)
            {
                if (o->state < 30)
                {
                    if (o->shock / 2 % 2)
                        o->rect = rc[6];
                    else
                        o->rect = rc[v12 + o->count2];
                }
                else
                {
                    o->rect = rc[7];
                }
            }
            else
            {
                o->rect = rc[o->count2];
            }
        }
        else
        {
            o->cond = 0;
            if (!GetInScoreAttack())
                CheckStageClear(5);
            StopLoopSound(32);
        }
        return;
    case 11:
        goto LABEL_9;
    case 15:
        goto LABEL_11;
    case 20:
        goto LABEL_15;
    case 110:
        goto LABEL_24;
    case 120:
        goto LABEL_30;
    case 130:
        goto LABEL_36;
    default:
        goto LABEL_40;
    }
}

//----- (00413780) --------------------------------------------------------
void ActNpc101(Object *o)
{
    static RECT rc[8] = {
        {0, 64, 16, 80},
        {16, 64, 32, 80},
        {32, 64, 48, 80},
        {48, 64, 64, 80},
        {64, 64, 80, 80},
        {80, 64, 96, 80},
        {96, 64, 112, 80},
        {112, 64, 128, 80},
    };

    int v1;           // [esp+4h] [ebp-24h]
    int s_x;          // [esp+14h] [ebp-14h] BYREF
    int s_y;          // [esp+18h] [ebp-10h] BYREF
    unsigned char v4; // [esp+1Fh] [ebp-9h]

    int v5 = (1000 - o->life) / 50;
    if (o->life < 850)
        o->life = 850;
    if (v5 > 2)
        v5 = 2;

    Object *parent = (Object *)o->type2;
    s_x = o->x;
    s_y = o->y;

    SubStageXOScroll(&s_x, &s_y);

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 8u;
        switch (o->x / 0x400)
        {
        case 20:
            o->xm = 3;
            o->count1 = -20;
            break;
        case 46:
            o->xm = 1;
            o->count1 = -40;
            break;
        case 82:
            o->xm = 2;
            o->count1 = -30;
            break;
        case 108:
            o->xm = 4;
            o->count1 = -10;
            break;
        default:; // fallthrough
        }
    case 10:
        if (++o->count1 < 200)
            goto LABEL_40;
        o->state = 15;
        PlaySound(38);
    LABEL_13:
        if (++o->count3 > 3)
        {
            ++o->count2;
            o->count3 = 0;
        }
        if (o->count2 < 3)
            goto LABEL_40;
        o->state = 20;
        o->flag &= ~8u;
        o->flag |= 1u;
        switch (o->xm)
        {
        case 1:
            o->count1 = -10;
            break;
        case 2:
            o->count1 = -20;
            break;
        case 3:
            o->count1 = -30;
            break;
        case 4:
            o->count1 = -40;
            break;
        default:
            break;
        }
    LABEL_21:
        if (v5 == 2)
        {
            o->flag &= ~1u;
            ++parent->child;
            o->state = 21;
            CreateEntity(1, s_x, s_y, 0);
            PlaySound(14);
        }
    LABEL_23:
        v1 = o->child;
        if (v1)
        {
            if (v1 != 1)
                goto LABEL_30;
        }
        else
        {
            if (++o->count1 < 180)
                goto LABEL_30;
            o->count1 = 0;
            o->child = 1;
            PlaySound(30);
            SetCaret(1, s_x, s_y + 0x800, 0);
            ++o->count1;
        }
        if (++o->count1 >= 14)
        {
            o->count1 = 0;
            o->child = 0;
            PlaySound(36);
            v4 = GetArktan(s_x - ship.x, s_y + 0x400 - ship.y, 64);
            CreateEntity(102, s_x, s_y + 0x800, v4);
            o->count1 = 50 * v5;
        }
    LABEL_30:
        if (o->shock)
            o->count1 += 2;
        if (parent->state >= 30)
        {
            o->state = 30;
            switch (o->xm)
            {
            case 1:
                o->count1 = -10;
                break;
            case 2:
                o->count1 = -20;
                break;
            case 3:
                o->count1 = -30;
                break;
            case 4:
                o->count1 = -40;
                break;
            default:
                break;
            }
        LABEL_38:
            if (++o->count1 >= 50)
            {
                o->state = 31;
                CreateEntity(1, s_x, s_y, 0);
                PlaySound(12);
            }
        }
    LABEL_40:
        if (o->state >= 20)
        {
            if (o->state <= 30)
            {
                if (o->shock / 2 % 2)
                    o->rect = rc[6];
                else
                    o->rect = rc[v5 + 3];
            }
            else
            {
                o->rect = rc[7];
            }
        }
        else
        {
            o->rect = rc[o->count2];
        }
        return;
    case 15:
        goto LABEL_13;
    case 20:
        goto LABEL_21;
    case 21:
        goto LABEL_23;
    case 30:
        goto LABEL_38;
    default:
        goto LABEL_40;
    }
}

//----- (00413D70) --------------------------------------------------------
void ActNpc102_B5Bullet(Object *o)
{
    int v1; // [esp+0h] [ebp-4h]

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_6;
    }
    else
    {
        o->xm = 2 * GetCos(o->type2);
        o->ym = 2 * GetSin(o->type2);
        CreateEntity(103, o->x + 0x1000, o->y, (intptr_t)o);
        CreateEntity(103, o->x - 0x1000, o->y, (intptr_t)o);
        o->state = 10;
    }
    o->x += o->xm;
    o->y += o->ym;
LABEL_6:
    if (o->x < -0x10000 || o->x > 0x2E000 || o->y < (signed int)0xFFFF0000 || o->y > 0x38000)
        o->cond = 0;
}

//----- (00413E70) --------------------------------------------------------
void ActNpc103(Object *o)
{
    static RECT rc = {120, 72, 136, 88};
    int v1;
    Object *parent = (Object *)o->type2;

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_11;
    }
    else
    {
        o->state = 10;
        o->rot1 = 0;
        o->count4 = parent->num;
        if (o->x >= parent->x)
            o->child = 128;
        else
            o->child = 0;
        o->flag |= 1u;
    }
    o->child += 12;
    o->child %= 256;
    if (o->rot1 < 0x1800)
        o->rot1 += 0x155;
    o->x = parent->x + o->rot1 * GetCos(o->child) / 0x400;
    o->y = parent->y + o->rot1 * GetSin(o->child) / 0x400;

LABEL_11:
    if ((parent->cond & 1) == 0 || parent->num != o->count4)
        o->cond = 0;

    o->rect = rc;
}

//----- (00413FE0) --------------------------------------------------------
void ActNpc104_B5Laser(Object *a1)
{
    static RECT rc = {168, 56, 176, 64};

    int v1 = a1->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_6;
    }
    else
    {
        a1->xm = 4 * GetCos(a1->type2);
        a1->ym = 4 * GetSin(a1->type2);
        a1->state = 10;
    }
    CreateEntity(105, a1->x, a1->y, 0);
    a1->x += a1->xm;
    a1->y += a1->ym;
LABEL_6:
    if (a1->x < -0x10000 || a1->x > 0x2E000 || a1->y < -0x10000 || a1->y > 0x38000)
        a1->cond = 0;

    a1->rect = rc;
}

//----- (004140E0) --------------------------------------------------------
void ActNpc105_B5LaserTrail(Object *o)
{
    int v1; // [esp+0h] [ebp-4h]
    static RECT rc[3] = {
        {168, 56, 176, 64},
        {168, 64, 176, 72},
        {168, 72, 176, 80},
    };

    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_9;
    }
    else
    {
        o->state = 10;
    }
    if (++o->count3 > 4)
    {
        ++o->count2;
        o->count3 = 0;
    }

    // OOB access!
    if (o->count2 >= 3)
        o->cond = 0;
LABEL_9:
    o->rect = rc[o->count2];
}

//----- (00414180) --------------------------------------------------------
void ActNpc106_AzaBonusSpawner_(Object *o)
{
    int v1;
    RECT rc = {16, 0, 32, 16};

    v1 = o->state;
    switch (v1)
    {
    case 0:
        o->x = 0;
        o->y = 0;
        asteroidsKilled = 0;
        o->state = 1;
    case 1:
        if (asteroidsKilled < 20)
            return;
        o->state = 10;
        o->x = bonusAzaX;
        o->y = bonusAzaY;
        o->flag |= 2u;
        o->ym = -0x800;
    case 10:
        if (o->ym < 0x800)
            o->ym += 64;
        o->y += o->ym;
        break;
    }

    if (o->y > 0x2C000)
        o->cond = 0;

    o->rect = rc;
}

//----- (004142A0) --------------------------------------------------------
void ActNpc107(Object *o)
{
    if (o->type2)
        ship.flag |= 0x100u;
    else
        ship.flag &= ~0x100u;
}

//----- (004142E0) --------------------------------------------------------
void ActNpc108_Boss6(Object *a1)
{
    static RECT rc = {0, 104, 48, 152};

    int v8;       // [esp-8h] [ebp-20h]
    intptr_t v9;  // [esp-4h] [ebp-1Ch]
    intptr_t v10; // [esp+8h] [ebp-10h]
    int px;       // [esp+10h] [ebp-8h]
    int py;       // [esp+14h] [ebp-4h]

    switch (a1->state)
    {
    case 0:
        a1->state = 10;
        a1->y = -32768;
        a1->ym = 512;
        a1->count3 = 96;
        CreateEntity(112, 0, -24576, (intptr_t)a1);
        CreateEntity(109, 0, -16384, (intptr_t)a1);
        CreateEntity(109, 0, -16384, (intptr_t)a1);
        CreateEntity(109, 0, -16384, (intptr_t)a1);
        CreateEntity(109, 0, -16384, (intptr_t)a1);
        CreateEntity(110, 0, -16384, (intptr_t)a1);
        CreateEntity(113, a1->x - 1024, -16384, (intptr_t)a1);
        CreateEntity(113, a1->x + 1024, -16384, (intptr_t)a1);
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (a1->y > 139264)
            a1->ym -= 8;
        if (a1->ym < 0)
        {
            a1->state = 20;
            a1->child = 0;
        }
        a1->y += a1->ym;
        a1->rot1 -= 4;
        if (a1->rot1 < 0)
            a1->rot1 += 256;
        goto LABEL_130;
    case 20:
        if (a1->count3 < 108)
            ++a1->count3;
        if (a1->y <= 0x8000)
        {
            a1->rot1 -= 4;
            if (a1->rot1 < 0)
                a1->rot1 += 256;
            a1->ym += 8;
        }
        else
        {
            a1->rot1 -= 8;
            if (a1->rot1 < 0)
                a1->rot1 += 256;
            a1->ym -= 8;
        }
        if (a1->x <= 98304)
        {
            if (a1->x >= 24576)
            {
                if (a1->x <= ship.x)
                    a1->xm += 8;
                else
                    a1->xm -= 8;
            }
            else
            {
                a1->xm += 8;
            }
        }
        else
        {
            a1->xm -= 8;
        }
        if (a1->xm > 768)
            a1->xm = 768;
        if (a1->xm < -768)
            a1->xm = -768;
        if (a1->ym > 768)
            a1->ym = 768;
        if (a1->ym < -768)
            a1->ym = -768;
        a1->y += a1->ym;
        a1->x += a1->xm;
        v10 = a1->child;
        if (v10)
        {
            if (v10 == 1)
            {
                if (!++a1->count1)
                {
                    SetCaret(1, a1->x - 14336, a1->y + 10240, (intptr_t)a1);
                    PlaySound(30);
                }
                if (a1->count1 == 10)
                {
                    CreateEntity(111, a1->x - 14336, a1->y + 10240, 0);
                    PlaySound(9);
                }
                if (a1->count1 == 15)
                {
                    SetCaret(1, a1->x + 15360, a1->y + 10240, (intptr_t)a1);
                    PlaySound(30);
                }
                if (a1->count1 == 25)
                {
                    CreateEntity(111, a1->x + 15360, a1->y + 10240, 0);
                    PlaySound(9);
                }
                if (a1->count1 == 30)
                {
                    SetCaret(1, a1->x - 5120, a1->y + 0x4000, (intptr_t)a1);
                    PlaySound(30);
                }
                if (a1->count1 == 40)
                {
                    CreateEntity(111, a1->x - 5120, a1->y + 0x4000, 0);
                    PlaySound(9);
                }
                if (a1->count1 > 80)
                {
                    a1->count1 = 0;
                    a1->child = 0;
                }
            }
            else if (v10 == 2)
            {
                a1->state = 30;
                a1->child = 2;
                a1->count4 = 0;
                a1->count1 = 0;
            }
        }
        else
        {
            if (++a1->count1 < 80 && !(a1->count1 % 12))
            {
                v9 = GetArktan(a1->x - ship.x + 1024, a1->y - ship.y - 2048, 64);
                CreateEntity(63, a1->x, a1->y, v9);
                SetCaret(1, a1->x + 1024, a1->y - 2048, (intptr_t)a1);
                PlaySound(36);
            }
            if (a1->count1 >= 96)
                a1->count1 = 0;
            if (ship.x >= a1->x - 12288 && ship.x <= a1->x + 12288 && ship.y > a1->y)
            {
                a1->count1 = -1;
                a1->child = 1;
            }
        }
        goto LABEL_130;
    case 30:
        if (a1->count3 < 128)
            ++a1->count3;
        if (a1->y <= 0x8000)
        {
            a1->rot1 -= 4;
            if (a1->rot1 < 0)
                a1->rot1 += 256;
            a1->ym += 8;
        }
        else
        {
            a1->rot1 -= 8;
            if (a1->rot1 < 0)
                a1->rot1 += 256;
            a1->ym -= 8;
        }
        if (a1->x <= 98304)
        {
            if (a1->x >= 24576)
            {
                if (a1->x <= ship.x)
                    a1->xm += 8;
                else
                    a1->xm -= 8;
            }
            else
            {
                a1->xm += 8;
            }
        }
        else
        {
            a1->xm -= 8;
        }
        if (a1->xm > 768)
            a1->xm = 768;
        if (a1->xm < -768)
            a1->xm = -768;
        if (a1->ym > 768)
            a1->ym = 768;
        if (a1->ym < -768)
            a1->ym = -768;
        a1->y += a1->ym;
        a1->x += a1->xm;
        ++a1->count1;
        switch (a1->child)
        {
        case 0:
        case 1:
            if (a1->child)
                px = a1->x - 12288;
            else
                px = a1->x + 13312;
            py = a1->y - 0x4000;
            if (a1->count1 == 1)
            {
                SetCaret(1, px, py, (intptr_t)a1);
                PlaySound(30);
            }
            if (a1->count1 > 24 && a1->count1 < 8 * a1->count4 + 64 && !(a1->count1 % 8))
            {
                CreateEntity(114, px, py, GetArktan(px - ship.x, py - ship.y, 64));
                PlaySound(36);
            }
            if (a1->count1 >= 8 * a1->count4 + 72)
            {
                ++a1->child;
                a1->count1 = 0;
            }
            break;
        case 2:
            if (a1->count1++ > (70 - 20 * a1->count4) && CountNpCharType(98) < 2 * a1->count4 + 8)
            {
                a1->child = 0;
                a1->count1 = 0;
            }
            break;
        case 3:
            a1->state = 40;
            a1->child = 0;
            a1->count4 = 0;
            a1->count1 = 0;
            a1->xm = a1->x;
            a1->ym = a1->y;
            PlayLoopSound(32);
            break;
        default:
            goto LABEL_130;
        }
        goto LABEL_130;
    case 40:
        if (++a1->count1 > 150 && a1->count3 > 80)
            --a1->count3;
        a1->rot1 -= 4;
        if (a1->rot1 < 0)
            a1->rot1 += 256;
        if (a1->xm < 61440)
            a1->xm += 170;
        if (a1->xm > 61440)
            a1->xm -= 170;
        if (a1->ym < 54272)
            a1->ym += 170;
        if (a1->ym > 54272)
            a1->ym -= 170;
        a1->x = a1->xm + ((GetRandom(2) - 1) << 10);
        a1->y = a1->ym + ((GetRandom(2) - 1) << 10);
        if (++a1->count4 > 5)
        {
            a1->count4 = GetRandom(4);
            v8 = a1->y + ((GetRandom(48) - 32) << 10);
            CreateEntity(1, a1->x + ((GetRandom(48) - 24) << 10), v8, 0);
        }
        if (a1->count1 < 300)
            goto LABEL_130;
        a1->state = 41;
        a1->count1 = 0;
        SetFadeWhiteActive(a1->x / 1024, a1->y / 1024);
        PlaySound(13);
        StopLoopSound(32);
        if (!CheckFadeWhiteEnd())
            goto LABEL_130;
    LABEL_125:
        a1->state = 100;
        a1->count1 = 0;
        if ((ship.cond & 2) == 0)
        {
            AddScore(a1->score);
            SetCaret(0, a1->x, a1->y - 4096, a1->score);
            SetShipInvincibility();
        }
    LABEL_128:
        if (a1->count1++ >= 150)
        {
            CheckStageClear(5);
            a1->cond = 0;
        }
        else
        {
        LABEL_130:
            if (a1->state >= 100)
                memset(&a1->rect, 0, sizeof(a1->rect));
            else
                a1->rect = rc;
        }
        return;
    case 41:
        goto LABEL_125;
    case 100:
        goto LABEL_128;
    default:
        goto LABEL_130;
    }
}

//----- (00414F80) --------------------------------------------------------
void ActNpc109(Object *o)
{
    static RECT rc[5] = {
        {0, 152, 16, 168},
        {16, 152, 32, 168},
        {80, 48, 96, 64},
        {96, 48, 112, 64},
        {96, 32, 112, 48},
    };

    int angle;            // [esp-4h] [ebp-10h]
    Object *parent;       // [esp+4h] [ebp-8h]
    unsigned char angle2; // [esp+Bh] [ebp-1h]

    parent = (Object *)o->type2;
    if (o->state < 100 && o->life < 930)
    {
        CreateEntity(1, o->x, o->y, 0);
        angle = GetArktan(o->x - ship.x, o->y - ship.y, 64);
        CreateEntity(98, o->x, o->y, angle);
        PlaySound(12);
        o->state = 100;
        o->count2 = 4;
        o->shock = 0;
        o->flag &= ~1u;
        ++parent->count4;
        AddScore(o->score);
        SetCaret(0, o->x, o->y, o->score);
    }
    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->child = parent->child++;
        if (parent->child == 4)
            parent->child = 0;
        o->flag |= 0xAu;

    case 10:
        if (parent->state < 30)
            goto LABEL_14;
        o->state = 20;
        o->count2 = 2;
        o->flag &= ~8u;
        o->flag |= 1u;
        SetCaret(1, o->x, o->y, (intptr_t)o);
        if (parent->state < 40)
            goto LABEL_14;
    LABEL_10:
        o->state = 100;
        o->count2 = 0;
        o->shock = 0;
        o->flag &= ~1u;
        o->flag |= 8u;
        SetCaret(1, o->x, o->y, (intptr_t)o);
    LABEL_12:
        if (parent->state == 100)
        {
            o->cond = 0;
        }
        else
        {
        LABEL_14:
            angle2 = (LOBYTE(o->child) << 6) + LOBYTE(parent->rot1);
            o->x = parent->x + parent->count3 * GetCos(angle2) / 4;
            o->y = parent->y + parent->count3 * GetSin(angle2) / 4;
            if (o->shock / 2 % 2)
                o->rect = rc[3];
            else
                o->rect = rc[o->count2];
        }
        return;
    case 20:
        goto LABEL_10;
    case 100:
        goto LABEL_12;
    default:
        goto LABEL_14;
    }
}

//----- (00415320) --------------------------------------------------------
void ActNpc110(Object *o)
{
    static RECT rc[4] = {
        {128, 64, 144, 80},
        {144, 64, 160, 80},
        {160, 64, 176, 80},
        {176, 64, 192, 80},
    };

    Object *parent;

    parent = (Object *)o->type2;
    if (o->state < 100 && o->life < 920)
        o->state = 30;
    switch (o->state)
    {
    case 0:
        o->flag |= 0xAu;
        o->state = 10;
        o->child = parent->child++;
        if (parent->child == 4)
            parent->child = 0;
        goto LABEL_7;
    case 10:
    LABEL_7:
        if (parent->state >= 20)
        {
            o->flag &= ~8u;
            o->flag |= 1u;
            PlaySound(38);
            SetCaret(1, o->x, o->y, (intptr_t)o);
            o->count2 = 1;
            o->state = 20;
        }
        goto LABEL_14;
    case 30:
        CreateEntity(1, o->x, o->y, 0);
        PlaySound(11);
        o->state = 100;
        o->flag &= ~1u;
        parent->child = 2;
        goto LABEL_10;
    case 100:
    LABEL_10:
        if (!(o->count1++ % 6))
            CreateEntity(29, o->x, o->y, 0);
        if (parent->state != 100)
            goto LABEL_14;
        o->cond = 0;
        break;
    default:
    LABEL_14:
        o->x = parent->x + 0x1800;
        o->y = parent->y + 0x4000;
        if (o->state == 100)
        {
            o->rect = rc[3];
        }
        else if (o->shock / 2 % 2)
        {
            o->rect = rc[2];
        }
        else
        {
            o->rect = rc[o->count2];
        }
        break;
    }
}

//----- (00415610) --------------------------------------------------------
void ActNpc111_B6Laser(Object *o)
{
    static RECT rc[5] = {
        {120, 112, 128, 136},
        {128, 112, 136, 136},
        {136, 112, 144, 136},
        {120, 136, 128, 160},
        {128, 136, 136, 160},
    };

    if (!o->state)
    {
        o->state = 1;
        o->count2 = -1;
    }
    if (o->count2 < 4)
        ++o->count2;

    o->y += 0x1000;
    if (o->y > 0x2E000)
        o->cond = 0;

    o->rect = rc[o->count2];
}

//----- (004156A0) --------------------------------------------------------
void ActNpc112(Object *o)
{
    static RECT rcNpc112[5] = {
        {0, 0, 0, 0},
        {48, 104, 72, 136},
        {72, 104, 96, 136},
        {96, 104, 120, 136},
        {120, 104, 144, 136},
    };

    Object *parent = (Object *)o->type2;

    switch (o->state)
    {
    case 0:
        o->state = 10;
        o->flag |= 0xAu;
        goto LABEL_3;
    case 10:
    LABEL_3:
        if (parent->state < 30)
            goto LABEL_11;
        o->state = 20;
        if (++o->count1 < 100)
            goto LABEL_11;
    LABEL_5:
        o->state = 30;
        o->count2 = 1;
        o->flag &= ~8u;
        o->flag |= 1u;
        PlaySound(12);
        CreateEntity(1, o->x, o->y, 0);
        o->count2 = (1000 - o->life) / 100 + 1;
        if (o->count2 < 4)
            goto LABEL_11;
    LABEL_7:
        o->state = 40;
        o->flag &= ~1u;
        parent->child = 3;
    LABEL_9:
        if (parent->state == 100)
        {
            o->cond = 0;
        }
        else
        {
        LABEL_11:
            o->x = parent->x;
            o->y = parent->y;
            o->rect = rcNpc112[o->count2];
            if (o->shock / 2 % 2)
            {
                o->rect.top += 32;
                o->rect.bottom += 32;
            }
        }
        return;
    case 20:
        goto LABEL_5;
    case 30:
        goto LABEL_7;
    case 40:
        goto LABEL_9;
    default:
        goto LABEL_11;
    }
}

//----- (004158A0) --------------------------------------------------------
void ActNpc113(Object *o)
{
    static RECT rc[2] = {
        {0, 0, 0, 0},
        {32, 152, 48, 168},
    };

    int v3;
    Object *parent = (Object *)o->type2;

    v3 = o->state;
    if (v3)
    {
        if (v3 != 10)
        {
            if (v3 != 20)
                goto LABEL_13;
            goto LABEL_11;
        }
    }
    else
    {
        o->state = 10;
        o->count2 = 0;
        o->child = o->x >= parent->x;
    }
    if (parent->state < 30)
        goto LABEL_13;

    if (o->count1++ < 16)
        goto LABEL_13;

    SetCaret(1, o->x, o->y, (intptr_t)o);
    o->state = 20;
    o->count2 = 1;
LABEL_11:
    if (parent->state == 100)
    {
        o->cond = 0;
        return;
    }
LABEL_13:
    if (o->child)
        o->x = parent->x + 13312;
    else
        o->x = parent->x - 12288;

    o->y = parent->y - 0x4000;
    o->rect = rc[o->count2];
}

//----- (004159F0) --------------------------------------------------------
void ActNpc114_B6Ball(Object *o)
{
    static RECT rcB6Ball[2] = {
        {136, 88, 152, 104},
        {152, 88, 168, 104},
    };
    int v4; // [esp+0h] [ebp-8h]

    if (o->life < 1000)
    {

        CreateEntity(98, o->x, o->y, GetArktan(o->x - ship.x, o->y - ship.y, 64));
        PlaySound(15);
        SetCaret(1, o->x, o->y, 0);
        o->cond = 0;
        return;
    }

    v4 = o->state;
    if (v4)
    {
        if (v4 == 20)
        {
            o->xm += GetCos(o->child) / 16;
            o->ym += GetSin(o->child) / 16;
            o->x += o->xm;
            o->y += o->ym;

            if (o->count3++ > 0)
            {
                o->count3 = 0;
                ++o->count2;
            }
            if (o->count2 > 3)
                o->count2 = 0;
            if (o->x < -102400 || o->x > 225280 || o->y < -102400 || o->y > 266240)
                o->cond = 0;
        }
    }
    else
    {
        o->state = 20;
        o->flag |= 1u;
        o->child = GetArktan(o->x - ship.x, o->y - ship.y, 64);
    }

    if (o->count3++ > 0)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 1)
        o->count2 = 0;

    o->rect = rcB6Ball[o->count2];
}

//----- (00415C40) --------------------------------------------------------
void ActNpc115_B6Caret(Object *o)
{
    static RECT rcB6Caret[4] = {
        {120, 104, 136, 120},
        {136, 104, 152, 120},
        {152, 104, 168, 120},
        {168, 104, 184, 120},
    };

    if (++o->count3 > 2)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 <= 3)
        o->rect = rcB6Caret[o->count2];
    else
        o->cond = 0;
}

//----- (00415CC0) --------------------------------------------------------
void ActNpc116_CreditText(Object *o)
{
    ShowNextEndingText();
    SetGameDelay(50);
    o->cond = 0;
}

//----- (00415CE0) --------------------------------------------------------
void ActNpc117_CreditReplace(Object *o)
{
    if (o->count1++ > 1)
    {
        ClearReplaceNpChar(o->type2, 1);
        o->cond = 0;
    }
}

//----- (00415D20) --------------------------------------------------------
void ActNpc118_CreditLoadImg(Object *o)
{
    LoadPximgEnemy(o->type2);
    o->cond = 0;
}

//----- (00415D40) --------------------------------------------------------
void ActNpc119_CPhoto(Object *o)
{
    static RECT rcCreditPhotos[6] = {
        {0, 0, 96, 72},
        {0, 64, 96, 136},
        {0, 128, 96, 200},
        {88, 0, 184, 72},
        {88, 64, 184, 136},
        {88, 128, 184, 200},
    };
    int v3; // [esp+0h] [ebp-4h]

    v3 = o->state;
    if (v3)
    {
        if (v3 == 30)
        {
            if (o->type2 % 2)
                o->x -= 1024;
            else
                o->x += 1024;

            if (o->count1++ == 50)
                ShowNextEndingText();
        }
    }
    else
    {
        if (!GetInScoreAttack() && o->type2 == 5)
        {
            o->cond = 0;
            return;
        }
        o->state = 30;
        if (o->type2 % 2)
            o->x = 172032;
        else
            o->x = -49152;
        o->y = 0x10000;
    }
    o->rect = rcCreditPhotos[o->type2];
}

//----- (00415E50) --------------------------------------------------------
void ActNpc120_CreditGimmick(Object *o)
{
    static RECT rcCreditGimmick[2] = {
        {0, 16, 48, 32},
        {0, 48, 48, 64},
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
        o->x += 0x1000;
        o->state = 10;
    }
    o->y += 0x600;
    if (o->y > 0x14000)
        o->count2 = 1;
    if (o->y > 0x2C000)
        o->cond = 0;

LABEL_9:
    o->rect = rcCreditGimmick[o->count2];
}

//----- (00415F00) --------------------------------------------------------
void ActNpc121_BonusHidden(Object *o)
{
    static RECT rc[5] = {
        {0, 0, 0, 0},
        {32, 0, 48, 16},
        {48, 0, 64, 16},
        {64, 0, 80, 16},
        {80, 0, 96, 16},
    };

    int v1;  // [esp+0h] [ebp-Ch]
    int s_x; // [esp+4h] [ebp-8h] BYREF
    int s_y; // [esp+8h] [ebp-4h] BYREF

    s_x = o->x;
    s_y = o->y;

    SubStageXOScroll(&s_x, &s_y);
    v1 = o->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_15;
    }
    else
    {
        o->state = 10;
    }
    if (o->type2 == 3 && ++o->count1 > 150)
        o->flag |= 1u;
    if (o->type2 == 4 && s_y > ship.y - 0x6000)
    {
        o->flag |= 1u;
        o->count2 = 4;
    }
    if (o->type2 == 5)
        o->flag |= 1u;
    if (o->life <= 960)
    {
        CreateEntity(1, s_x, s_y, 0);
        o->state = 20;
        o->count2 = o->type2 - 2;
        o->flag |= 2u;
        o->flag &= ~1u;
    }

LABEL_15:
    o->rect = rc[o->count2];
}