add_library(communication
    client.cpp
    client.h
    server.cpp
    server.h
    http_server.cpp
    http_server.h
)

# communication depends on sockets
target_link_libraries(communication
  PRIVATE
    sockets
)

target_include_directories(communication
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(test-client
    test_run_client.cpp
)

target_link_libraries(test-client
  PRIVATE
    communication
    sockets
)
