cmake_minimum_required(VERSION 3.10)
set(VCPKG_CRT_LINKAGE static)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
endif()
message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS: ${CMAKE_EXPORT_COMPILE_COMMANDS}")

project(AwesomeLibraries CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 CONFIG REQUIRED)
add_executable(catch2 catch2.cpp)
target_link_libraries(catch2 PRIVATE Catch2::Catch2)

# find_path(CROW_INCLUDE_DIRS NAMES crow.h )
# find_package(Boost REQUIRED COMPONENTS system date_time)
# add_executable(crow crow.cpp)
# target_include_directories(crow PRIVATE ${CROW_INCLUDE_DIRS})
# target_include_directories(crow PRIVATE ${Boost_INCLUDE_DIRS})
# target_link_libraries(crow PRIVATE ${Boost_LIBRARIES})

find_package(unofficial-http-parser REQUIRED)
find_package(fmt REQUIRED)
find_package(restinio REQUIRED)
find_path(NLOHMANNJSON_INCLUDE_DIR NAMES json.hpp PATH_SUFFIXES nlohmann)
add_executable(restinio restinio.cpp)
target_include_directories(restinio PRIVATE ${NLOHMANNJSON_INCLUDE_DIR})
target_link_libraries(restinio PRIVATE restinio::restinio)