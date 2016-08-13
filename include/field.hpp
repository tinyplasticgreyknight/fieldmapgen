#pragma once
#ifndef H_FIELD
#define H_FIELD

#include "graph.hpp"
#include "field_iterator.hpp"

namespace fieldmapgen {

	template <typename T, typename TGet=T>
	class IField {
	public:
		typedef MutableFieldIterator<IField<T, TGet>, T, TGet> iterator;
		typedef FieldIterator<const IField<T, TGet>, const T, const TGet> const_iterator;
	public:
		IField(Graph& graph);
		virtual ~IField(void) {};

		const TGet& get_value(Graph::node node) const;
		TGet& get_value(Graph::node node);
		T remove_value(Graph::node node);
		bool add_value(Graph::node node, T value);
		T set_value(Graph::node node, T value);

		iterator begin(void);
		iterator end(void);
		const_iterator cbegin(void) const;
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
		Graph& graph;
	};

#include "field.tmpl.hpp"

}

#endif
