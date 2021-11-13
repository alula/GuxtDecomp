#include <windows.h>

#include "Ship.h"

Ship ship;
int ShipUnused = 0;
int ShipUnused2 = 0;
int ShipSpeed = 0;
int ShipPowerup = 0;

Ship *GetShip()
{
    return &ship;
}

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