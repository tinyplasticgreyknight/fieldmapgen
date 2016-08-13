#include "grid.hpp"
#include "total_field.hpp"
#include <iostream>

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

void initialise_square_grid_links(Graph* graph, size_t width, size_t height) {
	size_t x_limit = width - 1;
	size_t y_limit = height - 1;
	auto address = [width](size_t i, size_t j) {
		return i + width * j;
	};
	auto link = [graph, address](size_t a, size_t i, size_t j) {
		auto b = address(i, j);
		std::cout << "link("<<a<<", "<<b<<")" << std::endl;
		graph->link(a, b);
	};
	for (size_t i = 0; i < x_limit; i++) {
		for (size_t j = 0; j < y_limit; j++) {
			auto a = address(i, j);
			link(a, i+1, j);
			link(a, i, j+1);
		}

		link(address(i, y_limit), i+1, y_limit);
	}

	for (size_t j = 0; j < y_limit; j++) {
		auto a = address(x_limit, j);
		link(a, x_limit, j+1);
	}
}

Grid Grid::Square(size_t width, size_t height, double cell_width, double cell_height) {
	auto grid = Grid(
		width * height,
		[width, cell_width, cell_height](Graph::node n) {
			size_t x = n % width;
			size_t y = (n - x) / width;
			return Grid::point { ((double)x) * cell_width, ((double)y) * cell_height };
		});

	initialise_square_grid_links(&grid.get_graph(), width, height);

	return grid;
}

Graph& Grid::get_graph(void) {
	return this->graph;
}

IField<Grid::point>* Grid::get_points(void) {
	return this->field_points;
}
