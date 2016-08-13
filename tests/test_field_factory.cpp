#include "test_support.hpp"
#include "assertions.hpp"

#include "graph.hpp"
#include "field_factory.hpp"

using namespace fieldmapgen;
using namespace std;

TEST_CASE(field_factory_should_create_flat) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<string> expected = { "foo", "foo", "foo", "foo" };

	auto field = factory.create_flat("foo");
	vector<string> actual(field->begin(), field->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field;
	return 0;
}

TEST_CASE(field_factory_should_create_from_function) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<int> expected { 40, 41, 42, 43 };

	function<int(Graph::node)> func = [](Graph::node n) { return n + 40; };
	auto field = factory.create_from_function(func);
	vector<int> actual(field->begin(), field->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field;
	return 0;
}

TEST_CASE(field_factory_should_create_partial) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<Option<int>> expected { None<int>(), None<int>(), None<int>(), None<int>() };

	auto field = factory.create_partial<int>();
	vector<Option<int>> actual(field->begin(), field->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field;
	return 0;
}

TEST_CASE(field_factory_should_create_partial_from_function) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<Option<int>> expected { Some(40), Some(41), Some(42), Some(43) };

	function<Option<int>(Graph::node)> func = [](Graph::node n) { return Some<int>(n + 40); };
	auto field = factory.create_partial_from_function(func);
	vector<Option<int>> actual(field->begin(), field->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field;
	return 0;
}

TEST_CASE(field_factory_should_map_one_field) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<int> expected { 0, 2, 4, 6 };

	function<int(Graph::node)> func1 = [](Graph::node n) { return (int)n; };
	function<int(int)> func_map = [](int a) { return 2 * a; };
	auto field1 = factory.create_from_function(func1);
	auto result = factory.map(field1, func_map);
	vector<int> actual(result->begin(), result->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field1;
	return 0;
}

TEST_CASE(field_factory_should_map_two_fields) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<int> expected { 0, 2, 6, 12 };

	function<int(Graph::node)> func1 = [](Graph::node n) { return (int)n; };
	function<int(Graph::node)> func2 = [](Graph::node n) { return (int)n + 1; };
	function<int(int, int)> func_map = [](int a, int b) { return a * b; };
	auto field1 = factory.create_from_function(func1);
	auto field2 = factory.create_from_function(func2);
	auto result = factory.map(field1, field2, func_map);
	vector<int> actual(result->begin(), result->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field1;
	return 0;
}

TEST_CASE(field_factory_should_map_three_fields) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<int> expected { 2, 5, 10, 17 };

	function<int(Graph::node)> func1 = [](Graph::node n) { return (int)n; };
	function<int(Graph::node)> func2 = [](Graph::node n) { return (int)n + 1; };
	function<int(Graph::node)> func3 = [](Graph::node n) { return (int)n + 2; };
	function<int(int, int, int)> func_map = [](int a, int b, int c) { return a * b + c; };
	auto field1 = factory.create_from_function(func1);
	auto field2 = factory.create_from_function(func2);
	auto field3 = factory.create_from_function(func3);
	auto result = factory.map(field1, field2, field3, func_map);
	vector<int> actual(result->begin(), result->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field1;
	return 0;
}

TEST_CASE(field_factory_should_map_four_fields) {
	Graph graph(4);
	FieldFactory factory(graph);
	vector<int> expected { 6, 14, 26, 42 };

	function<int(Graph::node)> func1 = [](Graph::node n) { return (int)n; };
	function<int(Graph::node)> func2 = [](Graph::node n) { return (int)n + 1; };
	function<int(Graph::node)> func3 = [](Graph::node n) { return (int)n + 2; };
	function<int(Graph::node)> func4 = [](Graph::node n) { return (int)n + 3; };
	function<int(int, int, int, int)> func_map = [](int a, int b, int c, int d) { return a * b + c * d; };
	auto field1 = factory.create_from_function(func1);
	auto field2 = factory.create_from_function(func2);
	auto field3 = factory.create_from_function(func3);
	auto field4 = factory.create_from_function(func4);
	auto result = factory.map(field1, field2, field3, field4, func_map);
	vector<int> actual(result->begin(), result->end());

	ASSERT_LIST_EQ(expected, actual);

	delete field1;
	return 0;
}
