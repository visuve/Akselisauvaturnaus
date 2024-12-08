#include "Strategy.hpp"
#include "Player.hpp"

namespace Ast
{
	float Mean(const char samples[], size_t size)
	{
		return std::accumulate(samples, samples + size, 0.0f,
			[](float accumulator, char c)
		{
			return accumulator + (c == Cooperate);
		}) / size;
	}

	float Variance(const char samples[], size_t size, float mean)
	{
		return std::accumulate(samples, samples + size, 0.0f,
			[mean, size](float accumulator, char c)
		{
			return accumulator + std::powf((c == Cooperate) - mean, 2.0f) / float(size - 1);
		});
	}

	float Deviation(const char samples[], size_t size)
	{
		const float mean = Mean(samples, size);
		const float variance = Variance(samples, size, mean);
		return std::sqrtf(variance);
	};

	float SquareSum(const char samples[], size_t size, float mean)
	{
		return std::accumulate(samples, samples + size, 0.0f,
			[mean](float accumulator, char c)
		{
			return accumulator + std::powf((c == Cooperate) - mean, 2.0f);
		});
	}

	float ChiSquare(const char samples[], size_t size)
	{
		const float mean = Mean(samples, size);
		const float squareSum = SquareSum(samples, size, mean);
		return squareSum / mean;
	};

	const std::seed_seq Seed({ 'A', 'x', 'e', 'l', 'r', 'o', 'd' });

	template <typename T>
	T RandomInteger(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
	{
		static thread_local std::default_random_engine engine(Seed);
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(engine);
	}

	template <typename T>
	T RandomFloat(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
	{
		static thread_local std::default_random_engine engine(Seed);
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(engine);
	}

	template <typename T>
	T RandomChoice(T heads, T tails, double probability = 0.5)
	{
		static thread_local std::default_random_engine engine(Seed);
		std::bernoulli_distribution distribution(probability);
		return distribution(engine) ? heads : tails;
	}

	namespace Strategies
	{
		char Self::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			std::cout << "Round: " << round << ". Left: " << left << '\n';
			std::cout << "Opponent: " << (opponent.History[0] ? opponent.History : "-") << '\n';
			std::cout << "You: " << self.History;

			std::string line;
			char c = '\0';

			while (std::getline(std::cin, line))
			{
				if (line.empty())
				{
					continue;
				}

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

		char Random::Apply(const Player&, const Player&, size_t, size_t)
		{
			return RandomChoice(Defect, Cooperate);
		}

		const char* Random::Name() const
		{
			return "Random";
		}

		char Tit4Tat::Apply(const Player&, const Player& opponent, size_t round, size_t)
		{
			if (round == 0)
			{
				return Cooperate;
			}

			return opponent.History[round - 1] == Cooperate ? Cooperate : Defect;
		}

		const char* Tit4Tat::Name() const
		{
			return "Tit4Tat";
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
			if (self.Score > opponent.Score &&
				(self.Score - opponent.Score) >= 10 &&
				opponent.History[round] != Defect &&
				SinceLastReset >= 20 &&
				left >= 10 &&
				Deviation(opponent.History, round) >= 3.0f)
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

		char Grofman::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 2)
			{
				return Cooperate;
			}

			if (round < 6)
			{
				return Tit4Tat::Apply(self, opponent, round, left);
			}

			if (self.History[round - 1] == opponent.History[round - 1])
			{
				return Cooperate;
			}

			return RandomInteger(0, 7) < 2 ? Cooperate : Defect;
		}

		const char* Grofman::Name() const
		{
			return "Grofman";
		}

		char Nydegger::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 3)
			{
				return Tit4Tat::Apply(self, opponent, round, left);
			}

			constexpr size_t nydegger[] = { 1, 6, 7, 17, 22, 23, 26, 29, 30, 31, 33, 38, 39, 45, 49, 54, 55, 58, 61 };

			constexpr size_t score[2][2] = 
			{ 
				{ 3, 1 },
				{ 2, 0 }
			};

			size_t a =
				16 * score[self.History[round - 0] == Cooperate][opponent.History[round - 0] == Cooperate] +
				04 * score[self.History[round - 1] == Cooperate][opponent.History[round - 1] == Cooperate] +
				01 * score[self.History[round - 2] == Cooperate][opponent.History[round - 2] == Cooperate];

			return std::find(std::begin(nydegger), std::end(nydegger), a) == std::end(nydegger) ? Cooperate : Defect;
		}

		const char* Nydegger::Name() const
		{
			return "Nydegger";
		}

		char SteinRapoport::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 4)
			{
				return Cooperate;
			}

			if (left < 2)
			{
				return Defect;
			}

			if (round % 15 == 0)
			{
				OpponentAppearsRandom = ChiSquare(opponent.History, round) >= 0.05f;
			}

			return OpponentAppearsRandom ? Defect : Cooperate;
		}

		const char* SteinRapoport::Name() const
		{
			return "SteinRapoport";
		}

		char Graaskamp::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 50)
			{
				return Tit4Tat::Apply(self, opponent, round, left);
			}
			
			if (round == 50)
			{
				return Defect;
			}
			
			if (round < 56)
			{
				return Tit4Tat::Apply(self, opponent, round, left);
			}

			if (round == 56 && ChiSquare(opponent.History, round) >= 0.05f)
			{
				NextDefectTurn = round + RandomInteger<size_t>(5u, 15u);
			}

			if (round == NextDefectTurn)
			{
				NextDefectTurn += RandomInteger<size_t>(5u, 15u);
				return Defect;
			}

			return Cooperate;
		}

		const char* Graaskamp::Name() const
		{
			return "Graaskamp";
		}

		char Downing::Apply(const Player&, const Player&, size_t, size_t)
		{
			// TODO
			return 0;
		}

		const char* Downing::Name() const
		{
			return "Downing";
		}

		char Downing2nd::Apply(const Player& self, const Player& opponent, size_t round, size_t left)
		{
			if (round < 2)
			{
				return Cooperate;
			}

			return Downing::Apply(self, opponent, round, left);
		}

		const char* Downing2nd::Name() const
		{
			return "Downing2nd";
		}

		char Feld::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{
			if (round == 0)
			{
				return Cooperate;
			}

			if (opponent.History[round - 1] == Defect)
			{
				if (CooperationProbability > 0.5)
				{
					CooperationProbability -= 0.05f;
				}

				return Defect;
			}

			return RandomChoice(Cooperate, Defect, CooperationProbability);
		}

		const char* Feld::Name() const
		{
			return "Feld";
		}

		char Joss::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{
			if (opponent.History[round - 1] == Defect)
			{
				return Defect;
			}

			return RandomChoice(Cooperate, Defect, 0.9f);
		}

		const char* Joss::Name() const
		{
			return "Joss";
		}

		char Tullock::Apply(const Player& self, const Player& opponent, size_t round, size_t)
		{
			if (round < 11)
			{
				return Cooperate;
			}

			float mean = Mean(opponent.History, round) - 0.1f;

			return RandomChoice(Cooperate, Defect, mean);
		}

		const char* Tullock::Name() const
		{
			return "Tullock";
		}

		char Unnamed::Apply(const Player&, const Player&, size_t round, size_t)
		{
			const float random = RandomFloat(0.0f, 1.0f);
			return random > 0.3f && random < 0.7f ? Cooperate : Defect;
		}

		const char* Unnamed::Name() const
		{
			return "Unnamed";
		}

		// Extras

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
	}

	std::ostream& operator << (std::ostream& os, const Strategy& strategy)
	{
		return os << std::setw(10) << strategy.Name();
	}
}