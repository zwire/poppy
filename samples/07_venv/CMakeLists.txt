set(VENV ${CMAKE_CURRENT_SOURCE_DIR}/.venv)
set(TARGET 07_venv)

add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} PRIVATE poppy)
target_compile_definitions(${TARGET}
  PRIVATE
    PYTHON_EXECUTABLE_PATH=L"${VENV}/Scripts/python.exe"
    PYTHON_MODULES_SEARCH_PATH=L"${VENV}/Lib/site-packages")

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)
install(FILES ${TARGET}.py DESTINATION bin/scripts)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  install(FILES ${TARGET}.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUTCONFIG}/scripts)
endforeach()
