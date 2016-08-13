#ifndef H_FIELD_FACTORY
#define H_FIELD_FACTORY

#include "graph.hpp"
#include "field.hpp"
#include "option.hpp"
#include "total_field.hpp"
#include "partial_field.hpp"
#include <functional>

namespace fieldmapgen {
	/// @class FieldFactory
	/// @brief Creates new instances of `IField<T>` for a given `Graph`.
	/// @see IField TotalField PartialField
	class FieldFactory {
	public:
		/// @brief Constructs a new `FieldFactory` for the `Graph` in question.
		/// @param graph The graph to construct fields for.
		FieldFactory(Graph& graph);

		/// @brief Constructs a `TotalField<T>` containing the specified default value at every node.
		/// @param default_value The default value.
		/// @return An owned pointer to the field.
		template <typename T>
		IField<T>* create_flat(T default_value);

		/// @brief Constructs a `TotalField<T>` containing the output of the given function at every node.
		/// @param func The function to enumerate over the graph.
		/// @return An owned pointer to the field.
		template <typename T>
		IField<T>* create_from_function(std::function<T(Graph::node)> func);

		/// @brief Constructs a `PartialField<T>` with every node empty.
		/// @return An owned pointer to the field.
		template <typename T>
		IField<Option<T>>* create_partial(void);

		/// @brief Constructs a `PartialField<T>` with every node assigned a value based on the given function.
		/// @param func A function which returns an `Option<T>` for every node.
		/// @return An owned pointer to the field.
		template <typename T>
		IField<Option<T>>* create_partial_from_function(std::function<Option<T>(Graph::node)> func);

		/// @brief Maps the specified function over the values in the input field, producing a new field from the results.
		/// @param field1 Values are taken from this field to the function parameter.
		/// @param func The results of this function define the initial values of the returned field.
		/// @return An owned pointer to a new field.
		template <typename T1, typename TR>
		IField<TR>* map(IField<T1>* field1, std::function<TR(T1)> func);

		/// @brief Maps the specified function over the values in the input fields, producing a new field from the results.
		/// @param field1 Values are taken from this field to the first function parameter.
		/// @param field2 Values are taken from this field to the second function parameter.
		/// @param func The results of this function define the initial values of the returned field.
		/// @return An owned pointer to a new field.
		template <typename T1, typename T2, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, std::function<TR(T1, T2)> func);

		/// @brief Maps the specified function over the values in the input fields, producing a new field from the results.
		/// @param field1 Values are taken from this field to the first function parameter.
		/// @param field2 Values are taken from this field to the second function parameter.
		/// @param field3 Values are taken from this field to the third function parameter.
		/// @param func The results of this function define the initial values of the returned field.
		/// @return An owned pointer to a new field.
		template <typename T1, typename T2, typename T3, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, std::function<TR(T1, T2, T3)> func);

		/// @brief Maps the specified function over the values in the input fields, producing a new field from the results.
		/// @param field1 Values are taken from this field to the first function parameter.
		/// @param field2 Values are taken from this field to the second function parameter.
		/// @param field3 Values are taken from this field to the third function parameter.
		/// @param field4 Values are taken from this field to the fourth function parameter.
		/// @param func The results of this function define the initial values of the returned field.
		/// @return An owned pointer to a new field.
		template <typename T1, typename T2, typename T3, typename T4, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, IField<T4>* field4, std::function<TR(T1, T2, T3, T4)> func);

	private:
		Graph& graph;
	};

#include "field_factory.tmpl.hpp"

}

#endif
