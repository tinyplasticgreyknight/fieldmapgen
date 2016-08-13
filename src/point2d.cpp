#include "point2d.hpp"

using namespace fieldmapgen;

bool Point2D::operator ==(const Point2D& that) {
	return x == that.x && y == that.y;
}

Point2D Point2D::zero(void) {
	return Point2D { 0, 0 };
}

namespace fieldmapgen {
	std::ostream& operator<<(std::ostream& stream, const Point2D& value) {
		return stream << "Point2D{" << value.x << ", " << value.y << "}";
	}
}
