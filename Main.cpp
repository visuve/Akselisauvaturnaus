#include "Competition.hpp"

int main()
{
	auto arthursStrategy = Ast::Strategies::Graaskamp();
	auto berthasStrategy = Ast::Strategies::Self();

	auto competition = Ast::Competition(200, arthursStrategy, berthasStrategy);

	while (competition)
	{
		++competition;
	}

	std::cout << competition << std::endl;

	return 0;
}
