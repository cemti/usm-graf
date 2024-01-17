#include "ColoringDP.h"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <cassert>

static auto InputGraph()
{
    Graph graph;
    size_t n;

    std::cout << "n = ";
    (std::cin >> n).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    for (size_t i = 1; i <= n; ++i)
    {
        std::cout << "v" << i << ": ";
        auto ptr = &graph[i];

        std::string temp;
        std::getline(std::cin, temp);
        std::istringstream istr(temp);

        for (Vertex v; istr >> v; ptr->insert(v))
            graph[v];
    }

    return graph;
}

static void Stopwatch()
{
    static bool status;
    auto now = std::chrono::high_resolution_clock::now();
    static decltype(now) start;    

    if (status)
        std::cout << "Timpul estimat: " << now - start << '\n';
    else
        status = true;
    
    start = now;
}

int main()
{
    auto g = InputGraph();
    size_t hi[2]{};

    Stopwatch();
    hi[0] = ChromaticDFS(g);
    Stopwatch();
 
    hi[1] = ChromaticBFS(g);
    Stopwatch();

    assert(hi[0] == hi[1]);
    std::cout << "Numarul cromatic: " << hi[0];
}