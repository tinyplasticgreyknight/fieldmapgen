#ifndef H_TOTAL_FIELD
#define H_TOTAL_FIELD

#include "field.hpp"
#include <vector>
#include <functional>

namespace fieldmapgen {

	template <typename T>
	class TotalField : public IField<T> {
	public:
		TotalField(Graph& graph, T default_value);
		TotalField(Graph& graph, std::function<T(Graph::node)> func);

	private:
		virtual const T& get_value_internal(Graph::node node) const;
		virtual T& get_value_internal(Graph::node node);
		virtual T remove_value_internal(Graph::node node);
		virtual bool add_value_internal(Graph::node node, T value);
		virtual T set_value_internal(Graph::node node, T value);

		T default_value;
		std::vector<T> values;
	};

#include "total_field.tmpl.hpp"

}

#endif
