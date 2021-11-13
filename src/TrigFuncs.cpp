#include <math.h>

#include "TrigFuncs.h"

short gTanTbl[36];
int gSinTbl[256];

//----- (004219E0) --------------------------------------------------------
void InitTriangleTable()
{
    for (int i = 0; i < 256; ++i)
        gSinTbl[i] = (sin(i * 6.2832 / 256.0) * 1024.0);

    for (int j = 0; j < 33; ++j)
    {
        float a1 = j * 6.2831855 / 256.0;
        float v0 = sin(a1);
        gTanTbl[j] = (v0 / cos(a1) * 8192.0);
    }
}

//----- (00421AA0) --------------------------------------------------------
int GetSin(unsigned char a1)
{
    return gSinTbl[a1];
}

//----- (00421AB0) --------------------------------------------------------
int GetCos(unsigned char a1)
{
    return gSinTbl[(a1 + 64) % 256];
}

//----- (00421AE0) --------------------------------------------------------
unsigned char GetArktan(int x, int y, char a3)
{
    unsigned char a; // [esp+7h] [ebp-1h]
    int xa;          // [esp+10h] [ebp+8h]
    int ya;          // [esp+14h] [ebp+Ch]

    xa = -x;
    ya = -y;
    a = 0;
    if (xa <= 0)
    {
        if (xa >= 0)
        {
            if (ya >= 0)
            {
                if (ya <= 0)
                    a = a3;
                else
                    a = 64;
            }
            else
            {
                a = -64;
            }
        }
        else if (ya <= 0)
        {
            if (ya >= 0)
            {
                a = 0x80;
            }
            else if (-xa <= -ya)
            {
                while ((-8192 * xa / -ya) > gTanTbl[a])
                    ++a;
                a = -64 - a;
            }
            else
            {
                while ((-8192 * ya / -xa) > gTanTbl[a])
                    ++a;
                a += 0x80;
            }
        }
        else if (-xa <= ya)
        {
            while ((-8192 * xa / ya) > gTanTbl[a])
                ++a;
            a += 64;
        }
        else
        {
            while (((ya << 13) / -xa) > gTanTbl[a])
                ++a;
            a = 0x80 - a;
        }
    }
    else if (ya <= 0)
    {
        if (ya >= 0)
        {
            a = 0;
        }
        else if (xa <= -ya)
        {
            while (((xa << 13) / -ya) > gTanTbl[a])
                ++a;
            a -= 64;
        }
        else
        {
            while ((-8192 * ya / xa) > gTanTbl[a])
                ++a;
            a = -a;
        }
    }
    else if (xa <= ya)
    {
        while (((xa << 13) / ya) > gTanTbl[a])
            ++a;
        a = 64 - a;
    }
    else
    {
        while (((ya << 13) / xa) > gTanTbl[a])
            ++a;
    }
    return a;
}