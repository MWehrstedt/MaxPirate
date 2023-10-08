#include <stdint.h>
#include <gb/gb.h>
#include "vars.h"

#pragma bank 0

uint8_t joypadCurrent = 0;
uint8_t joypadPrevious = 0;

int8_t targetTileIdTop;
int8_t targetTileIdCenter;
int8_t targetTileIdBottom;
int8_t iterator;
int8_t collision;
int8_t gamestate;

uint8_t heroPositionX;
uint8_t heroPositionY;
uint8_t heroMovement;

void (*currentPalaceInit)();
void (*currentLevelUpdate)();
void (*currentPalaceLoadRoom)();
void (*currentPalaceLoadNextRoom)();
BANKREF_EXTERN(currentLevelHitboxes)
const uint8_t (*currentLevelHitboxes)[];
uint8_t currentPalaceRoomId = 255;
uint8_t currentPalaceId = 255;


BANKREF_EXTERN(currentLevelEnemies)
uint8_t currentLevelEnemies[6][6];
