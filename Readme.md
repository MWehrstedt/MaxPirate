# Max Pirate
A simple top down action game for the original Game Boy (DMG). Made with GBDK Version 4.0.5. Aims to run on original hardware. This code is not optimized, especially the tiles and tile management could be better. The self-imposed goal was to restrict myself to the base cartridge, no MBC.

You are a pirate captain who has just arrived to a small port town. But the locals you are not as lively as you expected them. Armed with your trusty anchor and cannon Bessie, you try to eliminate as many of them as you can!

![image](https://onedrive.live.com/embed?resid=72F9E0AC3DFC344D%21558572&authkey=%21ADiuifm16hKWbS0&width=320&height=288)
![image](https://onedrive.live.com/embed?resid=72F9E0AC3DFC344D%21558573&authkey=%21AKkSacSQ_k1xCwE&width=320&height=288)

# Controls

**D-Pad**: Move character

**A Button**: Use anchor (melee attack)

**B Button**: Shoot cannon

**Start Button**: Start/Pause game

# Compile
Adjust paths to GDBK and your favourite emulator if necessary and run the make file or `compile.bat`. You can use `compile.bat -nostart` To just compile the game.
# Credits

## Assets

Graphics by and based on [the GB Oracles assets by GibbonGL](https://gibbongl.itch.io/)

SFX and BGM by [beatscribe](https://twitter.com/beatscribe)

## Frameworks
BGM driver: [hUGEDriver](https://github.com/SuperDisk/hUGEDriver)

SFX driver: [CBT-FX](https://github.com/coffeevalenbat/CBT-FX/tree/main)

Made with [GBDK 2020 version 4.0.5](https://github.com/gbdk-2020/gbdk-2020)

# Current state
I consider it basically done. Now hardware testing and balancing.

# Tested on

⭕ - not yet ❌ - doesn't work without issues ✔️ - works

- ✔️ BGB emulator on Windows 11
- ✔️ DMG-01 (OG Game Boy)
- ⭕ Super Game Boy (PAL SNES)
- ✔️ MGB-001 (Pocket)
- ⭕ MGB-101 (Light)
- ⭕ CGB-001 (Color)
- ⭕ AGB-001 (Advance)
- ⭕ AGS-001 (Advance SP)
