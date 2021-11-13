#ifndef __INPUT_H__
#define __INPUT_H__

#include <windows.h>

struct DirectInputProcStruct
{
    int left;
    int right;
    int up;
    int down;
    int extraBtns;
};

BOOL InitDirectInput(HINSTANCE hinst, HWND hWnd);
BOOL InitDirectInputDevice(HWND hWnd);
void ReleaseDirectInput();
BOOL DirectInputProc(DirectInputProcStruct *a1);
BOOL DirectInputUpdateAnalogStick();

void Input_Reset();
void Input_ProcessWinMsg(HWND hWnd, unsigned int msg, WPARAM wParam);
void Input_sub_425A40(int a1, int a2, int a3);
int Input_UpdateTriggers();

#endif