#include <windows.h>
#include <stdio.h>
#include <dsound.h>

#include "Sound.h"
#include "WinMain.h"
#include "pxtone.h"

static long pxtoneFadeReturnValue = 0;
static BOOL isMusicPlaying = FALSE;

//----- (00401000) --------------------------------------------------------
BOOL LoadMusic(const char *file_name)
{
    char path[268]; // [esp+0h] [ebp-110h] BYREF

    pxtone_Tune_Stop();
    isMusicPlaying = FALSE;
    sprintf(path, "%s\\%s.%s", dataPath, file_name, "ptcop");

    return pxtone_Tune_Load(0, 0, path);
}

//----- (00401070) --------------------------------------------------------
BOOL StartMusic(long start_sample)
{
    isMusicPlaying = FALSE;
    if (!pxtone_Tune_Start(start_sample, 0))
        return FALSE;

    isMusicPlaying = TRUE;
    return TRUE;
}

//----- (004010B0) --------------------------------------------------------
void SetMusicVolume(long msec)
{
    isMusicPlaying = FALSE;
    pxtone_Tune_Fadeout(msec);
}

//----- (004010D0) --------------------------------------------------------
void FadeMusic()
{
    if (isMusicPlaying)
        pxtoneFadeReturnValue = pxtone_Tune_Fadeout(200);
}

//----- (00401100) --------------------------------------------------------
void ResumeMusic()
{
    if (isMusicPlaying)
        pxtone_Tune_Start(pxtoneFadeReturnValue, 200);
}

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

//----- (004217C0) --------------------------------------------------------
BOOL LoadSound(const char *file_name, int idx)
{
    long sps;
    char Name[268];
    long bps;
    long chans;

    sprintf(Name, "%s\\%s.%s", dataPath, file_name, "ptnoise");
    pxtone_GetQuality(&chans, &sps, &bps, 0);
    return Sound_CreatePtNoise(Name, 0, chans, sps, bps, idx) != 0;
}

BOOL loopsoundplaying_ = FALSE;
int loopsound_ = 0;
BOOL soundDisabled = FALSE;

//----- (00421870) --------------------------------------------------------
void PlaySound(int idx)
{
    if (!soundDisabled)
        Sound_Replay(idx);
}

//----- (004218B0) --------------------------------------------------------
void PlayLoopSound(int idx)
{
    Sound_Loop(idx);
    loopsoundplaying_ = 1;
    loopsound_ = idx;
}

//----- (004218E0) --------------------------------------------------------
void StopLoopSound(int a1)
{
    Sound_Stop(a1);
    loopsoundplaying_ = 0;
    loopsound_ = 0;
}

//----- (00421910) --------------------------------------------------------
void PauseLoopSound()
{
    if (loopsoundplaying_)
        Sound_Stop(loopsound_);
}

//----- (00421930) --------------------------------------------------------
void ResumeLoopSound()
{
    if (loopsoundplaying_)
        Sound_Loop(loopsound_);
}

//----- (00421950) --------------------------------------------------------
void SetSoundDisabled(BOOL disabled)
{
    soundDisabled = disabled;
}

//----- (00424EF0) --------------------------------------------------------
BOOL Sound_CreatePtNoise(const char *lpName, const char *lpType, int a3, int a4, int a5, signed int sfx_idx)
{
    // TODO
    return TRUE;
}