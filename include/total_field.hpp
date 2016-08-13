#ifndef H_TOTAL_FIELD
#define H_TOTAL_FIELD

#include "field.hpp"
#include <vector>
#include <functional>

namespace fieldmapgen {
	/// @class TotalField
	/// @brief Assigns a value to every node of a `Graph`.
	/// @tparam T The type of the values assigned by the field.
	/// @see IField PartialField
	template <typename T>
	class TotalField : public IField<T> {
	public:
		/// @brief Constructs a new field with the specified default value.
		/// @param graph The graph for which this field assigns values.
		/// @param default_value The default value of the field.
		TotalField(Graph& graph, T default_value);
		/// @brief Constructs a new field with initial values specified by a function over nodes.
		/// @param graph The graph for which this field assigns values.
		/// @param func A function mapping an initial value for every node position.
		///
		/// The default value of the field will be `func(0)`.
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
