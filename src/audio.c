#include <gb/gb.h>
#include "../include/hUGEDriver.h"
#include "cbtfx.h"
#include "audio.h"
#include "vars.h"

/// @brief Initializes audio functions. Sets audio registers and enables sound playback.
void initAudio()
{
    // Enable audio output by setting up the correct registers.
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x54;

    // Add sound update functions to VBlank
    __critical
    {
        hUGE_init(&bgm_rpgbattle);
        // add_VBL(hUGE_dosound);
        // add_VBL(CBTFX_update);
        add_VBL(updateAudio);
    }

    // Unmute hUGE Channels
    hUGE_mute_channel(HT_CH1, 0);
    hUGE_mute_channel(HT_CH2, 0);
    hUGE_mute_channel(HT_CH3, 0);
    hUGE_mute_channel(HT_CH4, 0);
}

/// @brief Mute all audio channels
void muteAudio()
{
    // Flush current register values
    NR52_REG = 0;

    hUGE_mute_channel(HT_CH1, 1);
    hUGE_mute_channel(HT_CH2, 1);
    hUGE_mute_channel(HT_CH3, 1);
    hUGE_mute_channel(HT_CH4, 1);
}

/// @brief Unmute all audio channels
void unmuteAudio()
{
    // Enable audio output
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x54;

    hUGE_mute_channel(HT_CH1, 0);
    hUGE_mute_channel(HT_CH2, 0);
    hUGE_mute_channel(HT_CH3, 0);
    hUGE_mute_channel(HT_CH4, 0);
}

/// @brief Remove audio update from VBlank
void disableAudio()
{
    __critical
    {
        remove_VBL(updateAudio);
    }
}

/// @brief Advance audio tick for playback
void updateAudio()
{
    if (gamestate != GAMESTATE_PAUSED)
    {
        hUGE_dosound();
    }
    CBTFX_update();
}