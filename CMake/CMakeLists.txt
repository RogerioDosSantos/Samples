cmake_minimum_required (VERSION 2.8)

# about this project
# ------------------

project (Tutorial)
SET(Tutorial_VERSION_MAJOR "1")
SET(Tutorial_VERSION_MINOR "0")
SET(Tutorial_VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file ("${PROJECT_SOURCE_DIR}/TutorialConfig.h.in" "${PROJECT_BINARY_DIR}/TutorialConfig.h")

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#include_directories("${PROJECT_BINARY_DIR}/ProgramLibrary")
#add_subdirectory(ProgramLibrary)
#add_library(ProgramLibrary  ProgramLibrary.cpp)

add_executable(Tutorial Program.cpp)
