#ifndef H_FIELD
#define H_FIELD

#include "graph.hpp"
#include "field_iterator.hpp"

namespace fieldmapgen {
	/// @class IField
	/// @brief Assigns a value to every node of a `Graph`.
	/// @tparam T The type of the values assigned by the field.
	/// @tparam TGet Currently always equal to `T`, will probably be removed.
	/// @see Graph TotalField PartialField
	template <typename T, typename TGet=T>
	class IField {
	public:
		/// Iterator type over all values, in node order.
		typedef MutableFieldIterator<IField<T, TGet>, T, TGet> iterator;
		/// Constant iterator type over all values, in node order.
		typedef FieldIterator<const IField<T, TGet>, const T, const TGet> const_iterator;
	public:
		/// @brief Constructs a new field over the specified graph
		/// @param graph The graph for which this field assigns values.
		IField(Graph& graph);
		/// Destructor.
		virtual ~IField(void) {};

		/// @brief Look up the value assigned by the field for a given node.
		/// @param node The node to look up the value for.
		/// @return A reference to the value assigned by the field for this node.
		const TGet& get_value(Graph::node node) const;
		/// @brief Look up the value assigned by the field for a given node.
		/// @param node The node to look up the value for.
		/// @return A reference to the value assigned by the field for this node.
		TGet& get_value(Graph::node node);
		/// @brief Revert the value for this node to the default value for the field.
		/// @param node The node for which to remove the value.
		/// @return The previous value for the node.
		T remove_value(Graph::node node);
		/// @brief Sets the value for a node if it is currently default, otherwise does nothing.
		/// @param node The node to set the value for.
		/// @param value The new value to set.
		/// @return True if the value was previously default and has been updated;
		/// false if the node had a non-default value (in which case nothing has changed).
		bool add_value(Graph::node node, T value);
		/// @brief Sets the value for a node.
		/// @param node The node to set the value for.
		/// @param value The new value to set.
		/// @return The previous value for the node.
		T set_value(Graph::node node, T value);

		/// Iterator to the value for node 0.
		iterator begin(void);
		/// Iterator past the end of the collection of values.
		iterator end(void);
		/// Constant iterator to the value for node 0.
		const_iterator cbegin(void) const;
		/// Constant iterator past the end of the collection of values.
		const_iterator cend(void) const;

	private:
		IField(const IField & that) = delete;
		IField& operator=(const IField& that) = delete;

	private:
		virtual const TGet& get_value_internal(Graph::node node) const = 0;
		virtual TGet& get_value_internal(Graph::node node) = 0;
		virtual T remove_value_internal(Graph::node node) = 0;
		virtual bool add_value_internal(Graph::node node, T value) = 0;
		virtual T set_value_internal(Graph::node node, T value) = 0;

	protected:
		/// The graph over whose nodes the field values are defined.
		Graph& graph;
	};

#include "field.tmpl.hpp"

}

#endif
