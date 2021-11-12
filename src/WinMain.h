#ifndef __WINMAIN_H__
#define __WINMAIN_H__

#include <windows.h>

extern int ScreenRenderWidth;
extern int ScreenRenderHeight;
extern char *windowName[4];
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

#endif