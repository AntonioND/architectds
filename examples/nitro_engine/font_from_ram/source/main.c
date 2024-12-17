// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2024

#include <stdio.h>

#include <nds.h>
#include <NEMain.h>

#include "fonts/font_fnt.h"
#include "fonts/font_16_png.h"
#include "fonts/font_256_png.h"

NE_Sprite *TextSprite;

void Draw3DScene(void)
{
    NE_ClearColorSet(RGB15(0, 7, 7), 31, 63);

    NE_2DViewInit();

    NE_RichTextRender3D(3, "VAWATa\ntajl", 0, 0);

    NE_RichTextRender3DAlpha(2, "Text with alpha", 10, 80,
                             POLY_ALPHA(20) | POLY_CULL_BACK, 30);
}

void Draw3DScene2(void)
{
    NE_ClearColorSet(RGB15(7, 0, 7), 31, 63);

    NE_2DViewInit();

    NE_SpriteSetPos(TextSprite, 16, 32);
    NE_SpriteDraw(TextSprite);
}

int main(void)
{
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    // Init 3D mode
    NE_InitDual3D();
    NE_InitConsole();

    // Load a 16-color font to be used for rendering text as quads

    NE_RichTextInit(2);
    NE_RichTextMetadataLoadMemory(2, font_fnt, font_fnt_size);

    {
        NE_Material *Font16 = NE_MaterialCreate();
        NE_MaterialTexLoad(Font16, NE_PAL16, 256, 256,
                           NE_TEXGEN_TEXCOORD | NE_TEXTURE_COLOR0_TRANSPARENT,
                           font_16_pngBitmap);

        NE_Palette *Pal16 = NE_PaletteCreate();
        NE_PaletteLoad(Pal16, font_16_pngPal, 16, NE_PAL16);

        NE_MaterialSetPalette(Font16, Pal16);

        NE_RichTextMaterialSet(2, Font16, Pal16);
    }

    // Load a 256-color font to be used for rendering text as quads

    NE_RichTextInit(3);
    NE_RichTextMetadataLoadMemory(3, font_fnt, font_fnt_size);

    {
        NE_Material *Font256 = NE_MaterialCreate();
        NE_MaterialTexLoad(Font256, NE_PAL256, 256, 256,
                           NE_TEXGEN_TEXCOORD | NE_TEXTURE_COLOR0_TRANSPARENT,
                           font_256_pngBitmap);

        NE_Palette *Pal256 = NE_PaletteCreate();
        NE_PaletteLoad(Pal256, font_256_pngPal, 256, NE_PAL256);

        NE_MaterialSetPalette(Font256, Pal256);

        NE_RichTextMaterialSet(3, Font256, Pal256);
    }

    // Load a 16-color font to be used for rendering text to textures.

    NE_RichTextInit(5);
    NE_RichTextMetadataLoadMemory(5, font_fnt, font_fnt_size);
    NE_RichTextBitmapSet(5, font_16_pngBitmap, 256, 256, NE_PAL16,
                         font_16_pngPal, font_16_pngPalLen);

    // Render text to a texture using the last font we've loaded

    // We don't care about managing the palette. Passing NULL will tell Nitro
    // Engine to delete the palete automatically when the material is deleted.
    NE_Material *Material = NULL;
    NE_RichTextRenderMaterial(5,
                "Sample: AWAV.\nÿ_ßðñÑü(o´Áá)|\nInvalid char: ŋ",
                &Material, NULL);

    // Create a sprite to be used to render the texture we've rendered

    TextSprite = NE_SpriteCreate();
    NE_SpriteSetMaterial(TextSprite, Material);

    while (1)
    {
        NE_WaitForVBL(0);

        NE_ProcessDual(Draw3DScene, Draw3DScene2);

        scanKeys();
        if (keysHeld() & KEY_START)
            break;
    }

    NE_SpriteDelete(TextSprite);
    NE_MaterialDelete(Material);

    NE_RichTextEnd(2);
    NE_RichTextEnd(3);
    NE_RichTextEnd(5);

    return 0;
}
