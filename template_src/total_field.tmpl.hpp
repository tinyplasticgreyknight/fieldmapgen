#include "total_field.hpp"

template <typename T>
TotalField<T>::TotalField(Graph& graph, T default_value)
	: IField<T>(graph)
	, default_value(default_value)
	, values(graph.order(), default_value) {
}

template <typename T>
TotalField<T>::TotalField(Graph& graph, std::function<T(Graph::node)> func)
	: IField<T>(graph)
	, values() {
	for (auto n : graph) {
		values.push_back(func(n));
	}

	default_value = values[0];
}

template <typename T>
const T& TotalField<T>::get_value_internal(Graph::node node) const {
	return this->values.at(node);
}

template <typename T>
T& TotalField<T>::get_value_internal(Graph::node node) {
	return this->values.at(node);
}

template <typename T>
T TotalField<T>::remove_value_internal(Graph::node node) {
	return this->set_value_internal(node, this->default_value);
}

template <typename T>
bool TotalField<T>::add_value_internal(Graph::node node, T value) {
	auto iter = this->values.begin() + node;
	if (*iter == this->default_value) {
		*iter = value;
		return true;
	} else {
		return false;
	}
}

template <typename T>
T TotalField<T>::set_value_internal(Graph::node node, T value) {
	auto iter = this->values.begin() + node;
	auto previous = *iter;
	*iter = value;
	return previous;
}
