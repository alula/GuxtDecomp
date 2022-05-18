#ifndef __WINMAIN_H__
#define __WINMAIN_H__

#include <windows.h>

extern int ScreenRenderWidth;
extern int ScreenRenderHeight;
extern BOOL TimerFirstCountFlag;
extern const char *RankingFile;
extern RECT scWOffset_0;
extern LPCSTR lpClassName;
extern int screenSize;
extern LPCSTR lpName;
extern LPCSTR mutexName;

extern char dataPath[MAX_PATH];
extern char pszPath[MAX_PATH];
extern HINSTANCE g_Instance;
extern char temp_guxtPath[MAX_PATH];
extern HWND hWnd;
extern HMENU hMenu;

BOOL PollMessages();

void SaveWindowSettings(HWND hWnd);

#endif