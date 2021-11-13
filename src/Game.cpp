#include <windows.h>
#include <stdio.h>

#include "Game.h"
#include "Draw.h"
#include "Sound.h"
#include "Text.h"
#include "WinMain.h"

BOOL g_FullScreenEnabled = FALSE;
BOOL GameFocussed = FALSE;
int magnification = 1;

//----- (00419F00) --------------------------------------------------------
BOOL LoadGenericData()
{
    BOOL result = FALSE;

    if (!LoadPximg("color1", 16))
        goto err;
    if (!LoadPximg("color2", 17))
        goto err;
    if (!LoadPximg("color3", 18))
        goto err;
    if (!LoadPximg("color4", 19))
        goto err;
    if (!LoadPximg("color5", 20))
        goto err;
    if (!LoadPximg("escape", 22))
        goto err;
    if (!InitSurface(120, 160, 23, TRUE))
        goto err;
    if (!LoadSound("beem_normal", 0))
        goto err;
    if (!LoadSound("beem_twin", 1))
        goto err;
    if (!LoadSound("beem_machine", 2))
        goto err;
    if (!LoadSound("beem_triangle", 3))
        goto err;
    if (!LoadSound("beem_back", 4))
        goto err;
    if (!LoadSound("beem_wide", 5))
        goto err;
    if (!LoadSound("beem_3line", 6))
        goto err;
    if (!LoadSound("beem_Star", 8))
        goto err;
    if (!LoadSound("beem_enemy", 7))
        goto err;
    if (!LoadSound("beem_ray1", 9))
        goto err;
    if (!LoadSound("beem_ray2", 10))
        goto err;
    if (!LoadSound("destroy1", 11))
        goto err;
    if (!LoadSound("destroy2", 12))
        goto err;
    if (!LoadSound("destroy3", 13))
        goto err;
    if (!LoadSound("destroy4", 14))
        goto err;
    if (!LoadSound("destroy5", 15))
        goto err;
    if (!LoadSound("destroy6", 16))
        goto err;
    if (!LoadSound("damage1", 17))
        goto err;
    if (!LoadSound("damage2", 18))
        goto err;
    if (!LoadSound("damage3", 19))
        goto err;
    if (!LoadSound("damage4", 20))
        goto err;
    if (!LoadSound("damage5", 21))
        goto err;
    if (!LoadSound("damage6", 22))
        goto err;
    if (!LoadSound("damage7", 23))
        goto err;
    if (!LoadSound("nodamage", 24))
        goto err;
    if (!LoadSound("dead", 25))
        goto err;
    if (!LoadSound("comein", 26))
        goto err;
    if (!LoadSound("speedup", 27))
        goto err;
    if (!LoadSound("speeddown", 28))
        goto err;
    if (!LoadSound("equip", 29))
        goto err;
    if (!LoadSound("charge1", 30))
        goto err;
    if (!LoadSound("charge2", 31))
        goto err;
    if (!LoadSound("noise1", 32))
        goto err;
    if (!LoadSound("shi_on", 33))
        goto err;
    if (!LoadSound("shi_off", 34))
        goto err;
    if (!LoadSound("jet", 35))
        goto err;
    if (!LoadSound("missile", 36))
        goto err;
    if (!LoadSound("hitblock", 37))
        goto err;
    if (!LoadSound("open", 38))
        goto err;
    if (!LoadSound("bite", 39))
        goto err;
    if (!LoadSound("bonus", 40))
        goto err;
    if (!LoadSound("oneup", 41))
        goto err;
    if (!LoadSound("ameba", 42))
        goto err;
    if (!LoadSound("check_point", 43))
        goto err;
    if (!LoadSound("pause_on", 44))
        goto err;
    if (!LoadSound("pause_off", 45))
        goto err;

    result = TRUE;
err:
    return result;
}

