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

	Player::Player(Ast::IStrategy& strategy, size_t rounds, size_t competitions) :
		_strategy(strategy),
		_competitions(competitions),
		_history(new char*[competitions]),
		_score(new size_t[competitions])
	{
		
		for (size_t y = 0; y < _competitions; ++y)
		{
			_history[y] = new char[rounds + 1];

			for (size_t x = 0; x < rounds + 1; ++x)
			{
				_history[y][x] = '\0';
			}

			_score[y] = 0;
		}
	}

	Player::~Player()
	{
		if (_history)
		{
			for (size_t y = 0; y < _competitions; ++y)
			{
				delete[] _history[y];
			}

			delete[] _history;
		}

		if (_score)
		{
			delete[] _score;
		}
	}

	char Player::Play(const Player& other, size_t round, size_t left)
	{
		return _strategy.Apply(*this, other, round, left);
	}

	const char* Player::History() const
	{
		return _history[_competition];
	}

	char Player::History(size_t i) const
	{
		assert(_history[_competition][i]);
		return _history[_competition][i];
	}

	char& Player::History(size_t i)
	{
		return _history[_competition][i];
	}

	size_t Player::Cooperations() const
	{
		return Count(_history[_competition], Cooperate);
	}

	size_t Player::Defections() const
	{
		return Count(_history[_competition], Defect);
	}

	size_t Player::Score() const
	{
		return _score[_competition];
	}

	size_t& Player::Score()
	{
		return _score[_competition];
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << player._strategy << ": " <<
			player.History() << "\t-> Score:" << player.Score();
	}
}