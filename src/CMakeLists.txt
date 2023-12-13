set(TARGET poppy)

file(GLOB TARGETS src/*.cpp)
add_library(${TARGET} ${TARGETS})
set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${TARGET} PUBLIC $ENV{PYTHONPATH}/include ./include)
target_link_directories(${TARGET} PUBLIC $ENV{PYTHONPATH}/libs)

install(DIRECTORY include DESTINATION include)
install(TARGETS ${TARGET}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
