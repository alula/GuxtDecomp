#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <stdio.h>
#include <string.h>

#include "WinMain.h"
#include "Draw.h"
#include "Game.h"
#include "Input.h"
#include "Mutex.h"
#include "Sound.h"
#include "pxtone.h"

int ScreenRenderWidth = 120;                                             // weak
int ScreenRenderHeight = 160;                                            // weak
char *windowName[4] = {"Guxt", "main.rect", "main.screen_mode", "Main"}; // weak
// int mainrectFile = 4441624; // idb -> windowName[1]
// char *mainscreemodeFile[2] = { "main.screen_mode", "Main" }; // weak -> windowName[2]
LPCSTR lpClassName = "Main"; // idb
int screenSize = 2;          // weak
LPCSTR lpName = "directxsample";
LPCSTR mutexName = "map_directxsample";

char dataPath[MAX_PATH] = "";
char pszPath[MAX_PATH] = "";
HINSTANCE g_Instance = NULL;
char temp_guxtPath[MAX_PATH] = "";
HWND hWnd = NULL;
HMENU hMenu = NULL;
BOOL g_FullScreenEnabled = FALSE;

const char *PtrToTempGuxt = NULL;
const char *UnusedPtrTempGuxt = NULL;

BOOL ReadMainScreenMode();
LRESULT __stdcall GameWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static BOOL SetWindowAttr(HINSTANCE hInstance, const char *class_name, WNDPROC proc);
void SetPtrTempGuxt(const char *a1);
void SetUnusedPtrTempGuxt(const char *a1);

//----- (0041CE70) --------------------------------------------------------
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int result;           // eax
    DWORD v6;             // [esp+2Ch] [ebp-120h]
    Mutex mutex;          // [esp+30h] [ebp-11Ch] BYREF
    CHAR WindowName[268]; // [esp+3Ch] [ebp-110h] BYREF

    g_Instance = hInstance;

    if (!mutex.Start(lpName, mutexName))
        goto err;

    InitCommonControls();
    Input_Reset();
    GetModuleFileNameA(0, pszPath, 0x104u);
    PathRemoveFileSpecA(pszPath);

    sprintf(temp_guxtPath, "%s\\temp_guxt", pszPath);
    sprintf(dataPath, "%s\\data", pszPath);

    CreateDirectoryA(temp_guxtPath, 0);
    SetPtrTempGuxt(temp_guxtPath);
    SetUnusedPtrTempGuxt(temp_guxtPath);

    if (!SetWindowAttr(hInstance, lpClassName, GameWndProc))
        goto err;

    hMenu = LoadMenuA(hInstance, "MENU_MAIN");
    sprintf(WindowName, "%s", windowName[0]);

    hWnd = CreateWindowExA(0, lpClassName, WindowName, 0x800A0000, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0, hInstance, 0);
    if (!mutex.MapFile(lpName, mutexName, hWnd))
    {
        goto err;
    }

    InitMenuItem(hWnd);
    ReadMainScreenMode();

    if (!InitDirectDraw(hWnd, dataPath, g_FullScreenEnabled, TRUE))
    {
        MessageBoxA(0, "dxdraw", "error", 0);
        goto err;
    }

    if (!InitMainSurface(hWnd, 120, 160, screenSize))
    {
        MessageBoxA(0, "main surface", "error", 0);
        goto err;
    }

    SetRenderOffset(0, 0);
    InitText(0, 6, 12);
    SetScreenMode(0, 1);

    if (!g_FullScreenEnabled && !SetWindowPosRect(hWnd, windowName[1], 0))
        SetFullscreenWindowPos(hWnd);

    v6 = GetTickCount();
    DrawStudioPixel();
    InitDirectInput(hInstance, hWnd);
    DirectInputUpdateAnalogStick();
    pxtone_Ready(hWnd, 2, 44100, 16, 0.1f, 1, 0);

    AssignDirectSound(pxtone_GetDirectSound());
    // pxtnPulse_Frequency::Init();

    if (LoadGenericData())
    {
        while (v6 + 500.0 > GetTickCount())
            ;
        Game(hwnd);
    }

    pxtone_Tune_Stop();
    pxtone_Release();
    ReleaseDirectInput();
    CallDeleteObject();
    EndDirectDraw(hWnd);
    DestroyWindow(hWnd);
    DestroyMenu(hMenu);

    return 1;

err:
    result = 0;
    return result;
}

//----- (0041D280) --------------------------------------------------------
BOOL ReadMainScreenMode()
{
    char v1[268]; // [esp+0h] [ebp-118h] BYREF
    BOOL result;  // [esp+110h] [ebp-8h]
    FILE *v3;     // [esp+114h] [ebp-4h]

    result = FALSE;
    v3 = 0;
    sprintf(v1, "%s\\%s", temp_guxtPath, windowName[2]);
    v3 = fopen(v1, "rb");
    if (v3)
    {
        if (fread(&screenSize, 4u, 1u, v3) != 1 || fread(&g_FullScreenEnabled, 4u, 1u, v3) != 1)
            goto err;
        fclose(v3);
    }
    if (screenSize != 1 && screenSize != 2 && screenSize != 3 && screenSize != 4 && screenSize != 5)
        screenSize = 2;
    result = TRUE;
err:
    if (!result)
    {
        screenSize = 2;
        g_FullScreenEnabled = 0;
    }
    return result;
}

