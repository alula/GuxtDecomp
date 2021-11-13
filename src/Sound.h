#ifndef __SOUND_H__
#define __SOUND_H__

#include <windows.h>

BOOL LoadMusic(const char *file_name);
BOOL StartMusic(long start_sample);
void SetMusicVolume(long msec);
void FadeMusic();
void ResumeMusic();

void AssignDirectSound(void *a1);
BOOL UnusedInitDirectSound(HWND hwnd);
void ReleaseDirectSound();

BOOL Sound_CreateWAV(const char *lpName, const char *lpType, signed int a3);
BOOL Sound_LoadWAV(const char *lpName, const char *lpType, void *a3, int a4, int a5);
BOOL sub_424EB0(void **a1, size_t a2);
void Sound_ReleaseBuffer(int idx);
void Sound_Replay(int idx);
void Sound_Loop(int idx);
void Sound_Stop(int idx);

void ClearLoopSound();
void StopLoopSound2();
BOOL LoadSound(const char* file_name, int idx);

void PlaySound(int idx);
void PlayLoopSound(int idx);
void StopLoopSound(int a1);
void PauseLoopSound();
void ResumeLoopSound();
void SetSoundDisabled(BOOL disabled);

BOOL Sound_CreatePtNoise(const char *lpName, const char *lpType, int a3, int a4, int a5, signed int sfx_idx);

#endif