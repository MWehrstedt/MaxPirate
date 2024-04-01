#ifndef __VARS_H__
#define __VARS_H__
#include "../include/hUGEDriver.h"

// ----- Defines -----

#define CBTFX_PLAY_CLOSEDOOR CBTFX_init(&sfx_closedoor[0])
#define CBTFX_PLAY_DIE CBTFX_init(&sfx_die[0])
#define CBTFX_PLAY_ENEMYDESTROY CBTFX_init(&sfx_enemydestroy[0])
#define CBTFX_PLAY_ENERGYBEAM CBTFX_init(&sfx_energybeam[0])
#define CBTFX_PLAY_GOTHIT CBTFX_init(&sfx_gothit[0])
#define CBTFX_PLAY_GROWL CBTFX_init(&sfx_growl[0])
#define CBTFX_PLAY_HEALTH CBTFX_init(&sfx_health[0])
#define CBTFX_PLAY_OPENDOOR CBTFX_init(&sfx_opendoor[0])
#define CBTFX_PLAY_POWERUP CBTFX_init(&sfx_powerup[0])

#define ENEMY_DEFAULTHEALTH 127
#define ENEMY_DEFAULTENEMYNUMBER 8
#define ENEMY_DEFAULTTIMER 30
#define ENEMY_KNOCKBACK 2
#define ENEMY_INVULNTIMER 40
#define ENEMY_MAXNUMBER 3
#define ENEMY_OAM_ID_OFFSET 5
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
#define HITBOX_TYPE_DOOR 2
#define HITBOX_TYPE_SPIKES 3

#define GAME_INTROTIMER 240
#define GAME_MAPNUMBER 6
#define GAME_SCORETIMER 400
#define GAME_WINPLAYINGY 128
#define GAME_WINPAUSEDY 96

#define GAMESTATE_INTRO 0
#define GAMESTATE_MAINMENU 1
#define GAMESTATE_PAUSED 2
#define GAMESTATE_PLAYING 3
#define GAMESTATE_PAUSING 4
#define GAMESTATE_UNPAUSING 5
#define GAMESTATE_SCORE 6

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
#define HERO_STARTHEALTH 6

#define HEROSTATE_NORMAL 0b00000001
#define HEROSTATE_HIT 0b00000010
#define HEROSTATE_INVULNERABLE 0b00000011
#define HEROSTATE_DEMON 0b00000100
#define HEROSTATE_DEMON_HIT 0b00000101
#define HEROSTATE_ATTACK 0b00000110
#define HEROSTATE_SPECIAL 0b00000111
#define HEROSTATE_CUTSCENE 0b00001000

#define WEAPON_DEFAULTTIMER 15
#define WEAPON_HITBOX_OFFSET_X 2
#define WEAPON_HITBOX_OFFSET_Y 2
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

/// @brief Global iterator
extern uint8_t iterator;

/// @brief Global iterator for inner loops
extern uint8_t iterator2;

/// @brief General purpose var
extern uint8_t temp;

/// @brief Second general purpose var
extern uint8_t temp2;

/// @brief Timer to show score screen
extern uint16_t scoreTimer;

/// @brief Global game state.
extern int8_t gamestate;

/// @brief Number of enemies on the current screen
extern int8_t numberEnemies;

/// @brief Number of enemies to beat until level is cleared
extern int8_t numberEnemiesTotal;

/// @brief Id for currently loaded level.
extern uint8_t currentLevelId;

/// @brief Global score counter
extern uint16_t killedEnemies;

/// @brief BGM Game loop
extern const hUGESong_t bgm_rpgbattle;

/// @brief BGM Game Over
extern const hUGESong_t bgm_gameover;

// ----- Typedefs -----

/// @brief Hero type
typedef struct
{
    uint8_t animationTimer;
    uint8_t energy;
    int8_t health;
    uint8_t hitTimer;
    uint8_t isInvulnerable;
    uint8_t movement;
    uint8_t state;
    uint8_t lastDirection;
    uint8_t x;
    uint8_t y;
} hero_t;

/// @brief Weapon type
typedef struct
{
    uint8_t direction;
    uint8_t timer;
    uint8_t type;
    uint8_t x;
    uint8_t y;
} weapon_t;

/// @brief TargetTile type
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

/// @brief Collision tile for check function right direction
extern targetTile_t targetTileRight;

/// @brief Collision tile for check function up direction
extern targetTile_t targetTileUp;

/// @brief Collision tile for check function down direction
extern targetTile_t targetTileDown;

// ----- Arrays -----

/// @brief Hitmap for current level
extern const uint8_t (*currentLevelHitboxes)[];

/// @brief Saves to sprite id for the next update
extern uint8_t nextSpriteId[4];

/// @brief Enemy type
extern uint8_t enemiesType[ENEMY_MAXNUMBER];

/// @brief Enemy status flags
extern uint8_t enemiesStatus[ENEMY_MAXNUMBER];

/// @brief Enemy health counter
extern int8_t enemiesHealth[ENEMY_MAXNUMBER];

/// @brief General purpose enemy timer
extern uint8_t enemiesTimers[ENEMY_MAXNUMBER];

/// @brief Enemy animation timer
extern uint8_t enemiesAnimationTimers[ENEMY_MAXNUMBER];

/// @brief Enemy hit timers
extern uint8_t enemiesHitTimers[ENEMY_MAXNUMBER];

/// @brief Enemy movement flags
extern uint8_t enemiesMovement[ENEMY_MAXNUMBER];

/// @brief Enemy x position
extern uint8_t enemiesX[ENEMY_MAXNUMBER];

/// @brief Enemy y position
extern uint8_t enemiesY[ENEMY_MAXNUMBER];

/// @brief Enemy next direction in relation to hero
extern uint8_t enemiesNextDirection[2];

/// @brief Enemy sprite Id Pool
static const uint8_t enemiesSpriteId[3] =
{
    0,
    ENEMYZOMBIE_SPRITEID,
    ENEMYNINJA_SPRITEID
};

#endif