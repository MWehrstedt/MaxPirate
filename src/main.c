#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>
#include "vars.h"
#include "graphics.h"
#include "input.h"
#include "level-dbg.h"
#include "hero.h"
#include "enemies.h"

void loadPalace()
{
    switch (currentPalaceId)
    {
    case 0:
        currentPalaceInit = &initBossDebug;
        break;
    }

    (*currentPalaceInit)();
}

void main(void)
{
    initrand(DIV_REG);
    gamestate = GAMESTATE_MAINMENU;
    currentPalaceId = 0;
    loadPalace();
    // Loop forever
    while (1)
    {
        switch (gamestate)
        {
        case GAMESTATE_MAINMENU:
            break;
        case GAMESTATE_PLAYING:
            // Game main loop processing goes here

            getInputsPlaying();
            //(*currentLevelUpdate)();

            checkCollisionBackground();
            checkCollisionObject();

            updateHero();
            drawHero();

            updateEnemies();
            drawEnemies();
            
            break;
        case GAMESTATE_PAUSED:
            getInputsPaused();
            break;
        case GAMESTATE_DIEING:
            //(*currentPalaceInit)();
            initBossDebug();
            break;
        }
        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
