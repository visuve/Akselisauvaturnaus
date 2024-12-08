#pragma once

#include "Player.hpp"

namespace Ast
{
	class Competition
	{
	public:
		Competition(Player&, Player&, size_t rounds);

		operator bool() const;
		Competition& operator++ ();

		const size_t Rounds = 0;
		Player& Arthur;
		Player& Bertha;

		friend std::ostream& operator << (std::ostream&, const Competition&);

	private:
		size_t _round = 0;
	};
}