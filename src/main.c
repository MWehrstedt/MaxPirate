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

void updateMenu()
{
    ++temp;
    if (temp == 60)
        temp = 0;
    if (temp % 60 > 29)
    {
        set_bkg_tile_xy(4, 13, 88);
        set_bkg_tile_xy(5, 13, 89);
        set_bkg_tile_xy(6, 13, 90);
        set_bkg_tile_xy(7, 13, 91);
        set_bkg_tile_xy(8, 13, 91);

        set_bkg_tile_xy(12, 13, 91);
        set_bkg_tile_xy(13, 13, 92);
        set_bkg_tile_xy(14, 13, 93);
        set_bkg_tile_xy(15, 13, 89);
        set_bkg_tile_xy(16, 13, 92);
    }
    else
    {
        set_bkg_tile_xy(4, 13, 0);
        set_bkg_tile_xy(5, 13, 0);
        set_bkg_tile_xy(6, 13, 0);
        set_bkg_tile_xy(7, 13, 0);
        set_bkg_tile_xy(8, 13, 0);

        set_bkg_tile_xy(12, 13, 0);
        set_bkg_tile_xy(13, 13, 0);
        set_bkg_tile_xy(14, 13, 0);
        set_bkg_tile_xy(15, 13, 0);
        set_bkg_tile_xy(16, 13, 0);
    }
}

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

        // reset animation timer for main menu
        temp = 0;

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
    move_win(7, GAME_WINPLAYINGY - temp);

    if (--temp == 0)
    {
        SHOW_SPRITES;
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

        // reset animation timer for main menu
        temp = 0;

        // Set game state to main menu loop.
        gamestate = GAMESTATE_MAINMENU;

        // load Main Menu graphics
        initGfxMainMenu();
    }
}

/// @brief Hero is dieing loop
void updateDieing()
{
    if (--scoreTimer == 0)
    {
        DISPLAY_OFF;
        scoreTimer = GAME_SCORETIMER;
        gamestate = GAMESTATE_SCORE;
        hUGE_init(&bgm_gameover);
        initGfxScore();
    }
}

/// @brief Main loop.
void main(void)
{
    // Set game state to intro and show opening card.
    gamestate = GAMESTATE_INTRO;
    temp = GAME_INTROTIMER;
    initGfxIntro();

    // Init RNG function with DIV register
    initrand(DIV_REG);

    // Loop forever
    while (1)
    {
        switch (gamestate)
        {
        case GAMESTATE_INTRO:
            updateIntro();
            break;
        case GAMESTATE_MAINMENU:
            updateMenu();
            handleInputsMenu();
            break;
        case GAMESTATE_PLAYING:
            // Handle input first...
            handleInputsPlaying();

            // ... then handle knockback during hitstun ...
            handleHitstate();

            // ... then check for collisions ...
            getCollisions();

            // ... handle collisions and move hero ...
            updateHero();

            // ... and then draw hero
            drawHero();

            // Handle weapon logic
            updateWeapon();

            // Handle enemy logic...
            updateEnemies();

            // ... and then draw them
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
        case GAMESTATE_DIEING:
            updateDieing();
            break;
        }

        // Advance RNG counter. Done processing, yield CPU and wait for start of next frame.
        rand();
        wait_vbl_done();
    }
}
