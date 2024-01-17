#include "ColoringDP.h"
#include <iterator>
#include <algorithm>
#include <functional>

size_t ChromaticBFS(const Graph& g)
{
    if (g.empty())
        return 0;

    std::list<Set> nextQ;

    for (auto& s : BronKerbosch(g))
    {
        if (s.size() == g.size())
            return 1;

        nextQ.emplace_back(s);
    }

    for (size_t r = 2; ; ++r)
    {
        auto q = std::exchange(nextQ, {}); 
        
        for (auto it = q.begin(); it != q.end(); it = q.erase(it))
            for (Set s : BronKerbosch(g - *it))
            {
                if (std::ranges::copy(*it, std::inserter(s, s.end())); s.size() == g.size())
                    return r;

                if (std::ranges::none_of(nextQ, [&](auto& sq) { return std::ranges::includes(sq, s); }))
                {
                    std::erase_if(nextQ, [&](auto& sq) { return std::ranges::includes(s, sq); });
                    nextQ.emplace_back(std::move(s));
                }
            }
    }
}

size_t ChromaticDFS(const Graph& g)
{
    std::map<Set, size_t> m({{}});

    std::function<size_t(const Graph&)> lambda =
        [&,
            bound = SIZE_MAX,
            h = size_t{}
        ](auto& g) mutable
        {
            auto set = VertexSet(g);
        
            if (auto it = m.find(set); it != m.end())
            {
                if (set.empty())
                    bound = std::min(h - 1, bound);

                return it->second;
            }
        
            auto min = SIZE_MAX;
        
            if (h == bound)
                return min;

            for (auto& s : BronKerbosch(g))
            {
                ++h;

                if (auto temp = lambda(g - s); --h, temp != SIZE_MAX)
                    min = std::min(min, temp + 1);
                else
                    break;                
            }

            return m[std::move(set)] = min;
        };

    return lambda(g);
}