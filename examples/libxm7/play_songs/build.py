#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['arm9/source'],
    libs=['nds9', 'xm79'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/libxm7']
)
arm9.add_data(['music'])
arm9.generate_elf()

arm7 = Arm7Binary(
    sourcedirs=['arm7/source'],
    libs=['nds7', 'xm77', 'dswifi7'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/libxm7',
             '${BLOCKSDS}/libs/dswifi']
)
arm7.generate_elf()

nds = NdsRom(
    binaries=[arm9, arm7],
    game_title='LIBXM7 example',
    game_subtitle='how to use LIBXM7',
    game_author='(sverx, 2009-01-07)'
)
nds.generate_nds()

nds.run_command_line_arguments()