//----- (0041A450) --------------------------------------------------------
int Game(HWND hWnd)
{
    int v2;  // [esp+4h] [ebp-Ch]
    int ret; // [esp+8h] [ebp-8h]
    int v4;  // [esp+Ch] [ebp-4h]

    ret = 0;
    v2 = 0;
    v4 = 1;
#if 0
    InitTriangleTable();
    LoadPximgCharactor();
    ResetStage();
    SetBackgroundColor_();
    LoadPximgBullet();
    ResetCaret2();
    LoadPximgEntities();
    LoadPximgPlayerInit();
    ResetEntityStageTotal();
    LoadPximgSymbol();
    if (InitGameAttr())
    {
        ClearLoopSound();
        LoadPximgScreenEffect();
        InitPlayRecord();
        DragEnable(hWnd);
    LABEL_3:
        while (!v2)
        {
            switch (v4)
            {
            case 0:
                v2 = 1;
                break;
            case 1:
                v4 = MenuLoop();
                break;
            case 2:
                v4 = ModeAction(hWnd);
                break;
            case 3:
                v4 = RankingLoop();
                break;
            case 4:
                v4 = RankingViewLoop();
                break;
            case 5:
                v4 = KeyConfigLoop(hWnd, 0);
                break;
            case 6:
                v4 = KeyConfigLoop(hWnd, 1);
                break;
            case 7:
                v4 = ModeEnding();
                break;
            default:
                goto LABEL_3;
            }
        }
        ret = 1;
    }
    SaveWindowSettings(hWnd);
    CallClearCenterText();
    StopLoopSound2();
    FreePlayRecord();
#endif

    return ret;
}

//----- (0041A5C0) --------------------------------------------------------
BOOL LoadPximg(const char *file_name, int surf_no)
{
    char path[268]; // [esp+0h] [ebp-110h] BYREF

    sprintf(path, "%s.pximg", file_name);
    return MakeSurface_Pximg(path, surf_no, 1, 0);
}

BOOL GameReset;            // weak
int Timer1000TicksFinal;   // weak
int Timer1000TicksElapsed; // weak
int Timer1000Ticks;        // weak
int next_time;             // weak
int current_time;          // weak

//----- (0041A610) --------------------------------------------------------
int CountFramePerSecond()
{
    unsigned int tick_count; // eax

    if (TimerFirstCountFlag)
    {
        Timer1000Ticks = GetTickCount();
        TimerFirstCountFlag = FALSE;
    }
    tick_count = GetTickCount();
    ++Timer1000TicksElapsed;
    if (Timer1000Ticks + 1000 <= tick_count)
    {
        Timer1000Ticks += 1000;
        Timer1000TicksFinal = Timer1000TicksElapsed;
        Timer1000TicksElapsed = 0;
    }
    return Timer1000TicksFinal;
}

//----- (0041A690) --------------------------------------------------------
void PutFramePerSecond()
{
    RECT rect; // [esp+0h] [ebp-14h] BYREF
    int value; // [esp+10h] [ebp-4h]

    value = CountFramePerSecond();
    rect.left = 112;
    rect.top = 8;
    rect.right = 128;
    rect.bottom = 16;
    if (value == 50)
        PutBitmap3(&scWOffset_0, scWOffset_0.right - 16, 3, &rect, 11);
    else
        PutNumber(&scWOffset_0, scWOffset_0.right - 16, 3, value, 2, 0);
}

//----- (0041A710) --------------------------------------------------------
BOOL Flip_SystemTask()
{
    do
    {
        if (!PollMessages())
            return FALSE;
        Sleep(1u);
        current_time = GetTickCount();
    } while (current_time < (next_time + 20));

    if (current_time < (next_time + 100))
        next_time += 20;
    else
        next_time = current_time;

    Flip_Screen();
    return TRUE;
}

//----- (0041A790) --------------------------------------------------------
void SetReset(BOOL reset)
{
    GameReset = reset;
}
// 44C49C: using guessed type int GameReset;

//----- (0041A7A0) --------------------------------------------------------
BOOL GetGameReset()
{
    return GameReset;
}
