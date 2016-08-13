#include "test_support.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return RUN_ALL_TESTS();
	}

	return DISPATCH_TEST(argv[1]);
}
