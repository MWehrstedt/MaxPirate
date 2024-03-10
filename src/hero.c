#include <gb/gb.h>
#include <stdint.h>
#include "vars.h"
#include "hero.h"
#include "level-dbg.h"

void drawHero()
{
    move_sprite(0, hero.x + 8, hero.y + 16);
    move_sprite(1, hero.x + 16, hero.y + 16);
    move_sprite(2, hero.x + 8, hero.y + 24);
    move_sprite(3, hero.x + 16, hero.y + 24);

    move_sprite(4, weapon.x + 8, weapon.y + 16);
}

void updateHero()
{
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

    // Check for warp collisions
    if (hero.x <= 1 || hero.x > 143 || hero.y <= 1 || hero.y > 127)
    {
        //(*currentPalaceLoadNextRoom)();
        loadNextRoomDebug();
    }

    switch (hero.state)
    {
    case HEROSTATE_NORMAL:
        break;
    case HEROSTATE_ATTACK:
        if (--weapon.timer == 0)
        {
            weapon.x = 170;
            weapon.y = 170;
            hero.state = HEROSTATE_NORMAL;
            break;
        }
        switch (hero.lastDirection)
        {
        case HERO_FACING_LEFT:
            weapon.x = hero.x - 8;
            weapon.y = hero.y + 4;
            break;
        case HERO_FACING_RIGHT:
            weapon.x = hero.x + 16;
            weapon.y = hero.y + 4;
            break;
        case HERO_FACING_UP:
            weapon.x = hero.x + 4;
            weapon.y = hero.y - 8;
            break;
        case HERO_FACING_DOWN:
            weapon.x = hero.x + 4;
            weapon.y = hero.y + 16;
            break;
        }

        break;
    case HEROSTATE_HIT:
        if (--hero.hitTimer == 0)
        {
            hero.state = HEROSTATE_NORMAL;
        }
        break;
    }
}

void checkCollisionBackground()
{
    // check target tile left
    if (hero.movement & HERO_SPEED_LEFT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTile.top = ((hero.x - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.center = ((hero.x - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.bottom = ((hero.x - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if (
            (*currentLevelHitboxes)[targetTile.center] == 1 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTile.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
        else if (numberEnemies &&
            ((*currentLevelHitboxes)[targetTile.center] == 2 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 2 ||
            (*currentLevelHitboxes)[targetTile.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
    }

    if (hero.movement & HERO_SPEED_RIGHT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTile.top = ((hero.x + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.center = ((hero.x + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.bottom = ((hero.x + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if (
            (*currentLevelHitboxes)[targetTile.center] == 1 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTile.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
        else if (numberEnemies &&
            ((*currentLevelHitboxes)[targetTile.center] == 2 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 2 ||
            (*currentLevelHitboxes)[targetTile.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
    }

    if (hero.movement & HERO_SPEED_UP)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTile.top = ((hero.x + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.center = ((hero.x + 8) / HITBOX_TILESIZE) + (((hero.y - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.bottom = ((hero.x + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if ((*currentLevelHitboxes)[targetTile.center] == 1 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTile.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
        else if (numberEnemies &&
            ((*currentLevelHitboxes)[targetTile.center] == 2 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 2 ||
            (*currentLevelHitboxes)[targetTile.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
    }

    if (hero.movement & HERO_SPEED_DOWN)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTile.top = ((hero.x + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.center = ((hero.x + 8) / HITBOX_TILESIZE) + (((hero.y + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTile.bottom = ((hero.x + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((hero.y + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if ((*currentLevelHitboxes)[targetTile.center] == 1 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 1 ||
            (*currentLevelHitboxes)[targetTile.top] == 1)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
        else if (numberEnemies &&
            ((*currentLevelHitboxes)[targetTile.center] == 2 ||
            (*currentLevelHitboxes)[targetTile.bottom] == 2 ||
            (*currentLevelHitboxes)[targetTile.top] == 2))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
    }
}

void checkCollisionObject()
{
    iterator = 0;
    for (; iterator < numberEnemies; ++iterator)
    {
        if (enemiesStatus[iterator] | ENEMYSTATE_ACTIVE)
        {
            // Check hitbox overlap

            if ((hero.x + HITBOX_OFFSET_X) < (enemiesX[iterator] + 16) && (hero.x + 16 - HITBOX_OFFSET_X) > (enemiesX[iterator]) && (hero.y + HITBOX_OFFSET_Y) < (enemiesY[iterator] + 16) && (hero.y + 16 - HITBOX_OFFSET_Y) > (enemiesY[iterator]))
            {
                hero.hitTimer = HERO_DEFAULTTIMER;
                hero.state = HEROSTATE_HIT;

                switch (hero.lastDirection)
                {
                case HERO_FACING_RIGHT:
                    hero.x -= 8;
                    break;
                case HERO_FACING_LEFT:
                    hero.x += 8;
                    break;
                case HERO_FACING_DOWN:
                    hero.y -= 8;
                    break;
                case HERO_FACING_UP:
                    hero.y += 8;
                    break;
                };
            }
        }
    }
}