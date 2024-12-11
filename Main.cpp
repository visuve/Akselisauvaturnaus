#include "Competition.hpp"

constexpr size_t Rounds = 200;

int main()
{
	Ast::Player arthur(new Ast::Strategies::Graaskamp(), Rounds);
	Ast::Player bertha(new Ast::Strategies::Random(), Rounds);

	auto competition = Ast::Competition(arthur, bertha, Rounds);

	while (competition)
	{
		++competition;
	}

	std::cout << competition << std::endl;

	return 0;
}
