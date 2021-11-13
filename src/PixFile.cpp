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
        file->res = LockResource(hResData);
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
            memcpy(p + i, _p_desc->res + _p_desc->bytesRead, size);
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
