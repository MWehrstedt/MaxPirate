#include <gb/gb.h>
#include "vars.h"
#include "graphics.h"
#include "enemies.h"
#include "level-dbg.h"
#include "../res/generalTiles.h"
#include "../res/heroTiles.h"
#include "../res/generalTiles_Map.h"

void initBossDebug()
{

    gamestate = GAMESTATE_PLAYING;
    hero.state = HEROSTATE_NORMAL;
    hero.lastDirection = HERO_FACING_UP;

    hero.x = 40;
    hero.y = 50;

    weapon.x = 200;
    weapon.y = 200;
    currentPalaceRoomId = 2;

    // currentLevelUpdate = &updateDebug;
    // currentPalaceLoadRoom = &loadRoomDebug;
    // currentPalaceLoadNextRoom = &loadNextRoomDebug;

    loadRoomDebug();
}

void updateDebug()
{
    if (!numberEnemies)
    {
        // replace gate tiles with opened ones
    }
}

void loadRoomDebug()
{
    currentLevelHitboxes = &hitmapPool[debugHitmap[currentPalaceRoomId]];
    initGfx(generalTiles, mapList[currentPalaceRoomId], heroTiles);

    // Spawn enemies
    initEnemies();
}

void loadNextRoomDebug()
{
    if (hero.x > 143)
    {
        hero.x = 6;
        currentPalaceRoomId = warpsListRight[currentPalaceRoomId];
    }
    else if (hero.x <= 1)
    {
        hero.x = 141;
        currentPalaceRoomId = warpsListLeft[currentPalaceRoomId];
    }

    if (hero.y > 127)
    {
        hero.y = 6;
        currentPalaceRoomId = warpsListDown[currentPalaceRoomId];
    }
    else if (hero.y <= 1)
    {
        hero.y = 125;
        currentPalaceRoomId = warpsListUp[currentPalaceRoomId];
    }

    loadRoomDebug();
}
