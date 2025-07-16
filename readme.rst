ArchitectDS
===========

This is a build system for NDS ROMs meant to be used with BlocksDS. It allows
you to easily define source directories, libraries, etc; and define the location
of assets and their destination (NitroFS or CPU data).

- ARM9 and ARM7 binaries can have a custom list of libraries, definitions and
  source code directories.

- If an ARM7 isn't defined, it will use the default ARM7 binary of BlocksDS.

- Assets such as images and audio files can be converted as part of the build
  process and added to NitroFS or the CPU binary as data.

- An arbitrary number of DSP binaries can be built, and they can be stored in
  NitroFS or in a CPU binary as data.

- Popular NDS libraries and tools are supported:

  - grit: Converted assets are saved as GRF files in NitroFS, or as binary files
    if they need to be added as data to a CPU binary as an array.

  - Maxmod: Soundbanks can be generated to NitroFS or added as data to the CPU.

  - NFlib: Assets are converted and saved to NitroFS. Shared palettes are
    supported.

  - Nitro Engine: Static and animated models are supported.

  - ptexconv: Used to generate textures in all different DS formats, with a helper
    function for Tex4x4.

  - libxm7, dswifi, gbajpg and other libraries that don't require special
    tooling are also supported.

Note that this is still an early version of the build system. If you need a
feature, or a suggestion, feel free to create issues in the repository.

For an example of using Nitro Engine, NFlib and libnds at the same time, check
`this example <examples/nitro_engine/using_nflib>`__.

For an example of using the DSP, check `this example <examples/libnds/dsp>`__.

For an example of debug/release builds, check `this example
<examples/libnds/debug_build>`__.

Dependencies
------------

You need to install Ninja and Python 3. In Ubuntu or Debian simply run:

.. code:: bash

    sudo apt install python3 ninja-build

Setup
-----

If you don't want to install it in your system, you can just copy the
``architectds`` folder to your project. Then, you will be able to import the module
with:

.. code:: python

    from architectds import *

If you want to install it in a virtual environment instead of copying the
folder, follow the steps below:

.. code:: bash

    # Create and activate venv
    sudo apt install python3-venv
    python3 -m venv env
    source env/bin/activate

    # Install dependencies
    pip3 install wheel setuptools

    # Create wheel
    python3 setup.py bdist_wheel

    # Install wheel
    pip3 install dist/architectds-*-py3-none-any.whl

If you want to install it in your system, you may find issues. Linux
distributions now disallow installing user packages in system folders. This is
done so that users don't break system libraries, but it affects all packages,
even the ones that your system doesn't depend on. This is discouraged, but you
can force the instalation with:

.. code:: bash

    # Install wheel
    pip3 install dist/architectds-*-py3-none-any.whl --break-system-packages

Examples
--------

There are lots of examples that show how to use most features. To build any of
the examples, run ``python3 build.py`` in the folder of the example.

