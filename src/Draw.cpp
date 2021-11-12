#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <string.h>
#include <stdio.h>

#include "Draw.h"
#include "Game.h"

struct PxSurface
{
    unsigned int flags;
    char *tex_name;
    LPDIRECTDRAWSURFACE surface;
    int width;
    int height;
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
BOOL g_ScrambleSprites;
BOOL g_IsFullscreen;
HGDIOBJ h;

static void ReleaseSurfaceName(const char **p);
static BOOL AllocSurfaceName(char **a1, size_t a2);

//----- (00422B90) --------------------------------------------------------
void ClearSurface(signed int surf_id)
{
    if (surf_id >= 64)
        return;

    PxSurface *s = &g_Surfaces[surf_id];

    if (!s->surface)
        return;

    ReleaseSurfaceName(&s->tex_name);
    s->surface->Release();

    totalSurfaceSize -= magnification * s->height * magnification * s->width;
    memset(s, 0, sizeof(PxSurface));
}

//----- (00422C20) --------------------------------------------------------
static void ReleaseSurfaceName(const char **p)
{
    if (!*p)
        return;

    free((void *)*p);

    *p = NULL;
}

//----- (00422C50) --------------------------------------------------------
void ClearSurfaceTbl()
{
    for (int i = 0; i < 64; ++i)
        ClearSurface(i);
}

//----- (00422C80) --------------------------------------------------------
int GetTotalSurfaceSize()
{
    return totalSurfaceSize;
}

//----- (00422C90) --------------------------------------------------------
void SetRenderOffset(int off_x, int off_y)
{
    RenderOffsetX = off_x;
    RenderOffsetY = off_y;
}

//----- (00422CB0) --------------------------------------------------------
void SetFullscreenRenderPos()
{
    RenderOffsetX = (GetSystemMetrics(0) - magnification * MainSurfaceWidth) / 2;
    RenderOffsetY = (GetSystemMetrics(1) - magnification * MainSurfaceHeight) / 2;
}

//----- (00422D00) --------------------------------------------------------
BOOL SetFullscreenDDrawParams(BOOL fullscreen)
{
    if (!lpDD)
        return FALSE;

    if (fullscreen)
    {
        if (lpDD->SetCooperativeLevel(DDHWnd, DISCL_NOWINKEY | DISCL_EXCLUSIVE))
            return FALSE;
    }
    else
    {
        if (lpDD->SetCooperativeLevel(DDHWnd, DISCL_BACKGROUND))
            return FALSE;

        RenderOffsetX = 0;
        RenderOffsetY = 0;
    }
    g_IsFullscreen = fullscreen;

    return TRUE;
}

//----- (00422D80) --------------------------------------------------------
BOOL InitDirectDraw(HWND hwnd, char *data_path, BOOL fullscreen, BOOL scrambled_sprites)
{
    memset(DataPathFull, 0, 0x104u);

    if (data_path)
        strcpy(DataPathFull, data_path);

    memset(g_Surfaces, 0, sizeof(g_Surfaces));

    if (DirectDrawCreate(0, &lpDD, 0))
        return FALSE;

    DDHWnd = hwnd;

    if (!SetFullscreenDDrawParams(fullscreen))
        return FALSE;

    totalSurfaceSize = 0;
    g_ScrambleSprites = scrambled_sprites;

    return TRUE;
}

//----- (00422E10) --------------------------------------------------------
void EndDirectDraw(HWND hwnd)
{
    ClearSurfaceTbl();
    ReleaseSurfaceA();
    
    lpDD->SetCooperativeLevel(hwnd, DISCL_BACKGROUND);
    if (lpDD) // ??????????
    {
        lpDD->Release();
        lpDD = NULL;
    }

    DDHWnd = NULL;
}

//----- (00422E70) --------------------------------------------------------
BOOL InitMainSurface(HWND hwnd, int width, int height, int mag)
{
    DDSURFACEDESC desc;
    RECT rc;
    DDBLTFX fx;

    MainSurfaceWidth = width;
    MainSurfaceHeight = height;
    magnification = mag;

    memset(&desc, 0, sizeof(desc));
    desc.dwSize = 108;
    desc.dwFlags = 1;
    desc.ddsCaps.dwCaps = 512;
    desc.dwBackBufferCount = 0;

    if (lpDD->CreateSurface(&desc, &SurfaceA, 0))
        return FALSE;

    memset(&desc, 0, sizeof(desc));
    desc.dwSize = 108;
    desc.dwFlags = 7;
    desc.ddsCaps.dwCaps = 64;
    desc.dwWidth = magnification * MainSurfaceWidth;
    desc.dwHeight = magnification * MainSurfaceHeight;

    if (lpDD->CreateSurface(&desc, &SurfaceB, 0))
        return FALSE;

    lpDD->CreateClipper(0, &DDrawClipper, 0);
    DDrawClipper->SetHWnd(0, hwnd);

    SurfaceA->SetClipper(DDrawClipper);

    memset(&fx, 0, sizeof(fx));
    fx.dwSize = 100;
    fx.dwFillColor = 0;
    rc.left = 0;
    rc.right = magnification * MainSurfaceWidth;
    rc.top = 0;
    rc.bottom = magnification * MainSurfaceHeight;

    SurfaceB->Blt(&rc, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &fx);

    totalSurfaceSize += magnification * MainSurfaceHeight * magnification * MainSurfaceWidth;
    return TRUE;
}

//----- (00423060) --------------------------------------------------------
void ReleaseSurfaceA()
{
    if (!SurfaceA)
        return;

    SurfaceA->Release();
    SurfaceA = 0;
    totalSurfaceSize -= magnification * MainSurfaceHeight * magnification * MainSurfaceWidth;
}

//----- (004230C0) --------------------------------------------------------
BOOL Flip_Screen()
{
    RECT rcSurf;
    RECT rcWindow;

    if (!lpDD || !DDHWnd)
        return 0;

    rcSurf.left = 0;
    rcSurf.top = 0;
    rcSurf.right = magnification * MainSurfaceWidth;
    rcSurf.bottom = magnification * MainSurfaceHeight;

    GetWindowRect(DDHWnd, &rcWindow);
    rcWindow.left += RenderOffsetX;
    rcWindow.top += RenderOffsetY;
    rcWindow.right = rcWindow.left + magnification * MainSurfaceWidth;
    rcWindow.bottom = rcWindow.top + magnification * MainSurfaceHeight;

    SurfaceA->Blt(&rcWindow, SurfaceB, &rcSurf, DDBLT_WAIT, 0);
    Flip_Screen2();

    return 1;
}

//----- (00423190) --------------------------------------------------------
BOOL MakeSurface_Pximg(char *name, int surf_no, BOOL load_from_file, BOOL system_memory)
{
    unsigned int fuLoad;
    CHAR path[268];
    BITMAP bmp;
    PxSurface *s;
    HANDLE hImg;

    if (surf_no >= 64)
        return FALSE;

    if (g_Surfaces[surf_no].surface)
        return FALSE;

    s = &g_Surfaces[surf_no];
    if (load_from_file)
    {
        if (name[1] == ':')
            strcpy(path, name);
        else
            sprintf(path, "%s\\%s", DataPathFull, name);

        fuLoad = LR_CREATEDIBSECTION | LR_LOADFROMFILE;
    }
    else
    {
        strcpy(path, name);
        fuLoad = LR_CREATEDIBSECTION;
    }

    hImg = LoadImageA(GetModuleHandleA(NULL), path, 0, 0, 0, fuLoad);

    if (!hImg)
        return FALSE;
    GetObjectA(hImg, 24, &bmp);

    if (!MakeSurface(&s->surface, bmp.bmWidth, bmp.bmHeight, system_memory))
        return FALSE;

    PreparePximg(s->surface, hImg, bmp.bmWidth, bmp.bmHeight);
    DeleteObject(hImg);
    ReleaseSurfaceName(&s->tex_name);

    if (!AllocSurfaceName(&s->tex_name, strlen(name) + 1))
        ClearSurface(surf_no);

    strcpy(s->tex_name, name);

    s->width = bmp.bmWidth;
    s->height = bmp.bmHeight;

    s->flags = 0;

    if (load_from_file)
        s->flags |= 1u;
    if (system_memory)
        s->flags |= 2u;

    return TRUE;
}

//----- (00423380) --------------------------------------------------------
static BOOL AllocSurfaceName(char **ptr, size_t len)
{
    *ptr = (char *)malloc(len);

    if (!*ptr)
        return FALSE;

    memset(*ptr, 0, len);

    return TRUE;
}

//----- (004233C0) --------------------------------------------------------
BOOL MakeSurface(LPDIRECTDRAWSURFACE *ddSurf, int width, int height, BOOL system_memory)
{
    DDSURFACEDESC desc;
    DDCOLORKEY key;

    memset(&desc, 0, sizeof(desc));
    desc.dwSize = 108;
    desc.dwFlags = 7;
    desc.dwWidth = magnification * width;
    desc.dwHeight = magnification * height;

    if (system_memory)
        desc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
    else
        desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    if (lpDD->CreateSurface(&desc, ddSurf, 0))
        return FALSE;

    totalSurfaceSize += desc.dwHeight * desc.dwWidth;

    key.dwColorSpaceLowValue = 0;
    key.dwColorSpaceHighValue = 0;
    (*ddSurf)->SetColorKey(8, &key);

    return 1;
}

//----- (00423480) --------------------------------------------------------
void PreparePximg(LPDIRECTDRAWSURFACE ddSurf, HGDIOBJ h, int wSrc, int hSrc)
{
    PximgDecodeInfo info;

    HDC hdc = CreateCompatibleDC(0);
    HGDIOBJ v8 = SelectObject(hdc, h);
    HDC hdcDest;
    ddSurf->GetDC(&hdcDest);

    if (g_ScrambleSprites)
    {
        if (DecodePximg(&info, hSrc, 0x4444, 0x8888))
        {
            for (int i = 0; i < hSrc; ++i)
                StretchBlt(
                    hdcDest,
                    0,
                    magnification * i,
                    magnification * wSrc,
                    magnification,
                    hdc,
                    0,
                    info.line_indexes[i],
                    wSrc,
                    1,
                    0xCC0020u);
            ReleasePximgDecoder(&info);
        }
    }
    else
    {
        StretchBlt(hdcDest, 0, 0, magnification * wSrc, magnification * hSrc, hdc, 0, 0, wSrc, hSrc, 0xCC0020u);
    }

    ddSurf->ReleaseDC(hdcDest);
    SelectObject(hdc, v8);

    DeleteDC(hdc);
}

//----- (004235B0) --------------------------------------------------------
BOOL DecodePximg(PximgDecodeInfo *info, int img_height, unsigned short hash_a, unsigned short hash_b)
{
    memset(info, 0, 0x10u);
    info->hash_a = hash_a;
    info->hash_b = hash_b;
    info->height = img_height;
    info->line_indexes = (int *)malloc(4 * img_height);

    if (!info->line_indexes)
        return FALSE;

    memset(info->line_indexes, 255, 4 * img_height);
    int cycle_count;
    int cur_line = 0;

    for (int i = 0; i < img_height; ++i)
    {
        cycle_count = PximgHashShuffle(info) >> 8;
        if (!cycle_count)
            cycle_count = 1;
        do
        {
            cur_line = (cur_line + 1) % img_height;
            if (*(info->line_indexes + 4 * cur_line) == -1)
                --cycle_count;
        } while (cycle_count);
        *(info->line_indexes + 4 * cur_line) = i;
    }

    return TRUE;
}

//----- (004236C0) --------------------------------------------------------
unsigned short PximgHashShuffle(PximgDecodeInfo *info)
{
    unsigned short res;
    unsigned char *u1;
    unsigned char *u2;
    unsigned int tmp;

    tmp = (info->hash_b + info->hash_a);
    u1 = (unsigned char *)&tmp;
    u2 = (unsigned char *)&res;

    u2[0] = u1[1];
    u2[1] = u1[0];
    // ^ potential UB, might want to replace that with:
    // res = (((unsigned short)tmp) << 8) | (((unsigned short)tmp) >> 8);

    info->hash_b = (unsigned short)info->hash_a;
    info->hash_a = res;

    return res;
}

//----- (00423720) --------------------------------------------------------
void ReleasePximgDecoder(PximgDecodeInfo *info)
{
    if (info->line_indexes)
    {
        free(info->line_indexes);
        info->line_indexes = 0;
    }
}

//----- (00423750) --------------------------------------------------------
BOOL InitSurface(int width, int height, int surf_no, BOOL system_memory)
{
    if (surf_no >= 64)
        return FALSE;

    if (g_Surfaces[surf_no].surface)
        return FALSE;

    PxSurface *s = &g_Surfaces[surf_no];
    if (!MakeSurface(&s->surface, width, height, system_memory))
        return FALSE;

    ReleaseSurfaceName(&s->tex_name);

    s->width = width;
    s->height = height;

    if (system_memory)
        s->flags |= 2;
    else
        s->flags &= ~2u;

    return TRUE;
}

//----- (00423800) --------------------------------------------------------
BOOL MakeSurface_Generic(const char *path, int surf_no, int load_from_file)
{
    UINT fuLoad;    // [esp+0h] [ebp-134h]
    CHAR name[268]; // [esp+4h] [ebp-130h] BYREF
    BITMAP bmp;     // [esp+114h] [ebp-20h] BYREF
    PxSurface *s;   // [esp+12Ch] [ebp-8h]

    if (surf_no >= 64)
        return FALSE;

    if (!g_Surfaces[surf_no].surface)
        return FALSE;

    s = &g_Surfaces[surf_no];

    if (load_from_file)
    {
        if (path[1] == ':')
            strcpy(name, path);
        else
            sprintf(name, "%s\\%s", DataPathFull, path);
        fuLoad = LR_CREATEDIBSECTION | LR_LOADFROMFILE;
    }
    else
    {
        strcpy(name, path);
        fuLoad = LR_CREATEDIBSECTION;
    }

    HANDLE hImage = LoadImageA(GetModuleHandleA(0), name, 0, 0, 0, fuLoad);
    if (!hImage)
        return FALSE;

    GetObjectA(hImage, 24, &bmp);
    PreparePximg(s->surface, hImage, bmp.bmWidth, bmp.bmHeight);
    DeleteObject(hImage);
    ReleaseSurfaceName(&s->tex_name);

    if (!AllocSurfaceName(&s->tex_name, strlen(path) + 1))
        ClearSurface(surf_no);

    strcpy(s->tex_name, path);

    if (load_from_file)
        s->flags |= 1;
    else
        s->flags &= ~1u;

    return TRUE;
}

//----- (004239A0) --------------------------------------------------------
BOOL GetSurfaceSize(int *p_width, int *p_height, int surf_no)
{
    if (surf_no >= 64)
        return FALSE;

    if (!g_Surfaces[surf_no].surface)
        return FALSE;

    if (p_width)
        *p_width = g_Surfaces[surf_no].width;

    if (p_height)
        *p_height = g_Surfaces[surf_no].height;

    return TRUE;
}

//----- (00423A00) --------------------------------------------------------
void MagnifyRect(RECT *rc)
{
    rc->left *= magnification;
    rc->right *= magnification;
    rc->top *= magnification;
    rc->bottom *= magnification;
}

//----- (00423A50) --------------------------------------------------------
void PutRect(int x, int y, RECT *rect, int surf_no)
{
    RECT rcSrc;
    RECT rcDest;

    if (surf_no >= 64)
        return;

    if (!g_Surfaces[surf_no].surface)
        return;

    rcSrc = *rect;
    rcDest.left = x;
    rcDest.right = rect->right + x - rect->left;
    rcDest.top = y;
    rcDest.bottom = rect->bottom + y - rect->top;

    MagnifyRect(&rcSrc);
    MagnifyRect(&rcDest);

    SurfaceB->Blt(&rcDest, g_Surfaces[surf_no].surface, &rcSrc, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
}

//----- (00423B10) --------------------------------------------------------
void PutBitmapPause_(int surf_no)
{
    RECT rc;       // [esp+0h] [ebp-78h] BYREF
    DDBLTFX rcSrc; // [esp+10h] [ebp-68h] BYREF

    if (surf_no >= 64)
        return;

    if (!g_Surfaces[surf_no].surface)
        return;

    memset(&rcSrc, 0, sizeof(DDBLTFX));
    rcSrc.dwSize = 100;

    rc.left = 0;
    rc.right = MainSurfaceWidth;
    rc.top = 0;
    rc.bottom = MainSurfaceHeight;
    MagnifyRect(&rc);

    g_Surfaces[surf_no].surface->Blt(&rc, SurfaceB, &rc, DDBLT_WAIT, &rcSrc);
}

//----- (00423BB0) --------------------------------------------------------
void PutBitmap3(RECT *rcView, int x, int y, const RECT *rect, int surf_no)
{
    RECT rcWork; // [esp+0h] [ebp-20h] BYREF
    RECT rcSet;  // [esp+10h] [ebp-10h] BYREF

    if (surf_no >= 64)
        return;

    if (!g_Surfaces[surf_no].surface)
        return;

    rcWork = *rect;
    if (rect->right + x - rect->left > rcView->right)
        rcWork.right -= rect->right + x - rect->left - rcView->right;

    if (x < rcView->left)
    {
        rcWork.left += rcView->left - x;
        x = rcView->left;
    }

    if (rect->bottom + y - rect->top > rcView->bottom)
        rcWork.bottom -= rect->bottom + y - rect->top - rcView->bottom;

    if (y < rcView->top)
    {
        rcWork.top += rcView->top - y;
        y = rcView->top;
    }

    rcSet.left = x;
    rcSet.top = y;
    rcSet.right = rcWork.right + x - rcWork.left;
    rcSet.bottom = rcWork.bottom + y - rcWork.top;

    MagnifyRect(&rcWork);
    MagnifyRect(&rcSet);

    SurfaceB->Blt(&rcSet, g_Surfaces[surf_no].surface, &rcWork, DDBLT_WAIT | DDBLT_KEYSRC, 0);
}

//----- (00423D10) --------------------------------------------------------
void PutBitmap4(int x, int y, const RECT *rc, unsigned int surf_src, unsigned int surf_dst)
{
    RECT rcWork; // [esp+0h] [ebp-20h] BYREF
    RECT rcDst;  // [esp+10h] [ebp-10h] BYREF

    if (surf_src >= 64)
        return;
    if (surf_dst >= 64)
        return;

    if (!g_Surfaces[surf_src].surface)
        return;

    if (!g_Surfaces[surf_dst].surface)
        return;

    rcWork = *rc;
    rcDst.left = x;
    rcDst.top = y;
    rcDst.right = rc->right + x - rc->left;
    rcDst.bottom = rc->bottom + y - rc->top;

    MagnifyRect(&rcWork);
    MagnifyRect(&rcDst);

    g_Surfaces[surf_src].surface->Blt(
        &rcDst,
        g_Surfaces[surf_dst].surface,
        &rcWork,
        DDBLT_WAIT | DDBLT_KEYSRC,
        0);
}

//----- (00423E00) --------------------------------------------------------
void PutBackground(const RECT *rcView, int fill_color)
{
    RECT rcWork;   // [esp+0h] [ebp-78h] BYREF
    DDBLTFX bltfx; // [esp+10h] [ebp-68h] BYREF

    memset(&bltfx, 0, sizeof(bltfx));

    bltfx.dwSize = 100;
    bltfx.dwFillColor = fill_color;
    rcWork = *rcView;

    MagnifyRect(&rcWork);

    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &bltfx);
}

//----- (00423E70) --------------------------------------------------------
void PutRectOutline(const RECT *rcView, const RECT *rc, unsigned int color)
{
    RECT rcWork; // [esp+0h] [ebp-88h] BYREF
    DDBLTFX blt; // [esp+10h] [ebp-78h] BYREF
    RECT rcRect; // [esp+78h] [ebp-10h]

    memset(&blt, 0, sizeof(blt));
    blt.dwSize = 100;
    blt.dwFillColor = color;
    rcRect = *rc;

    if (rcRect.left < rcView->left)
        rcRect.left = rcView->left;
    if (rcRect.top < rcView->top)
        rcRect.top = rcView->top;
    if (rcRect.right > rcView->right)
        rcRect.right = rcView->right;
    if (rcRect.bottom > rcView->bottom)
        rcRect.bottom = rcView->bottom;

    rcWork.left = rcRect.left;
    rcWork.top = rcRect.top;
    rcWork.bottom = rcRect.bottom;
    rcWork.right = rcRect.left + 1;
    MagnifyRect(&rcWork);
    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &blt);

