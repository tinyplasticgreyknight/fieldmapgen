#ifndef H_TEST_SUPPORT
#define H_TEST_SUPPORT

#include <ostream>
#include <map>
#include <vector>
#include <functional>
#include <string>

template <typename T>
inline std::ostream& operator <<(std::ostream& stream, const std::vector<T>& value) {
	stream << "{";
	bool comma = false;
	for (auto elem : value) {
		if (comma) {
			stream << ", ";
		}

		stream << elem;
		comma = true;
	}
	stream << " }";
	return stream;
}

namespace test_support {

	class TestHub {
	public:
		static TestHub& instance(void);
		int register_test(std::string name, std::function<int(void)> func);
		int dispatch(std::string name);
		int run_all(void);

	private:
		TestHub(void);

		std::map<std::string, std::function<int(void)>> registry;
	};

}

#define DUMMY_RVALUE(nm) __dummy_test_register_##nm

#define REGISTER_TEST(nm) test_support::TestHub::instance().register_test(#nm, nm)

#define TEST_CASE(nm) \
	int nm (void); \
	static int DUMMY_RVALUE(nm) = REGISTER_TEST(nm); \
	int nm (void)

#define IGNORE(nm) int nm (void)

#define RUN_ALL_TESTS() test_support::TestHub::instance().run_all()

#define DISPATCH_TEST(name) test_support::TestHub::instance().dispatch(name)

#endif
