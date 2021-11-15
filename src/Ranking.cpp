#include <windows.h>
#include <stdio.h>

#include "Ranking.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Input.h"
#include "Sound.h"
#include "Text.h"
#include "WinMain.h"

int ComputeRankingChecksum(const char *raw);
int SetRankingEntryIfEligible(RankingEntry *entries, int score);
void ResetRankingInput();
BOOL RunRankingInput(char *input, TriggerStruct *trig);
void PutRankingInput(RECT *rcView, char *a2);

//----- (0041B880) --------------------------------------------------------
int RankingViewLoop()
{
    int rank_idx;             // [esp+0h] [ebp-94h]
    TriggerStruct trig;       // [esp+4h] [ebp-90h] BYREF
    RankingEntry ranking[10]; // [esp+14h] [ebp-80h] BYREF
    int bg_color;             // [esp+90h] [ebp-4h]

    OpenRankingFile(ranking);

    rank_idx = GetRankingIndexUnderScore(ranking, GetScore());
    bg_color = GetSurfaceColor(17);
    ClearTrg_(&trig);

    while (1)
    {
        if (Call_Escape())
            return 0;

        if (GetGameReset())
            return 1;

        trig.hold = GetTrg();
        UpdateTrg(&trig);
        if ((trig.prev & 1) != 0)
            break;

        PutBackground(&scWOffset_0, bg_color);
        PutRankingView(&scWOffset_0, ranking, rank_idx);
        PutFramePerSecond();
        if (!Flip_SystemTask())
            return 0;
    }
    return 1;
}

//----- (0041B9A0) --------------------------------------------------------
BOOL OpenRankingFile(RankingEntry *entries)
{
    char path[268]; // [esp+0h] [ebp-120h] BYREF
    int checksum; // [esp+110h] [ebp-10h] BYREF
    BOOL ret;     // [esp+114h] [ebp-Ch]
    FILE *file;   // [esp+118h] [ebp-8h]
    char unused;  // [esp+11Fh] [ebp-1h] BYREF

    ret = 0;
    file = 0;
    sprintf(path, "%s\\%s", temp_guxtPath, RankingFile);
    file = fopen(path, "rb");

    if (!file)
        goto err;

    if (fread(entries, 10 * sizeof(RankingEntry), 1u, file) != 1)
        goto err;

    if (fread(&checksum, 4u, 1u, file) != 1)
        goto err;

    if (fread(&unused, 1u, 1u, file) != 0)
        goto err;

    if (checksum == ComputeRankingChecksum(reinterpret_cast<const char *>(entries)))
        ret = TRUE;

err:
    if (file)
        fclose(file);

    if (!ret)
        SetDefaultRankingNames(entries);

    return ret;
}

//----- (0041BAA0) --------------------------------------------------------
void SetDefaultRankingNames(RankingEntry *entries)
{
    memset(entries, 0, 10 * sizeof(RankingEntry));

    strcpy(entries[0].name, "PINKY");
    entries[0].score = 1000;
    strcpy(entries[1].name, "ZOO");
    entries[1].score = 900;
    strcpy(entries[2].name, "FOODS");
    entries[2].score = 800;
    strcpy(entries[3].name, "KING");
    entries[3].score = 700;
    strcpy(entries[4].name, "PEARL-C");
    entries[4].score = 600;
    strcpy(entries[5].name, "IRON-H");
    entries[5].score = 500;
    strcpy(entries[6].name, "KANI");
    entries[6].score = 400;
    strcpy(entries[7].name, "HARISEN");
    entries[7].score = 300;
    strcpy(entries[8].name, "JACK");
    entries[8].score = 200;
    strcpy(entries[9].name, "CHINGYO");
    entries[9].score = 100;
}

//----- (0041BC20) --------------------------------------------------------
int ComputeRankingChecksum(const char *raw)
{
    unsigned int i; // [esp+0h] [ebp-Ch]
    int v3;         // [esp+4h] [ebp-8h]

    v3 = 7;
    for (i = 0; i < (10 * sizeof(RankingEntry)); ++i)
    {
        if ((int)i % 7 == 2)
            v3 -= raw[i];
        else
            v3 += raw[i];
    }
    return v3;
}

//----- (0041BC90) --------------------------------------------------------
int GetRankingIndexUnderScore(RankingEntry *entries, int score)
{
    int i; // [esp+0h] [ebp-4h]

    for (i = 0; i < 10 && score <= entries[i].score; ++i)
        ;

    if (i != 0)
    {
        if (score == entries[i - 1].score)
            --i;
    }

    if (i == 10)
        return -1;
    else
        return i;
}

