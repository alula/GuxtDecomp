#include <windows.h>

#include "KeyConfig.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "Sound.h"
#include "Text.h"
#include "WinMain.h"

char buttonConfigCount;
unsigned char byte_44C4B5;
TriggerStruct keyConfigTriggerStruct;
char byte_44C4C4;

BOOL ConfigKey(ButtonConfig *conf);
BOOL ConfigJoystick(ButtonConfig *conf);
void PutKeyConfig(RECT *rcView, ButtonConfigIdx *a2, BOOL is_joystick, int a4);

//----- (0041A8A0) --------------------------------------------------------
int KeyConfigLoop(HWND hWnd, int is_joystick)
{
    int result;       // [esp+0h] [ebp-18h]
    BOOL v4;          // [esp+4h] [ebp-14h]
    ButtonConfig a1a; // [esp+8h] [ebp-10h] BYREF
    int a2;           // [esp+14h] [ebp-4h]

    SetSoundDisabled(0);
    ChangeMusic(0);
    if (!LoadPximg("keycode", 13))
        return FALSE;
    if (!ReadButtonConfig(&a1a))
        ResetButtonConfig(&a1a);
    a2 = GetSurfaceColor(17);
    Input_Reset();
    memset(&keyConfigTriggerStruct, 0, sizeof(keyConfigTriggerStruct));
    buttonConfigCount = 0;
    do
    {
        v4 = FALSE;
        Input_UpdateTriggers();
        if (Input_IsTrig(VK_ESCAPE) || GetGameReset())
        {
            result = 1;
            goto LABEL_22;
        }
        if (!Input_IsTrig(VK_F1) && !Input_IsTrig(VK_F2))
        {
            if (is_joystick)
            {
                if (ConfigJoystick(&a1a))
                    v4 = TRUE;
            }
            else if (ConfigKey(&a1a))
            {
                v4 = TRUE;
            }
        }
        PutBackground(&scWOffset_0, a2);
        PutKeyConfig(&scWOffset_0, reinterpret_cast<ButtonConfigIdx *>(&a1a), is_joystick, v4);
        PutFramePerSecond();
        if (!Flip_SystemTask())
        {
            result = 0;
            goto LABEL_22;
        }
    } while (!v4);
    result = 1;
    WriteButtonConfig(&a1a);
    Sleep(500u);
LABEL_22:
    ClearSurface(13);
    return result;
}

//----- (0041AA40) --------------------------------------------------------
BOOL ConfigKey(ButtonConfig *conf)
{
    int i; // [esp+0h] [ebp-8h]
    int j; // [esp+4h] [ebp-4h]

    ++byte_44C4B5;
    for (i = 0; i < 256 && !Input_IsTrig(i); ++i)
        ;
    if (i == 256)
        return FALSE;
    for (j = 0; j < buttonConfigCount && reinterpret_cast<ButtonConfigIdx *>(conf)->btns[j] != i; ++j)
        ;
    if (j < buttonConfigCount)
    {
        buttonConfigCount = 0;
        PlaySound(34);
        ResetKeyboardConfig(conf);
        return FALSE;
    }

    reinterpret_cast<ButtonConfigIdx *>(conf)->btns[buttonConfigCount] = i;

    if (buttonConfigCount >= 5u)
    {
        PlaySound(33);
        return TRUE;
    }
    else
    {
        ++buttonConfigCount;
        PlaySound(2);
        return FALSE;
    }
}

//----- (0041AB40) --------------------------------------------------------
BOOL ConfigJoystick(ButtonConfig *conf)
{
    int i;                    // [esp+0h] [ebp-1Ch]
    DirectInputProcStruct a1; // [esp+4h] [ebp-18h] BYREF
    int j;                    // [esp+18h] [ebp-4h]

    ++byte_44C4B5;
    if (!DirectInputProc(&a1))
        return FALSE;

    keyConfigTriggerStruct.hold = a1.extraBtns;
    UpdateTrg(&keyConfigTriggerStruct);

    for (i = 0; i < 32 && (keyConfigTriggerStruct.prev & (1u << i)) == 0; ++i)
        ;
    if (i == 32)
        return FALSE;
    for (j = 0; j < buttonConfigCount && reinterpret_cast<ButtonConfigIdx *>(conf)->btns[6 + j] != i; ++j)
        ;

    if (j < buttonConfigCount)
    {
        buttonConfigCount = 0;
        PlaySound(34);
        ResetJoystickConfig(conf);
        return FALSE;
    }

    reinterpret_cast<ButtonConfigIdx *>(conf)->btns[6 + buttonConfigCount] = i;

    if (buttonConfigCount)
    {
        PlaySound(33);
        return TRUE;
    }
    else
    {
        ++buttonConfigCount;
        PlaySound(2);
        return FALSE;
    }
}

void PutKeyConfig(RECT *rcView, ButtonConfigIdx *a2, int is_joystick, BOOL a4)
{
    RECT rcCursor[2]; // [esp+0h] [ebp-84h] BYREF
    RECT v5;          // [esp+20h] [ebp-64h] BYREF
    RECT v6[2];       // [esp+30h] [ebp-54h] BYREF
    RECT v7;          // [esp+50h] [ebp-34h] BYREF
    int i;            // [esp+60h] [ebp-24h]
    RECT rcTmp;       // [esp+64h] [ebp-20h] BYREF
    RECT rect;        // [esp+74h] [ebp-10h] BYREF

    rect.left = 0;
    rect.top = 0;
    rect.right = 64;
    rect.bottom = 8;
    v5.left = 64;
    v5.top = 40;
    v5.right = 128;
    v5.bottom = 48;
    v7.left = 64;
    v7.top = 32;
    v7.right = 128;
    v7.bottom = 40;
    v6[0].left = 0;
    v6[0].top = 32;
    v6[0].right = 64;
    v6[0].bottom = 80;
    v6[1].left = 0;
    v6[1].top = 64;
    v6[1].right = 64;
    v6[1].bottom = 80;
    rcCursor[0].left = 104;
    rcCursor[0].top = 24;
    rcCursor[0].right = 112;
    rcCursor[0].bottom = 32;
    rcCursor[1].left = 0;
    rcCursor[1].top = 0;
    rcCursor[1].right = 0;
    rcCursor[1].bottom = 0;
    PutBitmap3(rcView, 30, 8, &rect, 11);
    PutBitmap3(rcView, 30, 32, &v6[is_joystick != 0], 11);
    PutBitmap3(rcView, 78, 8 * buttonConfigCount + 32, &rcCursor[(byte_44C4B5 / 4) % 2], 11);
    if (a4)
        PutBitmap3(rcView, 30, 136, &v7, 11);
    else
        PutBitmap3(rcView, 30, 136, &v5, 11);
    if (is_joystick)
    {
        for (i = 0; i < 2; ++i)
            PutNumber(rcView, 78, 8 * i + 32, a2->btns[i + 6] + 1, 1, 0);
    }
    else
    {
        for (i = 0; i < 6; ++i)
        {
            rcTmp.left = 8 * (a2->btns[i] & 0xF);
            rcTmp.top = 8 * (a2->btns[i] / 16);
            rcTmp.right = rcTmp.left + 8;
            rcTmp.bottom = rcTmp.top + 8;
            PutBitmap3(rcView, 78, 8 * i + 32, &rcTmp, 13);
        }
    }
}