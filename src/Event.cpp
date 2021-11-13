#include <windows.h>
#include <stdio.h>

#include "Event.h"
#include "Stage.h"
#include "PixFile.h"

//----- (00425380) --------------------------------------------------------
void InitEntityStage(EntityStageStruct *a1)
{
    memset(a1, 0, sizeof(EntityStageStruct));
}

//----- (004253A0) --------------------------------------------------------
void ReleaseEntities(EntityStageStruct *a1)
{
    ReleaseEntityPtr((void **)&a1->ptr);
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

    if (AllocEntity((void **)&a1->ptr, 24 * a1->total))
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

// those were probably used by pixel's editor

//----- (00425490) --------------------------------------------------------
BOOL AppendEntity(EntityStageStruct *a1, PxEveEntity *a2)
{
    int i; // [esp+0h] [ebp-4h]

    for (i = 0; i < a1->total && (a1->ptr[i].flags & 1) != 0; ++i)
        ;
    if (i >= a1->total)
        return FALSE;

    a1->ptr[i] = *a2;
    a1->ptr[i].flags |= 1u;
    a1->ptr[i].count = i;

    return TRUE;
}

//----- (00425550) --------------------------------------------------------
void OffsetEntitiesBy(EntityStageStruct *a1, int off_x, int off_y)
{

    if (!a1)
        return;

    for (int i = 0; i < a1->total; ++i)
    {
        if ((a1->ptr[i].flags & 1) != 0)
        {
            a1->ptr[i].pos_x += off_x;
            a1->ptr[i].pos_y += off_y;
        }
    }
}

//----- (004255E0) --------------------------------------------------------
BOOL ReadPxeve(EntityStageStruct *ptr, PixFile *file)
{
    int i;       // [esp+0h] [ebp-Ch]
    BOOL result; // [esp+4h] [ebp-8h]
    int p;       // [esp+8h] [ebp-4h] BYREF

    result = FALSE;
    ReleaseEntities(ptr);
    if (!VariableLengthRead(&p, file))
        goto err;

    ptr->total = p;
    if (!AllocEntity((void **)&ptr->ptr, sizeof(PxEveEntity) * ptr->total))
        goto err;

    for (i = 0; i < ptr->total; ++i)
    {
        if (!VariableLengthRead(&p, file))
            goto err;
        ptr->ptr[i].flags = p;
        if (!VariableLengthRead(&p, file))
            goto err;
        ptr->ptr[i].pos_x = p;
        if (!VariableLengthRead(&p, file))
            goto err;
        ptr->ptr[i].pos_y = p;
        if (!VariableLengthRead(&p, file))
            goto err;
        ptr->ptr[i].type = p;
        if (!VariableLengthRead(&p, file))
            goto err;
        ptr->ptr[i].type2 = p;
        ptr->ptr[i].count = i;
    }
    result = TRUE;

err:
    if (!result)
        ReleaseEntities(ptr);
    return result;
}

//----- (00425770) --------------------------------------------------------
BOOL WritePxeve(EntityStageStruct *a1, FILE *a2)
{
    int i;               // [esp+0h] [ebp-8h]
    BOOL result = FALSE; // [esp+4h] [ebp-4h]

    if (!VariableLengthWrite(a1->total, a2, 0))
        goto err;

    for (i = 0; i < a1->total; ++i)
    {
        if (!VariableLengthWrite(a1->ptr[i].flags, a2, 0) || !VariableLengthWrite(a1->ptr[i].pos_x, a2, 0) || !VariableLengthWrite(a1->ptr[i].pos_y, a2, 0) || !VariableLengthWrite(a1->ptr[i].type, a2, 0) || !VariableLengthWrite(a1->ptr[i].type2, a2, 0))
        {
            goto err;
        }
    }

    result = TRUE;

err:
    return result;
}