#pragma once

#include <iostream>
#include <string>

namespace Ast
{
	constexpr char Cooperate = 'C';
	constexpr char Defect = 'D';

	struct Strategy;

	struct Player
	{
		inline Player(const Strategy& strategy, size_t rounds) :
			Strategy(strategy),
			History(new char[rounds + 1])
		{
			memset(History, 0, rounds + 1);
		}

		virtual ~Player()
		{
			if (History)
			{
				delete[] History;
			}
		}

		char* History = nullptr;
		size_t Score = 0;
		const Strategy& Strategy;
	};

	struct Strategy
	{
		virtual char Apply(const Player& self, const Player& opponent, size_t round) const = 0;
		virtual const char* Name() const = 0;
	};

	namespace Strategies
	{
		struct Self : Strategy
		{
			inline char Apply(const Player& h, const Player&, size_t i) const override;

			inline const char* Name() const override
			{
				return "You";
			}
		};

		struct Nice : Strategy
		{
			inline char Apply(const Player&, const Player&, size_t) const override
			{
				return Cooperate;
			}

			inline const char* Name() const override
			{
				return "Nice";
			}
		};

		struct Evil : Strategy
		{
			inline char Apply(const Player&, const Player&, size_t) const override
			{
				return Defect;
			}

			inline const char* Name() const override
			{
				return "Evil";
			}
		};

		struct Random : Strategy
		{
			inline char Apply(const Player&, const Player&, size_t) const override
			{
				return rand() % 2 == 0 ? Cooperate : Defect;
			}

			inline const char* Name() const override
			{
				return "Random";
			}
		};

		struct Tit4Tat : Strategy
		{
			inline char Apply(const Player&, const Player& other, size_t i) const override
			{
				if (i == 0)
				{
					return Cooperate;
				}

				return other.History[i - 1] == Cooperate ? Cooperate : Defect;
			}

			inline const char* Name() const override
			{
				return "Tit4Tat";
			}
		};
	}

	class Game
	{
	public:
		Game(size_t rounds, const Strategy& arthursStrategy, const Strategy& berthasStrategy) :
			Rounds(rounds),
			Arthur(arthursStrategy, rounds),
			Bertha(berthasStrategy, rounds)
		{
		}

		operator bool() const;
		Game& operator++ ();

		const size_t Rounds = 0;
		Player Arthur;
		Player Bertha;

		friend std::ostream& operator << (std::ostream&, const Game&);

	private:
		size_t _round = 0;
	};

	std::ostream& operator << (std::ostream&, const Player&);
	std::ostream& operator << (std::ostream&, const Strategy&);
	std::ostream& operator << (std::ostream&, const Game&);
}