#ifndef __HERO_H__
#define __HERO_H__

BANKREF_EXTERN(drawHero)
void drawHero() NONBANKED;

BANKREF_EXTERN(checkCollision)
void checkCollision() NONBANKED;

BANKREF_EXTERN(updateHero)
void updateHero() NONBANKED;
#endif