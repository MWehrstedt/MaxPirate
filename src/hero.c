
#include <gb/gb.h>
#include <gbdk/platform.h>
#include <stdint.h>
#include "hero.h"
#include "vars.h"

#pragma bank 255

BANKREF_EXTERN(drawHero)
void drawHero() NONBANKED
{
    move_sprite(0, heroPositionX + 8, heroPositionY + 16);
    move_sprite(1, heroPositionX + 16, heroPositionY + 16);
    move_sprite(2, heroPositionX + 8, heroPositionY + 24);
    move_sprite(3, heroPositionX + 16, heroPositionY + 24);
}

BANKREF_EXTERN(updateHero)
void updateHero() NONBANKED
{
    if (heroMovement & HERO_SPEED_LEFT)
    {
        heroPositionX -= HERO_SPEED;
    }
    else if (heroMovement & HERO_SPEED_RIGHT)
    {
        heroPositionX += HERO_SPEED;
    }

    if (heroMovement & HERO_SPEED_UP)
    {
        heroPositionY -= HERO_SPEED;
    }
    else if (heroMovement & HERO_SPEED_DOWN)
    {
        heroPositionY += HERO_SPEED;
    }

    // Check for warp collisions
    if(heroPositionX <= 1 || heroPositionX > 143 || heroPositionY <= 1 || heroPositionY > 127) {
        (*currentPalaceLoadNextRoom)();
    } 
}

BANKREF_EXTERN(checkCollision)
void checkCollision() NONBANKED
{
    // check target tile left
    if (heroMovement & HERO_SPEED_LEFT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileIdTop = ((heroPositionX - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdCenter = ((heroPositionX - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdBottom = ((heroPositionX - 1 + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if (
            (*currentLevelHitboxes)[targetTileIdCenter] == 1 ||
            (*currentLevelHitboxes)[targetTileIdBottom] == 1 ||
            (*currentLevelHitboxes)[targetTileIdTop] == 1)
        {
            // set hero velocity to 0
            heroMovement &= ~HERO_SPEED_LEFT;
        }
    }

    if (heroMovement & HERO_SPEED_RIGHT)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileIdTop = ((heroPositionX + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdCenter = ((heroPositionX + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 8) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdBottom = ((heroPositionX + 16 + 1 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 16 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if (
            (*currentLevelHitboxes)[targetTileIdCenter] == 1 ||
            (*currentLevelHitboxes)[targetTileIdBottom] == 1 ||
            (*currentLevelHitboxes)[targetTileIdTop] == 1)
        {
            // set hero velocity to 0
            heroMovement &= ~HERO_SPEED_RIGHT;
        }
    }

    if (heroMovement & HERO_SPEED_UP)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileIdTop = ((heroPositionX + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdCenter = ((heroPositionX + 8) / HITBOX_TILESIZE) + (((heroPositionY - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdBottom = ((heroPositionX + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY - 1 + HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if ((*currentLevelHitboxes)[targetTileIdCenter] == 1 ||
            (*currentLevelHitboxes)[targetTileIdBottom] == 1 ||
            (*currentLevelHitboxes)[targetTileIdTop] == 1)
        {
            // set hero velocity to 0
            heroMovement &= ~HERO_SPEED_UP;
        }
    }

    if (heroMovement & HERO_SPEED_DOWN)
    {
        // get target tile top check
        // x = posX / TS
        // y = posY / TS
        // i = (posX / TS) + ((posY / TS) * MS)
        targetTileIdTop = ((heroPositionX + HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdCenter = ((heroPositionX + 8) / HITBOX_TILESIZE) + (((heroPositionY + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileIdBottom = ((heroPositionX + 16 - HITBOX_OFFSET_X) / HITBOX_TILESIZE) + (((heroPositionY + 16 + 1 - HITBOX_OFFSET_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);

        if ((*currentLevelHitboxes)[targetTileIdCenter] == 1 ||
            (*currentLevelHitboxes)[targetTileIdBottom] == 1 ||
            (*currentLevelHitboxes)[targetTileIdTop] == 1)
        {
            // set hero velocity to 0
            heroMovement &= ~HERO_SPEED_DOWN;
        }
    }
}