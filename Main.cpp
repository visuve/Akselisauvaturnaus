#include "Game.hpp"

int main()
{
	auto arthursStrategy = Ast::Strategies::Graaskamp();
	auto berthasStrategy = Ast::Strategies::Self();

	auto game = Ast::Game(100, arthursStrategy, berthasStrategy);

	while (game)
	{
		++game;
	}

	std::cout << game << std::endl;

	return 0;
}
