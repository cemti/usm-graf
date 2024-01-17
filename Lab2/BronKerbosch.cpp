#include "BronKerbosch.h"
#include <algorithm>

auto BronKerbosch::Iterator::operator++() -> Iterator&
{
	if (end)
		return *this;

	auto& g = bk->g;

	if (q.size() != 0)
		goto nextS;

#define QM q.back().first
#define QP q.back().second

	q.resize(1);

	for (auto v : VertexSet(g))
		QP.insert(v);

	for (; ; )
	{
		{
			auto vi = *QP.begin();
			s.insert(vi);

			q.emplace_back(q.back());
			QP.erase(QP.begin());

			for (auto& v : g.at(vi))
			{
				QM.erase(v);
				QP.erase(v);
			}
		}

		for (; ; )
		{
			if (QM.empty())
			{
				if (QP.empty())
					return *this;

				break;
			}
			else if (std::ranges::all_of(QM, [&](auto& v)
				{
					auto& gamma = g.at(v);
					return std::ranges::find_first_of(gamma, QP) != gamma.end();
				}))
				break;

		nextS:
			if (q.pop_back(); q.empty() || (q.size() == 1 && QP.size() == 1))
			{
				q.clear();
				s.clear();
				end = true;
				return *this;
			}

			auto vi = *QP.begin();
			QP.erase(QP.begin());
			QM.insert(vi);
			s.erase(vi);
		}
	}
#undef QP
#undef QM
}