#!/bin/bash

# Define variables
SOURCE_DIR="/home/jaden/Hamster"
BUILD_DIR="$SOURCE_DIR/cmake-build-debug"
CMAKE_EXEC="/home/jaden/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake"
C_COMPILER="/usr/bin/clang"
CXX_COMPILER="/usr/bin/clang++"
PY_MODULE="$BUILD_DIR/Hamster-Py/Hamster.cpython-310-x86_64-linux-gnu.so"  # Assuming this is the Python module output

# Clean previous build
# $CMAKE_EXEC --build $BUILD_DIR --target clean

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Configure the project with CMake, including pybind11 setup
$CMAKE_EXEC -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_C_COMPILER=$C_COMPILER \
            -DCMAKE_CXX_COMPILER=$CXX_COMPILER \
            -G "Ninja" \
            -S $SOURCE_DIR \
            -B $BUILD_DIR

# Build Hamster-Py (assuming it's a target in CMakeLists)
$CMAKE_EXEC --build $BUILD_DIR --target Hamster -j 6

# if [ $BUILD_STATUS -eq 0 ]; then
    # echo "Build successful"
# else
    # echo "Build failed with status $BUILD_STATUS"
    # exit $BUILD_STATUS
# fi
# Check if the Python module was created
if [ -f "$PY_MODULE" ]; then
    echo "Python module built successfully at $PY_MODULE"
else
    echo "Python module not found at $PY_MODULE"
fi
