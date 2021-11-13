#include <windows.h>

#include "Text.h"
#include "Draw.h"

//----- (00417BD0) --------------------------------------------------------
void PutNumber(RECT *rcView, int x, int y, signed int value, char flags, unsigned int surf)
{
    int v6[7];     // [esp+0h] [ebp-10Ch]
    int nx;        // [esp+1Ch] [ebp-F0h]
    RECT a3;       // [esp+20h] [ebp-ECh] BYREF
    int v9;        // [esp+30h] [ebp-DCh]
    int ny;        // [esp+34h] [ebp-D8h]
    int j;         // [esp+38h] [ebp-D4h]
    RECT rect[10]; // [esp+3Ch] [ebp-D0h] BYREF
    int v13;       // [esp+E0h] [ebp-2Ch]
    int v14;       // [esp+E4h] [ebp-28h]
    int v15[7];    // [esp+E8h] [ebp-24h]
    int i;         // [esp+104h] [ebp-8h]
    int v17;       // [esp+108h] [ebp-4h]

    rect[0].left = 48;
    rect[0].top = 8;
    rect[0].right = 56;
    rect[0].bottom = 16;
    rect[1].left = 56;
    rect[1].top = 8;
    rect[1].right = 64;
    rect[1].bottom = 16;
    rect[2].left = 64;
    rect[2].top = 8;
    rect[2].right = 72;
    rect[2].bottom = 16;
    rect[3].left = 72;
    rect[3].top = 8;
    rect[3].right = 80;
    rect[3].bottom = 16;
    rect[4].left = 0;
    rect[4].top = 16;
    rect[4].right = 8;
    rect[4].bottom = 24;
    rect[5].left = 8;
    rect[5].top = 16;
    rect[5].right = 16;
    rect[5].bottom = 24;
    rect[6].left = 16;
    rect[6].top = 16;
    rect[6].right = 24;
    rect[6].bottom = 24;
    rect[7].left = 24;
    rect[7].top = 16;
    rect[7].right = 32;
    rect[7].bottom = 24;
    rect[8].left = 32;
    rect[8].top = 16;
    rect[8].right = 40;
    rect[8].bottom = 24;
    rect[9].left = 40;
    rect[9].top = 16;
    rect[9].right = 48;
    rect[9].bottom = 24;
    a3.left = 104;
    a3.top = 0;
    a3.right = 112;
    a3.bottom = 8;
    v6[0] = 0;
    v6[1] = 1;
    v6[2] = 10;
    v6[3] = 100;
    v6[4] = 1000;
    v6[5] = 10000;
    v6[6] = 100000;
    v15[0] = 0;
    v15[1] = 9;
    v15[2] = 99;
    v15[3] = 999;
    v15[4] = 9999;
    v15[5] = 99999;
    v15[6] = 999999;
    v9 = 0;
    v13 = 0;
    j = 0;
    v14 = flags & 0xF;
    nx = x;
    ny = y;
    v17 = 0;
    if ((flags & 0xF) != 0)
    {
        if (value > v15[v14])
            value = v15[v14];
        if (value < 0)
        {
            value = -value;
            v13 = 1;
            ++v17;
        }
        for (i = 6; i > 1 && value < v6[i]; --i)
            ;
        v17 += 6 * i;
        if ((flags & 0x10) != 0)
        {
            nx -= v17 / 2;
            ny -= 4;
        }
        for (j = v14; j > 0; --j)
        {
            i = value / v6[j];
            value %= v6[j];
            if (v13 && i && !v9)
            {
                if (surf)
                    PutBitmap4(nx, ny, &a3, surf, 9u);
                else
                    PutBitmap3(rcView, nx - 6, ny, &a3, 9);
            }
            if (v9 || i || j == 1)
            {
                if (surf)
                    PutBitmap4(nx, ny, &rect[i], surf, 9u);
                else
                    PutBitmap3(rcView, nx, ny, &rect[i], 9);
            }
            if (i)
                v9 = 1;
            nx += 6;
        }
    }
}

//----- (00418010) --------------------------------------------------------
int PutTextObject(RECT *rcView, int pos_x, int pos_y, const char *text, int a5, int surf_src)
{
    int x;               // [esp+0h] [ebp-24h]
    int y;               // [esp+4h] [ebp-20h]
    signed int text_len; // [esp+8h] [ebp-1Ch]
    signed int i;        // [esp+Ch] [ebp-18h]
    int v11;             // [esp+10h] [ebp-14h]
    RECT a3;             // [esp+14h] [ebp-10h] BYREF

    x = pos_x;
    y = pos_y;
    text_len = strlen(text);
    if ((a5 & 0x10) != 0)
    {
        x = pos_x - 6 * text_len / 2;
        y = pos_y - 4;
    }
    for (i = 0; i < text_len; ++i)
    {
        v11 = text[i] - 32;
        a3.left = 8 * (v11 % 10);
        a3.right = a3.left + 8;
        a3.top = 8 * (v11 / 10);
        a3.bottom = a3.top + 8;
        if (surf_src)
            PutBitmap4(x, y, &a3, surf_src, 9u);
        else
            PutBitmap3(rcView, x, y, &a3, 9);
        x += 6;
    }
    return x;
}
