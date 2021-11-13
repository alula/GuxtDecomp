#include <windows.h>

#include "Caret.h"
#include "GameAttr.h"
#include "Stage.h"

void ActCaret00(Caret *c);
void ActCaret01(Caret *c);
void ActCaret02(Caret *c);
void ActCaret03(Caret *c);
void ActCaret04(Caret *c);
void ActCaret05(Caret *c);
void ActCaret06(Caret *c);
void ActCaret07(Caret *c);

Caret g_Carets[32];

CaretAttr CaretAttrTbl[8] =
    {
        {16u, 4u, 8u},
        {12u, 12u, 7u},
        {4u, 4u, 7u},
        {16u, 4u, 11u},
        {20u, 20u, 7u},
        {12u, 12u, 7u},
        {8u, 8u, 7u},
        {4u, 4u, 7u}};

void (*caretFuncTbl[8])(Caret *c) =
    {
        ActCaret00,
        ActCaret01,
        ActCaret02,
        ActCaret03,
        ActCaret04,
        ActCaret05,
        ActCaret06,
        ActCaret07};

//----- (004025D0) --------------------------------------------------------
void ActCaret00(Caret *c)
{
    if (!c->count3)
        c->y += 4096;
    if (++c->count3 <= 65)
    {
        if (c->count3 < 24)
            c->y -= 256;
        c->rect.left = 0;
        c->rect.top = 0;
        c->rect.right = 32;
        c->rect.bottom = 8;
        c->rect.left += 32 * (c->type2 / 8);
        c->rect.right += 32 * (c->type2 / 8);
        c->rect.top += 8 * (c->type2 % 8);
        c->rect.bottom += 8 * (c->type2 % 8);
        if (c->count3 > 50)
        {
            if (c->count3 / 2 % 2)
                c->rect.bottom = c->rect.top;
        }
    }
    else
    {
        c->cond = 0;
    }
}

//----- (00402720) --------------------------------------------------------
void ActCaret01(Caret *c)
{
    int state;    // [esp+0h] [ebp-6Ch]
    RECT v2[6];   // [esp+4h] [ebp-68h]
    Caret *child; // [esp+68h] [ebp-4h]

    v2[0].left = 0;
    v2[0].top = 32;
    v2[0].right = 24;
    v2[0].bottom = 56;
    v2[1].left = 24;
    v2[1].top = 32;
    v2[1].right = 48;
    v2[1].bottom = 56;
    v2[2].left = 48;
    v2[2].top = 32;
    v2[2].right = 72;
    v2[2].bottom = 56;
    v2[3].left = 72;
    v2[3].top = 32;
    v2[3].right = 96;
    v2[3].bottom = 56;
    v2[4].left = 96;
    v2[4].top = 32;
    v2[4].right = 120;
    v2[4].bottom = 56;
    v2[5].left = 120;
    v2[5].top = 32;
    v2[5].right = 144;
    v2[5].bottom = 56;

    child = reinterpret_cast<Caret *>(c->type2);
    state = c->state;
    if (state)
    {
        if (state != 10)
            goto LABEL_13;
    }
    else
    {
        if (c->type2)
        {
            if ((child->flag & 0x10) != 0)
                c->flag |= 0x10u;
            c->child = c->x - child->x;
            c->rot1 = c->y - child->y;
            c->count4 = child->type;
        }
        c->state = 10;
    }
    if (c->type2)
    {
        c->x = c->child + child->x;
        c->y = c->rot1 + child->y;
        if ((child->cond & 1) == 0 || child->type != c->count4)
            c->cond = 0;
    }
LABEL_13:
    if (++c->count3 > 2)
    {
        c->count3 = 0;
        ++c->count2;
    }
    if (c->count2 <= 5)
        c->rect = v2[c->count2];
    else
        c->cond = 0;
}

//----- (00402910) --------------------------------------------------------
void ActCaret02(Caret *c)
{
    RECT v1[4]; // [esp+0h] [ebp-40h]

    v1[0].left = 144;
    v1[0].top = 48;
    v1[0].right = 152;
    v1[0].bottom = 56;
    v1[1].left = 152;
    v1[1].top = 48;
    v1[1].right = 160;
    v1[1].bottom = 56;
    v1[2].left = 160;
    v1[2].top = 48;
    v1[2].right = 168;
    v1[2].bottom = 56;
    v1[3].left = 168;
    v1[3].top = 48;
    v1[3].right = 176;
    v1[3].bottom = 56;
    if (++c->count3 > 2)
    {
        c->count3 = 0;
        ++c->count2;
    }
    if (c->count2 <= 3)
        c->rect = v1[c->count2];
    else
        c->cond = 0;
}

//----- (00402A00) --------------------------------------------------------
void ActCaret03(Caret *c)
{
    RECT rc[2]; // [esp+0h] [ebp-20h]

    rc[0].left = 80;
    rc[0].top = 8;
    rc[0].right = 112;
    rc[0].bottom = 16;
    rc[1].left = 0;
    rc[1].top = 80;
    rc[1].right = 72;
    rc[1].bottom = 88;
    c->x = 61440;
    c->y = (8 * c->type2 + 40) << 10;
    if (++c->count3 <= 100)
    {
        c->rect = rc[c->type2];
        c->xoff = ((c->rect.right - c->rect.left) / 2) << 10;
        if (c->count3 > 85)
        {
            if (c->count3 / 2 % 2)
                c->rect.bottom = c->rect.top;
        }
    }
    else
    {
        c->cond = 0;
    }
}

