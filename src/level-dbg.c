#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include "vars.h"
#include "graphics.h"
#include "level-dbg.h"
#include "../res/generalTiles.h"
#include "../res/heroTiles.h"
#include "../res/generalTiles_Map.h"

#pragma bank 255

BANKREF_EXTERN(initBossDebug)
void initBossDebug()
{

    gamestate = GAMESTATE_PLAYING;

    heroPositionX = 40;
    heroPositionY = 50;
    currentPalaceRoomId = 2;

    // Init enemies to update
    // memcpy(&currentLevelHitboxes, &debugHitmap, 90);

    currentLevelUpdate = &updateDebug;
    currentPalaceLoadRoom = &loadRoomDebug;
    currentPalaceLoadNextRoom = &loadNextRoomDebug;

    loadRoomDebug();
}

BANKREF_EXTERN(updateDebug)
void updateDebug()
{
}

BANKREF_EXTERN(loadRoomDebug)
void loadRoomDebug()
{
    currentLevelHitboxes = &hitmapPool[debugHitmap[currentPalaceRoomId]];
    initGfx(generalTiles, mapList[currentPalaceRoomId], heroTiles);
}

BANKREF_EXTERN(loadNextRoomDebug)
void loadNextRoomDebug()
{
    if (heroPositionX > 143)
    {
        heroPositionX = 4;
        currentPalaceRoomId = warpsListRight[currentPalaceRoomId];
    } else if (heroPositionX <= 1) {
        heroPositionX = 143;
        currentPalaceRoomId = warpsListLeft[currentPalaceRoomId];
    }

    if (heroPositionY > 127)
    {
        heroPositionY = 4;
        currentPalaceRoomId = warpsListDown[currentPalaceRoomId];
    } else if (heroPositionY <= 1) {
        heroPositionY = 127;
        currentPalaceRoomId = warpsListUp[currentPalaceRoomId];
    }

    loadRoomDebug();
}
