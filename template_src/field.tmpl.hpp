template <typename T>
IField<T>::IField(Graph& graph)
	: graph(graph) {
}

template <typename T>
T& IField<T>::get_value(Graph::node node) {
	return this->get_value_internal(node);
}

template <typename T>
const T& IField<T>::get_value(Graph::node node) const {
	return this->get_value_internal(node);
}

template <typename T>
T IField<T>::remove_value(Graph::node node) {
	return this->remove_value_internal(node);
}

template <typename T>
bool IField<T>::add_value(Graph::node node, T value) {
	return this->add_value_internal(node, value);
}

template <typename T>
T IField<T>::set_value(Graph::node node, T value) {
	return this->set_value_internal(node, value);
}

template <typename T>
void IField<T>::map_in_place(std::function<T(Graph::node, T)> func) {
	auto iter = begin();
	for (auto n : graph) {
		*iter = func(n, *iter);
		iter++;
	}
}

template <typename T>
typename IField<T>::iterator IField<T>::begin(void) {
	return IField::iterator(graph.begin(), *this);
}

template <typename T>
typename IField<T>::iterator IField<T>::end(void) {
	return IField::iterator(graph.end(), *this);
}

template <typename T>
typename IField<T>::const_iterator IField<T>::cbegin(void) const {
	const IField<T>& f = *this;
	return IField::const_iterator(graph.begin(), f);
}

template <typename T>
typename IField<T>::const_iterator IField<T>::cend(void) const {
	const IField<T>& f = *this;
	return IField::const_iterator(graph.end(), f);
}
