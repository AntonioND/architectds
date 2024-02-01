#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['arm9/source', 'common/source'],
    includedirs=['common/include'],
    libs=['nds9', 'mm9'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod']
)
arm9.generate_elf()

arm7 = Arm7Binary(
    sourcedirs=['arm7/source', 'common/source'],
    includedirs=['common/include'],
    libs=['nds7', 'mm7', 'dswifi7'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod',
             '${BLOCKSDS}/libs/dswifi']
)
arm7.generate_elf()

nds = NdsRom(
    binaries=[arm9, arm7],
    game_title='ARM9 + ARM7',
)
nds.generate_nds()

nds.run_command_line_arguments()
