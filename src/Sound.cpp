#include <windows.h>
#include <stdio.h>
#include <dsound.h>

#include "Sound.h"
#include "PixFile.h"
#include "WinMain.h"
#include "pxtone.h"
#include "pxtone/pxtoneNoise.h"

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

void pxMem_free(void **a1);

//----- (00424AC0) --------------------------------------------------------
BOOL Sound_CreateWAV(const char *lpName, const char *lpType, int idx)
{
    void *v4;             // [esp+0h] [ebp-44h] BYREF
    DWORD v5;             // [esp+4h] [ebp-40h] BYREF
    DSBUFFERDESC bufDsc;  // [esp+8h] [ebp-3Ch] BYREF
    WAVEFORMATEX waveFmt; // [esp+1Ch] [ebp-28h] BYREF
    int a4;               // [esp+30h] [ebp-14h] BYREF
    void *v9;             // [esp+34h] [ebp-10h] BYREF
    int v10;              // [esp+38h] [ebp-Ch]
    DWORD v11;            // [esp+3Ch] [ebp-8h] BYREF
    void *a5;             // [esp+40h] [ebp-4h] BYREF

    v10 = 0;
    a5 = 0;
    if (!dsInstance)
        return 1;

    if (idx >= 0 && idx < 0x40)
    {
        if (Sound_LoadWAV(lpName, lpType, &waveFmt, &a4, &a5))
        {
            memset(&bufDsc, 0, sizeof(bufDsc));
            bufDsc.dwSize = 20;
            bufDsc.dwFlags = 32994;
            bufDsc.dwBufferBytes = a4;
            bufDsc.lpwfxFormat = &waveFmt;
            if (!dsInstance->CreateSoundBuffer(&bufDsc, &_buffers[idx], 0) && !_buffers[idx]->Lock(0, a4, &v9, &v5, &v4, &v11, 0))
            {
                memcpy(v9, a5, v5);

                if (v11)
                    memcpy(v4, (char *)a5 + v5, v11);

                _buffers[idx]->Unlock(v9, v5, v4, v11);
                v10 = 1;
            }
        }
    }

    pxMem_free(&a5);

    if (v10)
        return TRUE;

    if (!_buffers[idx])
        return TRUE;

    _buffers[idx]->Release();
    _buffers[idx] = NULL;

    return TRUE;
}

//----- (00424C60) --------------------------------------------------------
void pxMem_free(void **a1)
{
    if (*a1)
    {
        free(*a1);
        *a1 = 0;
    }
}

//----- (00424C90) --------------------------------------------------------
BOOL Sound_LoadWAV(const char *lpName, const char *lpType, LPWAVEFORMATEX a3, int *pSize, void **pBuffer)
{
    char hdr[44]; // [esp+0h] [ebp-4Ch] BYREF
    size_t a2;    // [esp+30h] [ebp-1Ch] BYREF
    BOOL result;  // [esp+34h] [ebp-18h]
    PixFile file; // [esp+38h] [ebp-14h] BYREF

    result = 0;
    *pBuffer = 0;
    memset(a3, 0, sizeof(WAVEFORMATEX));

    if (!OpenResource_(0, lpName, lpType, &file))
        goto err;

    if (!ReadFromFile(hdr, 1u, 44, &file))
        goto err;

    if (hdr[0] == 'R' && hdr[1] == 'I' && hdr[2] == 'F' && hdr[3] == 'F' && hdr[8] == 'W' && hdr[9] == 'A' && hdr[10] == 'V' && hdr[11] == 'E' && hdr[12] == 'f' && hdr[13] == 'm' && hdr[14] == 't' && hdr[15] == ' ')
    {
        memcpy(a3, &hdr[20], sizeof(WAVEFORMATEX));
        if (a3->wFormatTag == 1 && (a3->nChannels == 1 || a3->nChannels == 2) && (a3->wBitsPerSample == 8 || a3->wBitsPerSample == 16))
        {
            SeekResource(&file, 12, 0);

            while (ReadFromFile(hdr, 1u, 8, &file))
            {
                memcpy(&a2, &hdr[4], sizeof(a2));

                if (!memcmp("data", hdr, 4u))
                {
                    if (pxMem_zero_alloc(pBuffer, a2))
                    {
                        if (ReadFromFile(*pBuffer, 1u, a2, &file))
                        {
                            *pSize = a2;
                            result = 1;
                        }
                    }
                    break;
                }

                SeekResource(&file, a2, 1);
            }
        }
    }

err:
    if (!result)
        pxMem_free(pBuffer);

    CloseResource_(&file);

    return result;
}

