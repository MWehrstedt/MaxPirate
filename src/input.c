#include <gbdk/platform.h>
#include <gb/gb.h>
#include "vars.h"

#pragma bank 255

BANKREF_EXTERN(getInputsPlaying)
void getInputsPlaying() NONBANKED
{
    joypadCurrent = joypad();
    heroMovement &= ~HERO_SPEED_RESETMASK;

    if (joypadCurrent & J_LEFT)
    {
        // clear hero speed right
        heroMovement &= ~HERO_SPEED_RIGHT;
        // clear hero facing right
        heroMovement &= ~HERO_FACING_RIGHT;

        // set hero speed
        heroMovement |= HERO_SPEED_LEFT;
        // set hero facing left
        heroMovement |= HERO_FACING_LEFT;
    }
    else if (joypadCurrent & J_RIGHT)
    {
        // clear hero speed left
        heroMovement &= ~HERO_SPEED_LEFT;
        // clear hero facing left
        heroMovement &= ~HERO_FACING_LEFT;

        // set hero speed
        heroMovement |= HERO_SPEED_RIGHT;
        // set hero facing right
        heroMovement |= HERO_FACING_RIGHT;
    }

    if (joypadCurrent & J_UP)
    {
        // clear hero speed down
        heroMovement &= ~HERO_SPEED_DOWN;
        // clear hero facing down
        heroMovement &= ~HERO_FACING_DOWN;

        // set hero speed
        heroMovement |= HERO_SPEED_UP;
        // set hero facing up
        heroMovement |= HERO_FACING_UP;
    }
    else if (joypadCurrent & J_DOWN)
    {
        // clear hero speed up
        heroMovement &= ~HERO_SPEED_UP;
        // clear hero facing up
        heroMovement &= ~HERO_FACING_UP;

        // set hero speed
        heroMovement |= HERO_SPEED_DOWN;
        // set hero facing down
        heroMovement |= HERO_FACING_DOWN;
    }

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        gamestate = GAMESTATE_PAUSED;
    }

    // if (joypadCurrent & J_A && !(joypadPrevious & J_A))
    // {
    //     currentPalaceRoomId = *currentLevelWarpsRight[0];
    //     (*currentLevelLoadRoom)();
    // }

    // if (joypadCurrent & J_B && !(joypadPrevious & J_B))
    // {
    //     currentPalaceRoomId = *currentLevelWarpsRight[1];
    //     (*currentLevelLoadRoom)();
    // }

    // if (joypadCurrent & J_SELECT && !(joypadPrevious & J_SELECT))
    // {
    //     currentPalaceRoomId = *currentLevelWarpsRight[2];
    //     (*currentLevelLoadRoom)();
    // }

    joypadPrevious = joypadCurrent;
}

BANKREF_EXTERN(getInputsPaused)
void getInputsPaused() NONBANKED
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        gamestate = GAMESTATE_PLAYING;
    }

    joypadPrevious = joypadCurrent;
}
