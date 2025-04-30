#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024-2025

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'xm79'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/libxm7']
)
arm9.generate_elf()

arm7 = Arm7BinaryDefault(
    elf_path='${BLOCKSDS}/sys/arm7/main_core/arm7_libxm7.elf'
)

nds = NdsRom(
    binaries=[arm9, arm7],
    nitrofsdirs=['nitrofs'],
    game_title='NitroFS example',
    game_subtitle='LibXM7',
    game_author='(sverx, 2009-01-07)'
)
nds.generate_nds()

nds.run_command_line_arguments()
