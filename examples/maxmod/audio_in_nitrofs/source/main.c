// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024

#include <stdio.h>

#include <filesystem.h>
#include <nds.h>
#include <maxmod9.h>

#include "nitrofs/soundbank_info.h"

__attribute__((noreturn)) void WaitLoop(void)
{
    printf("Press START to exit");
    while (1)
    {
        swiWaitForVBlank();
        scanKeys();
        if (keysHeld() & KEY_START)
            exit(0);
    }
}

int main(int argc, char **argv)
{
    // Setup sub screen for the text console
    consoleDemoInit();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\n");
        WaitLoop();
    }

    // Setup sound bank
    mmInitDefault("maxmod/soundbank.bin");

    // load the module
    mmLoad(MOD_JOINT_PEOPLE);

    // load sound effects
    mmLoadEffect(SFX_FIRE_EXPLOSION);

    // Start playing module
    mmStart(MOD_JOINT_PEOPLE, MM_PLAY_LOOP);

    // Clear console
    printf("\x1b[2J");

    printf("Maxmod demo\n");
    printf("===========\n");
    printf("\n");
    printf("A:     Play SFX\n");
    printf("START: Exit to loader\n");
    printf("\n");

    while (1)
    {
        // Synchronize game loop to the screen refresh
        swiWaitForVBlank();

        // Print some text in the demo console
        // -----------------------------------

        // Handle user input
        // -----------------

        scanKeys();

        uint16_t keys = keysHeld();
        uint16_t keys_down = keysDown();

        if (keys_down & KEY_A)
            mmEffect(SFX_FIRE_EXPLOSION);

        if (keys & KEY_START)
            break;
    }

    return 0;
}
