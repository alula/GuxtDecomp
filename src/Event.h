#ifndef __EVENT_H__
#define __EVENT_H__

#include <windows.h>
#include <stdio.h>

#include "PixFile.h"

struct PxEveEntity
{
    int pos_x;
    int pos_y;
    int flags;
    int type;
    int type2;
    int count;
};

struct EntityStageStruct
{
    int total;
    PxEveEntity *ptr;
};

void InitEntityStage(EntityStageStruct *a1);
void ReleaseEntities(EntityStageStruct *a1);
void ReleaseEntityPtr(void **a1);
BOOL Unused4(EntityStageStruct *a1, int a2);
BOOL AllocEntity(void **a1, size_t a2);
BOOL AppendEntity(EntityStageStruct *a1, PxEveEntity *a2);
void OffsetEntitiesBy(EntityStageStruct *a1, int off_x, int off_y);
BOOL ReadPxeve(EntityStageStruct *ptr, PixFile *file);
BOOL WritePxeve(EntityStageStruct *a1, FILE *a2);

#endif