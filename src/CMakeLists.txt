set(TARGET poppy)

add_library(${TARGET} 
  src/object.cpp
  src/value.cpp
  src/tuple.cpp
  src/list.cpp
  src/dict.cpp
  src/buffer.cpp
  src/func.cpp
  src/gil.cpp
  src/poppy.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE C)

target_include_directories(${TARGET}
  PUBLIC
    $ENV{PYTHONPATH}/include
    ./include)

target_link_directories(${TARGET} 
  PUBLIC
    $ENV{PYTHONPATH}/libs)

install(TARGETS ${TARGET}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)

install(DIRECTORY include
  DESTINATION include
)
