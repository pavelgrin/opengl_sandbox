cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(OPENGL_SANDBOX)

set(APP_NAME app)

set(SOURCE
   "${CMAKE_SOURCE_DIR}/src/window/glfw.cpp"
   "${CMAKE_SOURCE_DIR}/src/window/sdl2.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/render.cpp"
)

add_executable("${APP_NAME}" "${SOURCE}" src/main.cpp)

set_target_properties("${APP_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories("${CMAKE_SOURCE_DIR}/deps/gleq")

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glad")
target_link_libraries("${APP_NAME}" glad)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glfw")
target_link_libraries("${APP_NAME}" glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/sdl2")
target_link_libraries("${APP_NAME}" SDL2main SDL2-static)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
