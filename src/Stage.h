#ifndef __STAGE_H__
#define __STAGE_H__

#include <windows.h>

#include "Event.h"
#include "Input.h"

struct StageState
{
    int state;
    int centerTextMiscTimer;
    int currentStage;
    int currentMusic;
    int shipLivesCount;
    int checkpointStageScroll;
    int gameFlags;
};

extern EntityStageStruct EntityStage;
extern int EntityStageCount;
extern char szFile[MAX_PATH];
extern StageState g_StageState;

extern int debugStage;
extern int debugStageScroll;
extern int debugSpeed;
extern int debugPowerup;
extern int debugLife;

void PrepPxeve();
BOOL ResetEntityStage();
BOOL LoadPxeve(int stage);
BOOL LoadPximgEnemy(int stage);
void ZeroEntityCount();
BOOL SetStageEntities();
BOOL SetStageEntitiesPartial();

int GetCurrentStage();
int IncreaseLives();
void SetCurrentStage(int stage);
BOOL StartStage();
BOOL InitStage();
int SetCheckpointScroll();
BOOL CheckStageClear(int a1);
BOOL ShipCrushProc2();
int ActStageState(TriggerStruct *a1);
int WriteGameCleared();
void EndRecordPlayback();
void PutHUD(RECT *rcView);
void PutCenter();

#endif