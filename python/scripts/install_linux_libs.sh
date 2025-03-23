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

# Clean up any existing CMake cache files
echo "Cleaning up any existing CMake cache files..."
rm -f CMakeCache.txt
rm -rf CMakeFiles

# Run CMake from scratch
echo "Running CMake..."
cmake -DCMAKE_INSTALL_PREFIX=/usr/local . -DCMAKE_BUILD_TYPE=Release
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
if [ -f /usr/local/lib/libarmadillo.so ] || [ -f /usr/local/lib64/libarmadillo.so ]; then
  echo "Armadillo library found!"
  if [ -f /usr/local/lib/libarmadillo.so ]; then
    ls -la /usr/local/lib/libarmadillo*
  fi
  if [ -f /usr/local/lib64/libarmadillo.so ]; then
    ls -la /usr/local/lib64/libarmadillo*
    # Create symlinks in /usr/local/lib if the library is in lib64
    if [ ! -f /usr/local/lib/libarmadillo.so ]; then
      echo "Creating symlinks in /usr/local/lib..."
      $use_sudo mkdir -p /usr/local/lib
      $use_sudo ln -sf /usr/local/lib64/libarmadillo.so.* /usr/local/lib/
      $use_sudo ln -sf /usr/local/lib64/libarmadillo.so /usr/local/lib/
      ls -la /usr/local/lib/libarmadillo*
    fi
  fi
else
  echo "Error: Armadillo library not found in /usr/local/lib or /usr/local/lib64"
  exit 1
fi
