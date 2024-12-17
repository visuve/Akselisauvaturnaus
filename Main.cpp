#include "Tournament.hpp"

constexpr size_t Rounds = 200;

int main()
{
	{
		constexpr size_t PlayerCount = 3;
		constexpr size_t CompetitionCount = PlayerCount * PlayerCount;
		constexpr size_t RoundsPerCompetition = 5;

		Ast::Player a(new Ast::Strategies::Tit4Tat(), RoundsPerCompetition, CompetitionCount);
		Ast::Player b(new Ast::Strategies::Friedman(), RoundsPerCompetition, CompetitionCount);
		Ast::Player c(new Ast::Strategies::Random(), RoundsPerCompetition, CompetitionCount);

		Ast::Player* players[PlayerCount] = { &a, &b, &c };

		Ast::Tournament tournament(players, PlayerCount, RoundsPerCompetition);

		while (tournament)
		{
			++tournament;
		}

		tournament.PrintMatrix(std::cout);

		std::cout << '\n' << std::endl;

		tournament.PrintTable(std::cout);
	}

	return 0;
}
