#ifndef H_PARTIAL_FIELD
#define H_PARTIAL_FIELD

#include "field.hpp"
#include "option.hpp"
#include <map>

namespace fieldmapgen {
	/// @class PartialField
	/// @brief Assigns an optional value to every node of a `Graph`.
	/// @tparam T The values assigned by the field will be of type `Option<T>`.
	///
	/// This class uses efficient storage so that node positions with no assigned value
	/// don't need to take up any space in memory.
	/// @see IField TotalField Option
	template <typename T>
	class PartialField : public IField<Option<T>> {
	public:
		/// @brief Constructs a new field with no values assigned to any node.
		/// @param graph The graph for which this field assigns values.
		PartialField(Graph& graph);

	private:
		virtual const Option<T>& get_value_internal(Graph::node node) const;
		virtual Option<T>& get_value_internal(Graph::node node);
		virtual Option<T> remove_value_internal(Graph::node node);
		virtual bool add_value_internal(Graph::node node, Option<T> value);
		virtual Option<T> set_value_internal(Graph::node node, Option<T> value);

		std::map<Graph::node, Option<T>> values;
		static const Option<T> STATIC_NONE;
	};

#include "partial_field.tmpl.hpp"

}

#endif
