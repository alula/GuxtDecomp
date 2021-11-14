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
int PauseLoop(HWND hWnd, TriggerStruct *trig)
{
    TriggerStruct v3;  // [esp+0h] [ebp-30h]
    TriggerStruct a1a; // [esp+Ch] [ebp-24h] BYREF
    int v5;            // [esp+18h] [ebp-18h]
    unsigned int v6;   // [esp+1Ch] [ebp-14h]
    RECT rect;         // [esp+20h] [ebp-10h] BYREF

    v6 = 0;
    if ((trig->prev & 2) == 0)
        return 2;
    v3 = *trig;
    rect.left = 64;
    rect.top = 48;
    rect.right = 104;
    rect.bottom = 56;
    SetReset(0);
    ClearTrg_(&a1a);
    PutBitmapPause_(23);
    PlaySound(44);
    while (1)
    {
        ++v6;
        if (Call_Escape())
        {
            v5 = 0;
            goto LABEL_14;
        }
        if (GetGameReset())
        {
            v5 = 1;
            goto LABEL_14;
        }
        a1a.hold = GetTrg();
        UpdateTrg(&a1a);
        if (v6 > 20 && (a1a.prev & 2) != 0)
            break;
        PutRect(0, 0, &scWOffset_0, 23);
        PutRect(2, 2, &rect, 11);
        if (!Flip_SystemTask())
            return 0;
    }
    v5 = 2;
    PlaySound(45);
LABEL_14:
    *trig = v3;
    return v5;
}