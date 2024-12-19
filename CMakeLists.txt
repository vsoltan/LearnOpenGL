
cmake_minimum_required(VERSION 3.20.0)

project(
    LearnOpenGL
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
include(FindOpenGL)

set(GLFW_INSTALL TRUE)

FetchContent_Declare(
    GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # release 3.4
    GIT_PROGRESS TRUE
)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

FetchContent_MakeAvailable(GLFW)
find_package(OpenGL REQUIRED)

enable_language(C)
add_subdirectory(glad)

add_executable(MyOpenGLApp main.cpp test.cpp)

target_include_directories(
    MyOpenGLApp
    PRIVATE "${GLFW_SOURCE_DIR}/include")

target_link_libraries(
    MyOpenGLApp
    PRIVATE glfw
    PRIVATE GLAD
    PRIVATE OpenGL::GL)

target_compile_definitions(
    MyOpenGLApp PRIVATE GL_SILENCE_DEPRECATION
)

target_compile_options(MyOpenGLApp PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
