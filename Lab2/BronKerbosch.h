#pragma once
#include <set>
#include <map>
#include <list>

using Vertex = size_t;
using Set = std::set<Vertex>;
using Graph = std::map<Vertex, Set>;

inline auto operator-(Graph g, const Set& s)
{
	for (auto& v : s)
		g.erase(v);

	for (auto& [_, gamma] : g)
		for (auto& v : s)
			gamma.erase(v);

	return g;
}

inline auto VertexSet(Graph g)
{
	Set s;

	for (auto& [v, _] : g)
		s.emplace(v);

	return s;
}

class BronKerbosch
{
	class Iterator
	{
		friend class BronKerbosch;
		const BronKerbosch* bk;
		std::list<std::pair<Set, Set>> q;
		Set s;
		bool end;

		Iterator(const BronKerbosch* bk, bool end) : bk(bk), end(end) {}
		Iterator(const BronKerbosch* bk) : Iterator(bk, bk->g.empty()) {}
	public:
		auto& operator*() const { return s; }
		Iterator& operator++();
		friend bool operator==(const Iterator& lhs, const Iterator& rhs) = default;
	};
	
	Graph g;

public:
	BronKerbosch(const Graph& g) : g(g) {}
	BronKerbosch(Graph&& g) : g(std::move(g)) {}

	auto begin() const { return ++Iterator(this); }
	auto end() const { return Iterator(this, true); }
};