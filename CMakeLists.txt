cmake_minimum_required(VERSION 3.16)

# Define project
project(the-chip-8 LANGUAGES C)

# Add the SDL3 library as subdirectory (ensure SDL3 is located under 'vendored/SDL')
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create executable target
add_executable(
    the-chip-8
    main.c
    chip8.c
    opcode.c
    chip8.h
    opcode.h
)

# Link the SDL3 library
target_link_libraries(the-chip-8 PRIVATE SDL3::SDL3)

# SDL3main, maybe?
# target_link_libraries(the-chip-8 PRIVATE SDL3::SDL3 SDL3::SDL3main)

# Ensure include directories for SDL are set
target_include_directories(the-chip-8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL/include)

# Include installation directories
include(GNUInstallDirs)

# Install the target (installs executable after 'make install')
install(TARGETS the-chip-8
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Optionally set the CMake module path to find the correct SDL3 package
# This can be useful if the submodule wasn't added correctly or you're working with other SDL versions
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL")

find_package(ALSA REQUIRED)
if (NOT ALSA_FOUND)
    message(FATAL_ERROR "ALSA development library not found. Please install libasound2-dev or alsa-lib-devel.")
endif()

