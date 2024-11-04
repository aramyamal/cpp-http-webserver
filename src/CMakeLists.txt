add_subdirectory(sockets)
add_subdirectory(communication)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    sockets
    communication
)
