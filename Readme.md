# Pocket Zombies
A simple top down action game for the original Game Boy (DMG). Made with GBDK Version 4.0.5. Aims to run on original hardware. This code is not optimized, especially the tiles and tile management could be better.

The self-imposed goal was to restrict myself to the base cartridge, no MBC. 

![image](https://onedrive.live.com/embed?resid=72F9E0AC3DFC344D%21558437&authkey=%21AM0Y2o9aiRn_AZ8&width=637&height=577)
![image](https://onedrive.live.com/embed?resid=72F9E0AC3DFC344D%21558435&authkey=%21AHn7upuRRB2_9_8&width=638&height=575)
![image](https://onedrive.live.com/embed?resid=72F9E0AC3DFC344D%21558436&authkey=%21AMetzUjHGYDHXXI&width=638&height=574)

## Compile
Adjust paths to GDBK and your favourite emulator if necessary and run the make file or `compile.bat`. You can use `compile.bat -nostart` To just compile the game.
## Credits

### Assets

Graphics by and based on [the GB Orables assets by GibbonGL](https://gibbongl.itch.io/)

SFX and BGM by [beatscribe](https://twitter.com/beatscribe)

Akuma is a trademark of Capcom

### Frameworks
BGM driver: [hUGEDriver](https://github.com/SuperDisk/hUGEDriver)

SFX driver: [CBT-FX](https://github.com/coffeevalenbat/CBT-FX/tree/main)

Made with [GBDK 2020 version 4.0.5](https://github.com/gbdk-2020/gbdk-2020)

## Current state
Most of it is done, it just needs a bit more polishing (some sprites show where they aren't supposed to, some sfx are missing) and then hardware testing.

# Tested on

⭕ - not yet ❌ - doesn't work without issues ✔️ - works

- ⭕ BGB emulator on Windows 11
- ⭕ DMG-01 (OG Game Boy)
- ⭕ MGB-001 (Pocket)
- ⭕ MGB-101 (Light)
- ⭕ CGB-001 (Color)
- ⭕ AGB-001 (Advance)
- ⭕ AGS-001 (Advance SP)
