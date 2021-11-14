#ifndef __SHIP_H__
#define __SHIP_H__

#include <windows.h>

#include "Input.h"
#include "Object.h"

typedef Object Ship;

extern Ship ship;

Ship *GetShip();
void ResetShip();
void SetInitialShipValues();
void ShipCrushProc();
BOOL ActPowerUp(Object *npc);
void LoadPximgPlayerInit();
void ActShipState(TriggerStruct *trig);
void ActShipFlightIntro();
void ActShipFlightExit();
void ActPlayerInput(TriggerStruct *trig);

void KillShip();
void ShipStateEndingProc();
void HitShipMap();
void MapCollideShipProc(Object *o, int a2, int a3, int a4);
void PutPlayerExtra(RECT *rcView);
void PutPlayer(RECT *rcView);
void GetShipPos(int *pos_x, int *pos_y);
int SetSpeedPowerUp();
int SetLifePowerUp();
void SetSpeed(int speed);
int GetShipSpeed();
void SetPowerUp(int power_up);
void SetShipBoost();
void SetLife(int life);
void SetShipInvincibility();
void SetShipEnding();
int LoadPximgCharactor();

#endif