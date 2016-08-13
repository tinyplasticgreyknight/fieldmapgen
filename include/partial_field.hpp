#ifndef H_PARTIAL_FIELD
#define H_PARTIAL_FIELD

#include "field.hpp"
#include "option.hpp"
#include <map>

namespace fieldmapgen {

	template <typename T>
	class PartialField : public IField<Option<T>> {
	public:
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
