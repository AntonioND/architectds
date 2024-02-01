#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

nitrofs = NitroFS()
# The header of the soundbank in NitroFS must be added as a dependency of the ARM9
nitrofs_soundbank_header = nitrofs.add_mmutil(['audio'])
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['source'],
    libs=['nds9', 'mm9'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod']
)
arm9.add_header_dependencies([nitrofs_soundbank_header])
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='maxmod example',
    game_subtitle='Audio in NitroFS',
)
nds.generate_nds()

nds.run_command_line_arguments()

