#include "partial_field.hpp"

template <typename T>
const Option<T> PartialField<T>::STATIC_NONE = None<T>();

template <typename T>
PartialField<T>::PartialField(Graph& graph)
	: IField<Option<T>>(graph) {
}

template <typename T>
const Option<T>& PartialField<T>::get_value_internal(Graph::node node) const {
	auto iter = this->values.find(node);
	if (iter == this->values.end()) {
		return STATIC_NONE;
	}

	return iter->second;
}

template <typename T>
Option<T>& PartialField<T>::get_value_internal(Graph::node node) {
	auto iter = this->values.find(node);
	if (iter == this->values.end()) {
		auto p = this->values.insert({ node, None<T>() });
		iter = p.first;
	}

	return iter->second;
}

template <typename T>
Option<T> PartialField<T>::remove_value_internal(Graph::node node) {
	auto iter = this->values.find(node);
	if (iter == this->values.end()) {
		return None<T>();
	} else {
		auto result = iter->second;
		this->values.erase(iter);
		return result;
	}
}

template <typename T>
bool PartialField<T>::add_value_internal(Graph::node node, Option<T> value) {
	if (value.is_none()) {
		return false;
	}

	auto result = this->values.insert({ node, value });
	return result.second;
}

template <typename T>
Option<T> PartialField<T>::set_value_internal(Graph::node node, Option<T> value) {
	auto iter = this->values.find(node);
	if (iter == this->values.end()) {
		if (value.is_none()) {
			return value;
		}

		this->values.insert({ node, value });
		return None<T>();
	} else {
		auto result = iter->second;
		this->values.erase(iter);
		if (value.is_some()) {
			this->values.insert({ node, value });
		}

		return result;
	}
}
