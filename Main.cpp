#include "Tournament.hpp"

class Timer
{
public:
	Timer() :
		_start(std::chrono::high_resolution_clock::now())
	{
	}

	friend std::ostream& operator << (std::ostream& os, const Timer& timer)
	{
		const auto end = std::chrono::high_resolution_clock::now();
		const auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - timer._start);
		return os << "Took: " << diff;
	}

private:
	const std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

int main()
{
	{
		Timer timer;

		constexpr size_t PlayerCount = 3;
		constexpr size_t CompetitionCount = PlayerCount * PlayerCount;
		constexpr size_t RoundsPerCompetition = 200;

		Ast::Player a(new Ast::Strategies::Tit4Tat(), RoundsPerCompetition, CompetitionCount);
		Ast::Player b(new Ast::Strategies::Friedman(), RoundsPerCompetition, CompetitionCount);
		Ast::Player c(new Ast::Strategies::Random(), RoundsPerCompetition, CompetitionCount);

		Ast::Player* players[PlayerCount] = { &a, &b, &c };

		Ast::Tournament tournament(players, PlayerCount, RoundsPerCompetition);

		while (tournament)
		{
			++tournament;
		}

		std::cout << timer << std::endl;

		tournament.PrintMatrix(std::cout);

		std::cout << '\n' << std::endl;

		tournament.PrintTable(std::cout);
	}

	return 0;
}
