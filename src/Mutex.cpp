#include <windows.h>
#include "Mutex.h"

Mutex::Mutex()
{
    mapping = NULL;
    mutex_handle = NULL;
    hwnd_channel = NULL;
}

Mutex::~Mutex()
{
    if (mutex_handle)
        ReleaseMutex(mutex_handle);
    if (mapping)
        CloseHandle(mapping);
    if (hwnd_channel)
        UnmapViewOfFile(hwnd_channel);
}

static void ShowExistingWindow(const char *lpName)
{
    HANDLE hObject;      // [esp+0h] [ebp-8h]
    HWND *lpBaseAddress; // [esp+4h] [ebp-4h]

    hObject = CreateFileMappingA(INVALID_HANDLE_VALUE, 0, 4u, 0, 4u, lpName);
    if (!hObject)
        return;

    if (GetLastError() == ERROR_ALREADY_EXISTS && (lpBaseAddress = (HWND *)MapViewOfFile(hObject, 2u, 0, 0, 4u)) != 0)
    {
        if (IsWindowVisible(*lpBaseAddress))
        {
            SetForegroundWindow(*lpBaseAddress);
            ShowWindow(*lpBaseAddress, TRUE);
        }

        UnmapViewOfFile(lpBaseAddress);
        CloseHandle(hObject);
    }
    else
    {
        CloseHandle(hObject);
    }
}

BOOL Mutex::Start(const char *lpName, const char *a3)
{
    bool result;

    mutex_handle = OpenMutexA(MUTEX_ALL_ACCESS, 0, lpName);
    if (mutex_handle)
    {
        ShowExistingWindow(a3);
        result = FALSE;
    }
    else
    {
        mutex_handle = CreateMutexA(0, 0, lpName);
        result = mutex_handle != 0;
    }

    return result;
}

BOOL Mutex::MapFile(const char *name, const char *mutex_name, HWND hwnd)
{
    BOOL result;

    mutex_handle = CreateMutexA(0, 0, name);
    if (!mutex_handle)
        return false;

    mapping = CreateFileMappingA(INVALID_HANDLE_VALUE, 0, 4u, 0, 4u, mutex_name);
    if (mapping)
    {
        hwnd_channel = (HWND *)MapViewOfFile(mapping, 2u, 0, 0, 4u);
        if (hwnd_channel)
        {
            *hwnd_channel = hwnd;
            result = true;
        }
        else
        {
            ReleaseMutex(mutex_handle);
            mutex_handle = NULL;

            CloseHandle(mapping);
            mapping = NULL;
            
            result = true;
        }
    }
    else
    {
        ReleaseMutex(mutex_handle);
        mutex_handle = NULL;
        result = false;
    }

    return result;
}