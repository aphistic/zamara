#!/bin/sh

# Removes CMake related files to clean up the repo

find . -name "CMakeFiles" | xargs rm -rfv
find . -name "CMakeScripts" | xargs rm -rfv
find . -name "*.xcodeproj" | xargs rm -rfv
find . -name "*.build" | xargs rm -rfv
find . -name "Makefile" | xargs rm -rfv
find . -name "cmake_install.cmake" | xargs rm -rfv
find . -name "CMakeCache.txt" | xargs rm -rfv
find . -name "CTestTestfile.cmake" | xargs rm -rfv
rm -vrf Testing
