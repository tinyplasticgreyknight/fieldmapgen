cmake_minimum_required(VERSION 3.0)
project(fieldmapgen)

include(files.cmake)
include(macros.cmake)

include_directories(${INCLUDE_DIRECTORY_NAMES})

add_library(fieldmapgen STATIC
	${MAIN_SOURCE_FILES}
	${MAIN_HEADER_FILES}
	${MAIN_TEMPLATE_FILES}
)
add_executable(testsuite
	${TEST_SUITE_FILES}
	${TEST_SUPPORT_FILES}
)

add_custom_target(
	scan_for_tests
	ALL
	COMMAND ${CMAKE_COMMAND} -P test_scan.cmake
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(testsuite fieldmapgen)

enable_lots_of_warnings()
enable_cpp_11()

enable_testing()
