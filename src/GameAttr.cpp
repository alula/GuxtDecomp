#include <windows.h>
#include <stdio.h>

#include "GameAttr.h"
#include "Caret.h"
#include "Draw.h"
#include "Game.h"
#include "Ship.h"
#include "Sound.h"
#include "Stage.h"
#include "Text.h"
#include "WinMain.h"

StageState g_StageState;

#define NUM_MUSIC 11
const char *musicTable[NUM_MUSIC] = {
    "-",
    "opening",
    "boss",
    "gameover",
    "stage1",
    "stage2",
    "stage3",
    "stage4",
    "stage5",
    "boss2",
    "ending",
};

//----- (00419390) --------------------------------------------------------
BOOL InitGameAttr()
{
    memset(&g_StageState, 0, sizeof(StageState));

    for (int i = 1; i < NUM_MUSIC; ++i)
    {
        if (!LoadMusic(musicTable[i]))
            return 0;
    }

    CheckGameCleared();
    return ResetStageSurface();
}

const char *clearedFile = "cleared.bin";
const char *clearedMentama = "mentama.";

//----- (004193F0) --------------------------------------------------------
void CheckGameCleared()
{
    char v0[264]; // [esp+0h] [ebp-220h] BYREF
    char v1[268]; // [esp+108h] [ebp-118h] BYREF
    int v2;       // [esp+218h] [ebp-8h]
    FILE *v3;     // [esp+21Ch] [ebp-4h]

    v2 = 0;
    sprintf(v0, "%s\\%s", temp_guxtPath, clearedFile);
    v3 = fopen(v0, "rt");
    memset(v1, 0, 0x104u);

    if (v3 && fscanf(v3, "%s\n", v1) == 1 && !strcmp(v1, clearedMentama))
        v2 = 1;

    if (v3)
        fclose(v3);

    if (v2)
        g_StageState.gameFlags |= 4u;
    else
        g_StageState.gameFlags &= ~4u;
}

//----- (004194E0) --------------------------------------------------------
void CallPutCenterText()
{
    PutCenterText();
}

//----- (004194F0) --------------------------------------------------------
void CallClearCenterText()
{
    ResetStageText();
}

//----- (00419500) --------------------------------------------------------
void SetInReplay(BOOL state)
{
    if (state)
        g_StageState.gameFlags |= 1u;
    else
        g_StageState.gameFlags &= 0xFFFFFFFE;
}

//----- (00419530) --------------------------------------------------------
void SetInScoreAttack(BOOL state)
{
    if (state)
        g_StageState.gameFlags |= 2u;
    else
        g_StageState.gameFlags &= ~2u;
}

//----- (00419560) --------------------------------------------------------
void SetGameCleared(BOOL state)
{
    if (state)
        g_StageState.gameFlags |= 4u;
    else
        g_StageState.gameFlags &= ~4u;
}

//----- (00419590) --------------------------------------------------------
BOOL GetInReplay()
{
    return (g_StageState.gameFlags & 1u) != 0;
}

//----- (004195B0) --------------------------------------------------------
BOOL GetInScoreAttack()
{
    return (g_StageState.gameFlags & 2u) != 0;
}

//----- (004195D0) --------------------------------------------------------
BOOL GetGameCleared()
{
    return (g_StageState.gameFlags & 4u) != 0;
}

//----- (004195F0) --------------------------------------------------------
BOOL ChangeMusic(int idx)
{
    BOOL result; // [esp+0h] [ebp-4h]

    result = FALSE;
    if ((g_StageState.state == 30 || g_StageState.state == 31) && idx != 1)
        return TRUE;

    if (idx)
    {
        if (idx != g_StageState.currentMusic && (!LoadMusic(musicTable[idx]) || !StartMusic(0)))
            goto err;
    }
    else
    {
        SetMusicVolume(3000);
    }

    g_StageState.currentMusic = idx;
    result = TRUE;

err:
    return result;
}

