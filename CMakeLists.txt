cmake_minimum_required(VERSION 3.10)

project(pixlet)

add_executable(pixlet 
  src/main.c 
  src/editor.c 
  src/layers.c
  src/selector.c
  )

target_include_directories(pixlet PUBLIC include/)
target_link_libraries(pixlet PUBLIC mingw32 
  ${CMAKE_BINARY_DIR}/libs/SDL2main.lib
  ${CMAKE_BINARY_DIR}/libs/SDL2.lib 
  ${CMAKE_BINARY_DIR}/libs/SDL2_image.lib)
