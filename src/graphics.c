#include <gbdk/platform.h>
#include <gb/gb.h>
#include "../res/generalTiles.h"
#include "../res/heroTiles.h"
#include "../res/generalTiles_Map.h"
#include "../res/generalTiles_Map2.h"
#include "../res/generalTiles_Map3.h"

#pragma bank 255

BANKREF(initGfx)
void initGfx(unsigned char *bgTiles, const unsigned char *bgMap, unsigned char *objTiles) BANKED{
    set_bkg_data(0, 32, bgTiles);
    set_bkg_tiles(0, 0, 20, 18u, bgMap);

    set_sprite_data(0, 6, objTiles);
    set_sprite_tile(0, 2);
    set_sprite_tile(1, 3);
    set_sprite_tile(2, 4);
    set_sprite_tile(3, 5);
    
    SHOW_BKG;
    SHOW_SPRITES;
}