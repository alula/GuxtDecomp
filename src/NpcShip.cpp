#include <windows.h>

#include "NpcShip.h"
#include "Bullet.h"
#include "Caret.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Map.h"
#include "Object.h"
#include "Sound.h"
#include "Stage.h"
#include "TrigFuncs.h"

unsigned int ShipSpeedTableDiag[5];
unsigned int ShipSpeedTable[5];
unsigned int ShipSpeed;
Ship ship;
unsigned int ShipUnused;
unsigned int ShipUnused2;
unsigned char ShipThrusterFrame;
unsigned char ShipIFrameFlash;
unsigned int fireHeldFrames;
unsigned int ShipPowerup;

void ShootBullet0();
void ShootBullet1();
void ShootBullet2();
void ShootBullet3();
void ShootBullet4();
void ShootBullet5();
void ShootBullet6();
void ShootBullet7();
void ShootBullet8();
void ShootBullet9(TriggerStruct *trig);
void ShootBullet10();
void ShootBullet11();

//----- (00416050) --------------------------------------------------------
Ship *GetShip()
{
    return &ship;
}

//----- (00416060) --------------------------------------------------------
void ResetShip()
{
    memset(&ship, 0, sizeof(ship));
    ship.cond = 1;
    ship.x = 0xF000;
    ship.y = 0x2D000;
    ship.xoff = 0x3000;
    ship.yoff = 0x2000;
    ship.w = 0x1000;
    ship.h = 0x1000;
    ship.surf = 0;
    ship.life = 1;
    ship.damage = 20;
    ShipUnused = 0;
    ShipUnused2 = 0;
    ShipSpeed = 0;
    ShipPowerup = 0;
}

//----- (00416110) --------------------------------------------------------
void SetInitialShipValues()
{
    ship.x = 0xF000;
    ship.y = 0x2D000;
    ship.state = 0;
    ship.count1 = 0;
    ship.shock = 100;
    ShipThrusterFrame = 0;
    ShipIFrameFlash = 0;
    fireHeldFrames = 0;
}

//----- (00416160) --------------------------------------------------------
void ShipCrushProc()
{
    ship.cond |= 2u;
    PlaySound(11);
    ShipCrushProc2();
}

//----- (00416190) --------------------------------------------------------
BOOL ActPowerUp(Object *npc)
{
    int type2;   // [esp+0h] [ebp-14h]
    int param;   // [esp+8h] [ebp-Ch]
    int o_x;     // [esp+Ch] [ebp-8h] BYREF
    int o_y;     // [esp+10h] [ebp-4h] BYREF

    switch (npc->type)
    {
    case 7:
    case 61:
        npc->cond = 0;
        o_x = npc->x;
        o_y = npc->y;
        if ((npc->flag & 0x10) != 0)
            SubStageXOScroll(&o_x, &o_y);
        type2 = npc->type2;
        if (type2 == 1)
        {
            if (SetSpeedPowerUp())
                PlaySound(27);
            else
                PlaySound(28);
            param = 8;
        }
        else if (type2 == 2)
        {
            param = 9;
            if (SetLifePowerUp())
            {
                SetCaret(0, o_x, o_y, 9);
                PlaySound(33);
            }
            else
            {
                SetCaret(0, o_x, o_y, 4);
                AddScore(4);
                PlaySound(40);
            }
        }
        else
        {
            PlaySound(29);
            SetPowerUp(npc->type2 - 2);
            param = npc->type2 + 13;
            if (ship.state == 100)
            {
                ship.xm = ship.x;
                ship.ym = ship.y;
            }
        }
        if (npc->type2 != 2)
        {
            if (npc->score)
            {
                AddScore(npc->score);
                SetCaret(0, o_x, o_y, npc->score);
                SetCaret(0, o_x, o_y - 0x2000, param);
            }
            else
            {
                SetCaret(0, o_x, o_y, param);
            }
        }
        SetCaret(1, o_x, o_y, 0);
        if (ship.rot1)
            ship.rot1 = 500;
        else
            ship.rot1 = 200;
        goto LABEL_33;
    case 45:
    case 106:
    case 121:
        npc->cond = 0;
        PlaySound(40);
        AddScore(npc->score);
        o_x = npc->x;
        o_y = npc->y;
        if ((npc->flag & 0x10) != 0)
            SubStageXOScroll(&o_x, &o_y);
        SetCaret(0, o_x, o_y, npc->score);
        SetCaret(0, o_x, o_y - 0x2000, 10);
        SetCaret(1, o_x, o_y, 0);
        goto LABEL_33;
    default:
        if (ship.shock)
            goto LABEL_33;

        if ((npc->flag & 1) != 0 && (npc->flag & 8) == 0)
            DamageNpChar(npc, ship.damage);

        ship.life -= npc->damage;
        ship.shock = 150;
        CreateEntity(1, ship.x, ship.y, 0);
        SetGameDelay(20);
        if (ship.life >= 1)
        {
            PlaySound(34);
        LABEL_33:
            return TRUE;
        }
        else
        {
            ShipCrushProc();
            return FALSE;
        }
    }
}

