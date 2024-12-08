#include "Competition.hpp"

constexpr size_t Rounds = 200;

int main()
{
	auto arthursStrategy = Ast::Strategies::Graaskamp();
	auto berthasStrategy = Ast::Strategies::Random();

	Ast::Player arthur(arthursStrategy, Rounds);
	Ast::Player bertha(berthasStrategy, Rounds);

	auto competition = Ast::Competition(arthur, bertha, Rounds);

	while (competition)
	{
		++competition;
	}

	std::cout << competition << std::endl;

	return 0;
}
