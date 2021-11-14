#include <windows.h>
#include <stdio.h>

#include "PixFile.h"

//----- (00421F50) --------------------------------------------------------
BOOL OpenResource_(HMODULE hModule, LPCSTR lpName, LPCSTR lpType, PixFile *file)
{
    HRSRC hResInfo;   // [esp+0h] [ebp-8h]
    HGLOBAL hResData; // [esp+4h] [ebp-4h]

    memset(file, 0, sizeof(PixFile));
    if (lpType)
    {
        hResInfo = FindResourceA(hModule, lpName, lpType);
        if (!hResInfo)
            return FALSE;
        file->size = SizeofResource(hModule, hResInfo);
        if (!file->size)
            return FALSE;
        hResData = LoadResource(hModule, hResInfo);
        if (!hResData)
            return FALSE;
        file->res = (char *)LockResource(hResData);
        if (!file->res)
            return FALSE;
        file->type = 0;
    }
    else
    {
        file->fp = fopen(lpName, "rb");
        if (!file->fp)
            return FALSE;
        file->type = 1;
    }

    return TRUE;
}

//----- (00422030) --------------------------------------------------------
int ReadFromFile(void *p, size_t size, int num, PixFile *_p_desc)
{
    if (_p_desc->type)
    {
        if (fread(p, size, num, _p_desc->fp) != num)
            return 0;
    }
    else
    {
        for (int i = 0; i < num; ++i)
        {
            if ((size + _p_desc->bytesRead) > _p_desc->size)
                return 0;
            memcpy(&((char *)p)[i], _p_desc->res + _p_desc->bytesRead, size);
            _p_desc->bytesRead += size;
        }
    }
    return 1;
}

//----- (004220D0) --------------------------------------------------------
BOOL SeekResource(PixFile *file, int pos, int mode)
{
    if (file->type)
    {
        if (fseek(file->fp, pos, mode))
            return 0;
    }
    else if (mode)
    {
        if (mode == 1)
        {
            if ((pos + file->bytesRead) >= file->size)
                return FALSE;

            file->bytesRead += pos;
        }
        else if (mode == 2)
        {
            return FALSE;
        }
    }
    else
    {
        if (pos >= file->size)
            return FALSE;

        file->bytesRead = pos;
    }
    return TRUE;
}

//----- (00422170) --------------------------------------------------------
void CloseResource_(PixFile *a1)
{
    if (a1->type)
    {
        if (a1->fp)
        {
            fclose(a1->fp);
            a1->fp = NULL;
        }
    }
    else if (a1->res)
    {
        a1->res = NULL;
    }
}

//----- (004221C0) --------------------------------------------------------
int VariableLengthCheck(int val)
{
    if ((unsigned int)val < 0x80)
        return 1;
    if ((unsigned int)val < 0x4000)
        return 2;
    if ((unsigned int)val < 0x200000)
        return 3;
    if ((unsigned int)val >= 0x10000000)
        return 5;

    return 4;
}

