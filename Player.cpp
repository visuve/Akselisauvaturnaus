#include "Player.hpp"
#include "Strategy.hpp"

namespace Ast
{
	Player::Player(Ast::Strategy& strategy, size_t rounds) :
		Strategy(strategy),
		History(new char[rounds + 1])
	{
		memset(History, 0, rounds + 1);
	}

	Player::~Player()
	{
		if (History)
		{
			delete[] History;
		}
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << player.Strategy << ": " <<
			player.History << "\t-> Score:" << player.Score;
	}
}