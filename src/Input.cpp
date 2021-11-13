#include <windows.h>
#include <dinput.h>
#include <stdio.h>

#include "Input.h"
#include "WinMain.h"

struct SomeWeirdInputStruct
{
    LPDIRECTINPUTA dinput;
    IDirectInputDevice2A *did2;
};

static const char *ButtonConfigFile = "buttons.bin";
ButtonConfig g_KeyMap = {0, 0, 0, 0, 0, 0, 0, 0};
static int isKeyHeld = 0;

//----- (00401130) --------------------------------------------------------
void ResetKeyboardConfig(ButtonConfig *a1)
{
    a1->left = VK_LEFT;
    a1->right = VK_RIGHT;
    a1->up = VK_UP;
    a1->down = VK_DOWN;
    a1->shot = VK_CONTROL;
    a1->pause = VK_TAB;
}

//----- (00401160) --------------------------------------------------------
void ResetJoystickConfig(ButtonConfig *a1)
{
    a1->joyShot = 0;
    a1->joyPause = 1;
}

//----- (00401180) --------------------------------------------------------
void ResetButtonConfig(ButtonConfig *a1)
{
    ResetKeyboardConfig(a1);
    ResetJoystickConfig(a1);
}

//----- (004011A0) --------------------------------------------------------
int WriteButtonConfig(void *a1)
{
    char v2[268]; // [esp+0h] [ebp-118h] BYREF
    int v3;       // [esp+110h] [ebp-8h]
    FILE *v4;     // [esp+114h] [ebp-4h]

    v3 = 0;
    v4 = 0;

    sprintf(v2, "%s\\%s", temp_guxtPath, ButtonConfigFile);
    v4 = fopen(v2, "wb");

    if (v4 && fwrite(a1, 8u, 1u, v4) == 1)
        v3 = 1;

    if (v4)
        fclose(v4);
    return v3;
}
// 441044: using guessed type char *ButtonConfigFile;

//----- (00401240) --------------------------------------------------------
BOOL ReadButtonConfig(ButtonConfig *a1)
{
    char v2[268];       // [esp+0h] [ebp-118h] BYREF
    int result = FALSE; // [esp+110h] [ebp-8h]
    FILE *fd = NULL;    // [esp+114h] [ebp-4h]

    sprintf(v2, "%s\\%s", temp_guxtPath, ButtonConfigFile);
    fd = fopen(v2, "rb");

    if (fd && fread(a1, 8u, 1u, fd) == 1)
        result = 1;

    if (fd)
        fclose(fd);

    return result;
}
// 441044: using guessed type char *ButtonConfigFile;

//----- (004012E0) --------------------------------------------------------
void LoadButtonConfig()
{
    if (!ReadButtonConfig(&g_KeyMap))
        ResetButtonConfig(&g_KeyMap);
}

//----- (00401310) --------------------------------------------------------
signed int GetTrg()
{
    signed int v1;            // [esp+0h] [ebp-18h]
    DirectInputProcStruct a1; // [esp+4h] [ebp-14h] BYREF

    v1 = 0;
    isKeyHeld = 0;

    if (Input_IsHeld(g_KeyMap.left))
        v1 = 0x10;
    if (Input_IsHeld(g_KeyMap.right))
        v1 |= 0x20u;
    if (Input_IsHeld(g_KeyMap.up))
        v1 |= 0x40u;
    if (Input_IsHeld(g_KeyMap.down))
        v1 |= 0x80u;
    if (Input_IsHeld(g_KeyMap.shot))
        v1 |= 1u;
    if (Input_IsHeld(g_KeyMap.pause))
        v1 |= 2u;
    if (v1)
        isKeyHeld = 1;
    if (DirectInputProc(&a1))
    {
        if (a1.left)
            v1 |= 0x10u;
        if (a1.right)
            v1 |= 0x20u;
        if (a1.up)
            v1 |= 0x40u;
        if (a1.down)
            v1 |= 0x80u;
        if ((a1.extraBtns & (1 << g_KeyMap.joyShot)) != 0)
            v1 |= 1u;
        if ((a1.extraBtns & (1 << g_KeyMap.joyPause)) != 0)
            v1 |= 2u;
    }
    return v1;
}
// 442C50: using guessed type int isKeyHeld;

//----- (00401480) --------------------------------------------------------
int GetKeyHeld()
{
    return isKeyHeld;
}

//----- (00401490) --------------------------------------------------------
void ClearTrg_(TriggerStruct *a1)
{
    Input_Reset();
    a1->hold = GetTrg();
    a1->trig = a1->hold;
    a1->prev = 0;
}

//----- (004014C0) --------------------------------------------------------
void UpdateTrg(TriggerStruct *a1)
{
    a1->prev = a1->trig ^ a1->hold;
    a1->prev &= a1->hold;
    a1->trig = a1->hold;
}

