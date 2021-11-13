#ifndef __PLAYRECORD_H__
#define __PLAYRECORD_H__

#include <windows.h>

struct PlayRecordAction
{
    int hold;
    int trg;
};

struct PlayRecord
{
    struct _SYSTEMTIME time;
    int flag;
    int trg;
    int action_count;
    int hold;
    int size;
    PlayRecordAction *action_tbl;
};

BOOL InitPlayRecord();
void FreePlayRecord();
void NewPlayRecord();
void ZeroPlayRecord();
BOOL RecordPlayRecord(int trg);
void EndPlayRecord();
int ActPlayRecord();
BOOL CheckPlayRecordFlag();
BOOL WritePlayRecord(BOOL inScoreAttack, int stage, int score);
void DeleteOldPlayRecord(const char *folder, unsigned int days);
BOOL ReadPlayRecord(const char *a1, BOOL *a2);

#endif