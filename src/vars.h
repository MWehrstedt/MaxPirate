#ifndef __VARS_H__
#define __VARS_H__
#include "../include/hUGEDriver.h"

// ----- Defines -----

#define CAMERALOCK_RIGHT 175
#define CAMERALOCK_BOTTOM 184

#define ENEMY_DEFAULTTIMER 30
#define ENEMY_KNOCKBACK 2
#define ENEMY_INVULNTIMER 40
#define ENEMY_MAXNUMBER 3
#define ENEMY_SPEED 1

#define ENEMYSTATE_CLEAR 0
#define ENEMYSTATE_SPAWNING 0b00000001
#define ENEMYSTATE_DIE 0b00000010
#define ENEMYSTATE_ACTIVE 0b00000100
#define ENEMYSTATE_HIT 0b00001000
#define ENEMYSTATE_DIRECTIONISRIGHT 0b00010000
#define ENEMYSTATE_DIRECTIONISDOWN 0b00100000
#define ENEMYSTATE_DIRECTIONISLEFT 0b01000000
#define ENEMYSTATE_DIRECTIONISUP 0b10000000

#define ENEMYTYPE_ZOMBIE 1
#define ENEMYTYPE_NINJA 2
#define ENEMYTYPE_SHOOTER 3

#define ENEMYNINJA_SPRITEID 53
#define ENEMYZOMBIE_SPRITEID 37

#define HITBOX_MAPSIZE_X 10
#define HITBOX_MAPSIZE_Y 9
#define HITBOX_OFFSET_X 4
#define HITBOX_OFFSET_Y 4
#define HITBOX_TILESIZE 16

#define HITBOX_TYPE_SOLID 1
#define HITBOX_TYPE_DEATH 2

#define GAMESTATE_MAINMENU 1
#define GAMESTATE_PAUSED 2
#define GAMESTATE_PLAYING 3
#define GAMESTATE_DIEING 4

#define HERO_FACING_LEFT 0b10000000
#define HERO_FACING_RIGHT 0b01000000
#define HERO_FACING_UP 0b00100000
#define HERO_FACING_DOWN 0b00010000

#define HERO_ANIMATIONTIMER 10
#define HERO_ANIMATIONTIMERMAX 20
#define HERO_DEFAULTTIMER 15
#define HERO_ENERGYMAX 5
#define HERO_INVULNTIMER 100
#define HERO_SPEED 1
#define HERO_SPEED_LEFT 0b00001000
#define HERO_SPEED_RIGHT 0b00000100
#define HERO_SPEED_UP 0b00000010
#define HERO_SPEED_DOWN 0b00000001
#define HERO_SPEED_RESETMASK 0b00001111
#define HERO_STARTHEALTH 8

#define HEROSTATE_NORMAL 0b00000001
#define HEROSTATE_HIT 0b00000010
#define HEROSTATE_INVULNERABLE 0b00000011
#define HEROSTATE_DEMON 0b00000100
#define HEROSTATE_DEMON_HIT 0b00000101
#define HEROSTATE_ATTACK 0b00000110
#define HEROSTATE_SPECIAL 0b00000111
#define HEROSTATE_CUTSCENE 0b00001000

#define WEAPON_DEFAULTTIMER 15
#define WEAPON_HITBOX_OFFSET_X 5
#define WEAPON_HITBOX_OFFSET_Y 5
#define WEAPON_SHOTTIMER 30
#define WEAPON_SHOTSPEED 2
#define WEAPON_MELEE_SPRITE_ID 33
#define WEAPON_SHOT_SPRITE_ID 35
#define WEAPON_TYPE_INACTIVE 0
#define WEAPON_TYPE_MELEE 1
#define WEAPON_TYPE_SHOT 2

// ----- Variables -----

/// @brief Inputs for current frame
extern uint8_t joypadCurrent;

/// @brief Inputs for last frame
extern uint8_t joypadPrevious;

extern uint8_t iterator;
extern uint8_t iterator2;
extern uint8_t temp;
extern uint8_t temp2;
extern int8_t gamestate;

/// @brief Number of enemies on the current screen
extern int8_t numberEnemies;
extern int8_t numberEnemiesTotal;

/// @brief Id for currently loaded room.
extern uint8_t currentPalaceRoomId;

/// @brief Id for currently loaded palace
extern uint8_t currentPalaceId;

extern uint16_t killedEnemies;

extern const hUGESong_t samplesong;

// ----- Typedefs -----
typedef struct
{
    uint8_t animationTimer;
    uint8_t energy;
    uint8_t deltaX;
    uint8_t deltaY;
    int8_t health;
    uint8_t hitTimer;
    uint8_t isInvulnerable;
    uint8_t movement;
    uint8_t state;
    uint8_t stats;
    uint8_t lastDirection;
    uint8_t x;
    uint8_t y;
} hero_t;

typedef struct
{
    uint8_t direction;
    uint8_t timer;
    uint8_t type;
    uint8_t x;
    uint8_t y;
} weapon_t;

typedef struct
{
    uint8_t bottom;
    uint8_t center;
    uint8_t top;
} targetTile_t;

// ----- Objects for typedefs -----

/// @brief Hero object
extern hero_t hero;

/// @brief Weapon object
extern weapon_t weapon;

/// @brief Collision tile for check function left direction
extern targetTile_t targetTileLeft;
extern targetTile_t targetTileRight;
extern targetTile_t targetTileUp;
extern targetTile_t targetTileDown;

// ----- Functions -----

/// @brief Init function for current Palace.
extern void (*currentPalaceInit)();

// extern void (*currentLevelUpdate)();

/// @brief Loads hitmap and tile map for the room with id 'currentPalaceRoomId'
// extern void (*currentPalaceLoadRoom)();

/// @brief Updates 'currentPalaceRoomId' after a warp and loads the proper room.
// extern void (*currentPalaceLoadNextRoom)();

// ----- Arrays -----

/// @brief Hitmap for current level
extern const uint8_t (*currentLevelHitboxes)[];

extern uint8_t nextSpriteId[4];

extern uint8_t enemiesType[ENEMY_MAXNUMBER];
extern uint8_t enemiesStatus[ENEMY_MAXNUMBER];
extern int8_t enemiesHealth[ENEMY_MAXNUMBER];
extern uint8_t enemiesTimers[ENEMY_MAXNUMBER];
extern uint8_t enemiesAnimationTimers[ENEMY_MAXNUMBER];
extern uint8_t enemiesHitTimers[ENEMY_MAXNUMBER];
extern uint8_t enemiesMovement[ENEMY_MAXNUMBER];
extern uint8_t enemiesX[ENEMY_MAXNUMBER];
extern uint8_t enemiesY[ENEMY_MAXNUMBER];
extern uint8_t enemiesNextDirection[2];

static const uint8_t enemiesSpriteId[3] =
{
    0,
    ENEMYZOMBIE_SPRITEID,
    ENEMYNINJA_SPRITEID
};

extern const hUGESong_t bg_song;
#endif