//----- (00416540) --------------------------------------------------------
void LoadPximgPlayerInit()
{
    LoadPximg("player", 0);
    LoadPximg("shield", 1);

    ShipSpeedTable[0] = 0x400;
    ShipSpeedTableDiag[0] = 0x300;
    ShipSpeedTable[1] = 0x600;
    ShipSpeedTableDiag[1] = 0x480;
    ShipSpeedTable[2] = 0x800;
    ShipSpeedTableDiag[2] = 0x600;
    ShipSpeedTable[3] = 0xA00;
    ShipSpeedTableDiag[3] = 0x780;
    ShipSpeedTable[4] = 0xC00;
    ShipSpeedTableDiag[4] = 0x900;
    
    ResetShip();
}

//----- (004165D0) --------------------------------------------------------
void ActShipState(TriggerStruct *trig)
{
    ship.cond &= 0xFFFFFF0F;
    
    ++ShipThrusterFrame;
    ++ShipIFrameFlash;

    if (ship.shock)
        --ship.shock;
    
    if (ship.rot1)
        --ship.rot1;
    
    if ((ship.cond & 2) != 0)
    {
        ship.cond = 0;
        ship.state = 200;
    }
    else if (ship.state > 200)
    {
        if (ship.state == 300)
        {
            ActShipFlightExit();
        }
        else if (ship.state == 900)
        {
            ShipStateEndingProc();
        }
    }
    else if (ship.state == 200)
    {
        KillShip();
    }
    else if (ship.state)
    {
        if (ship.state == 100)
            ActPlayerInput(trig);
    }
    else
    {
        ActShipFlightIntro();
    }
}

//----- (004166C0) --------------------------------------------------------
void ActShipFlightIntro()
{
    ship.y -= 0x300;

    if ((double)++ship.count1 <= 75.0)
    {
        if (ship.count1 % 2 == 1)
            CreateEntity(4, ship.x, ship.y + ((4 * (ship.count1 % 4 / 2) + 4) << 10), 0);
    }
    else
    {
        ship.count1 = 0;
        ship.state = 100;
        ship.shock = 0;
        ship.flag |= 4u;
        ship.xm = ship.x;
        ship.ym = ship.y;
        if (ship.life > 3)
        {
            ship.life -= 3;
            ship.cond |= 4u;
        }
        if ((ship.cond & 4) != 0)
        {
            CreateBullet(5, ship.x, ship.y, 0, 100, 1);
            CreateBullet(5, ship.x, ship.y, 1, 101, 1);
        }
    }
}

