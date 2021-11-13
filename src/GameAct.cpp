#include <windows.h>

#include "GameAct.h"
#include "Bullet.h"
#include "Caret.h"
#include "Draw.h"
#include "Event.h"
#include "Fade.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "Map.h"
#include "Object.h"
#include "PlayRecord.h"
#include "Ship.h"
#include "Sound.h"
#include "Stage.h"
#include "WinMain.h"

int PauseLoop(HWND a1, TriggerStruct *a2);

//----- (0041B470) --------------------------------------------------------
int ModeAction(HWND a1)
{
    int v1;            // eax
    int v3;            // [esp-8h] [ebp-30h]
    int v4;            // [esp-4h] [ebp-2Ch]
    TriggerStruct v5;  // [esp+0h] [ebp-28h] BYREF
    TriggerStruct *v6; // [esp+Ch] [ebp-1Ch]
    int v7;            // [esp+10h] [ebp-18h]
    TriggerStruct a1a; // [esp+14h] [ebp-14h] BYREF
    int a2;            // [esp+20h] [ebp-8h]
    char v10;          // [esp+27h] [ebp-1h]

    v10 = 0;
    a2 = GetSurfaceColor(16);
    
    if (GameStart())
    {
        SetSoundDisabled(0);
        ClearTrg_(&a1a);
        ClearTrg_(&v5);
        if (GetInReplay())
        {
            ZeroPlayRecord();
            v6 = &v5;
        }
        else
        {
            NewPlayRecord();
            v6 = &a1a;
        }
        
        InitStage();
        while (1)
        {
            
            ++v10;
            if (Call_Escape())
            {
                v7 = 0;
                goto LABEL_27;
            }
            if (GetGameReset())
            {
                v7 = 1;
                goto LABEL_27;
            }
            
            Input_UpdateTriggers();
            a1a.hold = GetTrg();
            if (GetInReplay())
            {
                v5.hold = ActPlayRecord();
                UpdateTrg(&v5);
            }
            else
            {
                RecordPlayRecord(a1a.hold);
            }
            
            UpdateTrg(&a1a);
            if (GetInReplay() && (a1a.hold & 1) != 0)
                SetReset(1);
            v7 = PauseLoop(a1, &a1a);
            if (v7 != 2)
                goto LABEL_27;
            v7 = ActStageState(&a1a);
            if (v7 != 2)
                goto LABEL_27;
            
            if (!GetGameDelayed())
            {
                SetStageEntities();
                ActStageScroll();
                ActNpc();
                ActShipState(v6);
                ActBullet();
                ActCaret();
                HitNpCharBullet();
                HitShipPowerup();
                HitShipMap();
                HitEntityMap();
                HitBulletMap();
                ActFade();
            }
            
            if (!GetInReplay() || (a1a.hold & 0x40) == 0 || (v10 & 0xF) == 0)
            {
                PutBackground(&scWOffset_0, a2);
                PutNpChar(&scWOffset_0);
                PutMapParts(&scWOffset_0);
                PutPlayer(&scWOffset_0);
                PutNpChar2(&scWOffset_0);
                PutPlayerExtra(&scWOffset_0);
                PutBullet(&scWOffset_0);
                PutMapParts2(&scWOffset_0);
                PutCaret(&scWOffset_0);
                PutFade(&scWOffset_0);
                PutHUD(&scWOffset_0);
                PutFramePerSecond();
                if (!Flip_SystemTask())
                    break;
            }
            
        }
        v7 = 0;
    }
    else
    {
        v7 = 0;
    }
LABEL_27:
    
    if (!GetInReplay())
    {
        EndPlayRecord();
        v4 = GetScore();
        v3 = GetCurrentStage();
        v1 = GetInScoreAttack();
        WritePlayRecord(v1, v3, v4);
    }
    StopLoopSound(32);
    return v7;
}

//----- (0041B730) --------------------------------------------------------
int PauseLoop(HWND a1, TriggerStruct *a2)
{
    return 2;
}