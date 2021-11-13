#ifndef __STAGE_H__
#define __STAGE_H__

#include <windows.h>

struct TileMap
{
    int width;
    int height;
    unsigned char *data;
};

extern TileMap mapStage;
extern TileMap attrStage;

BOOL ResetStage();
int GetStageHeight();

int GetTile(int x, int y);
void ShiftTile(int x, int y);
BOOL ResetStageSurface();
void ResetStageText();
void FreeStageText();
void PutStageText(const char *text);

void PutTextBuffer(RECT *rcView);

void PutCenterText();

BOOL ClearTileMap(TileMap *map);

#endif