//----- (0041DEA0) --------------------------------------------------------
LRESULT __stdcall GameWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HMENU v4;              // eax
    struct tagPOINT v6;    // [esp-14h] [ebp-30h]
    HIMC v7;               // [esp+10h] [ebp-Ch]
    struct tagPOINT Point; // [esp+14h] [ebp-8h] BYREF

    // TODO: refactor, originally it was a single switch() statement.

    if (Msg > 0x112)
    {
        switch (Msg)
        {
        case 0x201u:
            if (!g_FullScreenEnabled)
                PostMessageA(hWnd, 0xA1u, 2u, lParam);
            return 0;
        case 0x204u:
            Point.x = lParam;
            Point.y = HIWORD(lParam);
            ClientToScreen(hWnd, &Point);
            v6 = Point;
            v4 = GetSubMenu(hMenu, 0);
            TrackPopupMenu(v4, 0, v6.x, v6.y, 0, hWnd, 0);
            return 0;
        case 0x233u:
            DragFileProc(hWnd, wParam);
            SetForegroundWindow(hWnd);
            return 0;
        case 0x282u:
            if (wParam == 8)
            {
                v7 = ImmGetContext(hWnd);
                ImmSetOpenStatus(v7, 0);
                ImmReleaseContext(hWnd, v7);
            }
            return 0;
        default:
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }
    }
    if (Msg == 274)
    {
        if (wParam != 61696 && wParam != 61760 && wParam != 61808)
            DefWindowProcA(hWnd, Msg, wParam, lParam);
    }
    else if (Msg > 0x10)
    {
        if (Msg < 0x100)
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        if (Msg > 0x101)
        {
            if (Msg == 273)
            {
                switch (wParam)
                {
                case 0x9C42u:
                    SendMessageA(hWnd, 0x10u, 0, 0);
                    return 0;
                case 0x9C46u:
                case 0x9C47u:
                case 0x9C48u:
                case 0x9C4Eu:
                case 0x9C4Fu:
                case 0x9C54u:
                    SetScreenMode(wParam, 0);
                    return 0;
                case 0x9C4Bu:
                    SetReset(1);
                    return 0;
                case 0x9C50u:
                    ShowWindow(hWnd, 6);
                    return 0;
                case 0x9C52u:
                    OpenSoundVolume(hWnd);
                    return 0;
                default:
                    return DefWindowProcA(hWnd, Msg, wParam, lParam);
                }
            }
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }
        OutputDebugStringA("kk\n");
        Input_ProcessWinMsg(hWnd, Msg, wParam);
    }
    else
    {
        switch (Msg)
        {
        case 0x10u:
            PostQuitMessage(0);
            break;
        case 1u:
            GameFocussed = 1;
            break;
        case 5u:
            if (wParam)
            {
                if (wParam == 1)
                    MinimizeGame();
            }
            else
            {
                RestoreGame();
            }
            break;
        default:
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }
    }
    return 0;
}

//----- (0041DB20) --------------------------------------------------------
static BOOL SetWindowAttr(HINSTANCE hInstance, const char *class_name, WNDPROC proc)
{
    WNDCLASSEXA cls; // [esp+0h] [ebp-30h] BYREF

    memset(&cls, 0, sizeof(cls));
    cls.cbSize = 48;
    cls.lpszClassName = class_name;
    cls.style = 3;
    cls.lpfnWndProc = proc;
    cls.hInstance = hInstance;
    cls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    cls.hIcon = LoadIconA(hInstance, "0");
    cls.hCursor = LoadCursorA(NULL, IDC_ARROW);
    return RegisterClassExA(&cls) != 0;
}

//----- (0041E370) --------------------------------------------------------
UINT InitMenuItem(HWND hWnd)
{
    UINT result;                 // eax
    struct tagMENUITEMINFOA mii; // [esp+4h] [ebp-38h] BYREF
    UINT item;                   // [esp+34h] [ebp-8h]
    HMENU menu;                  // [esp+38h] [ebp-4h]

    menu = GetSystemMenu(hWnd, 0);
    result = GetMenuItemCount(menu) - 1;
    for (item = result; (item & 0x80000000) == 0; --item)
    {
        memset(&mii, 0, sizeof(mii));
        mii.cbSize = 48;
        mii.fMask = 18;
        result = GetMenuItemInfoA(menu, item, 1, &mii);
        if (result && (mii.wID == 61440 || mii.wID == 61488))
            result = DeleteMenu(menu, item, 0x400u);
    }
    return result;
}

//----- (00425D70) --------------------------------------------------------
void SetPtrTempGuxt(const char *a1)
{
    PtrToTempGuxt = a1;
}

//----- (00426500) --------------------------------------------------------
void SetUnusedPtrTempGuxt(const char *a1)
{
    UnusedPtrTempGuxt = a1;
}