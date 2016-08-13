#include "test_support.hpp"
#include "assertions.hpp"

#include "graph.hpp"

using namespace fieldmapgen;

TEST_CASE(graph_should_get_order) {
	size_t expected_order = 42;
	Graph graph(expected_order);

	auto actual_order = graph.order();

	ASSERT_EQ(expected_order, actual_order);
	return 0;
}

TEST_CASE(graph_should_initially_have_no_neighbours) {
	Graph graph(42);

	auto neighbours = graph.get_linked(35);
	auto outward = graph.get_linked_from(35);
	auto inward = graph.get_linked_to(35);

	ASSERT_EMPTY(neighbours);
	ASSERT_EMPTY(outward);
	ASSERT_EMPTY(inward);
	return 0;
}

TEST_CASE(graph_should_have_neighbours_after_linking) {
	Graph graph(42);
	Graph::node n_a = 4;
	Graph::node n_b = 2;

	graph.link(n_a, n_b);
	auto neighbours_a = graph.get_linked(n_a);
	auto neighbours_b = graph.get_linked(n_b);
	auto outward_a = graph.get_linked_from(n_a);
	auto outward_b = graph.get_linked_from(n_b);
	auto inward_a = graph.get_linked_to(n_a);
	auto inward_b = graph.get_linked_to(n_b);

	ASSERT_LIST_EQ({n_b}, neighbours_a);
	ASSERT_LIST_EQ({n_a}, neighbours_b);
	ASSERT_LIST_EQ({n_b}, outward_a);
	ASSERT_LIST_EQ({n_a}, outward_b);
	ASSERT_LIST_EQ({n_b}, inward_a);
	ASSERT_LIST_EQ({n_a}, inward_b);
	return 0;
}

TEST_CASE(graph_should_have_neighbours_after_linking_oneway) {
	Graph graph(42);
	Graph::node n_a = 4;
	Graph::node n_b = 2;

	graph.link_oneway(n_a, n_b);
	auto neighbours_a = graph.get_linked(n_a);
	auto neighbours_b = graph.get_linked(n_b);
	auto outward_a = graph.get_linked_from(n_a);
	auto outward_b = graph.get_linked_from(n_b);
	auto inward_a = graph.get_linked_to(n_a);
	auto inward_b = graph.get_linked_to(n_b);

	ASSERT_LIST_EQ({n_b}, neighbours_a);
	ASSERT_LIST_EQ({n_a}, neighbours_b);
	ASSERT_LIST_EQ({n_b}, outward_a);
	ASSERT_EMPTY(outward_b);
	ASSERT_EMPTY(inward_a);
	ASSERT_LIST_EQ({n_a}, inward_b);
	return 0;
}

TEST_CASE(graph_should_have_no_neighbours_after_unlinking) {
	Graph graph(42);
	Graph::node n_a = 4;
	Graph::node n_b = 2;

	graph.link(n_a, n_b);
	graph.unlink(n_a, n_b);
	auto neighbours_a = graph.get_linked(n_a);
	auto neighbours_b = graph.get_linked(n_b);
	auto outward_a = graph.get_linked_from(n_a);
	auto outward_b = graph.get_linked_from(n_b);
	auto inward_a = graph.get_linked_to(n_a);
	auto inward_b = graph.get_linked_to(n_b);

	ASSERT_EMPTY(neighbours_a);
	ASSERT_EMPTY(neighbours_b);
	ASSERT_EMPTY(outward_a);
	ASSERT_EMPTY(outward_b);
	ASSERT_EMPTY(inward_a);
	ASSERT_EMPTY(inward_b);
	return 0;
}

TEST_CASE(graph_should_have_neighbours_after_oneway_unlinking) {
	Graph graph(42);
	Graph::node n_a = 4;
	Graph::node n_b = 2;

	graph.link(n_a, n_b);
	graph.unlink_oneway(n_b, n_a);
	auto neighbours_a = graph.get_linked(n_a);
	auto neighbours_b = graph.get_linked(n_b);
	auto outward_a = graph.get_linked_from(n_a);
	auto outward_b = graph.get_linked_from(n_b);
	auto inward_a = graph.get_linked_to(n_a);
	auto inward_b = graph.get_linked_to(n_b);

	ASSERT_LIST_EQ({n_b}, neighbours_a);
	ASSERT_LIST_EQ({n_a}, neighbours_b);
	ASSERT_LIST_EQ({n_b}, outward_a);
	ASSERT_EMPTY(outward_b);
	ASSERT_EMPTY(inward_a);
	ASSERT_LIST_EQ({n_a}, inward_b);
	return 0;
}

TEST_CASE(graph_should_iterate_over_all_nodes) {
	Graph graph(4);

	std::vector<Graph::node> expected { 0, 1, 2, 3 };
	std::vector<Graph::node> actual;

	size_t i = 0;
	for (auto node : graph) {
		i += 1;
		ASSERT_TRUE(i < 10);
		actual.push_back(node);
	}

	ASSERT_LIST_EQ(expected, actual);
	return 0;
}
