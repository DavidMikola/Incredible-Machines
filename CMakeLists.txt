# Need recent version of cmake to properly find wxWidgets in windows
# using Visual Studio Code with CMake extension
# FATAL_ERROR specified for backwards compatibility with 2.x
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

# Name the project
project(MachineDemo)

# My C++ Object Oriented Design implementation
set(MACHINE_LIBRARY MachineLib)
add_subdirectory(${MACHINE_LIBRARY})

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# Fetch MachineDemoLib from Github
include(FetchContent)
FetchContent_Declare(
    MachineDemoLib
    GIT_REPOSITORY https://github.com/charles-owen/MachineDemoLib.git
    GIT_TAG 3b21a13abd6681b2c079a6561df5e6081fea4aa6
)
FetchContent_MakeAvailable(MachineDemoLib)

include_directories("${MACHINE_LIBRARY}/include" ${MachineDemoLib_SOURCE_DIR})

# This sets the Mac icon for the program
set(MACOSX_BUNDLE_ICON_FILE MachineDemoIcon.icns)
set_source_files_properties(${MACOSX_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp MachineSystemIsolator.h ${MachineDemoLib_SOURCE_DIR}/resources/MachineDemo.rc  ${MACOSX_BUNDLE_ICON_FILE})

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${MACHINE_LIBRARY} MachineDemoLib ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Copy resources into output directory
# Use both the root directory resources and those in MachineLib
file(COPY ${MachineDemoLib_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${MACHINE_LIBRARY}/resources/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(APPLE)
    # When building for MacOS, also copy resources into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources)
    file(COPY ${MachineDemoLib_SOURCE_DIR}/resources/ DESTINATION ${RESOURCE_DIR}/)
    file(COPY ${MACHINE_LIBRARY}/resources/images DESTINATION ${RESOURCE_DIR}/)
endif()

