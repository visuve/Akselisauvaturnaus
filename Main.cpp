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

		constexpr size_t PlayerCount = 16;
		constexpr size_t RoundsPerCompetition = 200;
		constexpr size_t CompetitionCount = PlayerCount * PlayerCount;

		Ast::Player a(new Ast::Strategies::Tit4Tat(), RoundsPerCompetition, CompetitionCount);
		Ast::Player b(new Ast::Strategies::Tideman(), RoundsPerCompetition, CompetitionCount);
		Ast::Player c(new Ast::Strategies::Nydegger(), RoundsPerCompetition, CompetitionCount);
		Ast::Player d(new Ast::Strategies::Grofman(), RoundsPerCompetition, CompetitionCount);
		Ast::Player e(new Ast::Strategies::Shubik(), RoundsPerCompetition, CompetitionCount);
		Ast::Player f(new Ast::Strategies::SteinRapoport(), RoundsPerCompetition, CompetitionCount);
		Ast::Player g(new Ast::Strategies::Friedman(), RoundsPerCompetition, CompetitionCount);
		Ast::Player h(new Ast::Strategies::Davis(), RoundsPerCompetition, CompetitionCount);
		Ast::Player i(new Ast::Strategies::Graaskamp(), RoundsPerCompetition, CompetitionCount);
		Ast::Player j(new Ast::Strategies::Downing(), RoundsPerCompetition, CompetitionCount);
		Ast::Player k(new Ast::Strategies::Downing2nd(), RoundsPerCompetition, CompetitionCount);
		Ast::Player l(new Ast::Strategies::Feld(), RoundsPerCompetition, CompetitionCount);
		Ast::Player m(new Ast::Strategies::Joss(), RoundsPerCompetition, CompetitionCount);
		Ast::Player n(new Ast::Strategies::Tullock(), RoundsPerCompetition, CompetitionCount);
		Ast::Player o(new Ast::Strategies::Unnamed(), RoundsPerCompetition, CompetitionCount);
		Ast::Player p(new Ast::Strategies::Random(), RoundsPerCompetition, CompetitionCount);

		Ast::Player* players[PlayerCount] = { &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p };

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
