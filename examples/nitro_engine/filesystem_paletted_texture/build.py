#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
nitrofs.add_grit(['assets'])
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['NE', 'nds9'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/nitro-engine']
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='NE: FS: Paletted texture',
)
nds.generate_nds()

nds.run_command_line_arguments()
