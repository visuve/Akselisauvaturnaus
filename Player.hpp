#pragma once

#include "Strategy.hpp"

namespace Ast
{
	struct Strategy;

	class Player
	{
	public:
		Player(const Strategy&, size_t rounds);
		virtual ~Player();

		char* History = nullptr;
		size_t Score = 0;
		const Strategy& Strategy;
	};

	std::ostream& operator << (std::ostream&, const Player&);
};