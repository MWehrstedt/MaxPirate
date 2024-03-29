#include <gb/gb.h>
#include "graphics.h"
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

        if (joypadCurrent & J_A && !(joypadPrevious & J_A) && weapon.type == WEAPON_TYPE_INACTIVE)
        {
            hero.state = HEROSTATE_ATTACK;
            weapon.direction = hero.lastDirection;
            weapon.type = WEAPON_TYPE_MELEE;
            weapon.timer = WEAPON_DEFAULTTIMER;
            hero.animationTimer = 0;
        }
        else if (joypadCurrent & J_B && !(joypadPrevious & J_B) && weapon.type == WEAPON_TYPE_INACTIVE)
        {
            if (hero.energy > 0)
            {
                --hero.energy;
                hero.animationTimer = 0;
                hero.state = HEROSTATE_ATTACK;

                weapon.x = hero.x + HITBOX_OFFSET_X;
                weapon.y = hero.y + HITBOX_OFFSET_Y;
                weapon.direction = hero.lastDirection;
                weapon.type = WEAPON_TYPE_SHOT;
                weapon.timer = WEAPON_SHOTTIMER;
                updateEnergyHUD();
            }
        }

        if (joypadCurrent & J_START && !(joypadPrevious & J_START))
        {
            gamestate = GAMESTATE_PAUSED;
        }

        break;
    }

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