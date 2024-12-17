#include "Player.hpp"

namespace Ast
{
	constexpr size_t Count(const char where[], char what)
	{
		assert(where);

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

	constexpr size_t Find(const char where[], char what)
	{
		assert(where);

		const char* start = where;

		while (where && *where)
		{
			if (*where == what)
			{
				return where - start;
			}

			++where;
		}

		return std::numeric_limits<size_t>::max();
	}

	constexpr bool Contains(const char where[], char what)
	{
		return Find(where, what) != std::numeric_limits<size_t>::max();
	}

	Player::Data::Data(size_t size) :
		Score(0),
		Choices(new char[++size])
	{
		while (size--)
		{
			Choices[size] = '\0';
		}
	}

	Player::Data::~Data()
	{
		if (Choices)
		{
			delete[] Choices;
		}
	}

	Player::Data* Player::Data::Clone(size_t size) const
	{
		auto clone = new Data();
		clone->Choices = new char[++size];

		while (size--)
		{
			clone->Choices[size] = Choices[size];
		}

		clone->Score = Score;

		return clone;
	}

	Player::Player(IStrategy* strategy, size_t rounds, size_t competitions, size_t competitionIndex) :
		_strategy(strategy),
		_rounds(rounds),
		_data(new Data*[competitions]),
		_competitionCount(competitions),
		_competitionIndex(competitionIndex)
	{
		for (size_t y = 0; y < _competitionCount; ++y)
		{
			_data[y] = new Data(rounds);
		}
	}

	Player::~Player()
	{
		if (_strategy)
		{
			delete _strategy;
		}

		if (_data)
		{
			for (size_t y = 0; y < _competitionCount; ++y)
			{
				delete _data[y];
			}

			delete[] _data;
		}
	}

	Player* Player::Clone(bool shallow) const
	{
		auto clone = new Player(_strategy->Clone(), _rounds, _competitionCount, _competitionIndex);

		if (!shallow)
		{
			for (size_t y = 0; y < _competitionCount; ++y)
			{
				clone->_data[y] = _data[y]->Clone(_rounds);
			}
		}

		return clone;
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
		return _data[_competitionIndex]->Choices;
	}

	char Player::History(size_t i) const
	{
		return _data[_competitionIndex]->Choices[i];
	}

	char& Player::History(size_t i)
	{
		return _data[_competitionIndex]->Choices[i];
	}

	size_t Player::Score() const
	{
		return _data[_competitionIndex]->Score;
	}

	size_t& Player::Score()
	{
		return _data[_competitionIndex]->Score;
	}

	size_t Player::Cooperations() const
	{
		return Count(_data[_competitionIndex]->Choices, Cooperate);
	}

	size_t Player::Defections() const
	{
		return Count(_data[_competitionIndex]->Choices, Defect);
	}

	const char* Player::Name() const
	{
		return _strategy->Name();
	}

	Player::Data* Player::Result(size_t competition) const
	{
		return _data[competition];
	}
}