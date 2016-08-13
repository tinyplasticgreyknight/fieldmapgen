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

void print_status_string(int status) {
	string label = status == 0 ? "[PASS]" : "[FAIL]";
	cout << label << endl;
}

int TestHub::run_all(void) {
	int status = 0;
	for (auto entry : this->registry) {
		cout << entry.first << ":" << endl;
		int entry_status = entry.second();
		print_status_string(entry_status);
		if (entry_status != 0) {
			status = entry_status;
		}
	}

	cout << "========" << endl << "OVERALL:" << endl;
	print_status_string(status);
	return status;
}
