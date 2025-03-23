#!/bin/bash

# Based on https://github.com/mlpack/mlpack-wheels
# Based on https://gitlab.com/jason-rumengan/pyarma

# Ensure we have sudo if needed, but don't use it in CI environments
if [ -z "$use_sudo" ]; then
  if [ "$(id -u)" -ne 0 ] && [ -z "$CI" ] && [ -z "$GITHUB_ACTIONS" ]; then
    use_sudo="sudo"
  else
    use_sudo=""
  fi
fi

# Install OpenBLAS
basedir=$(python3 scripts/openblas_support.py)
if [ -d "$basedir/lib" ] && [ -d "$basedir/include" ]; then
  echo "OpenBLAS downloaded successfully to $basedir"
  $use_sudo mkdir -p /usr/local/lib /usr/local/include
  $use_sudo cp -r $basedir/lib/* /usr/local/lib
  $use_sudo cp $basedir/include/* /usr/local/include
else
  echo "Failed to download OpenBLAS or directory structure is unexpected"
  echo "Contents of basedir: $(ls -la $basedir)"
  exit 1
fi

# Build and install Armadillo from the submodule
echo "Building Armadillo from submodule..."
cd external/armadillo-code
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF .
make -j$(nproc)
$use_sudo make install
cd ../..

# Create a configuration file for the dynamic linker if we have sudo
if [ -n "$use_sudo" ]; then
  echo "Configuring dynamic linker..."
  echo "/usr/local/lib" | $use_sudo tee /etc/ld.so.conf.d/usr-local.conf
  $use_sudo ldconfig
else
  echo "Skipping ldconfig as we don't have sudo privileges"
  # Set library paths for the current session
  export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
fi

# Set library paths for the current session
export DYLD_FALLBACK_LIBRARY_PATH=/usr/local/lib/
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH

# Verify installation
echo "Verifying Armadillo installation..."
ls -la /usr/local/lib/libarmadillo*
