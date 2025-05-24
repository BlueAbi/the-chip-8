cmake_minimum_required(VERSION 3.16)

# Define project
project(the-chip-8 LANGUAGES C)

# Add the SDL3 library as subdirectory
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create executable target
add_executable(
    the-chip-8
    main.c
    chip8.c
    opcode.c
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