    rcWork.left = rcRect.left;
    rcWork.top = rcRect.top;
    rcWork.right = rcRect.right;
    rcWork.bottom = rcRect.top + 1;
    MagnifyRect(&rcWork);
    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &blt);

    rcWork.top = rcRect.top;
    rcWork.right = rcRect.right;
    rcWork.bottom = rcRect.bottom;
    rcWork.left = rcRect.right - 1;
    MagnifyRect(&rcWork);
    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &blt);

    rcWork.left = rcRect.left;
    rcWork.right = rcRect.right;
    rcWork.bottom = rcRect.bottom;
    rcWork.top = rcRect.bottom - 1;
    MagnifyRect(&rcWork);
    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &blt);
}

//----- (00424080) --------------------------------------------------------
void BlitSurface(const RECT *rc, unsigned int color, signed int surf_no)
{
    RECT rcWork; // [esp+0h] [ebp-78h] BYREF
    DDBLTFX blt; // [esp+10h] [ebp-68h] BYREF

    if (surf_no >= 64)
        return;

    if (!g_Surfaces[surf_no].surface)
        return;

    memset(&blt, 0, sizeof(blt));
    blt.dwSize = 100;
    blt.dwFillColor = color;

    if (rc)
    {
        rcWork = *rc;
    }
    else
    {
        rcWork.left = 0;
        rcWork.right = g_Surfaces[surf_no].width;
        rcWork.top = 0;
        rcWork.bottom = g_Surfaces[surf_no].height;
    }
    MagnifyRect(&rcWork);

    g_Surfaces[surf_no].surface->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &blt);
}

