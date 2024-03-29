// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024
//
// This file is part of Nitro Engine

#include <NEMain.h>
#include <filesystem.h>

NE_Material *Material1, *Material2;
NE_Palette *Palette1, *Palette2;

void Draw3DScene(void)
{
    NE_2DViewInit();

    NE_2DDrawTexturedQuad(0, 0,
                          256, 192,
                          0, Material1);
}

void Draw3DScene2(void)
{
    NE_2DViewInit();

    NE_2DDrawTexturedQuad(64, 32,
                          64 + 128, 32 + 128,
                          0, Material2);
}

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

int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    // Init 3D mode
    NE_InitDual3D();
    NE_InitConsole();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\n");
        WaitLoop();
    }

    // Allocate objects
    Material1 = NE_MaterialCreate();
    Material2 = NE_MaterialCreate();
    Palette1 = NE_PaletteCreate();
    Palette2 = NE_PaletteCreate();

    int ret;

    ret = NE_MaterialTexLoadGRF(Material1, Palette1, NE_TEXGEN_TEXCOORD,
                                "grit/a3pal32_png.grf");
    if (ret == 0)
    {
        printf("Failed to load GRF 1\n");
        WaitLoop();
    }

    ret = NE_MaterialTexLoadGRF(Material2, Palette2, NE_TEXGEN_TEXCOORD,
                                "grit/a5pal8_png.grf");
    if (ret == 0)
    {
        printf("Failed to load GRF 2\n");
        WaitLoop();
    }

    while (1)
    {
        NE_WaitForVBL(0);

        NE_ProcessDual(Draw3DScene, Draw3DScene2);
    }

    return 0;
}
