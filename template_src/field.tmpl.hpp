template <typename T, typename TGet>
IField<T, TGet>::IField(Graph& graph)
	: graph(graph) {
}

template <typename T, typename TGet>
TGet& IField<T, TGet>::get_value(Graph::node node) {
	return this->get_value_internal(node);
}

template <typename T, typename TGet>
const TGet& IField<T, TGet>::get_value(Graph::node node) const {
	return this->get_value_internal(node);
}

template <typename T, typename TGet>
T IField<T, TGet>::remove_value(Graph::node node) {
	return this->remove_value_internal(node);
}

template <typename T, typename TGet>
bool IField<T, TGet>::add_value(Graph::node node, T value) {
	return this->add_value_internal(node, value);
}

template <typename T, typename TGet>
T IField<T, TGet>::set_value(Graph::node node, T value) {
	return this->set_value_internal(node, value);
}

template <typename T, typename TGet>
typename IField<T, TGet>::iterator IField<T, TGet>::begin(void) {
	return IField::iterator(graph.begin(), *this);
}

template <typename T, typename TGet>
typename IField<T, TGet>::iterator IField<T, TGet>::end(void) {
	return IField::iterator(graph.end(), *this);
}

template <typename T, typename TGet>
typename IField<T, TGet>::const_iterator IField<T, TGet>::cbegin(void) const {
	const IField<T, TGet>& f = *this;
	return IField::const_iterator(graph.begin(), f);
}

template <typename T, typename TGet>
typename IField<T, TGet>::const_iterator IField<T, TGet>::cend(void) const {
	const IField<T, TGet>& f = *this;
	return IField::const_iterator(graph.end(), f);
}