//----- (0041BD00) --------------------------------------------------------
void PutRankingView(RECT *rcView, RankingEntry *entries, int idx_under_score)
{

    RECT v4[2]; // [esp+4h] [ebp-54h] BYREF
    RECT v5;    // [esp+24h] [ebp-34h] BYREF
    RECT v6;    // [esp+34h] [ebp-24h] BYREF
    RECT v7;    // [esp+44h] [ebp-14h] BYREF
    int i;      // [esp+54h] [ebp-4h]

    v5.left = 36;
    v5.top = 8;
    v5.right = 80;
    v5.bottom = 16;
    v7.left = 120;
    v7.top = 24;
    v7.right = 128;
    v7.bottom = 32;
    v6.left = 112;
    v6.top = 24;
    v6.right = 120;
    v6.bottom = 32;
    v4[0].left = 0;
    v4[0].top = 24;
    v4[0].right = 104;
    v4[0].bottom = 32;
    v4[1].left = 0;
    v4[1].top = 0;
    v4[1].right = 0;
    v4[1].bottom = 0;

    if (idx_under_score >= 0)
    {
        if (entries[idx_under_score].score)
        {
            static unsigned char blink = 0;
            PutBitmap3(rcView, 8, 12 * idx_under_score + 32, &v4[blink++ / 4u % 2u], 11);
        }
    }

    PutBitmap3(rcView, 38, 8, &v5, 11);
    for (i = 0; i < 10; ++i)
    {
        if (i == 9)
            PutBitmap3(rcView, 8, 140, &v7, 11);
        else
            PutNumber(rcView, 8, 12 * i + 32, i + 1, 1, 0);
        PutTextObject(rcView, 20, 12 * i + 32, entries[i].name, 0, 0);
        if (entries[i].score)
            PutNumber(rcView, 68, 12 * i + 32, entries[i].score, 6, 0);
        PutBitmap3(rcView, 104, 12 * i + 32, &v6, 11);
    }
}

static int ranking_int = 0;
static unsigned char rankInputX = 0;
static unsigned char ranking_1 = 0;
static unsigned char ranking_2 = 0;
static unsigned char rankInputIdx = 0;
static unsigned char rankInputY = 0;

//----- (0041BF00) --------------------------------------------------------
int RankingLoop()
{
    int rankingIndex;         // [esp+0h] [ebp-A0h]
    TriggerStruct a1;         // [esp+4h] [ebp-9Ch] BYREF
    int ret;                  // [esp+10h] [ebp-90h]
    char a2[8];               // [esp+14h] [ebp-8Ch] BYREF
    RankingEntry ranking[10]; // [esp+20h] [ebp-80h] BYREF
    unsigned int color;       // [esp+9Ch] [ebp-4h]

    strcpy(a2, ".......");
    OpenRankingFile(ranking);

    rankingIndex = SetRankingEntryIfEligible(ranking, GetScore());
    if (rankingIndex == -1)
        return 1;
    color = GetSurfaceColor(17);
    ClearTrg_(&a1);
    ResetRankingInput();
    while (1)
    {
        if (Call_Escape())
            return 0;
        if (GetGameReset())
            return 1;
        a1.hold = GetTrg();
        UpdateTrg(&a1);
        if (!RunRankingInput(a2, &a1))
            break;
        PutBackground(&scWOffset_0, color);
        PutRankingInput(&scWOffset_0, a2);
        PutFramePerSecond();
        if (!Flip_SystemTask())
            return 0;
    }
    ret = 4;
    strcpy(ranking[rankingIndex].name, a2);
    WriteRankingFile(ranking);
    return ret;
}

//----- (0041C080) --------------------------------------------------------
BOOL WriteRankingFile(RankingEntry *entries)
{
    char path[264]; // [esp+0h] [ebp-118h] BYREF
    int csum;       // [esp+10Ch] [ebp-Ch] BYREF
    BOOL ret;       // [esp+110h] [ebp-8h]
    FILE *fd;       // [esp+114h] [ebp-4h]

    ret = FALSE;
    fd = 0;
    csum = ComputeRankingChecksum((const char *)entries);

    sprintf(path, "%s\\%s", temp_guxtPath, RankingFile);
    fd = fopen(path, "wb");
    if (!fd)
        goto err;

    if (fwrite((void *)entries, 10 * sizeof(RankingEntry), 1u, fd) != 1)
        goto err;

    if (fwrite(&csum, 4u, 1u, fd) != 1)
        goto err;

    ret = TRUE;

err:
    if (fd)
        fclose(fd);

    return ret;
}

