template <typename TField, typename T, typename TGet>
FieldIterator<TField, T, TGet>::FieldIterator(Graph::const_iterator graph_iter, TField& field)
	: graph_iter(graph_iter)
	, field(field) {
}

template <typename TField, typename T, typename TGet>
FieldIterator<TField, T, TGet>::FieldIterator(const FieldIterator<TField, T, TGet>& that)
	: RandomAccessIterator<FieldIterator<TField, T, TGet>, TGet, std::ptrdiff_t>()
	, graph_iter(that.graph_iter)
	, field(that.field) {
}

template <typename TField, typename T, typename TGet>
FieldIterator<TField, T, TGet>& FieldIterator<TField, T, TGet>::operator =(const FieldIterator<TField, T, TGet>& that) {
	if(this != &that) {
		graph_iter = that.graph_iter;
		field = that.field;
	}

	return *this;
}

template <typename TField, typename T, typename TGet>
void FieldIterator<TField, T, TGet>::increment(void) {
	++graph_iter;
}

template <typename TField, typename T, typename TGet>
void FieldIterator<TField, T, TGet>::decrement(void) {
	--graph_iter;
}

template <typename TField, typename T, typename TGet>
void FieldIterator<TField, T, TGet>::adjust_value(std::ptrdiff_t offset) {
	graph_iter += offset;
}

template <typename TField, typename T, typename TGet>
bool FieldIterator<TField, T, TGet>::is_equal(const FieldIterator<TField, T, TGet>& that) {
	return graph_iter == that.graph_iter; // TODO && field == that.field;
}

template <typename TField, typename T, typename TGet>
TGet& FieldIterator<TField, T, TGet>::dereference(void) const {
	return field.get_value(*graph_iter);
}

template <typename TField, typename T, typename TGet>
std::ptrdiff_t FieldIterator<TField, T, TGet>::distance_to(const FieldIterator<TField, T, TGet>& that) {
	return graph_iter - that.graph_iter;
}

template <typename TField, typename T, typename TGet>
std::ptrdiff_t FieldIterator<TField, T, TGet>::zero_distance(void) const {
	return (std::ptrdiff_t)0;
}

// ====

template <typename TField, typename T, typename TGet>
MutableFieldIterator<TField, T, TGet>::MutableFieldIterator(Graph::const_iterator graph_iter, TField& field)
	: FieldIterator<TField, T, TGet>(graph_iter, field) {
}

template <typename TField, typename T, typename TGet>
MutableFieldIterator<TField, T, TGet>::MutableFieldIterator(const MutableFieldIterator<TField, T, TGet>& that)
	: FieldIterator<TField, T, TGet>(that.graph_iter, that.field) {
}

template <typename TField, typename T, typename TGet>
void MutableFieldIterator<TField, T, TGet>::set_value(TGet new_value) {
	this->field.set_value(*(this->graph_iter), new_value);
}
