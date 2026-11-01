cmake_minimum_required(VERSION 3.16)
project(PROCH C)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Retro68")
    message(FATAL_ERROR "Use Retro68's m68k-apple-macos toolchain; host checks use tools/test_host.sh")
endif()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/font.h
                          ${CMAKE_CURRENT_BINARY_DIR}/generated/content.h
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_content.py
            ${CMAKE_CURRENT_BINARY_DIR}/generated
    DEPENDS tools/generate_content.py scenes.json items.json quests.json)
add_application(PROCH src/platform_mac/main.c src/render_1bit.c src/platform_mac/font_mac.c
                ${CMAKE_CURRENT_BINARY_DIR}/generated/font.h src/platform_mac/proch.r
                CREATOR PRCH)
target_include_directories(PROCH PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_compile_features(PROCH PRIVATE c_std_99)
target_compile_options(PROCH PRIVATE -m68000 -msoft-float -Os -Wall -Wextra
                       -Werror -ffunction-sections -fdata-sections)
target_link_options(PROCH PRIVATE -m68000 -msoft-float -Wl,-gc-sections)
option(PROCH_AUTOTEST "Run Toolbox smoke checks and exit; test build only" OFF)
if(PROCH_AUTOTEST)
    target_compile_definitions(PROCH PRIVATE PROCH_AUTOTEST=1)
endif()