//----- (00424150) --------------------------------------------------------
void CortBox(const RECT *rcView, const RECT *rc, unsigned int color)
{
    RECT rcWork;   // [esp+0h] [ebp-78h] BYREF
    DDBLTFX bltfx; // [esp+10h] [ebp-68h] BYREF

    memset(&bltfx, 0, sizeof(bltfx));
    bltfx.dwSize = 100;
    bltfx.dwFillColor = color;
    rcWork = *rc;
    if (rcWork.left < rcView->left)
        rcWork.left = rcView->left;
    if (rcWork.top < rcView->top)
        rcWork.top = rcView->top;
    if (rcWork.right > rcView->right)
        rcWork.right = rcView->right;
    if (rcWork.bottom > rcView->bottom)
        rcWork.bottom = rcView->bottom;

    MagnifyRect(&rcWork);

    SurfaceB->Blt(&rcWork, 0, 0, DDBLT_WAIT | DDBLT_COLORFILL, &bltfx);
}

//----- (00424210) --------------------------------------------------------
int ConvertRGBToNative(unsigned int color)
{
    COLORREF cref;
    DDSURFACEDESC desc;
    HDC hdc;

    if (SurfaceB->GetDC(&hdc))
        return -1;

    cref = GetPixel(hdc, 0, 0);
    SetPixel(hdc, 0, 0, color);
    SurfaceB->ReleaseDC(hdc);

    memset(&desc, 0, sizeof(desc));
    desc.dwSize = 108;

    if (SurfaceB->Lock(NULL, &desc, 1, NULL))
        return -1;

    unsigned int col = *((unsigned int *)desc.lpSurface);

    if (desc.ddpfPixelFormat.dwRGBBitCount < 32)
        col &= (1u << (desc.ddpfPixelFormat.dwRGBBitCount)) - 1u;

    SurfaceB->Unlock(NULL);
    if (SurfaceB->GetDC(&hdc))
        return -1;

    SetPixel(hdc, 0, 0, cref);
    SurfaceB->ReleaseDC(hdc);

    return col;
}

