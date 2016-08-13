#include "grid.hpp"
#include "total_field.hpp"

using namespace fieldmapgen;

Grid::Grid(size_t order)
	: graph(Graph(order))
	, field_points(new TotalField<Grid::point>(graph, Grid::point::zero())) {
}

Grid::Grid(size_t order, std::function<point(Graph::node)> init_func)
	: graph(Graph(order))
	, field_points(new TotalField<Grid::point>(graph, init_func)) {
}

Grid::~Grid(void) {
	delete field_points;
	field_points = nullptr;
}

Grid Grid::Square(size_t width, size_t height, double cell_width, double cell_height) {
	auto grid = Grid(
		width * height,
		[width, cell_width, cell_height](Graph::node n) {
			size_t x = n % width;
			size_t y = (n - x) / width;
			return Grid::point { ((double)x) * cell_width, ((double)y) * cell_height };
		});

	return grid;
}

Graph& Grid::get_graph(void) {
	return this->graph;
}

IField<Grid::point>* Grid::get_points(void) {
	return this->field_points;
}
