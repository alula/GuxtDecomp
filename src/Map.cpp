#include <windows.h>
#include <stdio.h>

#include "Map.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "PixFile.h"
#include "Stage.h"
#include "Text.h"
#include "WinMain.h"

TileMap mapStage;
TileMap attrStage;
char *centerTextBuffer = NULL;
static RECT unusedTextRender_ = {0, 0, 120, 8};

//----- (0041E4D0) --------------------------------------------------------
BOOL ResetMap()
{
    ClearTileMap(&mapStage);
    ClearTileMap(&attrStage);
    return TRUE;
}

//----- (0041E500) --------------------------------------------------------
int GetMapHeight()
{
    int result; // eax

    if (mapStage.data)
        result = mapStage.height;
    else
        result = 0;
    return result;
}

//----- (0041E520) --------------------------------------------------------
BOOL LoadMap(int id)
{
    CHAR Name[268]; // [esp+0h] [ebp-128h] BYREF
    BOOL v3;        // [esp+110h] [ebp-18h]
    PixFile a2;     // [esp+114h] [ebp-14h] BYREF

    v3 = 0;
    sprintf(Name, "%s\\map%d.pxmap", dataPath, id);
    ReleaseStageAttr(&mapStage);
    if (OpenResource_(0, Name, 0, &a2))
    {
        if (LoadStageAttr(&mapStage, &a2))
        {
            CloseResource_(&a2);
            sprintf(Name, "%s\\parts%d.pxatrb", dataPath, id);
            ReleaseStageAttr(&attrStage);
            if (OpenResource_(0, Name, 0, &a2))
            {
                if (LoadStageAttr(&attrStage, &a2))
                {
                    CloseResource_(&a2);
                    sprintf(Name, "parts%d", id);
                    ClearSurface(4);
                    if (LoadPximg(Name, 4))
                        v3 = 1;
                }
            }
        }
    }
    if (!v3)
    {
        ReleaseStageAttr(&mapStage);
        ReleaseStageAttr(&attrStage);
    }

    CloseResource_(&a2);

    return v3;
}

//----- (0041E690) --------------------------------------------------------
void PutMapParts(RECT *rcView)
{
    LONG tilesY;  // [esp+4h] [ebp-30h]
    LONG tilesH;  // [esp+8h] [ebp-2Ch]
    int scroll;   // [esp+Ch] [ebp-28h]
    int xoff;     // [esp+10h] [ebp-24h]
    int tile;     // [esp+18h] [ebp-1Ch]
    LONG j;       // [esp+1Ch] [ebp-18h]
    LONG i;       // [esp+20h] [ebp-14h]
    tagRECT rect; // [esp+24h] [ebp-10h] BYREF

    xoff = GetStageXOffset() / 1024;
    scroll = GetStageScroll() / 1024;
    tilesY = xoff / 16 + (rcView->right - rcView->left) / 16 + 2;
    tilesH = scroll / 16 + (rcView->bottom - rcView->top) / 16 + 2;

    if (tilesY > mapStage.width - 1)
        tilesY = mapStage.width - 1;
    if (tilesH > mapStage.height - 1)
        tilesH = mapStage.height - 1;

    for (i = 0; i <= tilesH; ++i)
    {
        for (j = 0; j <= tilesY; ++j)
        {
            tile = mapStage.data[j + mapStage.width * i];

            // the compiler generated `& 0x8000000f` there so `tile` was signed
            if (attrStage.data[(tile % 16) + attrStage.width * (tile / 16)] < 8u)
            {
                rect.left = 16 * (tile % 16);
                rect.right = rect.left + 16;
                rect.top = 16 * (tile / 16);
                rect.bottom = rect.top + 16;
                PutBitmap3(rcView, 16 * j - xoff, 16 * i - scroll, &rect, 4);
            }
        }
    }
}

//----- (0041E840) --------------------------------------------------------
void PutMapParts2(RECT *rcView)
{
    LONG tilesY;  // [esp+4h] [ebp-30h]
    LONG tilesH;  // [esp+8h] [ebp-2Ch]
    int scroll;   // [esp+Ch] [ebp-28h]
    int xoff;     // [esp+10h] [ebp-24h]
    int tile;     // [esp+18h] [ebp-1Ch]
    LONG j;       // [esp+1Ch] [ebp-18h]
    LONG i;       // [esp+20h] [ebp-14h]
    tagRECT rect; // [esp+24h] [ebp-10h] BYREF

    xoff = GetStageXOffset() / 1024;
    scroll = GetStageScroll() / 1024;
    tilesY = xoff / 16 + (rcView->right - rcView->left) / 16 + 2;
    tilesH = scroll / 16 + (rcView->bottom - rcView->top) / 16 + 2;

    if (tilesY > mapStage.width - 1)
        tilesY = mapStage.width - 1;
    if (tilesH > mapStage.height - 1)
        tilesH = mapStage.height - 1;

    for (i = 0; i <= tilesH; ++i)
    {
        for (j = 0; j <= tilesY; ++j)
        {
            tile = mapStage.data[j + mapStage.width * i];

            // the compiler generated `& 0x8000000f` there so `tile` was signed
            if (attrStage.data[(tile % 16) + attrStage.width * (tile / 16)] >= 8u)
            {
                rect.left = 16 * (tile % 16);
                rect.right = rect.left + 16;
                rect.top = 16 * (tile / 16);
                rect.bottom = rect.top + 16;
                PutBitmap3(rcView, 16 * j - xoff, 16 * i - scroll, &rect, 4);
            }
        }
    }
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

//----- (004267E0) --------------------------------------------------------
BOOL ClearTileMap(TileMap *map)
{
    memset(map, 0, sizeof(TileMap));

    return TRUE;
}

//----- (004269F0) --------------------------------------------------------
void FreeStageAttr(void **a1)
{
    if (*a1)
    {
        free(*a1);
        *a1 = 0;
    }
}

//----- (00426A20) --------------------------------------------------------
void ReleaseStageAttr(TileMap *a1)
{
    FreeStageAttr((void **)&a1->data);
    a1->width = 0;
    a1->height = 0;
}

//----- (00426A50) --------------------------------------------------------
int LoadStageAttr(TileMap *a1, PixFile *a2)
{
    int v3;    // [esp+0h] [ebp-Ch] BYREF
    size_t v4; // [esp+4h] [ebp-8h]
    int v5;    // [esp+8h] [ebp-4h]

    v5 = 0;
    ReleaseStageAttr(a1);
    if (ReadFromFile(&v3, 2u, 1, a2))
    {
        a1->width = v3;
        if (ReadFromFile(&v3, 2u, 1, a2))
        {
            a1->height = v3;
            v4 = a1->height * a1->width;
            a1->data = (unsigned char *)malloc(v4);
            if (a1->data)
            {
                if (ReadFromFile(a1->data, 1u, v4, a2))
                    v5 = 1;
            }
        }
    }

    if (!v5)
        ReleaseStageAttr(a1);

    return v5;
}