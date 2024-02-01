Instructions
============

When switching between debug and release builds, the build system will detect
that the libraries and defines have changed and rebuild everything that has been
affected.

Build release ROM:

.. code:: python

    python3 build.py

Build debug ROM:

.. code:: python

    python3 build.py --debug
