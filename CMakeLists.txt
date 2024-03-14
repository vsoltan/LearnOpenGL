
cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 23)

Set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)
include(FindOpenGL)

set(GLFW_INSTALL TRUE)

FetchContent_Declare(
    GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # release 3.4
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(GLFW)
find_package(OpenGL REQUIRED)

add_subdirectory(glad)

project(
    LearnOpenGL
    LANGUAGES C CXX)

add_executable(MyOpenGLApp main.cpp)

target_include_directories(
    MyOpenGLApp
    PRIVATE "${GLFW_SOURCE_DIR}/include")

target_link_libraries(
    MyOpenGLApp
    PRIVATE glfw
    PRIVATE GLAD
    PRIVATE OpenGL::GL)

target_compile_options(MyOpenGLApp PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)