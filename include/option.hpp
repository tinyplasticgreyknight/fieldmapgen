#ifndef H_OPTION
#define H_OPTION

#include <functional>
#include <iostream>

namespace fieldmapgen {
	template <typename T>
	class Option;

	template <typename T>
	std::ostream& operator<<(std::ostream& stream, const Option<T>& value) {
		if (value.is_some()) {
			stream << "Some(" << value.data << ")";
		} else {
			stream << "None";
		}

		return stream;
	}

	template <typename T>
	Option<T> Some(T value) {
		return Option<T>::Some(value);
	}

	template <typename T>
	Option<T> None(void) {
		return Option<T>::None();
	}

	template <typename T>
	class Option {
	public:
		static Option Some(const T& data) { return Option(data); };
		static Option None(void) { return Option(); };

		Option(void)
			: some(false) {
		}

		Option(const T& data)
			: data(data)
			, some(true) {
		}

		Option(const Option& that)
			: data(that.data)
			, some(that.some) {
		}

		Option& operator=(const Option& that) {
			data = that.data;
			some = that.some;
			return *this;
		}

		~Option(void) {
		}

		bool is_some(void) const { return this->some; }
		bool is_none(void) const { return !this->some; }

		template <typename U>
		Option<U> map(std::function<U(T)> func) const {
			if (this->is_some()) {
				return Option<U>::Some(func(this->data));
			} else {
				return Option<U>::None();
			}
		}

		const T& unwrap(void) {
			if (is_none()) {
				throw "attempt to unwrap None";
			}

			return data;
		}

		bool operator==(const Option& that) const {
			if (this->some != that.some) {
				return false;
			} else if (that.some) {
				return this->data == that.data;
			} else {
				return true;
			}
		}

		bool operator!=(const Option& that) const {
			return !(*this == that);
		}

		friend std::ostream& operator<< <T>(std::ostream& stream, const Option<T>& value);

	private:
		T data{};
		bool some;
	};

}

#endif
