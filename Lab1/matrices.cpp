#include <iostream>
#include <deque>
#include <set>

using Matrix = std::deque<std::deque<bool>>;

static auto InputAdjMtx()
{
    size_t n;

    std::cout << "n = ";
    std::cin >> n;
    
    Matrix mtx(n, Matrix::value_type(n));

    for (size_t j, i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            std::cin >> mtx[i][j];

    return mtx;
}

static auto AdjToInc(const Matrix& adj)
{
    const auto n = adj.size();
    Matrix mtx(n);

    for (size_t j, i = 0; i < n; ++i)
    {
        if (adj[i][i])
            throw std::invalid_argument("Graful trebuie sa nu fie pseudograf.");
        
        for (j = i + 1; j < n; ++j)
        {
            if (adj[i][j] != adj[j][i])
                throw std::invalid_argument("Graful trebuie sa nu fie orientat.");

            if (adj[i][j])
            {
                for (auto& r : mtx)
                    r.resize(r.size() + 1);

                mtx[i].back() = mtx[j].back() = true;
            }
        }
    }

    return mtx;
}

static auto IncToAdjEdgeMtx(const Matrix& inc)
{
    auto n = inc.size(), m = inc.at(0).size();
    Matrix mtx(m, Matrix::value_type(m));

    for (size_t j = 0; j < m; ++j)
    {
        size_t i1, i2;
        
        {
            for (i1 = 0; i1 < n && !inc[i1][j]; ++i1) {}

            if (i1 == n)
                throw std::invalid_argument("Graful are o muchie invalida.");
        }

        {
            for (i2 = i1 + 1; i2 < n && !inc[i2][j]; ++i2) {}

            if (i2 == n)
                throw std::invalid_argument("Graful are o muchie invalida.");
        }

        for (size_t k = j + 1; k < m; ++k)
            if ((inc[i1][j] && inc[i1][k]) || (inc[i2][j] && inc[i2][k]))
                mtx[j][k] = mtx[k][j] = true;
    }

    return mtx;
}

static auto& operator<<(std::ostream& out, const Matrix& mtx)
{
    for (auto& r : mtx)
    {
        for (auto& v : r)
            out << v << ' ';

        out << '\n';
    }

    return out << '\n';
}

int main()
{
    try
    {
        auto mtx = InputAdjMtx();
        std::cout << '\n';

        mtx = AdjToInc(mtx);
        std::cout << mtx;

        mtx = IncToAdjEdgeMtx(mtx);
        std::cout << mtx;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }
}