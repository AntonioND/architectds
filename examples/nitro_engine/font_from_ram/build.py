#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['NE', 'dsf', 'nds9'],
    libdirs=[
        '${BLOCKSDS}/libs/libnds',
        '${BLOCKSDSEXT}/libdsf',
        '${BLOCKSDSEXT}/nitro-engine'
    ]
)
arm9.add_grit(['graphics'], out_dir='fonts')
arm9.add_bmfont_fnt(['data'], out_dir='fonts')
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9],
    game_title='DSF: NE: BMFont for NDS',
)
nds.generate_nds()

nds.run_command_line_arguments()
