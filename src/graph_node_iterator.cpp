#include "graph_node_iterator.hpp"

using namespace std;
using namespace fieldmapgen;

GraphNodeIterator::GraphNodeIterator(size_t position, size_t lower, size_t upper)
	: current(position)
	, start(lower)
	, limit(upper) {
}

GraphNodeIterator::GraphNodeIterator(const GraphNodeIterator& that)
	: RandomAccessIterator()
	, current(that.current)
	, start(that.start)
	, limit(that.limit) {
}

GraphNodeIterator& GraphNodeIterator::operator =(const GraphNodeIterator& that) {
	if(this != &that) {
		limit = that.limit;
		start = that.start;
		current = that.current;
	}

	return *this;
}

void GraphNodeIterator::set_value(size_t new_value) {
	if (new_value < start) {
		current = start;
	} else if (new_value > limit) {
		current = limit;
	} else {
		current = new_value;
	}
}

void GraphNodeIterator::increment(void) {
	if (current < limit) {
		current++;
	}
}

void GraphNodeIterator::decrement(void) {
	if (current > start) {
		current--;
	}
}

void GraphNodeIterator::adjust_value(ptrdiff_t offset) {
	if (offset < 0) {
		offset = -offset;
		if (distance_v(current, start) < offset) {
			current = start;
		} else {
			current -= (size_t)offset;
		}
	} else if (offset > 0) {
		if (distance_v(limit, current) < offset) {
			current = limit;
		} else {
			current += (size_t)offset;
		}
	}
}

bool GraphNodeIterator::is_equal(const GraphNodeIterator& that) {
	return current == that.current && limit == that.limit;
}

const size_t& GraphNodeIterator::dereference(void) const {
	return current;
}

ptrdiff_t GraphNodeIterator::distance_to(const GraphNodeIterator& that) {
	return distance_v(current, that.current);
}

std::ptrdiff_t GraphNodeIterator::distance_v(size_t a, size_t b) {
	if (a < b) {
		return -(ptrdiff_t)(b - a);
	} else {
		return (ptrdiff_t)(a - b);
	}
}

ptrdiff_t GraphNodeIterator::zero_distance(void) const {
	return (ptrdiff_t)0;
}
