
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
    PRIVATE OpenGL::GL)

if( MSVC_VERSION GREATER_EQUAL 1936 AND MSVC_IDE ) # 17.6+
  # When using /std:c++latest, "Build ISO C++23 Standard Library Modules" defaults to "Yes".
  # Default to "No" instead.
  #
  # As of CMake 3.26.4, there isn't a way to control this property
  # (https://gitlab.kitware.com/cmake/cmake/-/issues/24922),
  # We'll use the MSBuild project system instead
  # (https://learn.microsoft.com/en-us/cpp/build/reference/vcxproj-file-structure)
  file( CONFIGURE OUTPUT "${CMAKE_BINARY_DIR}/Directory.Build.props" CONTENT [==[
<Project>
  <ItemDefinitionGroup>
    <ClCompile>
      <BuildStlModules>true</BuildStlModules>
    </ClCompile>
  </ItemDefinitionGroup>
</Project>
]==] @ONLY )
endif()


target_compile_options(MyOpenGLApp PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /std:c++latest>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)