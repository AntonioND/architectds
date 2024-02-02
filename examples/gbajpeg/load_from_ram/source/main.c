// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2023

#include <stdio.h>
#include <stdlib.h>

#include <nds.h>
#include <filesystem.h>

#include <gba-jpeg-decode.h>

#include "data/image_jpg.h"

uint16_t buffer[256 * 192];

int main(int argc, char **argv)
{
    consoleDemoInit();

    // Setup main screen as a 16-bit framebuffer
    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);

    printf("gbajpeg example\n");
    printf("===============\n");
    printf("\n");

    printf("Decoding JPEG file in RAM...\n");

    JPEG_DecompressImage(image_jpg, buffer, 256, 192);

    printf("Image decoded!\n");

    // Flush the cache before doing a DMA copy
    DC_FlushRange(buffer, sizeof(buffer));
    dmaCopyWords(3, buffer, VRAM_A, sizeof(buffer));

    printf("\n");
    printf("Press START to exit to loader");

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();
        if (keysDown() & KEY_START)
            break;
    }

    return 0;
}
