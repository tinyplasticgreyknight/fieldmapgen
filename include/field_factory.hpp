#ifndef H_FIELD_FACTORY
#define H_FIELD_FACTORY

#include "graph.hpp"
#include "field.hpp"
#include "option.hpp"
#include "total_field.hpp"
#include "partial_field.hpp"
#include <functional>

namespace fieldmapgen {
	class FieldFactory {
	public:
		FieldFactory(Graph& graph);

		template <typename T>
		IField<T>* create_flat(T default_value);

		template <typename T>
		IField<T>* create_from_function(std::function<T(Graph::node)> func);

		template <typename T>
		IField<Option<T>>* create_partial(void);

		template <typename T>
		IField<Option<T>>* create_partial_from_function(std::function<Option<T>(Graph::node)> func);

		template <typename T1, typename TR>
		IField<TR>* map(IField<T1>* field1, std::function<TR(T1)> func);

		template <typename T1, typename T2, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, std::function<TR(T1, T2)> func);

		template <typename T1, typename T2, typename T3, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, std::function<TR(T1, T2, T3)> func);

		template <typename T1, typename T2, typename T3, typename T4, typename TR>
		IField<TR>* map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, IField<T4>* field4, std::function<TR(T1, T2, T3, T4)> func);

	private:
		Graph& graph;
	};

#include "field_factory.tmpl.hpp"

}

#endif
