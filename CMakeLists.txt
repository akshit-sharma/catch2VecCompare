cmake_minimum_required(VERSION 3.8)

Project(test CXX)

set(CONAN_SYSTEM_INCLUDES "On")
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file (DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                 "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
endif()
include ("${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
conan_cmake_run(
  REQUIRES
  catch2/2.12.2@_/_
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing
  BUILD_TYPE RELEASE
  )

add_executable(test
  testCase.cpp
  main.cpp
  )

target_compile_options(test
  PUBLIC
  $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>)

target_link_libraries(test
  PRIVATE
  CONAN_PKG::catch2
  )

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
  add_custom_target(copy_compile_commands ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
  add_custom_command(
    TARGET copy_compile_commands
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
     ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
     ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

