#!/bin/bash

# Define variables
SOURCE_DIR="/home/jaden/Hamster"
BUILD_DIR="$SOURCE_DIR/cmake-build-debug"
CMAKE_EXEC="/home/jaden/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake"
C_COMPILER="/usr/bin/clang"
CXX_COMPILER="/usr/bin/clang++"
EXECUTABLE="$BUILD_DIR/Hamster-Wheel/Hamster-Wheel"  # Update this path if needed


$CMAKE_EXEC --build $BUILD_DIR --target clean

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Configure the project with CMake
$CMAKE_EXEC -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_C_COMPILER=$C_COMPILER \
            -DCMAKE_CXX_COMPILER=$CXX_COMPILER \
            -G "Ninja" \
            -S $SOURCE_DIR \
            -B $BUILD_DIR

# Build the project using Ninja
$CMAKE_EXEC --build $BUILD_DIR --target Hamster-Wheel -j 6

# Optional: Clean up old build files

 if [ -f "$EXECUTABLE" ]; then
       echo "Running the executable..."
           "$EXECUTABLE"
         else
               echo "Executable not found at $EXECUTABLE"
 fi
