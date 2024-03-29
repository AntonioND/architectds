// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2011, 2019, 2022
//
// This file is part of Nitro Engine

#include <stdbool.h>
#include <filesystem.h>
#include <NEMain.h>

NE_Camera *Camera;
NE_Model *Model;
NE_Animation *Animation;
NE_Material *Material;

void Draw3DScene(void)
{
    NE_CameraUse(Camera);

    NE_PolyFormat(31, 0, NE_LIGHT_0, NE_CULL_NONE, 0);
    NE_ModelDraw(Model);
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

    NE_Init3D();
    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\n");
        WaitLoop();
    }

    // Allocate space for objects...
    Model = NE_ModelCreate(NE_Animated);
    Camera = NE_CameraCreate();
    Material = NE_MaterialCreate();
    Animation = NE_AnimationCreate();

    // Setup camera
    NE_CameraSet(Camera,
                 6, 3, -4,
                 0, 3, 0,
                 0, 1, 0);

    if (NE_ModelLoadDSMFAT(Model, "models/robot.dsm") == 0)
    {
        printf("Couldn't load model...");
        WaitLoop();
    }

    if (NE_AnimationLoadFAT(Animation, "models/robot_wave.dsa") == 0)
    {
        printf("Couldn't load animation...");
        WaitLoop();
    }

    if (NE_MaterialTexLoadGRF(Material, NULL, NE_TEXGEN_TEXCOORD,
                              "grit/robot_png.grf") == 0)
    {
        printf("Failed to load GRF\n");
        WaitLoop();
    }

    // Assign material to the model
    NE_ModelSetMaterial(Model, Material);

    NE_ModelSetAnimation(Model, Animation);
    NE_ModelAnimStart(Model, NE_ANIM_LOOP, floattof32(0.1));

    NE_LightSet(0, NE_White, 0, -1, -1);

    NE_ClearColorSet(NE_Black, 31, 63);

    printf("\x1b[0;0HPad: Rotate\nSTART: Exit");

    while (1)
    {
        NE_WaitForVBL(NE_UPDATE_ANIMATIONS);

        scanKeys();
        uint32_t keys = keysHeld();

        if (keys & KEY_START)
            break;

        if (keys & KEY_RIGHT)
            NE_ModelRotate(Model, 0, 2, 0);
        if (keys & KEY_LEFT)
            NE_ModelRotate(Model, 0, -2, 0);
        if (keys & KEY_UP)
            NE_ModelRotate(Model, 0, 0, 2);
        if (keys & KEY_DOWN)
            NE_ModelRotate(Model, 0, 0, -2);

        // Draw scene...
        NE_Process(Draw3DScene);
    }

    return 0;
}
