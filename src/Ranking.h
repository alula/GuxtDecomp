#ifndef __RANKING_H__
#define __RANKING_H__

#include <windows.h>

struct RankingEntry
{
    char name[8];
    int score;
};

int RankingViewLoop();
BOOL OpenRankingFile(RankingEntry *entries);
void SetDefaultRankingNames(RankingEntry *entries);
int GetRankingIndexUnderScore(RankingEntry *entries, int score);
void PutRankingView(RECT *rcView, RankingEntry *entries, int idx_under_score);
int RankingLoop();
BOOL WriteRankingFile(RankingEntry *entry);

#endif