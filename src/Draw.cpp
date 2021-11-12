#include <windows.h>
#include <ddraw.h>
#include "Draw.h"

struct PxSurface
{
    unsigned int flags;
    void *xx04;
    LPDIRECTDRAWSURFACE7 surface;
    void *width;
    void *height;
};

char DataPathFull[264];
PxSurface g_Surfaces[64];
LPDIRECTDRAW lpDD;
LPDIRECTDRAWSURFACE SurfaceA;
LPDIRECTDRAWSURFACE SurfaceB;
LPDIRECTDRAWCLIPPER DDrawClipper;
HWND DDHWnd;
int RenderOffsetX;
int RenderOffsetY;
int MainSurfaceWidth;
int MainSurfaceHeight;
int totalSurfaceSize;
int g_ScrambleSprites;
int dword_44D35C;
HGDIOBJ h;

//----- (00422D80) --------------------------------------------------------
BOOL __cdecl InitDirectDraw(HWND a1, char *data_path, BOOL fullscreen, BOOL scrambled_sprites)
{
    memset(DataPathFull, 0, 0x104u);
    if (data_path)
        strcpy(DataPathFull, data_path);
    memset(g_Surfaces, 0, sizeof(g_Surfaces));
    if (DirectDrawCreate(0, &lpDD, 0))
        return 0;
    DDHWnd = a1;
    if (!SetFullscreenDDrawParams(fullscreen))
        return 0;
    totalSurfaceSize = 0;
    g_ScrambleSprites = scrambled_sprites;
    return 1;
}