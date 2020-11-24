# =========================================================================== #
# Variables
# =========================================================================== #

# Define the project name
set(PROJECTNAME OpenCvApp)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# =========================================================================== #
# Build
# =========================================================================== #

# CMake version check
cmake_minimum_required(VERSION 3.13)

# Create project
project( ${PROJECTNAME} )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable( ${PROJECTNAME} ${SOURCE_FILES} )

target_link_libraries( ${PROJECTNAME} ${OpenCV_LIBS} )