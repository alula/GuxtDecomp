#include <windows.h>

#include "Object.h"
#include "Bullet.h"
#include "Caret.h"
#include "Draw.h"
#include "Game.h"
#include "GameAttr.h"
#include "Map.h"
#include "NpcAct000.h"
#include "NpcAct020.h"
#include "NpcAct040.h"
#include "NpcAct060.h"
#include "NpcAct080.h"
#include "NpcAct100.h"
#include "NpcShip.h"
#include "Stage.h"
#include "Sound.h"

unsigned int backgroundColor;

//----- (004015B0) --------------------------------------------------------
void SetBackgroundColor()
{
    backgroundColor = ConvertRGBToNative(0xA0u);
}

//----- (004015D0) --------------------------------------------------------
void PutObject(RECT *rcView, Object *obj, int frame_x, int frame_y)
{
    int x;  // [esp+0h] [ebp-8h]
    int xa; // [esp+0h] [ebp-8h]
    int y;  // [esp+4h] [ebp-4h]
    int ya; // [esp+4h] [ebp-4h]

    if ((obj->cond & 1) == 0)
        return;

    x = obj->x - obj->xoff;
    y = obj->y - obj->yoff;
    if (x < 0)
        x -= 1023;
    if (y < 0)
        y -= 1023;
    if ((obj->flag & 0x10) != 0)
    {
        xa = x / 1024 - frame_x;
        ya = y / 1024 - frame_y;
    }
    else
    {
        xa = x / 1024;
        ya = y / 1024;
    }

    PutBitmap3(rcView, xa, ya, &obj->rect, obj->surf);
}

//----- (00403170) --------------------------------------------------------
Object *GetNpcTable()
{
    return EntityTbl;
}

//----- (00403180) --------------------------------------------------------
void ResetEntities()
{
    EntityCreateCount = 0;
    memset(EntityTbl, 0, sizeof(EntityTbl));
}

//----- (004031B0) --------------------------------------------------------
void LoadPximgEntities()
{
    LoadPximg("enemy_generic", 5);
    LoadPximg("power", 15);
    LoadPximg("caret", 7);
    LoadPximg("popup", 8);
    LoadPximg("bonus", 14);
    ResetEntities();
}

