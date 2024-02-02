#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'gbajpeg'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/gbajpeg']
)
arm9.generate_elf()

nds = NdsRom(
    nitrofsdirs=['nitrofs'],
    binaries=[arm9],
    game_title='gbajpeg example',
    game_subtitle='Load from NitroFS',
)
nds.generate_nds()

nds.run_command_line_arguments()