//----- (00416800) --------------------------------------------------------
void ActShipFlightExit()
{
    if (ship.child)
    {
        if (ship.child != 1)
            return;
        goto LABEL_14;
    }
    if (ship.x < 0xEC00)
        ship.x += 0x400;
    if (ship.x > 0xF400)
        ship.x -= 0x400;
    if (ship.y < 0x1BC00)
        ship.y += 0x400;
    if (ship.y > 0x1C400)
        ship.y -= 0x400;
    if (++ship.count1 >= 100)
    {
        ship.child = 1;
        ship.count1 = 0;
        ship.ym = 0x400;
        PlaySound(35);
    LABEL_14:
        ++ship.count1;
        ship.ym -= 0xAA;
        ship.y += ship.ym;
        if (ship.count1 % 2 == 1)
            CreateEntity(4, ship.x, ship.y + ((4 * (ship.count1 % 4 / 2) + 4) << 10), 0);
    }
}

//----- (00416960) --------------------------------------------------------
void ActPlayerInput(TriggerStruct *trig)
{
    switch (GetPlayerInput(trig->hold))
    {
    case 1:
        ship.x -= ShipSpeedTable[ShipSpeed];
        break;
    case 2:
        ship.x += ShipSpeedTable[ShipSpeed];
        break;
    case 3:
        ship.y -= ShipSpeedTable[ShipSpeed];
        break;
    case 4:
        ship.y += ShipSpeedTable[ShipSpeed];
        break;
    case 5:
        ship.x -= ShipSpeedTableDiag[ShipSpeed];
        ship.y -= ShipSpeedTableDiag[ShipSpeed];
        break;
    case 6:
        ship.x += ShipSpeedTableDiag[ShipSpeed];
        ship.y -= ShipSpeedTableDiag[ShipSpeed];
        break;
    case 7:
        ship.x -= ShipSpeedTableDiag[ShipSpeed];
        ship.y += ShipSpeedTableDiag[ShipSpeed];
        break;
    case 8:
        ship.x += ShipSpeedTableDiag[ShipSpeed];
        ship.y += ShipSpeedTableDiag[ShipSpeed];
        break;
    default:
        break;
    }
    if (ship.x < 0)
        ship.x = 0;
    if (ship.x > 0x1E000)
        ship.x = 0x1E000;
    if (ship.y < 0)
        ship.y = 0;
    if (ship.y > 0x28000)
        ship.y = 0x28000;
    if ((trig->hold & 1) != 0)
    {
        switch (ShipPowerup)
        {
        case 0:
            ShootBullet0();
            break;
        case 1:
            ShootBullet1();
            break;
        case 2:
            ShootBullet2();
            break;
        case 3:
            ShootBullet3();
            break;
        case 4:
            ShootBullet4();
            break;
        case 5:
            ShootBullet5();
            break;
        case 6:
            ShootBullet6();
            break;
        case 7:
            ShootBullet7();
            break;
        case 8:
            ShootBullet8();
            break;
        case 9:
            ShootBullet9(trig);
            break;
        case 10:
            ShootBullet10();
            break;
        case 11:
            ShootBullet11();
            break;
        default:
            break;
        }
    }
    else
    {
        fireHeldFrames = 0;
    }
    if ((ship.cond & 2) != 0)
        ship.state = 200;
}

//----- (00416C10) --------------------------------------------------------
void ShootBullet0()
{
    if (!(fireHeldFrames++ % 0x18u))
    {
        if (CreateBullet(0, ship.x, ship.y, 0, 0, 2))
            PlaySound(0);
    }
}

//----- (00416C70) --------------------------------------------------------
void ShootBullet1()
{
    BOOL v1; // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(2, ship.x - 0x2000, ship.y + 2048, 0, 0, 2);
        if (v1 + CreateBullet(2, ship.x + 0x2000, ship.y + 2048, 0, 1, 2))
            PlaySound(1);
    }
}

//----- (00416D10) --------------------------------------------------------
void ShootBullet2()
{
    int x; // [esp+0h] [ebp-Ch]

    if (!(fireHeldFrames++ % 4u))
    {
        if ((fireHeldFrames >> 2) % 2)
            x = ship.x - 1024;
        else
            x = ship.x + 1024;

        if (CreateBullet(1, x, ship.y, 0, 0, 6))
            PlaySound(2);
    }
}

