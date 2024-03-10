#include <stdint.h>
#include <gb/gb.h>
#include "vars.h"

uint8_t joypadCurrent = 0;
uint8_t joypadPrevious = 0;

int8_t iterator;
int8_t collision;
int8_t gamestate;
int8_t numberEnemies;

uint8_t currentPalaceRoomId = 255;
uint8_t currentPalaceId = 255;

heroObject hero;
weaponObject weapon;
targetTileObject targetTile;

void (*currentPalaceInit)();
//void (*currentLevelUpdate)();
//void (*currentPalaceLoadRoom)();
//void (*currentPalaceLoadNextRoom)();

// ----- Arrays -----
const uint8_t (*currentLevelHitboxes)[];
uint8_t enemiesStatus[4];
uint8_t enemiesHealth[4];
uint8_t enemiesX[4];
uint8_t enemiesY[4];
