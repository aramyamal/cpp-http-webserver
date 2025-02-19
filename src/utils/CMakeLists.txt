add_library(utils
    file_utils.cpp
    file_utils.h
)

target_include_directories(utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
