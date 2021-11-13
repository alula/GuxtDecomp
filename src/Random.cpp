#include "Random.h"

static int randomSeed1; // weak
static int randomSeed2; // weak

void ResetRandom()
{
    randomSeed1 = 0x4444;
    randomSeed2 = 0x8888;
}

unsigned short GetRandom(int max)
{
    unsigned short v2; // [esp+0h] [ebp-10h]

    int seed = (randomSeed2 + randomSeed1);
    ((unsigned char *)&v2)[0] = seed >> 8;
    ((unsigned char *)&v2)[1] = seed & 0xFF;

    randomSeed2 = randomSeed1;
    randomSeed1 = v2;

    return v2 % max;
}