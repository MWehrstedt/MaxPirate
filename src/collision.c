// #include <gb/gb.h>
#include <stdint.h>
#include "vars.h"
#include "hero.h"
#include "collision.h"

void checkCollisionObject()
{
    // iterator = 0;
    // for (; iterator < ENEMY_MAXNUMBER; ++iterator)
    // {
    //     if (enemiesStatus[iterator] & ENEMYSTATE_ACTIVE)
    //     {
    //         // Check hitbox overlap

            
    //     }
    // }
}

void checkCollisions()
{
    checkCollisionBackground(hero.movement, hero.x, hero.y, HERO_SPEED);

    if (hero.movement & HERO_SPEED_LEFT)
    {
        if (
            (*currentLevelHitboxes)[targetTileLeft.center] == 1 ||
            (*currentLevelHitboxes)[targetTileLeft.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTileLeft.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileLeft.center] == 2 ||
                  (*currentLevelHitboxes)[targetTileLeft.bottom] == 2 ||
                  (*currentLevelHitboxes)[targetTileLeft.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
    }

    if (hero.movement & HERO_SPEED_RIGHT)
    {
        if (
            (*currentLevelHitboxes)[targetTileRight.center] == 1 ||
            (*currentLevelHitboxes)[targetTileRight.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTileRight.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileRight.center] == 2 ||
                  (*currentLevelHitboxes)[targetTileRight.bottom] == 2 ||
                  (*currentLevelHitboxes)[targetTileRight.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
    }

    if (hero.movement & HERO_SPEED_DOWN)
    {
        if (
            (*currentLevelHitboxes)[targetTileDown.center] == 1 ||
            (*currentLevelHitboxes)[targetTileDown.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTileDown.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileDown.center] == 2 ||
                  (*currentLevelHitboxes)[targetTileDown.bottom] == 2 ||
                  (*currentLevelHitboxes)[targetTileDown.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
    }

    if (hero.movement & HERO_SPEED_UP)
    {
        if (
            (*currentLevelHitboxes)[targetTileUp.center] == 1 ||
            (*currentLevelHitboxes)[targetTileUp.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTileUp.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileUp.center] == 2 ||
                  (*currentLevelHitboxes)[targetTileUp.bottom] == 2 ||
                  (*currentLevelHitboxes)[targetTileUp.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
    }

    // if (hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT)
    // {
    //     checkCollisionObject();
    // }
}

void checkCollisionBackground(uint8_t direction, uint8_t x, uint8_t y, uint8_t speed)
{
    // check target tile left
    if (direction & HERO_SPEED_LEFT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileLeft.top = ((x - speed + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileLeft.center = ((x - speed + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileLeft.bottom = ((x - speed + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }

    if (direction & HERO_SPEED_RIGHT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileRight.top = ((x + 16 + speed - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileRight.center = ((x + 16 + speed - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileRight.bottom = ((x + 16 + speed - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }

    if (direction & HERO_SPEED_UP)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileUp.top = ((x + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y - speed + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileUp.center = ((x + 8) / HITBOX_TILESIZE) + (((y - speed + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileUp.bottom = ((x + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y - speed + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }

    if (direction & HERO_SPEED_DOWN)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileDown.top = ((x + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 16 + speed - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileDown.center = ((x + 8) / HITBOX_TILESIZE) + (((y + 16 + speed - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileDown.bottom = ((x + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((y + 16 + speed - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
}
