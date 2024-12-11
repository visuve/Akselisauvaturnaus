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
		_strategy(strategy),
		_history(new char[++rounds])
	{
		while (rounds--)
		{
			_history[rounds] = '\0';
		}
	}

	Player::~Player()
	{
		if (_history)
		{
			delete[] _history;
		}
	}

	size_t Player::Cooperations() const
	{
		return Count(_history, Cooperate);
	}

	size_t Player::Defections() const
	{
		return Count(_history, Defect);
	}

	char Player::Play(const Player& other, size_t round, size_t left)
	{
		return _strategy.Apply(*this, other, round, left);
	}

	const char* Player::History() const
	{
		return _history;
	}

	char Player::History(size_t i) const
	{
		assert(_history[i]);
		return _history[i];
	}

	char& Player::History(size_t i)
	{
		return _history[i];
	}

	size_t Player::Score() const
	{
		return _score;
	}

	size_t& Player::Score()
	{
		return _score;
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << player._strategy << ": " <<
			player._history << "\t-> Score:" << player._score;
	}
}