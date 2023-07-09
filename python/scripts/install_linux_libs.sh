#!/bin/bash

# Based on https://github.com/mlpack/mlpack-wheels
# Based on https://gitlab.com/jason-rumengan/pyarma

#basedir=$(python3 scripts/openblas_support.py)
#$use_sudo cp -r $basedir/lib/* /usr/local/lib
#$use_sudo cp $basedir/include/* /usr/local/include
#
#export DYLD_FALLBACK_LIBRARY_PATH=/usr/local/lib/

# Install Openblas
if $RUNNER_OS == "Linux"; then
    basedir=$(python tools/openblas_support.py)
    cp -r $basedir/lib/* /usr/local/lib
    cp $basedir/include/* /usr/local/include
elif [[ $RUNNER_OS == "Windows" ]]; then
    # delvewheel is the equivalent of delocate/auditwheel for windows.
    python -m pip install delvewheel

    # make the DLL available for tools/wheels/repair_windows.sh. If you change
    # this location you need to alter that script.
    mkdir -p /c/opt/openblas/openblas_dll

    PYTHONPATH=tools python -c "import openblas_support; openblas_support.make_init('numpy')"
    mkdir -p /c/opt/32/lib/pkgconfig
    mkdir -p /c/opt/64/lib/pkgconfig
    target=$(python -c "import tools.openblas_support as obs; plat=obs.get_plat(); ilp64=obs.get_ilp64(); target=f'openblas_{plat}.zip'; obs.download_openblas(target, plat, ilp64);print(target)")
    if [[ $PLATFORM == 'win-32' ]]; then
        # 32-bit openBLAS
        # Download 32 bit openBLAS and put it into c/opt/32/lib
        unzip -o -d /c/opt/ $target
        cp /c/opt/32/bin/*.dll /c/opt/openblas/openblas_dll
    else
        # 64-bit openBLAS
        unzip -o -d /c/opt/ $target
        if [[ -f /c/opt/64/lib/pkgconfig/openblas64.pc ]]; then
            # As of v0.3.23, the 64-bit interface has a openblas64.pc file,
            # but this is wrong. It should be openblas.pc
            cp /c/opt/64/lib/pkgconfig/openblas{64,}.pc
        fi
        cp /c/opt/64/bin/*.dll /c/opt/openblas/openblas_dll
    fi
fi