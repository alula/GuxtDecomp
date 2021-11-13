#ifndef __GAMEATTR_H__
#define __GAMEATTR_H__

#include <windows.h>

struct StageState {
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

void SetInReplay(BOOL state);
void SetInScoreAttack(BOOL state);
void SetGameCleared(BOOL state);

BOOL GetInReplay();
BOOL GetInScoreAttack();
BOOL GetGameCleared();

void PutHUD(RECT *rcView);
void PutCenter();

extern int gScore;
extern int LivesIncreaseCount;
extern int StageScroll;
extern int dword_44C854;
extern int StageScrollSpeed;

int GetScore();
void SetScore(int score);
void AddScore(int score_idx);
void PutScore(RECT *rcView, int x, int y);

void SetDefaultStageScroll();
void SetStageScrollShift(int scroll);

#endif