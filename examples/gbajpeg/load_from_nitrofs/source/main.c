// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2023

#include <stdio.h>
#include <stdlib.h>

#include <nds.h>
#include <filesystem.h>

#include <gba-jpeg-decode.h>

void wait_forever(void)
{
    while (1)
        swiWaitForVBlank();
}

void *file_load(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        perror("fopen");
        wait_forever();
    }

    int ret = fseek(f, 0, SEEK_END);
    if (ret != 0)
    {
        perror("fseek");
        wait_forever();
    }

    long size = ftell(f);
    if (size == -1)
    {
        perror("ftell");
        wait_forever();
    }

    rewind(f);

    void *buffer = malloc(size);
    if (buffer == NULL)
    {
        printf("malloc(): Not enough memory (%ld)\n", size);
        wait_forever();
    }

    size_t bytes = fread(buffer, 1, size, f);
    if (bytes != size)
    {
        printf("fread(%ld): %zu bytes read", size, bytes);
        wait_forever();
    }

    int res = fclose(f);
    if (res != 0)
    {
        perror("fclose");
        wait_forever();
    }

    return buffer;
}

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

    printf("Initializing NitroFS...\n");

    bool init_ok = nitroFSInit(NULL);
    if (!init_ok)
    {
        perror("nitroFSInit()");
        wait_forever();
    }

    printf("Loading JPEG file to RAM...\n");

    void *jpg_file = file_load("image.jpg");
    if (jpg_file == NULL)
    {
        printf("Failed to open file!");
        wait_forever();
    }

    printf("File loaded!\n");

    printf("Decoding image...\n");

    JPEG_DecompressImage(jpg_file, buffer, 256, 192);

    free(jpg_file);

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
