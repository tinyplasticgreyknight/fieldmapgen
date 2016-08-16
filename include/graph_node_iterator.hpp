#ifndef H_GRAPH_NODE_ITERATOR
#define H_GRAPH_NODE_ITERATOR

#include "random_access_iterator.hpp"

namespace fieldmapgen {
	/// @class GraphNodeIterator
	/// @brief An iterator type for constant iterators over graph nodes.
	/// @see RandomAccessIterator
	class GraphNodeIterator : public RandomAccessIterator<GraphNodeIterator, const size_t, std::ptrdiff_t> {
	public:
		GraphNodeIterator(size_t position, size_t lower, size_t upper);
		GraphNodeIterator(const GraphNodeIterator& that);
		GraphNodeIterator& operator =(const GraphNodeIterator& that);

	private:
		virtual const size_t& dereference(void) const;
		virtual void set_value(const size_t new_value);
		virtual void increment(void);
		virtual void decrement(void);
		virtual void adjust_value(std::ptrdiff_t offset);
		virtual bool is_equal(const GraphNodeIterator& that);
		virtual std::ptrdiff_t distance_to(const GraphNodeIterator& that);
		virtual std::ptrdiff_t zero_distance(void) const;
		static std::ptrdiff_t distance_v(size_t a, size_t b);

		size_t current;
		size_t start;
		size_t limit;
	};
}

#endif