//----- (00424340) --------------------------------------------------------
int GetSurfaceColor(int surf_no)
{
    DDSURFACEDESC desc;

    memset(&desc, 0, sizeof(desc));
    desc.dwSize = 108;

    if (g_Surfaces[surf_no].surface->Lock(NULL, &desc, 1, NULL))
        return -1;

    unsigned int col = *((unsigned int *)desc.lpSurface);

    if (desc.ddpfPixelFormat.dwRGBBitCount < 0x20)
        col &= (1u << desc.ddpfPixelFormat.dwRGBBitCount) - 1u;

    g_Surfaces[surf_no].surface->Unlock(NULL);

    return col;
}

//----- (004243E0) --------------------------------------------------------
void InitText(const char *pszFaceName, char width, int cHeight)
{
    h = CreateFontA(cHeight, width, 0, 0, 400, 0, 0, 0, 1u, 4u, 0, 0, 1u, pszFaceName);
}

//----- (00424420) --------------------------------------------------------
void PutText(int x, int y, LPCSTR lpString, COLORREF color)
{
    HGDIOBJ hObj;
    HDC hdc;

    SurfaceB->GetDC(&hdc);
    hObj = SelectObject(hdc, h);

    SetBkMode(hdc, 1);
    SetTextColor(hdc, color);
    TextOutA(hdc, x, y, lpString, strlen(lpString));
    SelectObject(hdc, hObj);

    SurfaceB->ReleaseDC(hdc);
}

