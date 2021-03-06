cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(OPENGL_SANDBOX)

set(CMAKE_BUILD_TYPE "Release")

set(APP_NAME app)

set(SOURCE
   "${CMAKE_SOURCE_DIR}/src/main.cpp"
   "${CMAKE_SOURCE_DIR}/src/window/window.cpp"
   "${CMAKE_SOURCE_DIR}/src/window/events.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/render.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/shader.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/texture.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/mesh.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/model.cpp"
   "${CMAKE_SOURCE_DIR}/src/render/camera.cpp"
   "${CMAKE_SOURCE_DIR}/src/loaders/load_shader.cpp"
   "${CMAKE_SOURCE_DIR}/src/loaders/load_texture.cpp"
   "${CMAKE_SOURCE_DIR}/src/loaders/load_model.cpp"
)

add_executable("${APP_NAME}" "${SOURCE}")

set_target_properties("${APP_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glad")
target_link_libraries("${APP_NAME}" glad)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/sdl2")
target_link_libraries("${APP_NAME}" SDL2main SDL2-static)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/stb")
target_link_libraries("${APP_NAME}" stb)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glm")
target_link_libraries("${APP_NAME}" glm)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/assimp")
target_link_libraries("${APP_NAME}" assimp)
