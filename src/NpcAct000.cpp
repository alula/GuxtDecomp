#include <windows.h>

#include "NpcAct000.h"

#include "Caret.h"
#include "GameAttr.h"
#include "Object.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

//----- (00403960) --------------------------------------------------------
void ActNpc000(Object *o)
{
    RECT rc = {0, 0, 16, 16};
    RECT rcStage; // [esp+10h] [ebp-10h] BYREF

    o->rect = rc;

    if (o->shock / 2 % 2)
    {
        o->rect.top += 16;
        o->rect.bottom += 16;
    }
    GetStageRect(&rcStage);
    if (o->y > rcStage.bottom + 0x2000)
        o->cond = 0;
}

//----- (00403A10) --------------------------------------------------------
void ActNpc001_Explode(Object *a1)
{
    RECT rc[7] = {
        {0, 0, 32, 32},
        {32, 0, 64, 32},
        {64, 0, 96, 32},
        {96, 0, 128, 32},
        {128, 0, 160, 32},
        {160, 0, 192, 32},
        {192, 0, 224, 32},
    };

    if (++a1->count1 >= 4)
        a1->y += 0x1000;
    else
        a1->y += 0x400;

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
void ActNpc002_CloudL(Object *o)
{
    RECT rc = {0, 0, 48, 24};
    o->y += 0x800;

    if (o->y > 0x2C000)
        o->cond = 0;

    o->rect = rc;
}

//----- (00403C00) --------------------------------------------------------
void ActNpc003_CloudS(Object *o)
{
    RECT rc = {0, 24, 16, 32};
    o->y += 0x200;
    if (o->y > 0x2C000)
        o->cond = 0;
    o->rect = rc;
}

//----- (00403C70) --------------------------------------------------------
void ActNpc004_Puff(Object *o)
{
    RECT rc[5] = {
        {0, 56, 8, 64},
        {8, 56, 16, 64},
        {16, 56, 24, 64},
        {24, 56, 32, 64},
        {32, 56, 40, 64},
    };

    o->y += 0x2000;
    if (o->y > 0x2C000)
        o->cond = 0;
    if (++o->count3 > 1)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 <= 4)
        o->rect = rc[o->count2];
    else
        o->cond = 0;
}

