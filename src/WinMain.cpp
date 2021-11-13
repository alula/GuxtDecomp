#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <stdio.h>
#include <string.h>

#include "WinMain.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "Mutex.h"
#include "Sound.h"
#include "Stage.h"
#include "WinDebugDrag.h"
#include "pxtone.h"

int ScreenRenderWidth = 120;
int ScreenRenderHeight = 160;
BOOL TimerFirstCountFlag = TRUE;
const char *RankingFile = "ranking.bin";
RECT scWOffset_0 = {0, 0, 120, 160};
const char *windowName[4] = {"Guxt", "main.rect", "main.screen_mode", "Main"};
// int mainrectFile = 4441624; // idb -> windowName[1]
// char *mainscreemodeFile[2] = { "main.screen_mode", "Main" }; // weak -> windowName[2]
LPCSTR lpClassName = "Main";
int screenSize = 2;
LPCSTR lpName = "directxsample";
LPCSTR mutexName = "map_directxsample";

char dataPath[MAX_PATH] = "";
char pszPath[MAX_PATH] = "";
HINSTANCE g_Instance = NULL;
char temp_guxtPath[MAX_PATH] = "";
HWND hWnd = NULL;
HMENU hMenu = NULL;
int g_FullScreenMode;

const char *PtrToTempGuxt = NULL;
const char *UnusedPtrTempGuxt = NULL;

BOOL ReadMainScreenMode();
static void DrawStudioPixel();
void SetScreenMode(unsigned short a1, int a2);
static LRESULT __stdcall GameWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static void MinimizeGame();
static void RestoreGame();
static BOOL OpenSoundVolume(HWND hwnd);
static void InitMenuItem(HWND hWnd);
static BOOL SetWindowAttr(HINSTANCE hInstance, const char *class_name, WNDPROC proc);
static void WriteScreenMode();
static BOOL SetFullscreenWindowPos(HWND hWnd);
static void SetPtrTempGuxt(const char *a1);
static BOOL SetWindowPosRect(HWND hWnd, const char *file_name, BOOL move_window);
static BOOL SaveWindowRect(HWND hWnd, const char *file_name);
static void SetUnusedPtrTempGuxt(const char *a1);

//----- (0041CE10) --------------------------------------------------------
BOOL PollMessages()
{
    struct tagMSG Msg; // [esp+0h] [ebp-1Ch] BYREF

    while (PeekMessageA(&Msg, 0, 0, 0, 0) || !GameFocussed)
    {
        if (!GetMessageA(&Msg, 0, 0, 0))
            return 0;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    return 1;
}

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

    if (!InitDirectDraw(hWnd, dataPath, g_FullScreenMode, TRUE))
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

    if (!g_FullScreenMode && !SetWindowPosRect(hWnd, windowName[1], 0))
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
        Game(hWnd);
    }

    pxtone_Tune_Stop();
    pxtone_Release();
    ReleaseDirectInput();
    ReleaseText();
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
        if (fread(&screenSize, 4u, 1u, v3) != 1 || fread(&g_FullScreenMode, 4u, 1u, v3) != 1)
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
        g_FullScreenMode = 0;
    }
    return result;
}