//----- (00419680) --------------------------------------------------------
BOOL GameStart()
{
    g_StageState.currentStage = 1;
    g_StageState.shipLivesCount = (g_StageState.gameFlags & 2) == 0;
    FreeStageText();
    ResetShip();
    return 1;
}

//----- (004196C0) --------------------------------------------------------
int GetCurrentStage()
{
    return g_StageState.currentStage;
}

//----- (004196D0) --------------------------------------------------------
int IncreaseLives()
{
    PlaySound(41);
    return ++g_StageState.shipLivesCount;
}

//----- (004196F0) --------------------------------------------------------
void SetCurrentStage(int stage)
{
    g_StageState.currentStage = stage;
}

//----- (00419D50) --------------------------------------------------------
void PutHUD(RECT *rcView)
{
    RECT v1;   // [esp+4h] [ebp-30h] BYREF
    RECT rect; // [esp+14h] [ebp-20h] BYREF
    RECT v3;   // [esp+24h] [ebp-10h] BYREF

    v1.left = 96;
    v1.top = 0;
    v1.right = 112;
    v1.bottom = 8;
    rect.left = 72;
    rect.top = 80;
    rect.right = 104;
    rect.bottom = 88;
    v3.left = 120;
    v3.top = 48;
    v3.right = 128;
    v3.bottom = 56;
    switch (g_StageState.state)
    {
    case 0:
        PutRect(48, 56, &v1, 11);
        if ((g_StageState.gameFlags & 2) != 0)
            PutRect(64, 56, &v3, 11);
        else
            PutNumber(rcView, 64, 56, g_StageState.shipLivesCount, 1, 0);
        break;
    case 10:
    case 30:
    case 50:
        PutScore(rcView, 36, 4);
        PutRect(4, 4, &v1, 11);
        if ((g_StageState.gameFlags & 2) != 0)
            PutRect(20, 4, &v3, 11);
        else
            PutNumber(rcView, 20, 4, g_StageState.shipLivesCount, 1, 0);
        break;
    case 20:
        PutRect(24, 56, &rect, 11);
        PutScore(rcView, 52, 56);
        break;
    default:
        break;
    }

    PutTextBuffer(rcView);
}

//----- (00419EF0) --------------------------------------------------------
void PutCenter()
{
    CallPutCenterText();
}

static int ScoreTbl[8] = {0, 1, 2, 5, 10, 20, 50, 100};
static int LivesScoreThresholds[12] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 65535};

int gScore;
int LivesIncreaseCount;
int StageScroll;
int dword_44C854;
int StageScrollSpeed;

//----- (00420F50) --------------------------------------------------------
int GetScore()
{
    return gScore;
}

//----- (00420F60) --------------------------------------------------------
void SetScore(int score)
{
    gScore = score;
}

//----- (00420F70) --------------------------------------------------------
void AddScore(int score_idx)
{
    gScore += ScoreTbl[score_idx];

    if (!GetInScoreAttack() && gScore >= LivesScoreThresholds[LivesIncreaseCount])
    {
        ++LivesIncreaseCount;
        IncreaseLives();
        SetCaret(3, 0, 0, 0);
    }
}

//----- (00420FD0) --------------------------------------------------------
void PutScore(RECT *rcView, int x, int y)
{
    RECT rect; // [esp+0h] [ebp-10h] BYREF

    rect.left = 112;
    rect.top = 24;
    rect.right = 120;
    rect.bottom = 32;
    if (gScore)
        PutNumber(rcView, x, y, gScore, 6, 0);
    PutRect(x + 36, y, &rect, 11);
}

//----- (00421040) --------------------------------------------------------
void SetDefaultStageScroll()
{
    StageScroll = (16 * GetStageHeight() - (scWOffset_0.bottom - scWOffset_0.top)) << 10;
}

//----- (00421070) --------------------------------------------------------
void SetStageScrollShift(int scroll)
{
    StageScroll = scroll << 14;
}
