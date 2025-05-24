cmake_minimum_required(VERSION 3.16)

project(the-chip-8 LANGUAGES C)

add_executable(the-chip-8
    main.c
    chip8.c
    chip8.h
    opcode.c
    opcode.h)

include(GNUInstallDirs)
install(TARGETS the-chip-8
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
