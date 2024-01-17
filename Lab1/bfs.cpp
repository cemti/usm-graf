#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <list>

using Vertex = size_t; // varf
using Set = std::set<Vertex>; // multimea gamma
using Graph = std::map<Vertex, Set>; // harta de adiacenta

static auto Eccentricity(const Graph& graph, Vertex start)
{    
    if (auto startIt = graph.find(start); startIt != graph.end())
    {
        std::map<Vertex, size_t> depth{ { start, 0 } };
        std::list<Graph::const_iterator> seq{ startIt };

        for (auto& it : seq)
        {
            auto& [vertex, gamma] = *it;
            for (auto& v : gamma)
                if (depth.emplace(v, depth[vertex] + 1).second)
                    seq.emplace_back(graph.find(v));
        }

        if (depth.size() != graph.size())
            throw std::invalid_argument("Graful nu este conex.");

        return depth[seq.back()->first];
    }

    throw std::invalid_argument("Varful de pornire dat nu exista in graf.");
}

static auto InputGraph()
{
    Graph graph;
    size_t m;

    std::cout << "m = ";
    std::cin >> m;

    if (m != 0)
        for (size_t i = 0; i < m; )
        {
            std::cout << "e" << i + 1 << " = ";
            Vertex a, b;

            if (std::cin >> a >> b; a != b)
            {
                graph[a].insert(b);
                graph[b].insert(a);
                ++i;
            }
            else
                std::cout << "Nu permitem bucle.\n";
        }
    else
        graph[0];
    
    return graph;
}

int main()
{
    auto graph = InputGraph();

    try
    {
        auto it = graph.begin();
        auto r = Eccentricity(graph, it->first), d = r;

        while (++it != graph.end())
            std::tie(r, d) = std::minmax({ Eccentricity(graph, it->first), r, d });

        std::cout << "r(G) = " << r << "; D(G) = " << d;
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what();
    }
}