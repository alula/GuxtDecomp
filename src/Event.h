#ifndef __EVENT_H__
#define __EVENT_H__

#include <windows.h>

struct EntityStageStruct
{
    int total;
    void *ptr;
};

BOOL ResetEntityStage();
void InitEntityStage(EntityStageStruct *a1);
void ReleaseEntities(EntityStageStruct *a1);
void ReleaseEntityPtr(void **a1);
BOOL Unused4(EntityStageStruct *a1, int a2);
BOOL AllocEntity(void **a1, size_t a2);

#endif