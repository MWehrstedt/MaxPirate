#ifndef __COLLISION_H__
#define __COLLISION_H__

/// @brief Handle hero collisions with current level hitmaps
void getCollisions();

/// @brief Get tile from current hitmap based on position. Sets `targetTileLeft`, `targetTileRight`, `targetTileUp` and `targetTileDown` based on directions given.
/// @param direction Direction flags
/// @param x x position in pixels
/// @param y y position in pixels
/// @param speed entity speed
void checkCollisionBackground(uint8_t direction, uint8_t x, uint8_t y, uint8_t speed);
#endif