//----- (00416DB0) --------------------------------------------------------
void ShootBullet3()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(0, ship.x, ship.y, 0, 0, 3);
        v2 = v1 + CreateBullet(2, ship.x + 3072, ship.y, 6, 1, 3);
        if (v2 + CreateBullet(2, ship.x - 4096, ship.y, 10, 2, 3))
            PlaySound(3);
    }
}

//----- (00416E70) --------------------------------------------------------
void ShootBullet4()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(0, ship.x, ship.y, 0, 0, 3);
        v2 = v1 + CreateBullet(2, ship.x - 5120, ship.y, 8, 1, 3);
        if (v2 + CreateBullet(2, ship.x + 5120, ship.y, 8, 2, 3))
            PlaySound(4);
    }
}

//----- (00416F30) --------------------------------------------------------
void ShootBullet5()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(0, ship.x, ship.y, 0, 0, 3);
        v2 = v1 + CreateBullet(2, ship.x + 5120, ship.y, 2, 2, 3);
        if (v2 + CreateBullet(2, ship.x - 6144, ship.y, 14, 3, 3))
            PlaySound(5);
    }
}

//----- (00416FF0) --------------------------------------------------------
void ShootBullet6()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(2, ship.x, ship.y - 3072, 0, 0, 2);
        v2 = v1 + CreateBullet(2, ship.x - 9216, ship.y + 3072, 0, 1, 2);
        if (v2 + CreateBullet(2, ship.x + 9216, ship.y + 3072, 0, 2, 2))
            PlaySound(6);
    }
}

//----- (004170C0) --------------------------------------------------------
void ShootBullet7()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]
    int v3;  // [esp+0h] [ebp-4h]
    int v4;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 6u))
    {
        v1 = CreateBullet(2, ship.x, ship.y - 3072, 0, 0, 2);
        v2 = v1 + CreateBullet(2, ship.x - 5120, ship.y, 15, 1, 2);
        v3 = v2 + CreateBullet(2, ship.x + 4096, ship.y, 1, 2, 2);
        v4 = v3 + CreateBullet(2, ship.x + 1024, ship.y, 6, 3, 3);
        if (v4 + CreateBullet(2, ship.x - 2048, ship.y, 10, 4, 3))
            PlaySound(8);
    }
}

//----- (004171D0) --------------------------------------------------------
void ShootBullet8()
{
    BOOL v1; // [esp+0h] [ebp-4h]
    int v2;  // [esp+0h] [ebp-4h]

    if (!(fireHeldFrames++ % 8u))
    {
        v1 = CreateBullet(4, ship.x, ship.y - 1024, 0, 10, 1);
        v2 = v1 + CreateBullet(4, ship.x - 4096, ship.y + 4096, 13, 11, 1);
        if (v2 + CreateBullet(4, ship.x + 3072, ship.y + 4096, 3, 12, 1))
            PlaySound(10);
    }
}

//----- (004172A0) --------------------------------------------------------
void ShootBullet9(TriggerStruct *a1)
{
    unsigned char v2; // [esp+7h] [ebp-1h]

    if ((a1->prev & 1) != 0)
    {
        ship.xm = ship.x;
        ship.ym = ship.y;
    }
    if (!(fireHeldFrames++ % 4u))
    {
        v2 = GetArktan(ship.x - ship.xm, ship.y - ship.ym, 192);
        if (CreateBullet(6, ship.x, ship.y, v2, 0, 6))
            PlaySound(5);
    }
}

//----- (00417350) --------------------------------------------------------
void ShootBullet10()
{
    if (!(fireHeldFrames++ % 0x20u))
    {
        if (CreateBullet(7, ship.x, ship.y - 0x2000, 0, 0, 2))
            PlaySound(20);
    }
}

