#include <stdint.h>
#include <gb/gb.h>
#include "vars.h"

uint8_t joypadCurrent = 0;
uint8_t joypadPrevious = 0;

uint8_t iterator;
uint8_t iterator2;
uint8_t temp;
uint8_t temp2;
//int8_t collision;
int8_t gamestate;
int8_t numberEnemies;
int8_t numberEnemiesTotal;

uint8_t currentPalaceRoomId = 255;
uint8_t currentPalaceId = 255;

uint16_t killedEnemies;

hero_t hero;
weapon_t weapon;
targetTile_t targetTileLeft;
targetTile_t targetTileRight;
targetTile_t targetTileUp;
targetTile_t targetTileDown;

void (*currentPalaceInit)();
//void (*currentLevelUpdate)();
//void (*currentPalaceLoadRoom)();
//void (*currentPalaceLoadNextRoom)();

// ----- Arrays -----
const uint8_t (*currentLevelHitboxes)[];
uint8_t nextSpriteId[4];
uint8_t enemiesType[ENEMY_MAXNUMBER];
uint8_t enemiesStatus[ENEMY_MAXNUMBER];
int8_t enemiesHealth[ENEMY_MAXNUMBER];
uint8_t enemiesTimers[ENEMY_MAXNUMBER];
uint8_t enemiesAnimationTimers[ENEMY_MAXNUMBER];
uint8_t enemiesHitTimers[ENEMY_MAXNUMBER];
uint8_t enemiesMovement[ENEMY_MAXNUMBER];
uint8_t enemiesX[ENEMY_MAXNUMBER];
uint8_t enemiesY[ENEMY_MAXNUMBER];
uint8_t enemiesNextDirection[2];
