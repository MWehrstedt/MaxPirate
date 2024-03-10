#ifndef __VARS_H__
#define __VARS_H__

// ----- Defines -----
#define HITBOX_TILESIZE 16
#define HITBOX_MAPSIZE_X 10
#define HITBOX_MAPSIZE_Y 9
#define HITBOX_OFFSET_X 4
#define HITBOX_OFFSET_Y 4

#define HITBOX_TYPE_SOLID 1
#define HITBOX_TYPE_DEATH 2

#define GAMESTATE_MAINMENU 1
#define GAMESTATE_PAUSED 2
#define GAMESTATE_PLAYING 3
#define GAMESTATE_DIEING 4

#define CAMERALOCK_RIGHT 175
#define CAMERALOCK_BOTTOM 184

#define HERO_FACING_LEFT 0b10000000
#define HERO_FACING_RIGHT 0b01000000
#define HERO_FACING_UP 0b00100000
#define HERO_FACING_DOWN 0b00010000

#define HERO_SPEED_LEFT 0b00001000
#define HERO_SPEED_RIGHT 0b00000100
#define HERO_SPEED_UP 0b00000010
#define HERO_SPEED_DOWN 0b00000001
#define HERO_SPEED_RESETMASK 0b00001111
#define HERO_SPEED 1
#define HERO_DEFAULTTIMER 30

#define HEROSTATE_NORMAL 0b00000001
#define HEROSTATE_HIT 0b00000010
#define HEROSTATE_INVULNERABLE 0b00000011
#define HEROSTATE_DEMON 0b00000100
#define HEROSTATE_DEMON_HIT 0b00000101
#define HEROSTATE_ATTACK 0b00000110
#define HEROSTATE_SPECIAL 0b00000111
#define HEROSTATE_CUTSCENE 0b00001000

#define WEAPON_DEFAULTTIMER 15

#define ENEMYSTATE_CLEAR 0
#define ENEMYSTATE_ACTIVE 0b00000100
#define ENEMYSTATE_HIT 0b00001000
#define ENEMYSTATE_DIRECTIONISRIGHT 0b00010000
#define ENEMYSTATE_DIRECTIONISDOWN 0b00100000
#define ENEMYSTATE_DIRECTIONISLEFT 0b01000000
#define ENEMYSTATE_DIRECTIONISUP 0b10000000

// ----- Variables -----
/// Inputs for current frame
extern uint8_t joypadCurrent;
/// Inputs for last frame
extern uint8_t joypadPrevious;

extern int8_t iterator;
extern int8_t collision;
extern int8_t gamestate;
extern int8_t numberEnemies;

/// @brief Id for currently loaded room.
extern uint8_t currentPalaceRoomId;

/// @brief Id for currently loaded palace
extern uint8_t currentPalaceId;

// ----- Typedefs -----
typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t movement;
    uint8_t stats;
    uint8_t state;
    uint8_t lastDirection;
    uint8_t hitTimer;
} heroObject;

typedef struct
{
    uint8_t timer;
    uint8_t x;
    uint8_t y;
} weaponObject;

typedef struct
{
    int8_t top;
    int8_t center;
    int8_t bottom;
} targetTileObject;

// ----- Objects for typedefs -----
extern heroObject hero;
extern weaponObject weapon;
extern targetTileObject targetTile;

// ----- Functions -----
/// @brief Init function for current Palace.
extern void (*currentPalaceInit)();

// extern void (*currentLevelUpdate)();

/// @brief Loads hitmap and tile map for the room with id 'currentPalaceRoomId'
// extern void (*currentPalaceLoadRoom)();

/// @brief Updates 'currentPalaceRoomId' after a warp and loads the proper room.
// extern void (*currentPalaceLoadNextRoom)();

// ----- Arrays -----
extern const uint8_t (*currentLevelHitboxes)[];
extern uint8_t enemiesStatus[4];
extern uint8_t enemiesHealth[4];
extern uint8_t enemiesX[4];
extern uint8_t enemiesY[4];
#endif