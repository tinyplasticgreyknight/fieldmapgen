#pragma once
#ifndef H_GRAPH
#define H_GRAPH

#include "graph_node_iterator.hpp"
#include <set>
#include <map>

namespace fieldmapgen {
	class Graph {
	public:
		typedef size_t node;
		typedef std::set<node> node_set;
		typedef std::map<node, node_set> connections;
		typedef GraphNodeIterator const_iterator;

	public:
		Graph(size_t order);
		~Graph(void);

		size_t order(void) const;
		void link(node a, node b);
		void link_oneway(node a, node b);
		void unlink(node a, node b);
		void unlink_oneway(node a, node b);
		const node_set get_linked_from(node n) const;
		const node_set get_linked_to(node n) const;
		const node_set get_linked(node n) const;

		const_iterator begin(void) const;
		const_iterator end(void) const;
		const_iterator cbegin(void) const;
		const_iterator cend(void) const;

	private:
		size_t V_order;
		connections E_in;
		connections E_out;
	};
}

#endif
