#ifndef __ENDING_H__
#define __ENDING_H__

#include <windows.h>

struct Ending
{
    BOOL running;
    int pos_x;
    int pos_y;
    int unused;
    int count;
    int timer;
};

struct EndingTextPos
{
    int x;
    int y;
};

void InitEnding();

void UnusedResetEndingText();

void ShowNextEndingText();

void EndingTextRunTimer();

void PutEndingText();

BOOL CheckEndingTextCount();

#endif