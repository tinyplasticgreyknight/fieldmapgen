#ifndef H_GRAPH
#define H_GRAPH

#include "graph_node_iterator.hpp"
#include <set>
#include <map>

namespace fieldmapgen {
	/// @class Graph
	/// @brief A graph with a fixed number of nodes.
	///
	/// The order (number of nodes) in the graph is fixed at construction time.
	/// Edges can be added or removed freely, in either directed or undirected manner.
	class Graph {
	public:
		/// Currently just fixed as `size_t`, this is the type of a node identifier.
		typedef size_t node;
		/// A collection of nodes.
		typedef std::set<node> node_set;
		/// The nodes can only be iterated over in `const` mode.
		typedef GraphNodeIterator const_iterator;
	private:
		typedef std::map<node, node_set> connections;

	public:
		/// @brief Constructs a new graph with a specified number of nodes.
		/// @param order The number of nodes.
		Graph(size_t order);
		/// Destructor.
		~Graph(void);

		/// Retrieves the number of nodes in the graph.
		size_t order(void) const;
		/// Adds an undirected edge between nodes `a` and `b` (actually made of two directed edges).
		/// Has no effect if already linked.
		void link(node a, node b);
		/// Adds a directed edge from node `a` to node `b`.  Has no effect if already linked.
		void link_oneway(node a, node b);
		/// Removes all edges between nodes `a` and `b`.
		void unlink(node a, node b);
		/// Removes the directed edge from node `a` to node `b`.
		/// If an undirected edge was present between these two nodes, it is now reduced to a directed edge from `b` to `a`.
		void unlink_oneway(node a, node b);
		/// Returns the set of nodes reachable by following a single edge from node `n`.
		const node_set get_linked_from(node n) const;
		/// Returns the set of nodes from which node `n` can be reached by following a single edge.
		const node_set get_linked_to(node n) const;
		/// Returns the set of nodes connected to node `n` by a single edge, without regard for edge direction.
		const node_set get_linked(node n) const;

		/// @see cbegin
		const_iterator begin(void) const;
		/// @see cend
		const_iterator end(void) const;
		/// Iterator to node 0.
		const_iterator cbegin(void) const;
		/// Iterator past the end of the collection of nodes.
		const_iterator cend(void) const;

	private:
		const node_set get_linked_general(const connections& conn_map, node n) const;

		size_t V_order;
		connections E_in;
		connections E_out;
	};
}

#endif
