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

struct TriggerStruct
{
    unsigned int hold;
    unsigned int prev;
    unsigned int trig;
};

struct ButtonConfig
{
    unsigned char left;
    unsigned char right;
    unsigned char up;
    unsigned char down;
    unsigned char shot;
    unsigned char pause;
    unsigned char joyShot;
    unsigned char joyPause;
};

// todo some static_assert() to ensure sizeof(ButtonConfig) == sizeof(ButtonConfigIdx)
struct ButtonConfigIdx
{
    unsigned char btns[8];
};

void ResetKeyboardConfig(ButtonConfig *a1);
void ResetJoystickConfig(ButtonConfig *a1);
void ResetButtonConfig(ButtonConfig *a1);
int WriteButtonConfig(void *a1);
BOOL ReadButtonConfig(ButtonConfig *a1);
void LoadButtonConfig();
int GetTrg();
int GetKeyHeld();
void ClearTrg_(TriggerStruct *a1);
void UpdateTrg(TriggerStruct *a1);
int GetPlayerInput(unsigned char a1);

BOOL InitDirectInput(HINSTANCE hinst, HWND hWnd);
BOOL InitDirectInputDevice(HWND hWnd);
void ReleaseDirectInput();
BOOL DirectInputProc(DirectInputProcStruct *a1);
BOOL DirectInputUpdateAnalogStick();

void Input_Reset();
void Input_ProcessWinMsg(HWND hWnd, unsigned int msg, WPARAM wParam);
void Input_sub_425A40(int a1, int a2, int a3);
int Input_UpdateTriggers();
int Input_GetUnused3();
BOOL Input_IsHeld(int a1);
BOOL Input_IsTrig(int a1);
BOOL Input_IsLMBHeld();
BOOL Input_IsRMBHeld();
BOOL Input_IsLMBTrig();
BOOL Input_IsRMBTrig();

#endif