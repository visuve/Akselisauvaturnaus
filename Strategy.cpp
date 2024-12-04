#include "Strategy.hpp"
#include "Player.hpp"

namespace Ast
{
	namespace Strategies
	{
		char Self::Apply(const Player& self, const Player& opponent, size_t round) const
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

		char Nice::Apply(const Player&, const Player&, size_t) const
		{
			return Cooperate;
		}

		const char* Nice::Name() const
		{
			return "Nice";
		}


		char Evil::Apply(const Player&, const Player&, size_t) const
		{
			return Defect;
		}

		const char* Evil::Name() const
		{
			return "Evil";
		}

		char Random::Apply(const Player&, const Player&, size_t) const
		{
			return rand() % 2 == 0 ? Cooperate : Defect;
		}

		const char* Random::Name() const
		{
			return "Random";
		}

		char Tit4Tat::Apply(const Player&, const Player& other, size_t i) const
		{
			if (i == 0)
			{
				return Cooperate;
			}

			return other.History[i - 1] == Cooperate ? Cooperate : Defect;
		}

		const char* Tit4Tat::Name() const
		{
			return "Tit4Tat";
		}
	}

	std::ostream& operator << (std::ostream& os, const Strategy& strategy)
	{
		return os << std::setw(10) << strategy.Name();
	}
}