#include <gb/gb.h>
#include <rand.h>
#include <stdint.h>
#include <string.h>
#include "../include/hUGEDriver.h"
#include "../res/sfx.h"
#include "cbtfx.h"
#include "collision.h"
#include "enemies.h"
#include "graphics.h"
#include "hero.h"
#include "vars.h"

/// @brief Spawn enemy in the next available slot.
void spawnEnemy()
{
    // Find empty enemyslot to spawn enemy
    if (numberEnemiesTotal)
    {
        for (iterator2 = 0; iterator2 < ENEMY_MAXNUMBER; ++iterator2)
        {
            if (!(enemiesStatus[iterator2] & ENEMYSTATE_ACTIVE))
            {
                // enemiesType[iterator2] = ENEMYTYPE_ZOMBIE;
                enemiesType[iterator2] = (DIV_REG % 2) + 1;

                enemiesStatus[iterator2] = ENEMYSTATE_SPAWNING | ENEMYSTATE_ACTIVE | ENEMYSTATE_DIRECTIONISRIGHT;
                enemiesHealth[iterator2] = 2;

                do
                {
                    enemiesX[iterator2] = (uint8_t)rand() % 100 + 20;
                    enemiesY[iterator2] = (uint8_t)rand() % 100 + 4;
                    checkCollisionBackground(HERO_SPEED_LEFT, enemiesX[iterator2], enemiesY[iterator2], 0);
                } while ((*currentLevelHitboxes)[targetTileLeft.center] != 0);

                enemiesTimers[iterator2] = ENEMY_INVULNTIMER;

                set_sprite_tile(5 + (4 * iterator2), enemiesSpriteId[enemiesType[iterator2]]);
                set_sprite_tile(6 + (4 * iterator2), enemiesSpriteId[enemiesType[iterator2]] + 2);
                set_sprite_tile(7 + (4 * iterator2), enemiesSpriteId[enemiesType[iterator2]] + 1);
                set_sprite_tile(8 + (4 * iterator2), enemiesSpriteId[enemiesType[iterator2]] + 3);
                --numberEnemiesTotal;
                return;
            }
        }
    }
}

/// @brief Initializes and spawns enemies
/// @param parNumberEnemies Number of enemies to spawn
void initEnemies(uint8_t parNumberEnemies)
{
    // Clear enemy pool
    for (iterator = 0; iterator < ENEMY_MAXNUMBER; ++iterator)
    {
        enemiesStatus[iterator] = ENEMYSTATE_CLEAR;
        enemiesHealth[iterator] = ENEMY_DEFAULTHEALTH;
        enemiesTimers[iterator] = ENEMY_DEFAULTTIMER;
        enemiesMovement[iterator] = (uint8_t)rand() % 4;
        switch (enemiesMovement[iterator])
        {
        case 0:
            enemiesMovement[iterator] = HERO_FACING_LEFT | HERO_SPEED_LEFT;
            break;
        case 1:
            enemiesMovement[iterator] = HERO_FACING_RIGHT | HERO_SPEED_RIGHT;
            break;
        case 2:
            enemiesMovement[iterator] = HERO_FACING_UP | HERO_SPEED_UP;
            break;
        case 3:
            enemiesMovement[iterator] = HERO_FACING_DOWN | HERO_SPEED_DOWN;
            break;
        }

        // Move enemy off-screen
        enemiesX[iterator] = 200;
        enemiesY[iterator] = 200;
    }

    // Set global enemy counters for the current room
    numberEnemies = parNumberEnemies;
    numberEnemiesTotal = parNumberEnemies;

    // Spawn enemies on screen
    spawnEnemy();
    spawnEnemy();
    spawnEnemy();
}

