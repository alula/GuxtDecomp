#include <windows.h>
#include <stdio.h>

#include "Stage.h"
#include "Bullet.h"
#include "Caret.h"
#include "Draw.h"
#include "Event.h"
#include "Fade.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "Map.h"
#include "Object.h"
#include "PlayRecord.h"
#include "Random.h"
#include "NpcShip.h"
#include "Sound.h"
#include "Text.h"
#include "WinMain.h"

EntityStageStruct EntityStage;
int EntityStageCount;
char szFile[MAX_PATH];
StageState g_StageState;

int debugStage;
int debugStageScroll;
int debugSpeed;
int debugPowerup;
int debugLife;

//----- (00418DD0) --------------------------------------------------------
void PrepPxeve()
{
    if (EntityStage.total && EntityStage.ptr)
    {
        for (int i = EntityStage.total - 1; i; --i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (EntityStage.ptr[j].pos_y < EntityStage.ptr[j + 1].pos_y)
                {
                    PxEveEntity v3 = EntityStage.ptr[j];
                    EntityStage.ptr[j] = EntityStage.ptr[j + 1];
                    EntityStage.ptr[j + 1] = v3;
                }
            }
        }

        for (int k = 0; k < EntityStage.total; ++k)
            EntityStage.ptr[k].count = k;
    }
}

//----- (00418F40) --------------------------------------------------------
BOOL ResetEntityStage()
{
    InitEntityStage(&EntityStage);
    return TRUE;
}

//----- (00418F60) --------------------------------------------------------
BOOL LoadPxeve(int stage)
{
    CHAR Name[268]; // [esp+0h] [ebp-128h] BYREF
    int result;     // [esp+110h] [ebp-18h]
    PixFile a1a;    // [esp+114h] [ebp-14h] BYREF

    result = FALSE;
    sprintf(Name, "%s\\event%d.pxeve", dataPath, stage);
    ReleaseEntities(&EntityStage);
    if (!OpenResource_(0, Name, 0, &a1a))
        goto err;

    if (!ReadPxeve(&EntityStage, &a1a))
        goto err;

    PrepPxeve();

    sprintf(Name, "enemy%d", stage);
    ClearSurface(6);
    if (!LoadPximg(Name, 6))
        goto err;

    result = TRUE;

err:
    CloseResource_(&a1a);

    if (!result)
        ReleaseEntities(&EntityStage);

    return result;
}

//----- (00419050) --------------------------------------------------------
BOOL LoadPximgEnemy(int stage)
{
    char a1a[268]; // [esp+0h] [ebp-110h] BYREF

    sprintf(a1a, "enemy%d", stage);
    ClearSurface(6);
    return LoadPximg(a1a, 6);
}

//----- (004190B0) --------------------------------------------------------
void ZeroEntityCount()
{
    EntityStageCount = 0;
}

//----- (004190C0) --------------------------------------------------------
BOOL SetStageEntities()
{
    int v1;          // [esp+0h] [ebp-18h]
    int x;           // [esp+4h] [ebp-14h] BYREF
    int y;           // [esp+8h] [ebp-10h] BYREF
    int v4;          // [esp+Ch] [ebp-Ch]
    int v5;          // [esp+10h] [ebp-8h]
    PxEveEntity *v6; // [esp+14h] [ebp-4h]

    if (!EntityStage.total || !EntityStage.ptr)
        return 0;
    v4 = GetStageScroll();
    v5 = GetStageXOffset();
    v1 = v4 / 1024 / 8 - 1;
    while (EntityStageCount < EntityStage.total && EntityStage.ptr[EntityStageCount].pos_y >= v1)
    {
        v6 = &EntityStage.ptr[EntityStageCount];
        x = (8 * v6->pos_x + 8) << 10;
        y = (8 * v6->pos_y + 8) << 10;
        SubStageXOScroll(&x, &y);
        CreateEntity(v6->type, x, y, v6->type2);
        ++EntityStageCount;
    }
    return 1;
}

