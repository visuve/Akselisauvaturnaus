#include "Competition.hpp"

namespace Ast
{
	Competition::Competition(Player& arthur, Player& bertha, size_t rounds) :
		Rounds(rounds),
		Arthur(arthur),
		Bertha(bertha)
	{
	}

	Competition::operator bool() const
	{
		return _round < Rounds;
	}

	Competition& Competition::operator++()
	{
		char& arthursChoice = Arthur.History[_round];
		char& berthasChoice = Bertha.History[_round];

		arthursChoice = Arthur.Strategy.Apply(Arthur, Bertha, _round, Rounds - _round);
		berthasChoice = Bertha.Strategy.Apply(Bertha, Arthur, _round, Rounds - _round);

		if (arthursChoice == Cooperate && berthasChoice == Cooperate)
		{
			Arthur.Score += 3;
			Bertha.Score += 3;
		}
		else if (arthursChoice == Cooperate && berthasChoice == Defect)
		{
			Bertha.Score += 5;
		}
		else if (arthursChoice == Defect && berthasChoice == Cooperate)
		{
			Arthur.Score += 5;
		}
		else if (arthursChoice == Defect && berthasChoice == Defect)
		{
			Arthur.Score += 1;
			Bertha.Score += 1;
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
		return os << game.Arthur << '\n' << game.Bertha;
	}
}