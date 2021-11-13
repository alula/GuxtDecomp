#ifndef __GAMEATTR_H__
#define __GAMEATTR_H__

#include <windows.h>
#include "Object.h"

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

extern StageState g_StageState;

BOOL InitGameAttr();

void CheckGameCleared();

void CallPutCenterText();
void CallClearCenterText();

void SetInReplay(BOOL state);
void SetInScoreAttack(BOOL state);
void SetGameCleared(BOOL state);

BOOL GetInReplay();
BOOL GetInScoreAttack();
BOOL GetGameCleared();

BOOL ChangeMusic(int idx);
BOOL GameStart();
int GetCurrentStage();
int IncreaseLives();
void SetCurrentStage(int stage);

void PutHUD(RECT *rcView);
void PutCenter();

extern int gScore;
extern int LivesIncreaseCount;
extern int StageScroll;
extern int dword_44C854;
extern int StageScrollSpeed;

void DoNothing(int a1);
BOOL LoadPximgSymbol();
BOOL ResetScore();
int GetScore();
void SetScore(int score);
void AddScore(int score_idx);
void PutScore(RECT *rcView, int x, int y);

void SetDefaultStageScroll();
void SetStageScrollShift(int scroll);
void Set44C854(int a1);
void SetScrollSpeed(int speed);
void SetStageXOffset(int x_offset);
void SetStageScroll_0(int scroll);
int GetCheckpointScrollValue();
int GetStageXOffset();
int GetStageScroll();
int Get44C854();
int GetStageScrollSpeed();

void AlignStageScroll(Object *o);
void ActStageScroll();
void AddStageXOScroll(int *a1, int *a2);
void SubStageXOScroll(int *a1, int *a2);

#endif