#ifndef __VARS_H__
#define __VARS_H__

// DEFINES
#define HITBOX_TILESIZE         16
#define HITBOX_MAPSIZE_X        10
#define HITBOX_MAPSIZE_Y        9
#define HITBOX_OFFSET_X         4
#define HITBOX_OFFSET_Y         4

#define HITBOX_TYPE_SOLID       1
#define HITBOX_TYPE_DEATH       2

#define GAMESTATE_MAINMENU      1
#define GAMESTATE_PAUSED        2
#define GAMESTATE_PLAYING       3
#define GAMESTATE_DIEING        4

#define CAMERALOCK_RIGHT        175
#define CAMERALOCK_BOTTOM       184

#define HERO_FACING_LEFT        0b10000000
#define HERO_FACING_RIGHT       0b01000000
#define HERO_FACING_UP          0b00100000
#define HERO_FACING_DOWN        0b00010000

#define HERO_SPEED_LEFT         0b00001000
#define HERO_SPEED_RIGHT        0b00000100
#define HERO_SPEED_UP           0b00000010
#define HERO_SPEED_DOWN         0b00000001
#define HERO_SPEED_RESETMASK    0b00001111
#define HERO_SPEED              1

// Variables

/// Inputs for current frame
extern uint8_t joypadCurrent;
/// Inputs for last frame
extern uint8_t joypadPrevious;

extern int8_t targetTileIdTop;
extern int8_t targetTileIdCenter;
extern int8_t targetTileIdBottom;
extern int8_t iterator;
extern int8_t collision;
extern int8_t gamestate;

/// @brief Current horizontal hero position. Top left anchor.
extern uint8_t heroPositionX;
/// @brief Current vertical hero position. Top left anchor.
extern uint8_t heroPositionY;
extern uint8_t heroMovement;

/// @brief Init function for current Palace.
extern void (*currentPalaceInit)();

extern void (*currentLevelUpdate)();

/// @brief Loads hitmap and tile map for the room with id 'currentPalaceRoomId'
extern void (*currentPalaceLoadRoom)();

/// @brief Updates 'currentPalaceRoomId' after a warp and loads the proper room.
extern void (*currentPalaceLoadNextRoom)();

BANKREF_EXTERN(currentLevelHitboxes)
extern const uint8_t (*currentLevelHitboxes)[];

/// @brief Id for currently loaded room.
extern uint8_t currentPalaceRoomId;

/// @brief Id for currently loaded palace
extern uint8_t currentPalaceId;

BANKREF_EXTERN(currentLevelEnemies)
extern uint8_t currentLevelEnemies[6][6];


#endif