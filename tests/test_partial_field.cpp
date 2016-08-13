#include "test_support.hpp"
#include "assertions.hpp"

#include "graph.hpp"
#include "partial_field.hpp"

using namespace fieldmapgen;

TEST_CASE(partial_field_should_construct) {
	Graph graph(3);
	PartialField<int> field(graph);
	return 0;
}

TEST_CASE(partial_field_should_return_none_from_set_if_not_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	auto result = field.set_value(0, Some(42));

	ASSERT_NONE(int, result);
	return 0;
}

TEST_CASE(partial_field_should_return_previous_from_set_if_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.set_value(0, Some(35));
	auto result = field.set_value(0, Some(42));

	ASSERT_SOME(int, 35, result);
	return 0;
}

TEST_CASE(partial_field_should_return_true_from_add_if_not_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	auto result = field.add_value(0, Some(42));

	ASSERT_EQ(true, result);
	return 0;
}

TEST_CASE(partial_field_should_return_false_from_add_if_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.set_value(0, Some(35));
	auto result = field.add_value(0, Some(42));

	ASSERT_EQ(false, result);
	return 0;
}

TEST_CASE(partial_field_should_return_none_from_remove_if_not_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	auto result = field.remove_value(0);

	ASSERT_NONE(int, result);
	return 0;
}

TEST_CASE(partial_field_should_return_previous_from_remove_if_existing) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.set_value(0, Some(35));
	auto result = field.remove_value(0);

	ASSERT_SOME(int, 35, result);
	return 0;
}

TEST_CASE(partial_field_should_initially_get_none) {
	Graph graph(3);
	PartialField<int> field(graph);

	auto actual = field.get_value(0);

	ASSERT_NONE(int, actual);
	return 0;
}

TEST_CASE(partial_field_should_get_added_value) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.add_value(0, Some(42));
	auto actual = field.get_value(0);

	ASSERT_SOME(int, 42, actual);
	return 0;
}

TEST_CASE(partial_field_should_get_set_value) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.add_value(0, Some(35));
	field.set_value(0, Some(42));
	auto actual = field.get_value(0);

	ASSERT_SOME(int, 42, actual);
	return 0;
}

TEST_CASE(partial_field_should_get_none_from_after_removal) {
	Graph graph(3);
	PartialField<int> field(graph);

	field.add_value(0, Some(42));
	field.remove_value(0);
	auto actual = field.get_value(0);

	ASSERT_NONE(int, actual);
	return 0;
}

TEST_CASE(partial_field_should_iterate) {
	Graph graph(4);
	PartialField<int> field(graph);

	std::vector<Option<int>> expected { Some(40), Some(41), None<int>(), Some(42) };

	field.add_value(0, Some(40));
	field.add_value(1, Some(41));
	field.add_value(3, Some(42));

	std::vector<Option<int>> actual(field.begin(), field.end());

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}

TEST_CASE(partial_field_should_write_through_iterator) {
	Graph graph(4);
	PartialField<int> field(graph);

	std::vector<Option<int>> expected { Some(40), Some(41), Some(42), Some(43) };

	*field.begin() = Some(40);
	*++field.begin() = Some(41);
	field.begin()[2] = Some(42);
	*(--field.end()) = Some(43);

	std::vector<Option<int>> actual(field.begin(), field.end());

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}
