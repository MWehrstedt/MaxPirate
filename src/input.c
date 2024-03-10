#include <gb/gb.h>
#include "vars.h"

void getInputsPlaying()
{
    joypadCurrent = joypad();
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
        }

        if (joypadCurrent & J_A && !(joypadPrevious & J_A))
        {
            hero.state = HEROSTATE_ATTACK;
            weapon.timer = WEAPON_DEFAULTTIMER;
        }

        if (joypadCurrent & J_START && !(joypadPrevious & J_START))
        {
            gamestate = GAMESTATE_PAUSED;
        }

        break;
    }

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

void getInputsPaused()
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        gamestate = GAMESTATE_PLAYING;
    }

    joypadPrevious = joypadCurrent;
}
