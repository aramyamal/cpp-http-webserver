add_library(sockets
    socket.cpp
    socket.h
    connecting_socket.cpp
    connecting_socket.h
    listening_socket.h
    listening_socket.cpp
)

target_include_directories(sockets
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