//----- (004191C0) --------------------------------------------------------
BOOL SetStageEntitiesPartial()
{
    int v1;          // [esp+4h] [ebp-Ch]
    PxEveEntity *v2; // [esp+Ch] [ebp-4h]

    if (!EntityStage.total || !EntityStage.ptr)
        return FALSE;

    v1 = GetStageScroll();
    GetStageXOffset();
    while (EntityStageCount < EntityStage.total && EntityStage.ptr[EntityStageCount].pos_y >= v1 / 1024 / 8 - 1)
    {
        v2 = &EntityStage.ptr[EntityStageCount];
        if (v2->type == 19 || v2->type == 22 || v2->type == 6 || v2->type == 38)
            CreateEntity(v2->type, 0, 0, v2->type2);
        ++EntityStageCount;
    }

    return TRUE;
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

//----- (00419700) --------------------------------------------------------
BOOL StartStage()
{
    char a1[24]; // [esp+0h] [ebp-1Ch] BYREF

    if (!LoadMap(g_StageState.currentStage))
        return FALSE;

    ZeroEntityCount();
    ResetBullet();
    ResetCaret();
    ResetEntities();
    FreeStageText();
    ResetRandom();
    SetInitialShipValues();
    ResetFade();
    SetGameDelay(0);
    StopLoopSound(32);
    SetDefaultStageScroll();
    SetScrollSpeed(0);
    SetStageXOffset(4096);

    if (g_StageState.checkpointStageScroll)
    {
        SetStageScrollShift(g_StageState.checkpointStageScroll);
        SetStageEntitiesPartial();
    }
    g_StageState.state = 0;
    g_StageState.centerTextMiscTimer = 0;

    sprintf(a1, "STAGE %d START!", g_StageState.currentStage);
    PutStageText(a1);

    return TRUE;
}

//----- (004197F0) --------------------------------------------------------
BOOL InitStage()
{
    BOOL result; // [esp+0h] [ebp-4h]

    result = 0;
    g_StageState.checkpointStageScroll = 0;

    if (debugStage)
    {
        g_StageState.currentStage = debugStage;
        SetPowerUp(debugPowerup);
        SetSpeed(debugSpeed);
        SetLife(debugLife);
    }

    if (!LoadPxeve(g_StageState.currentStage))
        goto err;

    if (!StartStage())
        goto err;

    if (debugStage)
    {
        if (debugStageScroll)
        {
            SetStageScrollShift(debugStageScroll);
            SetStageEntitiesPartial();
        }
        debugStage = 0;
    }

    result = 1;

err:
    return result;
}

//----- (004198B0) --------------------------------------------------------
void SetCheckpointScroll()
{
    g_StageState.checkpointStageScroll = GetCheckpointScrollValue();
}

//----- (004198C0) --------------------------------------------------------
BOOL CheckStageClear(int a1)
{
    char a1a[24]; // [esp+0h] [ebp-1Ch] BYREF

    if (g_StageState.state == 30 || g_StageState.state == 31 || g_StageState.state == 32 || g_StageState.state == 40 || g_StageState.state == 50)
    {
        return TRUE;
    }

    sprintf(a1a, "STAGE %d CLEAR!", a1);
    PutStageText(a1a);
    g_StageState.state = 20;
    g_StageState.centerTextMiscTimer = 0;
    g_StageState.currentMusic = 0;
    SetMusicVolume(3000);
    return TRUE;
}

//----- (00419960) --------------------------------------------------------
BOOL ShipCrushProc2()
{
    SetMusicVolume(100);
    FreeStageText();
    g_StageState.centerTextMiscTimer = 0;
    g_StageState.currentMusic = 0;
    g_StageState.state = 30;
    return 1;
}

//----- (004199A0) --------------------------------------------------------
int ActStageState(TriggerStruct *a1)
{
    switch (g_StageState.state)
    {
    case 0:
        if (g_StageState.centerTextMiscTimer++ > 100)
        {
            FreeStageText();
            g_StageState.state = 10;
        }

        return 2;
    case 10:
        if (CheckPlayRecordFlag())
            EndRecordPlayback();

        return 2;
    case 20:
        if (g_StageState.centerTextMiscTimer++ == 150)
        {
            g_StageState.centerTextMiscTimer = 0;
            g_StageState.state = 21;
            SetShipBoost();
            PutStageText("");
        }

        return 2;
    case 21:
        if (g_StageState.centerTextMiscTimer++ == 150)
        {
            g_StageState.state = 22;
            SetFadeActive();
        }

        return 2;
    case 22:
        if (!CheckFadeEnd())
            return 2;

        if (++g_StageState.currentStage <= 5)
        {
            InitStage();
            return 2;
        }

        if ((g_StageState.gameFlags & 1) != 0)
        {
            EndRecordPlayback();
            return 2;
        }

        g_StageState.currentStage = 0;
        WriteGameCleared();

        return 7;
    case 30:
        if (g_StageState.centerTextMiscTimer++ <= 100)
            return 2;

        if (g_StageState.shipLivesCount <= 0)
        {
            if ((g_StageState.gameFlags & 1) != 0)
            {
                EndRecordPlayback();
            }
            else
            {
                PutStageText("GAME OVER");
                g_StageState.state = 31;
                g_StageState.centerTextMiscTimer = 0;
                LoadMusic(musicTable[3]);
                StartMusic(0);
            }
        }
        else
        {
            g_StageState.state = 40;
            SetFadeActive();
        }

        return 2;
    case 31:
        if ((a1->prev & 1) != 0)
        {
            if ((g_StageState.gameFlags & 2) != 0)
                return 3;
            else
                return 1;
        }

        if (g_StageState.centerTextMiscTimer == 250)
            SetFadeActive();

        if (g_StageState.centerTextMiscTimer++ > 300)
        {
            g_StageState.state = 32;
            SetGameDelay(-1);
        }
        return 2;

    case 32:
        if ((a1->prev & 1) == 0)
            return 2;

        if ((g_StageState.gameFlags & 2) != 0)
            return 3;
        else
            return 1;
    case 40:
        if (CheckFadeEnd())
        {
            --g_StageState.shipLivesCount;
            ResetShip();
            StartStage();
        }
        return 2;
    default:
        return 2;
    }
}

static const char *clearedFile = "cleared.bin";
static const char *clearedMentama = "mentama.";

//----- (00419C70) --------------------------------------------------------
void WriteGameCleared()
{
    char v1[264]; // [esp+0h] [ebp-110h] BYREF
    FILE *v2;     // [esp+10Ch] [ebp-4h]

    sprintf(v1, "%s\\%s", temp_guxtPath, clearedFile);
    v2 = fopen(v1, "wt");
    if (v2)
    {
        fprintf(v2, "%s\n", clearedMentama);
        fclose(v2);
    }

    g_StageState.gameFlags |= 4u;
}

//----- (00419D00) --------------------------------------------------------
void EndRecordPlayback()
{
    PutStageText("RECORD OVER");
    g_StageState.state = 50;
    SetGameDelay(-1);
    SetMusicVolume(1000);
    StopLoopSound(32);
    RecordEndFadeWhite();
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