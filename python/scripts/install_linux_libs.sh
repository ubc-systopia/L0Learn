#!/bin/bash

# Based on https://github.com/mlpack/mlpack-wheels
# Based on https://gitlab.com/jason-rumengan/pyarma

set -ex

# Check if we're running in a CI environment and need sudo
if [ -n "$CI" ]; then
  SUDO="sudo"
else
  SUDO=""
fi

# Download and install OpenBLAS
echo "Downloading OpenBLAS..."
basedir=$(python3 scripts/openblas_support.py)
echo "OpenBLAS downloaded to $basedir"

# Create directories if they don't exist
$SUDO mkdir -p /usr/local/lib/cmake
$SUDO mkdir -p /usr/local/lib/pkgconfig
$SUDO mkdir -p /usr/local/include

# Copy OpenBLAS files
echo "Copying OpenBLAS files to /usr/local/..."
$SUDO cp -r $basedir/lib/* /usr/local/lib/
$SUDO cp -r $basedir/include/* /usr/local/include/

# Set environment variables
export DYLD_FALLBACK_LIBRARY_PATH=/usr/local/lib/
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

# Create symlinks for Armadillo
echo "Creating symlinks for Armadillo..."
cd python/external/armadillo-code
$SUDO ln -sf /usr/local/lib/libopenblas.so /usr/local/lib/libblas.so
$SUDO ln -sf /usr/local/lib/libopenblas.so /usr/local/lib/liblapack.so

# Set environment variables for Armadillo
export ARMA_USE_LAPACK=1
export ARMA_USE_BLAS=1

echo "Installation completed successfully"
