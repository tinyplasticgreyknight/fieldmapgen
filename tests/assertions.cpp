#include "assertions.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int test_support::assert_failed(std::string message, std::string filename, int line_number) {
	cout << filename << ":" << line_number << ": failed: " << message << endl;
	return 1;
}

std::string test_support::assert_format_internal(std::string left_name, std::string relation, std::string right_name, std::string left_val, std::string right_val) {
	std::stringstream ss;
	ss << left_name << " " << relation << " " << right_name << std::endl;
	ss << left_name << ": " << left_val << std::endl;
	ss << right_name << ": " << right_val << std::endl;
	return ss.str();
}

template <>
std::string test_support::assert_value_to_string<bool>(const bool& value) {
	return value ? "true" : "false";
}
