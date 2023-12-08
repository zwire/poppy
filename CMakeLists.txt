cmake_minimum_required(VERSION 3.14)

project(poppy)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_SAMPLES "Build samples" ON)

add_subdirectory(src)

if (${BUILD_SAMPLES})
  add_subdirectory(samples)
endif()

if (${BUILD_TESTS})
  enable_testing()
  add_subdirectory(tests)
endif()

install(DIRECTORY scripts DESTINATION .)
