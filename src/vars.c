#include <stdint.h>
#include <gb/gb.h>
#include "vars.h"

/// @brief Inputs for current frame
uint8_t joypadCurrent = 0;

/// @brief Inputs for last frame
uint8_t joypadPrevious = 0;

/// @brief Global iterator
uint8_t iterator;

/// @brief Global iterator for inner loops
uint8_t iterator2;

/// @brief General purpose var
uint8_t temp;

/// @brief Second general purpose var
uint8_t temp2;

/// @brief Timer to show score screen
uint16_t scoreTimer;

/// @brief Global game state.
int8_t gamestate;

/// @brief Number of enemies on the current screen
int8_t numberEnemies;

/// @brief Number of enemies to beat until level is cleared
int8_t numberEnemiesTotal;

/// @brief Id for currently loaded level.
uint8_t currentLevelId = 255;

/// @brief Global score counter
uint16_t killedEnemies;

/// @brief Counter for rooms cleared
uint8_t roomsCleared;

uint8_t heartCollected;

/// @brief Hero object
hero_t hero;

/// @brief Weapon object
weapon_t weapon;

/// @brief Collision tile for check function left direction
targetTile_t targetTileLeft;

/// @brief Collision tile for check function right direction
targetTile_t targetTileRight;

/// @brief Collision tile for check function up direction
targetTile_t targetTileUp;

/// @brief Collision tile for check function down direction
targetTile_t targetTileDown;

// ----- Arrays -----

/// @brief Hitmap for current level
const uint8_t (*currentLevelHitboxes)[];

/// @brief Saves to sprite id for the next update
uint8_t nextSpriteId[4];

/// @brief Enemy type
uint8_t enemiesType[ENEMY_MAXNUMBER];

/// @brief Enemy status flags
uint8_t enemiesStatus[ENEMY_MAXNUMBER];

/// @brief Enemy health counter
int8_t enemiesHealth[ENEMY_MAXNUMBER];

/// @brief General purpose enemy timer
uint8_t enemiesTimers[ENEMY_MAXNUMBER];

/// @brief Enemy animation timer
uint8_t enemiesAnimationTimers[ENEMY_MAXNUMBER];

/// @brief Enemy hit timers
uint8_t enemiesHitTimers[ENEMY_MAXNUMBER];

/// @brief Enemy movement flags
uint8_t enemiesMovement[ENEMY_MAXNUMBER];

/// @brief Enemy x position
uint8_t enemiesX[ENEMY_MAXNUMBER];

/// @brief Enemy y position
uint8_t enemiesY[ENEMY_MAXNUMBER];

/// @brief Enemy next direction in relation to hero
uint8_t enemiesNextDirection[2];
