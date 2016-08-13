#ifndef H_OPTION
#define H_OPTION

#include <functional>
#include <iostream>

namespace fieldmapgen {
	template <typename T>
	class Option;

	/// Streamification operator for `Option<T>`.
	template <typename T>
	std::ostream& operator<<(std::ostream& stream, const Option<T>& value) {
		if (value.is_some()) {
			stream << "Some(" << value.data << ")";
		} else {
			stream << "None";
		}

		return stream;
	}

	/// Type-inferring helper function for creating instances of `Option<T>`.
	template <typename T>
	Option<T> Some(T value) {
		return Option<T>::Some(value);
	}

	/// Type-inferring helper function for creating instances of `Option<T>`.
	template <typename T>
	Option<T> None(void) {
		return Option<T>::None();
	}

	/// @brief Checkable container for a value which may not be present (similar to Haskell's `Maybe`).
	/// @tparam T The type of the value which can be stored.
	template <typename T>
	class Option {
	public:
		static Option Some(const T& data) { return Option(data); };
		static Option None(void) { return Option(); };

		/// @brief Creates an empty `Option<T>`.
		Option(void)
			: some(false) {
		}

		/// @brief Creates an `Option<T>` containing a value.
		/// @param data The value to store.
		Option(const T& data)
			: data(data)
			, some(true) {
		}

		/// @brief Copy constructor.
		Option(const Option& that)
			: data(that.data)
			, some(that.some) {
		}

		/// @brief Assignment operator.
		Option& operator=(const Option& that) {
			data = that.data;
			some = that.some;
			return *this;
		}

		/// Destructor.
		~Option(void) {
		}

		/// Returns true if this `Option<T>` contains a value, false otherwise.
		bool is_some(void) const { return this->some; }
		/// Returns true if this `Option<T>` is empty, false otherwise.
		bool is_none(void) const { return !this->some; }

		/// @brief Applies a function to the contents of this `Option<T>`, if any.
		/// @tparam U The output type of the function.
		/// @param func The function to apply.
		/// @return An `Option<U>` containing the result of the function, if the
		/// original `Option<T>` contained a value.  Otherwise it is empty.
		template <typename U>
		Option<U> map(std::function<U(T)> func) const {
			if (this->is_some()) {
				return Option<U>::Some(func(this->data));
			} else {
				return Option<U>::None();
			}
		}

		/// @brief Unsafely extract the value from the `Option<T>`.
		/// @return The value contained.
		/// @throws Throws if the `Option<T>` was empty.
		const T& unwrap(void) {
			if (is_none()) {
				throw "attempt to unwrap None";
			}

			return data;
		}

		/// Equality operator.
		bool operator==(const Option& that) const {
			if (this->some != that.some) {
				return false;
			} else if (that.some) {
				return this->data == that.data;
			} else {
				return true;
			}
		}

		/// Inequality operator.
		bool operator!=(const Option& that) const {
			return !(*this == that);
		}

		/// Streamification operator.
		friend std::ostream& operator<< <T>(std::ostream& stream, const Option<T>& value);

	private:
		T data{};
		bool some;
	};

}

#endif
