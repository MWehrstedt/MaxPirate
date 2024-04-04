#include <gb/gb.h>
#include <stdint.h>
#include "../res/sfx.h"
#include "audio.h"
#include "cbtfx.h"
#include "collision.h"
#include "enemies.h"
#include "graphics.h"
#include "hero.h"
#include "level.h"
#include "vars.h"

/// @brief Draw and animate hero sprite
void drawHero()
{
    switch (hero.state)
    {
        // Default hero sprites
    case HEROSTATE_HIT:
    case HEROSTATE_NORMAL:
        switch (hero.lastDirection)
        {
        case HERO_FACING_LEFT:
            if ((hero.animationTimer % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
            {
                nextSpriteId[0] = 10;
                nextSpriteId[1] = 9;
                nextSpriteId[2] = 12;
                nextSpriteId[3] = 11;

                temp2 = S_FLIPX;
            }
            else
            {
                nextSpriteId[0] = 14;
                nextSpriteId[1] = 13;
                nextSpriteId[2] = 16;
                nextSpriteId[3] = 15;

                temp2 = S_FLIPX;
            }
            break;
        case HERO_FACING_RIGHT:
            if ((hero.animationTimer % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
            {
                nextSpriteId[0] = 9;
                nextSpriteId[1] = 10;
                nextSpriteId[2] = 11;
                nextSpriteId[3] = 12;

                temp2 = get_sprite_prop(0) & ~S_FLIPX;
            }
            else
            {
                nextSpriteId[0] = 13;
                nextSpriteId[1] = 14;
                nextSpriteId[2] = 15;
                nextSpriteId[3] = 16;

                temp2 = get_sprite_prop(0) & ~S_FLIPX;
            }
            break;
        case HERO_FACING_UP:
            if ((hero.animationTimer % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
            {
                nextSpriteId[0] = 5;
                nextSpriteId[1] = 6;
                nextSpriteId[2] = 7;
                nextSpriteId[3] = 8;

                temp2 = get_sprite_prop(0) & ~S_FLIPX;
            }
            else
            {
                nextSpriteId[0] = 6;
                nextSpriteId[1] = 5;
                nextSpriteId[2] = 8;
                nextSpriteId[3] = 7;

                temp2 = S_FLIPX;
            }
            break;
        case HERO_FACING_DOWN:
            if ((hero.animationTimer % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
            {
                nextSpriteId[0] = 1;
                nextSpriteId[1] = 2;
                nextSpriteId[2] = 3;
                nextSpriteId[3] = 4;

                temp2 = get_sprite_prop(0) & ~S_FLIPX;
            }
            else
            {
                nextSpriteId[0] = 2;
                nextSpriteId[1] = 1;
                nextSpriteId[2] = 4;
                nextSpriteId[3] = 3;

                temp2 = S_FLIPX;
            }
            break;
        }

        set_sprite_tile(0, nextSpriteId[0]);
        set_sprite_tile(1, nextSpriteId[1]);
        set_sprite_tile(2, nextSpriteId[2]);
        set_sprite_tile(3, nextSpriteId[3]);

        set_sprite_prop(0, temp2);
        set_sprite_prop(1, temp2);
        set_sprite_prop(2, temp2);
        set_sprite_prop(3, temp2);

        break;

        // // Hero attack sprites
    case HEROSTATE_ATTACK:
        switch (hero.lastDirection)
        {
        case HERO_FACING_LEFT:
            nextSpriteId[0] = 22;
            nextSpriteId[1] = 21;
            nextSpriteId[2] = 24;
            nextSpriteId[3] = 23;

            temp2 = S_FLIPX;
            break;
        case HERO_FACING_RIGHT:
            nextSpriteId[0] = 21;
            nextSpriteId[1] = 22;
            nextSpriteId[2] = 23;
            nextSpriteId[3] = 24;

            temp2 = get_sprite_prop(0) & ~S_FLIPX;
            break;
        case HERO_FACING_UP:
            nextSpriteId[0] = 5;
            nextSpriteId[1] = 6;
            nextSpriteId[2] = 27;
            nextSpriteId[3] = 28;

            temp2 = get_sprite_prop(0) & ~S_FLIPX;
            break;
        case HERO_FACING_DOWN:
            nextSpriteId[0] = 1;
            nextSpriteId[1] = 2;
            nextSpriteId[2] = 25;
            nextSpriteId[3] = 26;

            temp2 = get_sprite_prop(0) & ~S_FLIPX;
            break;
        }

        set_sprite_tile(0, nextSpriteId[0]);
        set_sprite_tile(1, nextSpriteId[1]);
        set_sprite_tile(2, nextSpriteId[2]);
        set_sprite_tile(3, nextSpriteId[3]);

        set_sprite_prop(0, temp2);
        set_sprite_prop(1, temp2);
        set_sprite_prop(2, temp2);
        set_sprite_prop(3, temp2);
    }

    // Flashing effect if hero is during iframes. Cheaply done by moving them off screen for a couple of frames.
    if (hero.isInvulnerable && DIV_REG % 4 > 1)
    {
        move_sprite(0, hero.x + 8, 200);
        move_sprite(1, hero.x + 16, 200);
        move_sprite(2, hero.x + 8, 200);
        move_sprite(3, hero.x + 16, 200);
    }
    else
    {
        move_sprite(0, hero.x + 8, hero.y + 16);
        move_sprite(1, hero.x + 16, hero.y + 16);
        move_sprite(2, hero.x + 8, hero.y + 24);
        move_sprite(3, hero.x + 16, hero.y + 24);
    }

    // Move sprites
    move_sprite(4, weapon.x + 8, weapon.y + 16);
}

/// @brief Main hero routine
void updateHero()
{
    // Check if hero has died
    if (hero.health == 0 && hero.state != HEROSTATE_DIEING)
    {
        // Mute BGM and enable sound channels afterwards again.
        // Quick fix to flush sound registers
        muteAudio();

        NR52_REG = 0x80;
        NR51_REG = 0xFF;
        NR50_REG = 0x54;

        for (iterator = 0; iterator < ENEMY_MAXNUMBER; ++iterator)
        {
            // Move enemy off-screen
            enemiesX[iterator] = 200;
            enemiesY[iterator] = 200;
        }

        CBTFX_PLAY_DIE;
        gamestate = GAMESTATE_DIEING;
        scoreTimer = HERO_DIEINGTIMER;
        return;
    }

    // Move hero if possible, i.e. the corresponding speed flags are still set.
    if (hero.movement & HERO_SPEED_LEFT)
    {
        hero.x -= HERO_SPEED;
    }
    else if (hero.movement & HERO_SPEED_RIGHT)
    {
        hero.x += HERO_SPEED;
    }

    if (hero.movement & HERO_SPEED_UP)
    {
        hero.y -= HERO_SPEED;
    }
    else if (hero.movement & HERO_SPEED_DOWN)
    {
        hero.y += HERO_SPEED;
    }

    // Remove invulnerable flag if timer runs out
    if (hero.isInvulnerable && --hero.hitTimer == 0)
    {
        hero.isInvulnerable = 0;
        hero.state = HEROSTATE_NORMAL;
    };

    // Dirty bug fix for northern warp
    if (hero.state != HEROSTATE_NORMAL && hero.y <= 2)
    {
        hero.y = 3;
    }

    // Check for warp collisions
    if (!numberEnemies && (hero.x <= 1 || hero.x > 143 || hero.y <= 2 || hero.y > 111))
    {
        loadNextLevel();
    }
}

/// @brief Handle knockback during hitstate
void handleHitstate()
{
    if (hero.state == HEROSTATE_HIT)
    {
        // Remove weapon from screen if hit during attack
        if (weapon.type == WEAPON_TYPE_MELEE)
        {
            weapon.type = WEAPON_TYPE_INACTIVE;
            weapon.timer = 0;
        }

        // Count down hit timer and remove flag if run out.
        if (--hero.hitTimer == 0)
        {
            SHOW_SPRITES;
            hero.hitTimer = HERO_INVULNTIMER;
            hero.state = HEROSTATE_NORMAL;
            hero.isInvulnerable = 1;
        }

        // Knockback during the first few frames
        else if (hero.hitTimer > HERO_DEFAULTTIMER - 12)
        {
            switch (hero.lastDirection)
            {
            case HERO_FACING_RIGHT:
                // set hero speed
                hero.movement |= HERO_SPEED_LEFT;
                hero.movement &= ~HERO_SPEED_RIGHT;
                break;
            case HERO_FACING_LEFT:
                hero.movement |= HERO_SPEED_RIGHT;
                hero.movement &= ~HERO_SPEED_LEFT;
                break;
            case HERO_FACING_DOWN:
                hero.movement |= HERO_SPEED_UP;
                hero.movement &= ~HERO_SPEED_DOWN;
                break;
            case HERO_FACING_UP:
                hero.movement |= HERO_SPEED_DOWN;
                hero.movement &= ~HERO_SPEED_UP;
                break;
            };
        }
    }
}

/// @brief Main weapon routine
void updateWeapon()
{
    // Disable weapon if timer runs out
    if (--weapon.timer == 0)
    {
        weapon.type = WEAPON_TYPE_INACTIVE;
        if (hero.state == HEROSTATE_ATTACK)
            hero.state = HEROSTATE_NORMAL;
    }

    switch (weapon.type)
    {
    case WEAPON_TYPE_INACTIVE:
        weapon.x = 170;
        weapon.y = 170;
        break;
    case WEAPON_TYPE_MELEE:
        switch (weapon.direction)
        {
        case HERO_FACING_LEFT:
            weapon.x = hero.x - 4;
            weapon.y = hero.y + 6;

            set_sprite_tile(4, WEAPON_MELEE_SPRITE_ID);
            set_sprite_prop(4, S_FLIPX);
            break;
        case HERO_FACING_RIGHT:
            weapon.x = hero.x + 12;
            weapon.y = hero.y + 6;
            set_sprite_tile(4, WEAPON_MELEE_SPRITE_ID);
            set_sprite_prop(4, get_sprite_prop(4) & ~S_FLIPX);
            break;
        case HERO_FACING_UP:
            weapon.x = hero.x + 4;
            weapon.y = hero.y - 6;
            set_sprite_tile(4, WEAPON_MELEE_SPRITE_ID + 1);
            set_sprite_prop(4, get_sprite_prop(4) & ~S_FLIPY);
            break;
        case HERO_FACING_DOWN:
            weapon.x = hero.x + 4;
            weapon.y = hero.y + 16;
            set_sprite_tile(4, WEAPON_MELEE_SPRITE_ID + 1);
            set_sprite_prop(4, S_FLIPY);

            break;
        }
        break;
    case WEAPON_TYPE_SHOT:
        switch (weapon.direction)
        {
        case HERO_FACING_LEFT:
            weapon.x -= WEAPON_SHOTSPEED;
            set_sprite_tile(4, WEAPON_SHOT_SPRITE_ID);
            set_sprite_prop(4, S_FLIPX);
            break;
        case HERO_FACING_RIGHT:
            weapon.x += WEAPON_SHOTSPEED;
            set_sprite_tile(4, WEAPON_SHOT_SPRITE_ID);
            set_sprite_prop(4, get_sprite_prop(4) & ~S_FLIPX);
            break;
        case HERO_FACING_UP:
            weapon.y -= WEAPON_SHOTSPEED;
            set_sprite_tile(4, WEAPON_SHOT_SPRITE_ID + 1);
            set_sprite_prop(4, get_sprite_prop(4) & ~S_FLIPY);
            break;
        case HERO_FACING_DOWN:
            weapon.y += WEAPON_SHOTSPEED;
            set_sprite_tile(4, WEAPON_SHOT_SPRITE_ID + 1);
            set_sprite_prop(4, S_FLIPY);
            break;
        }
        break;
    }

    // For the projectile weapon, set player state to normal after a few frames, so the hero doesn't need to wait for the whole shot to finish
    if (weapon.timer == (WEAPON_SHOTTIMER - WEAPON_DEFAULTTIMER) && hero.state == HEROSTATE_ATTACK)
    {
        hero.state = HEROSTATE_NORMAL;
    }
}
