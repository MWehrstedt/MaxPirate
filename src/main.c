#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>
#include "cbtfx.h"
#include "../res/25_monster_growl.h"
#include "../include/hUGEDriver.h"
#include "vars.h"
#include "graphics.h"
#include "input.h"
#include "level-dbg.h"
#include "hero.h"
#include "collision.h"
#include "enemies.h"

// void updateAudio()
// {
//     hUGE_dosound();
//     CBTFX_update();
// }

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

    // Enable audio output
    NR52_REG = 0x80;
    NR51_REG = 0xff;
    NR50_REG = 0x77;

    __critical
    {
        hUGE_init(&bg_song);
        //add_VBL(hUGE_dosound);
        add_VBL(CBTFX_update);
    }

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

            checkCollisions();
            // checkCollisionBackground();
            // checkCollisionObject();

            updateHero();
            drawHero();

            updateWeapon();
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
