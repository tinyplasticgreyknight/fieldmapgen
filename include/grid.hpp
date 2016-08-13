#ifndef H_GRID
#define H_GRID

#include "point2d.hpp"
#include "graph.hpp"
#include "field.hpp"

#include <functional>

namespace fieldmapgen {
	/// @class Grid
	/// @brief Easy way of creating a `Graph` with an associated `IField<Point2D>` of node positions.
	/// @see Graph IField
	class Grid {
	public:
		/// Type of the field points; currently just fixed at `Point2D`.
		typedef Point2D point;
	public:
		/// @brief Creates a square grid with `width * height` nodes.
		/// @param width The number of nodes per row.
		/// @param height The number of nodes per column.
		/// @param cell_width The horizontal spacing between node columns.
		/// @param cell_height The vertical spacing between node rows.
		/// @return The new grid created.
		static Grid Square(size_t width, size_t height, double cell_width, double cell_height);
		/// Destructor.
		~Grid(void);

		/// Gets a reference to the underlying graph, so you can create more fields on it.
		Graph& get_graph(void);
		/// Gets a pointer to the field of points.
		IField<point>* get_points(void);
	private:
		Grid(size_t order);
		Grid(size_t order, std::function<point(Graph::node)> init_func);

		Graph graph;
		IField<point>* field_points;
	};
}

#endif
