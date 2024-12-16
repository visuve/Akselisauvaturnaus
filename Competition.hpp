#pragma once

#include "Player.hpp"

namespace Ast
{
	class Competition
	{
	public:
		Competition(Player*, Player*, size_t rounds);
		~Competition();

		operator bool() const;
		Competition& operator++ ();

		friend std::ostream& operator << (std::ostream&, const Competition&);

	private:
		const size_t _rounds = 0;
		size_t _round = 0;
		Player* _arthur = nullptr;
		Player* _bertha = nullptr;
		bool _clone = false;
	};
}