//----- (0041D390) --------------------------------------------------------
static void DrawStudioPixel()
{
    RECT rcShadow; // [esp+0h] [ebp-2A4h] BYREF
    RECT rcView;   // [esp+10h] [ebp-294h] BYREF
    int cBlue;     // [esp+20h] [ebp-284h]
    int i;         // [esp+24h] [ebp-280h]
    int cWhite;    // [esp+28h] [ebp-27Ch]
    RECT rcPixel[39] = {
        {28, 3, 29, 14},
        {29, 3, 33, 7},
        {34, 3, 38, 7},
        {38, 3, 39, 14},
        {31, 8, 33, 14},
        {34, 8, 36, 14},
        {30, 9, 37, 12},
        {42, 3, 47, 4},
        {48, 3, 53, 4},
        {42, 4, 46, 6},
        {49, 4, 53, 6},
        {42, 6, 43, 8},
        {52, 6, 53, 8},
        {44, 8, 51, 11},
        {42, 11, 47, 14},
        {48, 11, 53, 14},
        {60, 3, 63, 4},
        {56, 4, 67, 5},
        {56, 5, 58, 7},
        {65, 5, 67, 7},
        {56, 8, 59, 10},
        {59, 6, 64, 9},
        {64, 8, 67, 10},
        {60, 9, 63, 13},
        {59, 11, 64, 12},
        {56, 13, 67, 14},
        {70, 3, 79, 10},
        {70, 10, 73, 14},
        {80, 7, 83, 9},
        {80, 10, 83, 14},
        {84, 7, 87, 10},
        {88, 7, 91, 10},
        {86, 9, 89, 12},
        {84, 11, 87, 14},
        {88, 11, 91, 14},
        {92, 7, 98, 11},
        {92, 11, 93, 12},
        {92, 12, 98, 14},
        {99, 3, 102, 14},
    };

    rcView.left = 0;
    rcView.top = 0;
    rcView.right = 128;
    rcView.bottom = 16;

    int cBlack = ConvertRGBToNative(0);
    cWhite = ConvertRGBToNative(0xF0F0F0u);
    cBlue = ConvertRGBToNative(0xF00000u);

    InitSurface(128, 16, 3, 0);
    PutBackground(&scWOffset_0, cBlack);
    BlitSurface(&rcView, cBlack, 3);
    for (i = 0; i < 39; ++i)
    {
        rcShadow = rcPixel[i];
        --rcShadow.left;
        ++rcShadow.right;
        BlitSurface(&rcShadow, cBlue, 3);
    }

    for (i = 0; i < 39; ++i)
        BlitSurface(&rcPixel[i], cWhite, 3);

    PutBitmap3(&scWOffset_0, scWOffset_0.right / 2 - 64, scWOffset_0.bottom / 2 - 8, &rcView, 3);
    Flip_Screen();
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

//----- (0041DBB0) --------------------------------------------------------
void SetScreenMode(unsigned short a1, int a2)
{
    struct tagRECT Rect; // [esp+10h] [ebp-18h] BYREF
    int scale;           // [esp+20h] [ebp-8h]
    int fullscreen;      // [esp+24h] [ebp-4h]

    scale = screenSize;
    fullscreen = g_FullScreenMode;

    switch (a1)
    {
    case 0x9C46:
        scale = 1;
        break;
    case 0x9C47:
        scale = 2;
        break;
    case 0x9C48:
        scale = 3;
        break;
    case 0x9C4E:
        scale = 4;
        break;
    case 0x9C4F:
        scale = 5;
        break;
    case 0x9C54:
        fullscreen = g_FullScreenMode == 0;
        break;
    default:
        break;
    }

    if (a2 || scale != screenSize)
    {
        if (!ResetSurfaceTbl(hWnd, scale))
            return;

        PutCenter();
    }

    if (a2 || fullscreen != g_FullScreenMode)
    {
        if (fullscreen)
        {
            if (!SetFullscreenDDrawParams(1))
                return;
        }
        else if (!SetFullscreenDDrawParams(0))
        {
            return;
        }
    }
    CheckMenuItem(hMenu, 0x9C46u, 0);
    CheckMenuItem(hMenu, 0x9C47u, 0);
    CheckMenuItem(hMenu, 0x9C48u, 0);
    CheckMenuItem(hMenu, 0x9C4Eu, 0);
    CheckMenuItem(hMenu, 0x9C4Fu, 0);
    switch (scale)
    {
    case 1:
        CheckMenuItem(hMenu, 0x9C46u, 8u);
        break;
    case 2:
        CheckMenuItem(hMenu, 0x9C47u, 8u);
        break;
    case 3:
        CheckMenuItem(hMenu, 0x9C48u, 8u);
        break;
    case 4:
        CheckMenuItem(hMenu, 0x9C4Eu, 8u);
        break;
    case 5:
        CheckMenuItem(hMenu, 0x9C4Fu, 8u);
        break;
    default:
        break;
    }

    if (fullscreen)
        CheckMenuItem(hMenu, 0x9C54u, 8u);
    else
        CheckMenuItem(hMenu, 0x9C54u, 0);

    if (fullscreen)
    {
        SetFullscreenRenderPos();
        GetWindowRect(hWnd, &Rect);
        RedrawWindow(hWnd, &Rect, 0, 5u);
    }
    else
    {
        SetWindowPos(hWnd, 0, 0, 0, 120 * scale, 160 * scale, 2u);
        if (g_FullScreenMode)
            SetFullscreenWindowPos(hWnd);
    }
    screenSize = scale;
    g_FullScreenMode = fullscreen;
}

//----- (0041DEA0) --------------------------------------------------------
static LRESULT __stdcall GameWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
            if (!g_FullScreenMode)
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
            DragFileProc(hWnd, (HDROP)wParam);
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
                    SetReset(TRUE);
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

//----- (0041E220) --------------------------------------------------------
static void MinimizeGame()
{
    if (GameFocussed)
    {
        GameFocussed = 0;
        FadeMusic();
        PauseLoopSound();
    }
}
// 44C7F8: using guessed type int GameFocussed;

//----- (0041E250) --------------------------------------------------------
static void RestoreGame()
{
    if (!GameFocussed)
    {
        SetFocus(hWnd);
        GameFocussed = 1;
        ResumeMusic();
        ResumeLoopSound();
        Input_Reset();
    }
}
// 44C7F8: using guessed type int GameFocussed;

//----- (0041E290) --------------------------------------------------------
static BOOL OpenSoundVolume(HWND hwnd)
{
    CHAR Buffer[264];  // [esp+0h] [ebp-328h] BYREF
    CHAR File[264];    // [esp+108h] [ebp-220h] BYREF
    HINSTANCE v4;      // [esp+210h] [ebp-118h]
    HINSTANCE v5;      // [esp+214h] [ebp-114h]
    CHAR pszPath[268]; // [esp+218h] [ebp-110h] BYREF

    GetSystemDirectoryA(Buffer, 0x104u);
    sprintf(File, "%s\\Sndvol32.exe", Buffer);
    strcpy(pszPath, Buffer);
    PathRemoveFileSpecA(pszPath);
    strcat(pszPath, "\\Sndvol32.exe");
    v4 = ShellExecuteA(hwnd, "open", File, 0, 0, 5);
    v5 = ShellExecuteA(hwnd, "open", pszPath, 0, 0, 5);

    return v4 > (HINSTANCE)SE_ERR_DLLNOTFOUND || v5 > (HINSTANCE)SE_ERR_DLLNOTFOUND;
}

//----- (0041E370) --------------------------------------------------------
static void InitMenuItem(HWND hWnd)
{
    struct tagMENUITEMINFOA mii; // [esp+4h] [ebp-38h] BYREF
    int item;                    // [esp+34h] [ebp-8h]

    HMENU hSysMenu = GetSystemMenu(hWnd, 0);
    for (item = GetMenuItemCount(hSysMenu) - 1; item >= 0; --item)
    {
        memset(&mii, 0, sizeof(mii));
        mii.cbSize = 48;
        mii.fMask = 18;
        if (GetMenuItemInfoA(hSysMenu, item, 1, &mii) && (mii.wID == 61440 || mii.wID == 61488))
            DeleteMenu(hSysMenu, item, 0x400u);
    }
}

//----- (0041E410) --------------------------------------------------------
void SaveWindowSettings(HWND hWnd)
{
    SaveWindowRect(hWnd, windowName[1]);
    WriteScreenMode();
}

//----- (0041E430) --------------------------------------------------------
static void WriteScreenMode()
{
    char path[264]; // [esp+0h] [ebp-110h] BYREF
    FILE *fd;       // [esp+10Ch] [ebp-4h]

    fd = 0;
    sprintf(path, "%s\\%s", temp_guxtPath, windowName[2]);
    fd = fopen(path, "wb");

    if (!fd)
        return;

    fwrite(&screenSize, 4u, 1u, fd);
    fwrite(&g_FullScreenMode, 4u, 1u, fd);
    fclose(fd);
}

//----- (00425C30) --------------------------------------------------------
static BOOL SetFullscreenWindowPos(HWND hWnd)
{
    WINDOWPLACEMENT wndpl; // [esp+4h] [ebp-68h] BYREF
    RECT rcWin;            // [esp+30h] [ebp-3Ch] BYREF
    HWND hWndParent;       // [esp+40h] [ebp-2Ch]
    RECT rcWorkArea;       // [esp+44h] [ebp-28h] BYREF
    int X;                 // [esp+54h] [ebp-18h]
    int Y;                 // [esp+58h] [ebp-14h]
    RECT rcWorkArea2;      // [esp+5Ch] [ebp-10h] BYREF

    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWorkArea2, 0);
    GetWindowRect(hWnd, &rcWin);

    hWndParent = GetParent(hWnd);
    if (hWndParent)
    {
        wndpl.length = sizeof(WINDOWPLACEMENT);

        GetWindowPlacement(hWndParent, &wndpl);

        if (wndpl.showCmd && wndpl.showCmd != 2)
            GetWindowRect(hWndParent, &rcWorkArea);
        else
            SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
    }
    else
    {
        SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
    }

    X = rcWorkArea.left + (rcWorkArea.right - rcWorkArea.left - (rcWin.right - rcWin.left)) / 2;
    Y = rcWorkArea.top + (rcWorkArea.bottom - rcWorkArea.top - (rcWin.bottom - rcWin.top)) / 2;

    if (X < rcWorkArea2.left)
        X = rcWorkArea2.left;
    if (Y < rcWorkArea2.top)
        Y = rcWorkArea2.top;
    if (X + rcWin.right - rcWin.left > rcWorkArea2.right)
        X = rcWorkArea2.right - (rcWin.right - rcWin.left);
    if (Y + rcWin.bottom - rcWin.top > rcWorkArea2.bottom)
        Y = rcWorkArea2.bottom - (rcWin.bottom - rcWin.top);

    return SetWindowPos(hWnd, 0, X, Y, 0, 0, 0x41u);
}

