#include <windows.h>
#include <stdio.h>

#include "GameAttr.h"
#include "Caret.h"
#include "Draw.h"
#include "Game.h"
#include "Map.h"
#include "Ship.h"
#include "Sound.h"
#include "Stage.h"
#include "Text.h"
#include "WinMain.h"

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
    return TRUE;
}

static int GameDelay;

//----- (00421960) --------------------------------------------------------
void ResetGameDelay()
{
    GameDelay = 0;
}

//----- (00421970) --------------------------------------------------------
void SetGameDelay(int a1)
{
    GameDelay = a1;
}

//----- (00421980) --------------------------------------------------------
BOOL IsGameDelay()
{
    return GameDelay != 0;
}

//----- (004219A0) --------------------------------------------------------
BOOL GetGameDelayed()
{
    if (GameDelay && GameDelay != -1)
        --GameDelay;
    return GameDelay != 0;
}

static int ScoreTbl[8] = {0, 1, 2, 5, 10, 20, 50, 100};
static int LivesScoreThresholds[12] = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 65535};

int gScore;
int LivesIncreaseCount;
int StageScroll;
int dword_44C854;
int StageScrollSpeed;
int StageXOffset = 0x1000;

//----- (00420EF0) --------------------------------------------------------
void DoNothing(int a1)
{
    ;
}

//----- (00420F00) --------------------------------------------------------
BOOL LoadPximgSymbol()
{
    LoadPximg("symbol", 11);
    gScore = 0;
    LivesIncreaseCount = 0;
    return 1;
}

//----- (00420F30) --------------------------------------------------------
BOOL ResetScore()
{
    gScore = 0;
    LivesIncreaseCount = 0;
    return 1;
}

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
    StageScroll = (16 * GetMapHeight() - (scWOffset_0.bottom - scWOffset_0.top)) << 10;
}

//----- (00421070) --------------------------------------------------------
void SetStageScrollShift(int scroll)
{
    StageScroll = scroll << 14;
}

//----- (00421090) --------------------------------------------------------
void Set44C854(int a1)
{
    dword_44C854 = a1;
}

//----- (004210A0) --------------------------------------------------------
void SetScrollSpeed(int speed)
{
    StageScrollSpeed = speed;
}

//----- (004210B0) --------------------------------------------------------
void SetStageXOffset(int x_offset)
{
    StageXOffset = x_offset;
}

//----- (004210C0) --------------------------------------------------------
void SetStageScroll_0(int scroll)
{
    StageScroll = scroll;
}

//----- (004210D0) --------------------------------------------------------
int GetCheckpointScrollValue()
{
    return StageScroll / 1024 / 16;
}

//----- (004210F0) --------------------------------------------------------
int GetStageXOffset()
{
    return StageXOffset;
}

//----- (00421100) --------------------------------------------------------
int GetStageScroll()
{
    return StageScroll;
}

//----- (00421110) --------------------------------------------------------
int Get44C854()
{
    return dword_44C854;
}

//----- (00421120) --------------------------------------------------------
int GetStageScrollSpeed()
{
    return StageScrollSpeed;
}

//----- (00421130) --------------------------------------------------------
void GetStageRect(RECT *a1)
{
  a1->left = StageXOffset;
  a1->right = StageXOffset + ((scWOffset_0.right - scWOffset_0.left) << 10);
  a1->top = StageScroll;
  a1->bottom = StageScroll + ((scWOffset_0.bottom - scWOffset_0.top) << 10);
}

//----- (00421190) --------------------------------------------------------
void ActStageScroll()
{
    LONG v0; // [esp+0h] [ebp-4h]

    StageScroll += StageScrollSpeed;
    v0 = (16 * GetMapHeight() - (scWOffset_0.bottom - scWOffset_0.top)) << 10;
    if (StageScroll < 0)
    {
        StageScroll = 0;
        if (StageScrollSpeed < 0)
            StageScrollSpeed = 0;
    }
    if (StageScroll > v0)
        StageScroll = v0;
}

//----- (00421200) --------------------------------------------------------
void AddStageXOScroll(int *a1, int *a2)
{
    if (a1)
        *a1 += StageXOffset;
    if (a2)
        *a2 += StageScroll;
}

//----- (00421240) --------------------------------------------------------
void SubStageXOScroll(int *a1, int *a2)
{
    if (a1)
        *a1 -= StageXOffset;
    if (a2)
        *a2 -= StageScroll;
}