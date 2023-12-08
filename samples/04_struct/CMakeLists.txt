set(TARGET 04_struct)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} PRIVATE poppy)

install(TARGETS ${TARGET}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