//----- (00424EB0) --------------------------------------------------------
BOOL pxMem_zero_alloc(void **a1, size_t a2)
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

BOOL loopsoundplaying_ = FALSE;
int loopsound_ = 0;
BOOL soundDisabled = FALSE;

//----- (00421770) --------------------------------------------------------
void ClearLoopSound()
{
    loopsoundplaying_ = FALSE;
    loopsound_ = 0;
}
// 44C8AC: using guessed type int loopsoundplaying_;

//----- (00421790) --------------------------------------------------------
void StopLoopSound2()
{
    if (loopsoundplaying_)
    {
        Sound_Stop(loopsound_);
        loopsoundplaying_ = FALSE;
        loopsound_ = 0;
    }
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
    return Sound_CreatePtNoise(Name, NULL, chans, sps, bps, idx) != 0;
}

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
BOOL Sound_CreatePtNoise(const char *lpName, const char *lpType, int channels, int sps, int bps, int sfx_idx)
{
    void *v7;         // [esp+0h] [ebp-44h] BYREF
    DWORD v8;         // [esp+4h] [ebp-40h] BYREF
    DSBUFFERDESC v9;  // [esp+8h] [ebp-3Ch] BYREF
    WAVEFORMATEX v10; // [esp+1Ch] [ebp-28h] BYREF
    int v11;          // [esp+30h] [ebp-14h] BYREF
    void *v12;        // [esp+34h] [ebp-10h] BYREF
    BOOL result;      // [esp+38h] [ebp-Ch]
    DWORD v14;        // [esp+3Ch] [ebp-8h] BYREF
    char *v15;        // [esp+40h] [ebp-4h] BYREF
    pxtoneNoise noise;
    pxtnDescriptor desc;
    PixFile file;

    // This function has been adapted to slightly newer PxTone code, so it's not accurately decompiled.

    result = FALSE;
    if (!dsInstance)
        return TRUE;

    if (sfx_idx < 0 || sfx_idx >= 64)
        goto err;
    {
        OpenResource_(NULL, lpName, lpType, &file);
        desc.set_file_r(file.fp);

        if (!noise.init())
            goto err;

        noise.quality_set(channels, sps, bps);

        if (!noise.generate(&desc, (void **)&v15, &v11))
            goto err;

        memset(&v10, 0, sizeof(v10));

        v10.cbSize = 0;
        v10.wFormatTag = 1;
        v10.nChannels = channels;
        v10.nSamplesPerSec = sps;
        v10.wBitsPerSample = bps;
        v10.nBlockAlign = v10.wBitsPerSample * v10.nChannels / 8;
        v10.nAvgBytesPerSec = v10.nSamplesPerSec * v10.nBlockAlign;

        memset(&v9, 0, sizeof(v9));
        v9.dwSize = 20;
        v9.dwFlags = 32994;
        v9.dwBufferBytes = v11;
        v9.lpwfxFormat = &v10;

        if (!dsInstance->CreateSoundBuffer(&v9, &_buffers[sfx_idx], 0) && !_buffers[sfx_idx]->Lock(0, v11, &v12, &v8, &v7, &v14, 0))
        {
            memcpy(v12, v15, v8);
            if (v14)
                memcpy(v7, &v15[v8], v14);
            _buffers[sfx_idx]->Unlock(v12, v8, v7, v14);

            result = TRUE;
        }
    }

err:
    if (!result)
    {
        if (_buffers[sfx_idx])
        {
            _buffers[sfx_idx]->Release();
            _buffers[sfx_idx] = 0;
        }
    }

    return result;
}