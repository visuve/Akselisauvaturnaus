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

	Player::Player(Ast::IStrategy* strategy, size_t rounds, size_t competitions) :
		_strategy(strategy),
		_rounds(rounds),
		_history(new char*[competitions]),
		_score(new size_t[competitions]),
		_competitionCount(competitions),
		_competitionIndex(0)
	{
		
		for (size_t y = 0; y < _competitionCount; ++y)
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
		if (_strategy)
		{
			delete _strategy;
		}

		if (_history)
		{
			for (size_t y = 0; y < _competitionCount; ++y)
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

	Player* Player::Clone(const Player* other)
	{
		return new Player(IStrategy::Clone(other->_strategy), other->_rounds, other->_competitionCount);
	}

	char Player::Play(const Player* other, size_t round, size_t left)
	{
		return _strategy->Apply(this, other, round, left);
	}

	Player::operator bool() const
	{
		return _competitionIndex < _competitionCount;
	}

	Player& Player::operator++()
	{
		++_competitionIndex;
		return *this;
	}

	const char* Player::History() const
	{
		return _history[_competitionIndex];
	}

	char Player::History(size_t i) const
	{
		assert(_history[_competitionIndex][i]);
		return _history[_competitionIndex][i];
	}

	char& Player::History(size_t i)
	{
		return _history[_competitionIndex][i];
	}

	size_t Player::Cooperations() const
	{
		return Count(_history[_competitionIndex], Cooperate);
	}

	size_t Player::Defections() const
	{
		return Count(_history[_competitionIndex], Defect);
	}

	size_t Player::Score() const
	{
		return _score[_competitionIndex];
	}

	size_t& Player::Score()
	{
		return _score[_competitionIndex];
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << *player._strategy << ": " <<
			player.History() << "\t-> Score:" << player.Score();
	}
}