#include <windows.h>

#include "Ship.h"
#include "Draw.h"
#include "Game.h"
#include "Sound.h"

int ShipSpeedTableDiag[5];
int ShipSpeedTable[5];
int ShipSpeed;
Ship ship;
int ShipUnused;
int ShipUnused2;
char ShipThrusterFrame;
char ShipIFrameFlash;
int fireHeldFrames;
int ShipPowerup;

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
