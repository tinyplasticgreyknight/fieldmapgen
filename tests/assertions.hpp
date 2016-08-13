#ifndef H_ASSERTIONS
#define H_ASSERTIONS

#include <string>
#include <sstream>
#include <vector>

namespace test_support {

	int assert_failed(std::string message, std::string filename, int line_number);

	template <typename T>
	std::string assert_value_to_string(const T& value);

	std::string assert_format_internal(std::string left_name, std::string relation, std::string right_name, std::string left_val, std::string right_val);

	template <typename T>
	std::string assert_format(std::string left_name, std::string relation, std::string right_name, const T& left_val, const T& right_val);

#include "assertions.tmpl.hpp"

}

#define ASSERT_GENERAL(a, msg) if (!(a)) { return test_support::assert_failed(msg, __FILE__, __LINE__); }
#define ASSERT_THAT(a) ASSERT_GENERAL(a, #a)
#define ASSERT_TRUE(p) ASSERT_GENERAL(p, "expected true:\nexpression: " #p)
#define ASSERT_SOME(T, exp, opt) ASSERT_EQ(Option<T>::Some(exp), (opt))
#define ASSERT_NONE(T, opt) ASSERT_EQ(Option<T>::None(), (opt))
#define ASSERT_EMPTY(coll) ASSERT_GENERAL((coll).empty(), "expected empty collection\nexpression: " #coll)
#define ASSERT_LIST_EQ(expected, actual) do { \
		auto __assertion_exp = expected; \
		auto __assertion_exp_iter = __assertion_exp.begin(); \
		for (auto __assertion_item : actual) { \
			ASSERT_GENERAL(__assertion_exp_iter != __assertion_exp.end(), "expected same size: actual was too big\nexpression: " #actual); \
			ASSERT_EQ(__assertion_item, *__assertion_exp_iter); \
			__assertion_exp_iter++; \
		} \
		ASSERT_GENERAL(__assertion_exp_iter == __assertion_exp.end(), "expected same size: actual was too small\nexpression: " #actual); \
	} while(0)
#define ASSERT_EQ(expected, actual) do { \
		auto __assertion_exp = (expected); \
		auto __assertion_act = (actual); \
		ASSERT_GENERAL(__assertion_exp == __assertion_act, test_support::assert_format("expected", "==", "actual", __assertion_exp, __assertion_act)); \
	} while(0)

#endif