//----- (00401500) --------------------------------------------------------
signed int GetPlayerInput(unsigned char a1)
{
    if ((a1 & 0x10) != 0 && (a1 & 0x40) != 0)
        return 5;
    if ((a1 & 0x20) != 0 && (a1 & 0x40) != 0)
        return 6;
    if ((a1 & 0x10) != 0 && (a1 & 0x80) != 0)
        return 7;
    if ((a1 & 0x20) != 0 && (a1 & 0x80) != 0)
        return 8;
    if ((a1 & 0x10) != 0)
        return 1;
    if ((a1 & 0x20) != 0)
        return 2;
    if ((a1 & 0x40) != 0)
        return 3;
    if ((a1 & 0x80) != 0)
        return 4;
    return 0;
}

LPDIRECTINPUTA ppDI; // idb
IDirectInputDevice2A *g_DID2;
int g_JoyAnalogStickX; // weak
int g_JoyAnalogStickY; // weak
IDirectInputDevice2A *did_interface;
LPDIRECTINPUTDEVICEA did_ptr;
SomeWeirdInputStruct *swis;
int someFlags = 0;

static BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, SomeWeirdInputStruct *pvRef);
static BOOL DirectInputDeviceLostCallback(BOOL acquire);

//----- (004226F0) --------------------------------------------------------
BOOL InitDirectInput(HINSTANCE hinst, HWND hWnd)
{
    BOOL result; // eax

    if (DirectInput8Create(hinst, 0x500u, IID_IDirectInput8A, (LPVOID *)&ppDI, 0))
        result = FALSE;
    else
        result = InitDirectInputDevice(hWnd);

    return result;
}

//----- (00422730) --------------------------------------------------------
BOOL InitDirectInputDevice(HWND hWnd)
{
    SomeWeirdInputStruct is; // [esp+0h] [ebp-8h] BYREF

    is.did2 = 0;
    is.dinput = ppDI;
    ppDI->AddRef();
    ppDI->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACKA)EnumDevicesCallback, &is, 1);

    if (is.dinput)
    {
        is.dinput->Release();
        is.dinput = NULL;
    }

    if (!is.did2)
        return FALSE;
    g_DID2 = is.did2;

    if (is.did2->SetDataFormat(&c_dfDIJoystick2))
        return FALSE;
    if (g_DID2->SetCooperativeLevel(hWnd, 9))
        return FALSE;

    g_DID2->Acquire();
    return TRUE;
}

//----- (00422800) --------------------------------------------------------
static BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, SomeWeirdInputStruct *pvRef)
{
    BOOL result; // eax

    if ((someFlags & 1) == 0)
    {
        someFlags |= 1u;
        swis = pvRef;
    }
    if (swis->dinput->CreateDevice(lpddi->guidInstance, &did_ptr, 0))
    {
        swis->did2 = NULL;
        result = TRUE;
    }
    else if (did_ptr->QueryInterface(IID_IDirectInputDevice2A, (LPVOID *)&did_interface) >= 0)
    {
        if (did_ptr)
        {
            did_ptr->Release();
            did_ptr = NULL;
        }
        swis->did2 = did_interface;
        result = FALSE;
    }
    else
    {
        g_DID2 = NULL;
        result = TRUE;
    }

    return result;
}

//----- (004228D0) --------------------------------------------------------
void ReleaseDirectInput()
{
    if (g_DID2)
    {
        g_DID2->Release();
        g_DID2 = NULL;
    }

    if (ppDI)
    {
        ppDI->Release();
        ppDI = NULL;
    }
}

//----- (00422920) --------------------------------------------------------
BOOL DirectInputProc(DirectInputProcStruct *a1)
{
    HRESULT err;
    int i;
    DIJOYSTATE state; // [esp+8h] [ebp-58h] BYREF

    if (!g_DID2)
        return FALSE;
    if (g_DID2->Poll())
        return FALSE;

    err = g_DID2->GetDeviceState(80, &state);
    if (err == DIERR_INPUTLOST)
    {
        DirectInputDeviceLostCallback(FALSE);
    }
    else if (err)
    {
        return FALSE;
    }

    for (i = 0; i < 32; ++i)
    {
        if ((state.rgbButtons[i] & 0x80) != 0)
            a1->extraBtns |= (1 << i);
        else
            a1->extraBtns &= ~(1 << i);
    }

    a1->down = 0;
    a1->right = 0;
    a1->up = 0;
    a1->left = 0;
    if (state.lX >= g_JoyAnalogStickX - 10000)
    {
        if (state.lX > g_JoyAnalogStickX + 10000)
            a1->right = 1;
    }
    else
    {
        a1->left = 1;
    }
    if (state.lY >= g_JoyAnalogStickY - 10000)
    {
        if (state.lY > g_JoyAnalogStickY + 10000)
            a1->down = 1;
    }
    else
    {
        a1->up = 1;
    }

    return TRUE;
}

