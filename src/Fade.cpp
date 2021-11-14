#include <windows.h>

#include "Fade.h"
#include "Draw.h"
#include "Game.h"

Fade g_Fade;
unsigned int Fade_wColor;
unsigned int Fade_color;

//----- (00421280) --------------------------------------------------------
void LoadPximgScreenEffect()
{
    LoadPximg("screen_effect", 12);
    Fade_color = GetSurfaceColor(16);
    Fade_wColor = GetSurfaceColor(20);
}

//----- (004212C0) --------------------------------------------------------
void EndingInitFade()
{
    memset(&g_Fade, 0, sizeof(g_Fade));
}

//----- (004212E0) --------------------------------------------------------
void ResetFade()
{
    g_Fade.wState = 0;
    g_Fade.state = 10;
    g_Fade.bounds.left = 0;
    g_Fade.bounds.right = 120;
    g_Fade.bounds.top = 0;
    g_Fade.bounds.bottom = 168;
}

//----- (00421330) --------------------------------------------------------
void SetFadeActive()
{
    g_Fade.state = 20;
    g_Fade.bounds.left = 0;
    g_Fade.bounds.right = 120;
    g_Fade.bounds.top = 168;
    g_Fade.bounds.bottom = 160;
}

//----- (00421370) --------------------------------------------------------
BOOL CheckFadeEnd()
{
    return g_Fade.state == 30;
}

//----- (00421390) --------------------------------------------------------
int SetFadeWhiteActive(int a1, int a2)
{
    int result; // eax

    g_Fade.wState = 10;
    g_Fade.wCount = 0;
    g_Fade.wRect.left = 0;
    g_Fade.wRect.right = 120;
    g_Fade.wRect.top = a2;
    g_Fade.wRect.bottom = a2;
    g_Fade.wRect2.left = a1;
    result = a1;
    g_Fade.wRect2.right = a1;
    g_Fade.wRect2.top = 0;
    g_Fade.wRect2.bottom = 160;
    g_Fade.wX = a1;
    g_Fade.unused = a2;
    return result;
}

//----- (00421410) --------------------------------------------------------
BOOL CheckFadeWhiteEnd()
{
    return g_Fade.wState == 20;
}

//----- (00421430) --------------------------------------------------------
void RecordEndFadeWhite()
{
    g_Fade.wState = 0;
}

//----- (00421440) --------------------------------------------------------
void ActFade()
{
    int v0; // edx
    int v1; // edx

    if (g_Fade.state == 10)
    {
        if (g_Fade.bounds.bottom < 0)
            g_Fade.state = 0;
        else
            g_Fade.bounds.bottom -= 8;
    }
    else if (g_Fade.state == 20)
    {
        g_Fade.bounds.top -= 8;
        if (g_Fade.bounds.top < 0)
        {
            g_Fade.bounds.top = 0;
            g_Fade.state = 30;
        }
    }
    if (g_Fade.wState != 10)
    {
        if (g_Fade.wState != 20)
            return;
        goto LABEL_22;
    }
    g_Fade.wRect.top -= g_Fade.wCount;
    g_Fade.wRect.bottom += g_Fade.wCount;
    g_Fade.wRect2.left -= g_Fade.wCount;
    g_Fade.wRect2.right += g_Fade.wCount;
    if (g_Fade.wRect.top < 0)
        g_Fade.wRect.top = 0;
    if (g_Fade.wRect.bottom > 160)
        g_Fade.wRect.bottom = 160;
    if (g_Fade.wRect2.left < 0)
        g_Fade.wRect.left = 0;
    if (g_Fade.wRect2.right > 120)
        g_Fade.wRect.right = 120;
    v0 = g_Fade.wCount++;
    if (v0 >= 80)
    {
        g_Fade.wState = 20;
        g_Fade.wCount = 1;
        g_Fade.wRect.left = g_Fade.wX - 120;
        g_Fade.wRect.right = g_Fade.wX + 120;
        g_Fade.wRect2.left = 0;
        g_Fade.wRect2.right = 0;
    LABEL_22:
        g_Fade.wRect.left = g_Fade.wX - 120 / (3 * g_Fade.wCount);
        g_Fade.wRect.right = g_Fade.wX + 120 / (3 * g_Fade.wCount);
        if (g_Fade.wRect.left < 0)
            g_Fade.wRect.left = 0;
        if (g_Fade.wRect.right > 120)
            g_Fade.wRect.right = 120;
        v1 = g_Fade.wCount++;
        if (v1 > 24)
            g_Fade.wState = 0;
    }
}

//----- (00421650) --------------------------------------------------------
void PutFade(RECT *rcView)
{
    RECT rect; // [esp+4h] [ebp-20h] BYREF
    RECT v2;   // [esp+14h] [ebp-10h] BYREF

    rect.left = 0;
    rect.top = 0;
    rect.right = 120;
    rect.bottom = 8;
    v2.left = 0;
    v2.top = 8;
    v2.right = 120;
    v2.bottom = 16;
    if (g_Fade.wState)
    {
        CortBox(rcView, &g_Fade.wRect, Fade_wColor);
        CortBox(rcView, &g_Fade.wRect2, Fade_wColor);
    }
    switch (g_Fade.state)
    {
    case 10:
        CortBox(rcView, &g_Fade.bounds, Fade_color);
        PutBitmap3(rcView, 0, g_Fade.bounds.bottom, &rect, 12);
        break;
    case 20:
        CortBox(rcView, &g_Fade.bounds, Fade_color);
        PutBitmap3(rcView, 0, g_Fade.bounds.top - 8, &v2, 12);
        break;
    case 30:
        CortBox(rcView, &g_Fade.bounds, Fade_color);
        break;
    }
}