#include "graph.hpp"

using namespace fieldmapgen;

Graph::Graph(size_t order)
	: V_order(order) {
}

Graph::~Graph(void) {
}

size_t Graph::order(void) const {
	return this->V_order;
}

void Graph::link(node a, node b) {
	this->link_oneway(a, b);
	this->link_oneway(b, a);
}

void Graph::link_oneway(node a, node b) {
	this->E_out[a].insert(b);
	this->E_in[b].insert(a);
}

void Graph::unlink(node a, node b) {
	this->unlink_oneway(a, b);
	this->unlink_oneway(b, a);
}

void Graph::unlink_oneway(node a, node b) {
	this->E_out[a].erase(b);
	this->E_in[b].erase(a);
}

const Graph::node_set Graph::get_linked_general(const Graph::connections& conn_map, Graph::node n) const {
	auto iter = conn_map.find(n);
	if (iter == conn_map.end()) {
		return Graph::node_set();
	} else {
		return iter->second;
	}
}

const Graph::node_set Graph::get_linked_from(Graph::node n) const {
	return get_linked_general(this->E_out, n);
}

const Graph::node_set Graph::get_linked_to(Graph::node n) const {
	return get_linked_general(this->E_in, n);
}

const Graph::node_set Graph::get_linked(Graph::node n) const {
	Graph::node_set result;
	for (auto neighbour : get_linked_from(n)) {
		result.insert(neighbour);
	}

	for (auto neighbour : get_linked_to(n)) {
		result.insert(neighbour);
	}

	return result;
}

Graph::const_iterator Graph::begin(void) const {
	return cbegin();
}

Graph::const_iterator Graph::end(void) const {
	return cend();
}

Graph::const_iterator Graph::cbegin(void) const {
	return GraphNodeIterator(0, 0, V_order);
}

Graph::const_iterator Graph::cend(void) const {
	return GraphNodeIterator(V_order, 0, V_order);
}
