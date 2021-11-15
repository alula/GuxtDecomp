#ifndef __FADE_H__
#define __FADE_H__

#include <windows.h>

struct Fade
{
    int state;
    int wState;
    int wCount;
    int wX;
    int unused;
    RECT bounds;
    RECT wRect;
    RECT wRect2;
};

void LoadPximgScreenEffect();
void EndingInitFade();
void ResetFade();
void SetFadeActive();
BOOL CheckFadeEnd();
void SetFadeWhiteActive(int a1, int a2);
BOOL CheckFadeWhiteEnd();
void RecordEndFadeWhite();
void ActFade();
void PutFade(RECT *a1);

#endif