/// @brief Draw and animate active enemies
void drawEnemies()
{
    // Iterate over enemy slots
    for (iterator = 0; iterator < ENEMY_MAXNUMBER; ++iterator)
    {
        // Get current OAM id
        temp = ENEMY_OAM_ID_OFFSET + (4 * iterator);

        // Spawning cloud
        if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE && enemiesStatus[iterator] & ENEMYSTATE_SPAWNING)
        {
            set_sprite_tile(temp, 78);
            set_sprite_tile(temp + 1, 78);
            set_sprite_tile(temp + 2, 78);
            set_sprite_tile(temp + 3, 78);

            set_sprite_prop(temp, get_sprite_prop(temp) & ~(S_FLIPX | S_FLIPY));
            set_sprite_prop(temp + 1, (get_sprite_prop(temp + 1) & ~S_FLIPY) | S_FLIPX);
            set_sprite_prop(temp + 2, (get_sprite_prop(temp + 1) & ~S_FLIPX) | S_FLIPY);
            set_sprite_prop(temp + 3, S_FLIPX | S_FLIPY);
        }

        // Destroyed cloud
        else if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE && enemiesStatus[iterator] & ENEMYSTATE_DIE)
        {
            if (enemiesTimers[iterator] < (ENEMY_DEFAULTTIMER / 2))
            {
                set_sprite_tile(temp, 79);
                set_sprite_tile(temp + 1, 79);
                set_sprite_tile(temp + 2, 79);
                set_sprite_tile(temp + 3, 79);
            }
            else
            {
                set_sprite_tile(temp, 80);
                set_sprite_tile(temp + 1, 80);
                set_sprite_tile(temp + 2, 80);
                set_sprite_tile(temp + 3, 80);
            }

            set_sprite_prop(temp, get_sprite_prop(temp) & ~(S_FLIPX | S_FLIPY));
            set_sprite_prop(temp + 1, (get_sprite_prop(temp + 1) & ~S_FLIPY) | S_FLIPX);
            set_sprite_prop(temp + 2, (get_sprite_prop(temp + 1) & ~S_FLIPX) | S_FLIPY);
            set_sprite_prop(temp + 3, S_FLIPX | S_FLIPY);
        }

        // Normal animations
        else if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE)
        {
            if (enemiesMovement[iterator] & HERO_SPEED_DOWN)
            {
                if ((enemiesAnimationTimers[iterator] % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]];
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 2;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 1;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 3;

                    temp2 = get_sprite_prop(temp) & ~S_FLIPX;
                }
                else
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 2;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]];
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 3;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 1;

                    temp2 = S_FLIPX;
                }
            }
            else if (enemiesMovement[iterator] & HERO_SPEED_UP)
            {
                if ((enemiesAnimationTimers[iterator] % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 4;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 6;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 5;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 7;

                    temp2 = get_sprite_prop(temp) & ~S_FLIPX;
                }
                else
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 6;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 4;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 7;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 5;

                    temp2 = S_FLIPX;
                }
            }
            else if (enemiesMovement[iterator] & HERO_SPEED_RIGHT)
            {
                if ((enemiesAnimationTimers[iterator] % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 8;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 10;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 9;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 11;

                    temp2 = get_sprite_prop(temp) & ~S_FLIPX;
                }
                else
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 12;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 14;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 13;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 15;

                    temp2 = get_sprite_prop(temp) & ~S_FLIPX;
                }
            }
            else if (enemiesMovement[iterator] & HERO_SPEED_LEFT)
            {
                if ((enemiesAnimationTimers[iterator] % HERO_ANIMATIONTIMERMAX) > HERO_ANIMATIONTIMER)
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 10;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 8;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 11;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 9;

                    temp2 = S_FLIPX;
                }
                else
                {
                    nextSpriteId[0] = enemiesSpriteId[enemiesType[iterator]] + 14;
                    nextSpriteId[1] = enemiesSpriteId[enemiesType[iterator]] + 12;
                    nextSpriteId[2] = enemiesSpriteId[enemiesType[iterator]] + 15;
                    nextSpriteId[3] = enemiesSpriteId[enemiesType[iterator]] + 13;

                    temp2 = S_FLIPX;
                }
            }

            set_sprite_tile(temp, nextSpriteId[0]);
            set_sprite_tile(temp + 1, nextSpriteId[1]);
            set_sprite_tile(temp + 2, nextSpriteId[2]);
            set_sprite_tile(temp + 3, nextSpriteId[3]);

            set_sprite_prop(temp, temp2);
            set_sprite_prop(temp + 1, temp2);
            set_sprite_prop(temp + 2, temp2);
            set_sprite_prop(temp + 3, temp2);
        }

        if (enemiesStatus[iterator] & ENEMYSTATE_HIT && DIV_REG % 4 > 1)
        {
            move_sprite(temp, enemiesX[iterator] + 8, 200);
            move_sprite(temp + 1, enemiesX[iterator] + 16, 200);
            move_sprite(temp + 2, enemiesX[iterator] + 8, 200);
            move_sprite(temp + 3, enemiesX[iterator] + 16, 200);
        }
        else
        {
            move_sprite(temp, enemiesX[iterator] + 8, enemiesY[iterator] + 16);
            move_sprite(temp + 1, enemiesX[iterator] + 16, enemiesY[iterator] + 16);
            move_sprite(temp + 2, enemiesX[iterator] + 8, enemiesY[iterator] + 24);
            move_sprite(temp + 3, enemiesX[iterator] + 16, enemiesY[iterator] + 24);
        }
    }
}

