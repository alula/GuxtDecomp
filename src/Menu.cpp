#include <windows.h>
#include <stdio.h>

#include "Menu.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "PlayRecord.h"
#include "Sound.h"
#include "Text.h"
#include "WinDebugDrag.h"
#include "WinMain.h"

//----- (0041C6F0) --------------------------------------------------------
static int GetCompileVersion(int *a, int *b, int *c, int *d)
{
    unsigned int puLen;         // [esp+0h] [ebp-134h] BYREF
    char Filename[MAX_PATH];    // [esp+4h] [ebp-130h] BYREF
    VS_FIXEDFILEINFO *lpBuffer; // [esp+114h] [ebp-20h] BYREF
    DWORD dwHandle;             // [esp+118h] [ebp-1Ch] BYREF
    DWORD dwLen;                // [esp+11Ch] [ebp-18h]
    int version[4];             // [esp+120h] [ebp-14h] BYREF
    LPVOID lpData;              // [esp+130h] [ebp-4h]

    lpData = 0;
    memset(version, 0, sizeof(version));

    if (a)
        *a = 0;
    if (b)
        *b = 0;
    if (c)
        *c = 0;
    if (d)
        *d = 0;

    GetModuleFileNameA(0, Filename, sizeof(Filename));

    dwLen = GetFileVersionInfoSizeA(Filename, &dwHandle);
    if (dwLen)
    {
        lpData = malloc(dwLen);
        if (lpData)
        {
            if (GetFileVersionInfoA(Filename, 0, dwLen, lpData) && VerQueryValueA(lpData, "\\", (void **)&lpBuffer, &puLen))
            {
                version[0] = HIWORD(lpBuffer->dwFileVersionMS);
                version[1] = lpBuffer->dwFileVersionMS;
                version[2] = HIWORD(lpBuffer->dwFileVersionLS);
                version[3] = lpBuffer->dwFileVersionLS;
                if (a)
                    *a = version[0];
                if (b)
                    *b = version[1];
                if (c)
                    *c = version[2];
                if (d)
                    *d = version[3];
            }
        }
    }
    if (lpData)
        free(lpData);
    return 10 * version[2] + version[3] + 100 * version[1] + 1000 * version[0];
}

