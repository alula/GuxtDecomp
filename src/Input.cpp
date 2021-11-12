#include <windows.h>

#include "Input.h"

static char keysHeld[256];
static char keysPrev[256];
static char keysTrig[256];
static int mouseHeld;
static int mousePrev;
static int mouseTrig;
static int unused1;
static int unused2;
static int unused3;

//----- (00425890) --------------------------------------------------------
void Input_Reset()
{
    memset(keysHeld, 0, sizeof(keysHeld));
    memset(keysPrev, 0, sizeof(keysPrev));
    memset(keysTrig, 0, sizeof(keysTrig));
    mouseHeld = 0;
    mousePrev = 0;
    mouseTrig = 0;
    unused1 = 0;
    unused2 = 0;
    unused3 = 0;
}
