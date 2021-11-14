#include <windows.h>

#include "Ending.h"
#include "Draw.h"
#include "Game.h"
#include "WinMain.h"

Ending endingState;

static EndingTextPos endingTextPosTbl[27] = {
    {44, 30},
    {60, 30},
    {60, 50},
    {60, 30},
    {60, 40},
    {80, 50},
    {60, 50},
    {60, 50},
    {60, 40},
    {60, 40},
    {60, 50},
    {60, 50},
    {60, 70},
    {74, 40},
    {40, 32},
    {60, 50},
    {40, 30},
    {40, 50},
    {60, 70},
    {80, 50},
    {60, 24},
    {60, 24},
    {60, 24},
    {60, 24},
    {60, 24},
    {60, 24},
    {60, 24},
};

//----- (00418C40) --------------------------------------------------------
void InitEnding()
{
    LoadPximg("enemy_name", 25);
    memset(&endingState, 0, sizeof(endingState));
    endingState.count = -1;
}

//----- (00418C70) --------------------------------------------------------
void UnusedResetEndingText()
{
    memset(&endingState, 0, sizeof(endingState));
    endingState.count = -1;
}

//----- (00418C90) --------------------------------------------------------
void ShowNextEndingText()
{
    endingState.running = TRUE;
    ++endingState.count;
    endingState.timer = 0;
    endingState.unused = 0;
    endingState.pos_x = endingTextPosTbl[endingState.count].x << 10;
    endingState.pos_y = endingTextPosTbl[endingState.count].y << 10;
}

//----- (00418CF0) --------------------------------------------------------
void EndingTextRunTimer()
{
    if (endingState.running)
    {
        if (++endingState.timer > 100)
            endingState.running = 0;
    }
}

//----- (00418D20) --------------------------------------------------------
void PutEndingText()
{
    RECT rect; // [esp+0h] [ebp-10h] BYREF

    if (!endingState.running)
        return;

    rect.left = (endingState.count / 16) << 6;
    rect.top = 8 * (endingState.count % 16);
    rect.right = rect.left + 64;
    rect.bottom = rect.top + 8;
    PutBitmap3(&scWOffset_0, endingState.pos_x / 1024 - 32, endingState.pos_y / 1024 - 4, &rect, 25);
}

//----- (00418DB0) --------------------------------------------------------
BOOL CheckEndingTextCount()
{
    return endingState.count >= 25;
}