//----- (0041C8A0) --------------------------------------------------------
int MenuLoop()
{
    int a1;                    // [esp+4h] [ebp-E4h] BYREF
    int b;                     // [esp+8h] [ebp-E0h] BYREF
    int d;                     // [esp+Ch] [ebp-DCh] BYREF
    int a;                     // [esp+10h] [ebp-D8h] BYREF
    int c;                     // [esp+14h] [ebp-D4h] BYREF
    RECT rc2;                  // [esp+18h] [ebp-D0h] BYREF
    unsigned char cursor_anim; // [esp+2Bh] [ebp-BDh]
    RECT rc4[2];               // [esp+2Ch] [ebp-BCh] BYREF
    TriggerStruct trig;        // [esp+4Ch] [ebp-9Ch] BYREF
    int game_cleared;          // [esp+58h] [ebp-90h]
    RECT rc5[2];               // [esp+5Ch] [ebp-8Ch] BYREF
    int v13;                   // [esp+7Ch] [ebp-6Ch]
    RECT rc6;                  // [esp+80h] [ebp-68h] BYREF
    RECT rcCursor[2];          // [esp+90h] [ebp-58h] BYREF
    unsigned int color;        // [esp+B0h] [ebp-38h]
    RECT rc1;                  // [esp+B4h] [ebp-34h] BYREF
    int curSel;                // [esp+C4h] [ebp-24h]
    char version[12];          // [esp+C8h] [ebp-20h] BYREF
    RECT rc3;                  // [esp+D8h] [ebp-10h] BYREF

    cursor_anim = 0;
    curSel = 0;
    v13 = 1;
    game_cleared = FALSE;
    rc3.left = 0;
    rc3.top = 88;
    rc3.right = 64;
    rc3.bottom = 96;
    rc5[0].left = 64;
    rc5[0].top = 56;
    rc5[0].right = 112;
    rc5[0].bottom = 64;
    rc5[1].left = 35;
    rc5[1].top = 8;
    rc5[1].right = 80;
    rc5[1].bottom = 16;
    rc4[0].left = 0;
    rc4[0].top = 96;
    rc4[0].right = 80;
    rc4[0].bottom = 104;
    rc4[1].left = 0;
    rc4[1].top = 104;
    rc4[1].right = 80;
    rc4[1].bottom = 112;
    rc6.left = 0;
    rc6.top = 0;
    rc6.right = 64;
    rc6.bottom = 8;
    rc1.left = 0;
    rc1.top = 0;
    rc1.right = 120;
    rc1.bottom = 32;
    rc2.left = 0;
    rc2.top = 32;
    rc2.right = 120;
    rc2.bottom = 40;
    rcCursor[0].left = 112;
    rcCursor[0].top = 0;
    rcCursor[0].right = 120;
    rcCursor[0].bottom = 8;
    rcCursor[1].left = 120;
    rcCursor[1].top = 0;
    rcCursor[1].right = 128;
    rcCursor[1].bottom = 8;
    GetCompileVersion(&a, &b, &c, &d);
    sprintf(version, "v.%d.%d%d%d", a, b, c, d);
    color = GetSurfaceColor(17);
    SetSoundDisabled(0);
    ResetScore();
    SetReset(0);
    LoadButtonConfig();
    ClearTrg_(&trig);
    if (GetGameCleared())
    {
        curSel = 1;
        game_cleared = 1;
    }
    LoadPximg("title", 21);
    ChangeMusic(1);
    InitDragFile();
    while (1)
    {
        if (Call_Escape())
        {
            v13 = 0;
            goto end;
        }
        if (GetGameReset())
        {
            v13 = 1;
            goto end;
        }
        trig.hold = GetTrg();
        UpdateTrg(&trig);
        if ((trig.prev & 1) != 0)
        {
            switch (curSel)
            {
            case 0:
                SetInScoreAttack(0);
                SetInReplay(0);
                v13 = 2;
                PlaySound(33);
                break;
            case 1:
                if (!game_cleared)
                    goto skip_1;
                SetInScoreAttack(1);
                SetInReplay(0);
                v13 = 2;
                PlaySound(33);
                break;
            case 2:
                if (game_cleared)
                {
                    v13 = 4;
                    PlaySound(33);
                }
                else
                {
                skip_1:
                    PlaySound(19);
                }
                break;
            case 3:
                if (GetKeyHeld())
                    v13 = 5;
                else
                    v13 = 6;
                PlaySound(33);
                break;
            default:
                break;
            }
            if (v13 != 1)
                break;
        }
        if (CheckDragFile())
        {

            if (ReadPlayRecord(GetDragFile(), &a1))
            {
                SetInScoreAttack(a1);
                SetInReplay(1);
                v13 = 2;
                break;
            }
        }
        if ((trig.prev & 0x80) != 0)
        {
            ++curSel;
            PlaySound(2);
        }
        if ((trig.prev & 0x40) != 0)
        {
            --curSel;
            PlaySound(2);
        }
        if (curSel < 0)
            curSel = 3;
        if (curSel > 3)
            curSel = 0;
        ++cursor_anim;
        PutBackground(&scWOffset_0, color);
        PutRect(0, 24, &rc1, 21);
        PutRect(0, 144, &rc2, 21);
        PutRect(28, 88, &rc3, 11);
        PutRect(28, 100, &rc4[game_cleared], 11);
        PutRect(28, 112, &rc5[game_cleared], 11);
        PutRect(28, 124, &rc6, 11);
        PutRect(16, 12 * curSel + 88, &rcCursor[cursor_anim / 8 % 2], 11);
        PutTextObject(&scWOffset_0, 60, 64, version, 16, 0);
        PutFramePerSecond();
        if (!Flip_SystemTask())
        {
            v13 = 0;
            goto end;
        }
    }
    Sleep(500u);
end:
    InitDragFile();
    return v13;
}