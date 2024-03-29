#include <gbdk/platform.h>
#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "../res/generalTiles.h"
#include "../res/heroTiles.h"
#include "../res/enemyTiles.h"
#include "../res/generalTiles_Map.h"
#include "../res/generalTiles_Map2.h"
#include "../res/generalTiles_Map3.h"
#include "../res/overlay.h"
#include "vars.h"

BANKREF(initGfx)
void initGfx(unsigned char *bgTiles, const unsigned char *bgMap, unsigned char *objTiles, unsigned char *overlayTiles)
{
    gb_decompress_bkg_data(0, bgTiles);
    set_bkg_tiles(0, 0, 20, 18u, bgMap);

    // Hero
    // set_sprite_data(0, 6, objTiles);
    gb_decompress_sprite_data(0, objTiles);
    gb_decompress_sprite_data(37, enemyTiles);
    set_sprite_tile(0, 1);
    set_sprite_tile(1, 2);
    set_sprite_tile(2, 3);
    set_sprite_tile(3, 4);

    // Weapon
    set_sprite_tile(4, 17);

    // Window

    move_win(7, 136);

    set_win_tiles(0, 0, 20, 3u, overlayTiles);
    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
}

void updateEnergyHUD()
{
    for (iterator2 = 0; iterator2 < HERO_ENERGYMAX; ++iterator2)
    {
        if (hero.energy > iterator2)
        {
            set_win_tile_xy(7 + iterator2, 0, 21);
        }
        else
        {
            set_win_tile_xy(7 + iterator2, 0, 22);
        }
    }
}

void updateEnemyHUD()
{
    //set_win_tile_xy(16, 0, 25 + (killedEnemies / 1000));
    set_win_tile_xy(17, 0, 25 + ((killedEnemies % 1000) / 100));
    set_win_tile_xy(18, 0, 25 + ((killedEnemies % 100) / 10));
    set_win_tile_xy(19, 0, 25 + (killedEnemies % 10));
}