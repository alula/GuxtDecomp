#include <windows.h>

#include "PlayRecord.h"
#include "PixFile.h"

struct _SYSTEMTIME SystemTime;
int PlayRecordFlag;
int PlayRecordTrg;
int PlayRecordActionCount;
int PlayRecordHold;
int PlayRecordSize;
void *PlayRecordActionTbl;

//----- (0041ECF0) --------------------------------------------------------
BOOL InitPlayRecord()
{
    memset(&SystemTime, 0, 0x28u);
    PlayRecordSize = 90000;
    PlayRecordActionTbl = malloc(0xAFC80u);
    if (!PlayRecordActionTbl)
        return FALSE;
    memset(PlayRecordActionTbl, 0, 8 * PlayRecordSize);
    return TRUE;
}

//----- (0041ED60) --------------------------------------------------------
void FreePlayRecord()
{
    if (PlayRecordActionTbl)
    {
        free(PlayRecordActionTbl);
        PlayRecordActionTbl = 0;
    }
}

//----- (0041ED90) --------------------------------------------------------
void NewPlayRecord()
{
    GetLocalTime(&SystemTime);
    PlayRecordFlag = 0;
    PlayRecordTrg = 0;
    PlayRecordHold = 0;
    PlayRecordActionCount = 0;
}

//----- (0041EDD0) --------------------------------------------------------
void ZeroPlayRecord()
{
    PlayRecordFlag = 0;
    PlayRecordTrg = 0;
    PlayRecordHold = 0;
    PlayRecordActionCount = 0;
}

//----- (0041F510) --------------------------------------------------------
BOOL ReadPlayRecord(const char *a1, BOOL *a2)
{
    CHAR Name[268]; // [esp+0h] [ebp-138h] BYREF
    int header[2];  // [esp+10Ch] [ebp-2Ch] BYREF
    int i;          // [esp+118h] [ebp-20h]
    int v6;         // [esp+11Ch] [ebp-1Ch] BYREF
    BOOL v7;        // [esp+120h] [ebp-18h]
    PixFile a4;     // [esp+124h] [ebp-14h] BYREF

    v7 = 0; // TODO
#if 0
    if (a1)
        strcpy(Name, a1);
    else
        // TODO: autoplay demos
        sprintf(Name, "%s\\%s", pszPath, "demo.bin");
    if (!PlayRecordActionTbl)
        return 0;
    memset(PlayRecordActionTbl, 0, 8 * PlayRecordSize);
    memset(&a4, 0, sizeof(a4));
    if (OpenResource_(0, Name, 0, &a4) && ReadFromFile(header, 1u, 8, &a4) && ReadFromFile(a2, 4u, 1, &a4) && ReadFromFile(&v6, 4u, 1, &a4) && !memcmp(playRecordHeader, header, 8u) && v6 <= 89998)
    {
        for (i = 0; i < v6; ++i)
        {
            if (!VariableLengthRead(PlayRecordActionTbl + 2 * i, &a4) || !VariableLengthRead(PlayRecordActionTbl + 2 * i + 1, &a4))
            {
                goto LABEL_19;
            }
        }
        v7 = 1;
    }
LABEL_19:
    if (!v7)
        memset(PlayRecordActionTbl, 0, 0xAFC80u);
    CloseResource_(&a4);
#endif
    return v7;
}