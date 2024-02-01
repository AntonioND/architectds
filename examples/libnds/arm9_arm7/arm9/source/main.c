// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024

#include <stdio.h>
#include <time.h>

#include <nds.h>
#include <maxmod9.h>

#include "common.h"

int main(int argc, char **argv)
{
    // Setup sub screen for the text console
    consoleDemoInit();

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        uint16_t keys = keysHeld();

        if (keys & KEY_START)
            break;

        // Clear console
        printf("\x1b[2J");

        // Print current time
        char str[100];
        time_t t = time(NULL);
        struct tm *tmp = localtime(&t);
        if (strftime(str, sizeof(str), "%Y-%m-%dT%H:%M:%S%z", tmp) == 0)
            snprintf(str, sizeof(str), "Failed to get time");
        printf("%s\n\n", str);

        // Print some controls
        printf("START:  Exit to loader\n");
        printf("\n");
    }

    return 0;
}
