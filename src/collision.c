// #include <gb/gb.h>
#include <stdint.h>
#include "cbtfx.h"
#include "../res/sfx.h"
#include "vars.h"
#include "hero.h"
#include "collision.h"

/// @brief Handle hero collisions with current level hitmaps
void getCollisions()
{
    // Get bg collisions
    checkCollisionBackground(hero.movement, hero.x, hero.y, HERO_SPEED);

    // Collision moving left
    if (hero.movement & HERO_SPEED_LEFT)
    {
        if (
            (*currentLevelHitboxes)[targetTileLeft.center] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileLeft.bottom] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileLeft.top] == HITBOX_TYPE_SOLID)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileLeft.center] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileLeft.bottom] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileLeft.top] == HITBOX_TYPE_DOOR))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_LEFT;
        }
        else if (hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT &&
                 ((*currentLevelHitboxes)[targetTileLeft.center] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileLeft.bottom] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileLeft.top] == HITBOX_TYPE_SPIKES))
        {
            CBTFX_PLAY_GOTHIT;
            hero.health--;
            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);
            hero.hitTimer = HERO_DEFAULTTIMER;
            hero.state = HEROSTATE_HIT;
            return;
        }
        else if (heartCollected == 0 &&
                 ((*currentLevelHitboxes)[targetTileLeft.center] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileLeft.bottom] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileLeft.top] == HITBOX_TYPE_HEART))
        {
            heartCollected = 1;
            ++hero.health;

            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);

            set_bkg_tile_xy(9, 6, 0);
            set_bkg_tile_xy(10, 6, 0);
            set_bkg_tile_xy(9, 7, 0);
            set_bkg_tile_xy(10, 7, 0);
        }
    }

    // Collision moving right
    if (hero.movement & HERO_SPEED_RIGHT)
    {
        if (
            (*currentLevelHitboxes)[targetTileRight.center] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileRight.bottom] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileRight.top] == HITBOX_TYPE_SOLID)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileRight.center] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileRight.bottom] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileRight.top] == HITBOX_TYPE_DOOR))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_RIGHT;
        }
        else if (hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT &&
                 ((*currentLevelHitboxes)[targetTileRight.center] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileRight.bottom] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileRight.top] == HITBOX_TYPE_SPIKES))
        {
            CBTFX_PLAY_GOTHIT;
            hero.health--;
            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);
            hero.hitTimer = HERO_DEFAULTTIMER;
            hero.state = HEROSTATE_HIT;
            return;
        }
        else if (heartCollected == 0 &&
                 ((*currentLevelHitboxes)[targetTileRight.center] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileRight.bottom] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileRight.top] == HITBOX_TYPE_HEART))
        {
            heartCollected = 1;
            ++hero.health;

            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);

            set_bkg_tile_xy(9, 6, 0);
            set_bkg_tile_xy(10, 6, 0);
            set_bkg_tile_xy(9, 7, 0);
            set_bkg_tile_xy(10, 7, 0);
        }
    }

    // Collision moving down
    if (hero.movement & HERO_SPEED_DOWN)
    {
        if (
            (*currentLevelHitboxes)[targetTileDown.center] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileDown.bottom] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileDown.top] == HITBOX_TYPE_SOLID)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileDown.center] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileDown.bottom] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileDown.top] == HITBOX_TYPE_DOOR))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_DOWN;
        }
        else if (hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT &&
                 ((*currentLevelHitboxes)[targetTileDown.center] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileDown.bottom] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileDown.top] == HITBOX_TYPE_SPIKES))
        {
            CBTFX_PLAY_GOTHIT;
            hero.health--;
            CBTFX_PLAY_GOTHIT;
            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);
            hero.hitTimer = HERO_DEFAULTTIMER;
            hero.state = HEROSTATE_HIT;
            return;
        }
        else if (heartCollected == 0 &&
                 ((*currentLevelHitboxes)[targetTileDown.center] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileDown.bottom] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileDown.top] == HITBOX_TYPE_HEART))
        {
            heartCollected = 1;
            ++hero.health;

            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);

            set_bkg_tile_xy(9, 6, 0);
            set_bkg_tile_xy(10, 6, 0);
            set_bkg_tile_xy(9, 7, 0);
            set_bkg_tile_xy(10, 7, 0);
        }
    }

    // Collision moving up
    if (hero.movement & HERO_SPEED_UP)
    {
        if (
            (*currentLevelHitboxes)[targetTileUp.center] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileUp.bottom] == HITBOX_TYPE_SOLID ||
            (*currentLevelHitboxes)[targetTileUp.top] == HITBOX_TYPE_SOLID)
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
        else if (numberEnemies &&
                 ((*currentLevelHitboxes)[targetTileUp.center] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileUp.bottom] == HITBOX_TYPE_DOOR ||
                  (*currentLevelHitboxes)[targetTileUp.top] == HITBOX_TYPE_DOOR))
        {
            // set hero velocity to 0
            hero.movement &= ~HERO_SPEED_UP;
        }
        else if (hero.isInvulnerable == 0 && hero.state != HEROSTATE_HIT &&
                 ((*currentLevelHitboxes)[targetTileUp.center] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileUp.bottom] == HITBOX_TYPE_SPIKES ||
                  (*currentLevelHitboxes)[targetTileUp.top] == HITBOX_TYPE_SPIKES))
        {
            // set hero velocity to 0
            // hero.movement &= ~HERO_SPEED_UP;
            CBTFX_PLAY_GOTHIT;
            hero.health--;
            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);
            hero.hitTimer = HERO_DEFAULTTIMER;
            hero.state = HEROSTATE_HIT;
            return;
        }
        else if (heartCollected == 0 &&
                 ((*currentLevelHitboxes)[targetTileUp.center] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileUp.bottom] == HITBOX_TYPE_HEART ||
                  (*currentLevelHitboxes)[targetTileUp.top] == HITBOX_TYPE_HEART))
        {
            heartCollected = 1;
            ++hero.health;

            set_win_tile_xy(GAME_NUMBERSPRITEHEALTHX, 1, GAME_NUMBERSPRITEOFFSETPLAYING + hero.health);

            set_bkg_tile_xy(9, 6, 0);
            set_bkg_tile_xy(10, 6, 0);
            set_bkg_tile_xy(9, 7, 0);
            set_bkg_tile_xy(10, 7, 0);
        }
    }
}

/// @brief Get tile from current hitmap based on position. Sets `targetTileLeft`, `targetTileRight`, `targetTileUp` and `targetTileDown` based on directions given.
/// @param direction Direction flags
/// @param x x position in pixels
/// @param y y position in pixels
/// @param speed entity speed
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
