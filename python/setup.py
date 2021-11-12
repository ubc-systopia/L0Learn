#!/usr/bin/python3

import os
from setuptools import setup, Extension, find_packages
import numpy as np

try:
    from Cython.Build import cythonize
except ImportError:
    cythonize = None

try:
    from psutil import cpu_count

    psutil_found = True
except ImportError:
    psutil_found = False

from Cython.Distutils import build_ext


# https://cython.readthedocs.io/en/latest/src/userguide/source_files_and_compilation.html#distributing-cython-modules
def no_cythonize(extensions, **_ignore):
    for extension in extensions:
        sources = []
        for sfile in extension.sources:
            path, ext = os.path.splitext(sfile)
            if ext in (".pyx", ".py"):
                if extension.language == "c++":
                    ext = ".cpp"
                else:
                    ext = ".c"
                sfile = path + ext
            sources.append(sfile)
        extension.sources[:] = sources
    return extensions


if psutil_found:
    os.environ["CMAKE_BUILD_PARALLEL_LEVEL"] = str(cpu_count(logical=False))

extensions = [
    Extension(name='l0learn.cyarma',
              sources=["l0learn/cyarma.pyx"],
              include_dirs=['.', np.get_include()],
              language="c++",
              libraries=["armadillo", "lapack", "blas"],
              extra_compile_args=["-std=c++11"],
              extra_link_args=["-std=c++11"],
              ),
    Extension(name='l0learn.testing_utils',
              sources=["l0learn/testing_utils.pyx"],
              include_dirs=['.', np.get_include()],
              language="c++",
              libraries=["armadillo", "lapack", "blas"],
              extra_compile_args=["-std=c++11"],
              extra_link_args=["-std=c++11"],
              ),
    Extension(name="l0learn.interface",
              sources=["l0learn/interface.pyx",
                       "l0learn/src/CDL012LogisticSwaps.cpp",
                       "l0learn/src/Grid2D.cpp",
                       "l0learn/src/CDL012SquaredHingeSwaps.cpp",
                       "l0learn/src/Normalize.cpp",
                       "l0learn/src/CDL012Swaps.cpp",
                       "l0learn/src/Grid.cpp",
                       "l0learn/src/Grid1D.cpp"
                       ],
              include_dirs=['.', np.get_include(), "l0learn/src/include"],
              language="c++",
              libraries=["armadillo", "lapack", "blas"],
              extra_compile_args=["-std=c++11"],
              extra_link_args=["-std=c++11"]),
]

CYTHONIZE = bool(int(os.getenv("CYTHONIZE", 0))) and cythonize is not None
if True:
    compiler_directives = {"language_level": 3, "embedsignature": True}
    extensions = cythonize(extensions, compiler_directives=compiler_directives)
else:
    extensions = no_cythonize(extensions)

"""
Installation Notes;
How to ensure proper underlying armadillo is installed?
    MacOsX: brew install armadillo --with-hdf5
"""

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setup(
    name='l0learn',
    maintainer='Tim Nonet',
    author_email="tim.nonet@gmail.com",
    description="L0Learn is a highly efficient framework for solving L0-regularized learning problems.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/hazimehh/L0Learn",
    project_urls={
        "Bug Tracker": "https://github.com/hazimehh/L0Learn/issues",
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    cmdclass={'build_ext': build_ext},
    ext_modules=extensions,
    # package_dir={"": "l0learn"},
    # packages=find_packages(where="l0learn"),
    python_requires=">=3.6",
)
