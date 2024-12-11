#include "Player.hpp"
#include "Strategy.hpp"

namespace Ast
{
	size_t Count(const char* where, char what)
	{
		size_t count = 0;

		while (where && *where)
		{
			if (*where == what)
			{
				++count;
			}

			++where;
		}

		return count;
	}

	Player::Player(Ast::IStrategy& strategy, size_t rounds) :
		Strategy(strategy),
		History(new char[++rounds])
	{
		while (rounds--)
		{
			History[rounds] = '\0';
		}
	}

	Player::~Player()
	{
		if (History)
		{
			delete[] History;
		}
	}

	size_t Player::Cooperations() const
	{
		return Count(History, Cooperate);
	}

	size_t Player::Defections() const
	{
		return Count(History, Defect);
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << player.Strategy << ": " <<
			player.History << "\t-> Score:" << player.Score;
	}
}