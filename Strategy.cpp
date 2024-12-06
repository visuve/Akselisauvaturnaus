#include "Strategy.hpp"
#include "Player.hpp"

namespace Ast
{
	namespace Strategies
	{
		char Self::Apply(const Player& self, const Player& opponent, size_t, size_t)
		{
			std::cout << "Opponent: " << (opponent.History[0] ? opponent.History : "-") << '\n';
			std::cout << "You: " << self.History;

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

		const char* Self::Name() const
		{
			return "You";
		}

		char Nice::Apply(const Player&, const Player&, size_t, size_t)
		{
			return Cooperate;
		}

		const char* Nice::Name() const
		{
			return "Nice";
		}


		char Evil::Apply(const Player&, const Player&, size_t, size_t)
		{
			return Defect;
		}

		const char* Evil::Name() const
		{
			return "Evil";
		}

		char Random::Apply(const Player&, const Player&, size_t, size_t)
		{
			return rand() % 2 ? Cooperate : Defect;
		}

		const char* Random::Name() const
		{
			return "Random";
		}

		char Tit4Tat::Apply(const Player&, const Player& other, size_t round, size_t)
		{
			if (round == 0)
			{
				return Cooperate;
			}

			return other.History[round - 1] == Cooperate ? Cooperate : Defect;
		}

		const char* Tit4Tat::Name() const
		{
			return "Tit4Tat";
		}

		char Alternator::Apply(const Player&, const Player&, size_t round, size_t)
		{
			return round % 2 ? Defect : Cooperate;
		}

		const char* Alternator::Name() const
		{
			return "Alternator";
		}

		char Grumpy::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{
			size_t grumpiness = 
				std::count(opponent.History, opponent.History + round, Defect) -
				std::count(opponent.History, opponent.History + round, Cooperate);
			
			return grumpiness < 10 ? Cooperate : Defect;
		}

		const char* Grumpy::Name() const
		{
			return "Grumpy";
		}

		char Shubik::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{
			if (round == 0)
			{
				return Cooperate;
			}

			if (opponent.History[round - 1] == Defect)
			{
				RetaliationCur = ++RetaliationMax;
			}
			else if (RetaliationCur)
			{
				--RetaliationCur;
			}

			return RetaliationCur ? Defect : Cooperate;
		}

		const char* Shubik::Name() const
		{
			return "Shubik";
		}

		char Tideman::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			auto deviation = [](char* samples, size_t size)->float
			{
				float mean = std::accumulate(samples, samples + size, 0.0f,
					[](float accumulator, char c)
				{
					return accumulator + (c == Cooperate);
				}) / size;


				float variance = std::accumulate(samples, samples + size, 0.0f,
					[mean](float accumulator, char c)
				{
					return accumulator + std::powf((c == Cooperate) - mean, 2.0f);
				});

				return std::sqrtf(variance);
			};

			if (self.Score > opponent.Score &&
				(self.Score - opponent.Score) >= 10 &&
				opponent.History[round] != Defect &&
				SinceLastReset >= 20 &&
				left >= 10 &&
				deviation(opponent.History, round) >= 3.0f)
			{
				SinceLastReset = 0;
				RetaliationCur = 0;
				Reset = true;
				return Cooperate;

			}
			
			++SinceLastReset;

			if (Reset)
			{
				Reset = false;
				return Cooperate;
			}

			return Shubik::Apply(self, opponent, round, left);
		}

		const char* Tideman::Name() const
		{
			return "Tideman";
		}
		
		char Friedman::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{		
			if (opponent.History[round] == Defect)
			{
				Mad = true;
			}

			return Mad ? Defect : Cooperate;
		}

		const char* Friedman::Name() const
		{
			return "Friedman";
		}

		char Davis::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 10)
			{
				return Cooperate;
			}

			return Friedman::Apply(self, opponent, round, left);
		}

		const char* Davis::Name() const
		{
			return "Davis";
		}
	}

	std::ostream& operator << (std::ostream& os, const Strategy& strategy)
	{
		return os << std::setw(10) << strategy.Name();
	}
}