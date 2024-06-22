cmake_minimum_required(VERSION 3.25)
project(sfSnake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB all_source_files "*.cpp")

 option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
 include(FetchContent)
 FetchContent_Declare(SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.6.0)
 FetchContent_MakeAvailable(SFML)

add_executable(sfSnake)
target_sources(sfSnake PRIVATE ${all_source_files})
#target_include_directories(sfSnake PRIVATE extlibs/include)
#target_link_directories(sfSnake PRIVATE extlibs/lib)
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio sfml-window sfml-network sfml-system)
target_compile_options(sfSnake PRIVATE -std=c++20)