void (*npcFuncTbl[122])(Object *a1) =
    {
        ActNpc000,
        ActNpc001_Explode,
        ActNpc002_CloudL,
        ActNpc003_CloudS,
        ActNpc004_Puff,
        ActNpc005_Hanger,
        ActNpc006_CloudGen,
        ActNpc007_Powerup,
        ActNpc008_Climber,
        ActNpc009_Kagome,
        ActNpc010_Unused_,
        ActNpc011_Wing,
        ActNpc012_WingCorpse,
        ActNpc013_Bullet,
        ActNpc014_BulletSlow,
        ActNpc015_Boss1,
        ActNpc016_Boss1Eye,
        ActNpc017_Boss1BigEye,
        ActNpc018_BulletLong,
        ActNpc019_BGM,
        ActNpc020_Asteroid_L,
        ActNpc021_Asteroid_S,
        ActNpc022_ScrollSpdSet,
        ActNpc023_Asteroid_SGravity,
        ActNpc024_Hanger_Wave,
        ActNpc025_Hanger_Shoot,
        ActNpc026_RockHugger,
        ActNpc027_RHAsteroidL,
        ActNpc028_RHAsteroidS,
        ActNpc029_Bullet2_,
        ActNpc030_Elka,
        ActNpc031_Sodi,
        ActNpc032_Boss2,
        ActNpc033_Boss2RocketSpawner,
        ActNpc034_B2ExplosionSpawner_,
        ActNpc035_B2Rocket,
        ActNpc036_Boss2Eye,
        ActNpc037_Stars_,
        ActNpc038_StarGen,
        ActNpc039_Elka2,
        ActNpc040_GuxtFort,
        ActNpc041_CatEye,
        ActNpc042_Slider,
        ActNpc043_Cycloid,
        ActNpc044_Chester,
        ActNpc045_Bonus,
        ActNpc046_BonusGen,
        ActNpc047_CloudXL,
        ActNpc048_Gimmick,
        ActNpc049_Boss3,
        ActNpc050_62_PowerupHelper,
        ActNpc051_B3Eye1_,
        ActNpc052_B3Eye2_,
        ActNpc053_B3Eye3_,
        ActNpc054_B3BulletBlocker_,
        ActNpc055_B3Target__,
        ActNpc056_Checkpoint,
        ActNpc057_Boss3TurretSpawner,
        ActNpc058_B3Turret,
        ActNpc059_PowerupSpinnerShield,
        ActNpc060_PowerupBox,
        ActNpc061_PowerupStatic,
        ActNpc050_62_PowerupHelper,
        ActNpc063_BulletWhite,
        ActNpc064_PowerupSpinner,
        ActNpc065_ClimberShoot,
        ActNpc066_Tri,
        ActNpc067_GuxtTank,
        ActNpc068_MedusaEye,
        ActNpc069_GuxtMine,
        ActNpc070_BlendyGen,
        ActNpc071_Blendy,
        ActNpc072_Cycloid2,
        ActNpc073_Cycloid2Gen,
        ActNpc074_PowerupHidden,
        ActNpc075_PowerupAsteroid,
        ActNpc076_Boss4,
        ActNpc077,
        ActNpc078,
        ActNpc079,
        ActNpc080,
        ActNpc081_SpaceAmeba,
        ActNpc082,
        ActNpc083_B4Bullet,
        ActNpc084_Square,
        ActNpc085_CloudDarkL,
        ActNpc086_CloudDarkS,
        ActNpc087_CloudDarkGen,
        ActNpc088_MissilePot,
        ActNpc089,
        ActNpc090_Missile,
        ActNpc091,
        ActNpc092_BGRock,
        ActNpc093_ClearRockCloudGen,
        ActNpc094_SandStamper,
        ActNpc095,
        ActNpc096_Stamp,
        ActNpc097_Brick,
        ActNpc098_BulletSquare,
        ActNpc099_BulletSquareGen,
        ActNpc100_Boss5,
        ActNpc101,
        ActNpc102_B5Bullet,
        ActNpc103,
        ActNpc104_B5Laser,
        ActNpc105_B5LaserTrail,
        ActNpc106_AzaBonusSpawner_,
        ActNpc107,
        ActNpc108_Boss6,
        ActNpc109,
        ActNpc110,
        ActNpc111_B6Laser,
        ActNpc112,
        ActNpc113,
        ActNpc114_B6Ball,
        ActNpc115_B6Caret,
        ActNpc116_CreditText,
        ActNpc117_CreditReplace,
        ActNpc118_CreditLoadImg,
        ActNpc119_CPhoto,
        ActNpc120_CreditGimmick,
        ActNpc121_BonusHidden
}; // weak

//----- (00403210) --------------------------------------------------------
void ActNpc()
{
    int i;      // [esp+0h] [ebp-8h]
    Object *v1; // [esp+4h] [ebp-4h]

    for (i = 0; i < 256; ++i)
    {
        v1 = &EntityTbl[i];

        if ((v1->cond & 2) != 0)
        {
            v1->cond = 0;
        }
        else if ((v1->cond & 1) != 0)
        {
            if (v1->shock)
                --v1->shock;

            npcFuncTbl[v1->type](v1);
        }
    }
}

//----- (004032A0) --------------------------------------------------------
void HitEntityMap()
{
    int i;                     // [esp+0h] [ebp-8h]
    Object *o = &EntityTbl[0]; // [esp+4h] [ebp-4h]

    for (i = 0; i < 256; ++i, ++o)
    {
        if ((o->cond & 1) != 0)
            HitMapGeneric(o, MapCollideEntityProc, 0);
    }
}

//----- (00403300) --------------------------------------------------------
void MapCollideEntityProc(Object *a1, int a2, int a3, int a4)
{
    if ((a1->flag & 0x20) != 0)
    {
        a1->cond = 0;
        SetCaret(2, a1->x, a1->y, 0);
    }
    if ((a1->flag & 0x40) != 0)
    {
        a1->x = a2;
        a1->y = a3;
        a1->cond |= a4;
    }
}

