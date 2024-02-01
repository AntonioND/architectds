// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024
//
// This file is part of Nitro Engine

#include <stdbool.h>
#include <filesystem.h>
#include <NEMain.h>

#include "ptexconv/grill_png_idx_bin.h"
#include "ptexconv/grill_png_pal_bin.h"
#include "ptexconv/grill_png_tex_bin.h"

NE_Material *Material1, *Material2;
NE_Palette *Palette1, *Palette2;

void Draw3DScene1(void)
{
    NE_ClearColorSet(RGB15(5, 5, 10), 31, 63);

    NE_2DViewInit();

    NE_2DDrawTexturedQuad(32, 32,
                          32 + 128, 32 + 128,
                          0, Material1);
}

void Draw3DScene2(void)
{
    NE_ClearColorSet(RGB15(10, 5, 0), 31, 63);

    NE_2DViewInit();

    NE_2DDrawTexturedQuad(64, 0,
                          64 + 128, 0 + 128,
                          0, Material2);
}

int main(void)
{
    // Init console in non-3D screen
    consoleDemoInit();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\nPress START to exit");
        while(1)
        {
            swiWaitForVBlank();
            scanKeys();
            if (keysHeld() & KEY_START)
                return 0;
        }
    }

    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    NE_InitDual3D();

    // Allocate objects
    Material1 = NE_MaterialCreate();
    Material2 = NE_MaterialCreate();
    Palette1 = NE_PaletteCreate();
    Palette2 = NE_PaletteCreate();

    NE_MaterialTex4x4Load(Material1, 128, 128, NE_TEXGEN_TEXCOORD,
                          grill_png_tex_bin, grill_png_idx_bin);
    NE_PaletteLoad(Palette1, grill_png_pal_bin, grill_png_pal_bin_size / 2,
                   NE_TEX4X4);
    NE_MaterialSetPalette(Material1, Palette1);


    NE_MaterialTex4x4LoadFAT(Material2, 128, 128, NE_TEXGEN_TEXCOORD,
                             "ptexconv/landscape_jpg_tex.bin",
                             "ptexconv/landscape_jpg_idx.bin");
    NE_PaletteLoadFAT(Palette2, "ptexconv/landscape_jpg_pal.bin", NE_TEX4X4);
    NE_MaterialSetPalette(Material2, Palette2);

    while (1)
    {
        NE_WaitForVBL(0);

        NE_ProcessDual(Draw3DScene1, Draw3DScene2);
    }

    return 0;
}
