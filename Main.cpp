#include "Game.hpp"

int main()
{
	srand(0xBEB0B);

	auto arthursStrategy = Ast::Strategies::Tideman();
	auto berthasStrategy = Ast::Strategies::Self();

	auto game = Ast::Game(100, arthursStrategy, berthasStrategy);

	while (game)
	{
		++game;
	}

	std::cout << game << std::endl;

	return 0;
}
