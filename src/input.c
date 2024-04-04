#include <gb/gb.h>
#include "../res/sfx.h"
#include "audio.h"
#include "cbtfx.h"
#include "graphics.h"
#include "level.h"
#include "vars.h"

/// @brief Handles inputs on main menu screen
void handleInputsMenu()
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        initAudio();
        initLevel();
        gamestate = GAMESTATE_PLAYING;
    }

    joypadPrevious = joypadCurrent;
}

/// @brief Handles inputs during main gameplay loop
void handleInputsPlaying()
{
    // Save current frame inputs
    joypadCurrent = joypad();

    // Reset hero movement
    hero.movement &= ~HERO_SPEED_RESETMASK;

    switch (hero.state)
    {
    case HEROSTATE_NORMAL:

        if (joypadCurrent & J_LEFT)
        {
            // clear hero speed right
            hero.movement &= ~HERO_SPEED_RIGHT;
            // clear hero facing right
            hero.movement &= ~HERO_FACING_RIGHT;

            // set hero speed
            hero.movement |= HERO_SPEED_LEFT;
            // set hero facing left
            hero.movement |= HERO_FACING_LEFT;

            hero.lastDirection = HERO_FACING_LEFT;
            hero.animationTimer = ++hero.animationTimer % HERO_ANIMATIONTIMERMAX;
        }
        else if (joypadCurrent & J_RIGHT)
        {
            // clear hero speed left
            hero.movement &= ~HERO_SPEED_LEFT;
            // clear hero facing left
            hero.movement &= ~HERO_FACING_LEFT;

            // set hero speed
            hero.movement |= HERO_SPEED_RIGHT;
            // set hero facing right
            hero.movement |= HERO_FACING_RIGHT;

            hero.lastDirection = HERO_FACING_RIGHT;
            hero.animationTimer = ++hero.animationTimer % HERO_ANIMATIONTIMERMAX;
        }

        if (joypadCurrent & J_UP)
        {
            // clear hero speed down
            hero.movement &= ~HERO_SPEED_DOWN;
            // clear hero facing down
            hero.movement &= ~HERO_FACING_DOWN;

            // set hero speed
            hero.movement |= HERO_SPEED_UP;
            // set hero facing up
            hero.movement |= HERO_FACING_UP;

            hero.lastDirection = HERO_FACING_UP;
            hero.animationTimer = ++hero.animationTimer % HERO_ANIMATIONTIMERMAX;
        }
        else if (joypadCurrent & J_DOWN)
        {
            // clear hero speed up
            hero.movement &= ~HERO_SPEED_UP;
            // clear hero facing up
            hero.movement &= ~HERO_FACING_UP;

            // set hero speed
            hero.movement |= HERO_SPEED_DOWN;
            // set hero facing down
            hero.movement |= HERO_FACING_DOWN;

            hero.lastDirection = HERO_FACING_DOWN;
            hero.animationTimer = ++hero.animationTimer % HERO_ANIMATIONTIMERMAX;
        }

        // Melee attack
        if (joypadCurrent & J_A && !(joypadPrevious & J_A) && weapon.type == WEAPON_TYPE_INACTIVE)
        {
            CBTFX_PLAY_SWING;
            hero.state = HEROSTATE_ATTACK;
            weapon.direction = hero.lastDirection;
            weapon.type = WEAPON_TYPE_MELEE;
            weapon.timer = WEAPON_DEFAULTTIMER;
            hero.animationTimer = 0;
        }

        // Shot attack
        else if (joypadCurrent & J_B && !(joypadPrevious & J_B) && weapon.type == WEAPON_TYPE_INACTIVE)
        {
            if (hero.energy > 0)
            {
                CBTFX_PLAY_BOOM;
                --hero.energy;
                hero.animationTimer = 0;
                hero.state = HEROSTATE_ATTACK;
                weapon.x = hero.x + HITBOX_OFFSET_X;
                weapon.y = hero.y + HITBOX_OFFSET_Y;
                weapon.direction = hero.lastDirection;
                weapon.type = WEAPON_TYPE_SHOT;
                weapon.timer = WEAPON_SHOTTIMER;
                updateEnergyHUDGfx();
            }
        }

        // Pause button
        if (joypadCurrent & J_START && !(joypadPrevious & J_START))
        {
            temp = GAME_WINPLAYINGY - GAME_WINPAUSEDY;
            gamestate = GAMESTATE_PAUSING;
        }

        // // Debug: kill yourself
        // if (joypadCurrent & J_SELECT && !(joypadPrevious & J_SELECT))
        // {
        //     hero.health = 0;
        // }

        break;
    }

    // Save current frame as old frames.
    joypadPrevious = joypadCurrent;
}

/// @brief Handles input during pause screen
void handleInputsPaused()
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        temp = GAME_WINPLAYINGY - GAME_WINPAUSEDY;
        gamestate = GAMESTATE_UNPAUSING;
    }

    joypadPrevious = joypadCurrent;
}


/// @brief Handles inputs on score screen
void handleInputsScore()
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        initAudio();
        initLevel();
        gamestate = GAMESTATE_MAINMENU;
    }

    joypadPrevious = joypadCurrent;
}