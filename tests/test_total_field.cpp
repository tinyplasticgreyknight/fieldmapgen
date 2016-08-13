#include "test_support.hpp"
#include "assertions.hpp"

#include "graph.hpp"
#include "total_field.hpp"

using namespace fieldmapgen;

TEST_CASE(total_field_should_construct_with_default_values) {
	Graph graph(3);
	TotalField<int> field(graph, 99);
	return 0;
}

TEST_CASE(total_field_should_return_default_from_set_if_not_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	auto result = field.set_value(0, 42);

	ASSERT_EQ(99, result);
	return 0;
}

TEST_CASE(total_field_should_return_previous_from_set_if_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.set_value(0, 35);
	auto result = field.set_value(0, 42);

	ASSERT_EQ(35, result);
	return 0;
}

TEST_CASE(total_field_should_return_true_from_add_if_not_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	auto result = field.add_value(0, 42);

	ASSERT_EQ(true, result);
	return 0;
}

TEST_CASE(total_field_should_return_false_from_add_if_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.set_value(0, 35);
	auto result = field.add_value(0, 42);

	ASSERT_EQ(false, result);
	return 0;
}

TEST_CASE(total_field_should_return_default_from_remove_if_not_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	auto result = field.remove_value(0);

	ASSERT_EQ(99, result);
	return 0;
}

TEST_CASE(total_field_should_return_previous_from_remove_if_existing) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.set_value(0, 35);
	auto result = field.remove_value(0);

	ASSERT_EQ(35, result);
	return 0;
}

TEST_CASE(total_field_should_initially_get_default) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	auto actual = field.get_value(0);

	ASSERT_EQ(99, actual);
	return 0;
}

TEST_CASE(total_field_should_get_added_value) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.add_value(0, 42);
	auto actual = field.get_value(0);

	ASSERT_EQ(42, actual);
	return 0;
}

TEST_CASE(total_field_should_get_set_value) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.add_value(0, 35);
	field.set_value(0, 42);
	auto actual = field.get_value(0);

	ASSERT_EQ(42, actual);
	return 0;
}

TEST_CASE(total_field_should_get_default_after_removal) {
	Graph graph(3);
	TotalField<int> field(graph, 99);

	field.add_value(0, 42);
	field.remove_value(0);
	auto actual = field.get_value(0);

	ASSERT_EQ(99, actual);
	return 0;
}

TEST_CASE(total_field_should_iterate) {
	Graph graph(4);
	TotalField<int> field(graph, 99);

	std::vector<int> expected { 40, 41, 42, 99 };

	field.add_value(0, 40);
	field.add_value(1, 41);
	field.add_value(2, 42);

	std::vector<int> actual(field.begin(), field.end());

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}

TEST_CASE(total_field_should_construct_from_function) {
	Graph graph(4);
	TotalField<int> field(graph, [](Graph::node n) { return n + 40; });

	std::vector<int> expected { 40, 41, 42, 43 };
	std::vector<int> actual(field.begin(), field.end());

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}

TEST_CASE(total_field_should_write_through_iterator) {
	Graph graph(4);
	TotalField<int> field(graph, 99);

	std::vector<int> expected { 40, 41, 42, 43 };

	*field.begin() = 40;
	*++field.begin() = 41;
	field.begin()[2] = 42;
	*(--field.end()) = 43;

	std::vector<int> actual(field.begin(), field.end());

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}
