cmake_minimum_required(VERSION 3.28)
project(RoguelikeGame LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SFML_DIR "C:/SFML/lib/cmake/SFML" CACHE PATH "Path to installed SFML" FORCE)

find_package(SFML 3 COMPONENTS Graphics Audio System)

if(NOT SFML_FOUND)
    message(STATUS "SFML not found locally, fetching 3.1.0")
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

set(SOURCES
    src/main.cpp
    src/Application/Application.cpp
    src/GameEntitiesAndComponents/AnimationComponent.cpp
    src/SceneGraph/SceneNode.cpp
    src/StateSystem/State.cpp
    src/StateSystem/StateStack.cpp
    src/SceneGraph/SceneNode.cpp
    src/World/World.cpp
)
add_executable(main ${SOURCES})

# Let's plain includes such as "SceneNode.h" work from any folder.
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Application
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameEntitiesAndComponents
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ResourceManagement
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SceneGraph
    ${CMAKE_CURRENT_SOURCE_DIR}/src/StateSystem
    ${CMAKE_CURRENT_SOURCE_DIR}/src/World
)

# Copy the assets folder next to the executable on every build.
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:main>/assets
)
add_dependencies(main copy_assets)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::System SFML::Audio)

# Precompiled header.
target_precompile_headers(main PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h"
)

# Copy SFML's DLLs next to the executable after the build.
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:main> $<TARGET_FILE_DIR:main>
    COMMAND_EXPAND_LISTS)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
