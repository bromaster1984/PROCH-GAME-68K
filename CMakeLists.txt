cmake_minimum_required(VERSION 3.16)
project(PROCH C)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Retro68")
    message(FATAL_ERROR "Use Retro68's m68k-apple-macos toolchain; host checks use tools/test_host.sh")
endif()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
option(PROCH_AUTOTEST "Run Toolbox smoke checks and exit; test build only" OFF)
option(PROCH_BRINGUP "Build the initial pattern/font diagnostic rather than the quest demo" OFF)
option(PROCH_CAMPAIGN "Build the developing full-campaign interface" ON)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/font.h
                          ${CMAKE_CURRENT_BINARY_DIR}/generated/content.h
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_content.py
            ${CMAKE_CURRENT_BINARY_DIR}/generated
    DEPENDS tools/generate_content.py scenes.json items.json quests.json)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/campaign_data.h
                          ${CMAKE_CURRENT_BINARY_DIR}/generated/campaign_data.c
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_campaign.py
            ${CMAKE_CURRENT_BINARY_DIR}/generated
    DEPENDS tools/generate_campaign.py tools/generate_content.py content/campaign_texts.json
            content/campaign_facts.json scenes.json quests.json items.json)
# Build the production model separately until the full campaign is connected.
add_library(PROCHCampaignCore STATIC src/campaign/model.c src/campaign/world.c
            src/campaign/rules.c src/campaign/rules_a.c src/campaign/rules_b.c
            src/campaign/rules_c.c
            ${CMAKE_CURRENT_BINARY_DIR}/generated/campaign_data.c)
target_include_directories(PROCHCampaignCore PRIVATE src/campaign ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_compile_features(PROCHCampaignCore PRIVATE c_std_99)
target_compile_options(PROCHCampaignCore PRIVATE -m68000 -msoft-float -Os -Wall -Wextra -Werror
                       -ffunction-sections -fdata-sections)
if(PROCH_AUTOTEST OR PROCH_BRINGUP)
    set(PROCH_ENTRY src/platform_mac/main.c)
elseif(PROCH_CAMPAIGN)
    set(PROCH_ENTRY src/platform_mac/campaign.c)
else()
    set(PROCH_ENTRY src/platform_mac/demo.c src/engine.c)
endif()
add_application(PROCH ${PROCH_ENTRY} src/render_1bit.c src/platform_mac/font_mac.c
                ${CMAKE_CURRENT_BINARY_DIR}/generated/font.h src/platform_mac/proch.r
                CREATOR PRCH)
target_include_directories(PROCH PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_compile_features(PROCH PRIVATE c_std_99)
target_compile_options(PROCH PRIVATE -m68000 -msoft-float -Os -Wall -Wextra
                       -Werror -ffunction-sections -fdata-sections)
target_link_options(PROCH PRIVATE -m68000 -msoft-float -Wl,-gc-sections)
if(PROCH_CAMPAIGN AND NOT PROCH_AUTOTEST AND NOT PROCH_BRINGUP)
    target_link_libraries(PROCH PRIVATE PROCHCampaignCore)
endif()
if(PROCH_AUTOTEST)
    target_compile_definitions(PROCH PRIVATE PROCH_AUTOTEST=1)
endif()
