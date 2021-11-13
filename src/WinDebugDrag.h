#ifndef __WINDEBUGDRAG_H__
#define __WINDEBUGDRAG_H__

#include <windows.h>

void DragEnable(HWND hWnd);

BOOL DragFileProc(HWND hWnd, HDROP hDrop);

BOOL CheckDragFile();

const char *GetDragFile();

void InitDragFile();

#endif