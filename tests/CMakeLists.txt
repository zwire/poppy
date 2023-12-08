include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

if (WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS *.cpp)
foreach(TEST ${TESTS})
  get_filename_component(TARGET ${TEST} NAME_WE)
  add_executable(${TARGET} ${TEST})
  target_link_libraries(${TARGET} gtest_main poppy)
  include(GoogleTest)
  gtest_discover_tests(${TARGET})
endforeach()
