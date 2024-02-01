#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['source'],
)
arm9.add_grit(['graphics'])
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9],
    game_title='OpenGL example',
)
nds.generate_nds()

nds.run_command_line_arguments()
