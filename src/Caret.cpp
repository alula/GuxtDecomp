#include <windows.h>

#include "Caret.h"

Caret g_Carets[32];
CaretAttr CaretAttrTbl[32] = {
    {16u, 4u, 8u},
    {12u, 12u, 7u},
    {4u, 4u, 7u},
    {16u, 4u, 11u},
    {20u, 20u, 7u},
    {12u, 12u, 7u},
    {8u, 8u, 7u},
    {4u, 4u, 7u},
    {208u, 37u, 64u},
    {0u, 32u, 39u},
    {64u, 0u, 16u},
    {41u, 64u, 0u},
    {0u, 42u, 64u},
    {0u, 0u, 43u},
    {64u, 0u, 0u},
    {45u, 64u, 0u},
    {160u, 45u, 64u},
    {0u, 144u, 46u},
    {64u, 0u, 16u},
    {3u, 1u, 1u},
    {8u, 8u, 7u},
    {7u, 6u, 0u},
    {5u, 0u, 0u},
    {8u, 0u, 0u},
    {16u, 16u, 0u},
    {0u, 0u, 0u},
    {7u, 0u, 0u},
    {3u, 0u, 0u},
    {24u, 16u, 0u},
    {0u, 0u, 0u},
    {6u, 0u, 0u},
    {2u, 0u, 0u}};

//----- (00403050) --------------------------------------------------------
BOOL SetCaret(int type, int x, int y, int param)
{
    int i;            // [esp+0h] [ebp-Ch]
    CaretAttr *cAttr; // [esp+4h] [ebp-8h]
    Caret *c;         // [esp+8h] [ebp-4h]

    for (int i = 0; i < 32 && (g_Carets[i].cond & 1) != 0; ++i)
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