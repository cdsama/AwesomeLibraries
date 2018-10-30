cmake_minimum_required(VERSION 3.10)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
endif()

project(AwesomeLibraries CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 CONFIG REQUIRED)
add_executable(catch2 catch2.cpp)
target_link_libraries(catch2 PRIVATE Catch2::Catch2)