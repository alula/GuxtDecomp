#ifndef __GAME_H__
#define __GAME_H__

#include <windows.h>

extern BOOL g_FullScreenEnabled;
extern BOOL GameFocussed;
extern int magnification;

BOOL LoadGenericData();

int Game(HWND hWnd);

BOOL LoadPximg(const char *file_name, int surf_no);

int CountFramePerSecond();

void PutFramePerSecond();

BOOL Flip_SystemTask();

void SetReset(BOOL reset);

BOOL GetGameReset();

BOOL Call_Escape();

#endif