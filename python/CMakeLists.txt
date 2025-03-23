cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF (NOT DEFINED L0LEARN_VERSION_INFO)
    SET(L0LEARN_VERSION_INFO "0.0.0")
ENDIF ()

SET(MODNAME "fastsparsegams")

PROJECT(
        ${MODNAME}
        VERSION ${L0LEARN_VERSION_INFO}
        DESCRIPTION "Python bindings for L0Learn CD and CDPSI optimization."
        LANGUAGES CXX
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "build shared library" FORCE)

ADD_SUBDIRECTORY(external/pybind11)
ADD_SUBDIRECTORY(external/armadillo-code)
ADD_SUBDIRECTORY(external/carma)

# Add Armadillo and pybind11
if($ENV{CIBUILDWHEEL})
    set(ALLOW_OPENBLAS_MACOS ON CACHE BOOL "Allow detection of OpenBLAS on macOS" FORCE)
    target_compile_definitions(armadillo PRIVATE -DARMA_USE_LAPACK)
    target_compile_definitions(armadillo PRIVATE -DARMA_USE_BLAS)
    
    # Add specific flags for macOS
    if(APPLE)
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version" FORCE)
        
        # Detect architecture
        execute_process(
            COMMAND uname -m
            OUTPUT_VARIABLE ARCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        
        # Set architecture-specific flags
        if(ARCH STREQUAL "arm64")
            set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS" FORCE)
        else()
            set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for macOS" FORCE)
        endif()
    endif()
endif()

INCLUDE_DIRECTORIES(fastsparsegams)
INCLUDE_DIRECTORIES(fastsparsegams/src)
INCLUDE_DIRECTORIES(fastsparsegams/src/include)

pybind11_add_module(${MODNAME} MODULE
        fastsparsegams/pyl0learn.cpp
        fastsparsegams/src/Normalize.cpp)

TARGET_LINK_LIBRARIES(${MODNAME} PRIVATE carma::carma)
TARGET_LINK_LIBRARIES(${MODNAME} PRIVATE armadillo)

# Add -fPIC for Armadillo (and OpenBLAS if compiled)
if(NOT MSVC)
    # clang on Windows does not support -fPIC
    if(NOT WIN32)
        target_compile_options(armadillo PRIVATE -fPIC)
    endif()
endif()

TARGET_INCLUDE_DIRECTORIES(${MODNAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

TARGET_COMPILE_OPTIONS(${MODNAME}
        PUBLIC
        "$<$<CONFIG:RELEASE>:${PROJECT_RELEASE_FLAGS}>"
        )

TARGET_COMPILE_DEFINITIONS(${MODNAME}
        PUBLIC
        "$<$<CONFIG:RELEASE>:${PROJECT_RELEASE_DEFINITIONS}>"
        )


INSTALL(TARGETS ${MODNAME} DESTINATION .)
