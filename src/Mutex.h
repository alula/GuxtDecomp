#ifndef __MUTEX_H__
#define __MUTEX_H__

class Mutex
{
    HANDLE mapping;
    HANDLE mutex_handle;
    HWND* hwnd_channel;

public:
    Mutex();
    ~Mutex();

    BOOL Start(const char* name, const char* mutex_name);
    BOOL MapFile(const char *name, const char *mutex_name, void* a4);
};

#endif