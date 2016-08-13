template <typename TField, typename T>
FieldIterator<TField, T>::FieldIterator(Graph::const_iterator graph_iter, TField& field)
	: graph_iter(graph_iter)
	, field(field) {
}

template <typename TField, typename T>
FieldIterator<TField, T>::FieldIterator(const FieldIterator<TField, T>& that)
	: RandomAccessIterator<FieldIterator<TField, T>, T, std::ptrdiff_t>()
	, graph_iter(that.graph_iter)
	, field(that.field) {
}

template <typename TField, typename T>
FieldIterator<TField, T>& FieldIterator<TField, T>::operator =(const FieldIterator<TField, T>& that) {
	if(this != &that) {
		graph_iter = that.graph_iter;
		field = that.field;
	}

	return *this;
}

template <typename TField, typename T>
void FieldIterator<TField, T>::increment(void) {
	++graph_iter;
}

template <typename TField, typename T>
void FieldIterator<TField, T>::decrement(void) {
	--graph_iter;
}

template <typename TField, typename T>
void FieldIterator<TField, T>::adjust_value(std::ptrdiff_t offset) {
	graph_iter += offset;
}

template <typename TField, typename T>
bool FieldIterator<TField, T>::is_equal(const FieldIterator<TField, T>& that) {
	return graph_iter == that.graph_iter; // TODO && field == that.field;
}

template <typename TField, typename T>
T& FieldIterator<TField, T>::dereference(void) const {
	return field.get_value(*graph_iter);
}

template <typename TField, typename T>
std::ptrdiff_t FieldIterator<TField, T>::distance_to(const FieldIterator<TField, T>& that) {
	return graph_iter - that.graph_iter;
}

template <typename TField, typename T>
std::ptrdiff_t FieldIterator<TField, T>::zero_distance(void) const {
	return (std::ptrdiff_t)0;
}

// ====

template <typename TField, typename T>
MutableFieldIterator<TField, T>::MutableFieldIterator(Graph::const_iterator graph_iter, TField& field)
	: FieldIterator<TField, T>(graph_iter, field) {
}

template <typename TField, typename T>
MutableFieldIterator<TField, T>::MutableFieldIterator(const MutableFieldIterator<TField, T>& that)
	: FieldIterator<TField, T>(that.graph_iter, that.field) {
}

template <typename TField, typename T>
void MutableFieldIterator<TField, T>::set_value(T new_value) {
	this->field.set_value(*(this->graph_iter), new_value);
}
