#include <windows.h>
#include <stdio.h>

#include "PlayRecord.h"
#include "PixFile.h"
#include "WinMain.h"

PlayRecord record;

static const char *playRecordHeader = "070316_0";
static const char *playrecordsFolder = "play-records";
static const char *replayPrefix = "replay";

//----- (0041ECF0) --------------------------------------------------------
BOOL InitPlayRecord()
{
    memset(&record, 0, sizeof(record));
    record.size = 90000;
    record.action_tbl = reinterpret_cast<PlayRecordAction *>(malloc(sizeof(PlayRecordAction) * 90000u));
    if (record.action_tbl == NULL)
        return FALSE;

    memset(record.action_tbl, 0, sizeof(PlayRecordAction) * record.size);

    return TRUE;
}

//----- (0041ED60) --------------------------------------------------------
void FreePlayRecord()
{
    if (record.action_tbl)
    {
        free(record.action_tbl);
        record.action_tbl = 0;
    }
}

//----- (0041ED90) --------------------------------------------------------
void NewPlayRecord()
{
    GetLocalTime(&record.time);
    record.flag = 0;
    record.trg = 0;
    record.hold = 0;
    record.action_count = 0;
}

//----- (0041EDD0) --------------------------------------------------------
void ZeroPlayRecord()
{
    record.flag = 0;
    record.trg = 0;
    record.hold = 0;
    record.action_count = 0;
}

//----- (0041EE00) --------------------------------------------------------
BOOL RecordPlayRecord(int trg)
{
    if (!record.action_tbl)
        return FALSE;

    if (record.action_count >= record.size)
        return FALSE;

    if ((record.flag & 1) != 0)
    {
        if (record.trg == trg)
        {
            ++record.hold;
        }
        else
        {
            record.action_tbl[record.action_count].trg = record.trg;
            record.action_tbl[record.action_count].hold = record.hold;
            record.trg = trg;
            record.hold = 1;
            ++record.action_count;
        }
    }
    else
    {
        record.flag |= 1u;
        record.trg = trg;
        record.hold = 1;
    }

    return TRUE;
}

//----- (0041EED0) --------------------------------------------------------
void EndPlayRecord()
{
    record.action_tbl[record.action_count].trg = record.trg;
    record.action_tbl[record.action_count++].hold = record.hold;
}

//----- (0041EF10) --------------------------------------------------------
int ActPlayRecord()
{
    if (!record.action_tbl)
        return 0;
        
    if (record.action_count < record.size && record.action_tbl[record.action_count].hold)
    {
        if (record.hold == record.action_tbl[record.action_count].hold)
        {
            ++record.action_count;
            record.hold = 0;
        }
        ++record.hold;
        return record.action_tbl[record.action_count].trg;
    }
    else
    {
        record.flag |= 2u;
        return 0;
    }
}

//----- (0041EFA0) --------------------------------------------------------
BOOL CheckPlayRecordFlag()
{
    return (record.flag & 2) != 0;
}

//----- (0041EFC0) --------------------------------------------------------
BOOL WritePlayRecord(BOOL inScoreAttack, int stage, int score)
{
    CHAR PathName[264]; // [esp+0h] [ebp-120h] BYREF
    PlayRecord *v5;     // [esp+10Ch] [ebp-14h]
    int i;              // [esp+110h] [ebp-10h]
    char v7;            // [esp+117h] [ebp-9h]
    BOOL result;        // [esp+118h] [ebp-8h]
    FILE *v9;           // [esp+11Ch] [ebp-4h]

    result = FALSE;
    v9 = 0;
    v7 = 67;

    sprintf(PathName, "%s\\%s", pszPath, playrecordsFolder);
    CreateDirectoryA(PathName, 0);

    v5 = &record;
    if (stage)
        v7 = stage + 48;

    sprintf(
        PathName,
        "%s\\%s\\%04d%02d%02d-%02d%02d%02d-%c-%d.%s",
        pszPath,
        playrecordsFolder,
        v5->time.wYear,
        v5->time.wMonth,
        v5->time.wDay,
        v5->time.wHour,
        v5->time.wMinute,
        v5->time.wSecond,
        v7,
        10 * score,
        replayPrefix);

    v9 = fopen(PathName, "wb");
    if (v9 && fwrite(playRecordHeader, 1u, 8u, v9) == 8 && fwrite(&inScoreAttack, 4u, 1u, v9) == 1 && fwrite(&record.action_count, 4u, 1u, v9) == 1)
    {
        for (i = 0; i < record.action_count; ++i)
        {
            if (!VariableLengthWrite(record.action_tbl[i].hold, v9, 0) || !VariableLengthWrite(record.action_tbl[i].trg, v9, 0))
            {
                goto end;
            }
        }
        result = TRUE;
    }

end:
    if (v9)
        fclose(v9);

    if (result)
    {
        sprintf(PathName, "%s\\%s", pszPath, playrecordsFolder);
        DeleteOldPlayRecord(PathName, 0x10u);
    }

    return result;
}

//----- (0041F1D0) --------------------------------------------------------
void DeleteOldPlayRecord(const char *folder, unsigned int days)
{
    // TODO
}

//----- (0041F510) --------------------------------------------------------
BOOL ReadPlayRecord(const char *a1, BOOL *a2)
{
    CHAR Name[268]; // [esp+0h] [ebp-138h] BYREF
    int header[2];  // [esp+10Ch] [ebp-2Ch] BYREF
    int i;          // [esp+118h] [ebp-20h]
    int v6;         // [esp+11Ch] [ebp-1Ch] BYREF
    BOOL result;    // [esp+120h] [ebp-18h]
    PixFile file;   // [esp+124h] [ebp-14h] BYREF

    result = FALSE;

    if (a1)
        strcpy(Name, a1);
    else
        // TODO: autoplay demos
        sprintf(Name, "%s\\%s", pszPath, "demo.bin");

    if (!record.action_tbl)
        return FALSE;

    memset(record.action_tbl, 0, 8 * record.size);
    memset(&file, 0, sizeof(file));

    if (OpenResource_(0, Name, 0, &file) && ReadFromFile(header, 1u, 8, &file) && ReadFromFile(a2, 4u, 1, &file) && ReadFromFile(&v6, 4u, 1, &file) && !memcmp(playRecordHeader, header, 8u) && v6 <= 89998)
    {
        for (i = 0; i < v6; ++i)
        {
            if (!VariableLengthRead(&record.action_tbl[i].hold, &file) || !VariableLengthRead(&record.action_tbl[i].trg, &file))
            {
                goto LABEL_19;
            }
        }
        result = TRUE;
    }

LABEL_19:
    if (!result)
        memset(record.action_tbl, 0, 90000 * sizeof(PlayRecordAction));

    CloseResource_(&file);
    return result;
}