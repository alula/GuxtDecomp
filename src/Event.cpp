#include <windows.h>

#include "Event.h"

EntityStageStruct EntityStage;
int EntityStageCount;

//----- (00418F40) --------------------------------------------------------
BOOL ResetEntityStage()
{
    InitEntityStage(&EntityStage);
    return 1;
}

//----- (00425380) --------------------------------------------------------
void InitEntityStage(EntityStageStruct *a1)
{
    memset(a1, 0, sizeof(EntityStageStruct));
}

//----- (004253A0) --------------------------------------------------------
void ReleaseEntities(EntityStageStruct *a1)
{
    ReleaseEntityPtr(&a1->ptr);
    a1->total = 0;
}

//----- (004253C0) --------------------------------------------------------
void ReleaseEntityPtr(void **a1)
{
    if (*a1)
    {
        free(*a1);
        *a1 = 0;
    }
}

//----- (004253F0) --------------------------------------------------------
BOOL Unused4(EntityStageStruct *a1, int a2)
{
    BOOL result; // [esp+0h] [ebp-4h]

    result = FALSE;
    a1->total = a2;
    
    if (AllocEntity(&a1->ptr, 24 * a1->total))
        result = TRUE;
    
    if (!result)
        ReleaseEntities(a1);

    return result;
}

//----- (00425450) --------------------------------------------------------
BOOL AllocEntity(void **a1, size_t a2)
{
    *a1 = malloc(a2);
    if (!*a1)
        return FALSE;
    memset(*a1, 0, a2);
    return TRUE;
}