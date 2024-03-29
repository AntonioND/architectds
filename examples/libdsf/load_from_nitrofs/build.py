#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
nitrofs.add_grit(['fonts'], out_dir='fonts')
nitrofs.add_bmfont_fnt(['fonts'], out_dir='fonts')
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'dsf'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/libdsf']
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='DSF: BMFont for NDS',
)
nds.generate_nds()

nds.run_command_line_arguments()
