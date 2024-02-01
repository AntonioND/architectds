#!/usr/bin/env python3

# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

from architectds import *

teak1 = TeakBinary(
    name='teak1',
    sourcedirs=['teak/source1'],
)
teak1.generate_tlf()

teak2 = TeakBinary(
    name='teak2',
    sourcedirs=['teak/source2'],
)
teak2.generate_tlf()

nitrofs = NitroFS()
nitrofs.add_tlf(teak2)
nitrofs.add_grit(['nitrofs/graphics'])
# The header of the soundbank in NitroFS must be added as a dependency of the ARM9
nitrofs_soundbank_header = nitrofs.add_mmutil(['nitrofs/audio'])
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['arm9/source', 'common/source'],
    defines=[],
    includedirs=['common/include'],
    libs=['nds9', 'mm9'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod']
)
arm9.add_header_dependencies([nitrofs_soundbank_header])
arm9.add_data(['arm9/data'])
arm9.add_grit(['arm9/graphics'])
arm9.add_mmutil(['arm9/audio'])
arm9.add_tlf(teak1)
arm9.generate_elf()

arm7 = Arm7Binary(
    sourcedirs=['arm7/source', 'common/source'],
    defines=[],
    includedirs=['common/include'],
    libs=['nds7', 'mm7', 'dswifi7'],
    libdirs=['${BLOCKSDS}/libs/libnds', '${BLOCKSDS}/libs/maxmod',
             '${BLOCKSDS}/libs/dswifi']
)
arm7.add_data(['arm7/data'])
arm7.generate_elf()

nds = NdsRom(
    nitrofsdirs=['nitrofs/root'],
    # Note: If no ARM7 is specified, it uses the default one
    binaries=[teak1, teak2, arm9, arm7, nitrofs],
    nds_path='rom.nds',
    game_title='Python build system',
    game_subtitle='Built with BlocksDS',
    game_author='github.com/blocksds/sdk',
    game_icon='icon.bmp'
)
nds.generate_nds()

nds.run_command_line_arguments()
