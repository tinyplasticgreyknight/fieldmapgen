template <typename self_type, typename value_type, typename distance_type>
self_type& RandomAccessIterator<self_type, value_type, distance_type>::operator ++(void) {
	increment();
	return *static_cast<self_type*>(this);
}

template <typename self_type, typename value_type, typename distance_type>
self_type RandomAccessIterator<self_type, value_type, distance_type>::operator ++(int) {
	self_type result(*static_cast<self_type*>(this));
	++(*static_cast<self_type*>(this));
	return result;
}

template <typename self_type, typename value_type, typename distance_type>
self_type& RandomAccessIterator<self_type, value_type, distance_type>::operator --() {
	decrement();
	return *static_cast<self_type*>(this);
}

template <typename self_type, typename value_type, typename distance_type>
self_type RandomAccessIterator<self_type, value_type, distance_type>::operator --(int) {
	self_type result(*this);
	--(*static_cast<self_type*>(this));
	return result;
}

template <typename self_type, typename value_type, typename distance_type>
self_type& RandomAccessIterator<self_type, value_type, distance_type>::operator +=(distance_type offset) {
	adjust_value(offset);
	return *static_cast<self_type*>(this);
}

template <typename self_type, typename value_type, typename distance_type>
self_type& RandomAccessIterator<self_type, value_type, distance_type>::operator -=(distance_type offset) {
	adjust_value(-offset);
	return *static_cast<self_type*>(this);
}

template <typename self_type, typename value_type, typename distance_type>
self_type RandomAccessIterator<self_type, value_type, distance_type>::operator +(distance_type offset) const {
	self_type result(*static_cast<const self_type*>(this));
	return result += offset;
}

template <typename self_type, typename value_type, typename distance_type>
self_type RandomAccessIterator<self_type, value_type, distance_type>::operator -(distance_type offset) const {
	self_type result(*static_cast<const self_type*>(this));
	return result -= offset;
}

template <typename self_type, typename value_type, typename distance_type>
distance_type RandomAccessIterator<self_type, value_type, distance_type>::operator -(const self_type& that) {
	return distance_to(that);
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator ==(const self_type& that) {
	return is_equal(that);
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator !=(const self_type& that) {
	return !is_equal(that);
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator <(const self_type& that) {
	return distance_to(that) < zero_distance();
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator >(const self_type& that) {
	return distance_to(that) > zero_distance();
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator <=(const self_type& that) {
	return distance_to(that) <= zero_distance();
}

template <typename self_type, typename value_type, typename distance_type>
bool RandomAccessIterator<self_type, value_type, distance_type>::operator >=(const self_type& that) {
	return distance_to(that) >= zero_distance();
}

template <typename self_type, typename value_type, typename distance_type>
value_type& RandomAccessIterator<self_type, value_type, distance_type>::operator *(void) const {
	return dereference();
}

template <typename self_type, typename value_type, typename distance_type>
value_type& RandomAccessIterator<self_type, value_type, distance_type>::operator [](distance_type index) const {
	return *(*static_cast<const self_type*>(this) + index);
}
