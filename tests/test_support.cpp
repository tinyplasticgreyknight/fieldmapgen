#include "test_support.hpp"
#include <iostream>

using namespace std;
using namespace test_support;

TestHub::TestHub(void) {
}

TestHub& TestHub::instance(void) {
	static TestHub* _instance = new TestHub();
	return *_instance;
}

int TestHub::register_test(string name, function<int(void)> func) {
	this->registry.insert({ name, func });
	return 0;
}

int TestHub::dispatch(string name) {
	auto iter = this->registry.find(name);
	if (iter == this->registry.end()) {
		cout << "no such test: " << name << endl;
		return 1;
	}

	return (iter->second)();
}

int print_status_string(int status) {
	string label = status == 0 ? "[OK]" : "[FAILED]";
	cout << label << endl;
	return status;
}

int TestHub::run_all(void) {
	size_t num_run = 0;
	size_t num_fail = 0;
	for (auto entry : this->registry) {
		num_run++;
		cout << entry.first << ":" << endl;
		int entry_status = entry.second();
		print_status_string(entry_status);
		if (entry_status != 0) {
			num_fail++;
		}
	}

	cout << "=================" << endl;
	cout << "failures: " << num_fail << "/" << num_run << endl;
	return print_status_string(num_fail != 0);
}
