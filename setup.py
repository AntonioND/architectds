import os

from setuptools import setup
from architectds import __author__, __version__

def read_file(name):
    return open(os.path.join(os.path.dirname(__file__), name)).read()

setup(
    name = 'architectds',
    version = __version__,
    author = __author__,
    description = (
        'A high-level build system for Nintendo DS homebrew that generates '
        'files for the ninja build system.'
    ),
    license = 'MIT',
    url = 'https://github.com/blocksds/architectds',
    packages = ['architectds'],
    long_description=read_file('readme.rst'),
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
    ],
)
