#include "Akselisauvaturnaus.hpp"

#include <iomanip>
#include <utility>

namespace Ast
{
	char Strategies::Self::Apply(const char* self, const char* opponent, size_t round) const
	{
		std::cout << "Opponent: " << (opponent[0] ? opponent : "-") << '\n';
		std::cout << "You: " << self;

		std::string line;
		char c = '\0';

		while (std::getline(std::cin, line))
		{
			c = line.front();

			if (c == Cooperate || c == Defect)
			{
				break;
			}

			c -= 0x20;

			if (c == Cooperate || c == Defect)
			{
				break;
			}
		}

		std::cout << '\n';
		return c;
	}

	Game::operator bool() const
	{
		return _round < Rounds;
	}

	Game& Game::operator++()
	{
		char& arthursChoice = Arthur.History[_round];
		char& berthasChoice = Bertha.History[_round];

		arthursChoice = Arthur.Strategy.Apply(Arthur.History, Bertha.History, _round);
		berthasChoice = Bertha.Strategy.Apply(Bertha.History, Arthur.History, _round);

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

	std::ostream& operator << (std::ostream& os, const Strategy& strategy)
	{
		return os << std::setw(10) << strategy.Name();
	}

	std::ostream& operator << (std::ostream& os, const Player& player)
	{
		return os << player.Strategy << ": " <<
			player.History << "\t-> Score:" << player.Score;;
	}

	std::ostream& operator << (std::ostream& os, const Game& game)
	{
		return os << game.Arthur << '\n' << game.Bertha;
	}
}

int main()
{
	srand(0xBEB0B);

	auto arthursStrategy = Ast::Strategies::Tit4Tat();
	auto berthasStrategy = Ast::Strategies::Self();

	auto game = Ast::Game(5, arthursStrategy, berthasStrategy);

	while (game)
	{
		++game;
	}

	std::cout << game << std::endl;

	return 0;
}
