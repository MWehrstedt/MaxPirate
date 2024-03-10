#ifndef _LEVEL_DBG_H_
#define _LEVEL_DBG_H_
#include <gbdk/platform.h>
#include <stdint.h>
#include "../include/hitmapsPool.h"
#include "../res/generalTiles_Map.h"
#include "../res/generalTiles_Map2.h"
#include "../res/generalTiles_Map3.h"

static const uint8_t debugHitmap[3] = {
    0,
    1,
    1
};

static const unsigned char *mapList[3] = {
    generalTiles_Map,
    generalTiles_Map2,
    generalTiles_Map3
};

static const uint8_t warpsListLeft[3] = {
    1,
    2,
    0
};

static const uint8_t warpsListRight[3] = {
    2,
    0,
    1
};

static const uint8_t warpsListUp[3] = {
    1,
    2,
    0
};

static const uint8_t warpsListDown[3] = {
    2,
    0,
    1
};

void initBossDebug();

void updateDebug();

void loadRoomDebug();

void loadNextRoomDebug();

// void loadRoom();

#endif // _LEVEL_DBG_H_