#ifndef __HERO_H__
#define __HERO_H__

/// @brief Draw and animate hero sprite
void drawHero();

/// @brief Main hero routine
void updateHero();

/// @brief Handle knockback during hitstate
void handleHitstate();

/// @brief Main weapon routine
void updateWeapon();
#endif