//----- (004244C0) --------------------------------------------------------
void PutTextSurface(int x, int y, LPCSTR lpString, COLORREF color, int surf_id)
{
    HDC hdc;

    if (surf_id >= 64)
        return;

    if (!g_Surfaces[surf_id].surface)
        return;

    g_Surfaces[surf_id].surface->GetDC(&hdc);

    HGDIOBJ hObj = SelectObject(hdc, h);
    SetBkMode(hdc, 1);
    SetTextColor(hdc, color);

    int text_len = strlen(lpString);
    TextOutA(hdc, x, y, lpString, text_len);
    SelectObject(hdc, hObj);

    g_Surfaces[surf_id].surface->ReleaseDC(hdc);
}

//----- (00424590) --------------------------------------------------------
void ReleaseText()
{
    DeleteObject(h);
}

//----- (004245B0) --------------------------------------------------------
BOOL DoNothing2(int some_surf_id)
{
    return TRUE;
}

//----- (004245E0) --------------------------------------------------------
void Flip_Screen2()
{
    char tex_name_buf[268];
    int surfaces_lost;
    PxSurface *s;
    RECT rc;

    surfaces_lost = 0;
    rc.left = 0;
    rc.top = 0;
    rc.right = 0;
    rc.bottom = 0;

    if (!SurfaceA)
        return;
    if (!SurfaceB)
        return;

    if (SurfaceA->IsLost() == DDERR_SURFACELOST)
    {
        ++surfaces_lost;
        SurfaceA->Restore();
        DoNothing2(102);
    }

    if (SurfaceB->IsLost() == DDERR_SURFACELOST)
    {
        ++surfaces_lost;
        SurfaceB->Restore();
        DoNothing2(98);
    }

    for (int i = 0; i < 64; ++i)
    {
        if (!g_Surfaces[i].surface)
            continue;

        s = &g_Surfaces[i];
        if (s->surface->IsLost() != DDERR_SURFACELOST)
            continue;

        ++surfaces_lost;
        s->surface->Restore();

        DoNothing2(i + 48);

        if ((s->flags & 2) != 0)
            continue;

        if (s->tex_name)
        {
            strcpy(tex_name_buf, s->tex_name);
            MakeSurface_Generic(tex_name_buf, i, (s->flags & 1) != 0);
        }
        else
        {
            rc.right = s->width;
            rc.bottom = s->height;
            BlitSurface(&rc, 0, i);
        }
    }
}

//----- (004247F0) --------------------------------------------------------
BOOL __cdecl ResetSurfaceTbl(HWND hwnd, int mag)
{
    BOOL load_from_file; // [esp+0h] [ebp-124h]
    char path[268];      // [esp+4h] [ebp-120h] BYREF
    BOOL system_memory;  // [esp+114h] [ebp-10h]

    if (magnification == mag)
        return TRUE;

    int old_mag = magnification;

    ReleaseSurfaceA();
    InitMainSurface(hwnd, MainSurfaceWidth, MainSurfaceHeight, mag);

    for (int i = 0; i < 64; ++i)
    {
        if (!g_Surfaces[i].surface)
            continue;

        PxSurface *s = &g_Surfaces[i];

        s->surface->Release();
        s->surface = NULL;

        totalSurfaceSize -= old_mag * s->height * old_mag * s->width;
        load_from_file = (s->flags & 1) != 0;
        system_memory = (s->flags & 2) != 0;

        if (s->tex_name)
        {
            strcpy(path, s->tex_name);
            InitSurface(s->width, s->height, i, system_memory);
            MakeSurface_Generic(path, i, load_from_file);
        }
        else
        {
            InitSurface(s->width, s->height, i, system_memory);
        }
    }

    return TRUE;
}