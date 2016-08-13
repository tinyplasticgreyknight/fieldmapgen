#ifndef H_FIELD_ITERATOR
#define H_FIELD_ITERATOR

#include "graph.hpp"
#include "random_access_iterator.hpp"

namespace fieldmapgen {
	template <typename TField, typename T, typename TGet>
	class FieldIterator : public RandomAccessIterator<FieldIterator<TField, T, TGet>, TGet, std::ptrdiff_t> {
	public:
		typedef TGet value_type;

	public:
		FieldIterator(Graph::const_iterator graph_iter, TField& field);
		FieldIterator(const FieldIterator& that);
		FieldIterator& operator =(const FieldIterator& that);

	private:
		virtual value_type& dereference(void) const;
		virtual void set_value(value_type) {}
		virtual void increment(void);
		virtual void decrement(void);
		virtual void adjust_value(std::ptrdiff_t offset);
		virtual bool is_equal(const FieldIterator& that);
		virtual std::ptrdiff_t distance_to(const FieldIterator& that);
		virtual std::ptrdiff_t zero_distance(void) const;

	protected:
		Graph::const_iterator graph_iter;
		TField& field;
	};

	template <typename TField, typename T, typename TGet>
	class MutableFieldIterator : public FieldIterator<TField, T, TGet> {
	public:
		typedef TGet value_type;

	public:
		MutableFieldIterator(Graph::const_iterator graph_iter, TField& field);
		MutableFieldIterator(const MutableFieldIterator& that);

	private:
		virtual void set_value(value_type new_value);
	};

#include "field_iterator.tmpl.hpp"

}

#endif