- **gbajpeg/**:

  - ``load_from_nitrofs``: Load and decode a JPEG image from NitroFS.

  - ``load_from_ram``: Load and decode a JPEG image from RAM.

- **gl2d/**: Examples that use the GL2D library included with libnds.

  - ``sprite_set``: Generate a sprite set from multiple PNG files and add it to
    the ARM9 binary as data.

  - ``sprite_set_nitrofs``: Generate a sprite set from multiple PNG files and
    add it to NitroFS.

- **libnds/**: Examples with the default BlocksDS libraries.

  - ``all``: It shows how to do most things supported by libnds and other very
    common libraries:

    - DSP: One binary stored in NitroFS, one binary added to the ARM9 as data.
    - NitroFS: Graphics files converted with grit to GRF format, audio files
      converted with mmutil into a soundbank.
    - ARM9: Graphics files converted with grit and added as data. Data files
      added to the ARM9 binary. Audio files converted into a soundbank with
      mmutil and added to the ARM9 binary.
    - ARM7: With Maxmod and dswifi. Data files are added to it.
    - NDS: NitroFS directories. Custom ROM title, subtitles, and icon.

  - ``arm9``: Simple ROM with only a source file for the ARM9 and default ARM7.

  - ``arm9_arm7``: Example of developing custom ARM9 and ARM7 binaries.

  - ``arm9_nitrofs``: Simple ROM with only a source file for the ARM9, default
    ARM7, and NitroFS data files added to the filesystem by the developer.

  - ``dsp``: Example of loading DSP binaries from memory and NitroFS.

  - ``opengl``: Example of converting graphics and displaying them with OpenGL.

- **libxm7/**:

  - ``nitrofs``: Example that uses LibXM7 to play XM and MOD songs from NitroFS.
    It also shows how to use a different pre-built ARM7 core from BlocksDS and
    how to add regular files to NitroFS in a ROM without converting them.

  - ``play_songs``: Example that uses LibXM7 to play songs included in the ARM9
    binary as data.

- **maxmod/**:

  - ``audio_as_data``: Example of using Maxmod with ARM9 data as a soundbank.

  - ``audio_in_nitrofs``: Example of using Maxmod with a soundbank in NitroFS.

- **nflib/**: NFlib examples ported to ArchitectDS.

  - ``3dsprites``: Tiled backgrounds and 3D sprites.

  - ``collisions``: Multiple examples that show pixel-perfect collisions, as
    well as tile-based collisions.

  - **graphics/**:

    - ``affine``: Affine backgrounds with and without shared palettes.

    - ``animatedbg``: Animated tiled background.

    - ``backbuffer3``: 16 bit background.

    - ``bg``: Tiled backgrounds.

    - ``bg16bits``: 16 bit backgrounds.

    - ``bgmixed``: Tiled and 8 bit backgrounds. 256 color sprites. Custom fonts.

    - ``bgtiled_spr256``: Tiled backgrounds, 256 color sprites, 8 bit
      backgrounds with shared palettes.

  - ``textdemo``: Tiled backgrounds and custom fonts.

- **nitro_engine/**: Nitro Engine examples ported to ArchitectDS.

  - ``animated_model``: MD5 animated model and 16 bit texture converted with
    grit added to the ARM9 as binary data.

  - ``error_handling``: Shows how to have release and debug builds with debug
    messages.

  - ``filesystem_animated_model``: MD5 animated model and 16 bit texture
    converted with grit and added to NitroFS.

  - ``filesystem_compressed_texture``: Textures converted to Tex4x4 with ptexconv
    (with and without optionally specified arguments) and saved to NitroFS.

  - ``filesystem_paletted_texture``: Paletted textures converted with grit to
    GRF format and saved to NitroFS.

  - ``filesystem_simple_model``: OBJ static model and 16 bit texture converted
    with grit and added to NitroFS.

  - ``model_with_vertex_color``: OBJ static model with vertex color information.

  - ``paletted_texture``: Paletted textures converted with grit to GRF format
    and saved to the ARM9 as binary data.

  - ``sdroot_animated_model``: MD5 animated model and 16 bit texture converted
    with grit and stored in the SD card of a flashcard or the DSi SD slot.

  - ``simple_model``: OBJ static model and 16 bit texture converted with grit
    and added to the ARM9 as binary data.

  - ``specular_material``: OBJ static model and 16 bit texture converted with
    grit and added to the ARM9 as binary data.

Usage guide
-----------

With this build system you need to create an ``Arm9Binary`` object, with a list
of source code directories, defines, include directories, libraries (and things
like CFLAGS, ASFLAGS, CXXFLAGS and LDFLAGS). This object can take any number of
assets through some functions like ``add_data()``, ``add_grit()`` or
``add_tlf()``. Check the examples for more information.

By default, assets functions will use a default path as destination. To define a
custom output path in any of the functions that include assets, set ``out_dir``
to the desired path:

.. code:: python

    # This will use the default path:
    arm9.add_grit(['graphics/trees'])
    arm9.add_grit(['graphics/food'])

    # This will set a different path:
    arm9.add_grit(['graphics/animals'], 'graphics/animals')
    arm9.add_grit(['graphics/rocks'], 'graphics/rocks')

When you're happy with your ARM9 binary, you can do the same thing with an
``Arm7Binary`` object if you want a custom ARM7 binary. If you don't create one,
the default BlocksDS binary will be used. You can also add assets to this binary,
but it only makes sense to use ``add_data()``.

You can also create a ``NitroFS`` object. This object is only used for assets
that need to be converted. For folders that need to be added as they are, check
the ``NdsRom`` class below. The ``NitroFS`` object can take any number of
graphics files to be converted with ``grit`` or ``ptexconv``, audio files that
are converted with ``mmutil``, or even 3D models to be used with Nitro Engine.

A special note must be made for converting graphics with ptexconv: if you are using
the ``-fp`` option to specify a fixed palette, you must also pass ``-fpo`` to ensure
the fixed palette is output to the destination directory.

If you want to store your files in your SD card instead of the NitroFS
filesystem, you can create a ``FatFS`` object instead. It behaves the same way
as ``NitroFS``, but it will use your chosen folder as a root folder for the
generated files. You will need to copy them to your SD card yourself.

If you want to create DSP binaries, you need to create ``TeakBinary`` objects in
a similar way as ARM binaries.

Finally, once you have all your objects, you need to create an ``NdsRom``
object. This object takes a list of binaries (NitroFS, ARM9, ARM7, DSP) and adds
them to the ROM. It can also take a list of paths to directories to be added to
NitroFS right as they are without any modifications. All directories passed in
this list will be added to the root of the filesystem. If a file is found in
multiple trees it will cause an error.

As mentioned previously, if no ARM7 binary is added to the ROM, the default
BlocksDS binary will be used.

You can also define the header title and subtitles, and the game icon here.

Once your objects are ready, ``run_command_line_arguments()`` will check the
arguments passed to the python script:

- ``python3 build.py``: Create a ``ninja.build`` file and build the ROM.
  Equivalent to ``python3 build.py --build``.

- ``python3 build.py --clean``: Clean all build files.

- ``python3 build.py --compdb``: Generate a ``compile_commands.json`` file.

- ``python3 build.py --graph``: If you have ``graphviz`` installed in your
  system, this will generate a PNG file with the dependency graph of your
  project.

- ``python3 build.py --ninja``: Create a ``ninja.build`` file and exit.

Note that this is just a python script. At any point in the script you can check
``sys.argv`` for your own arguments and change the build definitions based on
them. The ``debug_build`` example in the ``libnds`` folder and the
``error_handling`` example in the ``nitro_engine`` folder use this to handle
debug and release builds differently in the same project.

Also, once you have the ``build.ninja`` file, if you want to invoke ``ninja`` by
itself without the wrapper script, make sure that you set the environment
variable ``BLOCKSDS`` to the path of your installation of BlocksDS (for example,
in Linux, ``export BLOCKSDS=/opt/blocksds/core``).
