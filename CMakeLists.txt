cmake_minimum_required(VERSION 3.5.0)

# Define project
project(cube-simulator VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

set(RAYLIB_VERSION 5.0)

# Locate and configure raylib with FetchContent to include all headers
include(FetchContent)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # Don't build the supplied example 
FetchContent_MakeAvailable(raylib)

# Add other dependencies via vcpkg
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
find_package(unofficial-enet REQUIRED)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project
include_directories("extern/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE} ${RAYGUI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} raylib unofficial::enet::enet)

# Setting ASSETS_PATH
if (CMAKE_CPP_FLAGS_RELEASE)
	target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
else()
	target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
endif()