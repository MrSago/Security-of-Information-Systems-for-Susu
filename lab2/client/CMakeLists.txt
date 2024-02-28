set(TARGET lab2_client)

file(GLOB_RECURSE TARGET_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(${TARGET} ${TARGET_SOURCES})

target_link_libraries(${TARGET} ws2_32)
target_link_libraries(${TARGET} mswsock)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(${TARGET} cryptopp)
