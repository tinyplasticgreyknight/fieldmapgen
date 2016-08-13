set(INCLUDE_DIRECTORY_NAMES
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/template_src"
	"${CMAKE_CURRENT_SOURCE_DIR}/tests"
)

set(MAIN_SOURCE_FILES
	src/graph.cpp
	src/graph_node_iterator.cpp
	src/field_factory.cpp
	src/grid.cpp
	src/point2d.cpp
)

set(MAIN_HEADER_FILES
	include/graph.hpp
	include/graph_node_iterator.hpp
	include/field_factory.hpp
	include/grid.hpp
	include/point2d.hpp
	include/random_access_iterator.hpp
	include/field.hpp
	include/total_field.hpp
	include/partial_field.hpp
	include/option.hpp
)

set(MAIN_TEMPLATE_FILES
	template_src/random_access_iterator.tmpl.hpp
	template_src/field.tmpl.hpp
	template_src/total_field.tmpl.hpp
	template_src/partial_field.tmpl.hpp
)

set(TEST_SUITE_FILES
	tests/main.cpp
	tests/test_partial_field.cpp
	tests/test_total_field.cpp
	tests/test_graph.cpp
	tests/test_field_factory.cpp
	tests/test_grid.cpp
	tests/test_integration.cpp
)

set(TEST_SUPPORT_FILES
	tests/test_support.cpp
	tests/assertions.cpp
	tests/test_support.hpp
	tests/assertions.hpp
	template_src/assertions.tmpl.hpp
)
