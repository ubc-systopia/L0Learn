#!/bin/bash

# Based on https://github.com/mlpack/mlpack-wheels
# Based on https://gitlab.com/jason-rumengan/pyarma

# Ensure we have sudo if needed
if [ -z "$use_sudo" ]; then
  if [ "$(id -u)" -ne 0 ]; then
    use_sudo="sudo"
  else
    use_sudo=""
  fi
fi

# Install OpenBLAS
basedir=$(python3 scripts/openblas_support.py)
$use_sudo cp -r $basedir/lib/* /usr/local/lib
$use_sudo cp $basedir/include/* /usr/local/include

# Build and install Armadillo from the submodule
echo "Building Armadillo from submodule..."
# Get the current directory
CURRENT_DIR=$(pwd)
echo "Current directory: $CURRENT_DIR"

# Check if we're in the cibuildwheel environment
if [ -d "/project/external/armadillo-code" ]; then
  echo "Using cibuildwheel paths"
  cd /project/external/armadillo-code
elif [ -d "$CURRENT_DIR/external/armadillo-code" ]; then
  echo "Using relative paths from current directory"
  cd $CURRENT_DIR/external/armadillo-code
else
  echo "Trying parent directory"
  cd ../external/armadillo-code
fi

echo "Building Armadillo in: $(pwd)"
cmake -DCMAKE_INSTALL_PREFIX=/usr/local .
make -j4
$use_sudo make install
cd $CURRENT_DIR

# Create a configuration file for the dynamic linker
echo "Configuring dynamic linker..."
echo "/usr/local/lib" | $use_sudo tee /etc/ld.so.conf.d/usr-local.conf
$use_sudo ldconfig

# Set library paths for the current session
export DYLD_FALLBACK_LIBRARY_PATH=/usr/local/lib/
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

# Verify installation
echo "Verifying Armadillo installation..."
ls -la /usr/local/lib/libarmadillo*