//----- (00422220) --------------------------------------------------------
BOOL VariableLengthWrite(int val, FILE *fp, int *tgt_pos)
{
    unsigned char v4[5]; // [esp+4h] [ebp-14h] BYREF
    unsigned char v5[5]; // [esp+Ch] [ebp-Ch] BYREF

    *reinterpret_cast<int *>(v5) = val;
    v5[4] = 0;
    if (val >= 0x80)
    {
        if (val >= 0x4000)
        {
            if (val >= 0x200000)
            {
                if (val >= 0x10000000)
                {
                    v4[0] = v5[0] & 0x7F | 0x80;
                    v4[1] = (2 * v5[1]) & 0x7F | (v5[0] >> 7) | 0x80;
                    v4[2] = (4 * v5[2]) & 0x7F | (v5[1] >> 6) | 0x80;
                    v4[3] = (8 * v5[3]) & 0x7F | (v5[2] >> 5) | 0x80;
                    v4[4] = (16 * v5[4]) & 0x7F | (v5[3] >> 4);

                    if (fwrite(v4, 1u, 5u, fp) == 5)
                    {
                        if (tgt_pos)
                            *tgt_pos += 5;
                        return TRUE;
                    }
                    else
                    {
                        return FALSE;
                    }
                }
                else
                {
                    v4[0] = v5[0] & 0x7F | 0x80;
                    v4[1] = (2 * v5[1]) & 0x7F | (v5[0] >> 7) | 0x80;
                    v4[2] = (4 * v5[2]) & 0x7F | (v5[1] >> 6) | 0x80;
                    v4[3] = (8 * v5[3]) & 0x7F | (v5[2] >> 5);

                    if (fwrite(v4, 1u, 4u, fp) == 4)
                    {
                        if (tgt_pos)
                            *tgt_pos += 4;
                        return TRUE;
                    }
                    else
                    {
                        return FALSE;
                    }
                }
            }
            else
            {
                v4[0] = v5[0] & 0x7F | 0x80;
                v4[1] = (2 * v5[1]) & 0x7F | (v5[0] >> 7) | 0x80;
                v4[2] = (4 * v5[2]) & 0x7F | (v5[1] >> 6);

                if (fwrite(v4, 1u, 3u, fp) == 3)
                {
                    if (tgt_pos)
                        *tgt_pos += 3;
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
        else
        {
            v4[0] = v5[0] & 0x7F | 0x80;
            v4[1] = (2 * v5[1]) & 0x7F | (v5[0] >> 7);

            if (fwrite(v4, 1u, 2u, fp) == 2)
            {
                if (tgt_pos)
                    *tgt_pos += 2;
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
    else if (fwrite(v5, 1u, 1u, fp) == 1)
    {
        if (tgt_pos)
            ++*tgt_pos;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//----- (00422500) --------------------------------------------------------
// Variable length reading (guaranteed up to int32_t)
BOOL VariableLengthRead(int *p, PixFile *a2)
{
    unsigned char b[4]; // [esp+4h] [ebp-18h]
    int i;                // [esp+Ch] [ebp-10h]
    unsigned char a[5]; // [esp+10h] [ebp-Ch] BYREF

    b[3] = 0;
    b[2] = 0;
    b[1] = 0;
    b[0] = 0;
    for (i = 0; i < 5; ++i)
    {
        if (!ReadFromFile(&a[i], 1u, 1, a2))
            return FALSE;

        if ((a[i] & 0x80) == 0)
            break;
    }

    switch (i)
    {
    case 0:
        b[0] = a[0] & 0x7F;
        break;
    case 1:
        b[0] = (a[1] << 7) | a[0] & 0x7F;
        b[1] = (a[1] & 0x7F) >> 1;
        break;
    case 2:
        b[0] = (a[1] << 7) | a[0] & 0x7F;
        b[1] = (a[2] << 6) | ((a[1] & 0x7F) >> 1);
        b[2] = (a[2] & 0x7F) >> 2;
        break;
    case 3:
        b[0] = (a[1] << 7) | a[0] & 0x7F;
        b[1] = (a[2] << 6) | ((a[1] & 0x7F) >> 1);
        b[2] = (32 * a[3]) | ((a[2] & 0x7F) >> 2);
        b[3] = (a[3] & 0x7F) >> 3;
        break;
    case 4:
        b[0] = (a[1] << 7) | a[0] & 0x7F;
        b[1] = (a[2] << 6) | ((a[1] & 0x7F) >> 1);
        b[2] = (32 * a[3]) | ((a[2] & 0x7F) >> 2);
        b[3] = (16 * a[4]) | ((a[3] & 0x7F) >> 3);
        break;
    case 5:
        return FALSE;
    default:
        break;
    }

    *p = *(reinterpret_cast<int *>(b));
    return TRUE;
}