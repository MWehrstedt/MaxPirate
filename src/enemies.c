#include <gb/gb.h>
#include <stdint.h>
#include <string.h>
#include <rand.h>
#include "hero.h"
#include "vars.h"

void initEnemies()
{

    for (iterator = 0; iterator < 4; ++iterator)
    {
        enemiesStatus[iterator] = ENEMYSTATE_CLEAR;
        enemiesHealth[iterator] = 255;
        enemiesX[iterator] = 200;
        enemiesY[iterator] = 200;
    }

    numberEnemies = (uint8_t)rand() % 4 + 1;

    for (iterator = 0; iterator < numberEnemies; ++iterator)
    {
        enemiesStatus[iterator] = ENEMYSTATE_ACTIVE | ENEMYSTATE_DIRECTIONISRIGHT;
        enemiesHealth[iterator] = 2;
        enemiesX[iterator] = (uint8_t)rand() % 100 + 20;
        enemiesY[iterator] = (uint8_t)rand() % 100 + 20;

        set_sprite_tile(5 + (4 * iterator), 3);
        set_sprite_tile(6 + (4 * iterator), 3);
        set_sprite_tile(7 + (4 * iterator), 3);
        set_sprite_tile(8 + (4 * iterator), 3);
    }
}

void drawEnemies()
{
    for (iterator = 0; iterator < 4; ++iterator)
    {
        move_sprite(5 + (4 * iterator), enemiesX[iterator] + 8, enemiesY[iterator] + 16);
        move_sprite(6 + (4 * iterator), enemiesX[iterator] + 16, enemiesY[iterator] + 16);
        move_sprite(7 + (4 * iterator), enemiesX[iterator] + 8, enemiesY[iterator] + 24);
        move_sprite(8 + (4 * iterator), enemiesX[iterator] + 16, enemiesY[iterator] + 24);
    }
}

void updateEnemies()
{
    for (iterator = 0; iterator < 4; ++iterator)
    {
        if (enemiesStatus[iterator] | ENEMYSTATE_ACTIVE)
        {
            if ((weapon.x + HITBOX_OFFSET_X) < (enemiesX[iterator] + 16) && (weapon.x + 16 - HITBOX_OFFSET_X) > (enemiesX[iterator]) && (weapon.y + HITBOX_OFFSET_Y) < (enemiesY[iterator] + 16) && (weapon.y + 16 - HITBOX_OFFSET_Y) > (enemiesY[iterator]))
            {
                if (--enemiesHealth[iterator] == 0)
                {
                    enemiesStatus[iterator] &= ~ENEMYSTATE_ACTIVE;
                    enemiesX[iterator] = 200;
                    enemiesY[iterator] = 200;
                    numberEnemies--;

                    break;
                }

                switch (hero.lastDirection)
                {
                case HERO_FACING_RIGHT:
                    enemiesX[iterator] += 16;
                    break;
                case HERO_FACING_LEFT:
                    enemiesX[iterator] -= 16;
                    break;
                case HERO_FACING_DOWN:
                    enemiesY[iterator] += 16;
                    break;
                case HERO_FACING_UP:
                    enemiesY[iterator] -= 16;
                    break;
                };
            }
        }
    }
}