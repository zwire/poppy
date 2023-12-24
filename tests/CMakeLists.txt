include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

if (WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

file(GLOB TESTS *.cpp)
foreach(TEST ${TESTS})
  get_filename_component(TARGET ${TEST} NAME_WE)
  add_executable(${TARGET} ${TEST})
  target_link_libraries(${TARGET} gtest_main poppy)
  if (WIN32)
    target_compile_definitions(${TARGET} PRIVATE BAD_CAST="bad cast")
  else()
    target_compile_definitions(${TARGET} PRIVATE BAD_CAST="std::bad_cast")
  endif()
  include(GoogleTest)
  gtest_discover_tests(${TARGET}
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET}>
  )
endforeach()

install(FILES script.py DESTINATION $<TARGET_FILE_DIR:${TARGET}>)
