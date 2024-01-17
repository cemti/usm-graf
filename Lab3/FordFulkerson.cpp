#include <iostream>
#include <deque>
#include <map>

using Vertex = size_t;
using Edges = std::map<Vertex, double>;
using Graph = std::map<Vertex, Edges>;

static constexpr auto inf = std::numeric_limits<double>::infinity();

static auto InputGraph()
{
	Graph graph;
	size_t n;

	std::cout << "n = ";
	std::cin >> n;

	for (size_t i = 1; i <= n; ++i)
	{
		size_t deg;
		std::cout << "deg(v" << i << ") = ";
		std::cin >> deg;

		while (deg-- != 0)
		{
			Vertex u;
			double c;

			if (std::cin >> u >> c; c != 0)
				graph[i][u] = c;
		}
	}

	return graph;
}

static auto FordFulkerson(Graph g, Vertex source, Vertex sink)
{
	auto flow = 0.;

loop:
	std::map<Vertex, std::pair<Vertex, double>> path{ { source, { {}, inf } } };

	for (std::deque q{ source }; !q.empty(); q.pop_front())
		for (auto v = q.front(); auto [i, c] : g[v])
			if (!path.contains(i))
			{
				c = std::min(c, path[v].second);

				if (path[i] = { v, c }; i == sink)
				{
					flow += c;

					for (auto u = i; u != source; u = v)
					{
						v = path[u].first;

						if ((g[u][v] += c) == 0)
							g[u].erase(v);

						if ((g[v][u] -= c) == 0)
							g[v].erase(u);
					}

					// return maxFlow + FordFulkerson(g, source, sink);
					goto loop;
				}

				q.push_back(i);
			}

	return flow;
}

int main()
{
	auto g = InputGraph();

	Vertex a, b;

	std::cout << "Varful sursa: ";
	std::cin >> a;

	std::cout << "Varful destinatie: ";
	std::cin >> b;

	std::cout << "Fluxul maxim: " << FordFulkerson(g, a, b);
}