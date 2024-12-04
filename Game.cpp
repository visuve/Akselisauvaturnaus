#include "Game.hpp"

namespace Ast
{
	Game::Game(size_t rounds, const Strategy& arthursStrategy, const Strategy& berthasStrategy) :
		Rounds(rounds),
		Arthur(arthursStrategy, rounds),
		Bertha(berthasStrategy, rounds)
	{
	}

	Game::operator bool() const
	{
		return _round < Rounds;
	}

	Game& Game::operator++()
	{
		char& arthursChoice = Arthur.History[_round];
		char& berthasChoice = Bertha.History[_round];

		arthursChoice = Arthur.Strategy.Apply(Arthur, Bertha, _round);
		berthasChoice = Bertha.Strategy.Apply(Bertha, Arthur, _round);

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

	std::ostream& operator << (std::ostream& os, const Game& game)
	{
		return os << game.Arthur << '\n' << game.Bertha;
	}
}