//----- (004173C0) --------------------------------------------------------
void ShootBullet11()
{
    int x;   // [esp+0h] [ebp-10h]
    int v2;  // [esp+4h] [ebp-Ch]
    int v3;  // [esp+8h] [ebp-8h]
    BOOL v4; // [esp+Ch] [ebp-4h]

    if (!(fireHeldFrames++ % 4u))
    {
        if ((fireHeldFrames >> 2) % 2)
        {
            x = ship.x - 6144;
            v2 = ship.x + 6144;
        }
        else
        {
            x = ship.x - 0x2000;
            v2 = ship.x + 0x2000;
        }
        v3 = ship.y + 5120;
        v4 = CreateBullet(1, x, ship.y + 4096, 0, 0, 6);
        if (v4 && CreateBullet(1, v2, v3 - 1024, 0, 1, 6))
            PlaySound(2);
    }
}

//----- (004174B0) --------------------------------------------------------
void KillShip()
{
    PlaySound(25);

    ship.count1 = 1;
    ship.state = 1000;
    ship.x = 0xF000;
    ship.y = 0x50000;
}

//----- (004174F0) --------------------------------------------------------
void ShipStateEndingProc()
{
    int child; // [esp+0h] [ebp-8h]

    child = ship.child;
    if (child)
    {
        if (child != 1)
            return;
    }
    else
    {
        ship.count1++;
        if (ship.count1 < 290)
            return;
        ship.child = 1;
    }
    ship.y += 512;
    if (ship.y >= 136192)
        ship.child = 2;
}

//----- (00417570) --------------------------------------------------------
void HitShipMap()
{
    if ((ship.cond & 1) != 0 && (ship.cond & 2) == 0)
        HitMapGeneric(&ship, MapCollideShipProc, 0);
}

//----- (004175A0) --------------------------------------------------------
void MapCollideShipProc(Object *o, int a2, int a3, int a4)
{
    o->x = a2;
    o->y = a3;
    o->cond |= a4;
    if (o->y >= 0x28000 && (o->cond & 0x40) != 0)
    {
        ship.shock = 50;
        CreateEntity(1, ship.x, ship.y, 0);
        SetGameDelay(20);
        ShipCrushProc();
    }
}

static RECT shipRectTbl[12] =
    {
        {0, 0, 24, 16},
        {0, 16, 24, 32},
        {0, 32, 24, 48},
        {0, 48, 24, 64},
        {0, 64, 24, 80},
        {0, 80, 24, 96},
        {0, 96, 24, 112},
        {0, 112, 24, 128},
        {72, 0, 96, 16},
        {72, 16, 96, 32},
        {72, 32, 96, 48},
        {72, 48, 96, 64}};

static RECT rcShip[12] =
    {
        {48, 0, 72, 16},
        {48, 16, 72, 32},
        {48, 32, 72, 48},
        {48, 48, 72, 64},
        {48, 64, 72, 80},
        {48, 80, 72, 96},
        {48, 96, 72, 112},
        {48, 112, 72, 128},
        {120, 0, 144, 16},
        {120, 16, 144, 32},
        {120, 32, 144, 48},
        {120, 48, 144, 64}};

static RECT rcThruster[10] =
    {
        {176, 56, 184, 64},
        {184, 56, 192, 64},
        {176, 64, 184, 72},
        {184, 64, 192, 72},
        {176, 72, 184, 80},
        {184, 72, 192, 80},
        {176, 80, 184, 88},
        {184, 80, 192, 88},
        {168, 80, 176, 88},
        {112, 72, 120, 80}};

