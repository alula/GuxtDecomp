#include <windows.h>

#include "Stage.h"
#include "Draw.h"
#include "Text.h"

TileMap mapStage;
TileMap attrStage;
char *centerTextBuffer = NULL;
static RECT unusedTextRender_ = {0, 0, 120, 8};

//----- (0041E4D0) --------------------------------------------------------
BOOL ResetStage()
{
    ClearTileMap(&mapStage);
    ClearTileMap(&attrStage);
    return TRUE;
}

//----- (0041E500) --------------------------------------------------------
int GetStageHeight()
{
    int result; // eax

    if (mapStage.data)
        result = mapStage.height;
    else
        result = 0;
    return result;
}

//----- (0041E9F0) --------------------------------------------------------
int GetTile(int x, int y)
{
    if (x < 0 || y < 0)
        return 0;

    int index = x + y * mapStage.width;
    if (index >= mapStage.height * mapStage.width)
        return 0;

    int index2 = (mapStage.data[index] & 0xF) + attrStage.width * (mapStage.data[index] / 16);
    if (index2 < attrStage.height * attrStage.width)
        return attrStage.data[index2];

    return 0;
}

//----- (0041EA90) --------------------------------------------------------
void ShiftTile(int x, int y)
{

    if (x >= 0 && y >= 0)
    {
        int v2 = x + y * mapStage.width;
        if (v2 < mapStage.height * mapStage.width)
            --mapStage.data[v2];
    }
}

//----- (0041EAF0) --------------------------------------------------------
BOOL ResetStageSurface()
{
    return InitSurface(120, 8, 10, 1);
}

//----- (0041EB10) --------------------------------------------------------
void ResetStageText()
{
    if (centerTextBuffer)
    {
        free(centerTextBuffer);
        centerTextBuffer = 0;
    }
}

//----- (0041EB40) --------------------------------------------------------
void FreeStageText()
{
    BlitSurface(&unusedTextRender_, 0, 10);
    if (centerTextBuffer)
    {
        free(centerTextBuffer);
        centerTextBuffer = 0;
    }
}

//----- (0041EB80) --------------------------------------------------------
void PutStageText(const char *text)
{
    BlitSurface(&unusedTextRender_, 0, 10);
    if (text)
    {
        PutTextObject(&unusedTextRender_, 60, 4, text, 16, 10);
        if (centerTextBuffer)
        {
            free(centerTextBuffer);
            centerTextBuffer = 0;
        }
        size_t v1 = strlen(text) + 1;
        centerTextBuffer = (char *)malloc(v1);
        memcpy(centerTextBuffer, text, v1);
    }
}

//----- (0041EC20) --------------------------------------------------------
void PutTextBuffer(RECT *rcView)
{
    PutBitmap3(rcView, 0, 76, &unusedTextRender_, 10);
}

//----- (0041EC40) --------------------------------------------------------
void PutCenterText()
{
    if (centerTextBuffer)
        PutTextObject(&unusedTextRender_, 60, 4, centerTextBuffer, 16, 10);
}

// TODO: where to put this?
//----- (004267E0) --------------------------------------------------------
BOOL ClearTileMap(TileMap *map)
{
    memset(map, 0, sizeof(TileMap));

    return TRUE;
}