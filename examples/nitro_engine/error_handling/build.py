#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

import sys

argv = sys.argv

if '--debug' in argv:
    argv.remove('--debug') # Don't pass this to the build system
    defines_ = ['NE_DEBUG']
    libs_ = ['NE_debug', 'nds9d']
else:
    defines_ = []
    libs_ = ['NE', 'nds9']

arm9 = Arm9Binary(
    sourcedirs=['source'],
    defines=defines_,
    libs=libs_,
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDSEXT}/nitro-engine']
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9],
    game_title='NE: Animated model',
)
nds.generate_nds()

nds.run_command_line_arguments(args=argv)
