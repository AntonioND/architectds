#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
nitrofs.add_grit(['assets/robot'])
nitrofs.add_nitro_engine_md5(['assets/robot'])
nitrofs.add_nflib_bg_tiled(['assets/bg'], 'bg')
nitrofs.add_nflib_sprite_256(['assets/sprite'], 'sprite')
nitrofs.add_nflib_font(['assets/fnt'], 'fnt')
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['NE', 'nflib', 'nds9'],
    libdirs=[
        '${BLOCKSDS}/libs/libnds',
        '${BLOCKSDSEXT}/nitro-engine',
        '${BLOCKSDSEXT}/nflib'
    ]
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='NE: NFlib: Template',
)
nds.generate_nds()

nds.run_command_line_arguments()
