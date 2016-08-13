#ifndef H_RANDOM_ACCESS_ITERATOR
#define H_RANDOM_ACCESS_ITERATOR

#include <iterator>

namespace fieldmapgen {
	template <typename self_type, typename T, typename distance_type>
	class RandomAccessIterator {
	public:
		typedef T value_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	public:
		self_type& operator ++(void);
		self_type operator ++(int);
		self_type& operator --(void);
		self_type operator --(int);
		self_type& operator +=(distance_type offset);
		self_type& operator -=(distance_type offset);
		self_type operator +(distance_type offset) const;
		self_type operator -(distance_type offset) const;
		distance_type operator -(const self_type& that);

		bool operator ==(const self_type& that);
		bool operator !=(const self_type& that);
		bool operator <(const self_type& that);
		bool operator >(const self_type& that);
		bool operator <=(const self_type& that);
		bool operator >=(const self_type& that);
		T& operator *(void) const;
		T& operator [](distance_type index) const;

		friend self_type operator +(distance_type offset, const self_type& that) {
			self_type result(that);
			return result += offset;
		}

	protected:
		RandomAccessIterator(void) {}
		virtual ~RandomAccessIterator(void) {}

	private:
		RandomAccessIterator(const RandomAccessIterator& that) = delete;
		self_type& operator =(const self_type& that) = delete;

	private:
		virtual T& dereference(void) const = 0;
		virtual void set_value(T new_value) = 0;
		virtual void increment(void) = 0;
		virtual void decrement(void) = 0;
		virtual void adjust_value(distance_type offset) = 0;
		virtual bool is_equal(const self_type& that) = 0;
		virtual distance_type distance_to(const self_type& that) = 0;
		virtual distance_type zero_distance(void) const = 0;
	};

#include "random_access_iterator.tmpl.hpp"

}

#endif
