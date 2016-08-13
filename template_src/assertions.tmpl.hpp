template <>
std::string assert_value_to_string<bool>(const bool& value);

template <typename T>
std::string assert_value_to_string(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template <typename T>
std::string assert_format(std::string left_name, std::string relation, std::string right_name, const T& left_val, const T& right_val) {
	return assert_format_internal(
		left_name,
		relation,
		right_name,
		assert_value_to_string(left_val),
		assert_value_to_string(right_val));
}
