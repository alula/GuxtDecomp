#include <windows.h>
#include <dsound.h>

#include "Sound.h"

#define SOUND_NUM 64

LPDIRECTSOUND dsInstance = NULL;
BOOL dsExternallyInitialized = FALSE;
static LPDIRECTSOUNDBUFFER _buffers[SOUND_NUM];

//----- (00424990) --------------------------------------------------------
void AssignDirectSound(void *a1)
{
    dsInstance = (LPDIRECTSOUND)a1;
    dsExternallyInitialized = TRUE;
}

//----- (004249B0) --------------------------------------------------------
BOOL UnusedInitDirectSound(HWND hwnd)
{
    if (DirectSoundCreate(0, &dsInstance, 0))
    {
        dsInstance = NULL;
        return FALSE;
    }

    dsExternallyInitialized = FALSE;
    if (dsInstance->SetCooperativeLevel(hwnd, 2))
        return FALSE;

    for (int i = 0; i < SOUND_NUM; ++i)
        _buffers[i] = NULL;

    return TRUE;
}

//----- (00424A30) --------------------------------------------------------
void ReleaseDirectSound()
{
    if (!dsInstance)
        return;

    for (int i = 0; i < SOUND_NUM; ++i)
    {
        if (_buffers[i])
        {
            _buffers[i]->Release();
            _buffers[i] = NULL;
        }
    }

    if (!dsExternallyInitialized && dsInstance)
        dsInstance->Release();
}

//----- (00424AC0) --------------------------------------------------------
BOOL Sound_CreateWAV(const char *lpName, const char *lpType, signed int a3)
{
    // TODO
    return TRUE;
}

//----- (00424C90) --------------------------------------------------------
BOOL Sound_LoadWAV(const char *lpName, const char *lpType, void *a3, int a4, int a5)
{
    // TODO
    return TRUE;
}

//----- (00424EB0) --------------------------------------------------------
BOOL sub_424EB0(void **a1, size_t a2)
{
    *a1 = malloc(a2);
    if (!*a1)
        return FALSE;

    memset(*a1, 0, a2);
    return TRUE;
}

//----- (004251F0) --------------------------------------------------------
void Sound_ReleaseBuffer(int idx)
{
    if (!dsInstance)
        return;
    if (!_buffers[idx])
        return;
    if (idx < 0 || idx > SOUND_NUM)
        return;

    _buffers[idx]->Release();
    _buffers[idx] = NULL;
}

//----- (00425250) --------------------------------------------------------
void Sound_Replay(int idx)
{
    if (!dsInstance)
        return;
    if (!_buffers[idx])
        return;
    if (idx < 0 || idx > SOUND_NUM)
        return;

    _buffers[idx]->Stop();
    _buffers[idx]->SetCurrentPosition(0);
    _buffers[idx]->Play(0, 0, 0);
}

//----- (004252E0) --------------------------------------------------------
void Sound_Loop(int idx)
{
    if (!dsInstance)
        return;
    if (!_buffers[idx])
        return;
    if (idx < 0 || idx > SOUND_NUM)
        return;

    _buffers[idx]->Play(0, 0, DSBPLAY_LOOPING);
}

//----- (00425330) --------------------------------------------------------
void Sound_Stop(int idx)
{
    if (!dsInstance)
        return;
    if (!_buffers[idx])
        return;
    if (idx < 0 || idx > SOUND_NUM)
        return;

    _buffers[idx]->Stop();
}