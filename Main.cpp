#include "Game.hpp"

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
