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
if($ENV{CIBUILDWHEEL} OR DEFINED ENV{CI})
    set(ALLOW_OPENBLAS_MACOS ON CACHE BOOL "Allow detection of OpenBLAS on macOS" FORCE)
    target_compile_definitions(armadillo PRIVATE -DARMA_USE_LAPACK)
    target_compile_definitions(armadillo PRIVATE -DARMA_USE_BLAS)
endif()

# Ensure Armadillo can find BLAS and LAPACK
if(UNIX AND NOT APPLE)
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
    target_link_libraries(armadillo PRIVATE ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
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