//----- (00417610) --------------------------------------------------------
void PutPlayerExtra(RECT *rcView)
{
    RECT v1; // [esp+0h] [ebp-A8h] BYREF
    RECT rcShipThruster[8] = {
        {0, 0, 24, 24},
        {24, 0, 48, 24},
        {48, 0, 72, 24},
        {72, 0, 96, 24},
        {96, 0, 120, 24},
        {120, 0, 144, 24},
        {144, 0, 168, 24},
        {168, 0, 192, 24},
    };
    RECT rect; // [esp+90h] [ebp-18h] BYREF
    int a4;    // [esp+A0h] [ebp-8h]
    int a3;    // [esp+A4h] [ebp-4h]

    ship.rect = shipRectTbl[ShipPowerup];
    if (ship.shock && ShipIFrameFlash / 2 % 2)
    {
        ship.rect.left += 24;
        ship.rect.right += 24;
    }

    a3 = GetStageXOffset() / 1024;
    a4 = GetStageScroll() / 1024;

    PutObject(rcView, &ship, a3, a4);
    PutBitmap3(
        rcView,
        (ship.x - 4096) / 1024,
        (ship.y + 4096) / 1024,
        &rcThruster[2 * ShipSpeed + ShipThrusterFrame / 2 % 2],
        7);

    if (ship.life > 1)
    {
        rect = rcShipThruster[ShipThrusterFrame / 2 % 8];
        if (ship.life == 3)
        {
            rect.top += 24;
            rect.bottom += 24;
        }
        PutBitmap3(rcView, (ship.x - 0x3000) / 0x400, (ship.y - 0x3000) / 0x400, &rect, 1);
    }

    if (ship.state == 100 && ShipPowerup == 9)
    {
        if (fireHeldFrames % 2u)
        {
            v1.left = 72;
            v1.top = 0;
            v1.right = 88;
            v1.bottom = 16;

            PutBitmap3(rcView, (ship.xm - 0x2000) / 0x400, (ship.ym - 0x2000) / 0x400, &v1, 2);
        }
    }
}

//----- (00417960) --------------------------------------------------------
void PutPlayer(RECT *rcView)
{
    if ((ship.flag & 0x100) == 0)
        return;

    PutBitmap3(rcView, (ship.x - 0x2000) / 1024, (ship.y - 4096) / 1024, &rcShip[ShipPowerup], 0);
}

//----- (004179D0) --------------------------------------------------------
void GetShipPos(int *pos_x, int *pos_y)
{
    if (pos_x)
        *pos_x = ship.x;

    if (pos_y)
        *pos_y = ship.y;
}

//----- (00417A00) --------------------------------------------------------
int SetSpeedPowerUp()
{
    if (++ShipSpeed < 5)
        return 1;
    ShipSpeed = 1;
    return 0;
}

//----- (00417A30) --------------------------------------------------------
int SetLifePowerUp()
{
    if ((ship.cond & 4) != 0)
    {
        if (ship.life >= 2)
            return 0;
        ++ship.life;
    }
    else if (++ship.life > 3)
    {
        ship.life = 1;
        ship.cond |= 4u;
        CreateBullet(5, ship.x, ship.y, 0, 100, 1);
        CreateBullet(5, ship.x, ship.y, 1, 101, 1);
    }
    return 1;
}

//----- (00417AD0) --------------------------------------------------------
void SetSpeed(int speed)
{
    ShipSpeed = speed % 5;
}

//----- (00417AF0) --------------------------------------------------------
int GetShipSpeed()
{
    return ShipSpeed;
}

//----- (00417B00) --------------------------------------------------------
void SetPowerUp(int power_up)
{
    ShipPowerup = power_up;
}

//----- (00417B10) --------------------------------------------------------
void SetShipBoost()
{
    ship.state = 300;
    ship.child = 0;
    ship.count1 = 0;
}

//----- (00417B40) --------------------------------------------------------
void SetLife(int life)
{
    ship.life = life;
}

//----- (00417B50) --------------------------------------------------------
void SetShipInvincibility()
{
    ship.shock = 60000;
}

//----- (00417B60) --------------------------------------------------------
void SetShipEnding()
{
    ship.state = 900;
    ship.count1 = 0;
    ship.child = 0;
    ship.x = 61440;
    ship.y = 81920;
    ship.shock = 0;
}

//----- (00417BB0) --------------------------------------------------------
int LoadPximgCharactor()
{
    return LoadPximg("charactor", 9);
}