//----- (00422AA0) --------------------------------------------------------
static BOOL DirectInputDeviceLostCallback(BOOL acquire)
{
    if (!g_DID2)
        return TRUE;

    if (acquire)
        g_DID2->Acquire();
    else
        g_DID2->Unacquire();

    return TRUE;
}

//----- (00422AF0) --------------------------------------------------------
BOOL DirectInputUpdateAnalogStick()
{
    HRESULT err;      // [esp+0h] [ebp-5Ch]
    DIJOYSTATE state; // [esp+4h] [ebp-58h] BYREF

    if (!g_DID2)
        return FALSE;
    if (g_DID2->Poll())
        return FALSE;

    err = g_DID2->GetDeviceState(80, &state);
    if (err == DIERR_INPUTLOST)
    {
        DirectInputDeviceLostCallback(FALSE);
    }
    else if (err)
    {
        return FALSE;
    }

    g_JoyAnalogStickX = state.lX;
    g_JoyAnalogStickY = state.lY;

    return TRUE;
}

static char keysHeld[256];
static char keysPrev[256];
static char keysTrig[256];
static int mouseHeld;
static int mousePrev;
static int mouseTrig;
static int unused1;
static int unused2;
static int unused3;
static BOOL captured;

//----- (00425890) --------------------------------------------------------
void Input_Reset()
{
    memset(keysHeld, 0, sizeof(keysHeld));
    memset(keysPrev, 0, sizeof(keysPrev));
    memset(keysTrig, 0, sizeof(keysTrig));
    mouseHeld = 0;
    mousePrev = 0;
    mouseTrig = 0;
    unused1 = 0;
    unused2 = 0;
    unused3 = 0;
}

//----- (00425910) --------------------------------------------------------
void Input_ProcessWinMsg(HWND hWnd, unsigned int msg, WPARAM wParam)
{
    if (msg > 0x202)
    {
        if (msg == WM_RBUTTONDOWN)
        {
            mouseHeld |= 0x10u;
            if (!captured)
            {
                captured = TRUE;
                SetCapture(hWnd);
            }
        }
        else if (msg == WM_RBUTTONUP)
        {
            mouseHeld &= ~0x10u;
            if ((mouseHeld & 1) == 0)
            {
                captured = FALSE;
                ReleaseCapture();
            }
        }
    }
    else
    {
        switch (msg)
        {
        case WM_LBUTTONUP:
            mouseHeld &= ~1u;
            if ((mouseHeld & 0x10) == 0)
            {
                captured = FALSE;
                ReleaseCapture();
            }
            break;
        case WM_KEYFIRST:
            keysHeld[wParam] = 1;
            break;
        case WM_KEYUP:
            keysHeld[wParam] = 0;
            break;
        case WM_LBUTTONDOWN:
            mouseHeld |= 1u;
            if (!captured)
            {
                captured = TRUE;
                SetCapture(hWnd);
            }
            break;
        }
    }
}
// 44D770: using guessed type int mouseHeld;
// 44D788: using guessed type int input_18;

//----- (00425A40) --------------------------------------------------------
void Input_sub_425A40(int a1, int a2, int a3)
{
    if (HIWORD(a3) > 0)
        ++unused1;

    if (a3 < 0)
        --unused1;
}
// 44D77C: using guessed type int unused1;

//----- (00425A80) --------------------------------------------------------
int Input_UpdateTriggers()
{
    int result; // eax
    int i;      // [esp+0h] [ebp-4h]

    for (i = 0; i < 256; ++i)
    {
        keysTrig[i] = !keysPrev[i] && keysHeld[i];
        keysPrev[i] = keysHeld[i];
    }

    mouseTrig = (mousePrev ^ mouseHeld) & mouseHeld;
    mousePrev = mouseHeld;

    if (unused1 >= unused2)
        unused3 = unused1 > unused2;
    else
        unused3 = -1;

    result = unused1;
    unused2 = unused1;

    return result;
}

//----- (00425B60) --------------------------------------------------------
int Input_GetUnused3()
{
    return unused3;
}

//----- (00425B70) --------------------------------------------------------
BOOL Input_IsHeld(int a1)
{
    return keysHeld[a1] != 0;
}

//----- (00425B90) --------------------------------------------------------
BOOL Input_IsTrig(int a1)
{
    return keysTrig[a1] != 0;
}

//----- (00425BB0) --------------------------------------------------------
BOOL Input_IsLMBHeld()
{
    return (mouseHeld & 1) != 0;
}

//----- (00425BD0) --------------------------------------------------------
BOOL Input_IsRMBHeld()
{
    return (mouseHeld & 0x10) != 0;
}

//----- (00425BF0) --------------------------------------------------------
BOOL Input_IsLMBTrig()
{
    return (mouseTrig & 1) != 0;
}

//----- (00425C10) --------------------------------------------------------
BOOL Input_IsRMBTrig()
{
    return (mouseTrig & 0x10) != 0;
}
