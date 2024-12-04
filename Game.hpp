#pragma once

#include "Player.hpp"

namespace Ast
{
	class Game
	{
	public:
		Game(size_t rounds, const Strategy&, const Strategy&);

		operator bool() const;
		Game& operator++ ();

		const size_t Rounds = 0;
		Player Arthur;
		Player Bertha;

		friend std::ostream& operator << (std::ostream&, const Game&);

	private:
		size_t _round = 0;
	};
}