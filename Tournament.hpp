#pragma once

#include "Competition.hpp"

namespace Ast
{
	class Tournament
	{
	public:
		Tournament(Player** players, size_t playerCount, size_t rounds);
		~Tournament();

		operator bool() const;
		Tournament& operator++();

		void PrintMatrix(std::ostream&) const;
		void PrintTable(std::ostream&) const;

	private:
		Player** _players = nullptr;
		const size_t _playerCount = 0;

		Competition** _competitions = nullptr;
		const size_t _competitionCount = 0;

		size_t _competitionIndex = 0;
	};

	std::ostream& operator << (std::ostream&, const Tournament&);
}