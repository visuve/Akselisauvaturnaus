#pragma once

#include "Strategy.hpp"

namespace Ast
{
	struct IStrategy;

	class Player
	{
	public:
		Player(IStrategy&, size_t rounds);
		virtual ~Player();

		size_t Cooperations() const;
		size_t Defections() const;

		char* History = nullptr;
		size_t Score = 0;
		IStrategy& Strategy;
	};

	std::ostream& operator << (std::ostream&, const Player&);
};