//----- (00402B00) --------------------------------------------------------
void ActCaret04(Caret *c)
{
    int v1;       // [esp+0h] [ebp-6Ch]
    RECT v2[6];   // [esp+4h] [ebp-68h]
    Caret *child; // [esp+68h] [ebp-4h]

    v2[0].left = 0;
    v2[0].top = 80;
    v2[0].right = 40;
    v2[0].bottom = 120;
    v2[1].left = 40;
    v2[1].top = 80;
    v2[1].right = 80;
    v2[1].bottom = 120;
    v2[2].left = 80;
    v2[2].top = 80;
    v2[2].right = 120;
    v2[2].bottom = 120;
    v2[3].left = 0;
    v2[3].top = 120;
    v2[3].right = 40;
    v2[3].bottom = 160;
    v2[4].left = 40;
    v2[4].top = 120;
    v2[4].right = 80;
    v2[4].bottom = 160;
    v2[5].left = 80;
    v2[5].top = 120;
    v2[5].right = 120;
    v2[5].bottom = 160;

    child = reinterpret_cast<Caret *>(c->type2);
    v1 = c->state;
    if (v1)
    {
        if (v1 != 10)
            goto LABEL_16;
    }
    else
    {
        if (c->type2)
        {
            if ((child->flag & 0x10) != 0)
            {
                c->flag |= 0x10u;
            }
            else
            {
                c->child = c->x - child->x;
                c->rot1 = c->y - child->y;
            }
            c->count4 = child->type;
        }
        c->state = 10;
    }
    if (c->type2)
    {
        if ((child->flag & 0x10) == 0)
        {
            c->x = c->child + child->x;
            c->y = c->rot1 + child->y;
        }
        if ((child->cond & 1) == 0 || child->type != c->count4)
            c->cond = 0;
    }
LABEL_16:
    if (++c->count3 > 2)
    {
        c->count3 = 0;
        ++c->count2;
    }
    if (c->count2 <= 5)
        c->rect = v2[c->count2];
    else
        c->cond = 0;
}

//----- (00402D00) --------------------------------------------------------
void ActCaret05(Caret *c)
{
    if (++c->count1 <= 70)
    {
        c->rect.left = 48;
        c->rect.top = 56;
        c->rect.right = 72;
        c->rect.bottom = 80;
        if (++c->count3 % 2)
            c->rect.right = c->rect.left;
    }
    else
    {
        c->cond = 0;
    }
}

//----- (00402DA0) --------------------------------------------------------
void ActCaret06(Caret *c)
{
    RECT rc[2]; // [esp+0h] [ebp-20h]

    rc[0].left = 72;
    rc[0].top = 56;
    rc[0].right = 88;
    rc[0].bottom = 72;
    rc[1].left = 104;
    rc[1].top = 56;
    rc[1].right = 120;
    rc[1].bottom = 72;
    if (!c->count1)
    {
        static unsigned char ctr;
        c->child = ctr;
        ctr = (ctr + 1) % 2;
    }
    if (c->count1 > 1)
        c->cond = 0;
    c->rect = rc[c->child];
    c->rect.left += 16 * c->count1;
    c->rect.right += 16 * c->count1++;
}

//----- (00402E90) --------------------------------------------------------
void ActCaret07(Caret *c)
{
    if (c->count1 <= 3)
    {
        c->rect.left = 72;
        c->rect.top = 72;
        c->rect.right = 80;
        c->rect.bottom = 80;
        c->rect.left += 8 * c->count1;
        c->rect.right += 8 * c->count1++;
    }
    else
    {
        c->cond = 0;
    }
}

//----- (00402F20) --------------------------------------------------------
void ResetCaret()
{
    memset(g_Carets, 0, sizeof(g_Carets));
    for (int i = 0; i < 32; ++i)
        ;
}

//----- (00402F70) --------------------------------------------------------
void ResetCaret2()
{
    ResetCaret();
}

//----- (00402F80) --------------------------------------------------------
void ActCaret()
{
    int i; // [esp+0h] [ebp-8h]

    for (i = 0; i < 32; ++i)
    {
        if ((g_Carets[i].cond & 1) != 0)
            caretFuncTbl[g_Carets[i].type](&g_Carets[i]);
    }
}

//----- (00402FE0) --------------------------------------------------------
void PutCaret(RECT *rcView)
{
    int i;  // [esp+0h] [ebp-Ch]
    int a4; // [esp+4h] [ebp-8h]
    int a3; // [esp+8h] [ebp-4h]

    a3 = GetStageXOffset() / 0x400;
    a4 = GetStageScroll() / 0x400;

    for (i = 0; i < 32; ++i)
        PutObject(rcView, &g_Carets[i], a3, a4);
}

//----- (00403050) --------------------------------------------------------
BOOL SetCaret(int type, int x, int y, intptr_t param)
{
    int i;            // [esp+0h] [ebp-Ch]
    CaretAttr *cAttr; // [esp+4h] [ebp-8h]
    Caret *c;         // [esp+8h] [ebp-4h]

    for (i = 0; i < 32 && (g_Carets[i].cond & 1) != 0; ++i)
        ;
    if (i == 32)
        return 0;

    c = &g_Carets[i];
    cAttr = &CaretAttrTbl[type];

    memset(c, 0, sizeof(Caret));
    c->surf = cAttr->surf_no;
    c->type = type;
    c->cond = 1;
    c->x = x;
    c->y = y;
    c->type2 = param;
    c->xoff = cAttr->xoff << 10;
    c->yoff = cAttr->yoff << 10;

    return 1;
}