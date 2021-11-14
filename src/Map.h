#ifndef __MAP_H__
#define __MAP_H__

#include <windows.h>

#include "PixFile.h"

struct TileMap
{
    int width;
    int height;
    unsigned char *data;
};

extern TileMap mapStage;
extern TileMap attrStage;

BOOL ResetMap();
int GetMapHeight();
BOOL LoadMap(int id);
void PutMapParts(RECT *rcView);
void PutMapParts2(RECT *rcView);
int GetTile(int x, int y);
void ShiftTile(int x, int y);
BOOL ResetStageSurface();
void ResetStageText();
void FreeStageText();
void PutStageText(const char *text);
void PutTextBuffer(RECT *rcView);
void PutCenterText();

BOOL ClearTileMap(TileMap *map);
void FreeStageAttr(void **a1);
void ReleaseStageAttr(TileMap *a1);
BOOL LoadStageAttr(TileMap *a1, PixFile *a2);

#endif