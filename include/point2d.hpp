#ifndef H_POINT2D
#define H_POINT2D

#include <ostream>

namespace fieldmapgen {
	/// @class Point2D
	/// @brief A point in two-dimensional space.
	struct Point2D {
		/// The x-coordinate.
		double x;
		/// The y-coordinate.
		double y;

		/// Equality operator.
		bool operator ==(const Point2D& that);

		/// Returns the point (0, 0).
		static Point2D zero(void);
	};

	/// Streamification operator for `Point2D`.
	std::ostream& operator<<(std::ostream& stream, const Point2D& value);
}

#endif