//----- (00403DA0) --------------------------------------------------------
void ActNpc005_Hanger(Object *o)
{
    RECT rc[6] = {
        {0, 0, 24, 24},
        {24, 0, 48, 24},
        {48, 0, 72, 24},
        {72, 0, 96, 24},
        {96, 0, 120, 24},
        {120, 0, 144, 24},
    };

    if (o->life > 994)
    {
        switch (o->state)
        {
        case 0:
            o->state = 10;
            o->y = 0x28000;
            o->ym = -0x1800;
            PlaySound(26);
        case 10:
            o->ym += 0x71;
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
            if (ship.x >= o->x)
                o->xm += 0x20;
            else
                o->xm -= 0x20;

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
        o->rect = rc[o->count2];
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
void ActNpc006_CloudGen(Object *o)
{
    if (++o->count1 > 15)
    {
        o->count1 = 0;
        if (++o->state > 9)
            o->state = 0;
    }

    if (o->count1 == 0)
    {
        int x = GetRandom(120) << 10;
        switch (o->state)
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
    int v1;
    RECT rc[3] = {
        {240, 48, 256, 64},
        {240, 64, 256, 80},
        {240, 80, 256, 96},
    };

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
    RECT rc[3] = {
        {0, 48, 16, 64},
        {16, 48, 32, 64},
        {32, 48, 48, 64},
    };

    switch (o->state)
    {
    case 0:
        o->y = 0x2C000;
        o->ym = -0x400;
        PlaySound(26);
        o->state = 10;
        o->count2 = 2;
    case 10:
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
    RECT rc = {48, 48, 64, 64};

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
    case 10:
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
        o->rect = rc;
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
    int v1;
    int state;
    RECT rc = {0, 32, 40, 48};
    unsigned char v3;

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
void ActNpc013_Bullet(Object *o)
{
    int v1; // [esp+0h] [ebp-44h]
    RECT rc[4] = {
        {144, 32, 160, 48},
        {160, 32, 176, 48},
        {176, 32, 192, 48},
        {192, 32, 208, 48},
    };

    v1 = o->state;
    if (!v1)
    {
        o->xm = 2 * GetCos(o->type2);
        o->ym = 2 * GetSin(o->type2);
        o->state = 10;
        goto LABEL_5;
    }
    if (v1 == 10)
    {
    LABEL_5:
        o->x += o->xm;
        o->y += o->ym;
    }
    if (++o->count3 > 1)
    {
        o->count3 = 0;
        ++o->count2;
    }
    if (o->count2 > 3)
        o->count2 = 0;
    if (o->x < (signed int)-0x10000 || o->x > 0x2E000 || o->y < (signed int)-0x10000 || o->y > 0x38000)
        o->cond = 0;

    o->rect = rc[o->count2];
}

//----- (00404E50) --------------------------------------------------------
void ActNpc014_BulletSlow(Object *o)
{
    int v1;
    RECT v2[4] = {
        {144, 32, 160, 48},
        {160, 32, 176, 48},
        {176, 32, 192, 48},
        {192, 32, 208, 48},
    };

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
        {208, 128, 224, 144},
    };

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
    int v6;           // [esp-8h] [ebp-24h]
    int v7;           // [esp-8h] [ebp-24h]
    int i;            // [esp+4h] [ebp-18h]
    unsigned char v9; // [esp+1Bh] [ebp-1h]

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
        o->ym = -0x100;
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
                o->ym -= 8;
            else
                o->ym += 8;
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
            o->ym -= 8;
        else
            o->ym += 8;

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
        if (o->count1++ < 60)
            goto LABEL_42;

        if (o->x >= 0xF000)
            o->xm = -0x100;
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

            CreateEntity(1, o->x + ((GetRandom(96) - 48) << 10), v6, 0);
        }
    LABEL_36:
        if (++o->count1 > 5)
        {
            o->count1 = GetRandom(4);
            v7 = o->y + ((GetRandom(16) - 4) << 10);

            CreateEntity(1, o->x + ((GetRandom(96) - 48) << 10), v7, 0);
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
    RECT rc[3] = {
        {0, 64, 16, 80},
        {32, 64, 48, 80},
        {64, 64, 80, 80},
    };
    Object *parent = (Object *)a1->type2;
    unsigned char angle;

    switch (a1->state)
    {
    case 0:
        a1->child = a1->x - parent->x;
        a1->rot1 = a1->y - parent->y;
        a1->count4 = byte_44C265;
        byte_44C265 = (byte_44C265 + 1) % 4;
        a1->state = 10;
        a1->flag |= 0xAu;
        goto LABEL_3;
    case 10:
    LABEL_3:
        a1->x = a1->child + parent->x;
        a1->y = a1->rot1 + parent->y;
        if (parent->state != 30 && parent->count1 != 20)
            goto LABEL_20;
        a1->state = 20;
        a1->count2 = 1;
        a1->flag &= 0xFFFFFFF7;
        a1->flag |= 1u;
        SetCaret(1, a1->x, a1->y, (int)a1);
    LABEL_6:
        angle = GetArktan(a1->x - ship.x, a1->y - ship.y, 64);
        a1->x = a1->child + parent->x + 4 * GetCos(angle);
        a1->y = a1->rot1 + parent->y + 4 * GetSin(angle);
        if (parent->state >= 40 && parent->state < 100 && parent->count1 / 39 == a1->count4)
        {
            if (parent->count1 % 39)
            {
                if (parent->count1 % 39 == 20)
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
        if (parent->state == 110 && parent->count1 / 10 == a1->count4)
        {
            a1->score = 4;
        }
        else if (a1->life > 64)
        {
            goto LABEL_20;
        }
        ++parent->rot1;
        a1->state = 100;
        a1->count2 = 2;
        a1->shock = 0;
        a1->flag &= 0xFFFFFFFE;
        AddScore(a1->score);
        SetCaret(0, a1->x, a1->y - 24576, a1->score);
        CreateEntity(1, a1->x, a1->y, 0);
        PlaySound(11);
    LABEL_18:
        a1->x = a1->child + parent->x;
        a1->y = a1->rot1 + parent->y;
        if (!(a1->count1++ % 6))
            CreateEntity(29, a1->x, a1->y + 0x2000, 0);
    LABEL_20:
        a1->rect = rc[a1->count2];
        if (a1->shock / 2 % 2)
        {
            a1->rect.left += 16;
            a1->rect.right += 16;
        }
        if ((parent->cond & 1) == 0 || parent->type != 15)
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
    RECT rc[3] = {
        {96, 80, 120, 128},
        {0, 0, 0, 0},
        {80, 64, 96, 80},
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
                CreateEntity(1, o->x + ((GetRandom(32) - 16) << 10), o->y + ((GetRandom(48) - 32) << 10), 0);
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
    int v2; // [esp+0h] [ebp-34h]
    RECT rc[3] = {
        {0, 96, 16, 112},
        {32, 96, 48, 112},
        {64, 96, 80, 112},
    };

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
        a1->x -= 0x2000;
    else
        a1->x += 0x2000;

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

    a1->rect = rc[a1->count2];
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