/// @brief Update method. Handles main enemy behaviour.
void updateEnemies()
{
    // Iterate over enemy slots
    for (iterator = 0; iterator < ENEMY_MAXNUMBER; ++iterator)
    {
        // Spawn timer. If timer has run out, remove spawning flag.
        if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE && enemiesStatus[iterator] & ENEMYSTATE_SPAWNING)
        {
            if (--enemiesTimers[iterator] == 0)
            {
                enemiesStatus[iterator] &= ~ENEMYSTATE_SPAWNING;
                enemiesTimers[iterator] = ENEMY_DEFAULTTIMER;
            }
            continue;
        }

        // Destroy timer
        // If timer has run out, move enemy off screen. When all enemies are defeated, open room doors.
        // There is a 1 percent chance to refill energy on a kill.
        // Finally remove active and dieing flag and spawn a new enemy.
        else if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE && enemiesStatus[iterator] & ENEMYSTATE_DIE)
        {
            if (--enemiesTimers[iterator] == 0)
            {
                enemiesX[iterator] = 200;
                enemiesY[iterator] = 200;

                if (--numberEnemies == 0)
                {
                    CBTFX_PLAY_OPENDOOR;
                    openDoorsGfx();
                }

                if (++killedEnemies % 100 == 1)
                {
                    CBTFX_PLAY_POWERUP;
                    hero.energy += (hero.energy + 1 > 5 ? 0 : 1);
                    updateEnergyHUDGfx();
                }

                enemiesStatus[iterator] &= ~ENEMYSTATE_ACTIVE;
                enemiesStatus[iterator] &= ~ENEMYSTATE_DIE;
                spawnEnemy();
                updateEnemyHUDGfx();
            }
            continue;
        }
        // Normal logic
        else if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE)
        {
            // Check collision with hero
            if (!(enemiesStatus[iterator] & ENEMYSTATE_HIT) && hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT &&
                ((hero.x + HITBOX_OFFSET_X) < (enemiesX[iterator] + 10) && (hero.x + 16 - HITBOX_OFFSET_X) > (enemiesX[iterator] + 2) && (hero.y + HITBOX_OFFSET_Y) < (enemiesY[iterator] + 10) && (hero.y + 16 - HITBOX_OFFSET_Y) > (enemiesY[iterator] - 2)))
            {
                CBTFX_PLAY_GOTHIT;
                set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health--);
                hero.hitTimer = HERO_DEFAULTTIMER;
                hero.state = HEROSTATE_HIT;
            }

            // Check collision with weapon. If enemy is in hit state, ignore damage.
            // Set die flag if health drops to 0 and below
            if (!(enemiesStatus[iterator] & ENEMYSTATE_HIT) &&
                (weapon.x - WEAPON_HITBOX_OFFSET_X) < (enemiesX[iterator] + 16) &&
                (weapon.x + 8 + WEAPON_HITBOX_OFFSET_X) > (enemiesX[iterator]) &&
                (weapon.y - WEAPON_HITBOX_OFFSET_Y) < (enemiesY[iterator] + 16) &&
                (weapon.y + 8 + WEAPON_HITBOX_OFFSET_Y) > (enemiesY[iterator]))
            {
                enemiesHealth[iterator] -= weapon.type;
                if (enemiesHealth[iterator] <= 0)
                {
                    enemiesTimers[iterator] = ENEMY_DEFAULTTIMER;
                    enemiesStatus[iterator] |= ENEMYSTATE_DIE;

                    CBTFX_PLAY_ENEMYDESTROY;
                    break;
                }

                enemiesStatus[iterator] |= ENEMYSTATE_HIT;
                enemiesHitTimers[iterator] = HERO_INVULNTIMER;
                CBTFX_PLAY_GROWL;
                break;
            }

            // Remove hit flag if timer runs out
            if (--enemiesHitTimers[iterator] == 0)
            {
                enemiesStatus[iterator] &= ~ENEMYSTATE_HIT;
            }

            // Move enemy around
            if (!(enemiesStatus[iterator] & ENEMYSTATE_HIT && enemiesHitTimers[iterator] > (ENEMY_INVULNTIMER / 2)))
            {
                // Check background collision
                checkCollisionBackground(enemiesMovement[iterator], enemiesX[iterator], enemiesY[iterator], ENEMY_SPEED);

                // Check movement left
                if (enemiesMovement[iterator] & HERO_SPEED_LEFT)
                {
                    if ((*currentLevelHitboxes)[targetTileLeft.center] != 1 && (*currentLevelHitboxes)[targetTileLeft.center] != 2)
                    {
                        // move enemy to the left
                        enemiesX[iterator] -= ENEMY_SPEED;
                    }
                }
                // Check movement right
                else if (enemiesMovement[iterator] & HERO_SPEED_RIGHT)
                {
                    if ((*currentLevelHitboxes)[targetTileRight.center] != 1 && (*currentLevelHitboxes)[targetTileRight.center] != 2)
                    {
                        // move enemy to the right
                        enemiesX[iterator] += ENEMY_SPEED;
                    }
                }

                // Check movement up
                if (enemiesMovement[iterator] & HERO_SPEED_UP)
                {
                    if ((*currentLevelHitboxes)[targetTileUp.center] != 1 && (*currentLevelHitboxes)[targetTileUp.center] != 2)
                    {
                        // move enemy up
                        enemiesY[iterator] -= ENEMY_SPEED;
                    }
                }
                // Check movement down
                else if (enemiesMovement[iterator] & HERO_SPEED_DOWN)
                {
                    if ((*currentLevelHitboxes)[targetTileDown.center] != 1 && (*currentLevelHitboxes)[targetTileDown.center] != 2)
                    {
                        // move enemy down
                        enemiesY[iterator] += ENEMY_SPEED;
                    }
                }

                ++enemiesAnimationTimers[iterator];

                // Change direction if timer has run out
                if (--enemiesTimers[iterator] == 0)
                {
                    // Reset flags
                    enemiesAnimationTimers[iterator] = 0;
                    enemiesNextDirection[0] = 0;
                    enemiesNextDirection[1] = 0;
                    enemiesTimers[iterator] = ENEMY_DEFAULTTIMER;

                    // Check hero position. New direction is randomly selected from x and y position relative to it.
                    if (enemiesX[iterator] > hero.x)
                    {
                        enemiesNextDirection[0] |= HERO_FACING_LEFT | HERO_SPEED_LEFT;
                    }
                    else
                    {
                        enemiesNextDirection[0] |= HERO_FACING_RIGHT | HERO_SPEED_RIGHT;
                    }

                    if (enemiesY[iterator] > hero.y)
                    {
                        enemiesNextDirection[1] |= HERO_FACING_UP | HERO_SPEED_UP;
                    }
                    else
                    {
                        enemiesNextDirection[1] |= HERO_FACING_DOWN | HERO_SPEED_DOWN;
                    }

                    // Select new direction at random
                    enemiesMovement[iterator] = enemiesNextDirection[DIV_REG % 2];
                }
            }
        }
    }
}