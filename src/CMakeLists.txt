set(TARGET poppy)

file(GLOB TARGETS src/*.cpp)
add_library(${TARGET} ${TARGETS})
set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE C)

find_package(Python3 REQUIRED COMPONENTS Development.Embed)
message(Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS})
message(Python3_LIBRARIES: ${Python3_LIBRARIES})
target_include_directories(${TARGET}
  PRIVATE ${Python3_INCLUDE_DIRS}
  PUBLIC ./include)
target_link_libraries(${TARGET} PRIVATE ${Python3_LIBRARIES})

if(UNIX)
  target_compile_options(${TARGET} PRIVATE -std=c++14 -pthread)
endif()

install(DIRECTORY include DESTINATION include)
install(TARGETS ${TARGET}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