//----- (00425D70) --------------------------------------------------------
static void SetPtrTempGuxt(const char *a1)
{
    PtrToTempGuxt = a1;
}

//----- (00425D80) --------------------------------------------------------
static BOOL SetWindowPosRect(HWND hWnd, const char *file_name, BOOL move_window)
{
    char path[268];  // [esp+0h] [ebp-148h] BYREF
    int cyMax;       // [esp+110h] [ebp-38h]
    int cxMin;       // [esp+114h] [ebp-34h]
    int cxMax;       // [esp+118h] [ebp-30h]
    FILE *fd;        // [esp+11Ch] [ebp-2Ch]
    int cyMin;       // [esp+120h] [ebp-28h]
    RECT rcWin;      // [esp+124h] [ebp-24h] BYREF
    int max_mode;    // [esp+134h] [ebp-14h] BYREF
    RECT rcWorkArea; // [esp+138h] [ebp-10h] BYREF

    max_mode = SW_SHOWNORMAL;

    sprintf(path, "%s\\%s", PtrToTempGuxt, file_name);
    fd = fopen(path, "rb");
    if (!fd)
        return FALSE;

    fread(&rcWin, 0x10u, 1u, fd);
    fread(&max_mode, 4u, 1u, fd);
    fclose(fd);

    SystemParametersInfoA(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
    cxMax = GetSystemMetrics(SM_CXMAXIMIZED);
    cyMax = GetSystemMetrics(SM_CYMAXIMIZED);
    cxMin = GetSystemMetrics(SM_CXMIN);
    cyMin = GetSystemMetrics(SM_CYMIN);

    if (rcWin.right - rcWin.left < cxMin)
        rcWin.right = cxMin + rcWin.left;
    if (rcWin.bottom - rcWin.top < cyMin)
        rcWin.bottom = cyMin + rcWin.top;
    if (rcWin.right - rcWin.left > cxMax)
        rcWin.right = cxMax + rcWin.left;
    if (rcWin.bottom - rcWin.top > cyMax)
        rcWin.bottom = cyMax + rcWin.top;

    if (rcWin.left < rcWorkArea.left)
    {
        rcWin.right += rcWorkArea.left - rcWin.left;
        rcWin.left = rcWorkArea.left;
    }

    if (rcWin.top < rcWorkArea.top)
    {
        rcWin.bottom += rcWorkArea.top - rcWin.top;
        rcWin.top = rcWorkArea.top;
    }

    if (rcWin.right > rcWorkArea.right)
    {
        rcWin.left -= rcWin.right - rcWorkArea.right;
        rcWin.right = rcWorkArea.right;
    }

    if (rcWin.bottom > rcWorkArea.bottom)
    {
        rcWin.top -= rcWin.bottom - rcWorkArea.bottom;
        rcWin.bottom = rcWorkArea.bottom;
    }

    if (move_window)
        MoveWindow(hWnd, rcWin.left, rcWin.top, rcWin.right - rcWin.left, rcWin.bottom - rcWin.top, 0);
    else
        SetWindowPos(hWnd, 0, rcWin.left, rcWin.top, 0, 0, 1u);

    if (max_mode == SW_MAXIMIZE)
        ShowWindow(hWnd, SW_MAXIMIZE);
    else
        ShowWindow(hWnd, SW_SHOWNORMAL);

    return TRUE;
}

//----- (00425F90) --------------------------------------------------------
static BOOL SaveWindowRect(HWND hWnd, const char *file_name)
{
    char path[268];        // [esp+0h] [ebp-150h] BYREF
    WINDOWPLACEMENT wndpl; // [esp+110h] [ebp-40h] BYREF
    FILE *fd;              // [esp+13Ch] [ebp-14h]
    RECT rcPos;            // [esp+140h] [ebp-10h] BYREF

    if (!GetWindowPlacement(hWnd, &wndpl))
        return FALSE;

    if (wndpl.showCmd == 1)
    {
        if (!GetWindowRect(hWnd, &rcPos))
            return FALSE;
        wndpl.rcNormalPosition = rcPos;
    }

    sprintf(path, "%s\\%s", *PtrToTempGuxt, file_name);
    fd = fopen(path, "wb");
    if (!fd)
        return FALSE;

    fwrite(&wndpl.rcNormalPosition, sizeof(wndpl.rcNormalPosition), 1u, fd);
    fwrite(&wndpl.showCmd, sizeof(wndpl.showCmd), 1u, fd);

    fclose(fd);
    return TRUE;
}

//----- (00426500) --------------------------------------------------------
static void SetUnusedPtrTempGuxt(const char *a1)
{
    UnusedPtrTempGuxt = a1;
}