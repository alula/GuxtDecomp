#ifndef __DRAW_H__
#define __DRAW_H__

#include <windows.h>

struct PximgDecodeInfo
{
    unsigned int height;
    int *line_indexes;
    unsigned int hash_a;
    unsigned int hash_b;
};

void ClearSurface(int surf_id);

void ClearSurfaceTbl();

int GetTotalSurfaceSize();

void SetRenderOffset(int off_x, int off_y);

void SetFullscreenRenderPos();

BOOL SetFullscreenDDrawParams(BOOL fullscreen);

BOOL InitDirectDraw(HWND a1, char *data_path, BOOL fullscreen, BOOL scrambled_sprites);

void EndDirectDraw(HWND hwnd);

BOOL InitMainSurface(HWND hwnd, int width, int height, int mag);

void ReleaseSurfaceA();

BOOL Flip_Screen();

BOOL MakeSurface_Pximg(char *name, int surf_no, BOOL load_from_file, BOOL system_memory);

BOOL DecodePximg(PximgDecodeInfo *info, int img_height, unsigned short hash_a, unsigned short hash_b);

unsigned short PximgHashShuffle(PximgDecodeInfo *info);

void ReleasePximgDecoder(PximgDecodeInfo *info);

BOOL InitSurface(int width, int height, int surf_no, BOOL system_memory);

BOOL MakeSurface_Generic(const char *path, int surf_no, int load_from_file);

BOOL GetSurfaceSize(int *p_width, int *p_height, int surf_no);

void MagnifyRect(RECT *rc);

void PutRect(int x, int y, RECT *rect, int surf_no);

void PutBitmapPause_(int surf_no);

void PutBitmap3(RECT *rcView, int x, int y, const RECT *rect, int surf_no);

void PutBitmap4(int x, int y, const RECT *rc, unsigned int surf_src, unsigned int surf_dst);

void PutBackground(const RECT *rcView, int fill_color);

void PutRectOutline(const RECT *rcView, const RECT *rc, unsigned int color);

void BlitSurface(const RECT *rc, unsigned int color, int surf_no);

void CortBox(const RECT *rcView, const RECT *rc, unsigned int color);

int ConvertRGBToNative(unsigned int color);

int GetSurfaceColor(int surf_no);

void InitText(const char *pszFaceName, char width, int cHeight);

void PutText(int x, int y, LPCSTR lpString, COLORREF color);

void PutTextSurface(int x, int y, LPCSTR lpString, COLORREF color, int surf_id);

void ReleaseText();

BOOL DoNothing2(int some_surf_id);

void Flip_Screen2();

BOOL  ResetSurfaceTbl(HWND hwnd, int mag);

#endif