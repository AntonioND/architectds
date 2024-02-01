// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024

#include <stdio.h>

#include <nds.h>

int main(int argc, char **argv)
{
    consoleDemoInit();

    printf("sassert() test\n\n");

    // The values passed to this function are out of range, and they should
    // cause an assertion to fail.

    glFogColor(54, 30, 12, 70);

    // In a debug build this point will never be reached.

    printf("This is a release build.\n");
    printf("No sassert() will be checked\n\n");

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
