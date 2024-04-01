#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>
#include "../include/hUGEDriver.h"
#include "audio.h"
#include "cbtfx.h"
#include "collision.h"
#include "enemies.h"
#include "graphics.h"
#include "hero.h"
#include "input.h"
#include "level.h"
#include "vars.h"

/// @brief Update method for intro card. Runs down a timer and loads the main menu.
void updateIntro()
{
    if (--temp == 0)
    {
        // Turn off display to minimize artifacts.
        DISPLAY_OFF;
        delay(1000);

        // Set game state to main menu loop.
        gamestate = GAMESTATE_MAINMENU;

        // load Main Menu graphics
        initGfxMainMenu();
    }
}

/// @brief Animate window to slide up.
void updatePausing()
{
    HIDE_SPRITES;
    move_win(7, GAME_WINPAUSEDY + temp);

    if (--temp == 0)
    {
        muteAudio();
        gamestate = GAMESTATE_PAUSED;
    }
}

/// @brief Animate window to slide down.
void updateUnpausing()
{
    SHOW_SPRITES;
    move_win(7, GAME_WINPLAYINGY - temp);

    if (--temp == 0)
    {
        unmuteAudio();
        gamestate = GAMESTATE_PLAYING;
    }
}

/// @brief Update method for score card. Runs down a timer and loads the main menu.
void updateScore()
{
    if (--scoreTimer == 0)
    {
        // Turn off display to minimize artifacts.
        DISPLAY_OFF;
        disableAudio();
        delay(1000);
        
        // Set game state to main menu loop.
        gamestate = GAMESTATE_MAINMENU;

        // load Main Menu graphics
        initGfxMainMenu();
    }
}

/// @brief Main loop.
void main(void)
{
    // Init RNG function with DIV register
    initrand(DIV_REG);

    // Set game state to intro and show opening card.
    gamestate = GAMESTATE_INTRO;
    temp = GAME_INTROTIMER;
    initGfxIntro();

    // Loop forever
    while (1)
    {
        switch (gamestate)
        {
        case GAMESTATE_INTRO:
            updateIntro();
            break;
        case GAMESTATE_MAINMENU:
            handleInputsMenu();
            break;
        case GAMESTATE_PLAYING:
            // Game main loop processing goes here

            handleInputsPlaying();
            getCollisions();

            updateHero();
            drawHero();

            updateWeapon();
            updateEnemies();
            drawEnemies();

            break;
        case GAMESTATE_PAUSING:
            updatePausing();
            break;
        case GAMESTATE_UNPAUSING:
            updateUnpausing();
            break;
        case GAMESTATE_PAUSED:
            handleInputsPaused();
            break;
        case GAMESTATE_SCORE:
            updateScore();
            break;
        }

        // Done processing, yield CPU and wait for start of next frame. Advance RNG counter.
        wait_vbl_done();
        rand();
    }
}
