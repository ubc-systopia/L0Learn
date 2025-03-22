#!/bin/bash

# Based on https://github.com/mlpack/mlpack-wheels
# Based on https://gitlab.com/jason-rumengan/pyarma

# Install OpenBLAS
basedir=$(python3 scripts/openblas_support.py)
$use_sudo cp -r $basedir/lib/* /usr/local/lib
$use_sudo cp $basedir/include/* /usr/local/include

# Build and install Armadillo from the submodule
cd external/armadillo-code
cmake -DCMAKE_INSTALL_PREFIX=/usr/local .
make -j4
$use_sudo make install
cd ../..

# Set library paths
export DYLD_FALLBACK_LIBRARY_PATH=/usr/local/lib/
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH
