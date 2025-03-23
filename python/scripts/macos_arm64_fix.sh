#!/bin/bash

# Script to fix macOS arm64 build issues

# Set deployment target
export MACOSX_DEPLOYMENT_TARGET=10.15

# Detect architecture
ARCH=$(uname -m)
echo "Detected architecture: $ARCH"

# Install dependencies if needed
if [ ! -f "$(brew --prefix)/opt/openblas/lib/libopenblas.dylib" ]; then
    echo "Installing OpenBLAS via Homebrew..."
    brew install openblas
fi

# Set environment variables for OpenBLAS
export OPENBLAS=$(brew --prefix openblas)
export CFLAGS="-I$OPENBLAS/include $CFLAGS"
export CXXFLAGS="-I$OPENBLAS/include $CXXFLAGS"
export LDFLAGS="-L$OPENBLAS/lib $LDFLAGS"

# Create symbolic links if needed
mkdir -p /usr/local/lib /usr/local/include
ln -sf $OPENBLAS/lib/libopenblas.dylib /usr/local/lib/
ln -sf $OPENBLAS/include/cblas.h /usr/local/include/
ln -sf $OPENBLAS/include/lapacke.h /usr/local/include/

echo "macOS arm64 environment configured successfully"
