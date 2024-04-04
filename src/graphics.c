#include <gbdk/platform.h>
#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "../res/enemyTiles.h"
#include "../res/generalTiles.h"
#include "../res/generalTilesIntro_map.h"
#include "../res/generalTilesOutro_map.h"
#include "../res/generalTiles_Map.h"
#include "../res/generalTiles_Map2.h"
#include "../res/generalTiles_Map3.h"
#include "../res/generalTiles_Map4.h"
#include "../res/generalTiles_Map5.h"
#include "../res/heroTiles.h"
#include "../res/introTiles.h"
#include "../res/introTiles_Map.h"
#include "../res/menuTiles.h"
#include "../res/menuTiles_Map.h"
#include "../res/overlayMap.h"
#include "../res/scoreTiles_Map.h"
#include "../res/sfx.h"
#include "cbtfx.h"
#include "level.h"
#include "vars.h"

/// @brief Load intro card graphics
void initGfxIntro()
{
    DISPLAY_OFF;

    // Load compressed tiles to VRAM
    gb_decompress_bkg_data(0, introTiles);

    // Set bg map to intro map
    set_bkg_tiles(0, 0, 20, 18u, introTiles_Map);

    SHOW_BKG;
    DISPLAY_ON;
}

/// @brief Load main menu graphics
void initGfxMainMenu()
{
    DISPLAY_OFF;

    // Load compressed tiles to VRAM
    gb_decompress_bkg_data(0, menuTiles);

    // Set bg map to main menu map
    set_bkg_tiles(0, 0, 20, 18u, menuTiles_Map);

    HIDE_WIN;
    SHOW_BKG;
    HIDE_SPRITES;
    DISPLAY_ON;
}

/// @brief Loads graphics for current level.
/// @param bgTiles Address to background tiles
/// @param bgMap Address to background map
/// @param objTiles Address to OAM tiles
/// @param overlayMap Address to window map
void initGfx(unsigned char *bgTiles, const unsigned char *bgMap, unsigned char *objTiles, unsigned char *overlayMap)
{
    HIDE_BKG;
    HIDE_SPRITES;

    // Load compressed tiles to VRAM
    gb_decompress_bkg_data(0, bgTiles);

    // Set bg map to current room map
    set_bkg_tiles(0, 0, 20, 18u, bgMap);

    // Hero

    // Load compressed hero and enemy data to VRAM
    gb_decompress_sprite_data(0, objTiles);
    gb_decompress_sprite_data(37, enemyTiles);

    // Set hero tiles. Hero is always the first four OAM slots
    set_sprite_tile(0, 1);
    set_sprite_tile(1, 2);
    set_sprite_tile(2, 3);
    set_sprite_tile(3, 4);

    // Set weapon tile
    set_sprite_tile(4, 17);

    // Move window to position
    move_win(7, GAME_WINPLAYINGY);

    // Set window tile map
    set_win_tiles(0, 0, 20, 6u, overlayMap);

    SHOW_BKG;
    SHOW_WIN;
}

/// @brief Load score graphics
void initGfxScore()
{
    DISPLAY_OFF;
    HIDE_WIN;
    HIDE_SPRITES;
    // Load compressed tiles to VRAM
    gb_decompress_bkg_data(0, introTiles);

    // Set bg map to intro map
    set_bkg_tiles(0, 0, 20, 18u, scoreTiles_Map);

    set_bkg_tile_xy(8, 6, 28 + (killedEnemies / 1000));
    set_bkg_tile_xy(9, 6, 28 + ((killedEnemies % 1000) / 100));
    set_bkg_tile_xy(10, 6, 28 + ((killedEnemies % 100) / 10));
    set_bkg_tile_xy(11, 6, 28 + (killedEnemies % 10));

    set_bkg_tile_xy(9, 9, 28 + ((roomsCleared % 1000) / 100));
    set_bkg_tile_xy(10, 9, 28 + ((roomsCleared % 100) / 10));
    set_bkg_tile_xy(11, 9, 28 + (roomsCleared % 10));

    SHOW_BKG;
    DISPLAY_ON;
}

/// @brief Update energy count on window
void updateEnergyHUDGfx()
{
    // Count up until energy value is reached
    for (iterator2 = 0; iterator2 < HERO_ENERGYMAX; ++iterator2)
    {
        if (hero.energy > iterator2)
        {
            // Draw filled
            set_win_tile_xy(7 + iterator2, 1, 41);
        }
        else
        {
            // Draw empty
            set_win_tile_xy(7 + iterator2, 1, 42);
        }
    }
}

/// @brief Update enemy count on window
void updateEnemyHUDGfx()
{
    if (killedEnemies > 999)
    {
        set_win_tile_xy(15, 1, GAME_NUMBERSPRITEOFFSETPLAYING + (killedEnemies / 1000));
    }
    set_win_tile_xy(16, 1, GAME_NUMBERSPRITEOFFSETPLAYING + ((killedEnemies % 1000) / 100));
    set_win_tile_xy(17, 1, GAME_NUMBERSPRITEOFFSETPLAYING + ((killedEnemies % 100) / 10));
    set_win_tile_xy(18, 1, GAME_NUMBERSPRITEOFFSETPLAYING + (killedEnemies % 10));

    set_win_tile_xy(16, 2, GAME_NUMBERSPRITEOFFSETPLAYING + ((roomsCleared % 1000) / 100));
    set_win_tile_xy(17, 2, GAME_NUMBERSPRITEOFFSETPLAYING + ((roomsCleared % 100) / 10));
    set_win_tile_xy(18, 2, GAME_NUMBERSPRITEOFFSETPLAYING + (roomsCleared % 10));
}

/// @brief Replace closed gate graphics with empty tiles
void openDoorsGfx()
{

    for (iterator2 = 0; iterator2 < 4; ++iterator2)
    {
        set_bkg_tile_xy(doorLocationsTopX[currentLevelId] + iterator2, 0, 0);
        set_bkg_tile_xy(doorLocationsBottomX[currentLevelId] + iterator2, 14, 0);

        set_bkg_tile_xy(0, doorLocationsLeftY[currentLevelId] + iterator2, 0);
        set_bkg_tile_xy(18, doorLocationsRightY[currentLevelId] + iterator2, 0);

        set_bkg_tile_xy(doorLocationsTopX[currentLevelId] + iterator2, 1, 0);
        set_bkg_tile_xy(doorLocationsBottomX[currentLevelId] + iterator2, 15, 0);

        set_bkg_tile_xy(1, doorLocationsLeftY[currentLevelId] + iterator2, 0);
        set_bkg_tile_xy(19, doorLocationsRightY[currentLevelId] + iterator2, 0);
    }
}