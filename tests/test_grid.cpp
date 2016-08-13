#include "test_support.hpp"
#include "assertions.hpp"

#include "grid.hpp"

using namespace std;
using namespace fieldmapgen;

TEST_CASE(grid_square_points) {
	vector<Point2D> expected_pos { {0, 0}, {2, 0}, {4, 0}, {0, 5}, {2, 5}, {4, 5}, {0, 10}, {2, 10}, {4, 10} };

	Grid subject = Grid::Square(3, 3, 2, 5);
	vector<Point2D> actual_pos(subject.get_points()->cbegin(), subject.get_points()->cend());

	ASSERT_LIST_EQ(expected_pos, actual_pos);
	return 0;
}
