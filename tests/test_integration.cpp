#include "test_support.hpp"
#include "assertions.hpp"

#include "grid.hpp"
#include "graph.hpp"
#include "point2d.hpp"
#include "field_factory.hpp"

#include <iostream>

using namespace std;
using namespace fieldmapgen;

TEST_CASE(integration_build_elevation_map) {
	Grid* grid = Grid::Square(3, 3, 1, 1);
	FieldFactory factory(grid->get_graph());
	vector<Point2D> expected_pos { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };
	vector<int> expected_elev { 0, 2, 4, 2, 4, 6, 4, 6, 8 };
	function<int(Point2D)> assign_elev = [](Point2D pos) { return (int)(pos.x + pos.y); };

	auto field_pos = grid->get_points();
	auto field_elev = factory.map(field_pos, assign_elev);
	field_elev->map_in_place([](Graph::node, int elev) { return 2 * elev; });

	vector<Point2D> actual_pos(field_pos->begin(), field_pos->end());
	vector<int> actual_elev(field_elev->begin(), field_elev->end());
	ASSERT_LIST_EQ(expected_pos, actual_pos);
	ASSERT_LIST_EQ(expected_elev, actual_elev);

	delete field_elev;
	delete grid;
	return 0;
}
