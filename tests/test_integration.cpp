#include "test_support.hpp"
#include "assertions.hpp"

#include "graph.hpp"
#include "field_factory.hpp"

#include <iostream>

using namespace std;
using namespace fieldmapgen;

struct vec2d {
	int x;
	int y;

	bool operator ==(const vec2d& that) { return x == that.x && y == that.y; }
};

std::ostream& operator<<(ostream& stream, const vec2d& value) {
	return stream << "vec2d{" << value.x << ", " << value.y << "}";
}

function<vec2d(Graph::node)> initial_positions(int stride) {
	return [stride](Graph::node n) {
		int in = (int)n;
		int x = in % stride;
		int y = (in - x) / stride;
		return vec2d { x, y };
	};
}

TEST_CASE(integration_build_elevation_map) {
	Graph graph(9);
	FieldFactory factory(graph);
	vector<vec2d> expected_pos { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };
	vector<int> expected_elev { 0, 2, 4, 2, 4, 6, 4, 6, 8 };
	function<int(vec2d)> assign_elev = [](vec2d pos) { return pos.x + pos.y; };

	auto field_pos = factory.create_from_function(initial_positions(3));
	auto field_elev = factory.map(field_pos, assign_elev);
	for (int& elev : *field_elev) {
		elev = 2 * elev;
	}

	vector<vec2d> actual_pos(field_pos->begin(), field_pos->end());
	vector<int> actual_elev(field_elev->begin(), field_elev->end());
	ASSERT_LIST_EQ(expected_pos, actual_pos);
	ASSERT_LIST_EQ(expected_elev, actual_elev);

	delete field_pos;
	delete field_elev;
	return 0;
}
