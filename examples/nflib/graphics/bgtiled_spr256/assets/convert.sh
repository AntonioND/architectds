#!/bin/sh

# The two backgrounds that share the palette have been edited to use 128 colors
# each, so that the final combined palette is 256 colors in size.
/opt/blocksds/core/tools/grit/grit img8b_1.png img8b_2.png -ftB -fh! -gTFF00FF -gb -gB8 -pS -Oimg8b_1.pal

# This is required or the library will say that the second background doesn't
# have a palette.
cp img8b_1.pal img8b_2.pal

mkdir -p ../nitrofs/root/bg
mv *.pal *.img ../nitrofs/root/bg