//----- (00403360) --------------------------------------------------------
void PutNpChar2(RECT *rcView)
{
    int i;      // [esp+0h] [ebp-Ch]
    int scroll; // [esp+4h] [ebp-8h]
    int x;      // [esp+8h] [ebp-4h]

    x = GetStageXOffset() / 0x400;
    scroll = GetStageScroll() / 0x400;

    for (i = 50; i < 256; ++i)
        PutObject(rcView, &EntityTbl[i], x, scroll);
}

//----- (004033D0) --------------------------------------------------------
void PutNpChar(RECT *rcView)
{
    int i;      // [esp+0h] [ebp-Ch]
    int scroll; // [esp+4h] [ebp-8h]
    int x;      // [esp+8h] [ebp-4h]

    x = GetStageXOffset() / 0x400;
    scroll = GetStageScroll() / 0x400;

    for (i = 0; i < 50; ++i)
        PutObject(rcView, &EntityTbl[i], x, scroll);
}

Object EntityTbl[256];
int EntityCreateCount;
unsigned char KagomeCount;
unsigned char byte_44C265;
int dword_44C268;
unsigned char byte_44C26C;
int bonusAzaX;
int asteroidsKilled;
int bonusAzaY;

static NpcAttr NpcAttrTbl[122] =
    {
        {16u, 3u, 1u, 1u, 8u, 8u, 7u, 7u, 6, 5u, 0u},
        {0u, 8u, 0u, 0u, 16u, 16u, 0u, 0u, 0, 7u, 0u},
        {0u, 3u, 0u, 0u, 24u, 16u, 0u, 0u, 0, 6u, 0u},
        {0u, 2u, 0u, 0u, 8u, 4u, 0u, 0u, 0, 6u, 0u},
        {0u, 5u, 0u, 0u, 4u, 4u, 0u, 0u, 0, 7u, 0u},
        {0u, 6u, 2u, 0u, 12u, 12u, 8u, 8u, 1000, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {2u, 8u, 4u, 0u, 8u, 8u, 8u, 8u, 0, 5u, 0u},
        {67u, 5u, 1u, 1u, 8u, 8u, 5u, 5u, 3, 5u, 0u},
        {67u, 5u, 1u, 1u, 8u, 8u, 6u, 6u, 8, 5u, 0u},
        {0u, 9u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 3u, 1u, 20u, 8u, 5u, 4u, 24, 6u, 1u},
        {10u, 4u, 0u, 1u, 0u, 0u, 6u, 2u, 0, 6u, 0u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {0u, 4u, 7u, 1u, 68u, 16u, 7u, 6u, 1000, 6u, 2u},
        {0u, 4u, 3u, 1u, 8u, 8u, 4u, 3u, 100, 6u, 0u},
        {0u, 4u, 0u, 1u, 12u, 20u, 12u, 16u, 100, 6u, 3u},
        {2u, 8u, 0u, 1u, 8u, 8u, 2u, 4u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {67u, 4u, 0u, 1u, 8u, 8u, 5u, 5u, 6, 5u, 3u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 5u, 0u, 1u, 8u, 8u, 5u, 5u, 6, 5u, 3u},
        {0u, 6u, 1u, 1u, 12u, 12u, 8u, 8u, 6, 5u, 0u},
        {0u, 6u, 1u, 0u, 12u, 12u, 8u, 8u, 6, 5u, 0u},
        {67u, 5u, 2u, 1u, 12u, 12u, 8u, 8u, 100, 6u, 0u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {67u, 4u, 0u, 1u, 8u, 8u, 5u, 5u, 100, 5u, 3u},
        {0u, 8u, 0u, 0u, 4u, 4u, 0u, 0u, 0, 7u, 0u},
        {67u, 4u, 4u, 1u, 16u, 16u, 12u, 12u, 36, 6u, 2u},
        {67u, 6u, 2u, 1u, 12u, 12u, 10u, 8u, 10, 5u, 1u},
        {0u, 4u, 7u, 1u, 28u, 24u, 0u, 0u, 1000, 6u, 2u},
        {10u, 4u, 0u, 1u, 20u, 52u, 9u, 36u, 0, 6u, 0u},
        {10u, 4u, 0u, 1u, 20u, 24u, 12u, 15u, 1000, 6u, 3u},
        {67u, 6u, 0u, 1u, 8u, 8u, 4u, 4u, 1, 6u, 3u},
        {0u, 4u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 2u},
        {0u, 0u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 7u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {16u, 4u, 4u, 1u, 16u, 16u, 12u, 12u, 100, 6u, 2u},
        {16u, 3u, 2u, 1u, 8u, 8u, 7u, 7u, 10, 5u, 3u},
        {16u, 3u, 2u, 1u, 8u, 8u, 7u, 7u, 6, 5u, 3u},
        {16u, 4u, 3u, 1u, 16u, 8u, 8u, 6u, 24, 6u, 1u},
        {67u, 5u, 1u, 1u, 8u, 8u, 5u, 5u, 2, 5u, 0u},
        {16u, 5u, 2u, 1u, 8u, 8u, 6u, 6u, 2, 6u, 0u},
        {2u, 8u, 4u, 0u, 8u, 8u, 6u, 6u, 0, 14u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 4u, 0u, 0u, 48u, 40u, 0u, 0u, 0, 6u, 0u},
        {16u, 3u, 3u, 1u, 8u, 8u, 6u, 6u, 6, 6u, 3u},
        {16u, 3u, 7u, 1u, 32u, 28u, 16u, 16u, 0, 6u, 3u},
        {0u, 9u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 15u, 0u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 4u, 0u, 1u, 8u, 8u, 6u, 6u, 1000, 6u, 2u},
        {16u, 5u, 0u, 0u, 0u, 0u, 6u, 16u, 0, 6u, 2u},
        {16u, 3u, 3u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 3u},
        {0u, 9u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 8u, 0u},
        {16u, 4u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 6u, 3u},
        {16u, 3u, 0u, 0u, 8u, 8u, 6u, 6u, 4, 6u, 0u},
        {0u, 6u, 1u, 0u, 12u, 12u, 8u, 8u, 3, 5u, 0u},
        {16u, 3u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 5u, 3u},
        {16u, 3u, 0u, 1u, 8u, 8u, 8u, 8u, 1, 5u, 3u},
        {16u, 4u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 15u, 0u},
        {0u, 8u, 0u, 1u, 8u, 8u, 3u, 3u, 1, 5u, 3u},
        {0u, 6u, 0u, 0u, 12u, 12u, 8u, 8u, 1000, 5u, 0u},
        {16u, 3u, 2u, 1u, 8u, 12u, 6u, 10u, 3, 6u, 0u},
        {67u, 5u, 3u, 1u, 16u, 12u, 10u, 8u, 10, 6u, 1u},
        {16u, 3u, 2u, 1u, 16u, 8u, 15u, 6u, 14, 6u, 1u},
        {16u, 3u, 4u, 1u, 8u, 8u, 7u, 7u, 40, 5u, 3u},
        {16u, 3u, 1u, 1u, 8u, 12u, 7u, 7u, 100, 6u, 3u},
        {67u, 5u, 4u, 1u, 12u, 12u, 9u, 9u, 96, 6u, 3u},
        {0u, 4u, 0u, 1u, 4u, 4u, 4u, 4u, 0, 6u, 1u},
        {67u, 6u, 1u, 1u, 8u, 8u, 5u, 5u, 5, 5u, 0u},
        {0u, 4u, 0u, 1u, 4u, 4u, 4u, 4u, 0, 6u, 1u},
        {16u, 3u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 5u, 3u},
        {67u, 4u, 0u, 1u, 16u, 16u, 10u, 10u, 100, 5u, 3u},
        {0u, 7u, 0u, 1u, 24u, 24u, 16u, 16u, 1000, 6u, 2u},
        {0u, 8u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 2u},
        {0u, 4u, 0u, 1u, 4u, 4u, 3u, 3u, 1000, 6u, 3u},
        {0u, 6u, 0u, 1u, 8u, 8u, 3u, 3u, 1000, 6u, 3u},
        {0u, 5u, 0u, 1u, 4u, 4u, 3u, 3u, 1000, 6u, 3u},
        {16u, 5u, 1u, 1u, 8u, 8u, 6u, 6u, 2, 6u, 0u},
        {0u, 8u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 2u},
        {0u, 8u, 0u, 1u, 8u, 8u, 5u, 5u, 1, 5u, 3u},
        {0u, 6u, 1u, 1u, 8u, 8u, 5u, 5u, 1000, 6u, 0u},
        {0u, 3u, 0u, 0u, 24u, 16u, 0u, 0u, 0, 6u, 0u},
        {0u, 2u, 0u, 0u, 8u, 4u, 0u, 0u, 0, 6u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {67u, 4u, 3u, 1u, 16u, 16u, 5u, 4u, 24, 6u, 2u},
        {10u, 4u, 0u, 1u, 0u, 0u, 5u, 7u, 0, 6u, 0u},
        {67u, 5u, 0u, 1u, 4u, 12u, 2u, 5u, 1, 6u, 3u},
        {0u, 2u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 4u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 4u, 2u, 1u, 8u, 12u, 7u, 7u, 1000, 6u, 0u},
        {0u, 3u, 0u, 1u, 8u, 12u, 5u, 5u, 1000, 6u, 0u},
        {0u, 2u, 0u, 1u, 8u, 12u, 5u, 5u, 1000, 6u, 0u},
        {16u, 3u, 0u, 1u, 8u, 8u, 8u, 8u, 14, 6u, 3u},
        {34u, 8u, 0u, 1u, 8u, 8u, 1u, 1u, 1, 7u, 6u},
        {16u, 3u, 4u, 1u, 8u, 8u, 7u, 7u, 40, 5u, 3u},
        {16u, 4u, 7u, 1u, 16u, 12u, 7u, 7u, 1000, 6u, 5u},
        {16u, 4u, 0u, 1u, 8u, 8u, 7u, 7u, 1000, 6u, 2u},
        {0u, 0u, 0u, 0u, 8u, 8u, 0u, 0u, 1, 7u, 0u},
        {34u, 8u, 0u, 1u, 8u, 8u, 3u, 3u, 8, 7u, 4u},
        {34u, 8u, 0u, 1u, 4u, 4u, 2u, 2u, 1000, 7u, 0u},
        {34u, 8u, 0u, 1u, 4u, 4u, 2u, 2u, 1000, 7u, 4u},
        {0u, 3u, 5u, 0u, 8u, 8u, 6u, 6u, 0, 14u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 5u, 7u, 1u, 24u, 24u, 16u, 16u, 1000, 6u, 2u},
        {0u, 4u, 4u, 1u, 8u, 8u, 4u, 4u, 1000, 6u, 1u},
        {0u, 6u, 0u, 1u, 8u, 8u, 5u, 5u, 1000, 6u, 2u},
        {2u, 7u, 0u, 1u, 4u, 20u, 0u, 4u, 0, 5u, 0u},
        {0u, 6u, 0u, 1u, 12u, 16u, 8u, 8u, 1000, 6u, 7u},
        {0u, 6u, 0u, 1u, 8u, 8u, 0u, 0u, 1000, 6u, 2u},
        {34u, 7u, 0u, 1u, 8u, 8u, 4u, 4u, 1000, 7u, 0u},
        {0u, 8u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 7u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0, 5u, 0u},
        {0u, 3u, 0u, 0u, 48u, 36u, 0u, 0u, 0, 6u, 0u},
        {0u, 6u, 0u, 0u, 8u, 8u, 0u, 0u, 0, 4u, 0u},
        {16u, 3u, 5u, 1u, 8u, 8u, 6u, 6u, 1000, 14u, 3u}};

//----- (00403440) --------------------------------------------------------
Object *CreateEntity(int type, int x, int y, int type2)
{
    int i;          // [esp+8h] [ebp-Ch]
    NpcAttr *eAttr; // [esp+Ch] [ebp-8h]
    Object *ePtr;   // [esp+10h] [ebp-4h]

    eAttr = &NpcAttrTbl[type];
    for (i = ((int)eAttr->unk << 8) / 10; i < 256 && (EntityTbl[i].cond & 1) != 0; ++i)
        ;

    if (i == 256)
        return NULL;

    ePtr = &EntityTbl[i];
    memset(ePtr, 0, sizeof(Object));
    ePtr->cond = 1;
    ePtr->flag = (int)eAttr->flag;
    ePtr->xoff = (int)eAttr->xoff << 10;
    ePtr->yoff = (int)eAttr->yoff << 10;
    ePtr->w = (int)eAttr->w << 10;
    ePtr->h = (int)eAttr->h << 10;
    ePtr->life = eAttr->life;
    ePtr->score = eAttr->score;
    ePtr->damage = eAttr->damage;
    ePtr->surf = eAttr->surf;
    ePtr->destroyHitVoice = eAttr->destroyHitVoice;
    ePtr->type = type;
    ePtr->type2 = type2;

    if ((ePtr->flag & 0x10) != 0)
        AddStageXOScroll(&x, &y);

    ePtr->x = x;
    ePtr->y = y;
    ePtr->num = EntityCreateCount++;

    return &EntityTbl[i];
}

//----- (004035F0) --------------------------------------------------------
void DamageNpChar(Object *o, int dmg)
{
    int y; // [esp+8h] [ebp-8h] BYREF
    int x; // [esp+Ch] [ebp-4h] BYREF

    if ((o->cond & 2) == 0)
    {
        x = o->x;
        y = o->y;
        if ((o->flag & 0x10) != 0)
            SubStageXOScroll(&x, &y);
        o->life -= dmg;
        if (o->shock < 8)
            o->shock += 8;
        if (o->life > 0)
        {
            switch (o->destroyHitVoice)
            {
            case 0:
                PlaySound(17);
                break;
            case 1:
                PlaySound(18);
                break;
            case 2:
                PlaySound(19);
                break;
            case 3:
                PlaySound(20);
                break;
            case 4:
                PlaySound(21);
                break;
            case 5:
                PlaySound(22);
                break;
            case 7:
                PlaySound(23);
                break;
            default:
                return;
            }
        }
        else
        {
            switch (o->destroyHitVoice)
            {
            case 0:
                PlaySound(11);
                break;
            case 1:
                PlaySound(12);
                break;
            case 2:
            case 5:
                PlaySound(13);
                break;
            case 3:
                PlaySound(14);
                break;
            case 4:
                PlaySound(15);
                break;
            case 6:
                PlaySound(16);
                break;
            default:
                break;
            }
            AddScore(o->score);
            if (o->destroyHitVoice == 6)
                CreateEntity(115, x, y, 0);
            else
                CreateEntity(1, x, y, 0);
            if (o->score)
                SetCaret(0, x, y, o->score);
            o->cond |= 2u;
        }
    }
}

//----- (00403840) --------------------------------------------------------
int CountNpCharType(int type)
{
    int i;  // [esp+0h] [ebp-8h]
    int v3; // [esp+4h] [ebp-4h]

    v3 = 0;
    for (i = 0; i < 256; ++i)
    {
        if ((EntityTbl[i].cond & 1) != 0 && EntityTbl[i].type == type)
            ++v3;
    }
    return v3;
}

//----- (004038A0) --------------------------------------------------------
void ClearReplaceNpChar(int a1, int a2)
{
    int i;  // [esp+0h] [ebp-Ch]
    int v3; // [esp+4h] [ebp-8h] BYREF
    int v4; // [esp+8h] [ebp-4h] BYREF

    for (i = 0; i < 256; ++i)
    {
        if ((EntityTbl[i].cond & 1) != 0 && EntityTbl[i].type == a1)
        {
            EntityTbl[i].cond = 0;
            if (a2)
            {
                v3 = EntityTbl[i].x;
                v4 = EntityTbl[i].y;
                if ((EntityTbl[i].flag & 0x10) != 0)
                    SubStageXOScroll(&v3, &v4);

                CreateEntity(1, v3, v4, 0);
            }
        }
    }
}

//----- (00418110) --------------------------------------------------------
void HitNpCharBullet()
{
    int j;       // [esp+0h] [ebp-24h]
    int b_y;     // [esp+4h] [ebp-20h] BYREF
    Bullet *bul; // [esp+8h] [ebp-1Ch]
    Object *npc; // [esp+Ch] [ebp-18h]
    int i;       // [esp+10h] [ebp-14h]
    int v5;      // [esp+14h] [ebp-10h]
    int b_x;     // [esp+18h] [ebp-Ch] BYREF
    int n_y;     // [esp+1Ch] [ebp-8h] BYREF
    int n_x;     // [esp+20h] [ebp-4h] BYREF

    bul = GetBulletTbl();
    for (i = 0; i < 32; ++i)
    {
        if ((bul->cond & 1) != 0 && (bul->flag & 4) != 0)
        {
            b_x = bul->x;
            b_y = bul->y;
            if ((bul->flag & 0x10) != 0)
                SubStageXOScroll(&b_x, &b_y);
            npc = GetNpcTable();
            for (j = 0; j < 256; ++j)
            {
                v5 = 0;
                if ((npc->cond & 1) != 0)
                {
                    if ((bul->cond & 4) != 0)
                    {
                        if (npc->type == 13 || npc->type == 14 || npc->type == 98)
                            v5 = 1;
                        if ((npc->flag & 8) != 0)
                            v5 = 1;
                        if ((npc->flag & 2) != 0 && (npc->flag & 1) != 0)
                            v5 = 1;
                    }
                    else if ((npc->flag & 9) != 0)
                    {
                        v5 = 1;
                    }
                }
                if (v5)
                {
                    n_x = npc->x;
                    n_y = npc->y;
                    if ((npc->flag & 0x10) != 0)
                        SubStageXOScroll(&n_x, &n_y);
                    if (b_x - bul->w < npc->w + n_x && bul->w + b_x > n_x - npc->w && b_y - bul->h < npc->h + n_y && bul->h + b_y > n_y - npc->h)
                    {
                        if ((npc->flag & 8) != 0)
                        {
                            if ((bul->flag & 8) != 0)
                            {
                                bul->cond |= 8u;
                            }
                            else
                            {
                                bul->cond |= 8u;
                                SetCaret(7, bul->x, bul->y, 0);
                                PlaySound(24);
                                if ((bul->cond & 4) == 0)
                                {
                                    bul->cond |= 2u;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            bul->cond |= 8u;
                            SetCaret(6, bul->x, bul->y, 0);
                            DamageNpChar(npc, bul->damage);
                            bul->life -= npc->damage;
                            if (bul->life <= 0)
                            {
                                bul->cond |= 2u;
                                break;
                            }
                        }
                    }
                }
                ++npc;
            }
        }
        ++bul;
    }
}

//----- (004183C0) --------------------------------------------------------
void HitShipPowerup()
{
    int i;        // [esp+0h] [ebp-1Ch]
    Ship *s;      // [esp+4h] [ebp-18h]
    int ship_y;   // [esp+8h] [ebp-14h] BYREF
    Object *e;    // [esp+Ch] [ebp-10h]
    int entity_y; // [esp+10h] [ebp-Ch] BYREF
    int ship_x;   // [esp+14h] [ebp-8h] BYREF
    int entity_x; // [esp+18h] [ebp-4h] BYREF

    s = GetShip();
    e = GetNpcTable();
    if ((s->cond & 1) != 0 && (s->flag & 4) != 0)
    {
        ship_x = s->x;
        ship_y = s->y;
        if ((s->flag & 0x10) != 0)
            SubStageXOScroll(&ship_x, &ship_y);
        for (i = 0; i < 256; ++i)
        {
            if ((e->cond & 1) != 0 && (e->flag & 2) != 0)
            {
                entity_x = e->x;
                entity_y = e->y;
                if ((e->flag & 0x10) != 0)
                    SubStageXOScroll(&entity_x, &entity_y);
                if (ship_x - s->w < e->w + entity_x && s->w + ship_x > entity_x - e->w && ship_y - s->h < e->h + entity_y && s->h + ship_y > entity_y - e->h && !ActPowerUp(e))
                {
                    break;
                }
            }
            ++e;
        }
    }
}

//----- (00418510) --------------------------------------------------------
void HitMapGeneric(Object *o, void (*func)(Object *, int, int, int), int a3)
{
    int v3[8];  // [esp+8h] [ebp-58h]
    int i;      // [esp+28h] [ebp-38h]
    int v5;     // [esp+2Ch] [ebp-34h]
    int v6;     // [esp+30h] [ebp-30h]
    int ow;     // [esp+34h] [ebp-2Ch]
    int v8;     // [esp+38h] [ebp-28h]
    int x;      // [esp+3Ch] [ebp-24h]
    int ox;     // [esp+40h] [ebp-20h] BYREF
    int attr_;  // [esp+44h] [ebp-1Ch]
    int oy;     // [esp+48h] [ebp-18h] BYREF
    int v13;    // [esp+4Ch] [ebp-14h]
    int y;      // [esp+50h] [ebp-10h]
    int flag;   // [esp+54h] [ebp-Ch]
    int oh;     // [esp+58h] [ebp-8h]
    int direct; // [esp+5Ch] [ebp-4h]

    direct = 0;
    flag = 0;
    ox = o->x;
    oy = o->y;
    ow = o->w;
    oh = o->h;
    if ((o->flag & 0x10) == 0)
        AddStageXOScroll(&ox, &oy);
    x = (ox + 0x2000) / 0x4000;
    y = (oy + 0x2000) / 0x4000;
    if ((GetTile(x - 1, y - 1) & 1) != 0)
        direct |= 1u;
    if ((GetTile(x, y - 1) & 1) != 0)
        direct |= 2u;
    if ((GetTile(x - 1, y) & 1) != 0)
        direct |= 4u;
    if ((GetTile(x, y) & 1) != 0)
        direct |= 8u;
    if (a3)
        direct = 128;
    switch (direct)
    {
    case 0:
        break;
    case 3:
        if (oy - oh < y << 14)
        {
            oy = oh + (y << 14);
            flag |= 0x40u;
        }
        break;
    case 5:
        if (ox - ow < x << 14)
        {
            ox = ow + (x << 14);
            flag |= 0x10u;
        }
        break;
    case 10:
        if (ow + ox > x << 14)
        {
            ox = (x << 14) - ow;
            flag |= 0x20u;
        }
        break;
    case 12:
        if (oh + oy > y << 14)
        {
            oy = (y << 14) - oh;
            flag |= 0x80u;
        }
        break;
    default:
        v3[0] = -1;
        v3[1] = -1;
        v3[2] = 1;
        v3[3] = 0;
        v3[4] = -1;
        v3[5] = 1;
        v3[6] = 1;
        v3[7] = 0;
        for (i = 0; i < 4; ++i)
        {
            x += v3[2 * i];
            y += v3[2 * i + 1];
            attr_ = GetTile(x, y);
            if ((attr_ & 1) != 0 && ow + ox > x << 14 && ox - ow <= (x << 14) + 0x4000 && oh + oy > y << 14 && oy - oh <= (y << 14) + 0x4000)
            {
                v13 = (x << 14) + 0x2000;
                v8 = (y << 14) + 0x2000;
                v5 = ox - v13;
                if (ox - v13 < 0)
                    v5 = -v5;
                v6 = oy - v8;
                if (oy - v8 < 0)
                    v6 = -v6;
                if (16 * v5 / (ow + 0x2000) <= 16 * v6 / (oh + 0x2000))
                {
                    if (oy >= v8)
                    {
                        oy = v8 + oh + 0x2000;
                        flag |= 0x40u;
                    }
                    else
                    {
                        oy = v8 - (oh + 0x2000);
                        flag |= 0x80u;
                    }
                }
                else if (ox >= v13)
                {
                    ox = v13 + ow + 0x2000;
                    flag |= 0x10u;
                }
                else
                {
                    ox = v13 - (ow + 0x2000);
                    flag |= 0x20u;
                }
                if ((attr_ & 2) != 0 && a3)
                {
                    ShiftTile(x, y);
                    CreateEntity(10, (16 * x + 8) << 10, (16 * y + 8) << 10, 0);
                    PlaySound(15);
                    goto end;
                }
            }
        }
        break;
    }
end:
    if (flag)
    {
        if ((o->flag & 0x10) == 0)
            SubStageXOScroll(&ox, &oy);
        func(o, ox, oy, flag);
    }
}