#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'mm9'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod']
)
arm9.add_mmutil(['audio'])
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9],
    game_title='maxmod example',
    game_subtitle='Audio as data',
)
nds.generate_nds()

nds.run_command_line_arguments()
