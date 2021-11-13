#include <windows.h>

#include "WinDebugDrag.h"

CHAR szFile[MAX_PATH];

//----- (004192A0) --------------------------------------------------------
void DragEnable(HWND hWnd)
{
    DragAcceptFiles(hWnd, TRUE);
    memset(szFile, 0, sizeof(szFile));
}

//----- (004192D0) --------------------------------------------------------
BOOL DragFileProc(HWND hWnd, HDROP hDrop)
{
    BOOL result; // [esp+0h] [ebp-8h]

    result = FALSE;

    memset(szFile, 0, sizeof(szFile));
    if (DragQueryFileA(hDrop, 0xFFFFFFFF, 0, 0))
    {
        DragQueryFileA(hDrop, 0, szFile, 0x104u);
        result = TRUE;
    }

    DragFinish(hDrop);

    return result;
}

//----- (00419340) --------------------------------------------------------
BOOL CheckDragFile()
{
    return strlen(szFile) != 0;
}

//----- (00419360) --------------------------------------------------------
const char *GetDragFile()
{
    return szFile;
}

//----- (00419370) --------------------------------------------------------
void InitDragFile()
{
    memset(szFile, 0, sizeof(szFile));
}