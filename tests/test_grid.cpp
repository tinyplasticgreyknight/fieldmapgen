#include "test_support.hpp"
#include "assertions.hpp"

#include "grid.hpp"

using namespace std;
using namespace fieldmapgen;

TEST_CASE(grid_square_points) {
	vector<Point2D> expected_pos { {0, 0}, {2, 0}, {4, 0}, {0, 5}, {2, 5}, {4, 5}, {0, 10}, {2, 10}, {4, 10} };

	Grid* subject = Grid::Square(3, 3, 2, 5);
	vector<Point2D> actual_pos(subject->get_points()->cbegin(), subject->get_points()->cend());

	ASSERT_LIST_EQ(expected_pos, actual_pos);
	delete subject;
	return 0;
}

size_t calc_expected_square_grid_degree(Grid::point point, double x_limit, double y_limit) {
	auto x_edge = (point.x == 0 || point.x == x_limit);
	auto y_edge = (point.y == 0 || point.y == y_limit);
	if (x_edge && y_edge) {
		return 2;
	} else if (x_edge || y_edge) {
		return 3;
	} else {
		return 4;
	}
}

TEST_CASE(grid_square_num_neighbours) {
	size_t width = 9;
	size_t height = 9;
	double cell_size = 5;
	double x_limit = (width - 1) * cell_size;
	double y_limit = (height - 1) * cell_size;
	Grid* subject = Grid::Square(width, height, cell_size, cell_size);
	Graph& graph = subject->get_graph();

	for (auto n : graph) {
		auto pt = subject->get_points()->get_value(n);
		size_t expected_degree = calc_expected_square_grid_degree(pt, x_limit, y_limit);
		auto neighbours = graph.get_linked(n);
		ASSERT_EQ(expected_degree, neighbours.size());
	}

	delete subject;
	return 0;
}