//----- (0041C150) --------------------------------------------------------
int SetRankingEntryIfEligible(RankingEntry *entries, int score)
{
    int i; // [esp+0h] [ebp-8h]
    int j; // [esp+4h] [ebp-4h]

    for (i = 0; i < 10 && score <= entries[i].score; ++i)
        ;
    if (i == 10)
        return -1;

    for (j = 9; j > i; --j)
    {
        memcpy(entries[j].name, entries[j - 1].name, 8u);
        entries[j].score = entries[j - 1].score;
    }

    entries[i].score = score;
    memset(entries[i].name, 0, 8u);
    
    return i;
}

//----- (0041C200) --------------------------------------------------------
void ResetRankingInput()
{
    rankInputX = 0;
    rankInputY = 0;
    rankInputIdx = 0;
    ranking_1 = 0;
    ranking_2 = 0;
    ranking_int = 0;
}

//----- (0041C240) --------------------------------------------------------
BOOL RunRankingInput(char *input, TriggerStruct *trig)
{
    signed int v3; // [esp+8h] [ebp-4h]

    v3 = GetPlayerInput(trig->hold);
    ++ranking_2;
    if (v3)
    {
        if (ranking_int == v3)
        {
            if (++ranking_1 > 0xCu)
            {
                switch (v3)
                {
                case 1:
                    --rankInputX;
                    break;
                case 2:
                    ++rankInputX;
                    break;
                case 3:
                    --rankInputY;
                    break;
                case 4:
                    ++rankInputY;
                    break;
                default:
                    break;
                }
                PlaySound(2);
                ranking_1 = 6;
            }
        }
        else
        {
            switch (v3)
            {
            case 1:
                --rankInputX;
                break;
            case 2:
                ++rankInputX;
                break;
            case 3:
                --rankInputY;
                break;
            case 4:
                ++rankInputY;
                break;
            default:
                break;
            }
            PlaySound(2);
            ranking_int = v3;
            ranking_1 = 0;
        }
    }
    else
    {
        ranking_int = 0;
        ranking_1 = 0;
    }

    if (rankInputX > 9)
        rankInputX = 0;
    if (rankInputX < 0)
        rankInputX = 9;
    if (rankInputY > 9)
        rankInputY = 0;
    if (rankInputY < 0)
        rankInputY = 9;

    if ((trig->prev & 1) != 0)
    {
        // OK button
        if (rankInputY == 9 && (rankInputX == 8 || rankInputX == 9))
        {
            PlaySound(25);
            return FALSE;
        }

        // Back button
        if (rankInputY == 9 && (rankInputX == 6 || rankInputX == 7))
        {
            if (rankInputIdx > 0)
            {
                input[rankInputIdx] = ' ';
                PlaySound(17);
                --rankInputIdx;
            }
        }
        else if (rankInputY == 9 && rankInputX == 5)
        {
            PlaySound(1);
            input[rankInputIdx] = ' ';
            if (rankInputIdx < 6)
                ++rankInputIdx;
        }
        else
        {
            PlaySound(1);
            input[rankInputIdx] = rankInputX + 10 * rankInputY + 32;
            if (rankInputIdx < 6)
                ++rankInputIdx;
        }
    }

    return TRUE;
}

//----- (0041C550) --------------------------------------------------------
void PutRankingInput(RECT *rcView, char *a2)
{
    RECT rect[2]; // [esp+0h] [ebp-50h] BYREF
    RECT v4;      // [esp+20h] [ebp-30h] BYREF
    RECT v5;      // [esp+30h] [ebp-20h] BYREF
    RECT v6;      // [esp+40h] [ebp-10h] BYREF

    v6.left = 0;
    v6.top = 8;
    v6.right = 80;
    v6.bottom = 16;
    v4.left = 0;
    v4.top = 0;
    v4.right = 80;
    v4.bottom = 80;
    v5.left = 112;
    v5.top = 24;
    v5.right = 120;
    v5.bottom = 32;
    rect[0].left = 104;
    rect[0].top = 24;
    rect[0].right = 112;
    rect[0].bottom = 32;
    rect[1].left = 0;
    rect[1].top = 0;
    rect[1].right = 0;
    rect[1].bottom = 0;
    PutBitmap3(rcView, 6 * rankInputIdx + 38, 40, &rect[ranking_2 / 4 % 2], 11);
    PutBitmap3(rcView, 8 * rankInputX + 20, 8 * rankInputY + 64, &rect[ranking_2 / 4 % 2], 11);
    PutBitmap3(rcView, 20, 8, &v6, 11);
    PutBitmap3(rcView, 90, 24, &v5, 11);
    PutNumber(rcView, 54, 24, GetScore(), 6, 0);
    PutTextObject(rcView, 38, 40, a2, 0, 0);
    PutBitmap3(rcView, 20, 64, &v4, 9);
}