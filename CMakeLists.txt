cmake_minimum_required(VERSION "3.0")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O2 -static-libgcc -static-libstdc++ -std=c++17")
set(CMAKE_CXX_COMPILER "g++")

aux_source_directory(./src/ SRC_LIST)

project(main)

# add_subdirectory(./lib/gcc_dll_release)

# include(${wxWidgets_USE_FILE})
# and for each of your dependent executable/library targets:

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(EXECUTABLE_OUTPUT_PATH ./bin/)



add_executable(
    main
    ${SRC_LIST}
    ${include_directories}
)

target_include_directories(main PUBLIC ./include/ PUBLIC ./lib/gcc_dll_release/mswu PUBLIC ./src/)

target_link_libraries(main ${wxWidgets_LIBRARIES})

# target_link_libraries(main wxWidgets)





