#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

import sys

argv = sys.argv

if '--debug' in argv:
    argv.remove('--debug') # Don't pass this to the build system
    defines_ = []
    libs_ = ['nds9d']
else:
    defines_ = ['NDEBUG']
    libs_ = ['nds9']

arm9 = Arm9Binary(
    sourcedirs=['source'],
    defines=defines_,
    libs=libs_,
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9],
    game_title='Debug and release builds',
)
nds.generate_nds()

nds.run_command_line_arguments(args=argv)
