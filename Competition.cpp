#include "Competition.hpp"

namespace Ast
{
	Competition::Competition(Player& arthur, Player& bertha, size_t rounds) :
		_rounds(rounds),
		_arthur(arthur),
		_bertha(bertha)
	{
	}

	Competition::operator bool() const
	{
		return _round < _rounds;
	}

	Competition& Competition::operator++()
	{
		char& arthursChoice = _arthur.History(_round);
		char& berthasChoice = _bertha.History(_round);

		arthursChoice = _arthur.Play(_bertha, _round, _rounds - _round);
		berthasChoice = _bertha.Play(_arthur, _round, _rounds - _round);

		if (arthursChoice == Cooperate && berthasChoice == Cooperate)
		{
			_arthur.Score() += 3;
			_bertha.Score() += 3;
		}
		else if (arthursChoice == Cooperate && berthasChoice == Defect)
		{
			_bertha.Score() += 5;
		}
		else if (arthursChoice == Defect && berthasChoice == Cooperate)
		{
			_arthur.Score() += 5;
		}
		else if (arthursChoice == Defect && berthasChoice == Defect)
		{
			_arthur.Score() += 1;
			_bertha.Score() += 1;
		}
		else
		{
			std::unreachable();
		}

		++_round;
		return *this;
	}

	std::ostream& operator << (std::ostream& os, const Competition& game)
	{
		return os << game._arthur << '\n' << game._bertha;
	}
}