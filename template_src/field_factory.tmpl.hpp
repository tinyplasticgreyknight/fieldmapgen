template <typename T>
IField<T>* FieldFactory::create_flat(T default_value) {
	return new TotalField<T>(graph, default_value);
}

template <typename T>
IField<T>* FieldFactory::create_from_function(std::function<T(Graph::node)> func) {
	return new TotalField<T>(graph, func);
}

template <typename T>
IField<Option<T>>* FieldFactory::create_partial(void) {
	return new PartialField<T>(graph);
}

template <typename T>
IField<Option<T>>* FieldFactory::create_partial_from_function(std::function<Option<T>(Graph::node)> func) {
	auto field = new PartialField<T>(graph);
	for (auto n : graph) {
		field->set_value(n, func(n));
	}

	return field;
}

template <typename T1, typename TR>
IField<TR>* FieldFactory::map(IField<T1>* field1, std::function<TR(T1)> func) {
	auto iter1 = field1->begin();
	std::function<TR(Graph::node)> zipper
		= [&iter1, func](Graph::node n) {
			return func(*(iter1+n));
		};
	auto result = new TotalField<TR>(graph, zipper);
	return result;
}

template <typename T1, typename T2, typename TR>
IField<TR>* FieldFactory::map(IField<T1>* field1, IField<T2>* field2, std::function<TR(T1, T2)> func) {
	auto iter1 = field1->begin();
	auto iter2 = field2->begin();
	std::function<TR(Graph::node)> zipper
		= [&iter1, &iter2, func](Graph::node n) {
			return func(*(iter1+n), *(iter2+n));
		};
	auto result = new TotalField<TR>(graph, zipper);
	return result;
}

template <typename T1, typename T2, typename T3, typename TR>
IField<TR>* FieldFactory::map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, std::function<TR(T1, T2, T3)> func) {
	auto iter1 = field1->begin();
	auto iter2 = field2->begin();
	auto iter3 = field3->begin();
	std::function<TR(Graph::node)> zipper
		= [&iter1, &iter2, &iter3, func](Graph::node n) {
			return func(*(iter1+n), *(iter2+n), *(iter3+n));
		};
	auto result = new TotalField<TR>(graph, zipper);
	return result;
}

template <typename T1, typename T2, typename T3, typename T4, typename TR>
IField<TR>* FieldFactory::map(IField<T1>* field1, IField<T2>* field2, IField<T3>* field3, IField<T4>* field4, std::function<TR(T1, T2, T3, T4)> func) {
	auto iter1 = field1->begin();
	auto iter2 = field2->begin();
	auto iter3 = field3->begin();
	auto iter4 = field4->begin();
	std::function<TR(Graph::node)> zipper
		= [&iter1, &iter2, &iter3, &iter4, func](Graph::node n) {
			return func(*(iter1+n), *(iter2+n), *(iter3+n), *(iter4+n));
		};
	auto result = new TotalField<TR>(graph, zipper);
	return result;
}
