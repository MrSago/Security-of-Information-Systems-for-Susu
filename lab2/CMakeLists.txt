cmake_minimum_required(VERSION 3.21)
project(SOIS_lab2 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

# set(CRYPTOPP_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/cryptopp)
# file(GLOB CRYPTOPP_SOURCES ${CRYPTOPP_DIRECTORY}/*.cpp)
# add_library(cryptopp STATIC ${CRYPTOPP_SOURCES})
# target_include_directories(cryptopp PUBLIC ${CRYPTOPP_DIRECTORY})

add_subdirectory(client)
# add_subdirectory(server)
